// CHoverButton.cpp: 구현 파일
//

#include "pch.h"
#include "CockTailLauncher.h"
#include "CHoverButton.h"


// CHoverButton

IMPLEMENT_DYNAMIC(CHoverButton, CButton)

CHoverButton::CHoverButton()
{
}

CHoverButton::~CHoverButton()
{
}


BEGIN_MESSAGE_MAP(CHoverButton, CButton)
	ON_WM_MOUSEMOVE()
	ON_WM_MOUSELEAVE()
END_MESSAGE_MAP()



// CHoverButton 메시지 처리기




void CHoverButton::OnMouseMove(UINT nFlags, CPoint point)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	if(isHover != true)
	{
		TRACKMOUSEEVENT tme;
		tme.cbSize = sizeof(tme);
		tme.hwndTrack = m_hWnd;
		tme.dwFlags = TME_LEAVE | TME_HOVER;
		tme.dwHoverTime = 1;
		if(TrackMouseEvent(&tme))
		{
			// 호버의 경우 여기서 세팅 되기 때문에 사실상 필요 없습니다.
			isHover = true;
			// 메시지를 호출합니다.
			Invalidate(FALSE);
		}
	}

	CButton::OnMouseMove(nFlags, point);
}

void CHoverButton::OnMouseLeave()
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	isHover = false;
	// 메시지를 호출합니다.
	Invalidate(FALSE);

	CButton::OnMouseLeave();
}
