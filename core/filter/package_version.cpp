#include "package_version.h"

#include <string>
#include <stack>
#include <cmath>

namespace filter {

/**
 * @brief for example version: [2.3.1] -> [2 * 10^2 + 3 * 10^1 + 1 * 10^0]
 */
PackageVersionStruct PackageVersionStruct::GetPackageVersionStruct(std::string_view packageVersion) {
    std::stack<int> numberParts;
    auto size = packageVersion.size();

    while (true) {
        const auto curPos = packageVersion.find('.');
        if (curPos >= size) {
            const auto subVersionStr = packageVersion.substr(0, size);
            numberParts.push(std::atoi(subVersionStr.data()));
            break;
        }
        const auto subVersionStr = packageVersion.substr(0, curPos);
        numberParts.push(std::atoi(subVersionStr.data()));
        size -= subVersionStr.size() + 1;
        packageVersion = packageVersion.substr(curPos + 1, size);
    }

    PackageVersionStruct::Version versionValue = 0U;
    for (auto i = 0; numberParts.size() > 0; ++i) {
        versionValue += static_cast<PackageVersionStruct::Version>(numberParts.top() * pow(10, i));
        numberParts.pop();
    }
    return PackageVersionStruct(versionValue);
}

bool PackageVersionStruct::operator<(const PackageVersionStruct &other) const {
    return version_ < other.version_;
}

bool PackageVersionStruct::operator>(const PackageVersionStruct &other) const {
    return version_ > other.version_;
}

bool PackageVersionStruct::operator==(const PackageVersionStruct &other) const {
    return version_ == other.version_;
}

bool PackageVersionStruct::operator<=(const PackageVersionStruct &other) const {
    return version_ <= other.version_;
}

bool PackageVersionStruct::operator>=(const PackageVersionStruct &other) const {
    return version_ >= other.version_;
}

PackageVersionStruct::PackageVersionStruct(const Version version):
        version_(version) {
}

PackageVersionStruct::PackageVersionStruct():
version_(0) {
}

} // namespace filter