#pragma once


// CMyMfcButton

class CMyMfcButton : public CMFCButton
{
	DECLARE_DYNAMIC(CMyMfcButton)

public:
	CMyMfcButton();
	virtual ~CMyMfcButton();
	BOOL m_bCursorOnButton;
protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnMouseHover(UINT nFlags, CPoint point);
	afx_msg void OnMouseLeave();
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	COLORREF GetBkStdColor();
	void SetBkStdColor(COLORREF bkStdColor);
	COLORREF GetBkAltColor();
	void SetBkAltColor(COLORREF bkAltColor);
	COLORREF GetTextStdColor();
	void SetTextStdColor(COLORREF textStdColor);
	COLORREF GetTextAltColor();
	void SetTextAltColor(COLORREF textAltColor);
	BOOL GetSelected();
	void SetSelected(BOOL selected);
	void Update();
private:
	COLORREF bkStdColor;
	COLORREF bkAltColor;
	COLORREF textStdColor;
	COLORREF textAltColor;
	BOOL selected;
};


