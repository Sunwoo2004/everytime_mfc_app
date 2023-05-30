#pragma once
#include <vector>
#include <string>
enum eWeekly
{
	WK_MONDAY = 1, //월
	WK_TUESDAY, //화
	WK_WEDNESDAY, //수
	WK_THURSDAY, //목
	WK_FRIDAY, //금
	WK_MAXDAY, //day 의 최댓값
};

struct sLectures
{
	int iLectureIDX;
	char szLecturesName[256];
	char szProfessor[256];
	char szLectureRoom[256];
	int iLecturesTime;
	int iStartTime;

	sLectures()
	{
		iLectureIDX = -1;
		strcpy(szLecturesName, "");
		strcpy(szProfessor, "");
		strcpy(szLectureRoom, "");
		iLecturesTime = 0;
		iStartTime = 0;
	}
};

typedef std::vector<sLectures> vLecturesList;


class ScheduleManager
{
private:
	char m_szUrl[1024];
public:
	vLecturesList m_vLecturesList;
public:
	bool LoadINI();
	bool GetData();
	bool GetDataByINI();
	void GetLecturesByDay(vLecturesList &rkLecturesList, eWeekly week);
	bool GetLecturesByTime(vLecturesList& rkLecturesList, int iTime , sLectures & kLectures);
	void SaveINI(std::string szHTML);
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