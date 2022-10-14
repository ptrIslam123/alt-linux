#include <gtest/gtest.h>
#include "core/parser/package_parser.h"

TEST(Parser, ChechParsePackageJsonData) {
    auto examplePackageJsonData = R"({
        "request_args": {
            "arch": "x86_64-i586"
        },
        "length": 2,
        "packages": [
            {
              "name": "i586-0ad",
              "epoch": 1,
              "version": "0.0.26",
              "release": "alt0_0_rc1.p10",
              "arch": "x86_64-i586",
              "disttag": "p10+303432.100.3.1",
              "buildtime": 1657804386,
              "source": ""
            },
            {
              "name": "i586-4ti2-devel",
              "epoch": 0,
              "version": "1.6.9",
              "release": "alt1_7",
              "arch": "x86_64-i586",
              "disttag": "sisyphus+258318.100.1.1",
              "buildtime": 1600446138,
              "source": ""
            }
        ]
    })";

    const auto packageInfo = parser::ParsePackageJsonData(examplePackageJsonData);
    parser::PackagesInfo expectedPackageInfo;
    {
        parser::PackageStruct package;
        package.name = "i586-4ti2-devel";
        package.epoch = 0;
        package.version = "1.6.9";
        package.release = "alt1_7";
        package.arch = "x86_64-i586";
        package.distTag = "sisyphus+258318.100.1.1";
        package.buildTime = 1600446138;
        package.source = "";
        expectedPackageInfo.addPackage(std::string(package.name), std::move(package));
    }
    {
        parser::PackageStruct package;
        package.name = "i586-0ad";
        package.epoch = 1;
        package.version = "0.0.26";
        package.release = "alt0_0_rc1.p10";
        package.arch = "x86_64-i586";
        package.distTag = "p10+303432.100.3.1";
        package.buildTime = 1657804386;
        package.source = "";
        expectedPackageInfo.addPackage(std::string(package.name), std::move(package));
    }

    const auto &packages = packageInfo.getPackages();
    std::for_each(packages.cbegin(), packages.cend(),
                  [&expectedPackageInfo](const auto &info){
        const auto expectPackage = expectedPackageInfo.getPackages().find(info.first);
        EXPECT_FALSE(expectPackage == expectedPackageInfo.getPackages().cend());
        EXPECT_EQ(expectPackage->second, info.second);
    });
}

int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}