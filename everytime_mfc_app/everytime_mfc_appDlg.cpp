#define WM_CHANGE_BACKGROUND_COLOR (WM_USER + 1001)
#include "pch.h"
#include "everytime_mfc_app.h"
#include "everytime_mfc_appDlg.h"
#include "afxdialogex.h"
#include "ScheduleManager.h"
#include <vector>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

int m_iIndex = 0; // 변경할 컨트롤의 인덱스
int r = 242; // 빨강 값
int g = 232; // 초록 값
int b = 232; // 파랑 값

CeverytimemfcappDlg::CeverytimemfcappDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_EVERYTIME_MFC_APP_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CeverytimemfcappDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_PICTURE_STATIC, m_PictureControl);

	DDX_Control(pDX, IDC_TIMETABLE_BASE, m_timetable_base);
}

BEGIN_MESSAGE_MAP(CeverytimemfcappDlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_LOAD_TIMETABLE, &CeverytimemfcappDlg::OnBnClickedLoadTimetable)
	ON_BN_CLICKED(IDC_CLOSE_PROGRAM, &CeverytimemfcappDlg::OnBnClickedCloseProgram)
	ON_MESSAGE(WM_CHANGE_BACKGROUND_COLOR, OnChangeBackGroundColor)
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

	OnLoadTimeTable(false);


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
	OnLoadTimeTable(true);
}


void CeverytimemfcappDlg::OnBnClickedCloseProgram()
{
	::SendMessage(this->m_hWnd, WM_CLOSE, NULL, NULL);
}

void CeverytimemfcappDlg::OnCopyEditBox(int iIndex, int iLeft, int iTop, char* szText, BOOL bMulti)
{
	DWORD style = m_timetable_base.GetStyle();
	style |= ES_MULTILINE;
	style |= WS_VISIBLE;
	DWORD exStyle = m_timetable_base.GetExStyle();
	CFont* pFont = m_timetable_base.GetFont();
	CRect rect;
	m_timetable_base.GetWindowRect(&rect);
	ScreenToClient(&rect);

	rect.left = iLeft; // Edit Control의 왼쪽 X 좌표
	rect.top = iTop; // Edit Control의 상단 Y 좌표
	rect.right = rect.left + 124; // Edit Control의 오른쪽 X 좌표
	rect.bottom = rect.top + 59; // Edit Control의 하단 Y 좌표
	if (bMulti)
	{
		rect.bottom += 60;
	}

	m_timetables[iIndex].CreateEx(exStyle, "EDIT", szText, style, rect, this, IDC_TIMETABLE_BASE);
	m_timetables[iIndex].SetFont(pFont);

	r = 242, g = 232, b = 232;
	m_iIndex = iIndex;
	m_timetables[iIndex].SendMessage(WM_CHANGE_BACKGROUND_COLOR, MAKEWPARAM(r, g), MAKELPARAM(b, 0));
	//m_timetables[iIndex].SendMessage(WM_CHANGE_BACKGROUND_COLOR, RGB(242, 232, 232));
}

/*void*/LRESULT CeverytimemfcappDlg::OnChangeBackGroundColor(/*int iIndex, int r, int g, int b*/WPARAM wParam, LPARAM lParam)
{
	/*CBrush bkBrush;
	RECT ctrlRect;
	COLORREF crBk = RGB(r, g, b);
	bkBrush.CreateSolidBrush(crBk);

	m_timetables[iIndex].GetClientRect(&ctrlRect);

	CDC* cdc = m_timetables[iIndex].GetWindowDC();
	cdc->FillRect(&ctrlRect, &bkBrush);
	cdc->SetBkColor(crBk);*/
	int r = LOWORD(wParam); // 빨강 값
	int g = HIWORD(wParam); // 초록 값
	int b = LOWORD(lParam); // 파랑 값

	// 배경색 변경 로직 작성
	/*CBrush bkBrush;
	RECT ctrlRect;
	COLORREF crBk = RGB(r, g, b);
	bkBrush.CreateSolidBrush(crBk);

	m_timetables[m_iIndex].GetClientRect(&ctrlRect);

	CDC* cdc = m_timetables[m_iIndex].GetWindowDC();
	cdc->FillRect(&ctrlRect, &bkBrush);
	cdc->SetBkColor(crBk);

	m_timetables[m_iIndex].ReleaseDC(cdc);*/

	CBrush bkBrush;
	RECT ctrlRect;
	COLORREF crBk = RGB(r, g, b);
	bkBrush.CreateSolidBrush(crBk);

	m_timetables[m_iIndex].GetClientRect(&ctrlRect);

	CDC* cdc = m_timetables[m_iIndex].GetWindowDC();
	cdc->FillRect(&ctrlRect, &bkBrush);
	cdc->SetBkColor(crBk);

	return 0;
}

void CeverytimemfcappDlg::OnLoadTimeTable(bool bNew = false)
{
	if (bNew)
	{
		g_ScheduleMgr.GetData();
	}
	else
	{
		bool bResult = g_ScheduleMgr.GetDataByINI();
		if (!bResult)
		{
			int iResult = ::MessageBoxA(NULL, "처음 실행하였습니다. 새로 로드 하시겠습니까?", "[Notice] everytime_mfc_app", MB_YESNO);
			if (iResult == IDYES)
			{
				g_ScheduleMgr.GetData();
			}
			else if (iResult == IDNO)
			{
				return;
			}
		}
	}

	vLecturesList kList;

	kList.clear();

	int iIndex = 0;
	for (int i = 0; i < 5; i++)
	{
		for (int j = 0; j < 8; j++)
		{
			int iPosX = i * 126;
			int iPosY = j * 60;

			if (i == 0)
			{
				g_ScheduleMgr.GetLecturesByDay(kList, eWeekly::WK_MONDAY);
				//월
			}
			else if (i == 1)
			{
				g_ScheduleMgr.GetLecturesByDay(kList, eWeekly::WK_TUESDAY);
				//화
			}
			else if (i == 2)
			{
				g_ScheduleMgr.GetLecturesByDay(kList, eWeekly::WK_WEDNESDAY);
				//수
			}
			else if (i == 3)
			{
				g_ScheduleMgr.GetLecturesByDay(kList, eWeekly::WK_THURSDAY);
				//목
			}
			else
			{
				g_ScheduleMgr.GetLecturesByDay(kList, eWeekly::WK_FRIDAY);
				//금
			}

			sLectures kLectures;
			if (g_ScheduleMgr.GetLecturesByTime(kList, j + 9, kLectures))
			{
				char szBuf[256];
				sprintf(szBuf, "%s\r\n%s\r\n%s", kLectures.szLecturesName, kLectures.szProfessor, kLectures.szLectureRoom);
				if (kLectures.iLecturesTime > 1)
				{
					OnCopyEditBox(iIndex, 127 + iPosX, 51 + iPosY, szBuf, TRUE); //127 인덱스1 아래로 쭉 내려간다.
				}
				else
				{
					OnCopyEditBox(iIndex, 127 + iPosX, 51 + iPosY, szBuf); //127 인덱스1 아래로 쭉 내려간다.
				}
			}

			kList.clear();

			iIndex++;
		}
	}
}