// LookupDlg.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "o2ns.h"
#include "LookupDlg.h"
#include "afxdialogex.h"

// CLookupDlg 대화 상자입니다.

IMPLEMENT_DYNAMIC(CLookupDlg, CDialogEx)

CLookupDlg::CLookupDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CLookupDlg::IDD, pParent)
{

}

CLookupDlg::~CLookupDlg()
{
}

void CLookupDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT_BIZCODE, m_EditBizCode);
	DDX_Control(pDX, IDC_EDIT_LINKCODE, m_EditMoaCode);
	DDX_Control(pDX, IDC_MFCBUTTON_LOOKUP, m_BtnLookup);
	DDX_Control(pDX, IDC_DATETIMEPICKER_START, m_DateTimeStart);
	DDX_Control(pDX, IDC_DATETIMEPICKER_END, m_DateTimeEnd);
	DDX_Control(pDX, IDC_LIST_LOOKUP, m_ListLookup);
	DDX_Control(pDX, IDC_CHECK_START, m_CheckStart);
	DDX_Control(pDX, IDC_CHECK_END, m_CheckEnd);
	DDX_Control(pDX, IDC_COMBO_AGENCY2, m_ComboAgency);
	DDX_Control(pDX, IDC_MFCBUTTON_UNLINK, m_BtnUnlink);
}


BEGIN_MESSAGE_MAP(CLookupDlg, CDialogEx)
	ON_WM_MOVE()
	ON_BN_CLICKED(IDC_MFCBUTTON_LOOKUP, &CLookupDlg::OnBnClickedMfcbuttonLookup)
//	ON_NOTIFY(HDN_ITEMCLICK, 0, &CLookupDlg::OnHdnItemclickListLookup)
	ON_NOTIFY(LVN_COLUMNCLICK, IDC_LIST_LOOKUP, &CLookupDlg::OnLvnColumnclickListLookup)
	ON_BN_CLICKED(IDC_MFCBUTTON_UNLINK, &CLookupDlg::OnBnClickedMfcbuttonUnlink)
END_MESSAGE_MAP()


// CLookupDlg 메시지 처리기입니다.

BOOL CLookupDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();
	
	b_init = FALSE;
	m_BtnLookup.m_nFlatStyle = CMFCButton::BUTTONSTYLE_NOBORDERS;
	m_BtnLookup.m_bTransparent = FALSE;    // 투명도 설정
	m_BtnLookup.m_bDrawFocus = FALSE;
	m_BtnLookup.SetBkStdColor(RGB(60, 60, 60));
	m_BtnLookup.SetTextStdColor(RGB(250, 250, 250));
	m_BtnLookup.SetBkAltColor(RGB(110, 110, 110));
	m_BtnLookup.SetTextAltColor(RGB(250, 250, 250));
	m_BtnLookup.Update();
	m_BtnLookup.EnableWindowsTheming(FALSE);

	m_BtnUnlink.m_nFlatStyle = CMFCButton::BUTTONSTYLE_NOBORDERS;
	m_BtnUnlink.m_bTransparent = FALSE;    // 투명도 설정
	m_BtnUnlink.m_bDrawFocus = FALSE;
	m_BtnUnlink.SetBkStdColor(RGB(60, 60, 60));
	m_BtnUnlink.SetTextStdColor(RGB(250, 250, 250));
	m_BtnUnlink.SetBkAltColor(RGB(220, 20, 60));
	m_BtnUnlink.SetTextAltColor(RGB(250, 250, 250));
	m_BtnUnlink.Update();
	m_BtnUnlink.EnableWindowsTheming(FALSE);

	// Set Fonts
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

	GetDlgItem(IDC_STATIC_BIZCODE)->SetFont(&m_font, TRUE);
	GetDlgItem(IDC_STATIC_MOACODE)->SetFont(&m_font, TRUE);
	GetDlgItem(IDC_STATIC_LINKDATE)->SetFont(&m_font, TRUE);
	GetDlgItem(IDC_STATIC_TILDE)->SetFont(&m_font, TRUE);
	GetDlgItem(IDC_MFCBUTTON_LOOKUP)->SetFont(&m_font, TRUE);

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

	m_ListLookup.SetFont(&m_font, TRUE);
	m_ComboAgency.SetFont(&m_font, TRUE);

	m_font.Detach();

	// Set List control
	m_ListLookup.DeleteAllItems();

	m_ListLookup.ModifyStyle(0, LVS_SHOWSELALWAYS);
	m_ListLookup.SetExtendedStyle(LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES); //LVS_EX_CHECKBOXES

	// Moacall header
	m_ListLookup.InsertColumn(0, _T("대행사명"), LVCFMT_LEFT, 100, -1);
	m_ListLookup.InsertColumn(1, _T("사업자번호"), LVCFMT_LEFT, 100, -1);
	m_ListLookup.InsertColumn(2, _T("매장명"), LVCFMT_LEFT, 100, -1);
	m_ListLookup.InsertColumn(3, _T("매장코드"), LVCFMT_LEFT, 100, -1);
	m_ListLookup.InsertColumn(4, _T("대표자명"), LVCFMT_LEFT, 100, -1);
	m_ListLookup.InsertColumn(5, _T("연동코드"), LVCFMT_LEFT, 100, -1);
	m_ListLookup.InsertColumn(6, _T("매장 지점명"), LVCFMT_LEFT, 100, -1);
	m_ListLookup.InsertColumn(7, _T("매장 전화"), LVCFMT_LEFT, 100, -1);
	m_ListLookup.InsertColumn(8, _T("매장 휴대전화"), LVCFMT_LEFT, 100, -1);
	m_ListLookup.InsertColumn(9, _T("매장 주소"), LVCFMT_LEFT, 100, -1);
	m_ListLookup.InsertColumn(10, _T("연동일자"), LVCFMT_LEFT, 100, -1);
	m_ListLookup.InsertColumn(11, _T("연동해제일자"), LVCFMT_LEFT, 100, -1);

	m_CheckStart.SetCheck(TRUE);
	m_CheckEnd.SetCheck(TRUE);

	//for (int i = 0; i < m_ListLookup.GetHeaderCtrl()->GetItemCount(); ++i)
	//	m_ListLookup.SetColumnWidth(i, LVSCW_AUTOSIZE_USEHEADER);
	m_ListLookup.AdjustColumnWidth();

	m_ComboAgency.InsertString(0, L"모아콜");
	m_ComboAgency.InsertString(1, L"와따");
	m_ComboAgency.InsertString(2, L"토마토딜리버리");
	m_ComboAgency.InsertString(3, L"달리고");
	m_ComboAgency.InsertString(4, L"슈퍼히어로");
	m_ComboAgency.InsertString(5, L"티앤비");
	m_ComboAgency.InsertString(6, L"로드보이");
	m_ComboAgency.InsertString(7, L"스파이더");
	m_ComboAgency.InsertString(8, L"행복배달");
	m_ComboAgency.InsertString(9, L"이즈오케이");
	m_ComboAgency.InsertString(10, L"비욘드딜리버리");
	m_ComboAgency.InsertString(11, L"최강배달");
	m_ComboAgency.InsertString(12, L"베테랑");
	//m_ComboAgency.InsertString(12, L"로드파일럿");
	m_ComboAgency.InsertString(13, L"배달인");
	m_ComboAgency.InsertString(14, L"레몬콜");
	//m_ComboAgency.InsertString(15, L"키친딜리버리");
	m_ComboAgency.InsertString(15, L"엠터치");
	m_ComboAgency.InsertString(16, L"하나로");
	m_ComboAgency.InsertString(17, L"생각대로");
	m_ComboAgency.InsertString(18, L"젠딜리");
	m_ComboAgency.InsertString(19, L"딜리온");
	m_ComboAgency.InsertString(20, L"배달로나라를구하신");
	m_ComboAgency.InsertString(21, L"전체");
	//m_ComboAgency.InsertString(16, L"전체");
	m_ComboAgency.SetWindowText(L"");

	b_init = TRUE;

	return TRUE;  // 포커스를 컨트롤에 설정하지 않으면 TRUE를 반환합니다.
}


void CLookupDlg::OnMove(int x, int y)
{
	CDialogEx::OnMove(x, y);

	// TODO: 여기에 메시지 처리기 코드를 추가합니다.
	if (b_init) {
		CRect rt;
		GetClientRect(rt);

		GetDlgItem(IDC_COMBO_AGENCY2)->MoveWindow(rt.left + 10, rt.top + 10, 90, 25);
		GetDlgItem(IDC_STATIC_BIZCODE)->MoveWindow(rt.left + 110, rt.top + 10, 60, 25);
		GetDlgItem(IDC_EDIT_BIZCODE)->MoveWindow(rt.left + 190, rt.top + 10, 150, 25);
		GetDlgItem(IDC_STATIC_MOACODE)->MoveWindow(rt.left + 350, rt.top + 10, 60, 25);
		GetDlgItem(IDC_EDIT_MOACODE)->MoveWindow(rt.left + 410, rt.top + 10, 150, 25);
		GetDlgItem(IDC_MFCBUTTON_LOOKUP)->MoveWindow(rt.right - 75, rt.top + 10, 65, 25);

		GetDlgItem(IDC_STATIC_LINKDATE)->MoveWindow(rt.left + 10, rt.top + 45, 60, 25);
		GetDlgItem(IDC_STATIC_TILDE)->MoveWindow(rt.left + 215, rt.top + 45, 10, 25);
		GetDlgItem(IDC_DATETIMEPICKER_START)->MoveWindow(rt.left + 90, rt.top + 45, 100, 25);
		GetDlgItem(IDC_CHECK_START)->MoveWindow(rt.left + 195, rt.top + 45, 15, 25);
		GetDlgItem(IDC_DATETIMEPICKER_END)->MoveWindow(rt.left + 235, rt.top + 45, 100, 25);
		GetDlgItem(IDC_CHECK_END)->MoveWindow(rt.left + 340, rt.top + 45, 15, 25);
		GetDlgItem(IDC_MFCBUTTON_UNLINK)->MoveWindow(rt.right - 75, rt.top + 45, 65, 25);

		GetDlgItem(IDC_LIST_LOOKUP)->MoveWindow(rt.left + 10, rt.top + 80, rt.Width() - 20, rt.Height() - 90);
	}
}


void CLookupDlg::OnBnClickedMfcbuttonLookup()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	int ret = 0;
	CString list_seq_string;
	CString selText;
	CString temp;
	CString error;
	std::map<CString, LookupStore*> m_LookupStore;

	m_ComboAgency.GetWindowText(selText);
	m_ComboAgency.GetWindowText(l_condition.m_AgencyNm);
	m_EditBizCode.GetWindowText(l_condition.m_Bizcode);
	m_EditMoaCode.GetWindowText(l_condition.m_Linkcode);
	if (m_CheckStart.GetCheck()) {
		m_DateTimeStart.GetWindowText(l_condition.m_DateStart);
	}
	else {
		l_condition.m_DateStart = L"";
	}
	if (m_CheckEnd.GetCheck()) {
		m_DateTimeEnd.GetWindowText(l_condition.m_DateEnd);
	}
	else {
		l_condition.m_DateEnd = L"";
	}
	
	ret = CCustomMysql::SelectDeliveryLink(l_condition, &m_LookupStore, &error);

	if (ret) {
		temp.Format(L"Daligo store search fail.[%04d]: %s", ret, error);
		CJSLogger::Logger('e', "%s", CW2A(CT2W(temp), CP_UTF8));
		MessageBox(error, L"확인", MB_OK);
	}
	else {
		if (!selText.Compare(L"모아콜")
			|| !selText.Compare(L"와따")
			|| !selText.Compare(L"토마토딜리버리")) {
			m_ListLookup.DeleteAllItems();
			m_ListLookup.DeleteAllColumns();

			m_ListLookup.InsertColumn(0, _T("대행사명"), LVCFMT_LEFT, 100, -1);
			m_ListLookup.InsertColumn(1, _T("사업자번호"), LVCFMT_LEFT, 100, -1);
			m_ListLookup.InsertColumn(2, _T("매장명"), LVCFMT_LEFT, 100, -1);
			m_ListLookup.InsertColumn(3, _T("매장코드"), LVCFMT_LEFT, 100, -1);
			m_ListLookup.InsertColumn(4, _T("대표자명"), LVCFMT_LEFT, 100, -1);
			m_ListLookup.InsertColumn(5, _T("연동코드"), LVCFMT_LEFT, 100, -1);
			m_ListLookup.InsertColumn(6, _T("매장지점명"), LVCFMT_LEFT, 100, -1);
			m_ListLookup.InsertColumn(7, _T("매장전화"), LVCFMT_LEFT, 100, -1);
			m_ListLookup.InsertColumn(8, _T("매장휴대전화"), LVCFMT_LEFT, 100, -1);
			m_ListLookup.InsertColumn(9, _T("매장주소"), LVCFMT_LEFT, 100, -1);
			m_ListLookup.InsertColumn(10, _T("연동상태"), LVCFMT_LEFT, 100, -1);
			m_ListLookup.InsertColumn(11, _T("연동일자"), LVCFMT_LEFT, 100, -1);
			m_ListLookup.InsertColumn(12, _T("연동해제일자"), LVCFMT_LEFT, 100, -1);

			std::map<CString, LookupStore*>::iterator itr;
			if (!m_LookupStore.empty()) {
				for (auto itr = m_LookupStore.begin(); itr != m_LookupStore.end(); itr++) {
					m_ListLookup.InsertItem(0, list_seq_string);
					m_ListLookup.SetItem(0, 0, LVIF_TEXT, itr->second->agency_name, 0, 0, 0, NULL);
					m_ListLookup.SetItem(0, 1, LVIF_TEXT, itr->second->biz_num, 0, 0, 0, NULL);
					m_ListLookup.SetItem(0, 2, LVIF_TEXT, itr->second->store_name, 0, 0, 0, NULL);
					m_ListLookup.SetItem(0, 3, LVIF_TEXT, itr->second->store_code, 0, 0, 0, NULL);
					m_ListLookup.SetItem(0, 4, LVIF_TEXT, itr->second->owner_name, 0, 0, 0, NULL);
					m_ListLookup.SetItem(0, 5, LVIF_TEXT, itr->second->link_code, 0, 0, 0, NULL);
					m_ListLookup.SetItem(0, 6, LVIF_TEXT, itr->second->branch_name, 0, 0, 0, NULL);
					m_ListLookup.SetItem(0, 7, LVIF_TEXT, itr->second->store_phone, 0, 0, 0, NULL);
					m_ListLookup.SetItem(0, 8, LVIF_TEXT, itr->second->store_mobile, 0, 0, 0, NULL);
					m_ListLookup.SetItem(0, 9, LVIF_TEXT, itr->second->store_addr, 0, 0, 0, NULL);
					m_ListLookup.SetItem(0, 10, LVIF_TEXT, itr->second->link_status, 0, 0, 0, NULL);
					m_ListLookup.SetItem(0, 11, LVIF_TEXT, itr->second->link_time, 0, 0, 0, NULL);
					m_ListLookup.SetItem(0, 12, LVIF_TEXT, itr->second->unlink_time, 0, 0, 0, NULL);
					delete(itr->second);
					m_LookupStore.erase(itr);
				}
			}
		}
		else if (!selText.Compare(L"달리고")
			|| !selText.Compare(L"슈퍼히어로")
			|| !selText.Compare(L"티앤비")
			|| !selText.Compare(L"젠딜리")
			) {
			m_ListLookup.DeleteAllItems();
			m_ListLookup.DeleteAllColumns();

			m_ListLookup.InsertColumn(0, _T("대행사명"), LVCFMT_LEFT, 100, -1);
			m_ListLookup.InsertColumn(1, _T("사업자번호"), LVCFMT_LEFT, 100, -1);
			m_ListLookup.InsertColumn(2, _T("매장명"), LVCFMT_LEFT, 100, -1);
			m_ListLookup.InsertColumn(3, _T("매장번호"), LVCFMT_LEFT, 100, -1);
			m_ListLookup.InsertColumn(4, _T("연동코드"), LVCFMT_LEFT, 100, -1);
			m_ListLookup.InsertColumn(5, _T("매장전화"), LVCFMT_LEFT, 100, -1);
			m_ListLookup.InsertColumn(6, _T("매장주소"), LVCFMT_LEFT, 100, -1);
			m_ListLookup.InsertColumn(7, _T("연동상태"), LVCFMT_LEFT, 100, -1);
			m_ListLookup.InsertColumn(8, _T("연동일자"), LVCFMT_LEFT, 100, -1);
			m_ListLookup.InsertColumn(9, _T("연동해제일자"), LVCFMT_LEFT, 100, -1);

			std::map<CString, LookupStore*>::iterator itr;
			if (!m_LookupStore.empty()) {
				for (auto itr = m_LookupStore.begin(); itr != m_LookupStore.end(); itr++) {
					m_ListLookup.InsertItem(0, list_seq_string);
					m_ListLookup.SetItem(0, 0, LVIF_TEXT, itr->second->agency_name, 0, 0, 0, NULL);
					m_ListLookup.SetItem(0, 1, LVIF_TEXT, itr->second->biz_num, 0, 0, 0, NULL);
					m_ListLookup.SetItem(0, 2, LVIF_TEXT, itr->second->store_name, 0, 0, 0, NULL);
					m_ListLookup.SetItem(0, 3, LVIF_TEXT, itr->second->store_num, 0, 0, 0, NULL);
					m_ListLookup.SetItem(0, 4, LVIF_TEXT, itr->second->link_code, 0, 0, 0, NULL);
					m_ListLookup.SetItem(0, 5, LVIF_TEXT, itr->second->store_phone, 0, 0, 0, NULL);
					m_ListLookup.SetItem(0, 6, LVIF_TEXT, itr->second->store_addr, 0, 0, 0, NULL);
					m_ListLookup.SetItem(0, 7, LVIF_TEXT, itr->second->link_status, 0, 0, 0, NULL);
					m_ListLookup.SetItem(0, 8, LVIF_TEXT, itr->second->link_time, 0, 0, 0, NULL);
					m_ListLookup.SetItem(0, 9, LVIF_TEXT, itr->second->unlink_time, 0, 0, 0, NULL);
					delete(itr->second);
					m_LookupStore.erase(itr);
				}
			}
		}
		else if (!selText.Compare(L"로드보이")) {
			m_ListLookup.DeleteAllItems();
			m_ListLookup.DeleteAllColumns();

			m_ListLookup.InsertColumn(0, _T("대행사명"), LVCFMT_LEFT, 100, -1);
			m_ListLookup.InsertColumn(1, _T("사업자번호"), LVCFMT_LEFT, 100, -1);
			m_ListLookup.InsertColumn(2, _T("매장명"), LVCFMT_LEFT, 100, -1);
			m_ListLookup.InsertColumn(3, _T("매장코드"), LVCFMT_LEFT, 100, -1);
			m_ListLookup.InsertColumn(4, _T("연동코드"), LVCFMT_LEFT, 100, -1);
			m_ListLookup.InsertColumn(5, _T("매장전화"), LVCFMT_LEFT, 100, -1);
			m_ListLookup.InsertColumn(6, _T("매장휴대전화"), LVCFMT_LEFT, 100, -1);
			m_ListLookup.InsertColumn(7, _T("매장주소"), LVCFMT_LEFT, 100, -1);
			m_ListLookup.InsertColumn(8, _T("연동상태"), LVCFMT_LEFT, 100, -1);
			m_ListLookup.InsertColumn(9, _T("연동일자"), LVCFMT_LEFT, 100, -1);
			m_ListLookup.InsertColumn(10, _T("연동해제일자"), LVCFMT_LEFT, 100, -1);

			std::map<CString, LookupStore*>::iterator itr;
			if (!m_LookupStore.empty()) {
				for (auto itr = m_LookupStore.begin(); itr != m_LookupStore.end(); itr++) {
					m_ListLookup.InsertItem(0, list_seq_string);
					m_ListLookup.SetItem(0, 0, LVIF_TEXT, itr->second->agency_name, 0, 0, 0, NULL);
					m_ListLookup.SetItem(0, 1, LVIF_TEXT, itr->second->biz_num, 0, 0, 0, NULL);
					m_ListLookup.SetItem(0, 2, LVIF_TEXT, itr->second->store_name, 0, 0, 0, NULL);
					m_ListLookup.SetItem(0, 3, LVIF_TEXT, itr->second->store_code, 0, 0, 0, NULL);
					m_ListLookup.SetItem(0, 4, LVIF_TEXT, itr->second->link_code, 0, 0, 0, NULL);
					m_ListLookup.SetItem(0, 5, LVIF_TEXT, itr->second->store_phone, 0, 0, 0, NULL);
					m_ListLookup.SetItem(0, 6, LVIF_TEXT, itr->second->store_mobile, 0, 0, 0, NULL);
					m_ListLookup.SetItem(0, 7, LVIF_TEXT, itr->second->store_addr, 0, 0, 0, NULL);
					m_ListLookup.SetItem(0, 8, LVIF_TEXT, itr->second->link_status, 0, 0, 0, NULL);
					m_ListLookup.SetItem(0, 9, LVIF_TEXT, itr->second->link_time, 0, 0, 0, NULL);
					m_ListLookup.SetItem(0, 10, LVIF_TEXT, itr->second->unlink_time, 0, 0, 0, NULL);
					delete(itr->second);
					m_LookupStore.erase(itr);
				}
			}
		}
		else if (!selText.Compare(L"스파이더")
			|| !selText.Compare(L"행복배달")
			|| !selText.Compare(L"배달로나라를구하신")) {
			m_ListLookup.DeleteAllItems();
			m_ListLookup.DeleteAllColumns();

			m_ListLookup.InsertColumn(0, _T("대행사명"), LVCFMT_LEFT, 100, -1);
			m_ListLookup.InsertColumn(1, _T("사업자번호"), LVCFMT_LEFT, 100, -1);
			m_ListLookup.InsertColumn(2, _T("매장명"), LVCFMT_LEFT, 100, -1);
			m_ListLookup.InsertColumn(3, _T("매장코드"), LVCFMT_LEFT, 100, -1);
			m_ListLookup.InsertColumn(4, _T("연동코드"), LVCFMT_LEFT, 100, -1);
			m_ListLookup.InsertColumn(5, _T("매장전화"), LVCFMT_LEFT, 100, -1);
			m_ListLookup.InsertColumn(6, _T("매장휴대전화"), LVCFMT_LEFT, 100, -1);
			m_ListLookup.InsertColumn(7, _T("매장주소"), LVCFMT_LEFT, 100, -1);
			m_ListLookup.InsertColumn(8, _T("연동상태"), LVCFMT_LEFT, 100, -1);
			m_ListLookup.InsertColumn(9, _T("연동일자"), LVCFMT_LEFT, 100, -1);
			m_ListLookup.InsertColumn(10, _T("연동해제일자"), LVCFMT_LEFT, 100, -1);

			std::map<CString, LookupStore*>::iterator itr;
			if (!m_LookupStore.empty()) {
				for (auto itr = m_LookupStore.begin(); itr != m_LookupStore.end(); itr++) {
					m_ListLookup.InsertItem(0, list_seq_string);
					m_ListLookup.SetItem(0, 0, LVIF_TEXT, itr->second->agency_name, 0, 0, 0, NULL);
					m_ListLookup.SetItem(0, 1, LVIF_TEXT, itr->second->biz_num, 0, 0, 0, NULL);
					m_ListLookup.SetItem(0, 2, LVIF_TEXT, itr->second->store_name, 0, 0, 0, NULL);
					m_ListLookup.SetItem(0, 3, LVIF_TEXT, itr->second->store_code, 0, 0, 0, NULL);
					m_ListLookup.SetItem(0, 4, LVIF_TEXT, itr->second->link_code, 0, 0, 0, NULL);
					m_ListLookup.SetItem(0, 5, LVIF_TEXT, itr->second->store_phone, 0, 0, 0, NULL);
					m_ListLookup.SetItem(0, 6, LVIF_TEXT, itr->second->store_mobile, 0, 0, 0, NULL);
					m_ListLookup.SetItem(0, 7, LVIF_TEXT, itr->second->store_addr, 0, 0, 0, NULL);
					m_ListLookup.SetItem(0, 8, LVIF_TEXT, itr->second->link_status, 0, 0, 0, NULL);
					m_ListLookup.SetItem(0, 9, LVIF_TEXT, itr->second->link_time, 0, 0, 0, NULL);
					m_ListLookup.SetItem(0, 10, LVIF_TEXT, itr->second->unlink_time, 0, 0, 0, NULL);
					delete(itr->second);
					m_LookupStore.erase(itr);
				}
			}
		}
		else if (!selText.Compare(L"이즈오케이")	 // 이즈오케이->비욘드딜리버리
			|| !selText.Compare(L"비욘드딜리버리")	 // 이즈오케이->비욘드딜리버리
			|| !selText.Compare(L"최강배달")
			|| !selText.Compare(L"베테랑")
			//|| !selText.Compare(L"로드파일럿")
			|| !selText.Compare(L"배달인")
			|| !selText.Compare(L"레몬콜")
			//|| !selText.Compare(L"키친딜리버리")
			|| !selText.Compare(L"엠터치")
			|| !selText.Compare(L"하나로")) {
			m_ListLookup.DeleteAllItems();
			m_ListLookup.DeleteAllColumns();

			m_ListLookup.InsertColumn(0, _T("대행사명"), LVCFMT_LEFT, 100, -1);
			m_ListLookup.InsertColumn(1, _T("사업자번호"), LVCFMT_LEFT, 100, -1);
			m_ListLookup.InsertColumn(2, _T("매장명"), LVCFMT_LEFT, 100, -1);
			m_ListLookup.InsertColumn(3, _T("매장코드"), LVCFMT_LEFT, 100, -1);
			m_ListLookup.InsertColumn(4, _T("연동코드"), LVCFMT_LEFT, 100, -1);
			m_ListLookup.InsertColumn(5, _T("매장전화"), LVCFMT_LEFT, 100, -1);
			m_ListLookup.InsertColumn(6, _T("매장휴대전화"), LVCFMT_LEFT, 100, -1);
			m_ListLookup.InsertColumn(7, _T("매장주소"), LVCFMT_LEFT, 100, -1);
			m_ListLookup.InsertColumn(8, _T("연동상태"), LVCFMT_LEFT, 100, -1);
			m_ListLookup.InsertColumn(9, _T("연동일자"), LVCFMT_LEFT, 100, -1);
			m_ListLookup.InsertColumn(10, _T("연동해제일자"), LVCFMT_LEFT, 100, -1);

			std::map<CString, LookupStore*>::iterator itr;
			if (!m_LookupStore.empty()) {
				for (auto itr = m_LookupStore.begin(); itr != m_LookupStore.end(); itr++) {
					m_ListLookup.InsertItem(0, list_seq_string);
					m_ListLookup.SetItem(0, 0, LVIF_TEXT, itr->second->agency_name, 0, 0, 0, NULL);
					m_ListLookup.SetItem(0, 1, LVIF_TEXT, itr->second->biz_num, 0, 0, 0, NULL);
					m_ListLookup.SetItem(0, 2, LVIF_TEXT, itr->second->store_name, 0, 0, 0, NULL);
					m_ListLookup.SetItem(0, 3, LVIF_TEXT, itr->second->store_code, 0, 0, 0, NULL);
					m_ListLookup.SetItem(0, 4, LVIF_TEXT, itr->second->link_code, 0, 0, 0, NULL);
					m_ListLookup.SetItem(0, 5, LVIF_TEXT, itr->second->store_phone, 0, 0, 0, NULL);
					m_ListLookup.SetItem(0, 6, LVIF_TEXT, itr->second->store_mobile, 0, 0, 0, NULL);
					m_ListLookup.SetItem(0, 7, LVIF_TEXT, itr->second->store_addr, 0, 0, 0, NULL);
					m_ListLookup.SetItem(0, 8, LVIF_TEXT, itr->second->link_status, 0, 0, 0, NULL);
					m_ListLookup.SetItem(0, 9, LVIF_TEXT, itr->second->link_time, 0, 0, 0, NULL);
					m_ListLookup.SetItem(0, 10, LVIF_TEXT, itr->second->unlink_time, 0, 0, 0, NULL);
					delete(itr->second);
					m_LookupStore.erase(itr);
				}
			}
		}
		else if (!selText.Compare(L"생각대로")) {
			m_ListLookup.DeleteAllItems();
			m_ListLookup.DeleteAllColumns();

			m_ListLookup.InsertColumn(0, _T("대행사명"), LVCFMT_LEFT, 100, -1);
			m_ListLookup.InsertColumn(1, _T("사업자번호"), LVCFMT_LEFT, 100, -1);
			m_ListLookup.InsertColumn(2, _T("매장명"), LVCFMT_LEFT, 100, -1);
			m_ListLookup.InsertColumn(3, _T("매장코드"), LVCFMT_LEFT, 100, -1);
			m_ListLookup.InsertColumn(4, _T("연동코드"), LVCFMT_LEFT, 100, -1);
			m_ListLookup.InsertColumn(5, _T("매장지점명"), LVCFMT_LEFT, 100, -1);
			m_ListLookup.InsertColumn(6, _T("매장전화"), LVCFMT_LEFT, 100, -1);
			m_ListLookup.InsertColumn(7, _T("매장휴대전화"), LVCFMT_LEFT, 100, -1);
			m_ListLookup.InsertColumn(8, _T("매장주소"), LVCFMT_LEFT, 100, -1);
			m_ListLookup.InsertColumn(9, _T("연동상태"), LVCFMT_LEFT, 100, -1);
			m_ListLookup.InsertColumn(10, _T("연동일자"), LVCFMT_LEFT, 100, -1);
			m_ListLookup.InsertColumn(11, _T("연동해제일자"), LVCFMT_LEFT, 100, -1);

			std::map<CString, LookupStore*>::iterator itr;
			if (!m_LookupStore.empty()) {
				for (auto itr = m_LookupStore.begin(); itr != m_LookupStore.end(); itr++) {
					m_ListLookup.InsertItem(0, list_seq_string);
					m_ListLookup.SetItem(0, 0, LVIF_TEXT, itr->second->agency_name, 0, 0, 0, NULL);
					m_ListLookup.SetItem(0, 1, LVIF_TEXT, itr->second->biz_num, 0, 0, 0, NULL);
					m_ListLookup.SetItem(0, 2, LVIF_TEXT, itr->second->store_name, 0, 0, 0, NULL);
					m_ListLookup.SetItem(0, 3, LVIF_TEXT, itr->second->store_code, 0, 0, 0, NULL);
					m_ListLookup.SetItem(0, 4, LVIF_TEXT, itr->second->link_code, 0, 0, 0, NULL);
					m_ListLookup.SetItem(0, 5, LVIF_TEXT, itr->second->branch_name, 0, 0, 0, NULL);
					m_ListLookup.SetItem(0, 6, LVIF_TEXT, itr->second->store_phone, 0, 0, 0, NULL);
					m_ListLookup.SetItem(0, 7, LVIF_TEXT, itr->second->store_mobile, 0, 0, 0, NULL);
					m_ListLookup.SetItem(0, 8, LVIF_TEXT, itr->second->store_addr, 0, 0, 0, NULL);
					m_ListLookup.SetItem(0, 9, LVIF_TEXT, itr->second->link_status, 0, 0, 0, NULL);
					m_ListLookup.SetItem(0, 10, LVIF_TEXT, itr->second->link_time, 0, 0, 0, NULL);
					m_ListLookup.SetItem(0, 11, LVIF_TEXT, itr->second->unlink_time, 0, 0, 0, NULL);
					delete(itr->second);
					m_LookupStore.erase(itr);
				}
			}
		}
		else if (!selText.Compare(L"딜리온")) {
			m_ListLookup.DeleteAllItems();
			m_ListLookup.DeleteAllColumns();

			m_ListLookup.InsertColumn(0, _T("대행사명"), LVCFMT_LEFT, 100, -1);
			m_ListLookup.InsertColumn(1, _T("사업자번호"), LVCFMT_LEFT, 100, -1);
			m_ListLookup.InsertColumn(2, _T("매장명"), LVCFMT_LEFT, 100, -1);
			m_ListLookup.InsertColumn(3, _T("매장코드"), LVCFMT_LEFT, 100, -1);
			m_ListLookup.InsertColumn(4, _T("연동코드"), LVCFMT_LEFT, 100, -1);
			m_ListLookup.InsertColumn(5, _T("매장전화"), LVCFMT_LEFT, 100, -1);
			m_ListLookup.InsertColumn(6, _T("매장휴대전화"), LVCFMT_LEFT, 100, -1);
			m_ListLookup.InsertColumn(7, _T("매장주소"), LVCFMT_LEFT, 100, -1);
			m_ListLookup.InsertColumn(8, _T("연동상태"), LVCFMT_LEFT, 100, -1);
			m_ListLookup.InsertColumn(9, _T("연동일자"), LVCFMT_LEFT, 100, -1);
			m_ListLookup.InsertColumn(10, _T("연동해제일자"), LVCFMT_LEFT, 100, -1);

			std::map<CString, LookupStore*>::iterator itr;
			if (!m_LookupStore.empty()) {
				for (auto itr = m_LookupStore.begin(); itr != m_LookupStore.end(); itr++) {
					m_ListLookup.InsertItem(0, list_seq_string);
					m_ListLookup.SetItem(0, 0, LVIF_TEXT, itr->second->agency_name, 0, 0, 0, NULL);
					m_ListLookup.SetItem(0, 1, LVIF_TEXT, itr->second->biz_num, 0, 0, 0, NULL);
					m_ListLookup.SetItem(0, 2, LVIF_TEXT, itr->second->store_name, 0, 0, 0, NULL);
					m_ListLookup.SetItem(0, 3, LVIF_TEXT, itr->second->store_code, 0, 0, 0, NULL);
					m_ListLookup.SetItem(0, 4, LVIF_TEXT, itr->second->link_code, 0, 0, 0, NULL);
					m_ListLookup.SetItem(0, 5, LVIF_TEXT, itr->second->store_phone, 0, 0, 0, NULL);
					m_ListLookup.SetItem(0, 6, LVIF_TEXT, itr->second->store_mobile, 0, 0, 0, NULL);
					m_ListLookup.SetItem(0, 7, LVIF_TEXT, itr->second->store_addr, 0, 0, 0, NULL);
					m_ListLookup.SetItem(0, 8, LVIF_TEXT, itr->second->link_status, 0, 0, 0, NULL);
					m_ListLookup.SetItem(0, 9, LVIF_TEXT, itr->second->link_time, 0, 0, 0, NULL);
					m_ListLookup.SetItem(0, 10, LVIF_TEXT, itr->second->unlink_time, 0, 0, 0, NULL);
					delete(itr->second);
					m_LookupStore.erase(itr);
				}
			}
		}
		else if (!selText.Compare(L"전체")) {
			m_ListLookup.DeleteAllItems();
			m_ListLookup.DeleteAllColumns();

			m_ListLookup.InsertColumn(0, _T("대행사명"), LVCFMT_LEFT, 100, -1);
			m_ListLookup.InsertColumn(1, _T("사업자번호"), LVCFMT_LEFT, 100, -1);
			m_ListLookup.InsertColumn(2, _T("매장명"), LVCFMT_LEFT, 100, -1);
			m_ListLookup.InsertColumn(3, _T("매장번호"), LVCFMT_LEFT, 100, -1);
			m_ListLookup.InsertColumn(4, _T("매장코드"), LVCFMT_LEFT, 100, -1);
			m_ListLookup.InsertColumn(5, _T("대표자명"), LVCFMT_LEFT, 100, -1);
			m_ListLookup.InsertColumn(6, _T("연동코드"), LVCFMT_LEFT, 100, -1);
			m_ListLookup.InsertColumn(7, _T("매장지점명"), LVCFMT_LEFT, 100, -1);
			m_ListLookup.InsertColumn(8, _T("매장전화"), LVCFMT_LEFT, 100, -1);
			m_ListLookup.InsertColumn(9, _T("매장휴대전화"), LVCFMT_LEFT, 100, -1);
			m_ListLookup.InsertColumn(10, _T("매장주소"), LVCFMT_LEFT, 100, -1);
			m_ListLookup.InsertColumn(11, _T("연동상태"), LVCFMT_LEFT, 100, -1);
			m_ListLookup.InsertColumn(12, _T("연동일자"), LVCFMT_LEFT, 100, -1);
			m_ListLookup.InsertColumn(13, _T("연동해제일자"), LVCFMT_LEFT, 100, -1);
			
			std::map<CString, LookupStore*>::iterator itr;
			if (!m_LookupStore.empty()) {
				for (auto itr = m_LookupStore.begin(); itr != m_LookupStore.end(); itr++) {
					m_ListLookup.InsertItem(0, list_seq_string);
					m_ListLookup.SetItem(0, 0, LVIF_TEXT, itr->second->agency_name, 0, 0, 0, NULL);
					m_ListLookup.SetItem(0, 1, LVIF_TEXT, itr->second->biz_num, 0, 0, 0, NULL);
					m_ListLookup.SetItem(0, 2, LVIF_TEXT, itr->second->store_name, 0, 0, 0, NULL);
					m_ListLookup.SetItem(0, 3, LVIF_TEXT, itr->second->store_num, 0, 0, 0, NULL);
					m_ListLookup.SetItem(0, 4, LVIF_TEXT, itr->second->store_code, 0, 0, 0, NULL);
					m_ListLookup.SetItem(0, 5, LVIF_TEXT, itr->second->owner_name, 0, 0, 0, NULL);
					m_ListLookup.SetItem(0, 6, LVIF_TEXT, itr->second->link_code, 0, 0, 0, NULL);
					m_ListLookup.SetItem(0, 7, LVIF_TEXT, itr->second->branch_name, 0, 0, 0, NULL);
					m_ListLookup.SetItem(0, 8, LVIF_TEXT, itr->second->store_phone, 0, 0, 0, NULL);
					m_ListLookup.SetItem(0, 9, LVIF_TEXT, itr->second->store_mobile, 0, 0, 0, NULL);
					m_ListLookup.SetItem(0, 10, LVIF_TEXT, itr->second->store_addr, 0, 0, 0, NULL);
					m_ListLookup.SetItem(0, 11, LVIF_TEXT, itr->second->link_status, 0, 0, 0, NULL);
					m_ListLookup.SetItem(0, 12, LVIF_TEXT, itr->second->link_time, 0, 0, 0, NULL);
					m_ListLookup.SetItem(0, 13, LVIF_TEXT, itr->second->unlink_time, 0, 0, 0, NULL);
					delete(itr->second);
					m_LookupStore.erase(itr);
				}
			}
		}

		m_ListLookup.AdjustColumnWidth();
	}
	
	

	
}


//void CLookupDlg::OnHdnItemclickListLookup(NMHDR *pNMHDR, LRESULT *pResult)
//{
//	LPNMHEADER phdr = reinterpret_cast<LPNMHEADER>(pNMHDR);
//	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
//	
//
//	*pResult = 0;
//}

BOOL CLookupDlg::PreTranslateMessage(MSG* pMsg)
{
	// TODO: 여기에 특수화된 코드를 추가 및/또는 기본 클래스를 호출합니다.
	switch (pMsg->message) {
	case WM_KEYDOWN:	// 키가 눌렸을때
		switch (pMsg->wParam) {
		case VK_RETURN:	// 리턴키\tab 
			if (GetFocus() == GetDlgItem(IDC_EDIT_BIZCODE)
				|| GetFocus() == GetDlgItem(IDC_EDIT_LINKCODE)
				|| GetFocus() == GetDlgItem(IDC_DATETIMEPICKER_START)
				|| GetFocus() == GetDlgItem(IDC_DATETIMEPICKER_END)
				|| GetFocus() == GetDlgItem(IDC_COMBO_AGENCY2))
				::SendMessage(GetSafeHwnd(), WM_COMMAND, MAKEWPARAM(IDC_MFCBUTTON_LOOKUP, BN_CLICKED), 0);
			else if (GetFocus() == GetDlgItem(IDC_MFCBUTTON_LOOKUP))
				::SendMessage(GetSafeHwnd(), WM_COMMAND, MAKEWPARAM(IDC_MFCBUTTON_LOOKUP, BN_CLICKED), 0);
			return TRUE;
		case VK_ESCAPE:	// ESC키
			return TRUE;
		case 'C':
			if (GetKeyState(VK_CONTROL)<0)
			{
				int nID = GetFocus()->GetDlgCtrlID();
				if (nID == IDC_LIST_LOOKUP) {
					if (GetKeyState(VK_SHIFT) < 0) {
						if (pMsg->hwnd == m_ListLookup.GetSafeHwnd() &&
							GetFocus()->GetSafeHwnd() == m_ListLookup.GetSafeHwnd())
						{
							CopyAllRowListToClipboard(TRUE, &m_ListLookup, _T("\t"));
						}
					}
					else {
						if (pMsg->hwnd == m_ListLookup.GetSafeHwnd() &&
							GetFocus()->GetSafeHwnd() == m_ListLookup.GetSafeHwnd())
						{
							CopyListCellToClipboard(&m_ListLookup, _T("\t"));
						}
					}
					return true;
				}
			}
		}
	}
	return CDialogEx::PreTranslateMessage(pMsg);
}



void CLookupDlg::OnLvnColumnclickListLookup(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMLISTVIEW pNMLV = reinterpret_cast<LPNMLISTVIEW>(pNMHDR);
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	int column = pNMLV->iSubItem;

	if (column == m_SortedColumn) {
		m_Ascending = !m_Ascending;
	}
	else {
		m_Ascending = TRUE;
	}

	m_SortedColumn = column;

	int cnt = m_ListLookup.GetItemCount();
	CString* str = new CString[cnt];
	for (int i = 0; i<cnt; i++) {
		str[i] = m_ListLookup.GetItemText(i, column);
		m_ListLookup.SetItemData(i, (DWORD)(LPCTSTR)str[i]);
	}

	m_ListLookup.SortItems(CompareFunc, (LPARAM)m_Ascending);

	delete[]str;

	*pResult = 0;
}

int CALLBACK CLookupDlg::CompareFunc(LPARAM lParam1, LPARAM lParam2, LPARAM lParam)
{
	BOOL Ascending = (BOOL)lParam;

	LPCTSTR s1 = (LPCTSTR)(DWORD)lParam1;
	LPCTSTR s2 = (LPCTSTR)(DWORD)lParam2;

	if (Ascending)
		return _tcscmp(s1, s2);
	else
		return -(_tcscmp(s1, s2));

	return 0;
}

void CLookupDlg::OnBnClickedMfcbuttonUnlink()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CHttpsRequest hReq;
	LookupStore lookupStore;
	CString list_seq_string;
	CString temp;
	CString error;
	CString selText;
	int ret = 0;
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	int count = m_ListLookup.GetItemCount();
	int index = -1;

	for (int i = 0; i < count; i++) {
		if (LVIS_SELECTED == m_ListLookup.GetItemState(i, LVIS_SELECTED))
		{
			index = i;
			break;
		}
	}

	if (index == -1) {
		MessageBox(L"대행사를 선택해주세요.", L"경고", MB_ICONWARNING);
	}
	else {
		m_ComboAgency.GetWindowText(selText);
		//selText = m_ListLookup.GetItemText(index, 0);
		if (!m_ListLookup.GetItemText(index, 0).Compare(L"모아콜")
			|| !m_ListLookup.GetItemText(index, 0).Compare(L"와따")
			|| !m_ListLookup.GetItemText(index, 0).Compare(L"토마토딜리버리")) {
			CJSLogger::Logger('i', "Moacall store unlink.");

			lookupStore.agency_name = m_ListLookup.GetItemText(index, 0);
			if (!selText.Compare(L"모아콜")
				|| !selText.Compare(L"와따")
				|| !selText.Compare(L"토마토딜리버리"))
				lookupStore.link_code = m_ListLookup.GetItemText(index, 5);
			else
				lookupStore.link_code = m_ListLookup.GetItemText(index, 6);


			temp.Format(L"해당 매장을 연동해제 하시겠습니까?\n%s 연동코드 : %s", selText, lookupStore.link_code);
			if (MessageBox(temp, L"연동", MB_YESNO) != IDYES) 
				return;

			ret = CCustomMysql::UpdateDeliveryLink(lookupStore, &error);

			if (ret) {
				temp.Format(L"Moacall store unlink update fail.[%04d]: %s. linkcode : %s", ret, error, lookupStore.link_code);
				CJSLogger::Logger('e', "%s", CW2A(CT2W(temp), CP_UTF8));
				MessageBox(error, L"확인", MB_OK);
			}
			else {
				if (!selText.Compare(L"모아콜")
					|| !selText.Compare(L"와따")
					|| !selText.Compare(L"토마토딜리버리"))
					m_ListLookup.SetItemText(index, 10, L"U");
				else
					m_ListLookup.SetItemText(index, 11, L"U");

				CJSLogger::Logger('i', "Moacall store unlink success. : %s", CW2A(CT2W(lookupStore.link_code), CP_UTF8));
				temp.Format(L"%s 연동해제 업데이트가 완료되었습니다. 모아콜에 연동해제를 알려주세요.\n연동코드 : %s", selText, lookupStore.link_code);
				MessageBox(temp, L"확인", MB_OK);
			}
			
		}
		else if (!m_ListLookup.GetItemText(index, 0).Compare(L"달리고")
			|| !m_ListLookup.GetItemText(index, 0).Compare(L"슈퍼히어로")
			|| !m_ListLookup.GetItemText(index, 0).Compare(L"티앤비")
			|| !m_ListLookup.GetItemText(index, 0).Compare(L"젠딜리")
			) {
			DaligoResultData d_rdata;
			CJSLogger::Logger('i', "Daligo store unlink.");

			lookupStore.agency_name = m_ListLookup.GetItemText(index, 0);
			lookupStore.biz_num = m_ListLookup.GetItemText(index, 1);
			if (!selText.Compare(L"달리고")
				|| !selText.Compare(L"슈퍼히어로")
				|| !selText.Compare(L"티앤비")
				|| !selText.Compare(L"젠딜리")
				) {
				lookupStore.link_code = m_ListLookup.GetItemText(index, 4);
			}
			else {
				lookupStore.link_code = m_ListLookup.GetItemText(index, 6);
			}

			temp.Format(L"해당 매장을 연동해제 하시겠습니까?\n%s 연동코드 : %s", selText, lookupStore.link_code);
			if (MessageBox(temp, L"연동", MB_YESNO) != IDYES) 
				return;

			CString flagTemp = m_ListLookup.GetItemText(index, 0);
			if (!flagTemp.Compare(L"달리고"))
				daligoLink.SetAgencyFlag(1);
			else if (!flagTemp.Compare(L"슈퍼히어로"))
				daligoLink.SetAgencyFlag(2);
			else if (!flagTemp.Compare(L"티앤비"))
				daligoLink.SetAgencyFlag(3);
			if (!flagTemp.Compare(L"젠딜리"))
				daligoLink.SetAgencyFlag(4);
			ret = daligoLink.StoreUnlink(lookupStore.biz_num, lookupStore.link_code, &d_rdata);

			if (ret) {
				temp.Empty();
				temp.Format(L"Daligo Unlink fail.[%04d]: %s. Link_code : %s", ret, d_rdata.ret_msg, lookupStore.link_code);
				CJSLogger::Logger('e', "%s", CW2A(CT2W(temp), CP_UTF8));
				MessageBox(d_rdata.ret_msg, L"경고", MB_ICONWARNING);
			}
			else {
				ret = CCustomMysql::UpdateDeliveryLink(lookupStore, &error);

				if (ret) {
					temp.Format(L"Daligo store unlink update fail.[%04d]: %s. linkcode : %s", ret, error, lookupStore.link_code);
					CJSLogger::Logger('e', "%s", CW2A(CT2W(temp), CP_UTF8));
					MessageBox(error, L"확인", MB_OK);
				}
				else {
					if (!selText.Compare(L"달리고")
						|| !selText.Compare(L"슈퍼히어로")
						|| !selText.Compare(L"티앤비")
						|| !selText.Compare(L"젠딜리")
						)
						m_ListLookup.SetItemText(index, 7, L"U");
					else
						m_ListLookup.SetItemText(index, 11, L"U");

					CJSLogger::Logger('i', "Daligo store unlink success. : %s", CW2A(CT2W(lookupStore.link_code), CP_UTF8));
					temp.Format(L"연동해제 되었습니다.\n연동코드 : %s", lookupStore.link_code);
					MessageBox(temp, L"확인", MB_OK);
				}
			}
		}
		else if (!m_ListLookup.GetItemText(index, 0).Compare(L"로드보이")) {
			RoadvoyResultData r_rdata;
			CJSLogger::Logger('i', "Roadvoy store unlink.");

			lookupStore.agency_name = m_ListLookup.GetItemText(index, 0);
			lookupStore.biz_num = m_ListLookup.GetItemText(index, 1);
			if (!selText.Compare(L"로드보이")) {
				lookupStore.link_code = m_ListLookup.GetItemText(index, 4);
			}
			else {
				lookupStore.link_code = m_ListLookup.GetItemText(index, 6);
			}

			temp.Format(L"해당 매장을 연동해제 하시겠습니까?\n%s 연동코드 : %s", selText, lookupStore.link_code);
			if (MessageBox(temp, L"연동", MB_YESNO) != IDYES)
				return;

			ret = roadvoyLink.StoreUnlink(lookupStore.link_code, &r_rdata);

			if (ret) {
				temp.Empty();
				temp.Format(L"Roadvoy Unlink fail.[%04d]: %s. Link_code : %s", ret, r_rdata.ret_msg, lookupStore.link_code);
				CJSLogger::Logger('e', "%s", CW2A(CT2W(temp), CP_UTF8));
				MessageBox(r_rdata.ret_msg, L"경고", MB_ICONWARNING);
			}
			else {
				ret = CCustomMysql::UpdateDeliveryLink(lookupStore, &error);

				if (ret) {
					temp.Format(L"Roadvoy store unlink update fail.[%04d]: %s. linkcode : %s", ret, error, lookupStore.link_code);
					CJSLogger::Logger('e', "%s", CW2A(CT2W(temp), CP_UTF8));
					MessageBox(error, L"확인", MB_OK);
				}
				else {
					if (!selText.Compare(L"로드보이"))
						m_ListLookup.SetItemText(index, 8, L"U");
					else
						m_ListLookup.SetItemText(index, 11, L"U");

					CJSLogger::Logger('i', "Roadvoy store unlink success. : %s", CW2A(CT2W(lookupStore.link_code), CP_UTF8));
					temp.Format(L"연동해제 되었습니다.\n연동코드 : %s", lookupStore.link_code);
					MessageBox(temp, L"확인", MB_OK);
				}
			}
		}
		else if (!m_ListLookup.GetItemText(index, 0).Compare(L"스파이더")
			|| !m_ListLookup.GetItemText(index, 0).Compare(L"행복배달")
			|| !m_ListLookup.GetItemText(index, 0).Compare(L"배달로나라를구하신")
			) {
			CombineNetResultData cn_rdata;
			CJSLogger::Logger('i', "CombineNet store unlink.");

			lookupStore.agency_name = m_ListLookup.GetItemText(index, 0);
			lookupStore.store_code = m_ListLookup.GetItemText(index, 3);

			if (!selText.Compare(L"스파이더")
				|| !selText.Compare(L"행복배달")
				|| !selText.Compare(L"배달로나라를구하신")) {
				lookupStore.link_code = m_ListLookup.GetItemText(index, 4);
			}
			else {
				lookupStore.link_code = m_ListLookup.GetItemText(index, 6);
			}

			temp.Format(L"해당 매장을 연동해제 하시겠습니까?\n%s 연동코드 : %s", selText, lookupStore.link_code);
			if (MessageBox(temp, L"연동", MB_YESNO) != IDYES)
				return;

			if (!selText.Compare(L"행복배달"))	 // 이즈오케이->비욘드딜리버리
				combinetLink.SetAgencyFlag(cbn_hangbok);
			else if (!selText.Compare(L"스파이더"))
				combinetLink.SetAgencyFlag(cbn_spider);
			else if (!selText.Compare(L"배달로나라를구하신"))
				combinetLink.SetAgencyFlag(cbn_baena9);

			ret = combinetLink.StoreUnlink(lookupStore.store_code, lookupStore.link_code, &cn_rdata);

			if (ret || _ttoi(cn_rdata.ret_cd)) {
				temp.Empty();
				temp.Format(L"Roadvoy Unlink fail.[%04d]: %s. Link_code : %s", ret, cn_rdata.ret_msg, lookupStore.link_code);
				CJSLogger::Logger('e', "%s", CW2A(CT2W(temp), CP_UTF8));
				MessageBox(cn_rdata.ret_msg, L"경고", MB_ICONWARNING);
			}
			else {
				ret = CCustomMysql::UpdateDeliveryLink(lookupStore, &error);

				if (ret) {
					temp.Format(L"Roadvoy store unlink update fail.[%04d]: %s. linkcode : %s", ret, error, lookupStore.link_code);
					CJSLogger::Logger('e', "%s", CW2A(CT2W(temp), CP_UTF8));
					MessageBox(error, L"확인", MB_OK);
				}
				else {
					if (!selText.Compare(L"스파이더")
						|| !selText.Compare(L"행복배달")
						|| !selText.Compare(L"배달로나라를구하신"))
						m_ListLookup.SetItemText(index, 8, L"U");
					else
						m_ListLookup.SetItemText(index, 11, L"U");

					CJSLogger::Logger('i', "Roadvoy store unlink success. : %s", CW2A(CT2W(lookupStore.link_code), CP_UTF8));
					temp.Format(L"연동해제 되었습니다.\n연동코드 : %s", lookupStore.link_code);
					MessageBox(temp, L"확인", MB_OK);
				}
			}
		}
		else if (!m_ListLookup.GetItemText(index, 0).Compare(L"이즈오케이")
			|| !m_ListLookup.GetItemText(index, 0).Compare(L"비욘드딜리버리")
			|| !m_ListLookup.GetItemText(index, 0).Compare(L"최강배달")
			|| !m_ListLookup.GetItemText(index, 0).Compare(L"베테랑")
			//|| !m_ListLookup.GetItemText(index, 0).Compare(L"로드파일럿")
			|| !m_ListLookup.GetItemText(index, 0).Compare(L"배달인")
			|| !m_ListLookup.GetItemText(index, 0).Compare(L"레몬콜")
			//|| !m_ListLookup.GetItemText(index, 0).Compare(L"키친딜리버리")
			|| !m_ListLookup.GetItemText(index, 0).Compare(L"엠터치")
			|| !m_ListLookup.GetItemText(index, 0).Compare(L"하나로")
			) {
			BeyondResultData by_rdata;
			CJSLogger::Logger('i', "Beyond store unlink.");

			lookupStore.agency_name = m_ListLookup.GetItemText(index, 0);
			lookupStore.store_code = m_ListLookup.GetItemText(index, 3);
			if (!selText.Compare(L"이즈오케이")	 // 이즈오케이->비욘드딜리버리
				|| !selText.Compare(L"비욘드딜리버리")	 // 이즈오케이->비욘드딜리버리
				|| !selText.Compare(L"최강배달")
				|| !selText.Compare(L"베테랑")
				//|| !selText.Compare(L"로드파일럿")
				|| !selText.Compare(L"배달인")
				|| !selText.Compare(L"레몬콜")
				//|| !selText.Compare(L"키친딜리버리")
				|| !selText.Compare(L"엠터치")
				|| !selText.Compare(L"하나로")
				) {
				lookupStore.link_code = m_ListLookup.GetItemText(index, 4);
			}
			else {
				lookupStore.link_code = m_ListLookup.GetItemText(index, 6);
			}

			temp.Format(L"해당 매장을 연동해제 하시겠습니까?\n%s 연동코드 : %s", selText, lookupStore.link_code);
			if (MessageBox(temp, L"연동", MB_YESNO) != IDYES)
				return;

			CString flagTemp = m_ListLookup.GetItemText(index, 0);
			if (!selText.Compare(L"비욘드딜리버리") || !selText.Compare(L"이즈오케이"))	 // 이즈오케이->비욘드딜리버리
				beyondLink.SetServFlag(by_byservice);
			else if (!flagTemp.Compare(L"최강배달"))
				beyondLink.SetServFlag(by_rushcall);
			else if (!flagTemp.Compare(L"베테랑"))
				beyondLink.SetServFlag(by_veteran);
			else if (!flagTemp.Compare(L"로드파일럿"))
				beyondLink.SetServFlag(by_roadpilot);
			else if (!flagTemp.Compare(L"배달인"))
				beyondLink.SetServFlag(by_dsp);
			else if (!flagTemp.Compare(L"레몬콜"))
				beyondLink.SetServFlag(by_fooding);
			else if (!flagTemp.Compare(L"키친딜리버리"))
				beyondLink.SetServFlag(by_kitchen);
			else if (!flagTemp.Compare(L"엠터치"))
				beyondLink.SetServFlag(by_mtouch);
			else if (!flagTemp.Compare(L"하나로"))
				beyondLink.SetServFlag(by_hanaro);


			ret = beyondLink.StoreLink(lookupStore.store_code, lookupStore.link_code, FALSE, &by_rdata);
			
			if (ret || _ttoi(by_rdata.result_code)) {
				temp.Empty();
				temp.Format(L"Beyond Unlink fail.[%04d]: %s. Link_code : %s", ret, by_rdata.result_message, lookupStore.link_code);
				CJSLogger::Logger('e', "%s", CW2A(CT2W(temp), CP_UTF8));
				MessageBox(by_rdata.result_message, L"경고", MB_ICONWARNING);
			}
			else {
				ret = CCustomMysql::UpdateDeliveryLink(lookupStore, &error);

				if (ret) {
					temp.Format(L"Beyond store unlink update fail.[%04d]: %s. linkcode : %s", ret, error, lookupStore.link_code);
					CJSLogger::Logger('e', "%s", CW2A(CT2W(temp), CP_UTF8));
					MessageBox(error, L"확인", MB_OK);
				}
				else {
					if (!selText.Compare(L"이즈오케이")	 // 이즈오케이->비욘드딜리버리
						|| !selText.Compare(L"비욘드딜리버리")	 // 이즈오케이->비욘드딜리버리
						|| !selText.Compare(L"최강배달")
						|| !selText.Compare(L"베테랑")
						//|| !selText.Compare(L"로드파일럿")
						|| !selText.Compare(L"배달인")
						|| !selText.Compare(L"레몬콜")
						//|| !selText.Compare(L"키친딜리버리") 
						|| !selText.Compare(L"엠터치")
						|| !selText.Compare(L"하나로")
						)
						m_ListLookup.SetItemText(index, 8, L"U");
					else
						m_ListLookup.SetItemText(index, 11, L"U");

					CJSLogger::Logger('i', "Beyond store unlink success. : %s", CW2A(CT2W(lookupStore.link_code), CP_UTF8));
					temp.Format(L"연동해제 되었습니다.\n연동코드 : %s", lookupStore.link_code);
					MessageBox(temp, L"확인", MB_OK);
				}
			}
		}else if (!m_ListLookup.GetItemText(index, 0).Compare(L"생각대로")) {
			CJSLogger::Logger('i', "Sanggag store unlink.");

			lookupStore.agency_name = m_ListLookup.GetItemText(index, 0);
			if (!selText.Compare(L"생각대로"))
				lookupStore.link_code = m_ListLookup.GetItemText(index, 4);
			else
				lookupStore.link_code = m_ListLookup.GetItemText(index, 6);


			temp.Format(L"해당 매장을 연동해제 하시겠습니까?\n%s 연동코드 : %s", selText, lookupStore.link_code);
			if (MessageBox(temp, L"연동", MB_YESNO) != IDYES)
				return;

			ret = CCustomMysql::UpdateDeliveryLink(lookupStore, &error);

			if (ret) {
				temp.Format(L"Moacall store unlink update fail.[%04d]: %s. linkcode : %s", ret, error, lookupStore.link_code);
				CJSLogger::Logger('e', "%s", CW2A(CT2W(temp), CP_UTF8));
				MessageBox(error, L"확인", MB_OK);
			}
			else {
				if (!selText.Compare(L"생각대로"))
					m_ListLookup.SetItemText(index, 9, L"U");
				else
					m_ListLookup.SetItemText(index, 11, L"U");

				CJSLogger::Logger('i', "Moacall store unlink success. : %s", CW2A(CT2W(lookupStore.link_code), CP_UTF8));
				temp.Format(L"%s 연동해제 업데이트가 완료되었습니다. 생각대로에 연동해제를 알려주세요.\n연동코드 : %s", selText, lookupStore.link_code);
				MessageBox(temp, L"확인", MB_OK);
			}

		}
		else if (!m_ListLookup.GetItemText(index, 0).Compare(L"딜리온")) {
			ResultData rdata;
			CJSLogger::Logger('i', "Delion store unlink.");

			lookupStore.agency_name = m_ListLookup.GetItemText(index, 0);
			lookupStore.store_code = m_ListLookup.GetItemText(index, 3);
			if (!selText.Compare(L"딜리온")) {
				lookupStore.store_code = m_ListLookup.GetItemText(index, 3);
				lookupStore.link_code = m_ListLookup.GetItemText(index, 4);
			}
			else {
				lookupStore.store_code = m_ListLookup.GetItemText(index, 4);
				lookupStore.link_code = m_ListLookup.GetItemText(index, 6);
			}
			
			ret = delionLink.StoreUnlink(lookupStore.store_code, lookupStore.link_code, &rdata);

			if (ret || _ttoi(rdata.ret_cd)) {
				temp.Empty();
				temp.Format(L"Beyond Unlink fail.[%04d]: %s. Link_code : %s", ret, rdata.ret_msg, lookupStore.link_code);
				CJSLogger::Logger('e', "%s", CW2A(CT2W(temp), CP_UTF8));
				MessageBox(rdata.ret_msg, L"경고", MB_ICONWARNING);
			}
			else {
				ret = CCustomMysql::UpdateDeliveryLink(lookupStore, &error);

				if (ret) {
					temp.Format(L"Beyond store unlink update fail.[%04d]: %s. linkcode : %s", ret, error, lookupStore.link_code);
					CJSLogger::Logger('e', "%s", CW2A(CT2W(temp), CP_UTF8));
					MessageBox(error, L"확인", MB_OK);
				}
				else {
					if (!selText.Compare(L"딜리온"))
						m_ListLookup.SetItemText(index, 8, L"U");
					else
						m_ListLookup.SetItemText(index, 11, L"U");

					CJSLogger::Logger('i', "Beyond store unlink success. : %s", CW2A(CT2W(lookupStore.link_code), CP_UTF8));
					temp.Format(L"연동해제 되었습니다.\n연동코드 : %s", lookupStore.link_code);
					MessageBox(temp, L"확인", MB_OK);
				}
			}

		}
		m_ListLookup.AdjustColumnWidth();
	}
}

BOOL CLookupDlg::CopyAllRowListToClipboard(BOOL isHeader, CListCtrl* pListCtrl, LPCTSTR lpszSeparator /*= _T("\t")*/)
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
	sResult.Empty();
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

BOOL CLookupDlg::CopyListCellToClipboard(CListCtrl * pListCtrl, LPCTSTR lpszSeparator)
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
	sResult.Empty();
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