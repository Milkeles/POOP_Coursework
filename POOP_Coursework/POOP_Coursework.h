
// POOP_Coursework.h : main header file for the POOP_Coursework application
//
#pragma once

#ifndef __AFXWIN_H__
	#error "include 'pch.h' before including this file for PCH"
#endif

#include "resource.h"       // main symbols


// CPOOPCourseworkApp:
// See POOP_Coursework.cpp for the implementation of this class
//

class CPOOPCourseworkApp : public CWinAppEx
{
public:
	CPOOPCourseworkApp() noexcept;


// Overrides
public:
	virtual BOOL InitInstance();

// Implementation
	UINT  m_nAppLook;
	BOOL  m_bHiColorIcons;

	virtual void PreLoadState();
	virtual void LoadCustomState();
	virtual void SaveCustomState();

	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
};

extern CPOOPCourseworkApp theApp;
