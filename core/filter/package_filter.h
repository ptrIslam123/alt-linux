#ifndef PACKAGE_CHECKER_PACKAGE_FILTER_H
#define PACKAGE_CHECKER_PACKAGE_FILTER_H

#include <string>
#include <vector>

#include "core/parser/package_parser.h"
#include "package_version.h"

namespace filter {

typedef parser::PackagesInfo::Packages::const_iterator PackageInfoIter;

const auto GetFilterSamePackagesIntoTwoBranches = [](const parser::PackagesInfo &packagesInfo) {
    return [&otherPackages = packagesInfo](const PackageInfoIter &it) {
        return otherPackages.packages.find(it->first) != otherPackages.packages.cend();
    };
};

const auto GetFilterPackagesWithVersionLessFromOtherBranches = [](const parser::PackagesInfo &packagesInfo) {
    return [&otherPackages = packagesInfo](const PackageInfoIter &it){
        const auto packageVersion = filter::PackageVersionStruct::GetPackageVersionStruct(it->second);
        return packageVersion <= otherPackages.maxPackageVersion;
    };
};

const auto Filter = [](const parser::PackagesInfo &packagesInfo,
                              const auto &filter, parser::PackagesInfo &accumulate) {
    for (auto it = packagesInfo.packages.cbegin(); it != packagesInfo.packages.cend(); ++it) {
        if (!filter(it)) {
            accumulate.packages.insert(std::make_pair(it->first, it->second));
        }
    }
};

} // namespace filter

#endif //PACKAGE_CHECKER_PACKAGE_FILTER_H
