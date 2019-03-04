
// PathModifierDlg.cpp : implementation file
//

#include "stdafx.h"
#include "PathModifier.h"
#include "PathModifierDlg.h"
#include "afxdialogex.h"
#include "LogicalLayer.h"
#include "EditDialog.h"
#include <vector>

using namespace std;

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CAboutDlg dialog used for App About

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

// Implementation
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CPathModifierDlg dialog



CPathModifierDlg::CPathModifierDlg(CWnd* pParent /*=nullptr*/)
	: CDialog(IDD_PATHMODIFIER_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CPathModifierDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST, list_);
}

BEGIN_MESSAGE_MAP(CPathModifierDlg, CDialog)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON_ADD, &CPathModifierDlg::OnBnClickedButtonAdd)
	ON_BN_CLICKED(IDC_BUTTON_DELETE, &CPathModifierDlg::OnBnClickedButtonDelete)
	ON_BN_CLICKED(IDC_BUTTON_MODIFY, &CPathModifierDlg::OnBnClickedButtonModify)
END_MESSAGE_MAP()


// CPathModifierDlg message handlers

BOOL CPathModifierDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != nullptr)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon

	// TODO: Add extra initialization here
	auto v = LogicalLayer::getPathList();
	for (auto s : v)
		list_.AddString(s.c_str());

	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CPathModifierDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialog::OnSysCommand(nID, lParam);
	}
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CPathModifierDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

// The system calls this function to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CPathModifierDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CPathModifierDlg::OnBnClickedButtonAdd()
{
	// TODO: Add your control notification handler code here
	EditDialog dialog;
	if (dialog.DoModal() == IDOK)
	{
		if (list_.FindString(0, dialog.data().c_str()) == LB_ERR)
			list_.AddString(dialog.data().c_str());
		else
			MessageBox(TEXT("The item is already existed."));
	}
}


void CPathModifierDlg::OnBnClickedButtonDelete()
{
	// TODO: Add your control notification handler code here
	auto selected = list_.GetCurSel();
	if (selected == -1)
	{
		MessageBox(TEXT("You muse select an item before you edit."));
		return;
	}
	list_.DeleteString(selected);
}


void CPathModifierDlg::OnBnClickedButtonModify()
{
	// TODO: Add your control notification handler code here
	auto selected = list_.GetCurSel();
	if (selected == -1)
	{
		MessageBox(TEXT("You muse select an item before you edit."));
		return;
	}
	vector<TCHAR> buffer(MAX_PATH);
	list_.GetText(selected, &buffer[0]);
	EditDialog dialog;
	dialog.setData(&buffer[0]);
	if (dialog.DoModal() == IDOK)
	{
		list_.DeleteString(selected);
		list_.InsertString(selected, dialog.data().c_str());
	}
}


void CPathModifierDlg::OnOK()
{
	// TODO: Add your specialized code here and/or call the base class
	auto v = getItems();
	LogicalLayer::setPathList(v);
	CDialog::OnOK();
}

std::vector<tstring> CPathModifierDlg::getItems()
{
	auto count = list_.GetCount();
	vector<tstring> v;
	for (auto i = 0; i != count; ++i)
	{
		vector<TCHAR> buffer(MAX_PATH);
		list_.GetText(i, &buffer[0]);
		v.push_back(&buffer[0]);
	}
	return v;
}
