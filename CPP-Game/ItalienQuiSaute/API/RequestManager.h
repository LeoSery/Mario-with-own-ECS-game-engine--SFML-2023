#pragma once
#include <curl/curl.h>
#include <iostream>
#include <string>
#include <json/json.h>

class RequestManager
{

public:
	RequestManager(){}
	void NewScore(int score);
	std::string Scorelist();
	void Login(std::string username, std::string email, std::string password);
	void SignIn(std::string username, std::string email, std::string password);


private:
	static size_t WriteCallback(void* contents, size_t size, size_t nmemb, void* userp);
	static size_t HeaderCallback(char* buffer, size_t size, size_t nitems, void* userdata);
	const std::string LOGIN_ENDPOINT = "/login";
	const std::string SIGNIN_ENDPOINT = "/signin";
	const std::string BASE_URL = "http://localhost:3000";
	const std::string SCORE_LIST_ENDPOINT = "/scoreboard/Mario";
	const std::string NEW_SCORE_ENDPOINT = "/newscore";
	struct curl_slist* slist1;
	std::string auth_token;
};
