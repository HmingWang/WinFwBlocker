
// WinFwBlockerDlg.h: 头文件
//

#pragma once
#include "CNetFwCtrl.h"


// CWinFwBlockerDlg 对话框
class CWinFwBlockerDlg : public CDialogEx
{
// 构造
public:
	CWinFwBlockerDlg(CWnd* pParent = nullptr);	// 标准构造函数

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_WINFWBLOCKER_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()

	void RemoveDuplicates();

public:
	afx_msg void OnBnClickedButton1();
private:
	CListBox m_listbox;
	CNetFwCtrl cnet;
public:
	afx_msg void OnBnClickedButton2();
	afx_msg void OnBnClickedButton3();
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedButton4();
	afx_msg LRESULT OnNcHitTest(CPoint point);
};
