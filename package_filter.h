#ifndef PACKAGE_CHECKER_PACKAGE_FILTER_H
#define PACKAGE_CHECKER_PACKAGE_FILTER_H

#include <string>
#include <vector>

#include "core/parser/package_parser.h"
#include "package_version.h"

namespace filter {

typedef parser::PackagesInfo::Packages Packages;
typedef Packages::const_iterator PackageInfoIter;
typedef parser::PackagesInfo::PackageVersion PackageVersion;

const auto GetFilterSamePackagesIntoTwoBranches = [](const Packages &packages) {
    return [&otherPackages = packages](const PackageInfoIter &it) {
        return otherPackages.find(it->first) != otherPackages.cend();
    };
};

const auto GetFilterPackagesWithVersionLessFromOtherBranches = [](const PackageVersion &maxPackageVersion) {
    return [maxPackageVersion](const PackageInfoIter &it){
        const auto packageVersion = filter::PackageVersionStruct::GetPackageVersionStruct(it->second.version);
        return packageVersion <= maxPackageVersion;
    };
};

} // namespace filter

#endif //PACKAGE_CHECKER_PACKAGE_FILTER_H
