#pragma once

#include "afxdialogex.h"

// CPopup dialog

class CPopup : public CDialogEx
{
	DECLARE_DYNAMIC(CPopup)

public:
	CPopup(CWnd* pParent = nullptr);   // standard constructor
	virtual ~CPopup();
	CSliderCtrl m_slider;
	CString m_msg1;
	CString m_msg2;
	CString m_msg3;

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG1 };
#endif

protected:
	BOOL OnInitDialog() override;
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	int m_sliderval;
	afx_msg void OnNMCustomdrawSlider1(NMHDR* pNMHDR, LRESULT* pResult);
};

//////////////////////////////////////////////////////////
///////////////////////////////////////////////////////
////////////////////////////////////////////////////////


// CPopupOrtho dialog

class CPopupOrtho : public CDialogEx
{
	DECLARE_DYNAMIC(CPopupOrtho)

public:
	CPopupOrtho(CWnd* pParent = nullptr);   // standard constructor
	virtual ~CPopupOrtho();
	CString m_msg1;
	CString m_msg2;
	CString m_msg3;
	CString m_msg4;

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG2 };
#endif

protected:
	BOOL OnInitDialog() override;
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
};