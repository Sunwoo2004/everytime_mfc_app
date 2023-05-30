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
	m_vLecturesList.clear();
}

bool ScheduleManager::LoadINI()
{
	char szBuf[2048];
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

void ScheduleManager::SaveDataINI(char* szHTML)
{
	/*INILoader kLoader("C:/Users/Admin/Desktop/everytime_mfc_app.ini");
	kLoader.SetTitle("common");
	kLoader.SaveString("htmldata", szHTML);*/

	std::ofstream outfile;
	outfile.open("C:/Users/Admin/Desktop/everytime_mfc_app.ini");
	outfile << "[common]" << std::endl;
	outfile << "htmldata = " << szHTML << "|" << std::endl;
	outfile.close();
}

bool ScheduleManager::GetDataByINI()
{
	m_vLecturesList.clear();
	char szBuf[2048];
	INILoader kLoader(/*"config/everytime_mfc_app.ini"*/"C:/Users/Admin/Desktop/everytime_mfc_app.ini");
	kLoader.SetTitle("common");
	kLoader.LoadString("htmldata", "", szBuf, sizeof(szBuf));

	if (strlen(szBuf) < 5)
	{
		return false;
	}

	std::string szHTML = szBuf;
	//::MessageBoxA(NULL, szHTML.c_str(), "123", NULL);

	std::vector<std::string> tokens1;

	std::istringstream iss1(szHTML);
	std::string token1, token2;

	while (std::getline(iss1, token1, '|'))
	{
		tokens1.push_back(token1);
	}

	for (int i = 0; i < tokens1.size() - 1; i++) //for 문 돌릴때 마지막 | 뒤는 NULL 값이므로 빼자
	{
		const std::string& rkToken = tokens1[i];
		std::istringstream iss2(rkToken);

		sLectures kLectures;
		int k = 0;
		while (std::getline(iss2, token2, '&'))
		{
			switch (k)
			{
			case 0:
				kLectures.iLectureIDX = atoi(token2.c_str());
				break;
			case 1:
				strcpy(kLectures.szLecturesName, token2.c_str());
				break;
			case 2:
				strcpy(kLectures.szProfessor, token2.c_str());
				break;
			case 3:
				strcpy(kLectures.szLectureRoom, token2.c_str());
				break;
			case 4:
				kLectures.iLecturesTime = atoi(token2.c_str());
				break;
			case 5:
				kLectures.iStartTime = atoi(token2.c_str());
				break;
			default:
				break;
			}
			k++;
		}
		m_vLecturesList.push_back(kLectures);
		//::MessageBoxA(NULL, kLectures.szLecturesName, "ad", NULL);
	}

	return true;
}

bool ScheduleManager::GetData()
{
	m_vLecturesList.clear();
	if (strlen(m_szUrl) < 3)
	{
		return false;
	}

	std::string szHTML = g_HttpMgr.GetHTML(m_szUrl);
	//::MessageBoxA(NULL, szHTML.c_str(), "1234", NULL);
	SaveDataINI((char*)szHTML.c_str());

	std::vector<std::string> tokens1;

	std::istringstream iss1(szHTML);
	std::string token1, token2;

	while (std::getline(iss1, token1, '|'))
	{
		tokens1.push_back(token1);
	}

	for (int i = 0 ; i < tokens1.size() - 1; i++) //for 문 돌릴때 마지막 | 뒤는 NULL 값이므로 빼자
	{
		const std::string &rkToken = tokens1[i];
		std::istringstream iss2(rkToken);

		sLectures kLectures;
		int k = 0;
		while (std::getline(iss2, token2, '&'))
		{
			switch (k)
			{
			case 0:
				kLectures.iLectureIDX = atoi(token2.c_str());
				break;
			case 1:
				strcpy(kLectures.szLecturesName, token2.c_str());
				break;
			case 2:
				strcpy(kLectures.szProfessor, token2.c_str());
				break;
			case 3:
				strcpy(kLectures.szLectureRoom, token2.c_str());
				break;
			case 4:
				kLectures.iLecturesTime = atoi(token2.c_str());
				break;
			case 5:
				kLectures.iStartTime = atoi(token2.c_str());
				break;
			default:
				break;
			}
			k++;
		}
		m_vLecturesList.push_back(kLectures);
		//::MessageBoxA(NULL, kLectures.szLecturesName, "ad", NULL);
	}

	return true;
}

void ScheduleManager::GetLecturesByDay(vLecturesList& rkLecturesList, eWeekly week)
{
	for (int i = 0; i < m_vLecturesList.size(); i++)
	{
		const sLectures& rkLectures = m_vLecturesList[i];
		if (rkLectures.iLectureIDX != week)
		{
			continue;
		}
		rkLecturesList.push_back(rkLectures);
	}
}

bool ScheduleManager::GetLecturesByTime(vLecturesList& rkLecturesList, int iTime , sLectures& kLectures)
{
	int iCnt = rkLecturesList.size();
	for (int i = 0; i < iCnt; i++)
	{
		const sLectures& rkLectures = rkLecturesList[i];
		if (rkLectures.iStartTime == iTime)
		{
			kLectures = rkLectures;
			return true;
		}
	}
	return false;
}