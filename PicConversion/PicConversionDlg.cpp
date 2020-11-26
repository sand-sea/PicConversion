
// PicConversionDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include <iostream>
#include <io.h>
#include "PicConversion.h"
#include "PicConversionDlg.h"
#include <string>
#include "OV4CellLib.h"
#include <direct.h>
#include <fstream>


using namespace std;
#pragma comment(lib, "OV4CellLib.lib")

#include "afxdialogex.h"
#pragma warning(disable:4996)
#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// ����Ӧ�ó��򡰹��ڡ��˵���� CAboutDlg �Ի���

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// �Ի�������
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

// ʵ��
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CPicConversionDlg �Ի���




CPicConversionDlg::CPicConversionDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CPicConversionDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	m_Width = 0;
	m_Height = 0;
	m_ByteMode = 0;
	m_option = 0;
	m_ROI = 0;
}

void CPicConversionDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_Width, m_Width);
	DDX_Text(pDX, IDC_Height, m_Height);
	DDX_CBIndex(pDX, IDC_ByteMode, m_ByteMode);
	DDX_Radio(pDX, IDC_RADIO1, m_option);
	DDX_Control(pDX, IDC_LIST1, m_resultList);
	DDX_Text(pDX, IDC_ROI, m_ROI);
}

BEGIN_MESSAGE_MAP(CPicConversionDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDOK, &CPicConversionDlg::OnBnClickedOk)
	ON_BN_CLICKED(IDC_BUTTON1, &CPicConversionDlg::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON2, &CPicConversionDlg::OnBnClickedButton2)
	ON_BN_CLICKED(IDC_BUTTON3, &CPicConversionDlg::OnBnClickedButton3)
	ON_BN_CLICKED(IDC_BUTTON4, &CPicConversionDlg::OnBnClickedButton4)
	ON_BN_CLICKED(IDC_BUTTON5, &CPicConversionDlg::OnBnClickedButton5)
	ON_BN_CLICKED(IDC_BUTTON6, &CPicConversionDlg::OnBnClickedButton6)
	ON_BN_CLICKED(IDC_BUTTON7, &CPicConversionDlg::OnBnClickedButton7)
	ON_BN_CLICKED(IDC_BUTTON8, &CPicConversionDlg::OnBnClickedButton8)
END_MESSAGE_MAP()


// CPicConversionDlg ��Ϣ�������

BOOL CPicConversionDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// ��������...���˵�����ӵ�ϵͳ�˵��С�

	// IDM_ABOUTBOX ������ϵͳ���Χ�ڡ�
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

	// ���ô˶Ի����ͼ�ꡣ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��

	// TODO: �ڴ���Ӷ���ĳ�ʼ������
	
	m_resultList.SetExtendedStyle(LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);
	m_resultList.InsertColumn(0, _T(""), LVCFMT_CENTER, 0);
	m_resultList.InsertColumn(1, _T("�ļ���"), LVCFMT_CENTER, 200);
	m_resultList.InsertColumn(2, _T("ת��״̬"), LVCFMT_CENTER, 100);
	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
}

void CPicConversionDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CPicConversionDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // ���ڻ��Ƶ��豸������

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// ʹͼ���ڹ����������о���
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// ����ͼ��
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//���û��϶���С������ʱϵͳ���ô˺���ȡ�ù��
//��ʾ��
HCURSOR CPicConversionDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


//�ļ���ת��
void CPicConversionDlg::OnBnClickedOk()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	UpdateData(TRUE);
	if (m_Width <= 0 || m_Height <= 0)
	{
		AfxMessageBox(L"���߲����Ϲ��");
		return;
	}
	BYTE* raw8buf = new BYTE[m_Width * m_Height];
	BYTE* raw10buf = new BYTE[m_Width * m_Height * 2];
	BYTE* bmpbuf = new BYTE[m_Width * m_Height * 3];
	/*int *otp_dpc = new int[4096];
	FILE *file;
	file = fopen("123456.txt", "rb+");
	for (int i = 0; i < 4096; i++)
	{
		fscanf(file, "%d", &otp_dpc[i]);
	}
	fclose(file);*/
	CFolderPickerDialog dlg;
	if(dlg.DoModal() != IDCANCEL)
	{
		CFileFind finder;
		CString dirPath;
		CString filePath;
		CString outPath;
		dirPath = dlg.GetPathName();
		filePath = dirPath + L"\\*.raw";
		outPath = dirPath + L"\\OutFile";
		USES_CONVERSION;
		SetCurrentDirectoryA(T2A(dirPath));
		BOOL work = finder.FindFile(filePath);
		if (work)
		{
			int sta = 0;
			CString fileTitle;
			CString filename;
			CString ToFileName;
			int size = 0;
			m_resultList.DeleteAllItems();
			int i = 0;
			while (work)
			{
				work = finder.FindNextFileW();
				filename = finder.GetFileName();
				fileTitle = finder.GetFileTitle();
				size = finder.GetLength();
				BOOL state;
				state = FALSE;
				
				state = Choice(filename, fileTitle, raw8buf, raw10buf, bmpbuf, size);
#if 0

				else if (m_option == 6)
				{
					//OV����
					sta = m_Width * m_Height * 2;
					if (sta == size)
					{
						USES_CONVERSION;
						file = fopen(T2A(filename), "rb+");
						fread(raw10buf, 1, size, file);
						fclose(file);
						ToFileName = fileTitle + L"_ov.raw";
						state = OV16A1QTools(raw10buf, ov, otp_dpc);
						if (state == FALSE)
						{
							finder.Close();
							break;
						}
						file = fopen(T2A(ToFileName), "wb");
						fwrite(ov, 1, size, file);
						fclose(file);
					}
				}
#endif
				
				
				
				m_resultList.InsertItem(i, _T(""));
				m_resultList.SetItemText(i, 1, filename);
				
				if (state == FALSE)
				{
					m_resultList.SetItemText(i, 2, _T("---ʧ��---"));
				}
				else if (state == TRUE)
				{
					m_resultList.SetItemText(i, 2, _T("�ɹ�"));
				}
				i++;
			}
			finder.Close();
		}
//		delete[] otp_dpc;
	}
	delete[] raw8buf;
	delete[] raw10buf;
	delete[] bmpbuf;
	//CString filter = L"(*.raw)|*.raw||";
	//CFileDialog dlg(TRUE, NULL, NULL, OFN_ALLOWMULTISELECT, filter, NULL);
	//if (IDCANCEL != dlg.DoModal())
	//{
	//	CString filename;
	//	CString filepath;
	//	CString extName;
	//	CString filetitle;
	//	filename = dlg.GetFileName();
	//	extName = dlg.GetFileExt();
	//	filepath = dlg.GetPathName();
	//	filetitle = dlg.GetFileTitle();
	//	SetCurrentDirectory(filepath);
	//	int size = m_Width * m_Height;
	//	CString ToFileName;
	//	unsigned char* raw8buf;
	//	unsigned char* raw10buf;
	//	raw8buf = new unsigned char[size];
	//	raw10buf = new unsigned char[size * 2];
	//	FILE *file;
	//	if (m_option == 0)
	//	{
	//		//R8ToR10
	//		USES_CONVERSION;
	//		file = fopen(T2A(filename), "rb+");
	//		fread(raw8buf, 1, size, file);
	//		fclose(file);
	//		if (0 != access("OutRaw10File", 0))
	//		{
	//			// if this folder not exist, create a new one.
	//			mkdir("OutRaw10File");   // ���� 0 ��ʾ�����ɹ���-1 ��ʾʧ��
	//			//���� ::_mkdir  ::_access Ҳ�У���֪��ʲô��˼
	//		}
	//		Raw8ToRaw10(raw8buf, raw10buf, m_Width, m_Height);
	//		ToFileName = filetitle + L"_r10.raw";
	//		file = fopen(T2A(ToFileName), "wb+");
	//		fwrite(raw10buf, 1, size * 2, file);
	//		fclose(file);
	//	}
	//	else if (m_option == 1)
	//	{
	//		//R10T0R8
	//		USES_CONVERSION;
	//		file = fopen(T2A(filename), "rb+");
	//		fread(raw10buf, 1, size * 2, file);
	//		fclose(file);
	//		Raw10ToRaw8(raw10buf, raw8buf, m_Width, m_Height);
	//		ToFileName = filetitle + L"_r8.raw";
	//		file = fopen(T2A(ToFileName), "wb+");
	//		fwrite(raw8buf, 1, size, file);
	//		fclose(file);
	//	}
	//	else if(m_option == 2)
	//	{
	//		//R8ToBMP
	//		USES_CONVERSION;
	//		file = fopen(T2A(filename), "rb+");
	//		fread(raw8buf, 1, size, file);
	//		fclose(file);
	//		ToFileName = filetitle + L"_BMP.bmp";
	//		Raw8ToBMP(raw8buf, m_Width, m_Height, m_ByteMode, ToFileName);
	//	}
	//	else if(m_option == 3)
	//	{
	//		//R10ToBMP
	//		USES_CONVERSION;
	//		file = fopen(T2A(filename), "rb+");
	//		fread(raw10buf, 1, size * 2, file);
	//		fclose(file);
	//		ToFileName = filetitle + L"_BMP.bmp";
	//		Raw10ToRaw8(raw10buf, raw8buf, m_Width, m_Height);
	//		Raw8ToBMP(raw8buf, m_Width, m_Height, m_ByteMode, ToFileName);
	//	}
	//	else if (m_option == 4)
	//	{
	//		USES_CONVERSION;
	//		file = fopen(T2A(filename), "rb+");
	//		fread(raw8buf, 1, size, file);
	//		fclose(file);
	//		ToFileName = filetitle + L"_r8.raw";
	//		Cell8ToRaw8(raw8buf, m_Width, m_Height);
	//		file = fopen(T2A(ToFileName), "wb+");
	//		fwrite(raw8buf, 1, size, file);
	//		fclose(file);
	//	}
	//	else if (m_option == 5)
	//	{
	//		USES_CONVERSION;
	//		file = fopen(T2A(filename), "rb+");
	//		fread(raw10buf, 1, size * 2, file);
	//		fclose(file);
	//		ToFileName = filetitle + L"_r10.raw";
	//		Cell10ToRaw10(raw10buf, m_Width, m_Height);
	//		file = fopen(T2A(ToFileName), "wb+");
	//		fwrite(raw10buf, 1, size * 2, file);
	//		fclose(file);
	//	}
	//}
}

//��ѡ��
BOOL CPicConversionDlg::Choice(CString filename, CString fileTitle, BYTE *raw8buf, BYTE *raw10buf, BYTE *bmpbuf, int size)
{
	BOOL state;
	state = FALSE;
	int sta = 0;
	FILE *file = NULL;
	CString ToFileName = NULL;
	if(m_option == 0)
	{
		//R8ToR10
		sta = m_Width * m_Height;
		if (size == sta)
		{
			USES_CONVERSION;
			file = fopen(T2A(filename), "rb+");
			fread(raw8buf, 1, size, file);
			fclose(file);
			state = Raw8ToRaw10(raw8buf, raw10buf, m_Width, m_Height);
			if (0 != access("OutRaw10File", 0))
			{
				// if this folder not exist, create a new one.
				mkdir("OutRaw10File");   // ���� 0 ��ʾ�����ɹ���-1 ��ʾʧ��
				//���� ::_mkdir  ::_access Ҳ�У���֪��ʲô��˼
			}
			ToFileName = L"OutRaw10File\\" + fileTitle + L"_r10.raw";
			file = fopen(T2A(ToFileName), "wb");
			fwrite(raw10buf, 1, size * 2, file);
			fclose(file);
		}
	}
	else if (m_option == 1)
	{
		//R10ToR8
		sta = m_Width * m_Height * 2;
		if (size == sta)
		{
			USES_CONVERSION;
			file = fopen(T2A(filename), "rb+");
			fread(raw10buf, 1, size, file);
			fclose(file);
			state = Raw10ToRaw8(raw10buf, raw8buf, m_Width, m_Height);
			if (0 != access("OutRaw8File", 0))
			{
				// if this folder not exist, create a new one.
				mkdir("OutRaw8File");   // ���� 0 ��ʾ�����ɹ���-1 ��ʾʧ��
				//���� ::_mkdir  ::_access Ҳ�У���֪��ʲô��˼
			}
			ToFileName = L"OutRaw8File\\" + fileTitle + L"_r8.raw";
			file = fopen(T2A(ToFileName), "wb");
			fwrite(raw8buf, 1, size / 2, file);
			fclose(file);
		}
	}
	else if(m_option == 2)
	{
		//R8ToBMP
		sta = m_Width * m_Height;
		if (sta == size)
		{
			USES_CONVERSION;
			file = fopen(T2A(filename), "rb+");
			fread(raw8buf, 1, size, file);
			fclose(file);
			if (0 != access("OutRaw8BMPFile", 0))
			{
				// if this folder not exist, create a new one.
				mkdir("OutRaw8BMPFile");   // ���� 0 ��ʾ�����ɹ���-1 ��ʾʧ��
				//���� ::_mkdir  ::_access Ҳ�У���֪��ʲô��˼
			}
			ToFileName = L"OutRaw8BMPFile\\" + fileTitle + L"_BMP.bmp";
			BayerConversionFlip(raw8buf, bmpbuf, m_Width, m_Height,  m_ByteMode);
			state = SaveBMP(bmpbuf, m_Width, m_Height, ToFileName);
		}
	}
	else if(m_option == 3)
	{
		//R10ToBMP
		sta = m_Width * m_Height * 2;
		if (sta == size)
		{
			USES_CONVERSION;
			file = fopen(T2A(filename), "rb+");
			fread(raw10buf, 1, size, file);
			fclose(file);
			if (0 != access("OutRaw10BMPFile", 0))
			{
				// if this folder not exist, create a new one.
				mkdir("OutRaw10BMPFile");   // ���� 0 ��ʾ�����ɹ���-1 ��ʾʧ��
				//���� ::_mkdir  ::_access Ҳ�У���֪��ʲô��˼
			}
			ToFileName = L"OutRaw10BMPFile\\" + fileTitle + L"_BMP.bmp";
			Raw10ToRaw8(raw10buf, raw8buf, m_Width, m_Height);
			BayerConversionFlip(raw8buf, bmpbuf, m_Width, m_Height,  m_ByteMode);
			state = SaveBMP(bmpbuf, m_Width, m_Height, ToFileName);
		}
	}
	else if (m_option == 4)
	{
		//4CellR8ToBayerR8
		sta = m_Width * m_Height;
		if (sta == size)
		{
			USES_CONVERSION;
			file = fopen(T2A(filename), "rb+");
			fread(raw8buf, 1, size, file);
			fclose(file);
			if (0 != access("Out4CellRaw8File", 0))
			{
				// if this folder not exist, create a new one.
				mkdir("Out4CellRaw8File");   // ���� 0 ��ʾ�����ɹ���-1 ��ʾʧ��
				//���� ::_mkdir  ::_access Ҳ�У���֪��ʲô��˼
			}
			ToFileName = L"Out4CellRaw8File\\" + fileTitle + L"_r8.raw";
			state = Cell8ToRaw8(raw8buf, m_Width, m_Height);
			file = fopen(T2A(ToFileName), "wb");
			fwrite(raw8buf, 1, size, file);
			fclose(file);
		}
	}
	else if (m_option == 5)
	{
		//4CellR10ToBayerR10
		sta = m_Width * m_Height * 2;
		if (sta == size)
		{
			USES_CONVERSION;
			file = fopen(T2A(filename), "rb+");
			fread(raw10buf, 1, size, file);
			fclose(file);
			if (0 != access("Out4CellRaw10File", 0))
			{
				// if this folder not exist, create a new one.
				mkdir("Out4CellRaw10File");   // ���� 0 ��ʾ�����ɹ���-1 ��ʾʧ��
				//���� ::_mkdir  ::_access Ҳ�У���֪��ʲô��˼
			}
			ToFileName = L"Out4CellRaw10File\\" + fileTitle + L"_r10.raw";
			state = Cell10ToRaw10(raw10buf, m_Width, m_Height);
			file = fopen(T2A(ToFileName), "wb");
			fwrite(raw10buf, 1, size, file);
			fclose(file);
		}
	}
	else
	{
		MessageBox(L"�������������ƣ�");
	}
	return state;
}

#if 0


//int CPicConversionDlg::ReadReg(int id, int addr)
//{
//	// read sensor register
//	// ...
//	return 
//}

int g_ReadReg(void *handle, int id, int addr)
{
	return 0x56;
}

BOOL CPicConversionDlg::OV16A1QTools(unsigned char* src, unsigned char* dst, int *otp_dpc)
{
	int ret = 0;
	//int sensorID = 0x6c;	// or 0x20

	//// set sensor I2C callback
	ret = ov4c_set_i2c_callback(this, 0x6c, (ov4c_i2c_callback)g_ReadReg);
	if (ret != 0)
		return -1;
	ROI_PARA roi_para;
	roi_para.w = 4656;
	roi_para.h = 3497;
	roi_para.roi_w = 4656;
	roi_para.roi_h = 3496;
	roi_para.sensor_type = 3;
	roi_para.pattern = 0;
	ret = ov4c_init(&roi_para);
	if (ret != 0)
	{
		MessageBox(L"OV4C_INIT��ȡ�ļ�ʧ�ܣ�����");
		return FALSE;
	}
	roi_para.otp_dpc_data = otp_dpc;
	roi_para.otp_dpc_data_length = 1920;
	roi_para.enable_dpc = 1;
	roi_para.enable_otp_dpc = 1;
	ret = ov4c_transform_bayer_raw10((unsigned short*)src, (unsigned short*)dst, &roi_para);
	if (ret != 0)
	{
		MessageBox(L"OV4cתͼʧ�ܣ�");
		return FALSE;
	}
	return TRUE;
}

#endif

//һ����log.txtתbin�ļ�
void CPicConversionDlg::OnBnClickedButton1()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	BOOL result=false;
	char fnr[260]="";
	char fnw[260]="";
	 CString filter;
	 filter="�����ļ�(*.*)|*.txt||";
	 CFileDialog dlg(1,NULL,NULL,OFN_HIDEREADONLY|OFN_OVERWRITEPROMPT,filter,NULL);
	 if(dlg.DoModal()==IDOK)
	 {
	 	//��·���������
	 	CString sFilePath=dlg.GetPathName(); 
		 for(int i=0;i<sFilePath.GetLength();i++)
		 {
			 fnr[i] = sFilePath.GetAt(i);
			 fnw[i] = sFilePath.GetAt(i);
		 }
	 	//���ļ�ĩβ����Ϊbin�ļ�
		 fnw[sFilePath.GetLength()-3]='b';
		 fnw[sFilePath.GetLength()-2]='i';
		 fnw[sFilePath.GetLength()-1]='n';
		 
	 }
	 else
	 {
		 goto end;
		 result=true;
	 }
		

	 FILE *fr,*fw;
	 char address[5]={"0"};
	 BYTE *updata = (BYTE*)malloc(1); 
	 char data[2]="";
	 int tableIndex=0,msg=1,index=0;
	  
	fopen_s(&fr,fnr,"rb+");
	if(NULL==fr)
	{
		MessageBox(L"��ȡ�ļ�ʧ�ܣ�����"); 
		goto end;
		result=true;
	} 
	fopen_s(&fw,fnw,"wb+");
	if(NULL==fw)
	{
		MessageBox(L"��ȡ�ļ�ʧ�ܣ�����"); 
		goto end;
		result=true;
	}
	fgets(address,sizeof(address),fr);
	while(true)
	{
		msg = fread(&data,1,1,fr);
		if( msg == 0 )
			break;
		if(data[0]==9)
		{ 
			fread(&data,1,2,fr); 
			index = 0;
			int b;
			while(true)
			{ 
				fread(&data,1,1,fr); 
				if(data[0] != 9)
				{
					index += 1;
					address[index-1]=data[0];
				}
				else
				{
					 
					if(index==1)
					{ 
						/*b=stoi(address,nullptr,16);
						updata[0]=b>>8;
						updata[1]=b&0xff;*/
						
					}
					else if(index ==2 )
					{ 
						/*b=stoi(address,nullptr,16);
						updata[0]=b>>8;
						updata[1]=b&0xff;*/
					}
					else if(index ==3)
					{ 
						/*b=stoi(address,nullptr,16);
						updata[0]=b>>8;
						updata[1]=b&0xff;*/
					}
					else
					{
						 
						/*b=stoi(address,nullptr,16);
						updata[0]=b>>8;
						updata[1]=b&0xff;*/
					} 

					 fread(&data,2,1,fr);
					 fread(&data,2,1,fr);
					 if(data[1] == 10 )
					 { 
						 b= std::stoi(data,nullptr,16);
						 updata[0]=b;
					 }
					 else
					 { 
						 b= std::stoi(data,nullptr,16);
						 updata[0]=b;
					 }
					 
					fwrite(updata,1,1,fw); 

					break;
				} 
				 
			} 
		}
			
		   
	}
	fclose(fr);
    fclose(fw);
	free(updata);
    MessageBox(L"�ļ�ת���ɹ�������");
end:
	if(result)
		MessageBox(L"�ļ�ת��ʧ�ܣ�����");
}

//����90��
void CPicConversionDlg::OnBnClickedButton2()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	UpdateData(TRUE);
	CString filter;
	filter = "rawFile(*.raw)|*.raw||";
	CFileDialog dlg(TRUE, NULL, NULL, OFN_HIDEREADONLY|OFN_OVERWRITEPROMPT, filter, NULL);
	if (IDCANCEL != dlg.DoModal())
	{
		CString fileName = dlg.GetPathName();
		CString dirPath = dlg.GetFolderPath();
		CString fileTitle = dlg.GetFileTitle();
		CString NFileName = fileTitle + "_rota.raw";
		USES_CONVERSION;
		int size = 0;
		CFileStatus fileStatus;
		if (CFile::GetStatus(fileName, fileStatus))
		{
			size = fileStatus.m_size;
		}
		if (size == 0)
		{
			AfxMessageBox(L"�ļ�����Ϊ�㣡");
			return;
		}

		SetCurrentDirectoryA(T2A(dirPath));
		if (size == m_Width * m_Height)
		{
			unsigned char *raw8buf;
			raw8buf = new unsigned char[m_Width * m_Height];
			unsigned char *raw8buf2;
			raw8buf2 = new unsigned char[m_Width * m_Height];
			FILE *file;
			file = fopen(T2A(fileName), "rb");
			fread(raw8buf, 1, m_Width * m_Height, file);
			fclose(file);
			RAngleRotation(raw8buf, raw8buf2, m_Width, m_Height);
			file = fopen(T2A(NFileName), "wb+");
			fwrite(raw8buf2, 1, m_Width * m_Height, file);
			fclose(file);
			delete[] raw8buf;
			delete[] raw8buf2;
		}
		else if (size == m_Width * m_Height * 2)
		{
			USHORT *raw10buf;
			raw10buf = new USHORT[m_Width * m_Height];
			USHORT *raw10buf2;
			raw10buf2 = new USHORT[m_Width * m_Height];
			FILE *file;
			file = fopen(T2A(fileName), "rb");
			fread(raw10buf, 2, m_Width * m_Height, file);
			fclose(file);
			RAngleRotation(raw10buf, raw10buf2, m_Width, m_Height);
			file = fopen(T2A(NFileName), "wb+");
			fwrite(raw10buf2, 2, m_Width * m_Height, file);
			fclose(file);
			delete[] raw10buf;
			delete[] raw10buf2;
		}
		else
		{
			AfxMessageBox(L"��֧�ִ�ͼƬ��");
		}
	}
}

//ת��
void CPicConversionDlg::OnBnClickedButton3()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	UpdateData(TRUE);
	CString filter;
	filter = "rawFile(*.raw)|*.raw||";
	CFileDialog dlg(TRUE, NULL, NULL, OFN_HIDEREADONLY|OFN_OVERWRITEPROMPT, filter, NULL);
	if (IDCANCEL != dlg.DoModal())
	{
		CString fileName = dlg.GetPathName();
		CString dirPath = dlg.GetFolderPath();
		CString fileTitle = dlg.GetFileTitle();
		CString NFileName = fileTitle + "_tran.raw";
		USES_CONVERSION;
		int size = 0;
		CFileStatus fileStatus;
		if (CFile::GetStatus(fileName, fileStatus))
		{
			size = fileStatus.m_size;
		}
		if (size == 0)
		{
			AfxMessageBox(L"�ļ�����Ϊ�㣡");
			return;
		}
		
		SetCurrentDirectoryA(T2A(dirPath));
		if (size == m_Width * m_Height)
		{
			unsigned char *raw8buf;
			raw8buf = new unsigned char[m_Width * m_Height];
			unsigned char *raw8buf2;
			raw8buf2 = new unsigned char[m_Width * m_Height];
			FILE *file;
			file = fopen(T2A(fileName), "rb");
			fread(raw8buf, 1, m_Width * m_Height, file);
			fclose(file);
			Transpose(raw8buf, raw8buf2, m_Width, m_Height);
			file = fopen(T2A(NFileName), "wb+");
			fwrite(raw8buf2, 1, m_Width * m_Height, file);
			fclose(file);
			delete[] raw8buf;
			delete[] raw8buf2;
		}
		else if (size == m_Width * m_Height * 2)
		{
			USHORT *raw10buf;
			raw10buf = new USHORT[m_Width * m_Height];
			USHORT *raw10buf2;
			raw10buf2 = new USHORT[m_Width * m_Height];
			FILE *file;
			file = fopen(T2A(fileName), "rb");
			fread(raw10buf, 2, m_Width * m_Height, file);
			fclose(file);
			Transpose(raw10buf, raw10buf2, m_Width, m_Height);
			file = fopen(T2A(NFileName), "wb+");
			fwrite(raw10buf2, 2, m_Width * m_Height, file);
			fclose(file);
			delete[] raw10buf;
			delete[] raw10buf2;
		}
		else
		{
			AfxMessageBox(L"��֧�ִ�ͼƬ��");
		}
	}
}

//����
void CPicConversionDlg::OnBnClickedButton4()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	UpdateData(TRUE);
	CString filter;
	filter = "rawFile(*.raw)|*.raw||";
	CFileDialog dlg(TRUE, NULL, NULL, OFN_HIDEREADONLY|OFN_OVERWRITEPROMPT, filter, NULL);
	if (IDCANCEL != dlg.DoModal())
	{
		CString fileName = dlg.GetPathName();
		CString dirPath = dlg.GetFolderPath();
		CString fileTitle = dlg.GetFileTitle();
		CString NFileName = fileTitle + "_mirror.raw";
		USES_CONVERSION;
		int size = 0;
		CFileStatus fileStatus;
		if (CFile::GetStatus(fileName, fileStatus))
		{
			size = fileStatus.m_size;
		}
		if (size == 0)
		{
			AfxMessageBox(L"�ļ�����Ϊ�㣡");
			return;
		}

		SetCurrentDirectoryA(T2A(dirPath));
		if (size == m_Width * m_Height)
		{
			unsigned char *raw8buf;
			raw8buf = new unsigned char[m_Width * m_Height];
			unsigned char *raw8buf2;
			raw8buf2 = new unsigned char[m_Width * m_Height];
			FILE *file;
			file = fopen(T2A(fileName), "rb");
			fread(raw8buf, 1, m_Width * m_Height, file);
			fclose(file);
			mirrorTrans(raw8buf, raw8buf2, m_Width, m_Height);
			file = fopen(T2A(NFileName), "wb+");
			fwrite(raw8buf2, 1, m_Width * m_Height, file);
			fclose(file);
			delete[] raw8buf;
			delete[] raw8buf2;
		}
		else if (size == m_Width * m_Height * 2)
		{
			USHORT *raw10buf;
			raw10buf = new USHORT[m_Width * m_Height];
			USHORT *raw10buf2;
			raw10buf2 = new USHORT[m_Width * m_Height];
			FILE *file;
			file = fopen(T2A(fileName), "rb");
			fread(raw10buf, 2, m_Width * m_Height, file);
			fclose(file);
			mirrorTrans(raw10buf, raw10buf2, m_Width, m_Height);
			file = fopen(T2A(NFileName), "wb+");
			fwrite(raw10buf2, 2, m_Width * m_Height, file);
			fclose(file);
			delete[] raw10buf;
			delete[] raw10buf2;
		}
		else
		{
			AfxMessageBox(L"��֧�ִ�ͼƬ��");
		}
	}
}

//binתlog.txt
void CPicConversionDlg::OnBnClickedButton5()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������

	CString filter = L"�����ļ�(*.*)|*.*||";
	CFileDialog dlg(1,NULL,NULL,OFN_HIDEREADONLY|OFN_OVERWRITEPROMPT,filter,NULL);
	if(dlg.DoModal()==IDOK)
	{
		CString sFilePath = dlg.GetPathName();
		CString strFilePath = dlg.GetFileName();
		CString filetitle = dlg.GetFileTitle();
		CString dirPath = dlg.GetFolderPath();
		ULONGLONG size;
		CFileStatus fileStatus;
		USES_CONVERSION;
		SetCurrentDirectoryA(T2A(dirPath));
		if (CFile::GetStatus(sFilePath, fileStatus))
		{
			size = fileStatus.m_size;
		}
		if (size == 0)
		{
			AfxMessageBox(L"�ļ�����Ϊ�㣡");
			return;
		}
		BYTE *data = new BYTE[size];
		BYTE bin = 0x02;
		FILE *file;
		file = fopen(T2A(strFilePath), "rb+");
		fread(data, 1, size, file);
		fclose(file);
		SetOTPLog(L"xufuxing", 0, size - 1, data, filetitle, &bin);
	}
}


void CPicConversionDlg::SetOTPLog(CString title,int addr_start,int addr_end,UCHAR *val,CString filename,BYTE* val_byte)
{
	USES_CONVERSION; 
	CString filePath; 
	std::string s = "";
	if (0 != access("OTP_LOG", 0))
	{
		mkdir("OTP_LOG");
	}
	if (val_byte[0] == 0x01)
	{
		filePath.Format(_T("OTP_LOG\\%s_MTK.txt"),filename);
	}
	else if (val_byte[0] == 0x02)
	{
		filePath.Format(_T("OTP_LOG\\%s.txt"),filename);
	}

	s = CT2A(filePath); 
	CTime tm = CTime::GetCurrentTime();
	CString sz = tm.Format("����ʱ�䣺20%y-%m-%d %H:%M:%S\r\n"); 
	FILE *fa;
	char path_[1024] = "";
	GetCurrentDirectoryA(1024,path_);
	fopen_s(&fa,s.c_str(),"wb+");
	if(fa == NULL)
	{
		AfxMessageBox(L"����ʧ�ܣ�����");
		return;
	}

	fprintf(fa,"%s\r\n","test");

	s = CT2A(sz);
	fprintf(fa,s.c_str());
	char* a = T2A(title);
	int cnt = 0;
	for (int i = addr_start;i<= addr_end; i++)
	{
		fprintf(fa,"%s_%d\t0x%x\t0x%x\r\n",a,cnt,i,val[cnt]);
		cnt ++;
	} 
	fclose(fa);
	AfxMessageBox(L"���ɳɹ�������");
	return;
}

//10bitRawͼ����ͨ��ֵ���
void CPicConversionDlg::OnBnClickedButton6()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	UpdateData(TRUE);
	if (m_Height == 0 || m_Width == 0 || m_ROI == 0)
	{
		return;
	}
	CString filter = L"rawͼ(*.raw)|*.raw||";
	CFileDialog dlg(1,NULL,NULL,OFN_HIDEREADONLY|OFN_OVERWRITEPROMPT,filter,NULL);
	int count00 = 0, count10 = 0, count01 = 0, count11 = 0;
	int count00_num = 0, count10_num = 0, count01_num = 0, count11_num = 0;
	float R = 0, Gr = 0, Gb = 0, B = 0;
	unsigned short *data = new unsigned short [m_Width * m_Height];
	if (dlg.DoModal() != IDCANCEL)
	{
		CString filePath = dlg.GetPathName();
		CString dirPath = dlg.GetFolderPath();
		CString fileName = dlg.GetFileTitle();
		FILE *file;
		USES_CONVERSION;
		fopen_s(&file, T2A(filePath), "rb+");
		fread(data, 2, m_Width * m_Height, file);
		fclose(file);
		for (int i = (m_ROI - 1) * m_Height / (2 * m_ROI); i < (m_ROI + 1) * m_Height / (2 * m_ROI); i++)
		{
			for (int j = (m_ROI - 1) * m_Width / (2 * m_ROI); j < (m_ROI + 1) * m_Width / (2 * m_ROI); j++)
			{
				if (i % 2 == 0 && j % 2 == 0)
				{
					count00 += data[i * m_Width + j];
					count00_num++;
				}
				if (i % 2 != 0 && j % 2 == 0)
				{
					count10 += data[i * m_Width + j];
					count10_num++;
				}
				if (i % 2 == 0 && j % 2 != 0)
				{
					count01 += data[i * m_Width + j];
					count01_num++;
				}
				if (i % 2 != 0 && j % 2 != 0)
				{
					count11 += data[i * m_Width + j];
					count11_num++;
				}
			}
		}
		if (m_ByteMode == 0)
		{
			R = (float)count00 / count00_num;
			Gr = (float)count01 / count01_num;
			Gb = (float)count10 / count10_num;
			B = (float)count11 / count11_num;
		}
		else if (m_ByteMode == 1)
		{
			R = (float)count01 / count01_num;
			Gr = (float)count00 / count00_num;
			Gb = (float)count11 / count11_num;
			B = (float)count10 / count10_num;
		}
		else if (m_ByteMode == 2)
		{
			R = (float)count10 / count10_num;
			Gr = (float)count11 / count11_num;
			Gb = (float)count00 / count00_num;
			B = (float)count01 / count01_num;
		}
		else if (m_ByteMode == 3)
		{
			R = (float)count11 / count11_num;
			Gr = (float)count10 / count10_num;
			Gb = (float)count01 / count01_num;
			B = (float)count00 / count00_num;
		}
		fopen_s(&file, dirPath + "\\" + fileName + "_awb.txt", "w+");
		fprintf(file, "%s:%f\r\n", "R", R);
		fprintf(file, "%s:%f\r\n", "Gr", Gr);
		fprintf(file, "%s:%f\r\n", "Gb", Gb);
		fprintf(file, "%s:%f\r\n", "B", B);
		fclose(file);
	}
	delete[] data;
}

void CPicConversionDlg::OnBnClickedButton7()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CString filter;
	filter = "txt�ļ�(*.txt)|*.txt||";
	CFileDialog dlg(1, 0, 0, OFN_HIDEREADONLY|OFN_OVERWRITEPROMPT, filter, 0);
	if (dlg.DoModal() == IDOK)
	{
		CString dirPath = dlg.GetFolderPath();
		SetCurrentDirectory(dirPath);
		CString filePath = dlg.GetPathName();
		CString fileTitle = dlg.GetFileTitle();
		USES_CONVERSION;
		ReadSFRFile(T2A(filePath), T2A(fileTitle));
	}
}

/*
 * author: ������
 * date��2020/11/11
 * description: �̶���ʽ��txtתcsv
 * parameter: �ļ�·��
 */
int ReadSFRFile(char *filename, char *outfilename)
{
	using namespace std;
	string out_file_path = outfilename;
	out_file_path+=".csv";
	FILE *out_file;
	out_file = fopen(out_file_path.c_str(),"wb+");
	if (out_file == nullptr)
	{
		AfxMessageBox(L"�ļ�����ʧ�ܣ�");
		return 0;
	}

	char title[500];
	unsigned int addr;
	unsigned int value;
	FILE* readFile;
	int n=0;
	string tmp;
	float arg1;
	float temp2;
	int arg2,arg3;
	char arg4[50] = {0};
	char temp[50] = {0};
	float arg5[10] = {0};
	float arg6[10] = {0};
	float arg7[10] = {0};
	bool ng_flag = false;
	readFile = fopen(filename,"rb");
	if(readFile == nullptr)
	{
		AfxMessageBox(L"�ļ���ʧ�ܣ�");
		return 0;
	}
	else//�ļ�����
	{
		int cnt = 0;
		int cnt_i = 0;
		char line[500]={0};
		while(fgets(line,499,readFile))
		{
			if (cnt_i ==3)
			{
				sscanf(line,"%*[^0]%f\t\t%*[^0-9]%d*%d",&arg1,&arg2,&arg3);
				if (arg1 == 0.5f)
				{
					cnt_i = 18;
				}
				else if (arg1 == 0.8f)
				{
					cnt_i = 33;
				}

			}
			else if (cnt_i ==18)
			{
				sscanf(line,"%*[^0]%f\t\t%*[^0-9]%d*%d",&temp2,&arg2,&arg3);
				if (temp2 != 0.5f)
				{
					cnt_i = 3;
					if (temp2 == 0.8f)
					{
						cnt_i = 33;
					}
					goto save_data;
				}
			}
			else if (cnt_i ==33)
			{
				sscanf(line,"%*[^0]%f\t\t%*[^0-9]%d*%d",&temp2,&arg2,&arg3);
				if (temp2 != 0.8f)
				{
					cnt_i = 3;
					if (temp2 == 0.5f)
					{
						cnt_i = 18;
					}
					goto save_data;
				}
			}
			else if (cnt_i == 8)
			{
				sscanf(line,"%*10hs%16s",arg4);
			}

			else if (cnt_i == 23)
			{
				sscanf(line,"%*10hs%16s",temp);
				if (strcmp(arg4,temp)!=0)
				{
					cnt_i = 8;
					ng_flag = true;
					goto save_data;
				}
			}

			else if (cnt_i == 38)
			{
				sscanf(line,"%*10hs%16s",temp);
				if (strcmp(arg4,temp)!=0)
				{
					cnt_i = 8;
					ng_flag = true;
					goto save_data;
				}
			}

			else if (cnt_i >= 11 && cnt_i<=15)
			{
				sscanf(line,"%*[^H]%*[^0]%f\t\t%*[^V]%*[^0]%f",&arg5[2*(cnt_i-11)],&arg5[2*(cnt_i-11)+1]);
			}

			else if (cnt_i >= 26 && cnt_i<=30)
			{
				sscanf(line,"%*[^H]%*[^0]%f\t\t%*[^V]%*[^0]%f",&arg6[2*(cnt_i-26)],&arg6[2*(cnt_i-26)+1]);
			}

			else if (cnt_i >= 41 && cnt_i<=45)
			{
				sscanf(line,"%*[^H]%*[^0]%f\t\t%*[^V]%*[^0]%f",&arg7[2*(cnt_i-41)],&arg7[2*(cnt_i-41)+1]);
			}


			if (cnt_i == 45)
			{
				//todo �������
				cnt_i = 0;
save_data:		fprintf(out_file,"%s,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f\n",arg4,arg5[8],arg5[9],arg5[0],arg5[1],arg5[2],arg5[3],arg5[4],arg5[5],arg5[6],arg5[7]
				,arg6[0],arg6[1],arg6[2],arg6[3],arg6[4],arg6[5],arg6[6],arg6[7]
				,arg7[0],arg7[1],arg7[2],arg7[3],arg7[4],arg7[5],arg7[6],arg7[7]);
				if (ng_flag)
				{
					ng_flag = false;
					strcpy_s(arg4,temp);
				}
				memset(arg5,0,sizeof(float)*10);
				memset(arg6,0,sizeof(float)*10);
				memset(arg7,0,sizeof(float)*10);
			}
			cnt_i++;
			cnt++;

		}
	}
	fclose(readFile);
	fclose(out_file);
	return true;
}


//����ͼƬת��
void CPicConversionDlg::OnBnClickedButton8()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	UpdateData(TRUE);
	if (m_Width <= 0 || m_Height <= 0)
	{
		AfxMessageBox(L"���߲����Ϲ��");
		return;
	}
	BYTE* raw8buf = new BYTE[m_Width * m_Height];
	BYTE* raw10buf = new BYTE[m_Width * m_Height * 2];
	BYTE* bmpbuf = new BYTE[m_Width * m_Height * 3];
	CString filter = L"(*.raw)|*.raw||";
	CFileDialog dlg(TRUE, NULL, NULL, OFN_ALLOWMULTISELECT, filter, NULL);
	if (IDCANCEL != dlg.DoModal())
	{
		CString dirPath = dlg.GetFolderPath();
		SetCurrentDirectory(dirPath);
		CString filePath = dlg.GetPathName();
		CString fileName = dlg.GetFileName();
		
		CString fileTitle = dlg.GetFileTitle();
		int size;
		CFileStatus fileStatus;
		if (CFile::GetStatus(filePath, fileStatus))
		{
			size = fileStatus.m_size;
		}
		if (size == 0)
		{
			AfxMessageBox(L"�ļ�����Ϊ�㣡");
			delete[] raw8buf;
			delete[] raw10buf;
			delete[] bmpbuf;
			return;
		}
		BOOL state;
		state = FALSE;
		state = Choice(fileName, fileTitle,raw8buf, raw10buf, bmpbuf, size);
		if (state == FALSE)
		{
			AfxMessageBox(L"ת��ʧ��");
		}
		else if (state == TRUE)
		{
			AfxMessageBox(L"ת���ɹ�");
		}
	}
	delete[] raw8buf;
	delete[] raw10buf;
	delete[] bmpbuf;
}

BOOL Raw8ToRaw10(unsigned char* raw8, unsigned char* raw10, int width, int height)
{
	for (int i = 0; i < height; i++)
	{
		for (int j = 0; j < width; j++)
		{
			raw10[2 * (i * width + j)] = raw8[i * width + j] << 2;
			raw10[2 * (i * width + j) + 1] = raw8[i * width + j] >> 6;
		}
	}
	if (raw10 != NULL && raw10[0] == (raw8[0] << 2))
	{
		return TRUE;
	}
	return FALSE;
}

BOOL Raw10ToRaw8(unsigned char* raw10, unsigned char* raw8, int width, int height)
{
	for (int i = 0; i < height; i++)
	{
		for (int j = 0; j < width; j++)
		{
			raw8[i * width + j] = raw10[2 * (i * width + j)] >> 2 | raw10[2 * (i * width + j) + 1] << 6;
		}
	}
	if (raw8 != NULL && raw8[0] == (raw10[0] >> 2 | raw10[1] << 6))
	{
		return TRUE;
	}
	return FALSE;
}

BOOL SaveBMP(unsigned char* bmpbuf, int width, int height, CString filetitle)
{
	int size;
	size = width * height * 3;
	BITMAPFILEHEADER bmpHeader;
	bmpHeader.bfOffBits = sizeof(BITMAPFILEHEADER) + sizeof(BITMAPINFOHEADER);
	bmpHeader.bfReserved1 = 0;
	bmpHeader.bfReserved2 = 0;
	bmpHeader.bfSize = sizeof(BITMAPFILEHEADER) + sizeof(BITMAPINFOHEADER) + size;
	bmpHeader.bfType = 0x4D42;

	BITMAPINFOHEADER bmpInfo;
	bmpInfo.biSize = sizeof(BITMAPINFOHEADER);
	bmpInfo.biWidth = width;
	bmpInfo.biHeight = height;
	bmpInfo.biPlanes = 1;
	bmpInfo.biBitCount = 24;
	bmpInfo.biCompression = 0;
	bmpInfo.biSizeImage = size;
	bmpInfo.biXPelsPerMeter = 0;
	bmpInfo.biYPelsPerMeter = 0;
	bmpInfo.biClrUsed = 0;
	bmpInfo.biClrImportant = 0;

	if (bmpbuf == NULL)
	{
		return FALSE;
	}
	FILE *bmpFile;
	USES_CONVERSION;
	bmpFile = fopen(T2A(filetitle), "wb+");
	fwrite(&bmpHeader, 1, sizeof(BITMAPFILEHEADER), bmpFile);
	fwrite(&bmpInfo, 1, sizeof(BITMAPINFOHEADER), bmpFile);
	fwrite(bmpbuf, 3, width * height, bmpFile);
	fclose(bmpFile);
	return TRUE;
}

void BayerConversionFlip( BYTE* pSrcBuffer, BYTE* pDstBuffer, int nImgWidth, int nImgHeight, int bayerType)
{
	int width = nImgWidth;
	int height  = nImgHeight;

	int x = 0; 
	int y = 0;
	int i = 0;


	switch( bayerType )
	{
	case 0: //RGGB
		{
			//////////////////////////////			
			///Corner case;
			x = 0;
			y = 0;
			pDstBuffer[ y * width * 3 + x * 3 + 0 ] = pSrcBuffer[(height-1)*width+1]; //B
			pDstBuffer[ y * width * 3 + x * 3 + 1 ] = ( pSrcBuffer[ (height-2)*width+1] + pSrcBuffer[(height-1)*width])/2; //G
			pDstBuffer[ y * width * 3 + x * 3 + 2 ] = pSrcBuffer[ (height-2)*width]; // R

			x = width - 1;
			y = 0;
			pDstBuffer[ y * width * 3 + x * 3 + 0 ] = pSrcBuffer[ height*width - 1 ]; 
			pDstBuffer[ y * width * 3 + x * 3 + 1 ] = ( pSrcBuffer[height*width -2] + pSrcBuffer[(height-1)*width-1] )/2;
			pDstBuffer[ y * width * 3 + x * 3 + 2 ] = pSrcBuffer[(height-1)*width - 2];

			x = 0;
			y = height - 1;
			pDstBuffer[ y * width * 3 + x * 3 + 0 ] = pSrcBuffer[width+1];
			pDstBuffer[ y * width * 3 + x * 3 + 1 ] = (pSrcBuffer[1] + pSrcBuffer[width] )/2;
			pDstBuffer[ y * width * 3 + x * 3 + 2 ] = pSrcBuffer[0];

			x = width - 1;
			y = height - 1;
			pDstBuffer[ y * width * 3 + x * 3 + 0 ] = pSrcBuffer[width*2-1];
			pDstBuffer[ y * width * 3 + x * 3 + 1 ]  = ( pSrcBuffer[width*2 -2] + pSrcBuffer[width -1 ] )/2;
			pDstBuffer[ y * width * 3 + x * 3 + 2 ] = pSrcBuffer[width-2];

			//for boundary
			for(x = 1; x < width -1; x++ )
			{ 	
				if( x%2 == 1 )
				{
					y = 0;
					pDstBuffer[ y * width * 3 + x * 3 + 0 ] = pSrcBuffer[(height-1)*width+x]; //B
					pDstBuffer[ y * width * 3 + x * 3 + 1 ] = ( pSrcBuffer[(height-1)*width+x-1] + pSrcBuffer[(height-1)*width+x+1] + pSrcBuffer[(height-2)*width+x] )/3; //G
					pDstBuffer[ y * width * 3 + x * 3 + 2 ] = ( pSrcBuffer[(height-2)*width+x-1] +  pSrcBuffer[(height-2)*width+x+1] )/2; //R

					y = height -1;
					pDstBuffer[ y * width * 3 + x * 3 + 0 ] = pSrcBuffer[width+x];
					pDstBuffer[ y * width * 3 + x * 3 + 1 ] = ( pSrcBuffer[x] + pSrcBuffer[width+x-1] + pSrcBuffer[width+x+1] ) /3 ;
					pDstBuffer[ y * width * 3 + x * 3 + 2 ] = ( pSrcBuffer[x-1] + pSrcBuffer[x+1] )/2; 
				}
				else
				{
					y = 0;
					pDstBuffer[ y * width * 3 + x * 3 + 0 ] = ( pSrcBuffer[(height-1)*width+x-1] + pSrcBuffer[(height-1)*width+x+1] )/2; //B
					pDstBuffer[ y * width * 3 + x * 3 + 1 ] =  ( pSrcBuffer[(height-1)*width+x] + pSrcBuffer[(height-2)*width+x-1] + pSrcBuffer[(height-2)*width + x +1])/3; //G //Here
					pDstBuffer[ y * width * 3 + x * 3 + 2 ] =  pSrcBuffer[(height-2)*width+x];	//R

					y = height -1;
					pDstBuffer[ y * width * 3 + x * 3 + 0 ] =  ( pSrcBuffer[width+x-1] + pSrcBuffer[width+x+1] )/2;
					pDstBuffer[ y * width * 3 + x * 3 + 1 ] =  ( pSrcBuffer[width+x] + pSrcBuffer[x-1] + pSrcBuffer[x+1] )/3 ;
					pDstBuffer[ y * width * 3 + x * 3 + 2 ] = pSrcBuffer[x] ; 

				} 
			}

			for(y = 1;  y < height - 1; y++ )
			{
				if( y%2 == 1 )
				{
					x = 0;
					i = ( height -1 - y )*width;
					pDstBuffer[ y * width * 3 + x * 3 + 0 ] = ( pSrcBuffer[i-width+1] + pSrcBuffer[i+width+1] )/2;
					pDstBuffer[ y * width * 3 + x * 3 + 1 ] = ( pSrcBuffer[i-width] + pSrcBuffer[i+width] + pSrcBuffer[i+1] )/3;
					pDstBuffer[ y * width * 3 + x * 3 + 2 ] = pSrcBuffer[i];


					x = width -1;
					i = ( height - 1 - y)* width + x;
					pDstBuffer[ y * width * 3 + x * 3 + 0 ] = ( pSrcBuffer[i-width] + pSrcBuffer[i+width] )/2;
					pDstBuffer[ y * width * 3 + x * 3 + 1 ] = ( pSrcBuffer[i] + pSrcBuffer[i-width-1] + pSrcBuffer[i+width-1])/3;  //here 
					pDstBuffer[ y * width * 3 + x * 3 + 2 ] = pSrcBuffer[i-1];  
				}
				else
				{
					x = 0;                                             
					i = ( height -1 - y )*width;                       
					pDstBuffer[ y * width * 3 + x * 3 + 0 ] = pSrcBuffer[i+1];      
					pDstBuffer[ y * width * 3 + x * 3 + 1 ] = ( pSrcBuffer[i] + pSrcBuffer[i-width+1] + pSrcBuffer[i+width+1])/3;          
					pDstBuffer[ y * width * 3 + x * 3 + 2 ] = ( pSrcBuffer[i-width] + pSrcBuffer[i+width] )/2;         


					x = width -1;                                      
					i = ( height - 1 - y)* width + x;                      
					pDstBuffer[ y * width * 3 + x * 3 + 0 ] = pSrcBuffer[i];      
					pDstBuffer[ y * width * 3 + x * 3 + 1 ] = ( pSrcBuffer[i-width] + pSrcBuffer[i+width] + pSrcBuffer[i-1] )/3;        
					pDstBuffer[ y * width * 3 + x * 3 + 2 ] = ( pSrcBuffer[i-width-1] + pSrcBuffer[i+width-1] )/2;  //Here

				}
			}


			//other area
			for( y = 1; y < height-1; y++ )
			{
				for( x=1; x < width-1; x++ )
				{
					i = (height-1-y)*width + x;

					if( y%2 == 1 )
					{
						if( x%2 == 1 ) //G1
						{
							pDstBuffer[y * width * 3 + x * 3 + 0] =  ( pSrcBuffer[i-width] + pSrcBuffer[i+width] )/2;
							pDstBuffer[y * width * 3 + x * 3 + 1] =  ( pSrcBuffer[i] + pSrcBuffer[i-width-1] )/2;
							pDstBuffer[y * width * 3 + x * 3 + 2] =  (pSrcBuffer[i-1] + pSrcBuffer[i+1])/2;//Here

						}
						else  //R
						{
							pDstBuffer[y * width * 3 + x * 3 + 0] = ( pSrcBuffer[i-width-1] + pSrcBuffer[i-width+1] + pSrcBuffer[i+width-1] + pSrcBuffer[i+width+1] ) / 4;
							pDstBuffer[y * width * 3 + x * 3 + 1] = ( pSrcBuffer[i-width] + pSrcBuffer[i-1] + pSrcBuffer[i+1] + pSrcBuffer[i+width]) / 4;
							pDstBuffer[y * width * 3 + x * 3 + 2] =  pSrcBuffer[i]; 
						}
					}
					else
					{
						if( x%2  == 1)  //B
						{
							pDstBuffer[y * width * 3 + x * 3 + 0] = pSrcBuffer[i];
							pDstBuffer[y * width * 3 + x * 3 + 1] = ( pSrcBuffer[i-width] + pSrcBuffer[i+width] + pSrcBuffer[i-1] + pSrcBuffer[i+1] ) /4;//Here
							pDstBuffer[y * width * 3 + x * 3 + 2] = ( pSrcBuffer[i-width-1] + pSrcBuffer[i-width+1] + pSrcBuffer[i+width-1] + pSrcBuffer[i+width+1]) /4;
						}
						else  //G2
						{
							pDstBuffer[y * width * 3 + x * 3 + 0] =  ( pSrcBuffer[i-1] + pSrcBuffer[i+1] )/2;
							pDstBuffer[y * width * 3 + x * 3 + 1] =   (pSrcBuffer[i] + pSrcBuffer[i-width-1] )/2;
							pDstBuffer[y * width * 3 + x * 3 + 2] =  ( pSrcBuffer[i-width] + pSrcBuffer[i+width] )/2;
						}

					}
				}
			}
		}
		break;

	case 1: //GRBG
		{ 
			//corner case
			x = 0;
			y = 0;
			i = (height-1)*width;
			pDstBuffer[y * width * 3 + x * 3 + 0] = pSrcBuffer[i]; //B
			pDstBuffer[y * width * 3 + x * 3 + 1] = ( pSrcBuffer[i-width] + pSrcBuffer[i+1] )/2; //G
			pDstBuffer[y * width * 3 + x * 3 + 2] =   pSrcBuffer[i-width+1]; 

			x = width -1;
			y = 0;			 
			pDstBuffer[y * width * 3 + x * 3 + 0] = pSrcBuffer[height*width-2];
			pDstBuffer[y * width * 3 + x * 3 + 1] = ( pSrcBuffer[(height-1)*width-2] + pSrcBuffer[height*width-1] )/2;
			pDstBuffer[y * width * 3 + x * 3 + 2] = pSrcBuffer[(height-1)*width-1];

			x = 0;   
			y = height -1;
			pDstBuffer[y * width * 3 + x * 3 + 0] = pSrcBuffer[width];
			pDstBuffer[y * width * 3 + x * 3 + 1] = ( pSrcBuffer[0] + pSrcBuffer[width+1] )/2;
			pDstBuffer[y * width * 3 + x * 3 + 2] = pSrcBuffer[1];

			x = width - 1;
			y = height - 1;
			pDstBuffer[y * width * 3 + x * 3 + 0] =  pSrcBuffer[width*2-2];
			pDstBuffer[y * width * 3 + x * 3 + 1] =  ( pSrcBuffer[width*2 -1] +  pSrcBuffer[width-2] )/2;
			pDstBuffer[y * width * 3 + x * 3 + 2] =  pSrcBuffer[width -1];


			//for boundary case
			for( x = 1; x < width -1; x++ )
			{
				if( x%2 == 1 )
				{
					y = 0;                                             
					i = ( height -1  )*width + x;  //G                       
					pDstBuffer[ y * width * 3 + x * 3 + 0 ] = (  pSrcBuffer[i-1] + pSrcBuffer[i+1] )/2;      
					pDstBuffer[ y * width * 3 + x * 3 + 1 ] =  ( pSrcBuffer[i] + pSrcBuffer[i-width-1] + pSrcBuffer[i-width+1] )/3;      
					pDstBuffer[ y * width * 3 + x * 3 + 2 ] =  pSrcBuffer[i-width]; 


					y = height - 1;                                      
					i = x;       //R               
					pDstBuffer[ y * width * 3 + x * 3 + 0 ] =  ( pSrcBuffer[i+width-1] + pSrcBuffer[i+width+1] )/2;          
					pDstBuffer[ y * width * 3 + x * 3 + 1 ] =  ( pSrcBuffer[i-1] + pSrcBuffer[i+width] + pSrcBuffer[i+1])/3;        
					pDstBuffer[ y * width * 3 + x * 3 + 2 ] =  pSrcBuffer[i];    

				}
				else
				{
					y = 0;                                             
					i = ( height -1  )*width + x;  //B                     
					pDstBuffer[ y * width * 3 + x * 3 + 0 ] =  pSrcBuffer[i];      
					pDstBuffer[ y * width * 3 + x * 3 + 1 ] =  (  pSrcBuffer[i-width] + pSrcBuffer[i-1] + pSrcBuffer[i+1])/3 ;      
					pDstBuffer[ y * width * 3 + x * 3 + 2 ] =  ( pSrcBuffer[i-width-1] + pSrcBuffer[i-width+1] )/2; 


					y = height - 1;                                      
					i = x;                      
					pDstBuffer[ y * width * 3 + x * 3 + 0 ] =  pSrcBuffer[i+width] ;          
					pDstBuffer[ y * width * 3 + x * 3 + 1 ] =  ( pSrcBuffer[i] + pSrcBuffer[i+width-1] + pSrcBuffer[i+width+1] )/3 ;        
					pDstBuffer[ y * width * 3 + x * 3 + 2 ] =  ( pSrcBuffer[i-1] + pSrcBuffer[i+1] )/2;    
				}
			}

			for( y = 1; y < height - 1; y++ )
			{
				if( y%2 == 1 )
				{
					x = 0;                                             
					i = ( height -1 - y )*width;  //G                     
					pDstBuffer[ y * width * 3 + x * 3 + 0 ] = (  pSrcBuffer[i-width] + pSrcBuffer[i+width] )/2;      
					pDstBuffer[ y * width * 3 + x * 3 + 1 ] =  ( pSrcBuffer[i] + pSrcBuffer[i-width+1] + pSrcBuffer[i+width+1] )/3;      
					pDstBuffer[ y * width * 3 + x * 3 + 2 ] =  pSrcBuffer[i+1]; 


					x = width -1;                                      
					i = ( height - 1 - y)* width + x; //R                     
					pDstBuffer[ y * width * 3 + x * 3 + 0 ] =  ( pSrcBuffer[i-width-1] + pSrcBuffer[i+width-1] )/2;          
					pDstBuffer[ y * width * 3 + x * 3 + 1 ] =  ( pSrcBuffer[i-width] + pSrcBuffer[i+width] + pSrcBuffer[i-1])/3;        
					pDstBuffer[ y * width * 3 + x * 3 + 2 ] =  pSrcBuffer[i];   

				}
				else
				{
					x = 0;                                             
					i = ( height -1 - y )*width;                       
					pDstBuffer[ y * width * 3 + x * 3 + 0 ] =  pSrcBuffer[i];      
					pDstBuffer[ y * width * 3 + x * 3 + 1 ] =  (  pSrcBuffer[i-width] + pSrcBuffer[i+width] + pSrcBuffer[i+1])/3 ;      
					pDstBuffer[ y * width * 3 + x * 3 + 2 ] =  ( pSrcBuffer[i-width+1] + pSrcBuffer[i+width+1] )/2; 


					x = width -1;                                      
					i = ( height - 1 - y)* width + x;                      
					pDstBuffer[ y * width * 3 + x * 3 + 0 ] =  pSrcBuffer[i-1] ;          
					pDstBuffer[ y * width * 3 + x * 3 + 1 ] = (  pSrcBuffer[i] + pSrcBuffer[i-width-1] + pSrcBuffer[i+width-1])/3;        
					pDstBuffer[ y * width * 3 + x * 3 + 2 ] =  ( pSrcBuffer[i-width] + pSrcBuffer[i+width] )/2;  

				}
			}

			//other area
			for( y = 1; y < height -1; y++ )
			{
				for( x = 1; x < width -1; x++ )
				{
					i = ( height -1 -y)*width + x;

					if( y%2 == 1 )
					{
						if( x%2 == 1 ) //R
						{
							pDstBuffer[y * width * 3 + x * 3 + 0] = ( pSrcBuffer[i-width-1] + pSrcBuffer[i-width+1] + pSrcBuffer[i+width-1] + pSrcBuffer[i+width+1] )/4;
							pDstBuffer[y * width * 3 + x * 3 + 1] = ( pSrcBuffer[i-width] + pSrcBuffer[i+width] + pSrcBuffer[i-1] + pSrcBuffer[i+1])/4;
							pDstBuffer[y * width * 3 + x * 3 + 2] =  pSrcBuffer[i];

						}
						else     //G1
						{
							pDstBuffer[y * width * 3 + x * 3 + 0] = ( pSrcBuffer[i-width] + pSrcBuffer[i+width] )/2;
							pDstBuffer[y * width * 3 + x * 3 + 1] =   (pSrcBuffer[i] + pSrcBuffer[i-width-1] )/2;
							pDstBuffer[y * width * 3 + x * 3 + 2] = ( pSrcBuffer[i-1] + pSrcBuffer[i+1])/2; 
						}
					}
					else
					{
						if( x%2 == 1 ) //G2
						{   
							pDstBuffer[ y * width * 3 + x * 3 + 0 ] =   ( pSrcBuffer[i-1] + pSrcBuffer[i+1])/2;     
							pDstBuffer[ y * width * 3 + x * 3 + 1 ] =    ( pSrcBuffer[i] + pSrcBuffer[i-width-1] )/2;  
							pDstBuffer[ y * width * 3 + x * 3 + 2 ] =   ( pSrcBuffer[i-width] + pSrcBuffer[i+width])/2;

						}
						else //B
						{
							pDstBuffer[ y * width * 3 + x * 3 + 0 ] =   pSrcBuffer[i];     
							pDstBuffer[ y * width * 3 + x * 3 + 1 ] =   ( pSrcBuffer[i-width] + pSrcBuffer[i+width] + pSrcBuffer[i-1] + pSrcBuffer[i+1] )/4;  
							pDstBuffer[ y * width * 3 + x * 3 + 2 ] =   ( pSrcBuffer[i-width-1] + pSrcBuffer[i-width+1] + pSrcBuffer[i+width-1] + pSrcBuffer[i+width+1] )/4; 
						}

					}
				}

			} 
		}
		break;

	case 2:   //GBRG
		{
			//corner case
			x = 0;
			y = 0;
			i = (height-1)*width;
			pDstBuffer[y * width * 3 + x * 3 + 0] = pSrcBuffer[i-width+1]; //B
			pDstBuffer[y * width * 3 + x * 3 + 1] = ( pSrcBuffer[i-width] + pSrcBuffer[i+1] )/2; //G
			pDstBuffer[y * width * 3 + x * 3 + 2] =   pSrcBuffer[i]; //R

			x = width -1;
			y = 0;			 
			pDstBuffer[y * width * 3 + x * 3 + 0] = pSrcBuffer[(height - 1)*width-1];
			pDstBuffer[y * width * 3 + x * 3 + 1] = ( pSrcBuffer[(height-1)*width-2] + pSrcBuffer[height*width-1] )/2;
			pDstBuffer[y * width * 3 + x * 3 + 2] = pSrcBuffer[ height*width-2];

			x = 0;   
			y = height -1;
			pDstBuffer[y * width * 3 + x * 3 + 0] = pSrcBuffer[1];
			pDstBuffer[y * width * 3 + x * 3 + 1] = ( pSrcBuffer[0] + pSrcBuffer[width +1 ] )/2;
			pDstBuffer[y * width * 3 + x * 3 + 2] = pSrcBuffer[width];

			x = width -1;
			y = height -1;
			pDstBuffer[y * width * 3 + x * 3 + 0] =  pSrcBuffer[width-1];
			pDstBuffer[y * width * 3 + x * 3 + 1] =  ( pSrcBuffer[width-2] +  pSrcBuffer[width*2-1] )/2;
			pDstBuffer[y * width * 3 + x * 3 + 2] =  pSrcBuffer[width*2 -2];


			//for boundary case
			for( x = 1; x < width -1; x++ )
			{
				if( x%2 == 1 )
				{
					y = 0;                                             
					i = ( height -1  )*width + x;                       
					pDstBuffer[ y * width * 3 + x * 3 + 0 ] = pSrcBuffer[i-width];      
					pDstBuffer[ y * width * 3 + x * 3 + 1 ] =  ( pSrcBuffer[i-width-1] + pSrcBuffer[i-width+1] + pSrcBuffer[i] )/3;      
					pDstBuffer[ y * width * 3 + x * 3 + 2 ] =  ( pSrcBuffer[i-1] + pSrcBuffer[i+1] )/2; 


					y = height - 1;                                      
					i = x;                      
					pDstBuffer[ y * width * 3 + x * 3 + 0 ] =  pSrcBuffer[i];          
					pDstBuffer[ y * width * 3 + x * 3 + 1 ] =  ( pSrcBuffer[i-1] + pSrcBuffer[i+1] + pSrcBuffer[i+width])/3;        
					pDstBuffer[ y * width * 3 + x * 3 + 2 ] =  ( pSrcBuffer[i+width-1] + pSrcBuffer[i+width+1] )/2;    

				}
				else
				{
					y = 0;                                             
					i = ( height -1  )*width + x;                       
					pDstBuffer[ y * width * 3 + x * 3 + 0 ] = ( pSrcBuffer[i-width-1] + pSrcBuffer[i-width+1] )/2;      
					pDstBuffer[ y * width * 3 + x * 3 + 1 ] =  (  pSrcBuffer[i-width] + pSrcBuffer[i-1] + pSrcBuffer[i+1])/3 ;      
					pDstBuffer[ y * width * 3 + x * 3 + 2 ] =  pSrcBuffer[i]; 


					y = height - 1;                                      
					i = x;                      
					pDstBuffer[ y * width * 3 + x * 3 + 0 ] =  ( pSrcBuffer[i-1] + pSrcBuffer[i+1]  )/2 ;          
					pDstBuffer[ y * width * 3 + x * 3 + 1 ] =  ( pSrcBuffer[i] + pSrcBuffer[i+width-1] + pSrcBuffer[i+width+1] )/3 ;        
					pDstBuffer[ y * width * 3 + x * 3 + 2 ] =  pSrcBuffer[i+width];    
				}
			}

			for( y = 1; y < height - 1; y++ )
			{
				if( y%2 == 1 )
				{
					x = 0;                                             
					i = ( height -1 - y )*width;                       
					pDstBuffer[ y * width * 3 + x * 3 + 0 ] =  pSrcBuffer[i+1];      
					pDstBuffer[ y * width * 3 + x * 3 + 1 ] =  ( pSrcBuffer[i] + pSrcBuffer[i-width+1]+ pSrcBuffer[i+width+1])/3;      
					pDstBuffer[ y * width * 3 + x * 3 + 2 ] =  ( pSrcBuffer[i-width] + pSrcBuffer[i+width])/2;//Here 


					x = width -1;                                      
					i = ( height - 1 - y)* width + x;                      
					pDstBuffer[ y * width * 3 + x * 3 + 0 ] =  pSrcBuffer[i];          
					pDstBuffer[ y * width * 3 + x * 3 + 1 ] =  ( pSrcBuffer[i-width] + pSrcBuffer[i-1] + pSrcBuffer[i+width])/3;        
					pDstBuffer[ y * width * 3 + x * 3 + 2 ] =  ( pSrcBuffer[i-width-1] + pSrcBuffer[i+width-1] )/2;   

				}
				else
				{
					x = 0;                                             
					i = ( height -1 - y )*width;                       
					pDstBuffer[ y * width * 3 + x * 3 + 0 ] =  ( pSrcBuffer[i-width+1] + pSrcBuffer[i+width+1] )/2;      
					pDstBuffer[ y * width * 3 + x * 3 + 1 ] =  (  pSrcBuffer[i-width] + pSrcBuffer[i+1] + pSrcBuffer[i+width])/3 ;      
					pDstBuffer[ y * width * 3 + x * 3 + 2 ] =  pSrcBuffer[i]; 


					x = width -1;                                      
					i = ( height - 1 - y)* width + x;                      
					pDstBuffer[ y * width * 3 + x * 3 + 0 ] =  ( pSrcBuffer[i-width] + pSrcBuffer[i+width] )/2 ;          
					pDstBuffer[ y * width * 3 + x * 3 + 1 ] = (  pSrcBuffer[i-width-1] + pSrcBuffer[i] + pSrcBuffer[i+width-1])/3;        
					pDstBuffer[ y * width * 3 + x * 3 + 2 ] =  pSrcBuffer[i-1];  

				}
			}

			//other area
			for( y = 1; y < height -1; y++ )
			{
				for( x = 1; x < width -1; x++ )
				{
					i = ( height -1 -y)*width + x;

					if( y%2 == 1 )
					{
						if( x%2 == 1 )  
						{
							//B
							pDstBuffer[y * width * 3 + x * 3 + 0] = pSrcBuffer[i];
							pDstBuffer[y * width * 3 + x * 3 + 1] = ( pSrcBuffer[i-width] + pSrcBuffer[i-1] + pSrcBuffer[i+1] + pSrcBuffer[i+width])/4;
							pDstBuffer[y * width * 3 + x * 3 + 2] = (pSrcBuffer[i-width-1] +pSrcBuffer[i-width+1] + pSrcBuffer[i+width-1] + pSrcBuffer[i+width+1])/4;

						}
						else      
						{
							pDstBuffer[y * width * 3 + x * 3 + 0] = ( pSrcBuffer[i-1] + pSrcBuffer[i+1] )/2;
							pDstBuffer[y * width * 3 + x * 3 + 1] = ( pSrcBuffer[i] + pSrcBuffer[i-width-1] )/2;
							pDstBuffer[y * width * 3 + x * 3 + 2] = ( pSrcBuffer[i-width] +  + pSrcBuffer[i+width])/2; 
						}
					}
					else
					{
						if( x%2 == 1 )  
						{   
							pDstBuffer[ y * width * 3 + x * 3 + 0 ] =   ( pSrcBuffer[i-width] + pSrcBuffer[i+width])/2;     
							pDstBuffer[ y * width * 3 + x * 3 + 1 ] =     ( pSrcBuffer[i] + pSrcBuffer[i-width-1] )/2;  
							pDstBuffer[ y * width * 3 + x * 3 + 2 ] =   ( pSrcBuffer[i-1] + pSrcBuffer[i+1] )/2;

						}
						else  
						{
							pDstBuffer[ y * width * 3 + x * 3 + 0 ] =   ( pSrcBuffer[i-width-1] +pSrcBuffer[i-width+1]+ pSrcBuffer[i+width-1] + pSrcBuffer[i+width+1])/4;     
							pDstBuffer[ y * width * 3 + x * 3 + 1 ] =   ( pSrcBuffer[i-width] + pSrcBuffer[i+width]   + pSrcBuffer[i-1] + pSrcBuffer[i+1] )/4;  
							pDstBuffer[ y * width * 3 + x * 3 + 2 ] =   pSrcBuffer[i]; 
						}

					}
				}

			}

		}
		break;



	case 3:  //BGGR		
		//////////////////////////////////////
		{
			//corner case
			x = 0;
			y = 0;
			i = (height-1)*width;
			pDstBuffer[y * width * 3 + x * 3 + 0] = pSrcBuffer[i-width]; //B
			pDstBuffer[y * width * 3 + x * 3 + 1] = ( pSrcBuffer[i] + pSrcBuffer[i-width+1] )/2;  
			pDstBuffer[y * width * 3 + x * 3 + 2] =   pSrcBuffer[i+1]; //R

			x = width -1;
			y = 0;			 
			pDstBuffer[y * width * 3 + x * 3 + 0] = pSrcBuffer[(height - 1)*width-2];
			pDstBuffer[y * width * 3 + x * 3 + 1] = ( pSrcBuffer[height*width-2] + pSrcBuffer[(height-1)*width-1] )/2;
			pDstBuffer[y * width * 3 + x * 3 + 2] = pSrcBuffer[ height*width-1];

			x = 0;   
			y = height -1;
			pDstBuffer[y * width * 3 + x * 3 + 0] = pSrcBuffer[0];
			pDstBuffer[y * width * 3 + x * 3 + 1] = ( pSrcBuffer[1] + pSrcBuffer[width] )/2;
			pDstBuffer[y * width * 3 + x * 3 + 2] = pSrcBuffer[width+1];

			x = width -1;
			y = height -1;
			pDstBuffer[y * width * 3 + x * 3 + 0] =  pSrcBuffer[width-2];
			pDstBuffer[y * width * 3 + x * 3 + 1] =  ( pSrcBuffer[width-1] +  pSrcBuffer[width*2-2] )/2;
			pDstBuffer[y * width * 3 + x * 3 + 2] =  pSrcBuffer[width*2 -1];


			//for boundary case
			for( x = 1; x < width -1; x++ )
			{
				if( x%2 == 1 )
				{
					y = 0;                                             
					i = ( height -1  )*width + x;                       
					pDstBuffer[ y * width * 3 + x * 3 + 0 ] = (  pSrcBuffer[i-width-1] + pSrcBuffer[i-width+1] )/2;      
					pDstBuffer[ y * width * 3 + x * 3 + 1 ] =  ( pSrcBuffer[i-width] + pSrcBuffer[i-1] + pSrcBuffer[i+1] )/3;      
					pDstBuffer[ y * width * 3 + x * 3 + 2 ] =  pSrcBuffer[i]; 


					y = height - 1;                                      
					i = x;                      
					pDstBuffer[ y * width * 3 + x * 3 + 0 ] =  ( pSrcBuffer[i-1] + pSrcBuffer[i+1] )/2;          
					pDstBuffer[ y * width * 3 + x * 3 + 1 ] =  ( pSrcBuffer[i] + pSrcBuffer[i+width-1] + pSrcBuffer[i+width+1])/3;        
					pDstBuffer[ y * width * 3 + x * 3 + 2 ] =  pSrcBuffer[i+width];    

				}
				else
				{
					y = 0;                                             
					i = ( height -1  )*width + x;                       
					pDstBuffer[ y * width * 3 + x * 3 + 0 ] =  pSrcBuffer[i-width];      
					pDstBuffer[ y * width * 3 + x * 3 + 1 ] =  (  pSrcBuffer[i-width-1] + pSrcBuffer[i-width+1] + pSrcBuffer[i])/3 ;      
					pDstBuffer[ y * width * 3 + x * 3 + 2 ] =  ( pSrcBuffer[i-1] + pSrcBuffer[i+1] )/2; 


					y = height - 1;                                      
					i = x;                      
					pDstBuffer[ y * width * 3 + x * 3 + 0 ] =  pSrcBuffer[i] ;          
					pDstBuffer[ y * width * 3 + x * 3 + 1 ] =  ( pSrcBuffer[i-1] + pSrcBuffer[i+1] + pSrcBuffer[i+width] )/3 ;        
					pDstBuffer[ y * width * 3 + x * 3 + 2 ] =  ( pSrcBuffer[i+width-1] + pSrcBuffer[i+width+1] )/2;    
				}
			}

			for( y = 1; y < height - 1; y++ )
			{
				if( y%2 == 1 )
				{
					x = 0;                                             
					i = ( height -1 - y )*width;                       
					pDstBuffer[ y * width * 3 + x * 3 + 0 ] = pSrcBuffer[i];      
					pDstBuffer[ y * width * 3 + x * 3 + 1 ] =  ( pSrcBuffer[i-width] + pSrcBuffer[i+1] + pSrcBuffer[i+width] )/3;      
					pDstBuffer[ y * width * 3 + x * 3 + 2 ] =  (pSrcBuffer[i-width+1] + pSrcBuffer[i+width+1])/2; 


					x = width -1;                                      
					i = ( height - 1 - y)* width + x;                      
					pDstBuffer[ y * width * 3 + x * 3 + 0 ] =  pSrcBuffer[i-1];          
					pDstBuffer[ y * width * 3 + x * 3 + 1 ] =  ( pSrcBuffer[i-width-1] + pSrcBuffer[i] + pSrcBuffer[i+width-1])/3;        
					pDstBuffer[ y * width * 3 + x * 3 + 2 ] =  ( pSrcBuffer[i-width] + pSrcBuffer[i+width] )/2;   

				}
				else
				{
					x = 0;                                             
					i = ( height -1 - y )*width;                       
					pDstBuffer[ y * width * 3 + x * 3 + 0 ] =  ( pSrcBuffer[i-width] + pSrcBuffer[i+width] )/2;      
					pDstBuffer[ y * width * 3 + x * 3 + 1 ] =  (  pSrcBuffer[i-width+1] + pSrcBuffer[i] + pSrcBuffer[i+width+1])/3 ;      
					pDstBuffer[ y * width * 3 + x * 3 + 2 ] =  pSrcBuffer[i+1]; 


					x = width -1;                                      
					i = ( height - 1 - y)* width + x;                      
					pDstBuffer[ y * width * 3 + x * 3 + 0 ] =  ( pSrcBuffer[i-width-1] + pSrcBuffer[i+width-1] )/2 ;          
					pDstBuffer[ y * width * 3 + x * 3 + 1 ] = (  pSrcBuffer[i-width] + pSrcBuffer[i-1] + pSrcBuffer[i+width])/3;        
					pDstBuffer[ y * width * 3 + x * 3 + 2 ] =  pSrcBuffer[i];  

				}
			}

			//other area
			for( y = 1; y < height -1; y++ )
			{
				for( x = 1; x < width -1; x++ )
				{
					i = ( height -1 -y)*width + x;

					if( y%2 == 1 )
					{
						if( x%2 == 1 )  
						{
							pDstBuffer[y * width * 3 + x * 3 + 0] = ( pSrcBuffer[i-1] + pSrcBuffer[i+1] )/2;
							pDstBuffer[y * width * 3 + x * 3 + 1] = ( pSrcBuffer[i] + pSrcBuffer[i-width-1] )/2;
							pDstBuffer[y * width * 3 + x * 3 + 2] = (pSrcBuffer[i-width] + pSrcBuffer[i+width])/2;

						}
						else      
						{
							pDstBuffer[y * width * 3 + x * 3 + 0] = pSrcBuffer[i];
							pDstBuffer[y * width * 3 + x * 3 + 1] = ( pSrcBuffer[i-width] + pSrcBuffer[i-1] + pSrcBuffer[i+1] + pSrcBuffer[i+width ] )/4;
							pDstBuffer[y * width * 3 + x * 3 + 2] = ( pSrcBuffer[i-width-1] + pSrcBuffer[i-width+1] + pSrcBuffer[i+width-1] + pSrcBuffer[i+width+1])/4; 
						}
					}
					else
					{
						if( x%2 == 1 )  
						{   
							pDstBuffer[ y * width * 3 + x * 3 + 0 ] =   ( pSrcBuffer[i-width-1] + pSrcBuffer[i-width+1] + pSrcBuffer[i+width-1] + pSrcBuffer[i+width+1])/4;     
							pDstBuffer[ y * width * 3 + x * 3 + 1 ] =   ( pSrcBuffer[i-width] + pSrcBuffer[i+width] + pSrcBuffer[i-1] + pSrcBuffer[i+1] )/4;  
							pDstBuffer[ y * width * 3 + x * 3 + 2 ] =   pSrcBuffer[i];

						}
						else  
						{
							pDstBuffer[ y * width * 3 + x * 3 + 0 ] =   ( pSrcBuffer[i-width] + pSrcBuffer[i+width] )/2;     
							pDstBuffer[ y * width * 3 + x * 3 + 1 ] =   ( pSrcBuffer[i] + pSrcBuffer[i-width-1] )/2;  
							pDstBuffer[ y * width * 3 + x * 3 + 2 ] =   ( pSrcBuffer[i-1] + pSrcBuffer[i+1] )/2; 
						}

					}
				}

			} 

		}
		break;
	} 
}

BOOL Cell10ToRaw10(unsigned char* cell10buf, int width, int height)
{

	for (int i = 2; i < width * height * 2; i += 8)
	{
		unsigned char temp = 0;
		//��λ����
		temp = cell10buf[i];
		cell10buf[i] = cell10buf[i + 2];
		cell10buf[i + 2] = temp;
		//��λ����
		temp = cell10buf[i + 1];
		cell10buf[i + 1] = cell10buf[i + 3];
		cell10buf[i + 3] = temp;
	}

	for (int i = 1; i < height; i += 4)
	{
		for (int j = 0; j < width * 2; j++)
		{
			unsigned char temp = 0;
			//��ת��
			temp = cell10buf[i * width * 2 + j];
			cell10buf[i * width * 2 + j] = cell10buf[(i + 1) * width * 2 + j];
			cell10buf[(i + 1) * width * 2 + j] = temp;
		}
	}
	if (cell10buf != NULL)
	{
		return TRUE;
	}
	return FALSE;
}

BOOL Cell8ToRaw8(unsigned char* cell8buf, int width, int height)
{
	for (int i = 0; i < height; i++)
	{
		for (int j = 0; j < width; j++)
		{
			unsigned char temp = 0;
			//��ת��
			if (i % 4 == 2)
			{
				temp = cell8buf[i * width + j];
				cell8buf[i * width + j] = cell8buf[(i - 1) * width + j];
				cell8buf[(i - 1) * width + j] = temp;
			}
		}
	}
	for (int i = 0; i < height; i++)
	{
		for (int j = 0; j < width; j++)
		{
			unsigned char temp = 0;
			//��ת��
			if (j % 4 == 1)
			{
				temp = cell8buf[i * width + j];
				cell8buf[i * width + j] = cell8buf[i * width + j + 1];
				cell8buf[i * width + j + 1] = temp;
			}
		}
	}
	if (cell8buf != NULL)
	{
		return TRUE;
	}
	return FALSE;
}

/************************************************************************
 USHORTתUCHAR
 @param USHORT* srcΪԴ����
 @param UCHAR *dstΪĿ������ 
 @param widthΪUSHORT�Ŀ�
 @param heightΪUSHORT�ĸ�
 @desription
 ��Ҫ����	�Ѿ�������ڴ�ռ�	��ָ�룬�����ݽ���ת��
 ��Ҫ���	����Խ��	������

 @param size �����ܳ���
************************************************************************/
void US_to_UC(USHORT* src, UCHAR *dst, int width, int height)
{
	for (int col = 0; col < height; col++)
	{
		for (int row = 0; row < width; row++)
		{
			dst[2 * (col * width + row)] = (src[col * width + row] >> 8) & 0x00ff;
			dst[2 * (col * width + row) + 1] = src[col * width + row] & 0x00ff;
		}
	}
}

void US_to_UC(USHORT* src, UCHAR *dst, int size)
{
	for (int i = 0; i < size; i++)
	{
		dst[2 * i] = (src[i] >> 8) & 0xff;
		dst[2 * i + 1] = src[i] & 0xff;
	}
}

/************************************************************************
 UCHARתUSHORT
 @param UCHAR* srcΪԴ����
 @param USHORT *dstΪĿ������
 @param widthΪUCHAR�Ŀ�
 @param heightΪUCHAR�ĸ�
 @desription
 ��Ҫ����	�Ѿ�������ڴ�ռ�	��ָ�룬�����ݽ���ת��
 ��Ҫ���	����Խ��	������

 @param size �����ܳ���
************************************************************************/
BOOL UC_to_US(UCHAR* src, USHORT *dst, int width, int height)
{
	for (int col = 0; col < height; col++)
	{
		for (int row = 0; row < width; row += 2)
		{
			dst[(col * width + row) / 2] = src[col * width + row] * 256 + src[col * width + row + 1];
		}
	}
}

void UC_to_US(UCHAR* src, USHORT *dst, int size)
{
	for (int i = 0; i < size; i += 2)
	{
		dst[i / 2] = src[i] * 256 + src[i + 1];
	}
}

/*************************
 *
 *	����90��
 *	����֮��Ĺ�ϵ
 *	
 *	<b>width * height</b><br>
 *	==============>
 *	heigth * width
 *	
 *	old			new
 *	(h1, w1)	(h2, w2)
 *	
 *	h1 + w2 = height - 1;
 *	
 *	h2 = w1;
 *	
 *************************/
void RAngleRotation(unsigned char *src, unsigned char *dst, int width, int height)
{
	for (int h = 0; h < width; h++)
	{
		for (int w = 0; w < height; w++)
		{
			dst[h * height + w] = src[(height - w - 1) * width + h];
		}
	}
}

//Raw10����ת
void RAngleRotation(USHORT *src, USHORT *dst, int width, int height)
{
	for (int h = 0; h < width; h++)
	{
		for (int w = 0; w < height; w++)
		{
			dst[h * height + w] = src[(height - w - 1) * width + h];
		}
	}
}

/*************************
 *
 *	ת��
 *	����֮��Ĺ�ϵ
 *
 *	width * height
 *	==============>
 *	heigth * width
 *
 *	old			new
 *	(h1, w1)	(h2, w2)
 *
 *	w2 = h1;
 *
 *	h2 = w1;
 *	
 *************************/
void Transpose(unsigned char *src, unsigned char *dst, int width, int height)
{
	for (int h = 0; h < width; h++)
	{
		for (int w = 0; w < height; w++)
		{
			dst[h * height + w] = src[w * width + h];
		}
	}
}

//R10��ת��
void Transpose(USHORT *src, USHORT *dst, int width, int height)
{
	for (int h = 0; h < width; h++)
	{
		for (int w = 0; w < height; w++)
		{
			dst[h * height + w] = src[w * width + h];
		}
	}
}
/*************************
 *
 *	����
 *	����֮��Ĺ�ϵ
 *
 *	width * height
 *	==============>
 *	heigth * width
 *
 *	old			new
 *	(h1, w1)	(h2, w2)
 *
 *	w1 + w2 = width - 1;
 *
 *	h1 = h2;
 *	
 *************************/
void mirrorTrans(unsigned char *src, unsigned char *dst, int width, int height)
{
	for (int h = 0; h < height; h++)
	{
		for (int w = 0; w < width; w++)
		{
			dst[h * width + w] = src[h * width + width - w - 1];
		}
	}
}

//Raw10�ľ���
void mirrorTrans(USHORT *src, USHORT *dst, int width, int height)
{
	for (int h = 0; h < height; h++)
	{
		for (int w = 0; w < width; w++)
		{
			dst[h * width + w] = src[h * width + width - w - 1];
		}
	}
}