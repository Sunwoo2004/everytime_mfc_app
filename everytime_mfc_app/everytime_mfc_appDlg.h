﻿
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
	CListBox m_list1;
	CListBox m_list2;
	CListBox m_list3;
	CListBox m_list4;
	CListBox m_list5;
};
