#ifndef PACKAGE_CHECKER_HTTP_REQUEST_H
#define PACKAGE_CHECKER_HTTP_REQUEST_H

#include <string>
#include <curl/curl.h>

namespace net {

class HttpClient {
public:
    typedef std::pair<bool, std::string> Response;

    HttpClient();
    ~HttpClient();

    Response sendRequest(const std::string &url);
private:
    CURL *curlInstance_;
};

} // namespace net

#endif //PACKAGE_CHECKER_HTTP_REQUEST_H
