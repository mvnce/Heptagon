
// Step1.h : main header file for the Step1 application
//
#pragma once

#ifndef __AFXWIN_H__
	#error "include 'stdafx.h' before including this file for PCH"
#endif

#include "resource.h"       // main symbols


// CStep1App:
// See Step1.cpp for the implementation of this class
//

class CStep1App : public CWinAppEx
{
public:
	CStep1App();


// Overrides
public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();

// Implementation

public:
	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
};

extern CStep1App theApp;
