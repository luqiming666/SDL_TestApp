
// SDL_FirstAppDlg.h: 头文件
//

#pragma once

struct AudioPlaybackData {
	uint8_t* audio_buf;
	uint32_t audio_buf_len;
	uint32_t audio_played_len;
};

// CSDLFirstAppDlg 对话框
class CSDLFirstAppDlg : public CDialogEx
{
// 构造
public:
	CSDLFirstAppDlg(CWnd* pParent = nullptr);	// 标准构造函数

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_SDL_FIRSTAPP_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// 实现
protected:
	HICON m_hIcon;
	CString mSrcFile;

	// Audio
	AudioPlaybackData mAudioPlayData;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()

public:
	afx_msg void OnDestroy();
	afx_msg void OnBnClickedButtonCreateWnd();
	afx_msg void OnBnClickedButtonBrowse();
	afx_msg void OnBnClickedButtonShowPic();
	afx_msg void OnBnClickedButtonPlayAudio();
};
