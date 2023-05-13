#include "stdafx.h"
#include "HttpManager.h"
#include <winhttp.h>
#pragma comment(lib, "winhttp.lib")
#include <vector>
#include <codecvt>
#include <locale>

using namespace std;

wstring HttpManager::get_utf16(const string& str, int codepage)
{
	if (str.empty()) return wstring();
	int sz = MultiByteToWideChar(codepage, 0, &str[0], (int)str.size(), 0, 0);
	wstring res(sz, 0);
	MultiByteToWideChar(codepage, 0, &str[0], (int)str.size(), &res[0], sz);
	return res;
}

string HttpManager::WebHttp(string webaddress, string args, int port)
{
	DWORD dwSize = 0, dwDownloaded;
	LPSTR source;
	source = (char*)"";
	string responsed = "";

	HINTERNET hSession = NULL, hConnect = NULL, hRequest = NULL;
	BOOL bResults = FALSE;

	hSession = WinHttpOpen(L"Winhttp API", WINHTTP_ACCESS_TYPE_DEFAULT_PROXY, WINHTTP_NO_PROXY_NAME, WINHTTP_NO_PROXY_BYPASS, 0);

	if (hSession)
	{
		hConnect = WinHttpConnect(hSession, get_utf16(webaddress, CP_UTF8).c_str(), port, 0);
	}

	if (hConnect)
	{
		hRequest = WinHttpOpenRequest(hConnect, L"GET", get_utf16(args, CP_UTF8).c_str(), NULL, WINHTTP_NO_REFERER, WINHTTP_DEFAULT_ACCEPT_TYPES, 0);
	}

	if (hRequest)
	{
		bResults = WinHttpSendRequest(hRequest, WINHTTP_NO_ADDITIONAL_HEADERS, 0, WINHTTP_NO_REQUEST_DATA, 0, 0, 0);
	}

	if (bResults)
	{
		bResults = WinHttpReceiveResponse(hRequest, NULL);
	}

	if (bResults)
	{
		do
		{
			dwSize = 0;
			if (!WinHttpQueryDataAvailable(hRequest, &dwSize))
			{
				//printf("Error %u", GetLastError());
			}

			source = (char*)malloc(dwSize + 1);
			if (!source) {
				//printf("Out of memory\n");
				dwSize = 0;
			}
			else {
				ZeroMemory(source, dwSize + 1);

				if (!WinHttpReadData(hRequest, (LPVOID)source, dwSize, &dwDownloaded))
				{
					//printf("Error %u", GetLastError());
				}
				else
				{
					responsed = responsed + source;
				}
				free(source);
			}
		} while (dwSize > 0);
	}

	if (!bResults)
	{
		exit(0);
	}

	if (hRequest) WinHttpCloseHandle(hRequest);
	if (hConnect) WinHttpCloseHandle(hConnect);
	if (hSession) WinHttpCloseHandle(hSession);
	return responsed;
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

std::wstring ConvertToWideString(const std::string& input)
{
	std::wstring_convert<std::codecvt_utf8_utf16<wchar_t>> converter;
	return converter.from_bytes(input);
}

std::string ConvertToMultiByteString(const std::wstring& input, UINT codePage)
{
	int multiByteStrLen = WideCharToMultiByte(codePage, 0, input.c_str(), -1, nullptr, 0, nullptr, nullptr);
	if (multiByteStrLen == 0)
	{
		return "";
	}

	std::string multiByteStr(multiByteStrLen, '\0');
	if (WideCharToMultiByte(codePage, 0, input.c_str(), -1, &multiByteStr[0], multiByteStrLen, nullptr, nullptr) == 0)
	{
		return "";
	}

	return multiByteStr;
}

string HttpManager::GetHTML(const char* szUrl)
{
	char szBuf[2048]= "/api.aspx?url=";
	strcat(szBuf, szUrl);
	string iSource = WebHttp("127.0.0.1", szBuf, 800);
	std::wstring wideString = ConvertToWideString(iSource);

	int requiredSize = WideCharToMultiByte(CP_ACP, 0, wideString.c_str(), -1, nullptr, 0, nullptr, nullptr);
	std::string ansiString(requiredSize, '\0');
	WideCharToMultiByte(CP_ACP, 0, wideString.c_str(), -1, &ansiString[0], requiredSize, nullptr, nullptr);

	return ansiString;
}