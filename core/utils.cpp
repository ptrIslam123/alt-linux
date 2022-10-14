#include "utils.h"
#include <sstream>

namespace core {

parser::PackagesInfo DoHttpsRequest(const std::string &request) {
    static net::HttpClient httpClient;
    const auto [status, response] = httpClient.sendRequest(request);
    if (!status) {
        throw std::runtime_error("Invalid http get request: " + response);
    }
    return parser::ParsePackageJsonData(response);
}

std::string MakeHttpGetRequest(const std::string_view host, const std::string_view request,
                               const std::string_view arch, const std::string_view branch) {
    std::stringstream oss;
    oss << host << "/";
    oss << request << "/";
    oss << branch << "?arch=";
    oss << arch;
    return oss.str();
}

} // namespace core