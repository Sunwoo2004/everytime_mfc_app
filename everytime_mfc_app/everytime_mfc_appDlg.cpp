#include "pch.h"
#include "everytime_mfc_app.h"
#include "everytime_mfc_appDlg.h"
#include "afxdialogex.h"
#include "ScheduleManager.h"
#include <vector>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


CeverytimemfcappDlg::CeverytimemfcappDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_EVERYTIME_MFC_APP_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CeverytimemfcappDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_PICTURE_STATIC, m_PictureControl);

}

BEGIN_MESSAGE_MAP(CeverytimemfcappDlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_LOAD_TIMETABLE, &CeverytimemfcappDlg::OnBnClickedLoadTimetable)
	ON_BN_CLICKED(IDC_CLOSE_PROGRAM, &CeverytimemfcappDlg::OnBnClickedCloseProgram)
END_MESSAGE_MAP()


BOOL CeverytimemfcappDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	//초기
	CString imagePath = _T("resource/timetable.png"); // 이미지 파일 경로
	CImage image;
	image.Load(imagePath);
	m_PictureControl.SetBitmap(image.Detach());


	SetIcon(m_hIcon, TRUE);
	SetIcon(m_hIcon, FALSE);

	return TRUE;
}

void CeverytimemfcappDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this);

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

HCURSOR CeverytimemfcappDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


void CeverytimemfcappDlg::OnBnClickedLoadTimetable()
{
	/*g_ScheduleMgr.GetData();

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
	kList.clear();*/
}


void CeverytimemfcappDlg::OnBnClickedCloseProgram()
{
	::SendMessage(this->m_hWnd, WM_CLOSE, NULL, NULL);
}
