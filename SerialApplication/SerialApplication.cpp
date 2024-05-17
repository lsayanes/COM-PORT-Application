

#include "pch.h"
#include "framework.h"

#include <string>

#include <Comm.h>

#include "SerialApplication.h"
#include "SerialApplicationDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


BEGIN_MESSAGE_MAP(CSerialApplicationApp, CWinApp)
	ON_COMMAND(ID_HELP, &CWinApp::OnHelp)
END_MESSAGE_MAP()


CSerialApplicationApp::CSerialApplicationApp()
{
	// admite Administrador de reinicio
	m_dwRestartManagerSupportFlags = AFX_RESTART_MANAGER_SUPPORT_RESTART;

	// TODO: agregar aquí el código de construcción,
	// Colocar toda la inicialización importante en InitInstance
}


CSerialApplicationApp theApp;


BOOL CSerialApplicationApp::InitInstance()
{
// TODO: llamar a AfxInitRichEdit2() para inicializar la biblioteca richedit2.\n"	CWinApp::InitInstance();


	AfxEnableControlContainer();

	// Crear el administrador de shell, en caso de que el cuadro de diálogo contenga
	// alguna vista de árbol de shell o controles de vista de lista de shell.
	CShellManager *pShellManager = new CShellManager;

	// Activar el administrador visual "nativo de Windows" para habilitar temas en controles MFC
	CMFCVisualManager::SetDefaultManager(RUNTIME_CLASS(CMFCVisualManagerWindows));

	SetRegistryKey(_T("SerialApplication"));

	CSerialApplicationDlg dlg;
	m_pMainWnd = &dlg;
	INT_PTR nResponse = dlg.DoModal();
	if (nResponse == IDOK)
	{
		// TODO: insertar aquí el código para controlar
		//  cuándo se descarta el cuadro de diálogo con Aceptar
	}
	else if (nResponse == IDCANCEL)
	{
		// TODO: insertar aquí el código para controlar
		//  cuándo se descarta el cuadro de diálogo con Cancelar
	}
	else if (nResponse == -1)
	{
		TRACE(traceAppMsg, 0, "Advertencia: la aplicación está finalizando porque hubo un error al crear el cuadro de diálogo.\n");
		TRACE(traceAppMsg, 0, "Advertencia: si usa controles MFC en el cuadro de diálogo, no puede usar #define _AFX_NO_MFC_CONTROLS_IN_DIALOGS.\n");
	}

	// Eliminar el administrador de shell creado anteriormente.
	if (pShellManager != nullptr)
	{
		delete pShellManager;
	}

#if !defined(_AFXDLL) && !defined(_AFX_NO_MFC_CONTROLS_IN_DIALOGS)
	ControlBarCleanUp();
#endif

	// Dado que el cuadro de diálogo se ha cerrado, devolver FALSE para salir
	//  de la aplicación en vez de iniciar el suministro de mensajes de dicha aplicación.
	return FALSE;
}

