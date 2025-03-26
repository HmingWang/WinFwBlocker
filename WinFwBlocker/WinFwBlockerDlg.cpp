
// WinFwBlockerDlg.cpp: 实现文件
//

#include "pch.h"
#include "framework.h"
#include "WinFwBlocker.h"
#include "WinFwBlockerDlg.h"
#include "afxdialogex.h"
#include "CNetFwCtrl.h"
#include "CAddIPAdressDlg.h"
#include "AdminUtils.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CWinFwBlockerDlg 对话框



CWinFwBlockerDlg::CWinFwBlockerDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_WINFWBLOCKER_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CWinFwBlockerDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST1, m_listbox);
}

BEGIN_MESSAGE_MAP(CWinFwBlockerDlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON1, &CWinFwBlockerDlg::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON2, &CWinFwBlockerDlg::OnBnClickedButton2)
	ON_BN_CLICKED(IDC_BUTTON3, &CWinFwBlockerDlg::OnBnClickedButton3)
	ON_BN_CLICKED(IDOK, &CWinFwBlockerDlg::OnBnClickedOk)
	ON_BN_CLICKED(IDC_BUTTON4, &CWinFwBlockerDlg::OnBnClickedButton4)
	ON_WM_NCHITTEST()
END_MESSAGE_MAP()


// CWinFwBlockerDlg 消息处理程序

BOOL CWinFwBlockerDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 设置此对话框的图标。  当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO: 在此添加额外的初始化代码
	//检查管理员权限
	// 检查是否已经是管理员权限
	if (!AdminUtils::IsRunAsAdmin()) {
		MessageBox(L"需要管理员权限，正在请求提升...\n");
		AdminUtils::ElevateNow();
	}
	

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。  对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CWinFwBlockerDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作区矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CWinFwBlockerDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void CWinFwBlockerDlg::RemoveDuplicates()
{
	std::set<CString> set;
	int count = m_listbox.GetCount();
	for (int i = 0;i < count;++i) {
		CString tmp;
		m_listbox.GetText(i, tmp);
		set.insert(tmp);
	}

	m_listbox.ResetContent();
	for(auto e:set){
		m_listbox.AddString(e);
	}
}


void CWinFwBlockerDlg::OnBnClickedButton1()
{
	m_listbox.ResetContent();
	
	auto str=cnet.GetRuleRemoteAddress(L"!IP_Block");
	std::vector<std::wstring> list = cnet.ParseRemoteAddresses(str);
	for (auto i : list) {
		m_listbox.AddString(i.c_str());
	}

	RemoveDuplicates();
}

void CWinFwBlockerDlg::OnBnClickedButton2()
{
	// TODO: 在此添加控件通知处理程序代码
	CAddIPAdressDlg dlg;
	INT_PTR ptr= dlg.DoModal();
	if(ptr==IDOK){
		m_listbox.AddString(dlg.IPAddress);
	}
	RemoveDuplicates();
}

void CWinFwBlockerDlg::OnBnClickedButton3()
{
	m_listbox.DeleteString(m_listbox.GetCurSel());
}

void CWinFwBlockerDlg::OnBnClickedOk()
{
	// TODO: 在此添加控件通知处理程序代码
	CDialogEx::OnOK();
}

void CWinFwBlockerDlg::OnBnClickedButton4()
{
	// TODO: 在此添加控件通知处理程序代码
	std::wstring str;
	int count=m_listbox.GetCount();
	for (int i = 0;i < count;++i) {
		CString tmp;
		m_listbox.GetText(i, tmp);
		str = str + L"," + tmp.GetString();
	}
	if (cnet.SetRuleRemoteAddresses(L"!IP_Block", str)) {
		MessageBox(L"保存成功！");
	}
	else {
		MessageBox(L"保存失败！");
	}
}

LRESULT CWinFwBlockerDlg::OnNcHitTest(CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值

	return HTCAPTION;
}
