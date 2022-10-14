#include <iostream>
#include <string>
#include <array>
#include <string_view>

#include "core/utils.h"
#include "package_filter.h"

constexpr auto architecturesCapacity = 6;
const std::array<std::string, architecturesCapacity> architectures = {
        "x86_64-i586",
        "i586"
        "noarch",
        "aarch64",
        "armh",
        "ppc64le",
};

std::string GetHttpsRequestUrl(const std::string_view arch, const std::string_view branchName) {
    static const auto hostName("https://rdb.altlinux.org");
    static const auto httpGetRequest("api/export/branch_binary_packages");
    return core::MakeHttpGetRequest(hostName, httpGetRequest, arch, branchName);
}

void WriteOutputPackageListTo(std::ostream &ostream, const std::string_view firstBranch,
                              const std::string_view secondBranch, const std::string_view arch,
                              const filter::FilteredPackageList &filteredPackageList) {
    const auto offset = "\t";
    const auto writePackagesToStream = [&ostream, offset](const auto &packages){
        for (auto i = 0; i < packages.size(); ++i) {
            ostream  << packages[i];
            if (i + 1 < packages.size()) {
                ostream << offset << "\t\t" << ",\n";
            }
        }
    };

    ostream << offset << "\"for_arch\": \"" << arch << "\",\n";
    ostream << offset << "\"report\": [\n";
        ostream << offset << "\t{\n";
        ostream << offset << "\t\t\"unique_package_from_" << firstBranch << "\": [\n";
        writePackagesToStream(filteredPackageList[0]);
        ostream << offset << "\t\t]\n" << offset << "\t,\n";

        ostream << offset << "\t\t\"unique_packages_from_" << secondBranch << "\":[\n ";
        writePackagesToStream(filteredPackageList[1]);
        ostream << offset << "\t\t]\n" << offset << "\t\t,\n";

        ostream << offset << "\t\t\"packages_whose_version_is_greater_that_" << secondBranch << "\": [\n";
        writePackagesToStream(filteredPackageList[2]);
        ostream << offset << "\t\t]\n";
        ostream << offset << "\t}\n";
    ostream << offset << "]\n";
}

void GetPackagesDiffAndWriteTo(const std::string_view firstBranch, const std::string_view secondBranch,
                               std::ostream &outputs) {
    outputs << "{\n";
    filter::FilteredPackageList filteredPackageList;
    for (auto i = 0; i < architecturesCapacity; ++i) {
        const auto &arch(architectures[i]);
        auto firstPackagesInfo = core::DoHttpsRequest(GetHttpsRequestUrl(arch, firstBranch));
        auto secondPackagesInfo = core::DoHttpsRequest(GetHttpsRequestUrl(arch, secondBranch));

        filter::FilterPackages(std::move(firstPackagesInfo), std::move(secondPackagesInfo), filteredPackageList);
        WriteOutputPackageListTo(outputs, firstBranch, secondBranch, arch, filteredPackageList);
        std::for_each(filteredPackageList.begin(), filteredPackageList.end(), [](auto &packages){
            packages.clear();
        });

        if (i + 1 < architecturesCapacity) {
            outputs << ",\n";
        }
    }
    outputs << "\n}" << std::endl;
}

void PrintHelpInfo() {
    std::cout << "./package-checker <branch1> <branch2>       - Run analyzer packages for branch1 and branch2\n";
    std::cout << "./package-checker -h                         - Display help info about program" << std::endl;
}

int main(int argc, char **argv) {
    if (argc != 2 && argc != 4) {
        std::cerr << "No passing input args: <branch1> <branch2>" << std::endl;
        return EXIT_FAILURE;
    }

    const auto firstArg = std::string_view(argv[1]);
    if (argc == 2 && firstArg == std::string_view("-h")) {
        PrintHelpInfo();
        return EXIT_SUCCESS;
    }

    const auto firstBranchName(argv[1]);
    const auto secondBranchName(argv[2]);
    GetPackagesDiffAndWriteTo(firstBranchName, secondBranchName, std::cout);
    return EXIT_SUCCESS;
}