#ifndef REQUESTMANAGER_H
#define REQUESTMANAGER_H

#include "nlohmann/json.hpp"

#include <curl/curl.h>
#include <iostream>
#include <string>
#include <vector>

class RequestManager
{
public:
	RequestManager()
	{
		curl_global_init(CURL_GLOBAL_DEFAULT);
	}

	~RequestManager()
	{
		curl_global_cleanup();
	}

	std::string login(const std::string& username, const std::string& email, const std::string& password)
	{
		//Request body
		std::string jsonBody = "{\"username\": \"" + username + "\", \"email\": \"" + email + "\", \"password\": \"" + password + "\"}";
		std::string authToken;
		std::string response;

		//Headers
		struct curl_slist* headers = nullptr;
		headers = curl_slist_append(headers, "Content-Type: application/json");

		// Set the request options and perform the request
		CURL* curl = curl_easy_init();
		if (curl)
		{
			curl_easy_setopt(curl, CURLOPT_URL, "https://api.mathistitouan.com/login");
			curl_easy_setopt(curl, CURLOPT_POST, 1L);
			curl_easy_setopt(curl, CURLOPT_POSTFIELDS, jsonBody.c_str());
			curl_easy_setopt(curl, CURLOPT_POSTFIELDSIZE, jsonBody.size());
			curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);

			//Write callback
			curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, writeCallback);
			curl_easy_setopt(curl, CURLOPT_WRITEDATA, &response);

			//Header callback
			curl_easy_setopt(curl, CURLOPT_HEADERFUNCTION, headerCallback);
			curl_easy_setopt(curl, CURLOPT_HEADERDATA, &authToken);

			//Send Request
			CURLcode res = curl_easy_perform(curl);
			if (res != CURLE_OK)
			{
				std::cerr << "curl_easy_perform() failed: " << curl_easy_strerror(res) << std::endl;
			}

			std::cout << response;

			//Clean up
			curl_easy_cleanup(curl);
			curl_slist_free_all(headers);
		}
		return authToken;
	}

	std::string signIn(const std::string& username, const std::string& email, const std::string& password)
	{
		//Request body
		std::string jsonBody = "{\"username\": \"" + username + "\", \"email\": \"" + email + "\", \"password\": \"" + password + "\"}";
		std::string response;

		//Headers
		struct curl_slist* headers = nullptr;
		headers = curl_slist_append(headers, "Content-Type: application/json");

		// Set the request options and perform the request
		CURL* curl = curl_easy_init();
		if (curl)
		{
			curl_easy_setopt(curl, CURLOPT_URL, "https://api.mathistitouan.com/signin");
			curl_easy_setopt(curl, CURLOPT_POST, 1L);
			curl_easy_setopt(curl, CURLOPT_POSTFIELDS, jsonBody.c_str());
			curl_easy_setopt(curl, CURLOPT_POSTFIELDSIZE, jsonBody.size());
			curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);

			//Write callback
			curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, writeCallback);
			curl_easy_setopt(curl, CURLOPT_WRITEDATA, &response);

			//Send Request
			CURLcode res = curl_easy_perform(curl);
			if (res != CURLE_OK)
			{
				std::cerr << "curl_easy_perform() failed: " << curl_easy_strerror(res) << std::endl;
			}

			std::cout << response;

			//Clean up
			curl_easy_cleanup(curl);
			curl_slist_free_all(headers);
		}
		return response;
	}

	void newscore(int score, const std::string& game, const std::string& authToken)
	{
		CURL* curl = curl_easy_init();
		if (curl)
		{
			std::string newscoreUrl = "https://api.mathistitouan.com/newscore";

			//Request body
			std::string requestBody = "{\"score\":" + std::to_string(score) + ",\"game\":\"" + game + "\"}";

			//Set up curl options for newscore request
			curl_easy_setopt(curl, CURLOPT_URL, newscoreUrl.c_str());
			curl_easy_setopt(curl, CURLOPT_CUSTOMREQUEST, "PUT");
			curl_easy_setopt(curl, CURLOPT_POSTFIELDS, requestBody.c_str());

			//Content-Type
			struct curl_slist* headers = NULL;
			headers = curl_slist_append(headers, "Content-Type: application/json");

			//Authorization header
			std::string authHeader = "Authorization: " + authToken;
			headers = curl_slist_append(headers, authHeader.c_str());
			curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);

			//Send request
			CURLcode res = curl_easy_perform(curl);
			if (res != CURLE_OK)
			{
				std::cerr << "curl_easy_perform() failed: " << curl_easy_strerror(res) << std::endl;
			}
			//Clean up
			curl_easy_cleanup(curl);
			curl_slist_free_all(headers);
		}
	}

	using json = nlohmann::json;

	std::string Scorelist()
	{
		struct PseudoScore
		{
			std::string pseudo;
			int score;
		};

		std::vector<PseudoScore> arr;

		// Initialize libcurl
		CURL* curl = curl_easy_init();

		if (curl)
		{
			// Fetch the player score list
			std::string score_list_url = "https://api.mathistitouan.com/scoreboard/MARIO";
			std::string score_list_response;
			curl_easy_setopt(curl, CURLOPT_URL, score_list_url.c_str());
			curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, writeCallback);
			curl_easy_setopt(curl, CURLOPT_WRITEDATA, &score_list_response);
			CURLcode res = curl_easy_perform(curl);

			if (res == CURLE_OK)
			{
				std::cout << "Player score list response: " << score_list_response << std::endl;
			}
			else
			{
				std::cerr << "Failed to fetch player score list: " << curl_easy_strerror(res) << std::endl;
			}

			// Clean up libcurl resources
			curl_easy_cleanup(curl);

			// Parse Results
			if (!score_list_response.empty())
			{
				try
				{
					json root = json::parse(score_list_response);
					for (const auto& item : root)
					{
						std::string pseudo = item["user"].get<std::string>();
						int score = item["score"].get<int>();
						PseudoScore ps = { pseudo, score };
						arr.push_back(ps);
					}
				}
				catch (const json::parse_error& e)
				{
					std::cerr << "Failed to parse JSON string: " << e.what() << std::endl;
				}
			}

			std::string result = "";
			for (const auto& ps : arr)
			{
				result += "Pseudo: " + ps.pseudo + ", Score: " + std::to_string(ps.score) + "\n";
			}

			if (arr.empty())
			{
				result = "Error parsing JSON, raw data response:\n" + score_list_response;
			}
			std::cout << result;
			return result;
		}
		return "no curl";
	}

private:

	// Callback function to write token to a string
	static size_t headerCallback(char* buffer, size_t size, size_t nitems, void* userData)
	{
		std::string headerLine(buffer, size * nitems);
		std::string authTokenHeader = "Authorization: ";
		size_t pos = headerLine.find(authTokenHeader);
		if (pos != std::string::npos)
		{
			std::string authToken = headerLine.substr(pos + authTokenHeader.size());
			authToken.erase(std::remove(authToken.begin(), authToken.end(), '\r'), authToken.end());
			authToken.erase(std::remove(authToken.begin(), authToken.end(), '\n'), authToken.end());
			std::string* authTokenPtr = static_cast<std::string*>(userData);
			*authTokenPtr = authToken;
		}
		return size * nitems;
	}
	// Callback function to write response data to a string
	static size_t writeCallback(void* contents, size_t size, size_t nmemb, void* userp)
	{
		((std::string*)userp)->append((char*)contents, size * nmemb);
		return size * nmemb;
	}
};
#endif
