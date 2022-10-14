#ifndef PACKAGE_CHECKER_PACKAGE_FILTER_H
#define PACKAGE_CHECKER_PACKAGE_FILTER_H

#include <string>
#include <vector>

#include "core/parser/package_parser.h"
#include "core/parser/package_version.h"

namespace filter {

constexpr auto outputJsonDataSectionCapacity = 3;
typedef std::array<std::vector<parser::PackageStruct>, outputJsonDataSectionCapacity> FilteredPackageList;

void FilterPackages(parser::PackagesInfo &&firstPackagesInfo,
                    parser::PackagesInfo &&secondPackagesInfo,
                    FilteredPackageList &output);

} // namespace filter

#endif //PACKAGE_CHECKER_PACKAGE_FILTER_H
