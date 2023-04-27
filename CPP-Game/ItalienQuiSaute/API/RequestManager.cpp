#include "RequestManager.h"

size_t RequestManager::WriteCallback(void* contents, size_t size, size_t nmemb, void* userp) {
	((std::string*)userp)->append((char*)contents, size * nmemb);
	return size * nmemb;
}


size_t RequestManager::HeaderCallback(char* buffer, size_t size, size_t nitems, void* userdata)
{
	std::string header(buffer, size * nitems);
	const std::string auth_header_prefix = "Authorization: ";
	if (header.find(auth_header_prefix) != std::string::npos) {
		std::string auth_token = header.substr(auth_header_prefix.length());
		*(std::string*)userdata = auth_token;
	}
	return size * nitems;
}


void RequestManager::Login(std::string username, std::string email, std::string password) {
	CURL* curl = curl_easy_init();
	if (curl) {
		// Set Content-Type header to application/json
		slist1 = curl_slist_append(slist1, "Accept: application/json");
		slist1 = curl_slist_append(slist1, "Content-Type: application/json");
		slist1 = curl_slist_append(slist1, "charset: utf-8");

		// Construct the request body 
		std::string request = "{\"username\": \"" + username + "\", \"email\": \"" + email + "\", \"password\": \"" + password + "\"}";
		std::cout << request;

		// Set up the libcurl options
		std::string login_url = BASE_URL + LOGIN_ENDPOINT;
		std::string login_response;
		curl_easy_setopt(curl, CURLOPT_URL, login_url.c_str());
		curl_easy_setopt(curl, CURLOPT_HTTPHEADER, slist1);
		curl_easy_setopt(curl, CURLOPT_POSTFIELDS, request.c_str());
		curl_easy_setopt(curl, CURLOPT_POST, 1L);
		curl_easy_setopt(curl, CURLOPT_HEADERFUNCTION, HeaderCallback);
		curl_easy_setopt(curl, CURLOPT_HEADERDATA, &auth_token);
		curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
		curl_easy_setopt(curl, CURLOPT_WRITEDATA, &login_response);
		CURLcode res = curl_easy_perform(curl);

		// Handle the response
		if (res == CURLE_OK) {
			std::cout << "Login response: " << login_response << std::endl;
		}
		else {
			std::cerr << "Failed to perform login: " << curl_easy_strerror(res) << std::endl;
		}

		// Clean up libcurl resources
		curl_easy_cleanup(curl);
		curl_slist_free_all(slist1);
	}
}





void RequestManager::SignIn(std::string username, std::string email, std::string password) {
	CURL* curl = curl_easy_init();
	if (curl) {
		slist1 = curl_slist_append(slist1, "Content-Type: application/json");

		std::string signin_url = BASE_URL + SIGNIN_ENDPOINT;
		std::string signin_response;
		std::string request = "{\"username\": \"" + username + "\", \"email\": \"" + email + "\", \"password\": \"" + password + "\"}";
		curl_easy_setopt(curl, CURLOPT_URL, signin_url.c_str());
		curl_easy_setopt(curl, CURLOPT_HTTPHEADER, slist1 );
		curl_easy_setopt(curl, CURLOPT_POSTFIELDS, request.c_str());
		curl_easy_setopt(curl, CURLOPT_POST);
		curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
		curl_easy_setopt(curl, CURLOPT_WRITEDATA, &signin_response);
		CURLcode res = curl_easy_perform(curl);
		std::cout << request.c_str();

		if (res == CURLE_OK) {
			Json::Value root;
			Json::Reader reader;
			bool parsingSuccessful = reader.parse(signin_response, root);
			std::cout << "Signin response: " << signin_response << std::endl;
			std::cout << "Signin response: " << root << std::endl;
		}
		else {
			std::cerr << "Failed to perform signin: " << curl_easy_strerror(res) << std::endl;
		}

		// Clean up libcurl resources
		curl_easy_cleanup(curl);
	}
}



std::string RequestManager::Scorelist() {

	struct PseudoScore {
		std::string pseudo;
		int score;
	};
	std::vector<PseudoScore> arr;


	// Initialize libcurl
	CURL* curl = curl_easy_init();

	if (curl) {
		// Fetch the player score list
		std::string score_list_url = BASE_URL + SCORE_LIST_ENDPOINT;
		std::string score_list_response;
		curl_easy_setopt(curl, CURLOPT_URL, score_list_url.c_str());
		curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
		curl_easy_setopt(curl, CURLOPT_WRITEDATA, &score_list_response);
		CURLcode res = curl_easy_perform(curl);

		if (res == CURLE_OK) {
			std::cout << "Player score list response: " << score_list_response << std::endl;
		}
		else {
			std::cerr << "Failed to fetch player score list: " << curl_easy_strerror(res) << std::endl;
		}
		// Clean up libcurl resources
		curl_easy_cleanup(curl);

		//Parse Results
		Json::Value root;
		Json::Reader reader;
		bool parsingSuccessful = reader.parse(score_list_response, root);
		if (parsingSuccessful) {
			for (int i = 0; i < root.size(); i++) {

				std::string pseudo = root[i]["user"].asString();
				int score = root[i]["score"].asInt();
				PseudoScore ps = { pseudo, score };
				arr.push_back(ps);
			}
		}
		else {
			std::cout << "Failed to parse JSON string" << std::endl;
		}

		score_list_response = "";

		for (int i = 0; i < arr.size(); i++) {
			score_list_response += "Pseudo: " + arr[i].pseudo + ", Score: " + std::to_string(arr[i].score) + "\n";
		}



		return score_list_response;
	}
	return "no curl";
}

void RequestManager::NewScore(int score) {
	// Initialize libcurl
	CURL* curl = curl_easy_init();

	if (curl) {
		// Update or insert a player's score
		
		std::string authorization_header = "Authorization: " + auth_token;
		slist1 = curl_slist_append(slist1, authorization_header.c_str());
		slist1 = curl_slist_append(slist1, "Content-Type: application/json");
		
		std::string new_score_url = BASE_URL + NEW_SCORE_ENDPOINT;
		std::string new_score_response;
		std::string request = "{\"score\": " + std::to_string(score) + ",\"game\":\"daqdio\"}";
		std::cout << authorization_header.length() << authorization_header;
		curl_easy_setopt(curl, CURLOPT_URL, new_score_url.c_str());
		curl_easy_setopt(curl, CURLOPT_HTTPHEADER, slist1);
		curl_easy_setopt(curl, CURLOPT_POSTFIELDS, request.c_str());
		curl_easy_setopt(curl, CURLOPT_CUSTOMREQUEST, "PUT");
		curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
		curl_easy_setopt(curl, CURLOPT_WRITEDATA, &new_score_response);
		CURLcode res = curl_easy_perform(curl);

		if (res == CURLE_OK) {
			std::cout << "New score response: " << new_score_response << std::endl;
		}
		else {
			std::cerr << "Failed to update or insert player's score: " << curl_easy_strerror(res) << std::endl;
		}

		// Clean up libcurl resources
		curl_easy_cleanup(curl);
	}
}
