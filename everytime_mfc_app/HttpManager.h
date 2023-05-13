#pragma once
class HttpManager
{
public:
	const char* GetHTML(const char * szUrl);
private:
	static HttpManager* sg_Instance;
public:
	static HttpManager& GetInstance();
public:
	void Init();
	HttpManager();
	~HttpManager();
};

#define g_HttpMgr HttpManager::GetInstance()