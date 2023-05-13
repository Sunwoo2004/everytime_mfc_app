#include "stdafx.h"
#include "ScheduleManager.h"
#include "HttpManager.h"
#include "INILoader.h"

ScheduleManager* ScheduleManager::sg_Instance = NULL;

ScheduleManager& ScheduleManager::GetInstance()
{
	if (sg_Instance == NULL)
	{
		sg_Instance = new ScheduleManager;
	}
	return *sg_Instance;
}

ScheduleManager::ScheduleManager()
{
	Init();
}

ScheduleManager::~ScheduleManager()
{

}

void ScheduleManager::Init()
{
	strcpy(m_szUrl, "");
}

bool ScheduleManager::LoadINI()
{
	char szBuf[1024];
	INILoader kLoader("C:\\Users\\Admin\\Desktop\\everytime.ini");
	kLoader.SetTitle("common");
	kLoader.LoadString("url", "", szBuf, sizeof(szBuf));

	if (strlen(szBuf) < 3) //정상적인 url 길이보다 작다
	{
		return false;
	}

	strcpy(m_szUrl, szBuf);

	return true;
}

bool ScheduleManager::GetData()
{
	if (strlen(m_szUrl) < 3)
	{
		return false;
	}

	const char* szData = g_HttpMgr.GetHTML(m_szUrl);
	return true;
}