// LinkDlg.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "o2ns.h"
#include "LinkDlg.h"
#include "afxdialogex.h"

// CLinkDlg 대화 상자입니다.

IMPLEMENT_DYNAMIC(CLinkDlg, CDialogEx)

CLinkDlg::CLinkDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_LINK_DIALOG, pParent)
{

}

CLinkDlg::~CLinkDlg()
{
}

void CLinkDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT_SHOPCODE, m_EditShopCode);
	DDX_Control(pDX, IDC_LIST_STORES, m_ListStores);
	DDX_Control(pDX, IDC_BUTTON_CONFIRM, m_BtnConfirm);
	DDX_Control(pDX, IDC_BUTTON_LINK, m_BtnLink);
	DDX_Control(pDX, IDC_COMBO_AGENCY, m_ComboAgency);
}


BEGIN_MESSAGE_MAP(CLinkDlg, CDialogEx)
	//ON_EN_UPDATE(IDC_EDIT_SHOPCODE, &CLinkDlg::OnEnUpdateEditShopCode)
	ON_BN_CLICKED(IDC_BUTTON_CONFIRM, &CLinkDlg::OnBnClickedButtonConfirm)
	ON_BN_CLICKED(IDC_BUTTON_LINK, &CLinkDlg::OnBnClickedButtonLink)
	//ON_NOTIFY(NM_DBLCLK, IDC_LIST_STORES, &CLinkDlg::OnNMDblclkListStores)
	ON_WM_MOVE()
	ON_CBN_EDITCHANGE(IDC_COMBO_AGENCY, &CLinkDlg::OnCbnEditchangeComboAgency)
END_MESSAGE_MAP()


// CLinkDlg 메시지 처리기입니다.

BOOL CLinkDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	b_init = FALSE;

	m_BtnConfirm.m_nFlatStyle = CMFCButton::BUTTONSTYLE_NOBORDERS;
	m_BtnConfirm.m_bTransparent = FALSE;    // 투명도 설정
	m_BtnConfirm.m_bDrawFocus = FALSE;
	m_BtnConfirm.SetBkStdColor(RGB(60, 60, 60));
	m_BtnConfirm.SetTextStdColor(RGB(250, 250, 250));
	m_BtnConfirm.SetBkAltColor(RGB(110, 110, 110));
	m_BtnConfirm.SetTextAltColor(RGB(250, 250, 250));
	m_BtnConfirm.Update();
	//m_BtnNotice.SetFaceColor(RGB(250, 250, 250), TRUE);
	m_BtnConfirm.EnableWindowsTheming(FALSE);

	m_BtnLink.m_nFlatStyle = CMFCButton::BUTTONSTYLE_NOBORDERS;
	m_BtnLink.m_bTransparent = FALSE;    // 투명도 설정
	m_BtnLink.m_bDrawFocus = FALSE;
	m_BtnLink.SetBkStdColor(RGB(60, 60, 60));
	m_BtnLink.SetTextStdColor(RGB(250, 250, 250));
	m_BtnLink.SetBkAltColor(RGB(110, 110, 110));
	m_BtnLink.SetTextAltColor(RGB(250, 250, 250));
	m_BtnLink.Update();
	//m_BtnNotice.SetFaceColor(RGB(250, 250, 250), TRUE);
	m_BtnLink.EnableWindowsTheming(FALSE);

	m_font.CreateFont(
		16, // 문자 폭 
		0, // 문자 높이 
		0, // 기울기 각도
		0, // 문자 방향
		FW_HEAVY,            // 문자 굵기
		FALSE,               // 문자 기울림 모양
		FALSE,               // 밑 줄
		FALSE,               // 취소선
		DEFAULT_CHARSET,     // 문자 셋
		OUT_DEFAULT_PRECIS,  // 출력 정확도
		CLIP_DEFAULT_PRECIS, // 킬립핑 정확도
		DEFAULT_QUALITY,     // 출력의 질
		DEFAULT_PITCH,       // 자간 거리
		L"Arial"               // 문자 모양
	); // lpszFacename

	GetDlgItem(IDC_STATIC)->SetFont(&m_font, TRUE);
	//GetDlgItem(IDC_STATIC2)->SetFont(&m_font, TRUE);
	GetDlgItem(IDC_BUTTON_CONFIRM)->SetFont(&m_font, TRUE);
	GetDlgItem(IDC_BUTTON_LINK)->SetFont(&m_font, TRUE);

	m_font.Detach();

	m_font.CreateFont(
		16, // 문자 폭 
		0, // 문자 높이 
		0, // 기울기 각도
		0, // 문자 방향
		FALSE,            // 문자 굵기
		FALSE,               // 문자 기울림 모양
		FALSE,               // 밑 줄
		FALSE,               // 취소선
		DEFAULT_CHARSET,     // 문자 셋
		OUT_DEFAULT_PRECIS,  // 출력 정확도
		CLIP_DEFAULT_PRECIS, // 킬립핑 정확도
		DEFAULT_QUALITY,     // 출력의 질
		FIXED_PITCH,       // 자간 거리
		L"Arial"               // 문자 모양
	); // lpszFacename

	m_ListStores.SetFont(&m_font, TRUE);
	m_ComboAgency.SetFont(&m_font, TRUE);

	m_font.Detach();

	c_ShopCode = L"";

	if (!c_ShopCode.IsEmpty()) {
		m_EditShopCode.SetWindowText(c_ShopCode);
	}

	m_ListStores.DeleteAllItems();

	m_ListStores.ModifyStyle(0, LVS_SHOWSELALWAYS);
	m_ListStores.SetExtendedStyle(LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES); //LVS_EX_CHECKBOXES

	m_ListStores.InsertColumn(0, _T("매장명"), LVCFMT_LEFT, 100, -1);
	m_ListStores.InsertColumn(1, _T("대표자명"), LVCFMT_LEFT, 100, -1);
	m_ListStores.InsertColumn(2, _T("연동코드"), LVCFMT_LEFT, 100, -1);
	m_ListStores.InsertColumn(3, _T("매장 지점명"), LVCFMT_LEFT, 100, -1);
	m_ListStores.InsertColumn(4, _T("매장 전화"), LVCFMT_LEFT, 100, -1);
	m_ListStores.InsertColumn(5, _T("매장 휴대전화"), LVCFMT_LEFT, 100, -1);
	m_ListStores.InsertColumn(6, _T("매장 주소"), LVCFMT_LEFT, 100, -1);
	m_ListStores.AdjustColumnWidth();

	m_ComboAgency.InsertString(0, L"모아콜");
	m_ComboAgency.InsertString(1, L"와따");
	m_ComboAgency.InsertString(2, L"토마토딜리버리");
	m_ComboAgency.InsertString(3, L"달리고");
	m_ComboAgency.InsertString(4, L"슈퍼히어로");
	m_ComboAgency.InsertString(5, L"티앤비");
	m_ComboAgency.InsertString(6, L"로드보이");
	m_ComboAgency.InsertString(7, L"스파이더");
	m_ComboAgency.InsertString(8, L"행복배달");
	m_ComboAgency.InsertString(9, L"비욘드딜리버리"); // 이즈오케이->비욘드딜리버리
	m_ComboAgency.InsertString(10, L"최강배달");
	m_ComboAgency.InsertString(11, L"베테랑");
	//m_ComboAgency.InsertString(12, L"로드파일럿");
	m_ComboAgency.InsertString(12, L"배달인");
	m_ComboAgency.InsertString(13, L"레몬콜");
	//m_ComboAgency.InsertString(15, L"키친딜리버리");
	m_ComboAgency.InsertString(14, L"엠터치");
	m_ComboAgency.InsertString(15, L"하나로");
	m_ComboAgency.InsertString(16, L"생각대로");
	m_ComboAgency.InsertString(17, L"젠딜리");
	m_ComboAgency.InsertString(18, L"딜리온");
	m_ComboAgency.InsertString(19, L"배달로나라를구하신");
	m_ComboAgency.SetWindowText(L"");
	//m_ComboAgency.SetCurSel(1);

	b_init = TRUE;

	return TRUE;  // 포커스를 컨트롤에 설정하지 않으면 TRUE를 반환합니다.
}

BOOL CLinkDlg::PreTranslateMessage(MSG* pMsg)
{
	// TODO: 여기에 특수화된 코드를 추가 및/또는 기본 클래스를 호출합니다.
	switch (pMsg->message) {
	case WM_KEYDOWN:	// 키가 눌렸을때
		switch (pMsg->wParam) {
		case VK_RETURN:	// 리턴키\tab
			if (GetFocus() == GetDlgItem(IDC_EDIT_SHOPCODE))
				::SendMessage(GetSafeHwnd(), WM_COMMAND, MAKEWPARAM(IDC_BUTTON_CONFIRM, BN_CLICKED), 0);
			else if (GetFocus() == GetDlgItem(IDC_BUTTON_CONFIRM))
				::SendMessage(GetSafeHwnd(), WM_COMMAND, MAKEWPARAM(IDC_BUTTON_CONFIRM, BN_CLICKED), 0);
			return TRUE;
		case VK_ESCAPE:	// ESC키
			return TRUE;
		case 'C':
			if (GetKeyState(VK_CONTROL)<0)
			{
				int nID = GetFocus()->GetDlgCtrlID();
				if (nID == IDC_LIST_STORES) {
					if (GetKeyState(VK_SHIFT) < 0) {
						if (pMsg->hwnd == m_ListStores.GetSafeHwnd() &&
							GetFocus()->GetSafeHwnd() == m_ListStores.GetSafeHwnd())
						{
							CopyAllRowListToClipboard(TRUE, &m_ListStores, _T("\t"));
						}
					}
					else {
						if (pMsg->hwnd == m_ListStores.GetSafeHwnd() &&
							GetFocus()->GetSafeHwnd() == m_ListStores.GetSafeHwnd())
						{
							CopyListCellToClipboard(&m_ListStores, _T("\t"));
						}
					}
					return true;
				}
			}
		}
	}
	return CDialogEx::PreTranslateMessage(pMsg);
}

HBRUSH CLinkDlg::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CDialogEx::OnCtlColor(pDC, pWnd, nCtlColor);

	// TODO:  여기서 DC의 특성을 변경합니다.
	UINT nID = pWnd->GetDlgCtrlID();
	// TODO:  여기서 DC의 특성을 변경합니다.
	switch (nCtlColor) {
	case CTLCOLOR_STATIC:
		if (nID == IDC_STATIC || nID == IDC_STATIC3) {
			//pDC->SetTextColor(RGB(255, 0, 0));
			pDC->SetBkMode(TRANSPARENT);
			return (HBRUSH)GetStockObject(NULL_BRUSH);;
		}
		else if (nID == IDC_EDIT_SHOPCODE) {
			//pDC->SetBkMode(TRANSPARENT);
			pDC->SetBkMode(RGB(60, 60, 60));
			pDC->SetTextColor(RGB(255, 0, 0));
			//return (HBRUSH)GetStockObject(NULL_BRUSH);;
		}
	}
	// TODO:  기본값이 적당하지 않으면 다른 브러시를 반환합니다.
	return hbr;
}

BOOL CLinkDlg::OnEraseBkgnd(CDC* pDC)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	CRect rt, frame_rt;
	GetClientRect(rt);
	frame_rt.left = rt.left + 1;
	frame_rt.right = rt.right - 1;
	frame_rt.top = rt.top + 1;
	frame_rt.bottom = rt.bottom - 1;
	//pDC->FillSolidRect(rt, RGB(100, 140, 220));
	pDC->FillSolidRect(rt, RGB(60, 60, 60));
	pDC->FillSolidRect(frame_rt, RGB(250, 250, 250));


	return TRUE;
	//return CDialogEx::OnEraseBkgnd(pDC);
}

void CLinkDlg::OnBnClickedButtonConfirm()
{
	CHttpsRequest hReq;
	MoaResultData m_rdata;
	DaligoResultData d_rdata;
	RoadvoyResultData rv_rdata;
	CombineNetResultData cn_rdata;
	BeyondResultData by_rdata;
	SanggagResultData sg_rdata;
	ResultData rdata;
	CString list_seq_string;
	CString temp;
	CString selText;

	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	int ret = 0;
	m_EditShopCode.GetWindowText(c_ShopCode);
	
	if (!c_ShopCode.Compare(L"")) {
		if (!c_ShopCode.Compare(L""))
			MessageBox(L"사업자번호를 입력해주세요.", L"알림", MB_OK);
	}
	else {
		m_ComboAgency.GetWindowText(selText);
		if (!selText.Compare(L"모아콜")
			|| !selText.Compare(L"와따")
			|| !selText.Compare(L"토마토딜리버리")) {
			CJSLogger::Logger('i', "Moacall store search.");

			m_ListStores.DeleteAllItems();
			m_ListStores.DeleteAllColumns();
			m_ListStores.InsertColumn(0, _T("매장명"), LVCFMT_LEFT, 100, -1);
			m_ListStores.InsertColumn(1, _T("대표자명"), LVCFMT_LEFT, 100, -1);
			m_ListStores.InsertColumn(2, _T("연동코드"), LVCFMT_LEFT, 100, -1);
			m_ListStores.InsertColumn(3, _T("매장 지점명"), LVCFMT_LEFT, 100, -1);
			m_ListStores.InsertColumn(4, _T("매장 전화"), LVCFMT_LEFT, 100, -1);
			m_ListStores.InsertColumn(5, _T("매장 휴대전화"), LVCFMT_LEFT, 100, -1);
			m_ListStores.InsertColumn(6, _T("매장 주소"), LVCFMT_LEFT, 100, -1);

			ret = moaLink.StoreSearch(c_ShopCode, &m_moa, &m_rdata);

			if (ret) {
				temp.Format(L"Moacall store search fail.[%04d]: %s", ret, m_rdata.result_message);
				CJSLogger::Logger('e', "%s", CW2A(CT2W(temp), CP_UTF8));
				MessageBox(m_rdata.result_message, L"확인", MB_OK);
			}
			else {
				std::map<CString, MoacallStore*>::iterator itr;

				if (!m_moa.empty()) {
					for (auto itr = m_moa.begin(); itr != m_moa.end(); itr++) {
						m_ListStores.InsertItem(0, list_seq_string);
						m_ListStores.SetItem(0, 0, LVIF_TEXT, itr->second->store_name, 0, 0, 0, NULL);
						m_ListStores.SetItem(0, 1, LVIF_TEXT, itr->second->owner_name, 0, 0, 0, NULL);
						m_ListStores.SetItem(0, 2, LVIF_TEXT, itr->second->moacall_code, 0, 0, 0, NULL);
						m_ListStores.SetItem(0, 3, LVIF_TEXT, itr->second->branch_name, 0, 0, 0, NULL);
						m_ListStores.SetItem(0, 4, LVIF_TEXT, itr->second->store_phone, 0, 0, 0, NULL);
						m_ListStores.SetItem(0, 5, LVIF_TEXT, itr->second->store_mobile, 0, 0, 0, NULL);
						m_ListStores.SetItem(0, 6, LVIF_TEXT, itr->second->store_addr, 0, 0, 0, NULL);
						delete(itr->second);
						m_moa.erase(itr);
					}
				}
			}
		}
		else if (!selText.Compare(L"달리고")
			|| !selText.Compare(L"슈퍼히어로")
			|| !selText.Compare(L"티앤비")
			|| !selText.Compare(L"젠딜리")
			) {
			CJSLogger::Logger('i', "Daligo store search.");

			m_ListStores.DeleteAllItems();
			m_ListStores.DeleteAllColumns();
			m_ListStores.InsertColumn(0, _T("매장명"), LVCFMT_LEFT, 100, -1);
			m_ListStores.InsertColumn(1, _T("매장번호"), LVCFMT_LEFT, 100, -1);
			m_ListStores.InsertColumn(2, _T("연동코드"), LVCFMT_LEFT, 100, -1);
			m_ListStores.InsertColumn(3, _T("매장 전화"), LVCFMT_LEFT, 100, -1);
			m_ListStores.InsertColumn(4, _T("매장 주소"), LVCFMT_LEFT, 100, -1);

			if (!selText.Compare(L"달리고"))
				daligoLink.SetAgencyFlag(1);
			else if (!selText.Compare(L"슈퍼히어로"))
				daligoLink.SetAgencyFlag(2);
			else if (!selText.Compare(L"티앤비"))
				daligoLink.SetAgencyFlag(3);
			else if (!selText.Compare(L"젠딜리"))
				daligoLink.SetAgencyFlag(4);
			ret = daligoLink.StoreSearch(c_ShopCode, &m_daligo, &d_rdata);

			if (ret) {
				temp.Format(L"Daligo store search fail.[%04d]: %s", ret, d_rdata.ret_msg);
				CJSLogger::Logger('e', "%s", CW2A(CT2W(temp), CP_UTF8));
				MessageBox(d_rdata.ret_msg, L"확인", MB_OK);
			}
			else {
				std::map<CString, DaligoStore*>::iterator itr;

				if (!m_daligo.empty()) {
					for (auto itr = m_daligo.begin(); itr != m_daligo.end(); itr++) {
						int nameLen = 0;
						int numLen = 0;
						temp.Empty();
						m_ListStores.InsertItem(0, list_seq_string);
						m_ListStores.SetItem(0, 0, LVIF_TEXT, itr->second->store_name, 0, 0, 0, NULL);
						m_ListStores.SetItem(0, 1, LVIF_TEXT, itr->second->store_num, 0, 0, 0, NULL);
						
						CUtil::GetInitialFromHangeul(CT2W(itr->second->store_name), &temp, 20);
						//CUtil::han2eng(CT2W(itr->second->store_name), &temp, sizeof temp);
						temp.Remove(' ');
						temp.Remove('-');
						nameLen = temp.GetLength();
						numLen = itr->second->store_num.GetLength();
						if ((nameLen + numLen) > 40)
							itr->second->link_code = temp.Left(40 - numLen) + itr->second->store_num;
						else 
							itr->second->link_code = temp + itr->second->store_num;
						m_ListStores.SetItem(0, 2, LVIF_TEXT, itr->second->link_code, 0, 0, 0, NULL);
						m_ListStores.SetItem(0, 3, LVIF_TEXT, itr->second->store_phone, 0, 0, 0, NULL);
						m_ListStores.SetItem(0, 4, LVIF_TEXT, itr->second->store_addr, 0, 0, 0, NULL);
						delete(itr->second);
						m_daligo.erase(itr);
					}
				}
			}
		}
		else if (!selText.Compare(L"로드보이")) {
			CJSLogger::Logger('i', "Roadvoy store search.");

			m_ListStores.DeleteAllItems();
			m_ListStores.DeleteAllColumns();
			m_ListStores.InsertColumn(0, _T("매장명"), LVCFMT_LEFT, 100, -1);
			m_ListStores.InsertColumn(1, _T("로드보이ID"), LVCFMT_LEFT, 100, -1);
			m_ListStores.InsertColumn(2, _T("연동코드"), LVCFMT_LEFT, 100, -1);
			m_ListStores.InsertColumn(3, _T("매장 전화"), LVCFMT_LEFT, 100, -1);
			m_ListStores.InsertColumn(4, _T("매장 휴대전화"), LVCFMT_LEFT, 100, -1);
			m_ListStores.InsertColumn(5, _T("매장 주소"), LVCFMT_LEFT, 100, -1);

			ret = roadvoyLink.StoreSearch(c_ShopCode, &m_roadvoy, &rv_rdata);

			if (ret) {
				temp.Format(L"Daligo store search fail.[%04d]: %s", ret, rv_rdata.ret_msg);
				CJSLogger::Logger('e', "%s", CW2A(CT2W(temp), CP_UTF8));
				MessageBox(rv_rdata.ret_msg, L"확인", MB_OK);
			}
			else {
				std::map<CString, RoadvoyStore*>::iterator itr;

				if (!m_roadvoy.empty()) {
					for (auto itr = m_roadvoy.begin(); itr != m_roadvoy.end(); itr++) {
						int nameLen = 0;
						int numLen = 0;
						temp.Empty();
						m_ListStores.InsertItem(0, list_seq_string);
						m_ListStores.SetItem(0, 0, LVIF_TEXT, itr->second->store_name, 0, 0, 0, NULL);
						m_ListStores.SetItem(0, 1, LVIF_TEXT, itr->second->roadvoy_id, 0, 0, 0, NULL);

						CUtil::GetInitialFromHangeul(CT2W(itr->second->store_name), &temp, 20);
						//CUtil::han2eng(CT2W(itr->second->store_name), &temp, sizeof temp);
						itr->second->roadvoy_id.Remove('-');
						temp.Remove(' ');
						temp.Remove('-');
						nameLen = temp.GetLength();
						numLen = itr->second->roadvoy_id.GetLength();
						if ((nameLen + numLen) > 40)
							itr->second->link_code = temp.Left(40 - numLen) + itr->second->roadvoy_id;
						else
							itr->second->link_code = temp + itr->second->roadvoy_id;
						m_ListStores.SetItem(0, 2, LVIF_TEXT, itr->second->link_code, 0, 0, 0, NULL);
						m_ListStores.SetItem(0, 3, LVIF_TEXT, itr->second->store_phone, 0, 0, 0, NULL);
						m_ListStores.SetItem(0, 4, LVIF_TEXT, itr->second->store_mobile, 0, 0, 0, NULL);
						itr->second->addr_road += itr->second->addr_desc;
						m_ListStores.SetItem(0, 5, LVIF_TEXT, itr->second->addr_road, 0, 0, 0, NULL);
						delete(itr->second);
						m_roadvoy.erase(itr);
					}
				}
			}
		}
		else if (!selText.Compare(L"스파이더")
			|| !selText.Compare(L"행복배달")
			|| !selText.Compare(L"배달로나라를구하신")
			) {
			CJSLogger::Logger('i', "CombineNet store search.");

			m_ListStores.DeleteAllItems();
			m_ListStores.DeleteAllColumns();
			m_ListStores.InsertColumn(0, _T("매장명"), LVCFMT_LEFT, 100, -1);
			m_ListStores.InsertColumn(1, _T("매장고유번호"), LVCFMT_LEFT, 100, -1);
			m_ListStores.InsertColumn(2, _T("연동코드"), LVCFMT_LEFT, 100, -1);
			m_ListStores.InsertColumn(3, _T("매장 전화"), LVCFMT_LEFT, 100, -1);
			m_ListStores.InsertColumn(4, _T("매장 휴대전화"), LVCFMT_LEFT, 100, -1);
			m_ListStores.InsertColumn(5, _T("매장 주소"), LVCFMT_LEFT, 100, -1);

			if (!selText.Compare(L"행복배달"))	 // 이즈오케이->비욘드딜리버리
				combinetLink.SetAgencyFlag(cbn_hangbok);
			else if (!selText.Compare(L"스파이더"))
				combinetLink.SetAgencyFlag(cbn_spider);
			else if (!selText.Compare(L"배달로나라를구하신"))
				combinetLink.SetAgencyFlag(cbn_baena9);

			ret = combinetLink.StoreSearch(c_ShopCode, &m_combinet, &cn_rdata);

			if (ret) {
				temp.Format(L"CombineNet store search fail.[%04d]: %s", ret, cn_rdata.ret_msg);
				CJSLogger::Logger('e', "%s", CW2A(CT2W(temp), CP_UTF8));
				MessageBox(cn_rdata.ret_msg, L"확인", MB_OK);
			}
			else {
				std::map<CString, CombineNetStore*>::iterator itr;

				if (!m_combinet.empty()) {
					for (auto itr = m_combinet.begin(); itr != m_combinet.end(); itr++) {
						int nameLen = 0;
						int numLen = 0;
						temp.Empty();
						m_ListStores.InsertItem(0, list_seq_string);
						m_ListStores.SetItem(0, 0, LVIF_TEXT, itr->second->store_name, 0, 0, 0, NULL);
						m_ListStores.SetItem(0, 1, LVIF_TEXT, itr->second->combinenet_id, 0, 0, 0, NULL);

						CUtil::GetInitialFromHangeul(CT2W(itr->second->store_name), &temp, 20);
						//CUtil::han2eng(CT2W(itr->second->store_name), &temp, sizeof temp);
						itr->second->combinenet_id.Remove('-');
						temp.Remove(' ');
						temp.Remove('-');
						nameLen = temp.GetLength();
						numLen = itr->second->combinenet_id.GetLength();
						if ((nameLen + numLen) > 40)
							itr->second->link_code = temp.Left(40 - numLen) + itr->second->combinenet_id;
						else
							itr->second->link_code = temp + itr->second->combinenet_id;
						m_ListStores.SetItem(0, 2, LVIF_TEXT, itr->second->link_code, 0, 0, 0, NULL);
						m_ListStores.SetItem(0, 3, LVIF_TEXT, itr->second->store_phone, 0, 0, 0, NULL);
						m_ListStores.SetItem(0, 4, LVIF_TEXT, itr->second->store_mobile, 0, 0, 0, NULL);
						m_ListStores.SetItem(0, 5, LVIF_TEXT, itr->second->address, 0, 0, 0, NULL);
						delete(itr->second);
						m_combinet.erase(itr);
					}
				}
			}
		}
		else if (!selText.Compare(L"비욘드딜리버리")	 // 이즈오케이->비욘드딜리버리
			|| !selText.Compare(L"최강배달")
			|| !selText.Compare(L"베테랑")
			//|| !selText.Compare(L"로드파일럿")
			|| !selText.Compare(L"배달인")
			|| !selText.Compare(L"레몬콜")
			//|| !selText.Compare(L"키친딜리버리") 
			|| !selText.Compare(L"엠터치")
			|| !selText.Compare(L"하나로")
			) {
			CJSLogger::Logger('i', "Beyond store search.");
			int flag = 0;

			m_ListStores.DeleteAllItems();
			m_ListStores.DeleteAllColumns();
			m_ListStores.InsertColumn(0, _T("매장명"), LVCFMT_LEFT, 100, -1);
			m_ListStores.InsertColumn(1, _T("매장고유번호"), LVCFMT_LEFT, 100, -1);
			m_ListStores.InsertColumn(2, _T("연동코드"), LVCFMT_LEFT, 100, -1);
			m_ListStores.InsertColumn(3, _T("매장 전화"), LVCFMT_LEFT, 100, -1);
			m_ListStores.InsertColumn(4, _T("매장 휴대전화"), LVCFMT_LEFT, 100, -1);
			m_ListStores.InsertColumn(5, _T("매장 주소"), LVCFMT_LEFT, 100, -1);

			if (!selText.Compare(L"비욘드딜리버리"))	 // 이즈오케이->비욘드딜리버리
				beyondLink.SetServFlag(by_byservice);
			else if (!selText.Compare(L"최강배달"))
				beyondLink.SetServFlag(by_rushcall);
			else if (!selText.Compare(L"베테랑"))
				beyondLink.SetServFlag(by_veteran);
			//else if (!selText.Compare(L"로드파일럿"))
				//beyondLink.SetServFlag(by_roadpilot);
			else if (!selText.Compare(L"배달인"))
				beyondLink.SetServFlag(by_dsp);
			else if (!selText.Compare(L"레몬콜"))
				beyondLink.SetServFlag(by_fooding);
			//else if (!selText.Compare(L"키친딜리버리"))
				//beyondLink.SetServFlag(by_kitchen);
			else if (!selText.Compare(L"엠터치"))
				beyondLink.SetServFlag(by_mtouch);
			else if (!selText.Compare(L"하나로"))
				beyondLink.SetServFlag(by_hanaro);


			ret = beyondLink.StoreSearch(c_ShopCode, &m_beyond, &by_rdata);

			if (ret) {
				temp.Format(L"Beyond store search fail.[%04d]: %s", ret, by_rdata.result_message);
				CJSLogger::Logger('e', "%s", CW2A(CT2W(temp), CP_UTF8));
				MessageBox(by_rdata.result_message, L"확인", MB_OK);
			}
			else {
				std::map<CString, CombineNetStore*>::iterator itr;

				if (!m_beyond.empty()) {
					for (auto itr = m_beyond.begin(); itr != m_beyond.end(); itr++) {
						int nameLen = 0;
						int numLen = 0;
						temp.Empty();
						m_ListStores.InsertItem(0, list_seq_string);
						m_ListStores.SetItem(0, 0, LVIF_TEXT, itr->second->store_name, 0, 0, 0, NULL);
						m_ListStores.SetItem(0, 1, LVIF_TEXT, itr->second->beyond_code, 0, 0, 0, NULL);

						CUtil::GetInitialFromHangeul(CT2W(itr->second->store_name), &temp, 20);
						//CUtil::han2eng(CT2W(itr->second->store_name), &temp, sizeof temp);
						itr->second->beyond_code.Remove('-');
						temp.Remove(' ');
						temp.Remove('-');
						nameLen = temp.GetLength();
						numLen = itr->second->beyond_code.GetLength();
						if ((nameLen + numLen) > 40)
							itr->second->link_code = temp.Left(40 - numLen) + itr->second->beyond_code;
						else
							itr->second->link_code = temp + itr->second->beyond_code;
						m_ListStores.SetItem(0, 2, LVIF_TEXT, itr->second->link_code, 0, 0, 0, NULL);
						m_ListStores.SetItem(0, 3, LVIF_TEXT, itr->second->store_phone, 0, 0, 0, NULL);
						m_ListStores.SetItem(0, 4, LVIF_TEXT, itr->second->store_mobile, 0, 0, 0, NULL);
						m_ListStores.SetItem(0, 5, LVIF_TEXT, itr->second->store_addr, 0, 0, 0, NULL);
						delete(itr->second);
						m_beyond.erase(itr);
					}
				}
			}
		}
		else if (!selText.Compare(L"생각대로")) {
			CJSLogger::Logger('i', "Sanggag store search.");
			int flag = 0;

			m_ListStores.DeleteAllItems();
			m_ListStores.DeleteAllColumns();
			m_ListStores.InsertColumn(0, _T("매장명"), LVCFMT_LEFT, 100, -1);
			m_ListStores.InsertColumn(1, _T("매장고유번호"), LVCFMT_LEFT, 100, -1);
			m_ListStores.InsertColumn(2, _T("연동코드"), LVCFMT_LEFT, 100, -1);
			m_ListStores.InsertColumn(3, _T("매장 지점코드"), LVCFMT_LEFT, 100, -1);
			m_ListStores.InsertColumn(4, _T("매장 지점명"), LVCFMT_LEFT, 100, -1);
			m_ListStores.InsertColumn(5, _T("매장 전화"), LVCFMT_LEFT, 100, -1);
			m_ListStores.InsertColumn(6, _T("매장 휴대전화"), LVCFMT_LEFT, 100, -1);
			m_ListStores.InsertColumn(7, _T("매장 주소"), LVCFMT_LEFT, 100, -1);


			ret = sanggagLink.StoreSearch(c_ShopCode, &m_sanggag, &sg_rdata);

			if (ret) {
				temp.Format(L"Beyond store search fail.[%04d]: %s", ret, sg_rdata.ret_msg);
				CJSLogger::Logger('e', "%s", CW2A(CT2W(temp), CP_UTF8));
				MessageBox(sg_rdata.ret_msg, L"확인", MB_OK);
			}
			else {
				std::map<CString, SanggagStore*>::iterator itr;

				if (!m_sanggag.empty()) {
					for (auto itr = m_sanggag.begin(); itr != m_sanggag.end(); itr++) {
						int nameLen = 0;
						int numLen = 0;
						temp.Empty();
						m_ListStores.InsertItem(0, list_seq_string);
						m_ListStores.SetItem(0, 0, LVIF_TEXT, itr->second->store_name, 0, 0, 0, NULL);
						m_ListStores.SetItem(0, 1, LVIF_TEXT, itr->second->store_code, 0, 0, 0, NULL);
						
						CUtil::GetInitialFromHangeul(CT2W(itr->second->store_name), &temp, 20);
						//CUtil::han2eng(CT2W(itr->second->store_name), &temp, sizeof temp);
						itr->second->store_code.Remove('-');
						temp.Remove(' ');
						temp.Remove('-');
						nameLen = temp.GetLength();
						numLen = itr->second->store_code.GetLength();
						if ((nameLen + numLen) > 40)
							itr->second->link_code = temp.Left(40 - numLen) + itr->second->store_code;
						else
							itr->second->link_code = temp + itr->second->store_code;
						m_ListStores.SetItem(0, 2, LVIF_TEXT, itr->second->link_code, 0, 0, 0, NULL);
						m_ListStores.SetItem(0, 3, LVIF_TEXT, itr->second->branch_code, 0, 0, 0, NULL);
						m_ListStores.SetItem(0, 4, LVIF_TEXT, itr->second->branch_name, 0, 0, 0, NULL);
						m_ListStores.SetItem(0, 5, LVIF_TEXT, itr->second->store_phone, 0, 0, 0, NULL);
						m_ListStores.SetItem(0, 6, LVIF_TEXT, itr->second->store_mobile, 0, 0, 0, NULL);
						m_ListStores.SetItem(0, 7, LVIF_TEXT, itr->second->store_addr, 0, 0, 0, NULL);
						delete(itr->second);
						m_sanggag.erase(itr);
					}
				}
			}
		}
		else if (!selText.Compare(L"딜리온")) {
			CJSLogger::Logger('i', "Delion store search.");
			int flag = 0;

			m_ListStores.DeleteAllItems();
			m_ListStores.DeleteAllColumns();
			m_ListStores.InsertColumn(0, _T("매장명"), LVCFMT_LEFT, 100, -1);
			m_ListStores.InsertColumn(1, _T("매장고유번호"), LVCFMT_LEFT, 100, -1);
			m_ListStores.InsertColumn(2, _T("연동코드"), LVCFMT_LEFT, 100, -1);
			m_ListStores.InsertColumn(3, _T("사업자번호"), LVCFMT_LEFT, 100, -1);
			m_ListStores.InsertColumn(4, _T("매장 전화"), LVCFMT_LEFT, 100, -1);
			m_ListStores.InsertColumn(5, _T("매장 휴대전화"), LVCFMT_LEFT, 100, -1);
			m_ListStores.InsertColumn(6, _T("매장 주소"), LVCFMT_LEFT, 100, -1);


			ret = delionLink.StoreSearch(c_ShopCode, &m_store, &rdata);

			if (ret) {
				temp.Format(L"Beyond store search fail.[%04d]: %s", ret, rdata.ret_msg);
				CJSLogger::Logger('e', "%s", CW2A(CT2W(temp), CP_UTF8));
				MessageBox(rdata.ret_msg, L"확인", MB_OK);
			}
			else {
				std::map<CString, StoreInfo*>::iterator itr;

				if (!m_store.empty()) {
					for (auto itr = m_store.begin(); itr != m_store.end(); ) {
						int nameLen = 0;
						int numLen = 0;
						temp.Empty();
						m_ListStores.InsertItem(0, list_seq_string);
						m_ListStores.SetItem(0, 0, LVIF_TEXT, itr->second->store_name, 0, 0, 0, NULL);
						m_ListStores.SetItem(0, 1, LVIF_TEXT, itr->second->store_code, 0, 0, 0, NULL);

						CUtil::GetInitialFromHangeul(CT2W(itr->second->store_name), &temp, 20);
						//CUtil::han2eng(CT2W(itr->second->store_name), &temp, sizeof temp);
						itr->second->store_code.Remove('-');
						temp.Remove(' ');
						temp.Remove('-');
						
						itr->second->link_code = temp.Left(1) + itr->second->store_code;
						
						m_ListStores.SetItem(0, 2, LVIF_TEXT, itr->second->link_code, 0, 0, 0, NULL);
						m_ListStores.SetItem(0, 3, LVIF_TEXT, itr->second->biz_num, 0, 0, 0, NULL);
						m_ListStores.SetItem(0, 4, LVIF_TEXT, itr->second->store_phone, 0, 0, 0, NULL);
						m_ListStores.SetItem(0, 5, LVIF_TEXT, itr->second->store_mobile, 0, 0, 0, NULL);
						m_ListStores.SetItem(0, 6, LVIF_TEXT, itr->second->store_addr, 0, 0, 0, NULL);
						delete(itr->second);
						itr = m_store.erase(itr);
					}
				}
			}
		}
		m_ListStores.AdjustColumnWidth();
	}

}

void CLinkDlg::OnBnClickedButtonLink()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	MoaResultData m_rdata;
	DaligoResultData d_rdata;
	RoadvoyResultData rv_rdata;
	CombineNetResultData cn_rdata;
	BeyondResultData by_rdata;
	SanggagResultData sg_rdata;
	ResultData rdata;

	LookupStore mStore;
	CString linkCode;
	CString storeCode;
	CString storeNum;
	CString temp;
	CString error;
	CString selText;
	int ret = 0;
	int count = m_ListStores.GetItemCount();
	int index = -1;

	for (int i = 0; i < count; i++) {
		if (LVIS_SELECTED == m_ListStores.GetItemState(i, LVIS_SELECTED))
		{
			index = i;
			break;
		}
	}

	if (index == -1) {
		MessageBox(L"연동할 매장을 선택해주세요.", L"확인", MB_OK);
	}
	else {
		m_ComboAgency.GetWindowText(selText);
		if (!selText.Compare(L"모아콜")
			|| !selText.Compare(L"와따")
			|| !selText.Compare(L"토마토딜리버리")) {
			linkCode = m_ListStores.GetItemText(index, 2);
			temp.Format(L"해당 매장을 연동하시겠습니까?\n연동코드 : %s", linkCode);
			if (MessageBox(temp, L"연동", MB_YESNO) == IDYES) {
				temp.Empty();
				storeCode = m_ListStores.GetItemText(index, 3);
				CUtil::GetInitialFromHangeul(CT2W(storeCode), &temp, 6);
				temp.Remove(' ');
				temp.Remove('-');
				CTime c_time = CTime::GetCurrentTime(); // 현재 시스템으로부터 날짜 및 시간을 얻어 온다.
				storeCode.Empty();
				storeCode.Format(L"%04d%02d%02d%02d%02d%02d%s", c_time.GetYear(), c_time.GetMonth(), c_time.GetDay(), c_time.GetHour(), c_time.GetMinute(), c_time.GetSecond(), temp);
				storeCode.Replace(L" ", L"");
				ret = moaLink.StoreLink(&storeCode, linkCode, &m_rdata);

				if (ret) {
					temp.Empty();
					temp.Format(L"Moacall Link fail.[%04d]: %s. StoreCode : %s, LinkCode : %s", ret, m_rdata.result_message, storeCode, linkCode);
					CJSLogger::Logger('e', "%s", CW2A(CT2W(temp), CP_UTF8));
					MessageBox(m_rdata.result_message, L"경고", MB_ICONWARNING);
				}
				else {
					//LookupStore mStore;
					//MoacallStore mStore;
					mStore.agency_name = selText;
					mStore.biz_num = c_ShopCode;
					mStore.store_name = m_ListStores.GetItemText(index, 0);
					mStore.store_code = storeCode;
					mStore.owner_name = m_ListStores.GetItemText(index, 1);
					mStore.link_code = m_ListStores.GetItemText(index, 2);
					mStore.branch_name = m_ListStores.GetItemText(index, 3);
					mStore.store_phone = m_ListStores.GetItemText(index, 4);
					mStore.store_mobile = m_ListStores.GetItemText(index, 5);
					mStore.store_addr = m_ListStores.GetItemText(index, 6);
				}
			}
			else {
				ret = -99;
			}
		}
		else if (!selText.Compare(L"달리고")
			|| !selText.Compare(L"슈퍼히어로")
			|| !selText.Compare(L"티앤비")
			|| !selText.Compare(L"젠딜리")
			) {
			storeNum = m_ListStores.GetItemText(index, 1);
			linkCode = m_ListStores.GetItemText(index, 2);
			temp.Format(L"해당 매장을 연동하시겠습니까?\n연동코드 : %s", linkCode);
			if (MessageBox(temp, L"연동", MB_YESNO) == IDYES) {

				if (!selText.Compare(L"달리고"))
					daligoLink.SetAgencyFlag(1);
				else if (!selText.Compare(L"슈퍼히어로"))
					daligoLink.SetAgencyFlag(2);
				else if (!selText.Compare(L"티앤비"))
					daligoLink.SetAgencyFlag(3);
				else if (!selText.Compare(L"젠딜리"))
					daligoLink.SetAgencyFlag(4);
				ret = daligoLink.StoreLink(c_ShopCode, storeNum, linkCode, &d_rdata);

				if (ret) {
					temp.Empty();
					temp.Format(L"Daligo Link fail.[%04d]: %s. StoreCode : %s", ret, d_rdata.ret_msg, storeCode);
					CJSLogger::Logger('e', "%s", CW2A(CT2W(temp), CP_UTF8));
					MessageBox(d_rdata.ret_msg, L"경고", MB_ICONWARNING);
				}
				else {
					//LookupStore mStore;
					//MoacallStore mStore;
					mStore.agency_name = selText;
					mStore.biz_num = c_ShopCode;
					mStore.store_name = m_ListStores.GetItemText(index, 0);
					mStore.store_num = m_ListStores.GetItemText(index, 1);
					mStore.link_code = m_ListStores.GetItemText(index, 2);
					mStore.store_phone = m_ListStores.GetItemText(index, 3);
					mStore.store_addr = m_ListStores.GetItemText(index, 4);
				}
			}
			else {
				ret = -99;
			}
		}
		else if (!selText.Compare(L"로드보이")) {
			storeNum = m_ListStores.GetItemText(index, 1);
			linkCode = m_ListStores.GetItemText(index, 2);
			temp.Format(L"해당 매장을 연동하시겠습니까?\n연동코드 : %s", linkCode);
			if (MessageBox(temp, L"연동", MB_YESNO) == IDYES) {

				ret = roadvoyLink.StoreLink(storeNum, linkCode, &rv_rdata);

				if (ret) {
					temp.Empty();
					temp.Format(L"Roadvoy Link fail.[%04d]: %s. StoreCode : %s", ret, rv_rdata.ret_msg, storeCode);
					CJSLogger::Logger('e', "%s", CW2A(CT2W(temp), CP_UTF8));
					MessageBox(rv_rdata.ret_msg, L"경고", MB_ICONWARNING);
				}
				else {
					//LookupStore mStore;
					//MoacallStore mStore;
					mStore.agency_name = selText;
					mStore.biz_num = c_ShopCode;
					mStore.store_name = m_ListStores.GetItemText(index, 0);
					mStore.store_code = m_ListStores.GetItemText(index, 1);
					mStore.link_code = m_ListStores.GetItemText(index, 2);
					mStore.store_phone = m_ListStores.GetItemText(index, 3);
					mStore.store_mobile = m_ListStores.GetItemText(index, 4);
					mStore.store_addr = m_ListStores.GetItemText(index, 5);
				}
			}
			else {
				ret = -99;
			}
		}
		else if (!selText.Compare(L"스파이더")
			|| !selText.Compare(L"행복배달")
			|| !selText.Compare(L"배달로나라를구하신")
			) {
			storeNum = m_ListStores.GetItemText(index, 1);
			linkCode = m_ListStores.GetItemText(index, 2);
			temp.Format(L"해당 매장을 연동하시겠습니까?\n연동코드 : %s", linkCode);
			if (MessageBox(temp, L"연동", MB_YESNO) == IDYES) {

				if (!selText.Compare(L"행복배달"))	 // 이즈오케이->비욘드딜리버리
					combinetLink.SetAgencyFlag(cbn_hangbok);
				else if (!selText.Compare(L"스파이더"))
					combinetLink.SetAgencyFlag(cbn_spider);
				else if (!selText.Compare(L"배달로나라를구하신"))
					combinetLink.SetAgencyFlag(cbn_baena9);

				ret = combinetLink.StoreLink(storeNum, linkCode, &cn_rdata);

				if (ret) {
					temp.Empty();
					temp.Format(L"CombineNet Link fail.[%04d]: %s. StoreCode : %s", ret, cn_rdata.ret_msg, storeCode);
					CJSLogger::Logger('e', "%s", CW2A(CT2W(temp), CP_UTF8));
					MessageBox(cn_rdata.ret_msg, L"경고", MB_ICONWARNING);
				}
				else {
					//LookupStore mStore;
					//MoacallStore mStore;
					mStore.agency_name = selText;
					mStore.biz_num = c_ShopCode;
					mStore.store_name = m_ListStores.GetItemText(index, 0);
					mStore.store_code = m_ListStores.GetItemText(index, 1);
					mStore.link_code = m_ListStores.GetItemText(index, 2);
					mStore.store_phone = m_ListStores.GetItemText(index, 3);
					mStore.store_mobile = m_ListStores.GetItemText(index, 4);
					mStore.store_addr = m_ListStores.GetItemText(index, 5);
				}
			}
			else {
				ret = -99;
			}
		}
		else if (!selText.Compare(L"비욘드딜리버리")	 // 이즈오케이->비욘드딜리버리
			|| !selText.Compare(L"최강배달")
			|| !selText.Compare(L"베테랑")
			//|| !selText.Compare(L"로드파일럿")
			|| !selText.Compare(L"배달인")
			|| !selText.Compare(L"레몬콜")
			//|| !selText.Compare(L"키친딜리버리")
			|| !selText.Compare(L"엠터치")
			|| !selText.Compare(L"하나로")
			) {
			storeNum = m_ListStores.GetItemText(index, 1);
			linkCode = m_ListStores.GetItemText(index, 2);
			temp.Format(L"해당 매장을 연동하시겠습니까?\n연동코드 : %s", linkCode);
			if (MessageBox(temp, L"연동", MB_YESNO) == IDYES) {

				if (!selText.Compare(L"비욘드딜리버리"))	 // 이즈오케이->비욘드딜리버리
					beyondLink.SetServFlag(by_byservice);
				else if (!selText.Compare(L"최강배달"))
					beyondLink.SetServFlag(by_rushcall);
				else if (!selText.Compare(L"베테랑"))
					beyondLink.SetServFlag(by_veteran);
				//else if (!selText.Compare(L"로드파일럿"))
					//beyondLink.SetServFlag(by_roadpilot);
				else if (!selText.Compare(L"배달인"))
					beyondLink.SetServFlag(by_dsp);
				else if (!selText.Compare(L"레몬콜"))
					beyondLink.SetServFlag(by_fooding);
				//else if (!selText.Compare(L"키친딜리버리"))
					//beyondLink.SetServFlag(by_kitchen);
				else if (!selText.Compare(L"엠터치"))
					beyondLink.SetServFlag(by_mtouch);
				else if (!selText.Compare(L"하나로"))
					beyondLink.SetServFlag(by_hanaro);

				ret = beyondLink.StoreLink(storeNum, linkCode, TRUE, &by_rdata);

				if (ret) {
					temp.Empty();
					temp.Format(L"Beyond Link fail.[%04d]: %s. StoreCode : %s", ret, by_rdata.result_message, storeCode);
					CJSLogger::Logger('e', "%s", CW2A(CT2W(temp), CP_UTF8));
					MessageBox(by_rdata.result_message, L"경고", MB_ICONWARNING);
				}
				else {
					mStore.agency_name = selText;
					mStore.biz_num = c_ShopCode;
					mStore.store_name = m_ListStores.GetItemText(index, 0);
					mStore.store_code = m_ListStores.GetItemText(index, 1);
					mStore.link_code = m_ListStores.GetItemText(index, 2);
					mStore.store_phone = m_ListStores.GetItemText(index, 3);
					mStore.store_mobile = m_ListStores.GetItemText(index, 4);
					mStore.store_addr = m_ListStores.GetItemText(index, 5);
				}
			}
			else {
				ret = -99;
			}
		}
		else if (!selText.Compare(L"생각대로")) {
			CString branch_code;
			storeNum = m_ListStores.GetItemText(index, 1);
			linkCode = m_ListStores.GetItemText(index, 2);
			branch_code = m_ListStores.GetItemText(index, 3);

			temp.Format(L"해당 매장을 연동하시겠습니까?\n연동코드 : %s", linkCode);
			if (MessageBox(temp, L"연동", MB_YESNO) == IDYES) {

				ret = sanggagLink.StoreLink(branch_code, storeNum, linkCode, &sg_rdata);

				if (ret) {
					temp.Empty();
					temp.Format(L"Sanggag Link fail.[%04d]: %s. StoreCode : %s", ret, sg_rdata.ret_msg, storeCode);
					CJSLogger::Logger('e', "%s", CW2A(CT2W(temp), CP_UTF8));
					MessageBox(sg_rdata.ret_msg, L"경고", MB_ICONWARNING);
				}
				else {
					//LookupStore mStore;
					//MoacallStore mStore;
					mStore.agency_name = selText;
					mStore.biz_num = c_ShopCode;
					mStore.store_name = m_ListStores.GetItemText(index, 0);
					mStore.store_code = m_ListStores.GetItemText(index, 1);
					mStore.link_code = m_ListStores.GetItemText(index, 2);
					mStore.branch_name = m_ListStores.GetItemText(index, 4);
					mStore.store_phone = m_ListStores.GetItemText(index, 5);
					mStore.store_mobile = m_ListStores.GetItemText(index, 6);
					mStore.store_addr = m_ListStores.GetItemText(index, 7);
				}
			}
			else {
				ret = -99;
			}
		}
		else if (!selText.Compare(L"딜리온")) {
			CString branch_code;
			storeNum = m_ListStores.GetItemText(index, 1);
			linkCode = m_ListStores.GetItemText(index, 2);

			temp.Format(L"해당 매장을 연동하시겠습니까?\n연동코드 : %s", linkCode);
			if (MessageBox(temp, L"연동", MB_YESNO) == IDYES) {

				ret = delionLink.StoreLink(storeNum, linkCode, &rdata);

				if (ret) {
					temp.Empty();
					temp.Format(L"DelionDlvy Link fail.[%04d]: %s. StoreCode : %s", ret, rdata.ret_msg, storeCode);
					CJSLogger::Logger('e', "%s", CW2A(CT2W(temp), CP_UTF8));
					MessageBox(rdata.ret_msg, L"경고", MB_ICONWARNING);
				}
				else {
					//LookupStore mStore;
					//MoacallStore mStore;
					mStore.agency_name = selText;
					mStore.store_name = m_ListStores.GetItemText(index, 0);
					mStore.store_code = m_ListStores.GetItemText(index, 1);
					mStore.link_code = m_ListStores.GetItemText(index, 2);
					mStore.biz_num = m_ListStores.GetItemText(index, 3);
					mStore.store_phone = m_ListStores.GetItemText(index, 4);
					mStore.store_mobile = m_ListStores.GetItemText(index, 5);
					mStore.store_addr = m_ListStores.GetItemText(index, 6);
				}
			}
			else {
				ret = -99;
			}
		}

		if(!ret) {
			//MoacallStore mStore;
			CUtil::ReplaceSpecialCharacter(&(mStore.agency_name));
			CUtil::ReplaceSpecialCharacter(&(mStore.link_code));
			CUtil::ReplaceSpecialCharacter(&(mStore.branch_name));
			CUtil::ReplaceSpecialCharacter(&(mStore.biz_num));
			CUtil::ReplaceSpecialCharacter(&(mStore.owner_name));
			CUtil::ReplaceSpecialCharacter(&(mStore.store_name));
			CUtil::ReplaceSpecialCharacter(&(mStore.store_num));
			CUtil::ReplaceSpecialCharacter(&(mStore.store_code));
			CUtil::ReplaceSpecialCharacter(&(mStore.store_addr));
			CUtil::ReplaceSpecialCharacter(&(mStore.store_phone));
			CUtil::ReplaceSpecialCharacter(&(mStore.store_mobile));

			ret = CCustomMysql::InsertDeliveryLink(mStore, &error);

			temp.Empty();
			if (ret) {
				CJSLogger::Logger('e', "%s", CW2A(CT2W(error), CP_UTF8));
				temp.Format(L"연동 되었지만 서버전송에 실패했습니다. 개발자에게 전달해 주십시오.\n연동코드 : %s", linkCode);
				MessageBox(temp, L"경고", MB_ICONWARNING);
			}
			else {
				temp.Format(L"연동 되었습니다.\n연동코드 : %s", linkCode);
				MessageBox(temp, L"확인", MB_OK);
			}
		}
	}

}

void CLinkDlg::OnMove(int x, int y)
{
	CDialogEx::OnMove(x, y);

	// TODO: 여기에 메시지 처리기 코드를 추가합니다.

	if (b_init) {
		CRect rt;
		GetClientRect(rt);

		GetDlgItem(IDC_COMBO_AGENCY)->MoveWindow(rt.left + 10, rt.top + 10, 90, 25);
		GetDlgItem(IDC_STATIC)->MoveWindow(rt.left + 110, rt.top + 10, 60, 25);
		GetDlgItem(IDC_EDIT_SHOPCODE)->MoveWindow(rt.left + 190, rt.top + 10, 200, 25);
		GetDlgItem(IDC_BUTTON_CONFIRM)->MoveWindow(rt.left + 400, rt.top + 10, 65, 25);
		GetDlgItem(IDC_BUTTON_LINK)->MoveWindow(rt.right - 75, rt.top + 10, 65, 25);
		GetDlgItem(IDC_LIST_STORES)->MoveWindow(rt.left + 10, rt.top + 45, rt.Width() - 20, rt.Height() - 55);
	}
	
}


void CLinkDlg::OnCbnEditchangeComboAgency()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CString selText;

	m_ComboAgency.GetWindowText(selText);
	if (!selText.Compare(L"모아콜")
		|| !selText.Compare(L"와따")
		|| !selText.Compare(L"토마토딜리버리")) {
		m_ListStores.DeleteAllColumns();
		m_ListStores.InsertColumn(0, _T("매장명"), LVCFMT_LEFT, 100, -1);
		m_ListStores.InsertColumn(1, _T("대표자명"), LVCFMT_LEFT, 100, -1);
		m_ListStores.InsertColumn(2, _T("연동코드"), LVCFMT_LEFT, 100, -1);
		m_ListStores.InsertColumn(3, _T("매장 지점명"), LVCFMT_LEFT, 100, -1);
		m_ListStores.InsertColumn(4, _T("매장 전화"), LVCFMT_LEFT, 100, -1);
		m_ListStores.InsertColumn(5, _T("매장 휴대전화"), LVCFMT_LEFT, 100, -1);
		m_ListStores.InsertColumn(6, _T("매장 주소"), LVCFMT_LEFT, 100, -1);
	}else if (!selText.Compare(L"달리고")
		|| !selText.Compare(L"슈퍼히어로")
		|| !selText.Compare(L"티앤비")
		|| !selText.Compare(L"젠딜리")) {
		m_ListStores.DeleteAllColumns();
		m_ListStores.InsertColumn(0, _T("매장명"), LVCFMT_LEFT, 100, -1);
		m_ListStores.InsertColumn(1, _T("연동코드"), LVCFMT_LEFT, 100, -1);
		m_ListStores.InsertColumn(2, _T("매장고유번호"), LVCFMT_LEFT, 100, -1);
		m_ListStores.InsertColumn(3, _T("매장 전화"), LVCFMT_LEFT, 100, -1);
		m_ListStores.InsertColumn(4, _T("매장 주소"), LVCFMT_LEFT, 100, -1);
	}
	else if (!selText.Compare(L"로드보이")) {
		m_ListStores.DeleteAllColumns();
		m_ListStores.InsertColumn(0, _T("매장명"), LVCFMT_LEFT, 100, -1);
		m_ListStores.InsertColumn(1, _T("로드보이ID"), LVCFMT_LEFT, 100, -1);
		m_ListStores.InsertColumn(2, _T("연동코드"), LVCFMT_LEFT, 100, -1);
		m_ListStores.InsertColumn(3, _T("매장 전화"), LVCFMT_LEFT, 100, -1);
		m_ListStores.InsertColumn(4, _T("매장 휴대전화"), LVCFMT_LEFT, 100, -1);
		m_ListStores.InsertColumn(5, _T("매장 주소"), LVCFMT_LEFT, 100, -1);
	}
	else if (!selText.Compare(L"스파이더")
		|| !selText.Compare(L"행복배달")
		|| !selText.Compare(L"배달로나라를구하신")) {
		m_ListStores.DeleteAllColumns();
		m_ListStores.InsertColumn(0, _T("매장명"), LVCFMT_LEFT, 100, -1);
		m_ListStores.InsertColumn(1, _T("매장고유번호"), LVCFMT_LEFT, 100, -1);
		m_ListStores.InsertColumn(2, _T("연동코드"), LVCFMT_LEFT, 100, -1);
		m_ListStores.InsertColumn(3, _T("매장 전화"), LVCFMT_LEFT, 100, -1);
		m_ListStores.InsertColumn(4, _T("매장 휴대전화"), LVCFMT_LEFT, 100, -1);
		m_ListStores.InsertColumn(5, _T("매장 주소"), LVCFMT_LEFT, 100, -1);
	}
	else if (!selText.Compare(L"비욘드딜리버리")	 // 이즈오케이->비욘드딜리버리
		|| !selText.Compare(L"최강배달")
		|| !selText.Compare(L"베테랑")
		//|| !selText.Compare(L"로드파일럿")
		|| !selText.Compare(L"배달인")
		|| !selText.Compare(L"레몬콜")
		//|| !selText.Compare(L"키친딜리버리")
		|| !selText.Compare(L"엠터치")
		|| !selText.Compare(L"하나로")
		) {
		m_ListStores.DeleteAllColumns();
		m_ListStores.InsertColumn(0, _T("매장명"), LVCFMT_LEFT, 100, -1);
		m_ListStores.InsertColumn(1, _T("매장고유번호"), LVCFMT_LEFT, 100, -1);
		m_ListStores.InsertColumn(2, _T("연동코드"), LVCFMT_LEFT, 100, -1);
		m_ListStores.InsertColumn(3, _T("매장 전화"), LVCFMT_LEFT, 100, -1);
		m_ListStores.InsertColumn(4, _T("매장 휴대전화"), LVCFMT_LEFT, 100, -1);
		m_ListStores.InsertColumn(5, _T("매장 주소"), LVCFMT_LEFT, 100, -1);
	}
	else if (!selText.Compare(L"생각대로")) {
		m_ListStores.DeleteAllColumns();
		m_ListStores.InsertColumn(0, _T("매장명"), LVCFMT_LEFT, 100, -1);
		m_ListStores.InsertColumn(1, _T("매장고유번호"), LVCFMT_LEFT, 100, -1);
		m_ListStores.InsertColumn(2, _T("연동코드"), LVCFMT_LEFT, 100, -1);
		m_ListStores.InsertColumn(3, _T("매장 지점코드"), LVCFMT_LEFT, 100, -1);
		m_ListStores.InsertColumn(4, _T("매장 지점명"), LVCFMT_LEFT, 100, -1);
		m_ListStores.InsertColumn(5, _T("매장 전화"), LVCFMT_LEFT, 100, -1);
		m_ListStores.InsertColumn(6, _T("매장 휴대전화"), LVCFMT_LEFT, 100, -1);
		m_ListStores.InsertColumn(7, _T("매장 주소"), LVCFMT_LEFT, 100, -1);
	}
	else if (!selText.Compare(L"딜리온")) {
		m_ListStores.DeleteAllColumns();
		m_ListStores.InsertColumn(0, _T("매장명"), LVCFMT_LEFT, 100, -1);
		m_ListStores.InsertColumn(1, _T("매장고유번호"), LVCFMT_LEFT, 100, -1);
		m_ListStores.InsertColumn(2, _T("연동코드"), LVCFMT_LEFT, 100, -1);
		m_ListStores.InsertColumn(3, _T("사업자번호"), LVCFMT_LEFT, 100, -1);
		m_ListStores.InsertColumn(4, _T("매장 전화"), LVCFMT_LEFT, 100, -1);
		m_ListStores.InsertColumn(5, _T("매장 휴대전화"), LVCFMT_LEFT, 100, -1);
		m_ListStores.InsertColumn(6, _T("매장 주소"), LVCFMT_LEFT, 100, -1);
	}

	m_ListStores.AdjustColumnWidth();
}

BOOL CLinkDlg::CopyAllRowListToClipboard(BOOL isHeader, CListCtrl* pListCtrl, LPCTSTR lpszSeparator /*= _T("\t")*/)
{
	ASSERT(pListCtrl && ::IsWindow(pListCtrl->GetSafeHwnd()));

	CString sResult;
	POSITION pos = pListCtrl->GetFirstSelectedItemPosition();
	if (!pos)
		return TRUE;

	CWaitCursor wait;
	int nItem, nCount = 0;
	int nColumn = 1;

	//컬럼 이름 관련 구조체
	TCHAR szName[128]; // This is the buffer where the name will be stored
	LVCOLUMN lvColInfo;
	lvColInfo.mask = LVCF_TEXT;
	lvColInfo.pszText = szName;
	lvColInfo.cchTextMax = _countof(szName);

	//헤더와 컬럼 갯수 구하기
	if ((pListCtrl->GetStyle() & LVS_TYPEMASK) == LVS_REPORT &&
		pListCtrl->GetExtendedStyle() & LVS_EX_FULLROWSELECT)
	{
		CHeaderCtrl* pHeader = pListCtrl->GetHeaderCtrl();
		nColumn = pHeader ? pHeader->GetItemCount() : 1;
	}

	//컬럼 이름 삽입
	if (isHeader) {
		for (int i = 0; i < nColumn; ++i)
		{
			pListCtrl->GetColumn(i, &lvColInfo);

			sResult += lvColInfo.pszText;
			if (i != nColumn - 1)
				sResult += lpszSeparator;
		}
		sResult += _T("\r\n");
	}
	
	//데이터 내용 삽입
	while (pos)
	{
		nItem = pListCtrl->GetNextSelectedItem(pos);
		if (0 != nCount)
			sResult += _T("\r\n");

		for (int i = 0; i < nColumn; ++i)
		{
			sResult += pListCtrl->GetItemText(nItem, i);
			if (i != nColumn - 1)
				sResult += lpszSeparator;
		}
		++nCount;
	}
	sResult += _T("\r\n");

	//클립보드 저장
	if (pListCtrl->OpenClipboard())
	{
		EmptyClipboard();

		int nLen = sResult.GetLength() * sizeof(WCHAR) + 1;
		HGLOBAL hGlobal = GlobalAlloc(GMEM_MOVEABLE | GMEM_DDESHARE, nLen);
		LPBYTE pGlobalData = (LPBYTE)GlobalLock(hGlobal);

		USES_CONVERSION_EX;
		CopyMemory(pGlobalData, T2CW_EX(sResult, _ATL_SAFE_ALLOCA_DEF_THRESHOLD), nLen);
		SetClipboardData(CF_UNICODETEXT, hGlobal);

		GlobalUnlock(hGlobal);
		GlobalFree(hGlobal);

		CloseClipboard();
		return TRUE;
	}
	return FALSE;
}

BOOL CLinkDlg::CopyListCellToClipboard(CListCtrl * pListCtrl, LPCTSTR lpszSeparator)
{
	ASSERT(pListCtrl && ::IsWindow(pListCtrl->GetSafeHwnd()));

	CString sResult;
	CString temp;
	POSITION pos = pListCtrl->GetFirstSelectedItemPosition();
	if (!pos)
		return TRUE;

	CWaitCursor wait;
	int nItem, nCount = 0;
	int nColumn = 1;
	int subItem = -1;

	//컬럼 이름 관련 구조체
	TCHAR szName[128]; // This is the buffer where the name will be stored
	LVCOLUMN lvColInfo;
	lvColInfo.mask = LVCF_TEXT;
	lvColInfo.pszText = szName;
	lvColInfo.cchTextMax = _countof(szName);

	//헤더와 컬럼 갯수 구하기
	if ((pListCtrl->GetStyle() & LVS_TYPEMASK) == LVS_REPORT &&
		pListCtrl->GetExtendedStyle() & LVS_EX_FULLROWSELECT)
	{
		CHeaderCtrl* pHeader = pListCtrl->GetHeaderCtrl();
		nColumn = pHeader ? pHeader->GetItemCount() : 1;
	}

	//컬럼 이름 삽입
	for (int i = 0; i < nColumn; ++i)
	{
		pListCtrl->GetColumn(i, &lvColInfo);

		temp = lvColInfo.pszText;
		if (!temp.Compare(L"연동코드")) {
			subItem = i;
			break;
		}
	}
	

	//데이터 내용 삽입
	while (pos)
	{
		if (0 != nCount)
			sResult += _T("\r\n");
		nItem = pListCtrl->GetNextSelectedItem(pos);
		sResult += pListCtrl->GetItemText(nItem, subItem);
		++nCount;
	}

	//클립보드 저장
	if (pListCtrl->OpenClipboard())
	{
		EmptyClipboard();

		int nLen = sResult.GetLength() * sizeof(WCHAR) + 1;
		HGLOBAL hGlobal = GlobalAlloc(GMEM_MOVEABLE | GMEM_DDESHARE, nLen);
		LPBYTE pGlobalData = (LPBYTE)GlobalLock(hGlobal);

		USES_CONVERSION_EX;
		CopyMemory(pGlobalData, T2CW_EX(sResult, _ATL_SAFE_ALLOCA_DEF_THRESHOLD), nLen);
		SetClipboardData(CF_UNICODETEXT, hGlobal);

		GlobalUnlock(hGlobal);
		GlobalFree(hGlobal);

		CloseClipboard();
		return TRUE;
	}
	return FALSE;
}