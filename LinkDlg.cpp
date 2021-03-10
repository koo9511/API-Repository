// LinkDlg.cpp : ���� �����Դϴ�.
//

#include "stdafx.h"
#include "o2ns.h"
#include "LinkDlg.h"
#include "afxdialogex.h"

// CLinkDlg ��ȭ �����Դϴ�.

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


// CLinkDlg �޽��� ó�����Դϴ�.

BOOL CLinkDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	b_init = FALSE;

	m_BtnConfirm.m_nFlatStyle = CMFCButton::BUTTONSTYLE_NOBORDERS;
	m_BtnConfirm.m_bTransparent = FALSE;    // ���� ����
	m_BtnConfirm.m_bDrawFocus = FALSE;
	m_BtnConfirm.SetBkStdColor(RGB(60, 60, 60));
	m_BtnConfirm.SetTextStdColor(RGB(250, 250, 250));
	m_BtnConfirm.SetBkAltColor(RGB(110, 110, 110));
	m_BtnConfirm.SetTextAltColor(RGB(250, 250, 250));
	m_BtnConfirm.Update();
	//m_BtnNotice.SetFaceColor(RGB(250, 250, 250), TRUE);
	m_BtnConfirm.EnableWindowsTheming(FALSE);

	m_BtnLink.m_nFlatStyle = CMFCButton::BUTTONSTYLE_NOBORDERS;
	m_BtnLink.m_bTransparent = FALSE;    // ���� ����
	m_BtnLink.m_bDrawFocus = FALSE;
	m_BtnLink.SetBkStdColor(RGB(60, 60, 60));
	m_BtnLink.SetTextStdColor(RGB(250, 250, 250));
	m_BtnLink.SetBkAltColor(RGB(110, 110, 110));
	m_BtnLink.SetTextAltColor(RGB(250, 250, 250));
	m_BtnLink.Update();
	//m_BtnNotice.SetFaceColor(RGB(250, 250, 250), TRUE);
	m_BtnLink.EnableWindowsTheming(FALSE);

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

	GetDlgItem(IDC_STATIC)->SetFont(&m_font, TRUE);
	//GetDlgItem(IDC_STATIC2)->SetFont(&m_font, TRUE);
	GetDlgItem(IDC_BUTTON_CONFIRM)->SetFont(&m_font, TRUE);
	GetDlgItem(IDC_BUTTON_LINK)->SetFont(&m_font, TRUE);

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

	m_ListStores.InsertColumn(0, _T("�����"), LVCFMT_LEFT, 100, -1);
	m_ListStores.InsertColumn(1, _T("��ǥ�ڸ�"), LVCFMT_LEFT, 100, -1);
	m_ListStores.InsertColumn(2, _T("�����ڵ�"), LVCFMT_LEFT, 100, -1);
	m_ListStores.InsertColumn(3, _T("���� ������"), LVCFMT_LEFT, 100, -1);
	m_ListStores.InsertColumn(4, _T("���� ��ȭ"), LVCFMT_LEFT, 100, -1);
	m_ListStores.InsertColumn(5, _T("���� �޴���ȭ"), LVCFMT_LEFT, 100, -1);
	m_ListStores.InsertColumn(6, _T("���� �ּ�"), LVCFMT_LEFT, 100, -1);
	m_ListStores.AdjustColumnWidth();

	m_ComboAgency.InsertString(0, L"�����");
	m_ComboAgency.InsertString(1, L"�͵�");
	m_ComboAgency.InsertString(2, L"�丶���������");
	m_ComboAgency.InsertString(3, L"�޸���");
	m_ComboAgency.InsertString(4, L"���������");
	m_ComboAgency.InsertString(5, L"Ƽ�غ�");
	m_ComboAgency.InsertString(6, L"�ε庸��");
	m_ComboAgency.InsertString(7, L"�����̴�");
	m_ComboAgency.InsertString(8, L"�ູ���");
	m_ComboAgency.InsertString(9, L"�����������"); // ���������->�����������
	m_ComboAgency.InsertString(10, L"�ְ����");
	m_ComboAgency.InsertString(11, L"���׶�");
	//m_ComboAgency.InsertString(12, L"�ε����Ϸ�");
	m_ComboAgency.InsertString(12, L"�����");
	m_ComboAgency.InsertString(13, L"������");
	//m_ComboAgency.InsertString(15, L"Űģ��������");
	m_ComboAgency.InsertString(14, L"����ġ");
	m_ComboAgency.InsertString(15, L"�ϳ���");
	m_ComboAgency.InsertString(16, L"�������");
	m_ComboAgency.InsertString(17, L"������");
	m_ComboAgency.InsertString(18, L"������");
	m_ComboAgency.InsertString(19, L"��޷γ��󸦱��Ͻ�");
	m_ComboAgency.SetWindowText(L"");
	//m_ComboAgency.SetCurSel(1);

	b_init = TRUE;

	return TRUE;  // ��Ŀ���� ��Ʈ�ѿ� �������� ������ TRUE�� ��ȯ�մϴ�.
}

BOOL CLinkDlg::PreTranslateMessage(MSG* pMsg)
{
	// TODO: ���⿡ Ư��ȭ�� �ڵ带 �߰� ��/�Ǵ� �⺻ Ŭ������ ȣ���մϴ�.
	switch (pMsg->message) {
	case WM_KEYDOWN:	// Ű�� ��������
		switch (pMsg->wParam) {
		case VK_RETURN:	// ����Ű\tab
			if (GetFocus() == GetDlgItem(IDC_EDIT_SHOPCODE))
				::SendMessage(GetSafeHwnd(), WM_COMMAND, MAKEWPARAM(IDC_BUTTON_CONFIRM, BN_CLICKED), 0);
			else if (GetFocus() == GetDlgItem(IDC_BUTTON_CONFIRM))
				::SendMessage(GetSafeHwnd(), WM_COMMAND, MAKEWPARAM(IDC_BUTTON_CONFIRM, BN_CLICKED), 0);
			return TRUE;
		case VK_ESCAPE:	// ESCŰ
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

	// TODO:  ���⼭ DC�� Ư���� �����մϴ�.
	UINT nID = pWnd->GetDlgCtrlID();
	// TODO:  ���⼭ DC�� Ư���� �����մϴ�.
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
	// TODO:  �⺻���� �������� ������ �ٸ� �귯�ø� ��ȯ�մϴ�.
	return hbr;
}

BOOL CLinkDlg::OnEraseBkgnd(CDC* pDC)
{
	// TODO: ���⿡ �޽��� ó���� �ڵ带 �߰� ��/�Ǵ� �⺻���� ȣ���մϴ�.
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

	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	int ret = 0;
	m_EditShopCode.GetWindowText(c_ShopCode);
	
	if (!c_ShopCode.Compare(L"")) {
		if (!c_ShopCode.Compare(L""))
			MessageBox(L"����ڹ�ȣ�� �Է����ּ���.", L"�˸�", MB_OK);
	}
	else {
		m_ComboAgency.GetWindowText(selText);
		if (!selText.Compare(L"�����")
			|| !selText.Compare(L"�͵�")
			|| !selText.Compare(L"�丶���������")) {
			CJSLogger::Logger('i', "Moacall store search.");

			m_ListStores.DeleteAllItems();
			m_ListStores.DeleteAllColumns();
			m_ListStores.InsertColumn(0, _T("�����"), LVCFMT_LEFT, 100, -1);
			m_ListStores.InsertColumn(1, _T("��ǥ�ڸ�"), LVCFMT_LEFT, 100, -1);
			m_ListStores.InsertColumn(2, _T("�����ڵ�"), LVCFMT_LEFT, 100, -1);
			m_ListStores.InsertColumn(3, _T("���� ������"), LVCFMT_LEFT, 100, -1);
			m_ListStores.InsertColumn(4, _T("���� ��ȭ"), LVCFMT_LEFT, 100, -1);
			m_ListStores.InsertColumn(5, _T("���� �޴���ȭ"), LVCFMT_LEFT, 100, -1);
			m_ListStores.InsertColumn(6, _T("���� �ּ�"), LVCFMT_LEFT, 100, -1);

			ret = moaLink.StoreSearch(c_ShopCode, &m_moa, &m_rdata);

			if (ret) {
				temp.Format(L"Moacall store search fail.[%04d]: %s", ret, m_rdata.result_message);
				CJSLogger::Logger('e', "%s", CW2A(CT2W(temp), CP_UTF8));
				MessageBox(m_rdata.result_message, L"Ȯ��", MB_OK);
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
		else if (!selText.Compare(L"�޸���")
			|| !selText.Compare(L"���������")
			|| !selText.Compare(L"Ƽ�غ�")
			|| !selText.Compare(L"������")
			) {
			CJSLogger::Logger('i', "Daligo store search.");

			m_ListStores.DeleteAllItems();
			m_ListStores.DeleteAllColumns();
			m_ListStores.InsertColumn(0, _T("�����"), LVCFMT_LEFT, 100, -1);
			m_ListStores.InsertColumn(1, _T("�����ȣ"), LVCFMT_LEFT, 100, -1);
			m_ListStores.InsertColumn(2, _T("�����ڵ�"), LVCFMT_LEFT, 100, -1);
			m_ListStores.InsertColumn(3, _T("���� ��ȭ"), LVCFMT_LEFT, 100, -1);
			m_ListStores.InsertColumn(4, _T("���� �ּ�"), LVCFMT_LEFT, 100, -1);

			if (!selText.Compare(L"�޸���"))
				daligoLink.SetAgencyFlag(1);
			else if (!selText.Compare(L"���������"))
				daligoLink.SetAgencyFlag(2);
			else if (!selText.Compare(L"Ƽ�غ�"))
				daligoLink.SetAgencyFlag(3);
			else if (!selText.Compare(L"������"))
				daligoLink.SetAgencyFlag(4);
			ret = daligoLink.StoreSearch(c_ShopCode, &m_daligo, &d_rdata);

			if (ret) {
				temp.Format(L"Daligo store search fail.[%04d]: %s", ret, d_rdata.ret_msg);
				CJSLogger::Logger('e', "%s", CW2A(CT2W(temp), CP_UTF8));
				MessageBox(d_rdata.ret_msg, L"Ȯ��", MB_OK);
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
		else if (!selText.Compare(L"�ε庸��")) {
			CJSLogger::Logger('i', "Roadvoy store search.");

			m_ListStores.DeleteAllItems();
			m_ListStores.DeleteAllColumns();
			m_ListStores.InsertColumn(0, _T("�����"), LVCFMT_LEFT, 100, -1);
			m_ListStores.InsertColumn(1, _T("�ε庸��ID"), LVCFMT_LEFT, 100, -1);
			m_ListStores.InsertColumn(2, _T("�����ڵ�"), LVCFMT_LEFT, 100, -1);
			m_ListStores.InsertColumn(3, _T("���� ��ȭ"), LVCFMT_LEFT, 100, -1);
			m_ListStores.InsertColumn(4, _T("���� �޴���ȭ"), LVCFMT_LEFT, 100, -1);
			m_ListStores.InsertColumn(5, _T("���� �ּ�"), LVCFMT_LEFT, 100, -1);

			ret = roadvoyLink.StoreSearch(c_ShopCode, &m_roadvoy, &rv_rdata);

			if (ret) {
				temp.Format(L"Daligo store search fail.[%04d]: %s", ret, rv_rdata.ret_msg);
				CJSLogger::Logger('e', "%s", CW2A(CT2W(temp), CP_UTF8));
				MessageBox(rv_rdata.ret_msg, L"Ȯ��", MB_OK);
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
		else if (!selText.Compare(L"�����̴�")
			|| !selText.Compare(L"�ູ���")
			|| !selText.Compare(L"��޷γ��󸦱��Ͻ�")
			) {
			CJSLogger::Logger('i', "CombineNet store search.");

			m_ListStores.DeleteAllItems();
			m_ListStores.DeleteAllColumns();
			m_ListStores.InsertColumn(0, _T("�����"), LVCFMT_LEFT, 100, -1);
			m_ListStores.InsertColumn(1, _T("���������ȣ"), LVCFMT_LEFT, 100, -1);
			m_ListStores.InsertColumn(2, _T("�����ڵ�"), LVCFMT_LEFT, 100, -1);
			m_ListStores.InsertColumn(3, _T("���� ��ȭ"), LVCFMT_LEFT, 100, -1);
			m_ListStores.InsertColumn(4, _T("���� �޴���ȭ"), LVCFMT_LEFT, 100, -1);
			m_ListStores.InsertColumn(5, _T("���� �ּ�"), LVCFMT_LEFT, 100, -1);

			if (!selText.Compare(L"�ູ���"))	 // ���������->�����������
				combinetLink.SetAgencyFlag(cbn_hangbok);
			else if (!selText.Compare(L"�����̴�"))
				combinetLink.SetAgencyFlag(cbn_spider);
			else if (!selText.Compare(L"��޷γ��󸦱��Ͻ�"))
				combinetLink.SetAgencyFlag(cbn_baena9);

			ret = combinetLink.StoreSearch(c_ShopCode, &m_combinet, &cn_rdata);

			if (ret) {
				temp.Format(L"CombineNet store search fail.[%04d]: %s", ret, cn_rdata.ret_msg);
				CJSLogger::Logger('e', "%s", CW2A(CT2W(temp), CP_UTF8));
				MessageBox(cn_rdata.ret_msg, L"Ȯ��", MB_OK);
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
		else if (!selText.Compare(L"�����������")	 // ���������->�����������
			|| !selText.Compare(L"�ְ����")
			|| !selText.Compare(L"���׶�")
			//|| !selText.Compare(L"�ε����Ϸ�")
			|| !selText.Compare(L"�����")
			|| !selText.Compare(L"������")
			//|| !selText.Compare(L"Űģ��������") 
			|| !selText.Compare(L"����ġ")
			|| !selText.Compare(L"�ϳ���")
			) {
			CJSLogger::Logger('i', "Beyond store search.");
			int flag = 0;

			m_ListStores.DeleteAllItems();
			m_ListStores.DeleteAllColumns();
			m_ListStores.InsertColumn(0, _T("�����"), LVCFMT_LEFT, 100, -1);
			m_ListStores.InsertColumn(1, _T("���������ȣ"), LVCFMT_LEFT, 100, -1);
			m_ListStores.InsertColumn(2, _T("�����ڵ�"), LVCFMT_LEFT, 100, -1);
			m_ListStores.InsertColumn(3, _T("���� ��ȭ"), LVCFMT_LEFT, 100, -1);
			m_ListStores.InsertColumn(4, _T("���� �޴���ȭ"), LVCFMT_LEFT, 100, -1);
			m_ListStores.InsertColumn(5, _T("���� �ּ�"), LVCFMT_LEFT, 100, -1);

			if (!selText.Compare(L"�����������"))	 // ���������->�����������
				beyondLink.SetServFlag(by_byservice);
			else if (!selText.Compare(L"�ְ����"))
				beyondLink.SetServFlag(by_rushcall);
			else if (!selText.Compare(L"���׶�"))
				beyondLink.SetServFlag(by_veteran);
			//else if (!selText.Compare(L"�ε����Ϸ�"))
				//beyondLink.SetServFlag(by_roadpilot);
			else if (!selText.Compare(L"�����"))
				beyondLink.SetServFlag(by_dsp);
			else if (!selText.Compare(L"������"))
				beyondLink.SetServFlag(by_fooding);
			//else if (!selText.Compare(L"Űģ��������"))
				//beyondLink.SetServFlag(by_kitchen);
			else if (!selText.Compare(L"����ġ"))
				beyondLink.SetServFlag(by_mtouch);
			else if (!selText.Compare(L"�ϳ���"))
				beyondLink.SetServFlag(by_hanaro);


			ret = beyondLink.StoreSearch(c_ShopCode, &m_beyond, &by_rdata);

			if (ret) {
				temp.Format(L"Beyond store search fail.[%04d]: %s", ret, by_rdata.result_message);
				CJSLogger::Logger('e', "%s", CW2A(CT2W(temp), CP_UTF8));
				MessageBox(by_rdata.result_message, L"Ȯ��", MB_OK);
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
		else if (!selText.Compare(L"�������")) {
			CJSLogger::Logger('i', "Sanggag store search.");
			int flag = 0;

			m_ListStores.DeleteAllItems();
			m_ListStores.DeleteAllColumns();
			m_ListStores.InsertColumn(0, _T("�����"), LVCFMT_LEFT, 100, -1);
			m_ListStores.InsertColumn(1, _T("���������ȣ"), LVCFMT_LEFT, 100, -1);
			m_ListStores.InsertColumn(2, _T("�����ڵ�"), LVCFMT_LEFT, 100, -1);
			m_ListStores.InsertColumn(3, _T("���� �����ڵ�"), LVCFMT_LEFT, 100, -1);
			m_ListStores.InsertColumn(4, _T("���� ������"), LVCFMT_LEFT, 100, -1);
			m_ListStores.InsertColumn(5, _T("���� ��ȭ"), LVCFMT_LEFT, 100, -1);
			m_ListStores.InsertColumn(6, _T("���� �޴���ȭ"), LVCFMT_LEFT, 100, -1);
			m_ListStores.InsertColumn(7, _T("���� �ּ�"), LVCFMT_LEFT, 100, -1);


			ret = sanggagLink.StoreSearch(c_ShopCode, &m_sanggag, &sg_rdata);

			if (ret) {
				temp.Format(L"Beyond store search fail.[%04d]: %s", ret, sg_rdata.ret_msg);
				CJSLogger::Logger('e', "%s", CW2A(CT2W(temp), CP_UTF8));
				MessageBox(sg_rdata.ret_msg, L"Ȯ��", MB_OK);
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
		else if (!selText.Compare(L"������")) {
			CJSLogger::Logger('i', "Delion store search.");
			int flag = 0;

			m_ListStores.DeleteAllItems();
			m_ListStores.DeleteAllColumns();
			m_ListStores.InsertColumn(0, _T("�����"), LVCFMT_LEFT, 100, -1);
			m_ListStores.InsertColumn(1, _T("���������ȣ"), LVCFMT_LEFT, 100, -1);
			m_ListStores.InsertColumn(2, _T("�����ڵ�"), LVCFMT_LEFT, 100, -1);
			m_ListStores.InsertColumn(3, _T("����ڹ�ȣ"), LVCFMT_LEFT, 100, -1);
			m_ListStores.InsertColumn(4, _T("���� ��ȭ"), LVCFMT_LEFT, 100, -1);
			m_ListStores.InsertColumn(5, _T("���� �޴���ȭ"), LVCFMT_LEFT, 100, -1);
			m_ListStores.InsertColumn(6, _T("���� �ּ�"), LVCFMT_LEFT, 100, -1);


			ret = delionLink.StoreSearch(c_ShopCode, &m_store, &rdata);

			if (ret) {
				temp.Format(L"Beyond store search fail.[%04d]: %s", ret, rdata.ret_msg);
				CJSLogger::Logger('e', "%s", CW2A(CT2W(temp), CP_UTF8));
				MessageBox(rdata.ret_msg, L"Ȯ��", MB_OK);
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
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
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
		MessageBox(L"������ ������ �������ּ���.", L"Ȯ��", MB_OK);
	}
	else {
		m_ComboAgency.GetWindowText(selText);
		if (!selText.Compare(L"�����")
			|| !selText.Compare(L"�͵�")
			|| !selText.Compare(L"�丶���������")) {
			linkCode = m_ListStores.GetItemText(index, 2);
			temp.Format(L"�ش� ������ �����Ͻðڽ��ϱ�?\n�����ڵ� : %s", linkCode);
			if (MessageBox(temp, L"����", MB_YESNO) == IDYES) {
				temp.Empty();
				storeCode = m_ListStores.GetItemText(index, 3);
				CUtil::GetInitialFromHangeul(CT2W(storeCode), &temp, 6);
				temp.Remove(' ');
				temp.Remove('-');
				CTime c_time = CTime::GetCurrentTime(); // ���� �ý������κ��� ��¥ �� �ð��� ��� �´�.
				storeCode.Empty();
				storeCode.Format(L"%04d%02d%02d%02d%02d%02d%s", c_time.GetYear(), c_time.GetMonth(), c_time.GetDay(), c_time.GetHour(), c_time.GetMinute(), c_time.GetSecond(), temp);
				storeCode.Replace(L" ", L"");
				ret = moaLink.StoreLink(&storeCode, linkCode, &m_rdata);

				if (ret) {
					temp.Empty();
					temp.Format(L"Moacall Link fail.[%04d]: %s. StoreCode : %s, LinkCode : %s", ret, m_rdata.result_message, storeCode, linkCode);
					CJSLogger::Logger('e', "%s", CW2A(CT2W(temp), CP_UTF8));
					MessageBox(m_rdata.result_message, L"���", MB_ICONWARNING);
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
		else if (!selText.Compare(L"�޸���")
			|| !selText.Compare(L"���������")
			|| !selText.Compare(L"Ƽ�غ�")
			|| !selText.Compare(L"������")
			) {
			storeNum = m_ListStores.GetItemText(index, 1);
			linkCode = m_ListStores.GetItemText(index, 2);
			temp.Format(L"�ش� ������ �����Ͻðڽ��ϱ�?\n�����ڵ� : %s", linkCode);
			if (MessageBox(temp, L"����", MB_YESNO) == IDYES) {

				if (!selText.Compare(L"�޸���"))
					daligoLink.SetAgencyFlag(1);
				else if (!selText.Compare(L"���������"))
					daligoLink.SetAgencyFlag(2);
				else if (!selText.Compare(L"Ƽ�غ�"))
					daligoLink.SetAgencyFlag(3);
				else if (!selText.Compare(L"������"))
					daligoLink.SetAgencyFlag(4);
				ret = daligoLink.StoreLink(c_ShopCode, storeNum, linkCode, &d_rdata);

				if (ret) {
					temp.Empty();
					temp.Format(L"Daligo Link fail.[%04d]: %s. StoreCode : %s", ret, d_rdata.ret_msg, storeCode);
					CJSLogger::Logger('e', "%s", CW2A(CT2W(temp), CP_UTF8));
					MessageBox(d_rdata.ret_msg, L"���", MB_ICONWARNING);
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
		else if (!selText.Compare(L"�ε庸��")) {
			storeNum = m_ListStores.GetItemText(index, 1);
			linkCode = m_ListStores.GetItemText(index, 2);
			temp.Format(L"�ش� ������ �����Ͻðڽ��ϱ�?\n�����ڵ� : %s", linkCode);
			if (MessageBox(temp, L"����", MB_YESNO) == IDYES) {

				ret = roadvoyLink.StoreLink(storeNum, linkCode, &rv_rdata);

				if (ret) {
					temp.Empty();
					temp.Format(L"Roadvoy Link fail.[%04d]: %s. StoreCode : %s", ret, rv_rdata.ret_msg, storeCode);
					CJSLogger::Logger('e', "%s", CW2A(CT2W(temp), CP_UTF8));
					MessageBox(rv_rdata.ret_msg, L"���", MB_ICONWARNING);
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
		else if (!selText.Compare(L"�����̴�")
			|| !selText.Compare(L"�ູ���")
			|| !selText.Compare(L"��޷γ��󸦱��Ͻ�")
			) {
			storeNum = m_ListStores.GetItemText(index, 1);
			linkCode = m_ListStores.GetItemText(index, 2);
			temp.Format(L"�ش� ������ �����Ͻðڽ��ϱ�?\n�����ڵ� : %s", linkCode);
			if (MessageBox(temp, L"����", MB_YESNO) == IDYES) {

				if (!selText.Compare(L"�ູ���"))	 // ���������->�����������
					combinetLink.SetAgencyFlag(cbn_hangbok);
				else if (!selText.Compare(L"�����̴�"))
					combinetLink.SetAgencyFlag(cbn_spider);
				else if (!selText.Compare(L"��޷γ��󸦱��Ͻ�"))
					combinetLink.SetAgencyFlag(cbn_baena9);

				ret = combinetLink.StoreLink(storeNum, linkCode, &cn_rdata);

				if (ret) {
					temp.Empty();
					temp.Format(L"CombineNet Link fail.[%04d]: %s. StoreCode : %s", ret, cn_rdata.ret_msg, storeCode);
					CJSLogger::Logger('e', "%s", CW2A(CT2W(temp), CP_UTF8));
					MessageBox(cn_rdata.ret_msg, L"���", MB_ICONWARNING);
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
		else if (!selText.Compare(L"�����������")	 // ���������->�����������
			|| !selText.Compare(L"�ְ����")
			|| !selText.Compare(L"���׶�")
			//|| !selText.Compare(L"�ε����Ϸ�")
			|| !selText.Compare(L"�����")
			|| !selText.Compare(L"������")
			//|| !selText.Compare(L"Űģ��������")
			|| !selText.Compare(L"����ġ")
			|| !selText.Compare(L"�ϳ���")
			) {
			storeNum = m_ListStores.GetItemText(index, 1);
			linkCode = m_ListStores.GetItemText(index, 2);
			temp.Format(L"�ش� ������ �����Ͻðڽ��ϱ�?\n�����ڵ� : %s", linkCode);
			if (MessageBox(temp, L"����", MB_YESNO) == IDYES) {

				if (!selText.Compare(L"�����������"))	 // ���������->�����������
					beyondLink.SetServFlag(by_byservice);
				else if (!selText.Compare(L"�ְ����"))
					beyondLink.SetServFlag(by_rushcall);
				else if (!selText.Compare(L"���׶�"))
					beyondLink.SetServFlag(by_veteran);
				//else if (!selText.Compare(L"�ε����Ϸ�"))
					//beyondLink.SetServFlag(by_roadpilot);
				else if (!selText.Compare(L"�����"))
					beyondLink.SetServFlag(by_dsp);
				else if (!selText.Compare(L"������"))
					beyondLink.SetServFlag(by_fooding);
				//else if (!selText.Compare(L"Űģ��������"))
					//beyondLink.SetServFlag(by_kitchen);
				else if (!selText.Compare(L"����ġ"))
					beyondLink.SetServFlag(by_mtouch);
				else if (!selText.Compare(L"�ϳ���"))
					beyondLink.SetServFlag(by_hanaro);

				ret = beyondLink.StoreLink(storeNum, linkCode, TRUE, &by_rdata);

				if (ret) {
					temp.Empty();
					temp.Format(L"Beyond Link fail.[%04d]: %s. StoreCode : %s", ret, by_rdata.result_message, storeCode);
					CJSLogger::Logger('e', "%s", CW2A(CT2W(temp), CP_UTF8));
					MessageBox(by_rdata.result_message, L"���", MB_ICONWARNING);
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
		else if (!selText.Compare(L"�������")) {
			CString branch_code;
			storeNum = m_ListStores.GetItemText(index, 1);
			linkCode = m_ListStores.GetItemText(index, 2);
			branch_code = m_ListStores.GetItemText(index, 3);

			temp.Format(L"�ش� ������ �����Ͻðڽ��ϱ�?\n�����ڵ� : %s", linkCode);
			if (MessageBox(temp, L"����", MB_YESNO) == IDYES) {

				ret = sanggagLink.StoreLink(branch_code, storeNum, linkCode, &sg_rdata);

				if (ret) {
					temp.Empty();
					temp.Format(L"Sanggag Link fail.[%04d]: %s. StoreCode : %s", ret, sg_rdata.ret_msg, storeCode);
					CJSLogger::Logger('e', "%s", CW2A(CT2W(temp), CP_UTF8));
					MessageBox(sg_rdata.ret_msg, L"���", MB_ICONWARNING);
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
		else if (!selText.Compare(L"������")) {
			CString branch_code;
			storeNum = m_ListStores.GetItemText(index, 1);
			linkCode = m_ListStores.GetItemText(index, 2);

			temp.Format(L"�ش� ������ �����Ͻðڽ��ϱ�?\n�����ڵ� : %s", linkCode);
			if (MessageBox(temp, L"����", MB_YESNO) == IDYES) {

				ret = delionLink.StoreLink(storeNum, linkCode, &rdata);

				if (ret) {
					temp.Empty();
					temp.Format(L"DelionDlvy Link fail.[%04d]: %s. StoreCode : %s", ret, rdata.ret_msg, storeCode);
					CJSLogger::Logger('e', "%s", CW2A(CT2W(temp), CP_UTF8));
					MessageBox(rdata.ret_msg, L"���", MB_ICONWARNING);
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
				temp.Format(L"���� �Ǿ����� �������ۿ� �����߽��ϴ�. �����ڿ��� ������ �ֽʽÿ�.\n�����ڵ� : %s", linkCode);
				MessageBox(temp, L"���", MB_ICONWARNING);
			}
			else {
				temp.Format(L"���� �Ǿ����ϴ�.\n�����ڵ� : %s", linkCode);
				MessageBox(temp, L"Ȯ��", MB_OK);
			}
		}
	}

}

void CLinkDlg::OnMove(int x, int y)
{
	CDialogEx::OnMove(x, y);

	// TODO: ���⿡ �޽��� ó���� �ڵ带 �߰��մϴ�.

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
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	CString selText;

	m_ComboAgency.GetWindowText(selText);
	if (!selText.Compare(L"�����")
		|| !selText.Compare(L"�͵�")
		|| !selText.Compare(L"�丶���������")) {
		m_ListStores.DeleteAllColumns();
		m_ListStores.InsertColumn(0, _T("�����"), LVCFMT_LEFT, 100, -1);
		m_ListStores.InsertColumn(1, _T("��ǥ�ڸ�"), LVCFMT_LEFT, 100, -1);
		m_ListStores.InsertColumn(2, _T("�����ڵ�"), LVCFMT_LEFT, 100, -1);
		m_ListStores.InsertColumn(3, _T("���� ������"), LVCFMT_LEFT, 100, -1);
		m_ListStores.InsertColumn(4, _T("���� ��ȭ"), LVCFMT_LEFT, 100, -1);
		m_ListStores.InsertColumn(5, _T("���� �޴���ȭ"), LVCFMT_LEFT, 100, -1);
		m_ListStores.InsertColumn(6, _T("���� �ּ�"), LVCFMT_LEFT, 100, -1);
	}else if (!selText.Compare(L"�޸���")
		|| !selText.Compare(L"���������")
		|| !selText.Compare(L"Ƽ�غ�")
		|| !selText.Compare(L"������")) {
		m_ListStores.DeleteAllColumns();
		m_ListStores.InsertColumn(0, _T("�����"), LVCFMT_LEFT, 100, -1);
		m_ListStores.InsertColumn(1, _T("�����ڵ�"), LVCFMT_LEFT, 100, -1);
		m_ListStores.InsertColumn(2, _T("���������ȣ"), LVCFMT_LEFT, 100, -1);
		m_ListStores.InsertColumn(3, _T("���� ��ȭ"), LVCFMT_LEFT, 100, -1);
		m_ListStores.InsertColumn(4, _T("���� �ּ�"), LVCFMT_LEFT, 100, -1);
	}
	else if (!selText.Compare(L"�ε庸��")) {
		m_ListStores.DeleteAllColumns();
		m_ListStores.InsertColumn(0, _T("�����"), LVCFMT_LEFT, 100, -1);
		m_ListStores.InsertColumn(1, _T("�ε庸��ID"), LVCFMT_LEFT, 100, -1);
		m_ListStores.InsertColumn(2, _T("�����ڵ�"), LVCFMT_LEFT, 100, -1);
		m_ListStores.InsertColumn(3, _T("���� ��ȭ"), LVCFMT_LEFT, 100, -1);
		m_ListStores.InsertColumn(4, _T("���� �޴���ȭ"), LVCFMT_LEFT, 100, -1);
		m_ListStores.InsertColumn(5, _T("���� �ּ�"), LVCFMT_LEFT, 100, -1);
	}
	else if (!selText.Compare(L"�����̴�")
		|| !selText.Compare(L"�ູ���")
		|| !selText.Compare(L"��޷γ��󸦱��Ͻ�")) {
		m_ListStores.DeleteAllColumns();
		m_ListStores.InsertColumn(0, _T("�����"), LVCFMT_LEFT, 100, -1);
		m_ListStores.InsertColumn(1, _T("���������ȣ"), LVCFMT_LEFT, 100, -1);
		m_ListStores.InsertColumn(2, _T("�����ڵ�"), LVCFMT_LEFT, 100, -1);
		m_ListStores.InsertColumn(3, _T("���� ��ȭ"), LVCFMT_LEFT, 100, -1);
		m_ListStores.InsertColumn(4, _T("���� �޴���ȭ"), LVCFMT_LEFT, 100, -1);
		m_ListStores.InsertColumn(5, _T("���� �ּ�"), LVCFMT_LEFT, 100, -1);
	}
	else if (!selText.Compare(L"�����������")	 // ���������->�����������
		|| !selText.Compare(L"�ְ����")
		|| !selText.Compare(L"���׶�")
		//|| !selText.Compare(L"�ε����Ϸ�")
		|| !selText.Compare(L"�����")
		|| !selText.Compare(L"������")
		//|| !selText.Compare(L"Űģ��������")
		|| !selText.Compare(L"����ġ")
		|| !selText.Compare(L"�ϳ���")
		) {
		m_ListStores.DeleteAllColumns();
		m_ListStores.InsertColumn(0, _T("�����"), LVCFMT_LEFT, 100, -1);
		m_ListStores.InsertColumn(1, _T("���������ȣ"), LVCFMT_LEFT, 100, -1);
		m_ListStores.InsertColumn(2, _T("�����ڵ�"), LVCFMT_LEFT, 100, -1);
		m_ListStores.InsertColumn(3, _T("���� ��ȭ"), LVCFMT_LEFT, 100, -1);
		m_ListStores.InsertColumn(4, _T("���� �޴���ȭ"), LVCFMT_LEFT, 100, -1);
		m_ListStores.InsertColumn(5, _T("���� �ּ�"), LVCFMT_LEFT, 100, -1);
	}
	else if (!selText.Compare(L"�������")) {
		m_ListStores.DeleteAllColumns();
		m_ListStores.InsertColumn(0, _T("�����"), LVCFMT_LEFT, 100, -1);
		m_ListStores.InsertColumn(1, _T("���������ȣ"), LVCFMT_LEFT, 100, -1);
		m_ListStores.InsertColumn(2, _T("�����ڵ�"), LVCFMT_LEFT, 100, -1);
		m_ListStores.InsertColumn(3, _T("���� �����ڵ�"), LVCFMT_LEFT, 100, -1);
		m_ListStores.InsertColumn(4, _T("���� ������"), LVCFMT_LEFT, 100, -1);
		m_ListStores.InsertColumn(5, _T("���� ��ȭ"), LVCFMT_LEFT, 100, -1);
		m_ListStores.InsertColumn(6, _T("���� �޴���ȭ"), LVCFMT_LEFT, 100, -1);
		m_ListStores.InsertColumn(7, _T("���� �ּ�"), LVCFMT_LEFT, 100, -1);
	}
	else if (!selText.Compare(L"������")) {
		m_ListStores.DeleteAllColumns();
		m_ListStores.InsertColumn(0, _T("�����"), LVCFMT_LEFT, 100, -1);
		m_ListStores.InsertColumn(1, _T("���������ȣ"), LVCFMT_LEFT, 100, -1);
		m_ListStores.InsertColumn(2, _T("�����ڵ�"), LVCFMT_LEFT, 100, -1);
		m_ListStores.InsertColumn(3, _T("����ڹ�ȣ"), LVCFMT_LEFT, 100, -1);
		m_ListStores.InsertColumn(4, _T("���� ��ȭ"), LVCFMT_LEFT, 100, -1);
		m_ListStores.InsertColumn(5, _T("���� �޴���ȭ"), LVCFMT_LEFT, 100, -1);
		m_ListStores.InsertColumn(6, _T("���� �ּ�"), LVCFMT_LEFT, 100, -1);
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