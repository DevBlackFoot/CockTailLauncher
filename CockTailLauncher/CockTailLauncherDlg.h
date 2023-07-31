
// CockTailLauncherDlg.h: 헤더 파일
//

#pragma once
#include "CHoverButton.h"

// CCockTailLauncherDlg 대화 상자
class CCockTailLauncherDlg : public CDialogEx
{
// 생성입니다.
public:
	CCockTailLauncherDlg(CWnd* pParent = nullptr);	// 표준 생성자입니다.

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_COCKTAILLAUNCHER_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 지원입니다.


// 구현입니다.
protected:
	HICON m_hIcon;
	HCURSOR cursor;

	CBitmap BGBitmap;

	CBitmap runBitmap;
	CBitmap exitBitmap;

	CBitmap runHoverBitmap;
	CBitmap exitHoverBitmap;

	CHoverButton startButton;
	CHoverButton exitButton;

	// 생성된 메시지 맵 함수
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();
	afx_msg void OnDrawItem(int nIDCtl, LPDRAWITEMSTRUCT lpDrawItemStruct);
	afx_msg void OnBnClickedExit();

private:
	// 버튼의 비트맵, 현재 그려줄 DC 등이 필요할듯.
	void TransparentDraw(CDC* pDC, CBitmap* buttonBitmap, CRect* ButtonRect, CRect* ScreenRect);
public:
	afx_msg BOOL OnSetCursor(CWnd* pWnd, UINT nHitTest, UINT message);
};
