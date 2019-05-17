#include "stdafx.h"
#include "ClientSocket.h"
#include "ChatClientDlg.h"


CClientSocket::CClientSocket()
{
}


CClientSocket::~CClientSocket()
{
}


void CClientSocket::OnReceive(int nErrorCode)
{
	// TODO:  在此添加专用代码和/或调用基类
	Command cmd;
	Receive(&cmd, sizeof(cmd));

	CChatClientDlg* pMainDlg = (CChatClientDlg*)AfxGetMainWnd();


	switch (cmd.cmd) {
	case POSTNEWMESSAGE:{
				  wchar_t newmessage[500] = {0};
				  Receive(newmessage, sizeof(newmessage));
				  pMainDlg->m_history.SetWindowText(newmessage);
	}
		break;
	}
	CSocket::OnReceive(nErrorCode);
}
