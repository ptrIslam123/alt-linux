#include <iostream>
#include <string>
#include <fstream>
#include <array>
#include <string_view>
#include <sstream>

#include "core/parser/package_parser.h"
#include "core/filter/package_filter.h"
#include "core/net/http_request.h"

constexpr auto architecturesCapacity = 6;
const std::array<std::string, architecturesCapacity> architectures = {
        "x86_64-i586",
        "i586",
        "noarch",
        "aarch64",
        "armh",
        "ppc64le",
};

parser::PackagesInfo GetPackagesInfo(net::HttpClient &httpClient, const std::string_view arch,
                                     const std::string_view branchName) {
    static const auto hostName("https://rdb.altlinux.org");
    static const auto httpGetRequest("api/export/branch_binary_packages");

    const auto url = net::MakeHttpGetRequest(hostName, httpGetRequest, arch, branchName);
    const auto [status, response] = httpClient.sendRequest(url);
    if (!status) {
        throw std::runtime_error(response);
    }
    return parser::ParsePackageJsonData(response);
}

parser::PackagesInfo FilterPackages(parser::PackagesInfo &&firstPackagesInfo,
                                    parser::PackagesInfo &&secondPackagesInfo) {
    using namespace filter;
    parser::PackagesInfo resultPackages;
    {
        const auto packageFilterByName = GetFilterSamePackagesIntoTwoBranches(secondPackagesInfo);
        const auto packageFilterByVersion = GetFilterPackagesWithVersionLessFromOtherBranches(secondPackagesInfo);
        const auto filter = [&filterByName = packageFilterByName, &filterByVersion = packageFilterByVersion]
                (const PackageInfoIter &it) {
            return filterByName(it) && filterByVersion(it);
        };
        filter::Filter(firstPackagesInfo, filter, resultPackages);
    }

    {
        const auto packageFilterByName = GetFilterSamePackagesIntoTwoBranches(firstPackagesInfo);
        const auto packageFilterByVersion = GetFilterPackagesWithVersionLessFromOtherBranches(firstPackagesInfo);
        const auto filter = [&filterByName = packageFilterByName, &filterByVersion = packageFilterByVersion]
                (const PackageInfoIter &it) {
            return filterByName(it) && filterByVersion(it);
        };
        filter::Filter(secondPackagesInfo, filter, resultPackages);
    }
    return std::move(resultPackages);
}

void PrintHelpInfo() {
    std::cout << "./package-checker <branch1> <branch2> <output>      - Run analyzer packages for branch1 and branch2\n";
    std::cout << "./package-checker -h                                - Display help info about program" << std::endl;
}

int main(int argc, char **argv) {
    const auto firstArg = std::string_view(argv[1]);
    if (argc == 2 && firstArg == std::string_view("-h")) {
        PrintHelpInfo();
        return EXIT_SUCCESS;
    }

    if (argc != 4) {
        std::cerr << "No passing input args: <branch1> <branch2> <output outputs>" << std::endl;
        return EXIT_FAILURE;
    }

    const auto firstBranchName(argv[1]);
    const auto secondBranchName(argv[2]);
    const auto output(argv[3]);
    net::HttpClient client;
    std::ofstream outputs(output, std::ios::out);
    if (!outputs.is_open()) {
        std::cerr << "Can`t open file: " << output << std::endl;
        return EXIT_FAILURE;
    }

    outputs << "{\n";
    for (auto i = 0; i < architecturesCapacity; ++i) {
        const auto &arch(architectures[i]);
        auto firstPackagesInfo = GetPackagesInfo(client, arch, firstBranchName);
        auto secondPackagesInfo = GetPackagesInfo(client, arch, secondBranchName);

        auto resultPackages = FilterPackages(std::move(firstPackagesInfo),
                                             std::move(secondPackagesInfo));

        std::stringstream branchPair;
        branchPair << firstBranchName << ":" << secondBranchName;
        parser::WritePackageInfoTo(outputs, branchPair.str(), arch, std::move(resultPackages));
        if (i + 1 < architecturesCapacity) {
            outputs << ",\n";
        }
        std::cout << "************************| Analyzed packages for arch: " << arch << std::endl;
    }
    outputs << "\n}" << std::endl;
    return EXIT_SUCCESS;
}