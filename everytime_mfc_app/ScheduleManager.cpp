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
	strcpy(szUrl, "");
}

bool ScheduleManager::LoadINI()
{
	char szBuf[1024];
	INILoader kLoader("C:\\Users\\Admin\\Desktop\\everytime.ini");
	kLoader.SetTitle("common");
	kLoader.LoadString("url", "", szBuf, sizeof(szBuf));
	::MessageBoxA(NULL, szBuf, "asd", NULL);
}