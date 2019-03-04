#pragma once


// EditDialog dialog

class EditDialog : public CDialog
{
	DECLARE_DYNAMIC(EditDialog)

public:
	EditDialog(CWnd* pParent = nullptr);   // standard constructor
	virtual ~EditDialog();

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_EDIT };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual BOOL OnInitDialog();
	DECLARE_MESSAGE_MAP()
private:
	tstring data_;
public:
	void setData(const tstring& value)
	{
		data_ = value;
	}
	const tstring& data()const
	{
		return data_;
	}
private:
	CEdit editData_;
public:
	afx_msg void OnBnClickedOk();
};
