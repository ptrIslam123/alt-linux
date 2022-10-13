#ifndef PACKAGE_CHECKER_CORE_H
#define PACKAGE_CHECKER_CORE_H

#include <string>
#include <string_view>

#include "net/http_request.h"
#include "parser/package_parser.h"

namespace core {

parser::PackagesInfo DoHttpsRequest(const std::string &request);

enum class JsonDataType {
    PackagesFilteredToFirstBranch,
    PackagesFilteredToSecondBranch,
    PackagesFilteredByPackageVersion
};


} // namespace core

#endif //PACKAGE_CHECKER_CORE_H
