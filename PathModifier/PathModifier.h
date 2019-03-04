
// PathModifier.h : main header file for the PROJECT_NAME application
//

#pragma once

#ifndef __AFXWIN_H__
	#error "include 'stdafx.h' before including this file for PCH"
#endif

#include "resource.h"		// main symbols


// CPathModifierApp:
// See PathModifier.cpp for the implementation of this class
//

class CPathModifierApp : public CWinApp
{
public:
	CPathModifierApp();

// Overrides
public:
	virtual BOOL InitInstance();

// Implementation

	DECLARE_MESSAGE_MAP()
};

extern CPathModifierApp theApp;
