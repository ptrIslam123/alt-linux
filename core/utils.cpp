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

void SerializePackageInfoTo(std::ostream &outs, const JsonDataType dataType, const parser::PackagesInfo &packageInfo) {

}

} // namespace core