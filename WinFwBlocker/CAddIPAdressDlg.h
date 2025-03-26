#pragma once
#include "afxdialogex.h"


// CAddIPAdressDlg 对话框

class CAddIPAdressDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CAddIPAdressDlg)

public:
	CAddIPAdressDlg(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~CAddIPAdressDlg();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG1 };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
private:
	CEdit m_input;
public:
	afx_msg void OnBnClickedOk();
	CString IPAddress;
	afx_msg void OnBnClickedCancel();
};
