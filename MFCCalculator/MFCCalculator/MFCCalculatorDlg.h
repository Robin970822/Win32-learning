
// MFCCalculatorDlg.h : 头文件
//

#pragma once


// CMFCCalculatorDlg 对话框
class CMFCCalculatorDlg : public CDialogEx
{
// 构造
public:
	CMFCCalculatorDlg(CWnd* pParent = NULL);	// 标准构造函数

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_MFCCALCULATOR_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedId0();
	afx_msg void OnBnClickedId1();
	afx_msg void OnBnClickedId2();
	afx_msg void OnBnClickedId3();
	afx_msg void OnBnClickedId4();
	afx_msg void OnBnClickedId5();
	afx_msg void OnBnClickedId6();
	afx_msg void OnBnClickedId7();
	afx_msg void OnBnClickedId8();
	afx_msg void OnBnClickedId9();
	afx_msg void OnBnClickedIdDot();
	afx_msg void OnBnClickedIdAc();
	afx_msg void OnBnClickedIdSqrt();
	afx_msg void OnBnClickedIdMod();
	afx_msg void OnBnClickedIdPlus();
	afx_msg void OnBnClickedIdMinus();
	afx_msg void OnBnClickedIdTimes();
	afx_msg void OnBnClickedIdOver();
	afx_msg void OnBnClickedIdEqual();
	afx_msg void OnMenuFileExit();
};
