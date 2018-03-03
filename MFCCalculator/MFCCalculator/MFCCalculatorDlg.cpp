
// MFCCalculatorDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "MFCCalculator.h"
#include "MFCCalculatorDlg.h"
#include "afxdialogex.h"
#include "operate.h"
#include <mmsystem.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

wstring input_operator;			// 记录前次输入的运算符
bool isEqual = false;		// 是否按下等号


// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 实现
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


// CMFCCalculatorDlg 对话框



CMFCCalculatorDlg::CMFCCalculatorDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_MFCCALCULATOR_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CMFCCalculatorDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CMFCCalculatorDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_WM_SETFOCUS()
	ON_BN_CLICKED(BTN_ID_0, &CMFCCalculatorDlg::OnBnClickedId0)
	ON_BN_CLICKED(BTN_ID_1, &CMFCCalculatorDlg::OnBnClickedId1)
	ON_BN_CLICKED(BTN_ID_2, &CMFCCalculatorDlg::OnBnClickedId2)
	ON_BN_CLICKED(BTN_ID_3, &CMFCCalculatorDlg::OnBnClickedId3)
	ON_BN_CLICKED(BTN_ID_4, &CMFCCalculatorDlg::OnBnClickedId4)
	ON_BN_CLICKED(BTN_ID_5, &CMFCCalculatorDlg::OnBnClickedId5)
	ON_BN_CLICKED(BTN_ID_6, &CMFCCalculatorDlg::OnBnClickedId6)
	ON_BN_CLICKED(BTN_ID_7, &CMFCCalculatorDlg::OnBnClickedId7)
	ON_BN_CLICKED(BTN_ID_8, &CMFCCalculatorDlg::OnBnClickedId8)
	ON_BN_CLICKED(BTN_ID_9, &CMFCCalculatorDlg::OnBnClickedId9)
	ON_BN_CLICKED(BTN_ID_DOT, &CMFCCalculatorDlg::OnBnClickedIdDot)
	ON_BN_CLICKED(BTN_ID_AC, &CMFCCalculatorDlg::OnBnClickedIdAc)
	ON_BN_CLICKED(BTN_ID_SQRT, &CMFCCalculatorDlg::OnBnClickedIdSqrt)
	ON_BN_CLICKED(BTN_ID_MOD, &CMFCCalculatorDlg::OnBnClickedIdMod)
	ON_BN_CLICKED(BTN_ID_PLUS, &CMFCCalculatorDlg::OnBnClickedIdPlus)
	ON_BN_CLICKED(BTN_ID_MINUS, &CMFCCalculatorDlg::OnBnClickedIdMinus)
	ON_BN_CLICKED(BTN_ID_TIMES, &CMFCCalculatorDlg::OnBnClickedIdTimes)
	ON_BN_CLICKED(BTN_ID_OVER, &CMFCCalculatorDlg::OnBnClickedIdOver)
	ON_BN_CLICKED(BTN_ID_EQUAL, &CMFCCalculatorDlg::OnBnClickedIdEqual)
	ON_COMMAND(IDR_MENU_FILE_EXIT, &CMFCCalculatorDlg::OnMenuFileExit)
END_MESSAGE_MAP()


// CMFCCalculatorDlg 消息处理程序

BOOL CMFCCalculatorDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 将“关于...”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
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

	CMenu m_Menu;
	m_Menu.LoadMenu(IDR_MENU1);
	SetMenu(&m_Menu);

	// 设置此对话框的图标。  当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO: 在此添加额外的初始化代码
	CFont *m_Font = new CFont;
	m_Font->CreateFont(80, 35, 0, 0, 100,
		FALSE, FALSE,0, ANSI_CHARSET, OUT_DEFAULT_PRECIS,
		CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, FF_SWISS, _T("Segoe UI Bold"));
	CStatic* screen_hwnd_main = (CStatic*)GetDlgItem(SCREEN_MAIN);
	CStatic* screen_hwnd_sub = (CStatic*)GetDlgItem(SCREEN_SUB);
	screen_hwnd_main->SetFont(m_Font);
	screen_hwnd_main->SetWindowText(_T("0"));
	screen_hwnd_sub->SetWindowText(_T(""));

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CMFCCalculatorDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。  对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CMFCCalculatorDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作区矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CMFCCalculatorDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


void CMFCCalculatorDlg::OnBnClickedId0()
{
	// TODO: 在此添加控件通知处理程序代码
	CStatic* screen_main = (CStatic*)GetDlgItem(SCREEN_MAIN);
	CStatic* screen_sub = (CStatic*)GetDlgItem(SCREEN_SUB);
	wstring input = _T("0");
	Number(screen_main, screen_sub, input, input_operator, isEqual);
}


void CMFCCalculatorDlg::OnBnClickedId1()
{
	// TODO: 在此添加控件通知处理程序代码
	CStatic* screen_main = (CStatic*)GetDlgItem(SCREEN_MAIN);
	CStatic* screen_sub = (CStatic*)GetDlgItem(SCREEN_SUB);
	wstring input = _T("1");
	Number(screen_main, screen_sub, input, input_operator, isEqual);
}


void CMFCCalculatorDlg::OnBnClickedId2()
{
	// TODO: 在此添加控件通知处理程序代码
	CStatic* screen_main = (CStatic*)GetDlgItem(SCREEN_MAIN);
	CStatic* screen_sub = (CStatic*)GetDlgItem(SCREEN_SUB);
	wstring input = _T("2");
	Number(screen_main, screen_sub, input, input_operator, isEqual);
}


void CMFCCalculatorDlg::OnBnClickedId3()
{
	// TODO: 在此添加控件通知处理程序代码
	CStatic* screen_main = (CStatic*)GetDlgItem(SCREEN_MAIN);
	CStatic* screen_sub = (CStatic*)GetDlgItem(SCREEN_SUB);
	wstring input = _T("3");
	Number(screen_main, screen_sub, input, input_operator, isEqual);
}


void CMFCCalculatorDlg::OnBnClickedId4()
{
	// TODO: 在此添加控件通知处理程序代码
	CStatic* screen_main = (CStatic*)GetDlgItem(SCREEN_MAIN);
	CStatic* screen_sub = (CStatic*)GetDlgItem(SCREEN_SUB);
	wstring input = _T("4");
	Number(screen_main, screen_sub, input, input_operator, isEqual);
}


void CMFCCalculatorDlg::OnBnClickedId5()
{
	// TODO: 在此添加控件通知处理程序代码
	CStatic* screen_main = (CStatic*)GetDlgItem(SCREEN_MAIN);
	CStatic* screen_sub = (CStatic*)GetDlgItem(SCREEN_SUB);
	wstring input = _T("5");
	Number(screen_main, screen_sub, input, input_operator, isEqual);
}


void CMFCCalculatorDlg::OnBnClickedId6()
{
	// TODO: 在此添加控件通知处理程序代码
	CStatic* screen_main = (CStatic*)GetDlgItem(SCREEN_MAIN);
	CStatic* screen_sub = (CStatic*)GetDlgItem(SCREEN_SUB);
	wstring input = _T("6");
	Number(screen_main, screen_sub, input, input_operator, isEqual);
}


void CMFCCalculatorDlg::OnBnClickedId7()
{
	// TODO: 在此添加控件通知处理程序代码
	CStatic* screen_main = (CStatic*)GetDlgItem(SCREEN_MAIN);
	CStatic* screen_sub = (CStatic*)GetDlgItem(SCREEN_SUB);
	wstring input = _T("7");
	Number(screen_main, screen_sub, input, input_operator, isEqual);
}


void CMFCCalculatorDlg::OnBnClickedId8()
{
	// TODO: 在此添加控件通知处理程序代码
	CStatic* screen_main = (CStatic*)GetDlgItem(SCREEN_MAIN);
	CStatic* screen_sub = (CStatic*)GetDlgItem(SCREEN_SUB);
	wstring input = _T("8");
	Number(screen_main, screen_sub, input, input_operator, isEqual);
}


void CMFCCalculatorDlg::OnBnClickedId9()
{
	// TODO: 在此添加控件通知处理程序代码
	CStatic* screen_main = (CStatic*)GetDlgItem(SCREEN_MAIN);
	CStatic* screen_sub = (CStatic*)GetDlgItem(SCREEN_SUB);
	wstring input = _T("9");
	Number(screen_main, screen_sub, input, input_operator, isEqual);
}


void CMFCCalculatorDlg::OnBnClickedIdDot()
{
	// TODO: 在此添加控件通知处理程序代码
	CStatic* screen_main = (CStatic*)GetDlgItem(SCREEN_MAIN);
	CStatic* screen_sub = (CStatic*)GetDlgItem(SCREEN_SUB);
	Dot(screen_main, screen_sub, isEqual);
}


void CMFCCalculatorDlg::OnBnClickedIdAc()
{
	// TODO: 在此添加控件通知处理程序代码
	input_operator.clear();
	CStatic* screen_main = (CStatic*)GetDlgItem(SCREEN_MAIN);
	CStatic* screen_sub = (CStatic*)GetDlgItem(SCREEN_SUB);
	Clear(screen_main, screen_sub, isEqual);
}


void CMFCCalculatorDlg::OnBnClickedIdSqrt()
{
	// TODO: 在此添加控件通知处理程序代码
	CStatic* screen_main = (CStatic*)GetDlgItem(SCREEN_MAIN);
	CStatic* screen_sub = (CStatic*)GetDlgItem(SCREEN_SUB);
	Sqrt(screen_main, screen_sub, isEqual);
}


void CMFCCalculatorDlg::OnBnClickedIdMod()
{
	// TODO: 在此添加控件通知处理程序代码
	CStatic* screen_main = (CStatic*)GetDlgItem(SCREEN_MAIN);
	CStatic* screen_sub = (CStatic*)GetDlgItem(SCREEN_SUB);
	input_operator = _T("%");
	Operator(screen_main, screen_sub, input_operator, isEqual);
}


void CMFCCalculatorDlg::OnBnClickedIdPlus()
{
	// TODO: 在此添加控件通知处理程序代码
	CStatic* screen_main = (CStatic*)GetDlgItem(SCREEN_MAIN);
	CStatic* screen_sub = (CStatic*)GetDlgItem(SCREEN_SUB);
	input_operator = _T("+");
	Operator(screen_main, screen_sub, input_operator, isEqual);
}


void CMFCCalculatorDlg::OnBnClickedIdMinus()
{
	// TODO: 在此添加控件通知处理程序代码
	CStatic* screen_main = (CStatic*)GetDlgItem(SCREEN_MAIN);
	CStatic* screen_sub = (CStatic*)GetDlgItem(SCREEN_SUB);
	input_operator = _T("-");
	Operator(screen_main, screen_sub, input_operator, isEqual);
}


void CMFCCalculatorDlg::OnBnClickedIdTimes()
{
	// TODO: 在此添加控件通知处理程序代码
	CStatic* screen_main = (CStatic*)GetDlgItem(SCREEN_MAIN);
	CStatic* screen_sub = (CStatic*)GetDlgItem(SCREEN_SUB);
	input_operator = _T("*");
	Operator(screen_main, screen_sub, input_operator, isEqual);
}


void CMFCCalculatorDlg::OnBnClickedIdOver()
{
	// TODO: 在此添加控件通知处理程序代码
	CStatic* screen_main = (CStatic*)GetDlgItem(SCREEN_MAIN);
	CStatic* screen_sub = (CStatic*)GetDlgItem(SCREEN_SUB);
	input_operator = _T("/");
	Operator(screen_main, screen_sub, input_operator, isEqual);
}


void CMFCCalculatorDlg::OnBnClickedIdEqual()
{
	// TODO: 在此添加控件通知处理程序代码
	CStatic* screen_main = (CStatic*)GetDlgItem(SCREEN_MAIN);
	CStatic* screen_sub = (CStatic*)GetDlgItem(SCREEN_SUB);
	input_operator = _T("=");
	Operator(screen_main, screen_sub, input_operator, isEqual);
}

void CMFCCalculatorDlg::OnMenuFileExit()
{
	DestroyWindow();
}
