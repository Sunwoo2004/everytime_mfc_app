#pragma once
class ScheduleManager
{
private:
	char m_szUrl[1024];
public:
	bool LoadINI();
	bool GetData();
public:
	static ScheduleManager& GetInstance();
private:
	static ScheduleManager* sg_Instance;
public:
	void Init();
	ScheduleManager();
	~ScheduleManager();
};

#define g_ScheduleMgr ScheduleManager::GetInstance()