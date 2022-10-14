#include "package_filter.h"

namespace {

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
        const auto packageVersion = parser::PackageVersionStruct::GetPackageVersionStruct(it->second.version);
        return packageVersion <= maxPackageVersion;
    };
};

} // namespace

namespace filter {

void FilterPackages(parser::PackagesInfo &&firstPackagesInfo,
                    parser::PackagesInfo &&secondPackagesInfo,
                    FilteredPackageList &output) {
    using namespace filter;
    const auto filterForFirstSection =
           GetFilterSamePackagesIntoTwoBranches(secondPackagesInfo.getPackages());
    const auto filterForSecondSection =
            GetFilterSamePackagesIntoTwoBranches(firstPackagesInfo.getPackages());
    const auto filterForThirdSection =
            GetFilterPackagesWithVersionLessFromOtherBranches(secondPackagesInfo.getMaxPackageVersion());

    auto firstIt = firstPackagesInfo.getPackages().cbegin();
    auto secondIt = secondPackagesInfo.getPackages().cbegin();
    const auto secondItEnd = secondPackagesInfo.getPackages().cend();
    const auto firstItEnd = firstPackagesInfo.getPackages().cend();

    while (firstIt != firstItEnd && secondIt != secondItEnd) {
        if (firstIt != firstItEnd) {
            if (!filterForFirstSection(firstIt)) {
                output[0].push_back(firstIt->second);
            }
            if (!filterForThirdSection(firstIt)) {
                output[2].push_back(firstIt->second);
                ++firstIt;
            }
            ++firstIt;
        }

        if (secondIt != secondItEnd) {
            if (!filterForSecondSection(secondIt)) {
                output[1].push_back(secondIt->second);
            }
            ++secondIt;
        }
    }
}

} // namespace filter