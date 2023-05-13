#pragma once
class HttpManager
{
public:
	std::wstring get_utf16(const std::string& str, int codepage);
	std::string WebHttp(std::string webaddress, std::string args, int port);
	std::string GetHTML(const char * szUrl);
	std::wstring ConvertToWideString(const std::string& input);
	std::string ConvertToMultiByteString(const std::wstring& input, UINT codePage);
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