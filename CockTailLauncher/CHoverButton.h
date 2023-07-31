#pragma once


// CHoverButton

class CHoverButton : public CButton
{
	DECLARE_DYNAMIC(CHoverButton)

public:
	CHoverButton();
	virtual ~CHoverButton();

protected:
	DECLARE_MESSAGE_MAP()

	// 호버인지 아닌지를 체크하는 bool 변수를 하나 둡니다.
	bool isHover = false;

public:
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnMouseLeave();

	bool GetHover() { return isHover; }
};


