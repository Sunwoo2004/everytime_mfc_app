#pragma once
class ScheduleManager
{
private:
	char szUrl[1024];
public:
	bool LoadINI();
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