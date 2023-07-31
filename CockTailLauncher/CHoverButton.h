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

	// ȣ������ �ƴ����� üũ�ϴ� bool ������ �ϳ� �Ӵϴ�.
	bool isHover = false;

public:
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnMouseLeave();

	bool GetHover() { return isHover; }
};


