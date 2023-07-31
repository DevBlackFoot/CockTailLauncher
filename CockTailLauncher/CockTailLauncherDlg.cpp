
// CockTailLauncherDlg.cpp: 구현 파일
//

#include "pch.h"
#include "framework.h"
#include "CockTailLauncher.h"
#include "CockTailLauncherDlg.h"
#include "afxdialogex.h"

#include <fstream>
#include <dwmapi.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// 응용 프로그램 정보에 사용되는 CAboutDlg 대화 상자입니다.

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

	// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

// 구현입니다.
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CCockTailLauncherDlg 대화 상자



CCockTailLauncherDlg::CCockTailLauncherDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_COCKTAILLAUNCHER_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CCockTailLauncherDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDOK, startButton);
	DDX_Control(pDX, IDC_EXIT, exitButton);
}

BEGIN_MESSAGE_MAP(CCockTailLauncherDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDOK, &CCockTailLauncherDlg::OnBnClickedOk)
	ON_WM_DRAWITEM()
	ON_BN_CLICKED(IDC_EXIT, &CCockTailLauncherDlg::OnBnClickedExit)
	ON_WM_SETCURSOR()
END_MESSAGE_MAP()


// CCockTailLauncherDlg 메시지 처리기

BOOL CCockTailLauncherDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 시스템 메뉴에 "정보..." 메뉴 항목을 추가합니다.

	// IDM_ABOUTBOX는 시스템 명령 범위에 있어야 합니다.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);
	
	cursor = LoadCursor(AfxGetInstanceHandle(), MAKEINTRESOURCE(IDC_CURSOR1));

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != nullptr)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// 이 대화 상자의 아이콘을 설정합니다.  응용 프로그램의 주 창이 대화 상자가 아닐 경우에는
	//  프레임워크가 이 작업을 자동으로 수행합니다.
	SetIcon(m_hIcon, TRUE);			// 큰 아이콘을 설정합니다.
	SetIcon(m_hIcon, FALSE);		// 작은 아이콘을 설정합니다.

	// TODO: 여기에 추가 초기화 작업을 추가합니다.
	//SetWindowPos(nullptr, 200, 200, 816, 489, SWP_NOMOVE);
	SetWindowPos(nullptr, 200, 200, 800, 450, SWP_NOMOVE);
	BGBitmap.LoadBitmapW(IDB_BACKGROUND);

	runBitmap.LoadBitmapW(IDB_START);
	runHoverBitmap.LoadBitmapW(IDB_START_HOVER);

	exitBitmap.LoadBitmapW(IDB_EXIT);
	exitHoverBitmap.LoadBitmapW(IDB_EXIT_HOVER);

	startButton.SetWindowPos(nullptr, 660, 343, 125, 34, 0);
	startButton.SetBitmap(runBitmap);

	exitButton.SetWindowPos(nullptr, 701, 402, 85, 33, 0);
	exitButton.SetBitmap(exitBitmap);

	return TRUE;  // 포커스를 컨트롤에 설정하지 않으면 TRUE를 반환합니다.
}

void CCockTailLauncherDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// 대화 상자에 최소화 단추를 추가할 경우 아이콘을 그리려면
//  아래 코드가 필요합니다.  문서/뷰 모델을 사용하는 MFC 애플리케이션의 경우에는
//  프레임워크에서 이 작업을 자동으로 수행합니다.

void CCockTailLauncherDlg::OnPaint()
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
		CPaintDC dc(this);

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		CRect rect;
		GetClientRect(&rect);

		int cx = rect.Width();
		int cy = rect.Height();

		//배경화면 
		CBitmap* old_resBack;
		CDC memDC;
		memDC.CreateCompatibleDC(&dc);

		old_resBack = memDC.SelectObject(&BGBitmap);

		dc.BitBlt(0, 0, cx, cy, &memDC, 0, 0, SRCCOPY);
		memDC.SelectObject(old_resBack);
		memDC.DeleteDC();

	}
}

// 사용자가 최소화된 창을 끄는 동안에 커서가 표시되도록 시스템에서
//  이 함수를 호출합니다.
HCURSOR CCockTailLauncherDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CCockTailLauncherDlg::OnBnClickedOk()
{
	std::ofstream batch;
	batch.open("Play.bat", std::ios::out);
	batch << "@echo OFF\n";
	batch << "set PATH=%~dp0Game\\DLL;%PATH%\n";
	batch << "echo %PATH%\n";
	batch << "pushd %~dp0Game\n";
	batch << "start CockTailClient.exe\n";
	batch << "exit\n";
	batch.close();

	system("Play.bat");
	system("del Play.bat");

	// 만든 뒤 종료
	::PostQuitMessage(0);
}



void CCockTailLauncherDlg::OnDrawItem(int nIDCtl, LPDRAWITEMSTRUCT lpDrawItemStruct)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.

	if (nIDCtl == IDOK)
	{
		CDC* pDC = CDC::FromHandle(lpDrawItemStruct->hDC);

		CRect rect;
		rect.CopyRect(&lpDrawItemStruct->rcItem);
		CRect screenRect;
		startButton.GetWindowRect(&screenRect);
		ScreenToClient(&screenRect);

		UINT state = lpDrawItemStruct->itemState;
		if (state & ODS_SELECTED)
			TransparentDraw(pDC, &runBitmap, &rect, &screenRect);
		else
		{
			if (startButton.GetHover() == true)
				TransparentDraw(pDC, &runHoverBitmap, &rect, &screenRect);
			else
				TransparentDraw(pDC, &runBitmap, &rect, &screenRect);
		}

		pDC->Detach();
	}
	/*
	*/

	// ExitButton을 고쳐줍니다.
	if (nIDCtl == IDC_EXIT)
	{
		CDC* pDC = CDC::FromHandle(lpDrawItemStruct->hDC);

		CRect rect;
		rect.CopyRect(&lpDrawItemStruct->rcItem);
		CRect screenRect;
		exitButton.GetWindowRect(&screenRect);
		ScreenToClient(&screenRect);

		UINT state = lpDrawItemStruct->itemState;

		// 클릭했을 때
		if (state & ODS_SELECTED)
			TransparentDraw(pDC, &exitBitmap, &rect, &screenRect);
		else
		{
			// 호버일 때
			if (exitButton.GetHover() == true)
				TransparentDraw(pDC, &exitHoverBitmap, &rect, &screenRect);
			else
				TransparentDraw(pDC, &exitBitmap, &rect, &screenRect);
		}

		pDC->Detach();
	}

	CDialogEx::OnDrawItem(nIDCtl, lpDrawItemStruct);
}


void CCockTailLauncherDlg::OnBnClickedExit()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.

	// 누르면 그냥 종료해버립니다.
	::PostQuitMessage(0);
}

void CCockTailLauncherDlg::TransparentDraw(CDC* pDC, CBitmap* buttonBitmap, CRect* ButtonRect, CRect* ScreenRect)
{
	// pc와 Rect 등을 받습니다.
	// 기존 배경을 우선 깔아봅시다.
	CBitmap* old_resBack;
	// 투명 처리할 할 비트맵..
	CBitmap* old_transres;
	// 작업을 해줄 DC를 하나 더 만들어줍니다.
	CDC memDC;
	memDC.CreateCompatibleDC(pDC);
	// 투명 처리할 DC를 하나 더 만들어줍니다.
	CDC transMemDC;
	transMemDC.CreateCompatibleDC(pDC);

	old_resBack = memDC.SelectObject(&BGBitmap);
	old_transres = transMemDC.SelectObject(buttonBitmap);

	// 현재 버튼 영역만큼 가져와줍니다.
	pDC->BitBlt(0, 0, ButtonRect->Width(), ButtonRect->Height(), &memDC, ScreenRect->left, ScreenRect->top, SRCCOPY);
	// 현재 버튼 영역만큼 TransBlt를 사용해줍니다.
	pDC->TransparentBlt(0, 0, ButtonRect->Width(), ButtonRect->Height(), &transMemDC, 0, 0, ButtonRect->Width(), ButtonRect->Height(), RGB(255, 0, 251));
	//pDC->BitBlt(0, 0, rect.Width(), rect.Height(), &transMemDC, 0, 0, SRCCOPY);

	memDC.SelectObject(old_resBack);
	memDC.DeleteDC();
	// 트랜스를 가져오고 지워줍니다.
	transMemDC.SelectObject(old_transres);
	transMemDC.DeleteDC();
}

BOOL CCockTailLauncherDlg::OnSetCursor(CWnd* pWnd, UINT nHitTest, UINT message)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	::SetCursor(cursor);

	return true;
}
