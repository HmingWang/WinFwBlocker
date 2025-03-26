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
