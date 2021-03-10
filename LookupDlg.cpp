// LookupDlg.cpp : ���� �����Դϴ�.
//

#include "stdafx.h"
#include "o2ns.h"
#include "LookupDlg.h"
#include "afxdialogex.h"

// CLookupDlg ��ȭ �����Դϴ�.

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


// CLookupDlg �޽��� ó�����Դϴ�.

BOOL CLookupDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();
	
	b_init = FALSE;
	m_BtnLookup.m_nFlatStyle = CMFCButton::BUTTONSTYLE_NOBORDERS;
	m_BtnLookup.m_bTransparent = FALSE;    // ���� ����
	m_BtnLookup.m_bDrawFocus = FALSE;
	m_BtnLookup.SetBkStdColor(RGB(60, 60, 60));
	m_BtnLookup.SetTextStdColor(RGB(250, 250, 250));
	m_BtnLookup.SetBkAltColor(RGB(110, 110, 110));
	m_BtnLookup.SetTextAltColor(RGB(250, 250, 250));
	m_BtnLookup.Update();
	m_BtnLookup.EnableWindowsTheming(FALSE);

	m_BtnUnlink.m_nFlatStyle = CMFCButton::BUTTONSTYLE_NOBORDERS;
	m_BtnUnlink.m_bTransparent = FALSE;    // ���� ����
	m_BtnUnlink.m_bDrawFocus = FALSE;
	m_BtnUnlink.SetBkStdColor(RGB(60, 60, 60));
	m_BtnUnlink.SetTextStdColor(RGB(250, 250, 250));
	m_BtnUnlink.SetBkAltColor(RGB(220, 20, 60));
	m_BtnUnlink.SetTextAltColor(RGB(250, 250, 250));
	m_BtnUnlink.Update();
	m_BtnUnlink.EnableWindowsTheming(FALSE);

	// Set Fonts
	m_font.CreateFont(
		16, // ���� �� 
		0, // ���� ���� 
		0, // ���� ����
		0, // ���� ����
		FW_HEAVY,            // ���� ����
		FALSE,               // ���� ��︲ ���
		FALSE,               // �� ��
		FALSE,               // ��Ҽ�
		DEFAULT_CHARSET,     // ���� ��
		OUT_DEFAULT_PRECIS,  // ��� ��Ȯ��
		CLIP_DEFAULT_PRECIS, // ų���� ��Ȯ��
		DEFAULT_QUALITY,     // ����� ��
		DEFAULT_PITCH,       // �ڰ� �Ÿ�
		L"Arial"               // ���� ���
	); // lpszFacename 

	GetDlgItem(IDC_STATIC_BIZCODE)->SetFont(&m_font, TRUE);
	GetDlgItem(IDC_STATIC_MOACODE)->SetFont(&m_font, TRUE);
	GetDlgItem(IDC_STATIC_LINKDATE)->SetFont(&m_font, TRUE);
	GetDlgItem(IDC_STATIC_TILDE)->SetFont(&m_font, TRUE);
	GetDlgItem(IDC_MFCBUTTON_LOOKUP)->SetFont(&m_font, TRUE);

	m_font.Detach();
	
	m_font.CreateFont(
		16, // ���� �� 
		0, // ���� ���� 
		0, // ���� ����
		0, // ���� ����
		FALSE,            // ���� ����
		FALSE,               // ���� ��︲ ���
		FALSE,               // �� ��
		FALSE,               // ��Ҽ�
		DEFAULT_CHARSET,     // ���� ��
		OUT_DEFAULT_PRECIS,  // ��� ��Ȯ��
		CLIP_DEFAULT_PRECIS, // ų���� ��Ȯ��
		DEFAULT_QUALITY,     // ����� ��
		FIXED_PITCH,       // �ڰ� �Ÿ�
		L"Arial"               // ���� ���
	); // lpszFacename

	m_ListLookup.SetFont(&m_font, TRUE);
	m_ComboAgency.SetFont(&m_font, TRUE);

	m_font.Detach();

	// Set List control
	m_ListLookup.DeleteAllItems();

	m_ListLookup.ModifyStyle(0, LVS_SHOWSELALWAYS);
	m_ListLookup.SetExtendedStyle(LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES); //LVS_EX_CHECKBOXES

	// Moacall header
	m_ListLookup.InsertColumn(0, _T("������"), LVCFMT_LEFT, 100, -1);
	m_ListLookup.InsertColumn(1, _T("����ڹ�ȣ"), LVCFMT_LEFT, 100, -1);
	m_ListLookup.InsertColumn(2, _T("�����"), LVCFMT_LEFT, 100, -1);
	m_ListLookup.InsertColumn(3, _T("�����ڵ�"), LVCFMT_LEFT, 100, -1);
	m_ListLookup.InsertColumn(4, _T("��ǥ�ڸ�"), LVCFMT_LEFT, 100, -1);
	m_ListLookup.InsertColumn(5, _T("�����ڵ�"), LVCFMT_LEFT, 100, -1);
	m_ListLookup.InsertColumn(6, _T("���� ������"), LVCFMT_LEFT, 100, -1);
	m_ListLookup.InsertColumn(7, _T("���� ��ȭ"), LVCFMT_LEFT, 100, -1);
	m_ListLookup.InsertColumn(8, _T("���� �޴���ȭ"), LVCFMT_LEFT, 100, -1);
	m_ListLookup.InsertColumn(9, _T("���� �ּ�"), LVCFMT_LEFT, 100, -1);
	m_ListLookup.InsertColumn(10, _T("��������"), LVCFMT_LEFT, 100, -1);
	m_ListLookup.InsertColumn(11, _T("������������"), LVCFMT_LEFT, 100, -1);

	m_CheckStart.SetCheck(TRUE);
	m_CheckEnd.SetCheck(TRUE);

	//for (int i = 0; i < m_ListLookup.GetHeaderCtrl()->GetItemCount(); ++i)
	//	m_ListLookup.SetColumnWidth(i, LVSCW_AUTOSIZE_USEHEADER);
	m_ListLookup.AdjustColumnWidth();

	m_ComboAgency.InsertString(0, L"�����");
	m_ComboAgency.InsertString(1, L"�͵�");
	m_ComboAgency.InsertString(2, L"�丶���������");
	m_ComboAgency.InsertString(3, L"�޸���");
	m_ComboAgency.InsertString(4, L"���������");
	m_ComboAgency.InsertString(5, L"Ƽ�غ�");
	m_ComboAgency.InsertString(6, L"�ε庸��");
	m_ComboAgency.InsertString(7, L"�����̴�");
	m_ComboAgency.InsertString(8, L"�ູ���");
	m_ComboAgency.InsertString(9, L"���������");
	m_ComboAgency.InsertString(10, L"�����������");
	m_ComboAgency.InsertString(11, L"�ְ����");
	m_ComboAgency.InsertString(12, L"���׶�");
	//m_ComboAgency.InsertString(12, L"�ε����Ϸ�");
	m_ComboAgency.InsertString(13, L"�����");
	m_ComboAgency.InsertString(14, L"������");
	//m_ComboAgency.InsertString(15, L"Űģ��������");
	m_ComboAgency.InsertString(15, L"����ġ");
	m_ComboAgency.InsertString(16, L"�ϳ���");
	m_ComboAgency.InsertString(17, L"�������");
	m_ComboAgency.InsertString(18, L"������");
	m_ComboAgency.InsertString(19, L"������");
	m_ComboAgency.InsertString(20, L"��޷γ��󸦱��Ͻ�");
	m_ComboAgency.InsertString(21, L"��ü");
	//m_ComboAgency.InsertString(16, L"��ü");
	m_ComboAgency.SetWindowText(L"");

	b_init = TRUE;

	return TRUE;  // ��Ŀ���� ��Ʈ�ѿ� �������� ������ TRUE�� ��ȯ�մϴ�.
}


void CLookupDlg::OnMove(int x, int y)
{
	CDialogEx::OnMove(x, y);

	// TODO: ���⿡ �޽��� ó���� �ڵ带 �߰��մϴ�.
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
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
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
		MessageBox(error, L"Ȯ��", MB_OK);
	}
	else {
		if (!selText.Compare(L"�����")
			|| !selText.Compare(L"�͵�")
			|| !selText.Compare(L"�丶���������")) {
			m_ListLookup.DeleteAllItems();
			m_ListLookup.DeleteAllColumns();

			m_ListLookup.InsertColumn(0, _T("������"), LVCFMT_LEFT, 100, -1);
			m_ListLookup.InsertColumn(1, _T("����ڹ�ȣ"), LVCFMT_LEFT, 100, -1);
			m_ListLookup.InsertColumn(2, _T("�����"), LVCFMT_LEFT, 100, -1);
			m_ListLookup.InsertColumn(3, _T("�����ڵ�"), LVCFMT_LEFT, 100, -1);
			m_ListLookup.InsertColumn(4, _T("��ǥ�ڸ�"), LVCFMT_LEFT, 100, -1);
			m_ListLookup.InsertColumn(5, _T("�����ڵ�"), LVCFMT_LEFT, 100, -1);
			m_ListLookup.InsertColumn(6, _T("����������"), LVCFMT_LEFT, 100, -1);
			m_ListLookup.InsertColumn(7, _T("������ȭ"), LVCFMT_LEFT, 100, -1);
			m_ListLookup.InsertColumn(8, _T("�����޴���ȭ"), LVCFMT_LEFT, 100, -1);
			m_ListLookup.InsertColumn(9, _T("�����ּ�"), LVCFMT_LEFT, 100, -1);
			m_ListLookup.InsertColumn(10, _T("��������"), LVCFMT_LEFT, 100, -1);
			m_ListLookup.InsertColumn(11, _T("��������"), LVCFMT_LEFT, 100, -1);
			m_ListLookup.InsertColumn(12, _T("������������"), LVCFMT_LEFT, 100, -1);

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
		else if (!selText.Compare(L"�޸���")
			|| !selText.Compare(L"���������")
			|| !selText.Compare(L"Ƽ�غ�")
			|| !selText.Compare(L"������")
			) {
			m_ListLookup.DeleteAllItems();
			m_ListLookup.DeleteAllColumns();

			m_ListLookup.InsertColumn(0, _T("������"), LVCFMT_LEFT, 100, -1);
			m_ListLookup.InsertColumn(1, _T("����ڹ�ȣ"), LVCFMT_LEFT, 100, -1);
			m_ListLookup.InsertColumn(2, _T("�����"), LVCFMT_LEFT, 100, -1);
			m_ListLookup.InsertColumn(3, _T("�����ȣ"), LVCFMT_LEFT, 100, -1);
			m_ListLookup.InsertColumn(4, _T("�����ڵ�"), LVCFMT_LEFT, 100, -1);
			m_ListLookup.InsertColumn(5, _T("������ȭ"), LVCFMT_LEFT, 100, -1);
			m_ListLookup.InsertColumn(6, _T("�����ּ�"), LVCFMT_LEFT, 100, -1);
			m_ListLookup.InsertColumn(7, _T("��������"), LVCFMT_LEFT, 100, -1);
			m_ListLookup.InsertColumn(8, _T("��������"), LVCFMT_LEFT, 100, -1);
			m_ListLookup.InsertColumn(9, _T("������������"), LVCFMT_LEFT, 100, -1);

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
		else if (!selText.Compare(L"�ε庸��")) {
			m_ListLookup.DeleteAllItems();
			m_ListLookup.DeleteAllColumns();

			m_ListLookup.InsertColumn(0, _T("������"), LVCFMT_LEFT, 100, -1);
			m_ListLookup.InsertColumn(1, _T("����ڹ�ȣ"), LVCFMT_LEFT, 100, -1);
			m_ListLookup.InsertColumn(2, _T("�����"), LVCFMT_LEFT, 100, -1);
			m_ListLookup.InsertColumn(3, _T("�����ڵ�"), LVCFMT_LEFT, 100, -1);
			m_ListLookup.InsertColumn(4, _T("�����ڵ�"), LVCFMT_LEFT, 100, -1);
			m_ListLookup.InsertColumn(5, _T("������ȭ"), LVCFMT_LEFT, 100, -1);
			m_ListLookup.InsertColumn(6, _T("�����޴���ȭ"), LVCFMT_LEFT, 100, -1);
			m_ListLookup.InsertColumn(7, _T("�����ּ�"), LVCFMT_LEFT, 100, -1);
			m_ListLookup.InsertColumn(8, _T("��������"), LVCFMT_LEFT, 100, -1);
			m_ListLookup.InsertColumn(9, _T("��������"), LVCFMT_LEFT, 100, -1);
			m_ListLookup.InsertColumn(10, _T("������������"), LVCFMT_LEFT, 100, -1);

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
		else if (!selText.Compare(L"�����̴�")
			|| !selText.Compare(L"�ູ���")
			|| !selText.Compare(L"��޷γ��󸦱��Ͻ�")) {
			m_ListLookup.DeleteAllItems();
			m_ListLookup.DeleteAllColumns();

			m_ListLookup.InsertColumn(0, _T("������"), LVCFMT_LEFT, 100, -1);
			m_ListLookup.InsertColumn(1, _T("����ڹ�ȣ"), LVCFMT_LEFT, 100, -1);
			m_ListLookup.InsertColumn(2, _T("�����"), LVCFMT_LEFT, 100, -1);
			m_ListLookup.InsertColumn(3, _T("�����ڵ�"), LVCFMT_LEFT, 100, -1);
			m_ListLookup.InsertColumn(4, _T("�����ڵ�"), LVCFMT_LEFT, 100, -1);
			m_ListLookup.InsertColumn(5, _T("������ȭ"), LVCFMT_LEFT, 100, -1);
			m_ListLookup.InsertColumn(6, _T("�����޴���ȭ"), LVCFMT_LEFT, 100, -1);
			m_ListLookup.InsertColumn(7, _T("�����ּ�"), LVCFMT_LEFT, 100, -1);
			m_ListLookup.InsertColumn(8, _T("��������"), LVCFMT_LEFT, 100, -1);
			m_ListLookup.InsertColumn(9, _T("��������"), LVCFMT_LEFT, 100, -1);
			m_ListLookup.InsertColumn(10, _T("������������"), LVCFMT_LEFT, 100, -1);

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
		else if (!selText.Compare(L"���������")	 // ���������->�����������
			|| !selText.Compare(L"�����������")	 // ���������->�����������
			|| !selText.Compare(L"�ְ����")
			|| !selText.Compare(L"���׶�")
			//|| !selText.Compare(L"�ε����Ϸ�")
			|| !selText.Compare(L"�����")
			|| !selText.Compare(L"������")
			//|| !selText.Compare(L"Űģ��������")
			|| !selText.Compare(L"����ġ")
			|| !selText.Compare(L"�ϳ���")) {
			m_ListLookup.DeleteAllItems();
			m_ListLookup.DeleteAllColumns();

			m_ListLookup.InsertColumn(0, _T("������"), LVCFMT_LEFT, 100, -1);
			m_ListLookup.InsertColumn(1, _T("����ڹ�ȣ"), LVCFMT_LEFT, 100, -1);
			m_ListLookup.InsertColumn(2, _T("�����"), LVCFMT_LEFT, 100, -1);
			m_ListLookup.InsertColumn(3, _T("�����ڵ�"), LVCFMT_LEFT, 100, -1);
			m_ListLookup.InsertColumn(4, _T("�����ڵ�"), LVCFMT_LEFT, 100, -1);
			m_ListLookup.InsertColumn(5, _T("������ȭ"), LVCFMT_LEFT, 100, -1);
			m_ListLookup.InsertColumn(6, _T("�����޴���ȭ"), LVCFMT_LEFT, 100, -1);
			m_ListLookup.InsertColumn(7, _T("�����ּ�"), LVCFMT_LEFT, 100, -1);
			m_ListLookup.InsertColumn(8, _T("��������"), LVCFMT_LEFT, 100, -1);
			m_ListLookup.InsertColumn(9, _T("��������"), LVCFMT_LEFT, 100, -1);
			m_ListLookup.InsertColumn(10, _T("������������"), LVCFMT_LEFT, 100, -1);

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
		else if (!selText.Compare(L"�������")) {
			m_ListLookup.DeleteAllItems();
			m_ListLookup.DeleteAllColumns();

			m_ListLookup.InsertColumn(0, _T("������"), LVCFMT_LEFT, 100, -1);
			m_ListLookup.InsertColumn(1, _T("����ڹ�ȣ"), LVCFMT_LEFT, 100, -1);
			m_ListLookup.InsertColumn(2, _T("�����"), LVCFMT_LEFT, 100, -1);
			m_ListLookup.InsertColumn(3, _T("�����ڵ�"), LVCFMT_LEFT, 100, -1);
			m_ListLookup.InsertColumn(4, _T("�����ڵ�"), LVCFMT_LEFT, 100, -1);
			m_ListLookup.InsertColumn(5, _T("����������"), LVCFMT_LEFT, 100, -1);
			m_ListLookup.InsertColumn(6, _T("������ȭ"), LVCFMT_LEFT, 100, -1);
			m_ListLookup.InsertColumn(7, _T("�����޴���ȭ"), LVCFMT_LEFT, 100, -1);
			m_ListLookup.InsertColumn(8, _T("�����ּ�"), LVCFMT_LEFT, 100, -1);
			m_ListLookup.InsertColumn(9, _T("��������"), LVCFMT_LEFT, 100, -1);
			m_ListLookup.InsertColumn(10, _T("��������"), LVCFMT_LEFT, 100, -1);
			m_ListLookup.InsertColumn(11, _T("������������"), LVCFMT_LEFT, 100, -1);

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
		else if (!selText.Compare(L"������")) {
			m_ListLookup.DeleteAllItems();
			m_ListLookup.DeleteAllColumns();

			m_ListLookup.InsertColumn(0, _T("������"), LVCFMT_LEFT, 100, -1);
			m_ListLookup.InsertColumn(1, _T("����ڹ�ȣ"), LVCFMT_LEFT, 100, -1);
			m_ListLookup.InsertColumn(2, _T("�����"), LVCFMT_LEFT, 100, -1);
			m_ListLookup.InsertColumn(3, _T("�����ڵ�"), LVCFMT_LEFT, 100, -1);
			m_ListLookup.InsertColumn(4, _T("�����ڵ�"), LVCFMT_LEFT, 100, -1);
			m_ListLookup.InsertColumn(5, _T("������ȭ"), LVCFMT_LEFT, 100, -1);
			m_ListLookup.InsertColumn(6, _T("�����޴���ȭ"), LVCFMT_LEFT, 100, -1);
			m_ListLookup.InsertColumn(7, _T("�����ּ�"), LVCFMT_LEFT, 100, -1);
			m_ListLookup.InsertColumn(8, _T("��������"), LVCFMT_LEFT, 100, -1);
			m_ListLookup.InsertColumn(9, _T("��������"), LVCFMT_LEFT, 100, -1);
			m_ListLookup.InsertColumn(10, _T("������������"), LVCFMT_LEFT, 100, -1);

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
		else if (!selText.Compare(L"��ü")) {
			m_ListLookup.DeleteAllItems();
			m_ListLookup.DeleteAllColumns();

			m_ListLookup.InsertColumn(0, _T("������"), LVCFMT_LEFT, 100, -1);
			m_ListLookup.InsertColumn(1, _T("����ڹ�ȣ"), LVCFMT_LEFT, 100, -1);
			m_ListLookup.InsertColumn(2, _T("�����"), LVCFMT_LEFT, 100, -1);
			m_ListLookup.InsertColumn(3, _T("�����ȣ"), LVCFMT_LEFT, 100, -1);
			m_ListLookup.InsertColumn(4, _T("�����ڵ�"), LVCFMT_LEFT, 100, -1);
			m_ListLookup.InsertColumn(5, _T("��ǥ�ڸ�"), LVCFMT_LEFT, 100, -1);
			m_ListLookup.InsertColumn(6, _T("�����ڵ�"), LVCFMT_LEFT, 100, -1);
			m_ListLookup.InsertColumn(7, _T("����������"), LVCFMT_LEFT, 100, -1);
			m_ListLookup.InsertColumn(8, _T("������ȭ"), LVCFMT_LEFT, 100, -1);
			m_ListLookup.InsertColumn(9, _T("�����޴���ȭ"), LVCFMT_LEFT, 100, -1);
			m_ListLookup.InsertColumn(10, _T("�����ּ�"), LVCFMT_LEFT, 100, -1);
			m_ListLookup.InsertColumn(11, _T("��������"), LVCFMT_LEFT, 100, -1);
			m_ListLookup.InsertColumn(12, _T("��������"), LVCFMT_LEFT, 100, -1);
			m_ListLookup.InsertColumn(13, _T("������������"), LVCFMT_LEFT, 100, -1);
			
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
//	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
//	
//
//	*pResult = 0;
//}

BOOL CLookupDlg::PreTranslateMessage(MSG* pMsg)
{
	// TODO: ���⿡ Ư��ȭ�� �ڵ带 �߰� ��/�Ǵ� �⺻ Ŭ������ ȣ���մϴ�.
	switch (pMsg->message) {
	case WM_KEYDOWN:	// Ű�� ��������
		switch (pMsg->wParam) {
		case VK_RETURN:	// ����Ű\tab 
			if (GetFocus() == GetDlgItem(IDC_EDIT_BIZCODE)
				|| GetFocus() == GetDlgItem(IDC_EDIT_LINKCODE)
				|| GetFocus() == GetDlgItem(IDC_DATETIMEPICKER_START)
				|| GetFocus() == GetDlgItem(IDC_DATETIMEPICKER_END)
				|| GetFocus() == GetDlgItem(IDC_COMBO_AGENCY2))
				::SendMessage(GetSafeHwnd(), WM_COMMAND, MAKEWPARAM(IDC_MFCBUTTON_LOOKUP, BN_CLICKED), 0);
			else if (GetFocus() == GetDlgItem(IDC_MFCBUTTON_LOOKUP))
				::SendMessage(GetSafeHwnd(), WM_COMMAND, MAKEWPARAM(IDC_MFCBUTTON_LOOKUP, BN_CLICKED), 0);
			return TRUE;
		case VK_ESCAPE:	// ESCŰ
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
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
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
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	CHttpsRequest hReq;
	LookupStore lookupStore;
	CString list_seq_string;
	CString temp;
	CString error;
	CString selText;
	int ret = 0;
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
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
		MessageBox(L"����縦 �������ּ���.", L"���", MB_ICONWARNING);
	}
	else {
		m_ComboAgency.GetWindowText(selText);
		//selText = m_ListLookup.GetItemText(index, 0);
		if (!m_ListLookup.GetItemText(index, 0).Compare(L"�����")
			|| !m_ListLookup.GetItemText(index, 0).Compare(L"�͵�")
			|| !m_ListLookup.GetItemText(index, 0).Compare(L"�丶���������")) {
			CJSLogger::Logger('i', "Moacall store unlink.");

			lookupStore.agency_name = m_ListLookup.GetItemText(index, 0);
			if (!selText.Compare(L"�����")
				|| !selText.Compare(L"�͵�")
				|| !selText.Compare(L"�丶���������"))
				lookupStore.link_code = m_ListLookup.GetItemText(index, 5);
			else
				lookupStore.link_code = m_ListLookup.GetItemText(index, 6);


			temp.Format(L"�ش� ������ �������� �Ͻðڽ��ϱ�?\n%s �����ڵ� : %s", selText, lookupStore.link_code);
			if (MessageBox(temp, L"����", MB_YESNO) != IDYES) 
				return;

			ret = CCustomMysql::UpdateDeliveryLink(lookupStore, &error);

			if (ret) {
				temp.Format(L"Moacall store unlink update fail.[%04d]: %s. linkcode : %s", ret, error, lookupStore.link_code);
				CJSLogger::Logger('e', "%s", CW2A(CT2W(temp), CP_UTF8));
				MessageBox(error, L"Ȯ��", MB_OK);
			}
			else {
				if (!selText.Compare(L"�����")
					|| !selText.Compare(L"�͵�")
					|| !selText.Compare(L"�丶���������"))
					m_ListLookup.SetItemText(index, 10, L"U");
				else
					m_ListLookup.SetItemText(index, 11, L"U");

				CJSLogger::Logger('i', "Moacall store unlink success. : %s", CW2A(CT2W(lookupStore.link_code), CP_UTF8));
				temp.Format(L"%s �������� ������Ʈ�� �Ϸ�Ǿ����ϴ�. ����ݿ� ���������� �˷��ּ���.\n�����ڵ� : %s", selText, lookupStore.link_code);
				MessageBox(temp, L"Ȯ��", MB_OK);
			}
			
		}
		else if (!m_ListLookup.GetItemText(index, 0).Compare(L"�޸���")
			|| !m_ListLookup.GetItemText(index, 0).Compare(L"���������")
			|| !m_ListLookup.GetItemText(index, 0).Compare(L"Ƽ�غ�")
			|| !m_ListLookup.GetItemText(index, 0).Compare(L"������")
			) {
			DaligoResultData d_rdata;
			CJSLogger::Logger('i', "Daligo store unlink.");

			lookupStore.agency_name = m_ListLookup.GetItemText(index, 0);
			lookupStore.biz_num = m_ListLookup.GetItemText(index, 1);
			if (!selText.Compare(L"�޸���")
				|| !selText.Compare(L"���������")
				|| !selText.Compare(L"Ƽ�غ�")
				|| !selText.Compare(L"������")
				) {
				lookupStore.link_code = m_ListLookup.GetItemText(index, 4);
			}
			else {
				lookupStore.link_code = m_ListLookup.GetItemText(index, 6);
			}

			temp.Format(L"�ش� ������ �������� �Ͻðڽ��ϱ�?\n%s �����ڵ� : %s", selText, lookupStore.link_code);
			if (MessageBox(temp, L"����", MB_YESNO) != IDYES) 
				return;

			CString flagTemp = m_ListLookup.GetItemText(index, 0);
			if (!flagTemp.Compare(L"�޸���"))
				daligoLink.SetAgencyFlag(1);
			else if (!flagTemp.Compare(L"���������"))
				daligoLink.SetAgencyFlag(2);
			else if (!flagTemp.Compare(L"Ƽ�غ�"))
				daligoLink.SetAgencyFlag(3);
			if (!flagTemp.Compare(L"������"))
				daligoLink.SetAgencyFlag(4);
			ret = daligoLink.StoreUnlink(lookupStore.biz_num, lookupStore.link_code, &d_rdata);

			if (ret) {
				temp.Empty();
				temp.Format(L"Daligo Unlink fail.[%04d]: %s. Link_code : %s", ret, d_rdata.ret_msg, lookupStore.link_code);
				CJSLogger::Logger('e', "%s", CW2A(CT2W(temp), CP_UTF8));
				MessageBox(d_rdata.ret_msg, L"���", MB_ICONWARNING);
			}
			else {
				ret = CCustomMysql::UpdateDeliveryLink(lookupStore, &error);

				if (ret) {
					temp.Format(L"Daligo store unlink update fail.[%04d]: %s. linkcode : %s", ret, error, lookupStore.link_code);
					CJSLogger::Logger('e', "%s", CW2A(CT2W(temp), CP_UTF8));
					MessageBox(error, L"Ȯ��", MB_OK);
				}
				else {
					if (!selText.Compare(L"�޸���")
						|| !selText.Compare(L"���������")
						|| !selText.Compare(L"Ƽ�غ�")
						|| !selText.Compare(L"������")
						)
						m_ListLookup.SetItemText(index, 7, L"U");
					else
						m_ListLookup.SetItemText(index, 11, L"U");

					CJSLogger::Logger('i', "Daligo store unlink success. : %s", CW2A(CT2W(lookupStore.link_code), CP_UTF8));
					temp.Format(L"�������� �Ǿ����ϴ�.\n�����ڵ� : %s", lookupStore.link_code);
					MessageBox(temp, L"Ȯ��", MB_OK);
				}
			}
		}
		else if (!m_ListLookup.GetItemText(index, 0).Compare(L"�ε庸��")) {
			RoadvoyResultData r_rdata;
			CJSLogger::Logger('i', "Roadvoy store unlink.");

			lookupStore.agency_name = m_ListLookup.GetItemText(index, 0);
			lookupStore.biz_num = m_ListLookup.GetItemText(index, 1);
			if (!selText.Compare(L"�ε庸��")) {
				lookupStore.link_code = m_ListLookup.GetItemText(index, 4);
			}
			else {
				lookupStore.link_code = m_ListLookup.GetItemText(index, 6);
			}

			temp.Format(L"�ش� ������ �������� �Ͻðڽ��ϱ�?\n%s �����ڵ� : %s", selText, lookupStore.link_code);
			if (MessageBox(temp, L"����", MB_YESNO) != IDYES)
				return;

			ret = roadvoyLink.StoreUnlink(lookupStore.link_code, &r_rdata);

			if (ret) {
				temp.Empty();
				temp.Format(L"Roadvoy Unlink fail.[%04d]: %s. Link_code : %s", ret, r_rdata.ret_msg, lookupStore.link_code);
				CJSLogger::Logger('e', "%s", CW2A(CT2W(temp), CP_UTF8));
				MessageBox(r_rdata.ret_msg, L"���", MB_ICONWARNING);
			}
			else {
				ret = CCustomMysql::UpdateDeliveryLink(lookupStore, &error);

				if (ret) {
					temp.Format(L"Roadvoy store unlink update fail.[%04d]: %s. linkcode : %s", ret, error, lookupStore.link_code);
					CJSLogger::Logger('e', "%s", CW2A(CT2W(temp), CP_UTF8));
					MessageBox(error, L"Ȯ��", MB_OK);
				}
				else {
					if (!selText.Compare(L"�ε庸��"))
						m_ListLookup.SetItemText(index, 8, L"U");
					else
						m_ListLookup.SetItemText(index, 11, L"U");

					CJSLogger::Logger('i', "Roadvoy store unlink success. : %s", CW2A(CT2W(lookupStore.link_code), CP_UTF8));
					temp.Format(L"�������� �Ǿ����ϴ�.\n�����ڵ� : %s", lookupStore.link_code);
					MessageBox(temp, L"Ȯ��", MB_OK);
				}
			}
		}
		else if (!m_ListLookup.GetItemText(index, 0).Compare(L"�����̴�")
			|| !m_ListLookup.GetItemText(index, 0).Compare(L"�ູ���")
			|| !m_ListLookup.GetItemText(index, 0).Compare(L"��޷γ��󸦱��Ͻ�")
			) {
			CombineNetResultData cn_rdata;
			CJSLogger::Logger('i', "CombineNet store unlink.");

			lookupStore.agency_name = m_ListLookup.GetItemText(index, 0);
			lookupStore.store_code = m_ListLookup.GetItemText(index, 3);

			if (!selText.Compare(L"�����̴�")
				|| !selText.Compare(L"�ູ���")
				|| !selText.Compare(L"��޷γ��󸦱��Ͻ�")) {
				lookupStore.link_code = m_ListLookup.GetItemText(index, 4);
			}
			else {
				lookupStore.link_code = m_ListLookup.GetItemText(index, 6);
			}

			temp.Format(L"�ش� ������ �������� �Ͻðڽ��ϱ�?\n%s �����ڵ� : %s", selText, lookupStore.link_code);
			if (MessageBox(temp, L"����", MB_YESNO) != IDYES)
				return;

			if (!selText.Compare(L"�ູ���"))	 // ���������->�����������
				combinetLink.SetAgencyFlag(cbn_hangbok);
			else if (!selText.Compare(L"�����̴�"))
				combinetLink.SetAgencyFlag(cbn_spider);
			else if (!selText.Compare(L"��޷γ��󸦱��Ͻ�"))
				combinetLink.SetAgencyFlag(cbn_baena9);

			ret = combinetLink.StoreUnlink(lookupStore.store_code, lookupStore.link_code, &cn_rdata);

			if (ret || _ttoi(cn_rdata.ret_cd)) {
				temp.Empty();
				temp.Format(L"Roadvoy Unlink fail.[%04d]: %s. Link_code : %s", ret, cn_rdata.ret_msg, lookupStore.link_code);
				CJSLogger::Logger('e', "%s", CW2A(CT2W(temp), CP_UTF8));
				MessageBox(cn_rdata.ret_msg, L"���", MB_ICONWARNING);
			}
			else {
				ret = CCustomMysql::UpdateDeliveryLink(lookupStore, &error);

				if (ret) {
					temp.Format(L"Roadvoy store unlink update fail.[%04d]: %s. linkcode : %s", ret, error, lookupStore.link_code);
					CJSLogger::Logger('e', "%s", CW2A(CT2W(temp), CP_UTF8));
					MessageBox(error, L"Ȯ��", MB_OK);
				}
				else {
					if (!selText.Compare(L"�����̴�")
						|| !selText.Compare(L"�ູ���")
						|| !selText.Compare(L"��޷γ��󸦱��Ͻ�"))
						m_ListLookup.SetItemText(index, 8, L"U");
					else
						m_ListLookup.SetItemText(index, 11, L"U");

					CJSLogger::Logger('i', "Roadvoy store unlink success. : %s", CW2A(CT2W(lookupStore.link_code), CP_UTF8));
					temp.Format(L"�������� �Ǿ����ϴ�.\n�����ڵ� : %s", lookupStore.link_code);
					MessageBox(temp, L"Ȯ��", MB_OK);
				}
			}
		}
		else if (!m_ListLookup.GetItemText(index, 0).Compare(L"���������")
			|| !m_ListLookup.GetItemText(index, 0).Compare(L"�����������")
			|| !m_ListLookup.GetItemText(index, 0).Compare(L"�ְ����")
			|| !m_ListLookup.GetItemText(index, 0).Compare(L"���׶�")
			//|| !m_ListLookup.GetItemText(index, 0).Compare(L"�ε����Ϸ�")
			|| !m_ListLookup.GetItemText(index, 0).Compare(L"�����")
			|| !m_ListLookup.GetItemText(index, 0).Compare(L"������")
			//|| !m_ListLookup.GetItemText(index, 0).Compare(L"Űģ��������")
			|| !m_ListLookup.GetItemText(index, 0).Compare(L"����ġ")
			|| !m_ListLookup.GetItemText(index, 0).Compare(L"�ϳ���")
			) {
			BeyondResultData by_rdata;
			CJSLogger::Logger('i', "Beyond store unlink.");

			lookupStore.agency_name = m_ListLookup.GetItemText(index, 0);
			lookupStore.store_code = m_ListLookup.GetItemText(index, 3);
			if (!selText.Compare(L"���������")	 // ���������->�����������
				|| !selText.Compare(L"�����������")	 // ���������->�����������
				|| !selText.Compare(L"�ְ����")
				|| !selText.Compare(L"���׶�")
				//|| !selText.Compare(L"�ε����Ϸ�")
				|| !selText.Compare(L"�����")
				|| !selText.Compare(L"������")
				//|| !selText.Compare(L"Űģ��������")
				|| !selText.Compare(L"����ġ")
				|| !selText.Compare(L"�ϳ���")
				) {
				lookupStore.link_code = m_ListLookup.GetItemText(index, 4);
			}
			else {
				lookupStore.link_code = m_ListLookup.GetItemText(index, 6);
			}

			temp.Format(L"�ش� ������ �������� �Ͻðڽ��ϱ�?\n%s �����ڵ� : %s", selText, lookupStore.link_code);
			if (MessageBox(temp, L"����", MB_YESNO) != IDYES)
				return;

			CString flagTemp = m_ListLookup.GetItemText(index, 0);
			if (!selText.Compare(L"�����������") || !selText.Compare(L"���������"))	 // ���������->�����������
				beyondLink.SetServFlag(by_byservice);
			else if (!flagTemp.Compare(L"�ְ����"))
				beyondLink.SetServFlag(by_rushcall);
			else if (!flagTemp.Compare(L"���׶�"))
				beyondLink.SetServFlag(by_veteran);
			else if (!flagTemp.Compare(L"�ε����Ϸ�"))
				beyondLink.SetServFlag(by_roadpilot);
			else if (!flagTemp.Compare(L"�����"))
				beyondLink.SetServFlag(by_dsp);
			else if (!flagTemp.Compare(L"������"))
				beyondLink.SetServFlag(by_fooding);
			else if (!flagTemp.Compare(L"Űģ��������"))
				beyondLink.SetServFlag(by_kitchen);
			else if (!flagTemp.Compare(L"����ġ"))
				beyondLink.SetServFlag(by_mtouch);
			else if (!flagTemp.Compare(L"�ϳ���"))
				beyondLink.SetServFlag(by_hanaro);


			ret = beyondLink.StoreLink(lookupStore.store_code, lookupStore.link_code, FALSE, &by_rdata);
			
			if (ret || _ttoi(by_rdata.result_code)) {
				temp.Empty();
				temp.Format(L"Beyond Unlink fail.[%04d]: %s. Link_code : %s", ret, by_rdata.result_message, lookupStore.link_code);
				CJSLogger::Logger('e', "%s", CW2A(CT2W(temp), CP_UTF8));
				MessageBox(by_rdata.result_message, L"���", MB_ICONWARNING);
			}
			else {
				ret = CCustomMysql::UpdateDeliveryLink(lookupStore, &error);

				if (ret) {
					temp.Format(L"Beyond store unlink update fail.[%04d]: %s. linkcode : %s", ret, error, lookupStore.link_code);
					CJSLogger::Logger('e', "%s", CW2A(CT2W(temp), CP_UTF8));
					MessageBox(error, L"Ȯ��", MB_OK);
				}
				else {
					if (!selText.Compare(L"���������")	 // ���������->�����������
						|| !selText.Compare(L"�����������")	 // ���������->�����������
						|| !selText.Compare(L"�ְ����")
						|| !selText.Compare(L"���׶�")
						//|| !selText.Compare(L"�ε����Ϸ�")
						|| !selText.Compare(L"�����")
						|| !selText.Compare(L"������")
						//|| !selText.Compare(L"Űģ��������") 
						|| !selText.Compare(L"����ġ")
						|| !selText.Compare(L"�ϳ���")
						)
						m_ListLookup.SetItemText(index, 8, L"U");
					else
						m_ListLookup.SetItemText(index, 11, L"U");

					CJSLogger::Logger('i', "Beyond store unlink success. : %s", CW2A(CT2W(lookupStore.link_code), CP_UTF8));
					temp.Format(L"�������� �Ǿ����ϴ�.\n�����ڵ� : %s", lookupStore.link_code);
					MessageBox(temp, L"Ȯ��", MB_OK);
				}
			}
		}else if (!m_ListLookup.GetItemText(index, 0).Compare(L"�������")) {
			CJSLogger::Logger('i', "Sanggag store unlink.");

			lookupStore.agency_name = m_ListLookup.GetItemText(index, 0);
			if (!selText.Compare(L"�������"))
				lookupStore.link_code = m_ListLookup.GetItemText(index, 4);
			else
				lookupStore.link_code = m_ListLookup.GetItemText(index, 6);


			temp.Format(L"�ش� ������ �������� �Ͻðڽ��ϱ�?\n%s �����ڵ� : %s", selText, lookupStore.link_code);
			if (MessageBox(temp, L"����", MB_YESNO) != IDYES)
				return;

			ret = CCustomMysql::UpdateDeliveryLink(lookupStore, &error);

			if (ret) {
				temp.Format(L"Moacall store unlink update fail.[%04d]: %s. linkcode : %s", ret, error, lookupStore.link_code);
				CJSLogger::Logger('e', "%s", CW2A(CT2W(temp), CP_UTF8));
				MessageBox(error, L"Ȯ��", MB_OK);
			}
			else {
				if (!selText.Compare(L"�������"))
					m_ListLookup.SetItemText(index, 9, L"U");
				else
					m_ListLookup.SetItemText(index, 11, L"U");

				CJSLogger::Logger('i', "Moacall store unlink success. : %s", CW2A(CT2W(lookupStore.link_code), CP_UTF8));
				temp.Format(L"%s �������� ������Ʈ�� �Ϸ�Ǿ����ϴ�. ������ο� ���������� �˷��ּ���.\n�����ڵ� : %s", selText, lookupStore.link_code);
				MessageBox(temp, L"Ȯ��", MB_OK);
			}

		}
		else if (!m_ListLookup.GetItemText(index, 0).Compare(L"������")) {
			ResultData rdata;
			CJSLogger::Logger('i', "Delion store unlink.");

			lookupStore.agency_name = m_ListLookup.GetItemText(index, 0);
			lookupStore.store_code = m_ListLookup.GetItemText(index, 3);
			if (!selText.Compare(L"������")) {
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
				MessageBox(rdata.ret_msg, L"���", MB_ICONWARNING);
			}
			else {
				ret = CCustomMysql::UpdateDeliveryLink(lookupStore, &error);

				if (ret) {
					temp.Format(L"Beyond store unlink update fail.[%04d]: %s. linkcode : %s", ret, error, lookupStore.link_code);
					CJSLogger::Logger('e', "%s", CW2A(CT2W(temp), CP_UTF8));
					MessageBox(error, L"Ȯ��", MB_OK);
				}
				else {
					if (!selText.Compare(L"������"))
						m_ListLookup.SetItemText(index, 8, L"U");
					else
						m_ListLookup.SetItemText(index, 11, L"U");

					CJSLogger::Logger('i', "Beyond store unlink success. : %s", CW2A(CT2W(lookupStore.link_code), CP_UTF8));
					temp.Format(L"�������� �Ǿ����ϴ�.\n�����ڵ� : %s", lookupStore.link_code);
					MessageBox(temp, L"Ȯ��", MB_OK);
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

	//�÷� �̸� ���� ����ü
	TCHAR szName[128]; // This is the buffer where the name will be stored
	LVCOLUMN lvColInfo;
	lvColInfo.mask = LVCF_TEXT;
	lvColInfo.pszText = szName;
	lvColInfo.cchTextMax = _countof(szName);

	//����� �÷� ���� ���ϱ�
	if ((pListCtrl->GetStyle() & LVS_TYPEMASK) == LVS_REPORT &&
		pListCtrl->GetExtendedStyle() & LVS_EX_FULLROWSELECT)
	{
		CHeaderCtrl* pHeader = pListCtrl->GetHeaderCtrl();
		nColumn = pHeader ? pHeader->GetItemCount() : 1;
	}

	//�÷� �̸� ����
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

	//������ ���� ����
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

	//Ŭ������ ����
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

	//�÷� �̸� ���� ����ü
	TCHAR szName[128]; // This is the buffer where the name will be stored
	LVCOLUMN lvColInfo;
	lvColInfo.mask = LVCF_TEXT;
	lvColInfo.pszText = szName;
	lvColInfo.cchTextMax = _countof(szName);

	//����� �÷� ���� ���ϱ�
	if ((pListCtrl->GetStyle() & LVS_TYPEMASK) == LVS_REPORT &&
		pListCtrl->GetExtendedStyle() & LVS_EX_FULLROWSELECT)
	{
		CHeaderCtrl* pHeader = pListCtrl->GetHeaderCtrl();
		nColumn = pHeader ? pHeader->GetItemCount() : 1;
	}

	//�÷� �̸� ����
	for (int i = 0; i < nColumn; ++i)
	{
		pListCtrl->GetColumn(i, &lvColInfo);

		temp = lvColInfo.pszText;
		if (!temp.Compare(L"�����ڵ�")) {
			subItem = i;
			break;
		}
	}


	//������ ���� ����
	sResult.Empty();
	while (pos)
	{
		if (0 != nCount)
			sResult += _T("\r\n");
		nItem = pListCtrl->GetNextSelectedItem(pos);
		sResult += pListCtrl->GetItemText(nItem, subItem);
		++nCount;
	}

	//Ŭ������ ����
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