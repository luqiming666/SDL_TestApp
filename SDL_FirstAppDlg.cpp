
// SDL_FirstAppDlg.cpp: 实现文件
//

#include "pch.h"
#include "framework.h"
#include "SDL_FirstApp.h"
#include "SDL_FirstAppDlg.h"
#include "afxdialogex.h"
#include <iostream>

#include "SDL.h"
#include "audiotest.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


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


// CSDLFirstAppDlg 对话框

CSDLFirstAppDlg::CSDLFirstAppDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_SDL_FIRSTAPP_DIALOG, pParent)
	, mSrcFile(_T(""))
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CSDLFirstAppDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_SRC_FILE, mSrcFile);
}

BEGIN_MESSAGE_MAP(CSDLFirstAppDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_WM_DESTROY()
	ON_BN_CLICKED(IDC_BUTTON_CREATE_WND, &CSDLFirstAppDlg::OnBnClickedButtonCreateWnd)
	ON_BN_CLICKED(IDC_BUTTON_BROWSE, &CSDLFirstAppDlg::OnBnClickedButtonBrowse)
	ON_BN_CLICKED(IDC_BUTTON_SHOW_PIC, &CSDLFirstAppDlg::OnBnClickedButtonShowPic)
	ON_BN_CLICKED(IDC_BUTTON_PLAY_AUDIO, &CSDLFirstAppDlg::OnBnClickedButtonPlayAudio)
END_MESSAGE_MAP()


// CSDLFirstAppDlg 消息处理程序

BOOL CSDLFirstAppDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 将“关于...”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
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

	// 设置此对话框的图标。  当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO: 在此添加额外的初始化代码
	if (::GetConsoleWindow() == NULL)
	{
		if (::AllocConsole())
		{
			FILE* stream;
			freopen_s(&stream, "CONOUT$", "w", stdout);
		}
	}

	if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) < 0) {
		std::cerr << "Failed to initialize SDL: " << SDL_GetError() << std::endl;
		return FALSE;
	}

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CSDLFirstAppDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CSDLFirstAppDlg::OnPaint()
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
HCURSOR CSDLFirstAppDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void CSDLFirstAppDlg::OnDestroy()
{
	CDialogEx::OnDestroy();

	SDL_Quit();
}

void CSDLFirstAppDlg::OnBnClickedButtonBrowse()
{
	CFileDialog fileDlg(TRUE, NULL, NULL, OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT,
		_T("Video Files|*.mp4;*.mpg;*.avi;*.wmv;*.mov|\
		Audio Files|*.wav|\
		Image Files|*.bmp|\
		All Files (*.*)|*.*||"),
		NULL);
	if (fileDlg.DoModal() == IDOK)
	{
		mSrcFile = fileDlg.GetPathName();
		UpdateData(FALSE);
	}
}

void CSDLFirstAppDlg::OnBnClickedButtonShowPic()
{
	//mSrcFile = _T("D:\\a.bmp");
	if (mSrcFile.IsEmpty()) {
		AfxMessageBox("Please select an image file.");
		return;
	}

	SDL_Surface* pPicSurface = SDL_LoadBMP((LPCTSTR)mSrcFile); // 加载图片  
	if (pPicSurface == NULL) {
		std::cout << "Unable to load image! SDL Error: " << SDL_GetError() << std::endl;
		return;
	}

	// 绑定窗口
	SDL_Window* window = SDL_CreateWindowFrom(this->GetDlgItem(IDC_STATIC_SDLPIC)->GetSafeHwnd());
	if (!window) {
		std::cout << "Failed to create SDL window: " << SDL_GetError() << std::endl;
		return;
	}

	// 获取窗口对应的surface 
	SDL_Surface* pWndSurface = SDL_GetWindowSurface(window);
	//SDL_BlitSurface(pPicSurface, NULL, pWndSurface, NULL);
	SDL_BlitScaled(pPicSurface, NULL, pWndSurface, NULL);
	SDL_UpdateWindowSurface(window);

	SDL_DestroyWindow(window);
}

void CSDLFirstAppDlg::OnBnClickedButtonCreateWnd()
{
}

void audio_callback(void* userdata, Uint8* stream, int len) 
{
	AudioPlaybackData* pData = (AudioPlaybackData*)userdata;
	if (pData->isCompleted()) return;

	// 从音频缓冲区复制数据到播放流
	Uint32 remaining_len = pData->audio_buf_len - pData->audio_played_len;
	Uint32 copy_len = (len > remaining_len) ? remaining_len : len;
	memcpy(stream, pData->audio_buf + pData->audio_played_len, copy_len);

	// 如果还有剩余数据，需要进行适当处理，比如填充静音数据
	if (copy_len < len) {
		memset(stream + copy_len, 0, len - copy_len);
	}

	// 记录已经播放的数据量
	pData->audio_played_len += len;
}

//#define _TEST_jakebesworth_
// Many thanks to https://github.com/jakebesworth/Simple-SDL2-Audio
// 注意：编译.c文件时，单独设置“属性”不要使用预编译头
// Win10：重新定义 #define SDL_AUDIO_ALLOW_CHANGES (SDL_AUDIO_ALLOW_FREQUENCY_CHANGE | SDL_AUDIO_ALLOW_CHANNELS_CHANGE)

void CSDLFirstAppDlg::OnBnClickedButtonPlayAudio()
{
#ifdef _TEST_jakebesworth_	
	test_audio_main();
	return;
#endif

	//mSrcFile = _T("D:\\Media\\Bomb.wav");
	if (mSrcFile.IsEmpty()) {
		AfxMessageBox("Please select an audio file.");
		return;
	}

	SDL_AudioSpec audio_spec;
	if (SDL_LoadWAV((LPCTSTR)mSrcFile, &audio_spec, &mAudioPlayData.audio_buf, &mAudioPlayData.audio_buf_len) == NULL) {
		std::cout << "Failed to load audio file: " << SDL_GetError() << std::endl;
		return;
	}

	audio_spec.callback = audio_callback; // 音频回调函数
	audio_spec.userdata = &mAudioPlayData; // 用户数据
	if (SDL_OpenAudio(&audio_spec, NULL) < 0) {
		std::cout << "Failed to open audio device: " << SDL_GetError() << std::endl;
		SDL_FreeWAV(mAudioPlayData.audio_buf);
		mAudioPlayData.audio_buf = NULL;
		return;
	}

	mAudioPlayData.prepare();
	SDL_PauseAudio(0);   // 开始播放音频，0表示取消暂停

	// Wait till the audio playback finishes
	// ...
	SDL_Delay(2000);

	SDL_CloseAudio();    // 关闭音频设备
	SDL_FreeWAV(mAudioPlayData.audio_buf);   // 释放音频缓冲区
}
