#pragma once
#include "afxcmn.h"
class CMyListCtrl :
	public CListCtrl
{
public:
	CMyListCtrl();
	~CMyListCtrl();

	void AdjustColumnWidth();
	int GetColumnCount();
	void DeleteAllColumns();
};

