// MyMfcButton.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "MyMfcButton.h"


// CMyMfcButton

IMPLEMENT_DYNAMIC(CMyMfcButton, CMFCButton)

CMyMfcButton::CMyMfcButton()
{
	m_bCursorOnButton = FALSE;
	
	this->selected = FALSE;
}

CMyMfcButton::~CMyMfcButton()
{
}


BEGIN_MESSAGE_MAP(CMyMfcButton, CMFCButton)
	ON_WM_MOUSEHOVER()
	ON_WM_MOUSELEAVE()
	ON_WM_MOUSEMOVE()
END_MESSAGE_MAP()



// CMyMfcButton 메시지 처리기입니다.

void CMyMfcButton::OnMouseHover(UINT nFlags, CPoint point)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	if (!this->selected){
		SetTextColor(this->textAltColor);
		SetFaceColor(this->bkAltColor, TRUE);
		Invalidate();
	}
	CMFCButton::OnMouseHover(nFlags, point);
}


void CMyMfcButton::OnMouseLeave()
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	if (!this->selected){
		m_bCursorOnButton = FALSE;
		SetTextColor(this->textStdColor);
		SetFaceColor(this->bkStdColor, TRUE);
		Invalidate();
	}
	CMFCButton::OnMouseLeave();
}


void CMyMfcButton::OnMouseMove(UINT nFlags, CPoint point)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	if (m_bCursorOnButton == FALSE)
	{
		TRACKMOUSEEVENT tme;
		ZeroMemory(&tme, sizeof(TRACKMOUSEEVENT));
		tme.cbSize = sizeof(tme);
		tme.hwndTrack = m_hWnd;
		tme.dwFlags = TME_LEAVE | TME_HOVER;
		tme.dwHoverTime = 1;
		m_bCursorOnButton = _TrackMouseEvent(&tme);
	}
	CMFCButton::OnMouseMove(nFlags, point);
}

COLORREF CMyMfcButton::GetBkStdColor()
{
	return this->bkStdColor;
}

void CMyMfcButton::SetBkStdColor(COLORREF bkStdColor){
	this->bkStdColor = bkStdColor;
}

COLORREF CMyMfcButton::GetBkAltColor()
{
	return this->bkAltColor;
}

void CMyMfcButton::SetBkAltColor(COLORREF bkAltColor){
	this->bkAltColor = bkAltColor;
}
COLORREF CMyMfcButton::GetTextStdColor()
{
	return this->textStdColor;
}
void CMyMfcButton::SetTextStdColor(COLORREF textStdColor){
	this->textStdColor = textStdColor;
}
COLORREF CMyMfcButton::GetTextAltColor()
{
	return this->textAltColor;
}
void CMyMfcButton::SetTextAltColor(COLORREF textAltColor){
	this->textAltColor = textAltColor;
}
BOOL CMyMfcButton::GetSelected()
{
	return this->selected;
}
void CMyMfcButton::Update(){
	SetFaceColor(this->bkStdColor, TRUE);
	SetTextColor(this->textStdColor);
}

void CMyMfcButton::SetSelected(BOOL selected){
	this->selected = selected;
	if (selected){
		SetTextColor(this->textAltColor);
		SetFaceColor(this->bkAltColor, TRUE);
	}
	else{
		SetFaceColor(this->bkStdColor, TRUE);
		SetTextColor(this->textStdColor);
	}
	
}