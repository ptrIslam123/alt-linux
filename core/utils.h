#ifndef PACKAGE_CHECKER_CORE_H
#define PACKAGE_CHECKER_CORE_H

#include <string>
#include <string_view>

#include "net/http_request.h"
#include "parser/package_parser.h"

namespace core {

parser::PackagesInfo DoHttpsRequest(const std::string &request);
std::string MakeHttpGetRequest(std::string_view host, std::string_view request,
                               std::string_view arch, std::string_view branch);

} // namespace core

#endif //PACKAGE_CHECKER_CORE_H
