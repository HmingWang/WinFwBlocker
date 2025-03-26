// CAddIPAdressDlg.cpp: 实现文件
//

#include "pch.h"
#include "WinFwBlocker.h"
#include "afxdialogex.h"
#include "CAddIPAdressDlg.h"


// CAddIPAdressDlg 对话框

IMPLEMENT_DYNAMIC(CAddIPAdressDlg, CDialogEx)

CAddIPAdressDlg::CAddIPAdressDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG1, pParent)
{

}

CAddIPAdressDlg::~CAddIPAdressDlg()
{
}

void CAddIPAdressDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT1, m_input);
}


BEGIN_MESSAGE_MAP(CAddIPAdressDlg, CDialogEx)
	ON_BN_CLICKED(IDOK, &CAddIPAdressDlg::OnBnClickedOk)
	ON_BN_CLICKED(IDCANCEL, &CAddIPAdressDlg::OnBnClickedCancel)
	ON_EN_CHANGE(IDC_EDIT1, &CAddIPAdressDlg::OnEnChangeEdit1)
	ON_WM_NCHITTEST()
END_MESSAGE_MAP()


// CAddIPAdressDlg 消息处理程序

void CAddIPAdressDlg::OnBnClickedOk()
{
	// TODO: 在此添加控件通知处理程序代码
	
	CString str;
	m_input.GetWindowTextW(str);
	if (str.GetLength() == 0) {
		MessageBox(L"请填写IP地址");
		return;
	}
	this->IPAddress = str;
	CDialogEx::OnOK();
}

void CAddIPAdressDlg::OnBnClickedCancel()
{
	// TODO: 在此添加控件通知处理程序代码
	CDialogEx::OnCancel();
}

void CAddIPAdressDlg::OnEnChangeEdit1()
{
	// TODO:  如果该控件是 RICHEDIT 控件，它将不
	// 发送此通知，除非重写 CDialogEx::OnInitDialog()
	// 函数并调用 CRichEditCtrl().SetEventMask()，
	// 同时将 ENM_CHANGE 标志“或”运算到掩码中。

	// TODO:  在此添加控件通知处理程序代码
}

LRESULT CAddIPAdressDlg::OnNcHitTest(CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值

	return HTCAPTION;
}
