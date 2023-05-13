#include "stdafx.h"
#include "HttpManager.h"
#include "curl/curl.h"

using namespace std;

int writer(char* data, size_t size, size_t nmemb, string* buffer)
{
	int result = 0;
	if (buffer != NULL)
	{
		buffer->append(data, size * nmemb);
		result = size * nmemb;
	}
	return result;
}

string curl_httpget(const string& url)
{
	string buffer;

	CURL* curl;
	CURLcode result;

	curl = curl_easy_init();

	if (curl)
	{
		curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
		curl_easy_setopt(curl, CURLOPT_HEADER, 0);
		curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, writer);
		curl_easy_setopt(curl, CURLOPT_WRITEDATA, &buffer);

		result = curl_easy_perform(curl);

		curl_easy_cleanup(curl);

		if (result == CURLE_OK)
		{
			return buffer;
		}
		return "";
	}
	return "";
}

HttpManager* HttpManager::sg_Instance = NULL;

HttpManager& HttpManager::GetInstance()
{
	if (sg_Instance == NULL)
	{
		sg_Instance = new HttpManager;
	}
	return *sg_Instance;
}

HttpManager::HttpManager()
{
	Init();
}

HttpManager::~HttpManager()
{

}

void HttpManager::Init()
{
}

const char* HttpManager::GetHTML(const char* szUrl)
{
	string iSource = curl_httpget(szUrl);
	return iSource.c_str();
}