#include "package_parser.h"

#include <algorithm>

#include "external/json/include/nlohmann/json.hpp"

namespace parser {

PackagesInfo ParsePackageJsonData(const std::string &packageJsonData) {
    using json = nlohmann::json;

    PackagesInfo packageInfo;
    const auto responseJson = json::parse(packageJsonData);
    const auto &arch = responseJson["request_args"]["arch"];
    const auto &packages = responseJson["packages"];

    for (const auto &package : packages) {
        const auto &name = package["name"];
        const auto &version = package["version"];
        {
            const auto curPackageVersion = filter::PackageVersionStruct::GetPackageVersionStruct(std::string(version));
            packageInfo.maxPackageVersion = std::max(packageInfo.maxPackageVersion, curPackageVersion);
        }
        packageInfo.packages.insert(std::make_pair(name, version));
    }

    return std::move(packageInfo);
}

void WritePackageInfoTo(std::ostream &outs, const std::string_view branchPair,
                        const std::string_view arch, parser::PackagesInfo &&packageInfo) {
    outs << "\t\"branch_pair\": " << "\"" << branchPair << "\",\n";
    outs << "\t\"arch\": " << "\"" << arch << "\",\n";
    outs << "\t\"packages\": [\n";
    outs << "\t\t{\n";
    const auto &packages = packageInfo.packages;
    for (auto it = packages.cbegin(); it != packages.cend(); ++it) {
        outs << "\t\t\t\"name\": " << "\"" << it->first << "\", ";
        outs << "\"version\": " << "\"" << it->second << "\"";

        const auto eof = it == --packages.cend();
        if (!eof) {
            outs << ",\n";
        } else {
            outs << "\n";
        }
    }
    outs << "\t\t}\n";
    outs << "\t]\n";
}


} // namespace parser