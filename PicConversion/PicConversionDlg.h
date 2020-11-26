
// PicConversionDlg.h : 头文件
//

#pragma once


// CPicConversionDlg 对话框
class CPicConversionDlg : public CDialogEx
{
// 构造
public:
	CPicConversionDlg(CWnd* pParent = NULL);	// 标准构造函数

// 对话框数据
	enum { IDD = IDD_PICCONVERSION_DIALOG };

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
	int m_Width;
	int m_Height;
	int m_ByteMode;
	afx_msg void OnBnClickedOk();
	int m_option;
	BOOL Choice(CString filename, CString fileTitle, BYTE *raw8buf, BYTE *raw10buf, BYTE *bmpbuf, int size);

	int CPicConversionDlg::ReadReg(int id, int addr);
	
	afx_msg void OnBnClickedButton1();
	BOOL OV16A1QTools(unsigned char* src, unsigned char* dst, int *otp_dpc);
	CListCtrl m_resultList;
	afx_msg void OnBnClickedButton2();
	afx_msg void OnBnClickedButton3();
	afx_msg void OnBnClickedButton4();
	afx_msg void OnBnClickedButton5();

public:
	void SetOTPLog(CString title,int addr_start,int addr_end,UCHAR *val,CString filename,BYTE* val_byte);
	afx_msg void OnBnClickedButton6();
	int m_ROI;
	afx_msg void OnBnClickedButton7();
	afx_msg void OnBnClickedButton8();
};

BOOL Raw8ToRaw10(unsigned char* raw8, unsigned char* raw10, int width, int height);
BOOL Raw10ToRaw8(unsigned char* raw10, unsigned char* raw8, int width, int height);
BOOL SaveBMP(unsigned char* bmpbuf, int width, int height, CString filetitle);
void BayerConversionFlip( BYTE* pSrcBuffer, BYTE* pDstBuffer, int nImgWidth, int nImgHeight, int bayerType);
BOOL Cell10ToRaw10(unsigned char* cell10buf, int width, int height);
BOOL Cell8ToRaw8(unsigned char* cell8buf, int width, int height);
void RAngleRotation(unsigned char *src, unsigned char *dst, int width, int height);
void RAngleRotation(USHORT *src, USHORT *dst, int width, int height);
void Transpose(unsigned char *src, unsigned char *dst, int width, int height);
void Transpose(USHORT *src, USHORT *dst, int width, int height);
void mirrorTrans(unsigned char *src, unsigned char *dst, int width, int height);
void mirrorTrans(USHORT *src, USHORT *dst, int width, int height);
int ReadSFRFile(char *filename, char *outfilename);