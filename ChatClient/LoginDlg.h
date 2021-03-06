#pragma once
#include "afxcmn.h"


// CLoginDlg 对话框

class CLoginDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CLoginDlg)

public:
	CLoginDlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CLoginDlg();

// 对话框数据
	enum { IDD = IDD_LOGIN_DIALOG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedBtnLogin();
	CString m_strUsername;
	CIPAddressCtrl m_IPAddressCtrl;
	int m_uPort;
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedBtnCancel();
};
