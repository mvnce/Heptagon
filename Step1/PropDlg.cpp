// PropDlg.cpp : implementation file
//

#include "stdafx.h"
#include "Step1.h"
#include "PropDlg.h"
#include "afxdialogex.h"


// CPropDlg dialog

IMPLEMENT_DYNAMIC(CPropDlg, CDialog)

CPropDlg::CPropDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CPropDlg::IDD, pParent)
	, m_centerx(0)
	, m_centery(0)
	, m_length(0)
	, m_angle(0)
{

}

CPropDlg::~CPropDlg()
{
}

void CPropDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_CTX, m_centerx);
	DDX_Text(pDX, IDC_CTY, m_centery);
	DDX_Text(pDX, IDC_LEN, m_length);
	DDX_Text(pDX, IDC_ANG, m_angle);
}


BEGIN_MESSAGE_MAP(CPropDlg, CDialog)
END_MESSAGE_MAP()


// CPropDlg message handlers
