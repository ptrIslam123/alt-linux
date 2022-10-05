#include <gtest/gtest.h>
#include "core/filter/package_filter.h"

TEST(PackageFilter, CheckPackageFiletr) {
    parser::PackagesInfo firstPackagesInfo;
    firstPackagesInfo.packages = {
            {"i586-0ad", "0.0.26"},
            {"i586-4ti2-devel", "1.6.9"},
            {"i586-4ti2-libs", "1.6.9"},
            {"i586-ArxLibertatis-devel", "1.2"},
            {"i586-CTK-devel", "0.1.0"},
            {"i586-CTK-qt5-designer-plugin", "0.1.0"}
    };
    parser::PackagesInfo secondPackagesInfo;
    secondPackagesInfo.packages = {
            {"i586-CTK-qt5-designer-plugin", "0.1.0"},
            {"i586-CTKAppLauncherLib-devel", "0.1.29"},
            {"i586-CUnit", "2.1.3"},
            {"i586-CUnit-devel", "2.1.3"},
            {"i586-FreeAdhocUDF", "3.0.1.20211001"},
            {"i586-0ad", "0.0.26"},
            {"i586-4ti2-libs", "1.6.9"},
    };

    parser::PackagesInfo expectedPackagesInfo;
    expectedPackagesInfo.packages = {
            {"i586-4ti2-devel", "1.6.9"},
            {"i586-ArxLibertatis-devel", "1.2"},
            {"i586-CTK-devel", "0.1.0"}
    };

    auto filter = filter::GetFilterSamePackagesIntoTwoBranches(secondPackagesInfo);
    parser::PackagesInfo result;
    filter::Filter(firstPackagesInfo, filter, result);

    auto &resultPackages = result.packages;
    std::for_each(resultPackages.cbegin(), resultPackages.cend(), [&expectedPackagesInfo](const auto &packageInfo){
        EXPECT_NE(expectedPackagesInfo.packages.find(packageInfo.first), expectedPackagesInfo.packages.cend());
    });
}

TEST(PackageFilter, CheckPackageVersionStrToNumber) {
    const auto v1 = filter::PackageVersionStruct::GetPackageVersionStruct("0.0.1");
    const auto v2 = filter::PackageVersionStruct::GetPackageVersionStruct("1.0.1");
    const auto v3 = filter::PackageVersionStruct::GetPackageVersionStruct("1.1.1");
    const auto v4 = filter::PackageVersionStruct::GetPackageVersionStruct("2.0.1");
    const auto v5 = filter::PackageVersionStruct::GetPackageVersionStruct("2.1.0");
    const auto v6 = filter::PackageVersionStruct::GetPackageVersionStruct("2.0.5");
    const auto v7 = filter::PackageVersionStruct::GetPackageVersionStruct("20.12.534");

    EXPECT_TRUE(v4 > v3 && v4 > v2 && v4 > v1);
    EXPECT_TRUE(v1 < v2 & v1 < v3 & v1 < v4 & v1 < v5);
    EXPECT_TRUE(v7 > v6);
    EXPECT_TRUE(v5 > v4);
}

int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}