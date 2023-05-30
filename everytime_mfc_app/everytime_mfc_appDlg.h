
// everytime_mfc_appDlg.h: 헤더 파일
//

#pragma once





// CeverytimemfcappDlg 대화 상자
class CeverytimemfcappDlg : public CDialogEx
{
// 생성입니다.
public:
	CeverytimemfcappDlg(CWnd* pParent = nullptr);	// 표준 생성자입니다.

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_EVERYTIME_MFC_APP_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 지원입니다.


// 구현입니다.
protected:
	HICON m_hIcon;

	// 생성된 메시지 맵 함수
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedLoadTimetable();
	afx_msg void OnBnClickedCloseProgram();
	CStatic m_PictureControl;
	CEdit m_timetable_base;
	CEdit m_timetables[40];
	void OnLoadTimeTable(bool bNew);
	void OnCopyEditBox(int iIndex, int iLeft, int iTop, char * szText, BOOL bMulti = FALSE);
	/*void*/LRESULT OnChangeBackGroundColor(/*int iIndex, int r, int g, int b*/WPARAM wParam, LPARAM lParam);
};
