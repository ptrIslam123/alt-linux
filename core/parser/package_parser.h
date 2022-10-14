#ifndef PACKAGE_CHECKER_PACKAGE_PARSER_H
#define PACKAGE_CHECKER_PACKAGE_PARSER_H

#include <string>
#include <string_view>
#include <map>
#include <iostream>
#include <vector>

#include "package_version.h"

namespace parser {

struct PackageStruct {
    std::string name;
    int epoch;
    std::string version;
    std::string release;
    std::string arch;
    std::string distTag;
    int buildTime;
    std::string source;

    bool operator==(const PackageStruct &other) const;
    std::ostream &operator<<(std::ostream &ostream) const;
};

class PackagesInfo {
public:
    typedef std::string PackageName;
    typedef std::map<PackageName, PackageStruct> Packages;
    typedef parser::PackageVersionStruct PackageVersion;

    void addPackage(PackageName &&packageName, PackageStruct &&packageStruct);
    void updateMaxPackageVersion(PackageVersion &&packageVersion);
    const Packages &getPackages() const;
    Packages &getPackages();
    const PackageVersion &getMaxPackageVersion() const;
    std::ostream &operator<<(std::ostream &ostream) const;
private:
    Packages packages_;
    PackageVersion maxPackageVersion_;
};

PackagesInfo ParsePackageJsonData(const std::string &packageJsonData);
std::ostream &operator<<(std::ostream &ostream, const PackageStruct &packageStruct);

} // namespace parser

#endif //PACKAGE_CHECKER_PACKAGE_PARSER_H
