#ifndef PACKAGE_CHECKER_PACKAGE_PARSER_H
#define PACKAGE_CHECKER_PACKAGE_PARSER_H

#include <string>
#include <string_view>
#include <map>
#include <iostream>

#include "core/filter/package_version.h"

namespace parser {

struct PackagesInfo {
    typedef std::map<std::string, std::string> Packages;
    typedef filter::PackageVersionStruct PackageVersion;
    Packages packages;
    PackageVersion maxPackageVersion;
};

PackagesInfo ParsePackageJsonData(const std::string &packageJsonData);

void WritePackageInfoTo(std::ostream &outs, std::string_view branch,
                        std::string_view arch, parser::PackagesInfo &&packageInfo);

} // namespace parser

#endif //PACKAGE_CHECKER_PACKAGE_PARSER_H
