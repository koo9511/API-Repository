#pragma once
#include "afxwin.h"
#include "afxbutton.h"
#include "afxdtctl.h"
#include "afxcmn.h"
#include "MyMfcButton.h"
#include "MyListCtrl.h"
#include "resource.h"
#include "CustomMysql.h"
#include "MoacallLink.h"
#include "DaligoLink.h"
#include "RoadvoyLink.h"
#include "CombineNetLink.h"
#include "BeyondLink.h"
#include "DelionDlvyLink.h"

// CLookupDlg 대화 상자입니다.

class CLookupDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CLookupDlg)

public:
	CLookupDlg(CWnd* pParent = NULL);   // 표준 생성자입니다.
	virtual ~CLookupDlg();

// 대화 상자 데이터입니다.
	enum { IDD = IDD_LOOKUP_DIALOG};

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.
	virtual BOOL OnInitDialog();
	virtual BOOL PreTranslateMessage(MSG* pMsg);

	DECLARE_MESSAGE_MAP()

private:
	CFont m_font;
	BOOL b_init;

	CEdit m_EditBizCode;
	CEdit m_EditMoaCode;
	CMyMfcButton m_BtnLookup;
	CMyMfcButton m_BtnUnlink;
	CComboBox m_ComboAgency;
	CDateTimeCtrl m_DateTimeStart;
	CDateTimeCtrl m_DateTimeEnd;
	CMyListCtrl m_ListLookup;


	CString m_Bizcode;
	CString m_Moacode;
	CString m_DateStart;
	CString m_DateEnd;

	int  m_SortedColumn;
	BOOL m_Ascending;

	CDaligoLink daligoLink;
	CRoadvoyLink roadvoyLink;
	CCombineNetLink combinetLink;
	CBeyondLink beyondLink;
	CDelionDlvyLink delionLink;
public:
	LookupCondition l_condition;
	//std::map<CString, res_moacall_store*> m_MoaStore;

	afx_msg void OnMove(int x, int y);
	afx_msg void OnBnClickedMfcbuttonLookup();
//	afx_msg void OnHdnItemclickListLookup(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnLvnColumnclickListLookup(NMHDR *pNMHDR, LRESULT *pResult);

	static int CALLBACK CompareFunc(LPARAM lParam1, LPARAM lParam2, LPARAM lParam);
	CButton m_CheckStart;
	CButton m_CheckEnd;
	
	afx_msg void OnBnClickedMfcbuttonUnlink();
	BOOL CopyAllRowListToClipboard(BOOL isHeader, CListCtrl * pListCtrl, LPCTSTR lpszSeparator);
	BOOL CopyListCellToClipboard(CListCtrl * pListCtrl, LPCTSTR lpszSeparator);
};
