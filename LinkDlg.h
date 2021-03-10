#pragma once

#include <locale.h>
#include "afxwin.h"
#include "MoacallLink.h"
#include "DaligoLink.h"
#include "RoadvoyLink.h"
#include "CombineNetLink.h"
#include "BeyondLink.h"
#include "SanggagLink.h"
#include "DelionDlvyLink.h"

#include "CustomMysql.h"

// CLinkDlg 대화 상자입니다.

class CLinkDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CLinkDlg)

public:
	CLinkDlg(CWnd* pParent = NULL);   // 표준 생성자입니다.
	virtual ~CLinkDlg();

// 대화 상자 데이터입니다.
	enum { IDD = IDD_LINK_DIALOG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.
	virtual BOOL OnInitDialog();
	virtual BOOL PreTranslateMessage(MSG* pMsg);

	DECLARE_MESSAGE_MAP()

public:
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	afx_msg void OnBnClickedButtonConfirm();
	afx_msg void OnBnClickedButtonLink();

	CComboBox m_ComboAgency;

	CEdit m_EditShopCode;

	CMyMfcButton m_BtnConfirm;
	CMyMfcButton m_BtnLink;

	CMyListCtrl m_ListStores;

	std::map<CString, MoacallStore*> m_moa;
	std::map<CString, DaligoStore*> m_daligo;
	std::map<CString, RoadvoyStore*> m_roadvoy;
	std::map<CString, CombineNetStore*> m_combinet;
	std::map<CString, BeyondStore*> m_beyond;
	std::map<CString, SanggagStore*> m_sanggag;
	std::map<CString, StoreInfo*> m_store;

private:
	CMoacallLink moaLink;
	CDaligoLink daligoLink;
	CRoadvoyLink roadvoyLink;
	CCombineNetLink combinetLink;
	CBeyondLink beyondLink;
	CSanggagLink sanggagLink;
	CDelionDlvyLink delionLink;

	CFont m_font;
	CString c_ShopCode;
	int m_iItem;
	int m_iSubitem;
	BOOL b_init;
public:
	afx_msg void OnMove(int x, int y);
	
	afx_msg void OnCbnEditchangeComboAgency();
	BOOL CopyAllRowListToClipboard(BOOL isHeader, CListCtrl * pListCtrl, LPCTSTR lpszSeparator);
	BOOL CopyListCellToClipboard(CListCtrl * pListCtrl, LPCTSTR lpszSeparator);
};
