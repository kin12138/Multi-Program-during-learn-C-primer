//
// Created by libin on 2025/6/20.
//

#include "Fetcher.h"
#include <curl/curl.h>
#include <stdexcept>

static size_t writeCallback(void * ptr, size_t size, size_t nmemb, void * userdata) {
    auto *out = static_cast<std::string*> (userdata);
    out->append(static_cast<char*> (ptr), size * nmemb);
    return size * nmemb;
}

std::string Fetcher::fetch(const std::string &url) {
    CURL * curl = curl_easy_init();
    if (!curl) throw std::runtime_error("curl init failed");
    std::string response;
    curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, writeCallback);
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, &response);
    curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1L);

    CURLcode res = curl_easy_perform(curl);
    curl_easy_cleanup(curl);
    if (res != CURLE_OK)
        throw std::runtime_error(curl_easy_strerror(res));
    return response;
}