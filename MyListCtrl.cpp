#include "stdafx.h"
#include "MyListCtrl.h"


CMyListCtrl::CMyListCtrl()
{
}


CMyListCtrl::~CMyListCtrl()
{
}


void CMyListCtrl::AdjustColumnWidth()
{
	SetRedraw(FALSE);
	int nColumnCount = GetColumnCount();

	for (int i = 0; i < nColumnCount; i++)
	{
		SetColumnWidth(i, LVSCW_AUTOSIZE);
		int nColumnWidth = GetColumnWidth(i);
		SetColumnWidth(i, LVSCW_AUTOSIZE_USEHEADER);
		int nHeaderWidth = GetColumnWidth(i);
		SetColumnWidth(i, max(nColumnWidth, nHeaderWidth));
	}
	SetRedraw(TRUE);
}

int CMyListCtrl::GetColumnCount()
{
	CHeaderCtrl* pHeaderCtrl = GetHeaderCtrl();
	return (pHeaderCtrl->GetItemCount());
}

void CMyListCtrl::DeleteAllColumns() {	int nCol = this->GetColumnCount();
	for (int i = 0; i < nCol; i++) {		this->DeleteColumn(0);	}}