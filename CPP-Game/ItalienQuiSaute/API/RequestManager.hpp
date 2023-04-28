// RequestManager.h

#ifndef REQUESTMANAGER_H
#define REQUESTMANAGER_H

#include <iostream>
#include <string>
#include <curl/curl.h>

class RequestManager {
public:
    RequestManager() {
        curl_global_init(CURL_GLOBAL_DEFAULT);
    }

    ~RequestManager() {
        curl_global_cleanup();
    }

    static size_t headerCallback(char* buffer, size_t size, size_t nitems, void* userData) {
        std::string headerLine(buffer, size * nitems);
        std::string authTokenHeader = "Authorization: ";
        size_t pos = headerLine.find(authTokenHeader);
        if (pos != std::string::npos) {
            std::string authToken = headerLine.substr(pos + authTokenHeader.size());
            authToken.erase(std::remove(authToken.begin(), authToken.end(), '\r'), authToken.end());
            authToken.erase(std::remove(authToken.begin(), authToken.end(), '\n'), authToken.end());
            std::string* authTokenPtr = static_cast<std::string*>(userData);
            *authTokenPtr = authToken;
        }
        return size * nitems;
    }

    std::string login(const std::string& username, const std::string& email, const std::string& password) {
        // Construct login request body with username, email, and password
        std::string jsonBody_ = "{\"username\": \"" + username + "\", \"email\": \"" + email + "\", \"password\": \"" + password + "\"}";
        std::string authToken_;
        std::string response_;
        // Set the request headers
        struct curl_slist* headers = nullptr;
        headers = curl_slist_append(headers, "Content-Type: application/json");

        // Set the request options and perform the request
        CURL* curl = curl_easy_init();
        if (curl) {
            curl_easy_setopt(curl, CURLOPT_URL, "http://192.168.0.23:7865/login");
            curl_easy_setopt(curl, CURLOPT_POST, 1L);
            curl_easy_setopt(curl, CURLOPT_POSTFIELDS, jsonBody_.c_str());
            curl_easy_setopt(curl, CURLOPT_POSTFIELDSIZE, jsonBody_.size());
            curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);

            // Set the write callback to store the response body in the response_ string
            curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, writeCallback);
            curl_easy_setopt(curl, CURLOPT_WRITEDATA, &response_);

            // Set the header callback to retrieve the auth token from the response headers
            curl_easy_setopt(curl, CURLOPT_HEADERFUNCTION, headerCallback);
            curl_easy_setopt(curl, CURLOPT_HEADERDATA, &authToken_);

            // Perform the request
            CURLcode res = curl_easy_perform(curl);
            if (res != CURLE_OK) {
                std::cerr << "curl_easy_perform() failed: " << curl_easy_strerror(res) << std::endl;
            }

            std::cout << response_;

            // Clean up curl handle and headers
            curl_easy_cleanup(curl);
            curl_slist_free_all(headers);
        }

        return authToken_;
    }


    // Newscore function to submit a score for a game
    void newscore(int score, const std::string& game, const std::string& authToken) {
        CURL* curl = curl_easy_init();
        if (curl) {
            // Construct newscore URL
            std::string newscoreUrl = "http://192.168.0.23:7865/newscore";

            // Construct newscore request body as a JSON string
            std::string requestBody = "{\"score\":" + std::to_string(score) + ",\"game\":\"" + game + "\"}";

            // Set up curl options for newscore request
            curl_easy_setopt(curl, CURLOPT_URL, newscoreUrl.c_str());
            curl_easy_setopt(curl, CURLOPT_CUSTOMREQUEST, "PUT");
            curl_easy_setopt(curl, CURLOPT_POSTFIELDS, requestBody.c_str());

            // Set Content-Type header to application/json
            struct curl_slist* headers = NULL;
            headers = curl_slist_append(headers, "Content-Type: application/json");
            // Set Authorization header with auth token
            std::string authHeader = "Authorization: " + authToken;
            headers = curl_slist_append(headers, authHeader.c_str());
            curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);

            // Perform newscore request
            CURLcode res = curl_easy_perform(curl);
            if (res != CURLE_OK) {
                std::cerr << "curl_easy_perform() failed: " << curl_easy_strerror(res) << std::endl;
            }

            // Clean up curl handle and headers
            curl_easy_cleanup(curl);
            curl_slist_free_all(headers);
        }
    }
private:
    // Callback function to write response data to a string
    static size_t writeCallback(void* contents, size_t size, size_t nmemb, void* userp) {
        ((std::string*)userp)->append((char*)contents, size * nmemb);
        return size * nmemb;
    }
};

#endif