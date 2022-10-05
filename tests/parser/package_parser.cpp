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
    expectedPackageInfo.packages = {
            {"i586-0ad", "0.0.26"},
            {"i586-4ti2-devel", "1.6.9"}
    };

    std::for_each(packageInfo.packages.cbegin(), packageInfo.packages.cend(),
                  [&expectedPackageInfo](const auto &info){
        const auto expectInfo = expectedPackageInfo.packages.find(info.first);
        EXPECT_FALSE(expectInfo == expectedPackageInfo.packages.cend());
        EXPECT_EQ(expectInfo->second, info.second);
    });
}

int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}