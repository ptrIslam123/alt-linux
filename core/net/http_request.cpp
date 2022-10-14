#include "http_request.h"

#include <stdexcept>
#include <vector>
#include <cstring>

namespace {

struct MemBuffer {
    explicit MemBuffer(const size_t size):
    buffer(size, '\0'), size(0)
    {}

    std::vector<char> buffer;
    size_t size;
};

size_t ReceiveDataEventHandler(const void *const ptr, const size_t size, const size_t receiveBufferSize,
                               void *const memBufferStream) {
    auto const memBuffer = static_cast<MemBuffer*>(memBufferStream);
    auto &buffer = memBuffer->buffer;
    const auto buffSize = memBuffer->size;
    const auto buffCapacity = buffer.size();
    if (buffCapacity < buffSize + receiveBufferSize) {
        buffer.resize(buffCapacity * 2);
    }

    std::memcpy(buffer.data() + buffSize, ptr, receiveBufferSize);
    memBuffer->size += receiveBufferSize;
    return size * receiveBufferSize;
}

} // namespace

namespace net {

HttpClient::HttpClient():
curlInstance_(nullptr) {
    curl_global_init(CURL_GLOBAL_ALL);
}

HttpClient::~HttpClient() {
    curl_global_cleanup();
}

HttpClient::Response HttpClient::sendRequest(const std::string &url) {
    curlInstance_ = curl_easy_init();
    if (curlInstance_ == nullptr) {
        throw std::runtime_error("Can`t init curl instance");
    }

    MemBuffer rawMemory(65536);
    curl_easy_setopt(curlInstance_, CURLOPT_URL, url.data());
    curl_easy_setopt(curlInstance_, CURLOPT_WRITEFUNCTION, ReceiveDataEventHandler);
    curl_easy_setopt(curlInstance_, CURLOPT_WRITEDATA, &rawMemory);

    const auto responseBuff = curl_easy_perform(curlInstance_);
    auto response = std::make_pair(false, std::string());
    if (responseBuff != CURLE_OK) {
        response.second = std::string(curl_easy_strerror(responseBuff));
    } else {
        response.first = true;
        response.second = std::string(rawMemory.buffer.data());
    }
    curl_easy_cleanup(curlInstance_);
    rawMemory.size = 0;
    rawMemory.buffer.clear();
    return std::move(response);
}

} // namespace net