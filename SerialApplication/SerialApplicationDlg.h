
// EldarPinpadApplicationDlg.h: archivo de encabezado
//

#pragma once


constexpr COLORREF	BLACK	{ RGB(0, 0, 0) };
constexpr COLORREF	RED		{ RGB(255, 0, 0) };
constexpr COLORREF	BLUE	{ RGB(0, 0, 255) };
constexpr COLORREF	GREEN	{ RGB(73, 145, 67) };

// Cuadro de diálogo de CPinpadApplicationDlg
class CSerialApplicationDlg : public CDialogEx
{
// Construcción
public:
	CSerialApplicationDlg(CWnd* pParent = nullptr);
	virtual ~CSerialApplicationDlg();


// Datos del cuadro de diálogo
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_PINPADAPPLICATION_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// Compatibilidad con DDX/DDV


// Implementación
protected:

	HICON	m_hIcon;
	CFont* m_pFont;

	//int getNumVisibleLines();

	void addText(const std::string& szText, COLORREF color);
	void sendSelected();
	void closePort();
	void read();

	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()


public:
	afx_msg void OnBnClickedBttnSwipeCard();
private:
	CRichEditCtrl		m_edView;
	comm::Serial		*m_pSerialPort;

public:
	afx_msg void OnBnClickedBttnOpenPort();

private:
	int m_nPortNumber;
public:
	afx_msg void OnBnClickedBttnClosePort();
	afx_msg void OnBnClickedBttnSendSelected();
};
