
// CSerialApplicationDlg.cpp: archivo de implementación
//




#include "pch.h"
#include "framework.h"

#include <iostream>
#include <string>
#include <thread>

#include <Comm.h>

#include "SerialApplication.h"
#include "SerialApplicationDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

#define _AFX_NO_MFC_CONTROLS_IN_DIALOGS

// Cuadro de diálogo CAboutDlg utilizado para el comando Acerca de

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// Datos del cuadro de diálogo
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // Compatibilidad con DDX/DDV

// Implementación
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


// Cuadro de diálogo de CPinpadApplicationDlg



CSerialApplicationDlg::CSerialApplicationDlg(CWnd* pParent /*= nullptr*/)
	: CDialogEx(IDD_PINPADAPPLICATION_DIALOG, pParent),
	m_pFont{ new CFont() },
	m_pSerialPort{ nullptr },
	m_nPortNumber{ 0 }
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	
	
	AfxInitRichEdit();
}

CSerialApplicationDlg::~CSerialApplicationDlg()
{
	delete m_pFont;
}

void CSerialApplicationDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_REDIT_VIEW, m_edView);
	DDX_Text(pDX, IDC_ED_PORT_NUM, m_nPortNumber);
}

BEGIN_MESSAGE_MAP(CSerialApplicationDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BTTN_SWIPE_CARD, &CSerialApplicationDlg::OnBnClickedBttnSwipeCard)
	ON_BN_CLICKED(IDC_BTTN_OPEN_PORT, &CSerialApplicationDlg::OnBnClickedBttnOpenPort)
	ON_BN_CLICKED(IDC_BTTN_CLOSE_PORT, &CSerialApplicationDlg::OnBnClickedBttnClosePort)
	ON_BN_CLICKED(IDC_BTTN_SEND_SELECTED, &CSerialApplicationDlg::OnBnClickedBttnSendSelected)
END_MESSAGE_MAP()


BOOL CSerialApplicationDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// Agregar el elemento de menú "Acerca de..." al menú del sistema.

	// IDM_ABOUTBOX debe estar en el intervalo de comandos del sistema.
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


	SetIcon(m_hIcon, TRUE);			// Establecer icono grande
	SetIcon(m_hIcon, FALSE);		// Establecer icono pequeño


	LOGFONT		LogFont;

	memset(&LogFont, 0, sizeof(LOGFONT));

	LogFont.lfHeight = 32;
	LogFont.lfEscapement = GM_COMPATIBLE;
	LogFont.lfOrientation = GM_COMPATIBLE;
	LogFont.lfWeight = FW_DONTCARE;
	LogFont.lfCharSet = ANSI_CHARSET;
	LogFont.lfOutPrecision = OUT_OUTLINE_PRECIS;
	LogFont.lfClipPrecision = CLIP_DEFAULT_PRECIS;
	LogFont.lfQuality = DEFAULT_QUALITY;
	LogFont.lfPitchAndFamily = DEFAULT_PITCH;
	LogFont.lfItalic = FALSE;
	LogFont.lfStrikeOut = FALSE;
	LogFont.lfUnderline = FALSE;

	strcpy(LogFont.lfFaceName, "Verdana");

	m_pFont->CreateFontIndirect(&LogFont);
	m_edView.SetFont(m_pFont);
	

	addText("SerialApplication", BLACK);

	return TRUE;  // Devuelve TRUE  a menos que establezca el foco en un control
}

void CSerialApplicationDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

// Si agrega un botón Minimizar al cuadro de diálogo, necesitará el siguiente código
//  para dibujar el icono.  Para aplicaciones MFC que utilicen el modelo de documentos y vistas,
//  esta operación la realiza automáticamente el marco de trabajo.

void CSerialApplicationDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // Contexto de dispositivo para dibujo

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// Centrar icono en el rectángulo de cliente
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Dibujar el icono
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

// El sistema llama a esta función para obtener el cursor que se muestra mientras el usuario arrastra
//  la ventana minimizada.
HCURSOR CSerialApplicationDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CSerialApplicationDlg::OnBnClickedBttnSwipeCard()
{
}
/*
int CSerialApplicationDlg::getNumVisibleLines()
{
	CRect rect;
	long nFirstChar, nLastChar;
	long nFirstLine, nLastLine;

	// Get client rect of rich edit control
	m_edView.GetClientRect(rect);

	// Get character index close to upper left corner
	nFirstChar = m_edView.CharFromPos(CPoint(0, 0));

	// Get character index close to lower right corner
	nLastChar = m_edView.CharFromPos(CPoint(rect.right, rect.bottom));
	if (nLastChar < 0)
		nLastChar = m_edView.GetTextLength();

	// Convert to lines
	nFirstLine = m_edView.LineFromChar(nFirstChar);
	nLastLine = m_edView.LineFromChar(nLastChar);

	return (nLastLine - nFirstLine);
}
*/

void CSerialApplicationDlg::addText(const std::string& szText, COLORREF color)
{
	int nOldLines = 0; 
	int nNewLines = 0; 
	int nScroll = 0;
	long nInsertionPoint = 0;
	
	CHARRANGE cr{};
	CHARFORMAT cf{};

	nOldLines = m_edView.GetLineCount();

	cf.cbSize = sizeof(CHARFORMAT);
	cf.dwMask = CFM_COLOR;
	cf.dwEffects = 0;	// To disable CFE_AUTOCOLOR
	cf.crTextColor = color;

	nInsertionPoint = m_edView.GetWindowTextLength();

	nInsertionPoint = -1;
	m_edView.SetSel(nInsertionPoint, -1);

	m_edView.SetSelectionCharFormat(cf);

	m_edView.ReplaceSel(szText.c_str());

	nNewLines = m_edView.GetLineCount();

	nScroll = nNewLines - nOldLines;
	
	m_edView.LineScroll(nScroll);
	
	nInsertionPoint = m_edView.GetWindowTextLength();
	m_edView.SetSel(nInsertionPoint, -1);

	cf.crTextColor = BLACK;
	m_edView.SetSelectionCharFormat(cf);

	m_edView.ReplaceSel("\r\n");



	// Now this is the fix of CRichEditCtrl's abnormal behaviour when used
	// in an application not based on dialogs. Checking the focus prevents
	// us from scrolling when the CRichEditCtrl does so automatically,
	// even though ES_AUTOxSCROLL style is NOT set.

	/*
	int nVisible = GetNumVisibleLines();

	if (&m_edView != m_edView.GetFocus())
	{
		m_edView.LineScroll(INT_MAX);
		m_edView.LineScroll(1 - nVisible);
	}
	*/
}


void CSerialApplicationDlg::OnBnClickedBttnOpenPort()
{
	UpdateData();
	
	std::string msg{""};
	COLORREF color{RED};

	if (nullptr == m_pSerialPort)
	{
		std::string szCOMM{"COM"};
		szCOMM += std::to_string(m_nPortNumber);

		m_pSerialPort = new comm::Serial(szCOMM.c_str(), 19200);

		if(m_pSerialPort->open())
		{
			msg = "El puerto se abrio correctamente";
			color = BLUE;
		}
		else
		{
			msg = "No se pudo abrir el puerto ";
			msg += std::to_string(m_nPortNumber);
			msg += " Err:";
			msg += std::to_string(GetLastError());
		}
	}


	addText(msg, color);
}


void CSerialApplicationDlg::OnBnClickedBttnClosePort()
{
	closePort();
}


void CSerialApplicationDlg::sendSelected()
{

	if (m_pSerialPort)
	{
		auto selected = m_edView.GetSelText();

		if (selected.IsEmpty())
			return;

		auto* data = selected.GetBuffer();

		if (m_pSerialPort->write(data, static_cast<uint16_t>(strlen(data))))
		{
			std::string snd{ "send :" };
			snd += data;
			addText(snd, RGB(255, 0, 255));

			std::thread t(&CSerialApplicationDlg::read, this);
			t.detach();
		}


		selected.ReleaseBuffer();
	}
}

void CSerialApplicationDlg::OnBnClickedBttnSendSelected()
{
	sendSelected();
}

void CSerialApplicationDlg::closePort()
{
	if (m_pSerialPort)
	{
		delete m_pSerialPort;
		m_pSerialPort = nullptr;

		addText("El puerto se cerro correctamente", BLUE);
	}
}

void CSerialApplicationDlg::read()
{
	if (m_pSerialPort)
	{
		char data[2048] = {0};

		auto r = m_pSerialPort->read(data, sizeof(data));
		if (r > 0)
		{
			data[r] = 0;
			std::string rcv{ "data recibida: " };
			rcv += data;

			addText(rcv, GREEN);
		}
		else
			addText("No responde", RED);
	}
}
