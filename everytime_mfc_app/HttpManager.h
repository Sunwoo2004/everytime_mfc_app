#pragma once
class HttpManager
{
public:
	
private:
	static HttpManager* sg_Instance;
public:
	static HttpManager& GetInstance();
public:
	void Init();
	HttpManager();
	~HttpManager();
};

int writer(char* data, size_t size, size_t nmemb, std::string* buffer);
std::string curl_httpget(const std::string& url);

#define g_HttpMgr HttpManager::GetInstance()