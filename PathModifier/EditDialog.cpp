// EditDialog.cpp : implementation file
//

#include "stdafx.h"
#include "PathModifier.h"
#include "EditDialog.h"
#include "afxdialogex.h"
#include <vector>

using namespace std;

// EditDialog dialog

IMPLEMENT_DYNAMIC(EditDialog, CDialog)

EditDialog::EditDialog(CWnd* pParent /*=nullptr*/)
	: CDialog(IDD_DIALOG_EDIT, pParent)
{

}

EditDialog::~EditDialog()
{
}

void EditDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT_TEXT, editData_);
}


BEGIN_MESSAGE_MAP(EditDialog, CDialog)
	ON_BN_CLICKED(IDOK, &EditDialog::OnBnClickedOk)
END_MESSAGE_MAP()


// EditDialog message handlers

BOOL EditDialog::OnInitDialog()
{
	UpdateData(FALSE);
	editData_.SetWindowText(data_.c_str());
	return TRUE;
}


void EditDialog::OnBnClickedOk()
{
	// TODO: Add your control notification handler code here
	auto length = editData_.GetWindowTextLength();
	vector<TCHAR> v(length + 1);
	editData_.GetWindowText(&v[0], length + 1);
	setData(&v[0]);
	CDialog::OnOK();
}
