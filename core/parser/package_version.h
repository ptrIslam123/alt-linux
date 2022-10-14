#ifndef PACKAGE_CHECKER_PACKAGE_VERSION_H
#define PACKAGE_CHECKER_PACKAGE_VERSION_H

#include <string_view>

namespace parser {

class PackageVersionStruct {
public:
    typedef unsigned int Version;
    explicit PackageVersionStruct();
    PackageVersionStruct(const PackageVersionStruct &other) = default;
    PackageVersionStruct(PackageVersionStruct &&other) = default;
    PackageVersionStruct &operator=(const PackageVersionStruct &other) = default;
    PackageVersionStruct &operator=(PackageVersionStruct &&other) = default;

    bool operator<(const PackageVersionStruct &other) const;
    bool operator>(const PackageVersionStruct &other) const;
    bool operator==(const PackageVersionStruct &other) const;
    bool operator<=(const PackageVersionStruct &other) const;
    bool operator>=(const PackageVersionStruct &other) const;

    static PackageVersionStruct GetPackageVersionStruct(std::string_view packageVersion);
private:
    explicit PackageVersionStruct(Version version);
    Version version_;
};

} // namespace parser

#endif //PACKAGE_CHECKER_PACKAGE_VERSION_H
