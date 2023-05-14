﻿
// everytime_mfc_appDlg.cpp: 구현 파일
//
#include "pch.h"
#include "everytime_mfc_app.h"
#include "everytime_mfc_appDlg.h"
#include "afxdialogex.h"
#include "ScheduleManager.h"
#include <vector>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CeverytimemfcappDlg 대화 상자



CeverytimemfcappDlg::CeverytimemfcappDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_EVERYTIME_MFC_APP_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CeverytimemfcappDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_MFCVSLISTBOX1, m_vslist1);
	DDX_Control(pDX, IDC_MFCVSLISTBOX2, m_vslist2);
	DDX_Control(pDX, IDC_MFCVSLISTBOX3, m_vslist3);
	DDX_Control(pDX, IDC_MFCVSLISTBOX4, m_vslist4);
	DDX_Control(pDX, IDC_MFCVSLISTBOX5, m_vslist5);
}

BEGIN_MESSAGE_MAP(CeverytimemfcappDlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_LOAD_TIMETABLE, &CeverytimemfcappDlg::OnBnClickedLoadTimetable)
	ON_BN_CLICKED(IDC_CLOSE_PROGRAM, &CeverytimemfcappDlg::OnBnClickedCloseProgram)
END_MESSAGE_MAP()


// CeverytimemfcappDlg 메시지 처리기
BOOL CeverytimemfcappDlg::OnInitDialog()
{
	//초기


	CDialogEx::OnInitDialog();

	// 이 대화 상자의 아이콘을 설정합니다.  응용 프로그램의 주 창이 대화 상자가 아닐 경우에는
	//  프레임워크가 이 작업을 자동으로 수행합니다.
	SetIcon(m_hIcon, TRUE);			// 큰 아이콘을 설정합니다.
	SetIcon(m_hIcon, FALSE);		// 작은 아이콘을 설정합니다.

	// TODO: 여기에 추가 초기화 작업을 추가합니다.

	return TRUE;  // 포커스를 컨트롤에 설정하지 않으면 TRUE를 반환합니다.
}

// 대화 상자에 최소화 단추를 추가할 경우 아이콘을 그리려면
//  아래 코드가 필요합니다.  문서/뷰 모델을 사용하는 MFC 애플리케이션의 경우에는
//  프레임워크에서 이 작업을 자동으로 수행합니다.

void CeverytimemfcappDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 그리기를 위한 디바이스 컨텍스트입니다.

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 클라이언트 사각형에서 아이콘을 가운데에 맞춥니다.
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 아이콘을 그립니다.
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

// 사용자가 최소화된 창을 끄는 동안에 커서가 표시되도록 시스템에서
//  이 함수를 호출합니다.
HCURSOR CeverytimemfcappDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


void CeverytimemfcappDlg::OnBnClickedLoadTimetable()
{
	g_ScheduleMgr.GetData();

	int itemCount = m_vslist1.GetCount();

	vLecturesList kList;

	kList.clear();
	g_ScheduleMgr.GetLecturesByDay(kList, eWeekly::WK_MONDAY);
	for (int i = 0; i < kList.size(); i++)
	{
		const sLectures& rkLecture = kList[i];
		m_vslist1.AddItem(rkLecture.szLecturesName);
	}
	kList.clear();

	g_ScheduleMgr.GetLecturesByDay(kList, eWeekly::WK_TUESDAY);
	for (int i = 0; i < kList.size(); i++)
	{
		const sLectures& rkLecture = kList[i];
		m_vslist2.AddItem(rkLecture.szLecturesName);
	}
	kList.clear();

	g_ScheduleMgr.GetLecturesByDay(kList, eWeekly::WK_WEDNESDAY);
	for (int i = 0; i < kList.size(); i++)
	{
		const sLectures& rkLecture = kList[i];
		m_vslist3.AddItem(rkLecture.szLecturesName);
	}
	kList.clear();

	g_ScheduleMgr.GetLecturesByDay(kList, eWeekly::WK_THURSDAY);
	for (int i = 0; i < kList.size(); i++)
	{
		const sLectures& rkLecture = kList[i];
		m_vslist4.AddItem(rkLecture.szLecturesName);
	}
	kList.clear();

	g_ScheduleMgr.GetLecturesByDay(kList, eWeekly::WK_FRIDAY);
	for (int i = 0; i < kList.size(); i++)
	{
		const sLectures& rkLecture = kList[i];
		m_vslist5.AddItem(rkLecture.szLecturesName);
	}
	kList.clear();
}


void CeverytimemfcappDlg::OnBnClickedCloseProgram()
{
	::SendMessage(this->m_hWnd, WM_CLOSE, NULL, NULL);
}
