// LoginDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "ChatClient.h"
#include "LoginDlg.h"
#include "afxdialogex.h"
#include "ClientSocket.h"


// CLoginDlg 对话框

IMPLEMENT_DYNAMIC(CLoginDlg, CDialogEx)

CLoginDlg::CLoginDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CLoginDlg::IDD, pParent)
	, m_strUsername(_T(""))
	, m_uPort(6680)
{

}

CLoginDlg::~CLoginDlg()
{
}

void CLoginDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, m_strUsername);
	DDX_Control(pDX, IDC_IPADDRESS1, m_IPAddressCtrl);
	DDX_Text(pDX, IDC_EDIT2, m_uPort);
}


BEGIN_MESSAGE_MAP(CLoginDlg, CDialogEx)
	ON_BN_CLICKED(ID_BTN_LOGIN, &CLoginDlg::OnBnClickedBtnLogin)
	ON_BN_CLICKED(ID_BTN_CANCEL, &CLoginDlg::OnBnClickedBtnCancel)
END_MESSAGE_MAP()


// CLoginDlg 消息处理程序



void CLoginDlg::OnBnClickedBtnLogin()
{
	UpdateData(TRUE);
	// TODO:  在此添加控件通知处理程序代码
	if (m_strUsername.IsEmpty()) {
		MessageBox(L"Username cannot be empty.");
		return;
	}


	CString strIPAddress;
	m_IPAddressCtrl.GetWindowText(strIPAddress);

	if (strIPAddress.IsEmpty() || strIPAddress == L"0.0.0.0") {
		MessageBox(L"Please enter IP Address.");
		return;
	}

	if (m_uPort == 0) {
		MessageBox(L"Please enter Port number.");
		return;
	}

	theApp.m_pClientSocket = new CClientSocket;

	if (FALSE == theApp.m_pClientSocket->Create()) {
		CString str;
		str.Format(L"Failed to create socket. Error Code:%d", GetLastError());
		MessageBox(str);
		delete theApp.m_pClientSocket;
		theApp.m_pClientSocket = NULL;
		return;
	}

	if (FALSE == theApp.m_pClientSocket->Connect(strIPAddress, m_uPort)) {
		CString str;
		str.Format(L"Failed to connect with server. Error Code:%d", GetLastError());
		MessageBox(str);
		delete theApp.m_pClientSocket;
		theApp.m_pClientSocket = NULL;
		return;
	}

	Command cmd;
	cmd.cmd = LOGIN;
	cmd.nDataSize = m_strUsername.GetLength() * 2;

	theApp.m_pClientSocket->Send(&cmd, sizeof(cmd));

	theApp.m_pClientSocket->Send(m_strUsername, m_strUsername.GetLength() * 2);

	CLoginDlg::OnOK();
}


BOOL CLoginDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  在此添加额外的初始化
	m_IPAddressCtrl.SetWindowText(_T("192.168.0.20"));

	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常:  OCX 属性页应返回 FALSE
}


void CLoginDlg::OnBnClickedBtnCancel()
{
	// TODO:  在此添加控件通知处理程序代码
	CDialogEx::OnCancel();
}
