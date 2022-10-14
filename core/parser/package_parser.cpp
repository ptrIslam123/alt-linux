#include "package_parser.h"

#include <algorithm>

#include "external/json/include/nlohmann/json.hpp"

namespace parser {

PackagesInfo ParsePackageJsonData(const std::string &packageJsonData) {
    using json = nlohmann::json;

    PackagesInfo packageInfo;
    auto responseJson = decltype(json::parse(packageJsonData))();
    try {
        responseJson = json::parse(packageJsonData);
    } catch (...) {
        throw std::runtime_error("Can`t parse data. Invalid json format");
    }

    const auto &packages = responseJson["packages"];

    for (const auto &package : packages) {
        const auto &version = package["version"];
        const auto &name = package["name"];

        PackageStruct packageStruct;
        packageStruct.name = package["name"];
        packageStruct.epoch = package["epoch"];
        packageStruct.version = version;
        packageStruct.release = package["release"];
        packageStruct.arch = package["arch"];
        packageStruct.distTag = package["disttag"];
        packageStruct.buildTime = package["buildtime"];
        packageStruct.source = package["source"];

        packageInfo.addPackage(std::string(name), std::move(packageStruct));
        packageInfo.updateMaxPackageVersion(
                parser::PackageVersionStruct::GetPackageVersionStruct(std::string(version)));
    }

    return std::move(packageInfo);
}

std::ostream &operator<<(std::ostream &ostream, const PackageStruct &packageStruct) {
    return packageStruct.operator<<(ostream);
}

std::ostream &PackagesInfo::operator<<(std::ostream &ostream) const {
    const auto offset = "\t\t";
    ostream << offset << "{\n";
    for (auto it = packages_.cbegin(); it != packages_.cend(); ++it) {
        it->second.operator<<(ostream);
        if (auto next = it; ++next != packages_.cend()) {
            ostream << offset << ",\n";
        }
    }
    ostream << offset << "}\n";
    return ostream;
}

void PackagesInfo::addPackage(PackageName &&packageName,PackageStruct &&packageStruct) {
    packages_.insert(std::make_pair(packageName, packageStruct));
}

void PackagesInfo::updateMaxPackageVersion(PackagesInfo::PackageVersion &&packageVersion) {
    maxPackageVersion_ = std::max(maxPackageVersion_, packageVersion);
}

const PackagesInfo::Packages &PackagesInfo::getPackages() const {
    return packages_;
}

const PackagesInfo::PackageVersion &PackagesInfo::getMaxPackageVersion() const {
    return maxPackageVersion_;
}

PackagesInfo::Packages &PackagesInfo::getPackages() {
    return packages_;
}

std::ostream &PackageStruct::operator<<(std::ostream &ostream) const {
    const auto offset = "\t\t\t";
    ostream << offset << "{\n";
    ostream << offset << "\t\"name\": \"" << name << "\",\n";
    ostream << offset << "\t\"epoch\": " << epoch << ",\n";
    ostream << offset << "\t\"version\": \"" << version << "\",\n";
    ostream << offset << "\t\"release\": \"" << release << "\",\n";
    ostream << offset << "\t\"arch\": \"" << arch << "\",\n";
    ostream << offset << "\t\"disttag\": \""  << distTag << "\",\n";
    ostream << offset << "\t\"buildtime\": " << buildTime << ",\n";
    ostream << offset << "\t\"source\": \"" << source << "\"\n";
    ostream << offset << "}\n";
    return ostream;
}

bool PackageStruct::operator==(const PackageStruct &other) const {
    const auto isEqName = name == other.name;
    const auto isEqEpoch = epoch == other.epoch;
    const auto isEqVersion = version == other.version;
    const auto isEqRelease = release == other.release;
    const auto isEqArch = arch == other.arch;
    const auto isEqDistTag = distTag == other.distTag;
    const auto isEqBuildTime = buildTime == other.buildTime;
    const auto isEqSource = source == other.source;
    return isEqName && isEqEpoch && isEqVersion && isEqRelease && isEqArch && isEqDistTag &&
            isEqBuildTime && isEqSource;
}

} // namespace parser