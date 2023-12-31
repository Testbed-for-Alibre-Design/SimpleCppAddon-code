// SimpleCppAddon.cpp : Defines the initialization routines for the DLL.
//
#include "stdafx.h"
#include "SimpleCppAddon.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif
//
//	Note!
//
//		If this DLL is dynamically linked against the MFC
//		DLLs, any functions exported from this DLL which
//		call into MFC must have the AFX_MANAGE_STATE macro
//		added at the very beginning of the function.
//
//		For example:
//
//		extern "C" BOOL PASCAL EXPORT ExportedFunction()
//		{
//			AFX_MANAGE_STATE(AfxGetStaticModuleState());
//			// normal function body here
//		}
//
//		It is very important that this macro appear in each
//		function, prior to any calls into MFC.  This means that
//		it must appear as the first statement within the 
//		function, even before any object variable declarations
//		as their constructors may generate calls into the MFC
//		DLL.
//
//		Please see MFC Technical Notes 33 and 58 for additional
//		details.
//
/////////////////////////////////////////////////////////////////////////////
// CSimpleCppAddonApp
BEGIN_MESSAGE_MAP(CSimpleCppAddonApp, CWinApp)
	//{{AFX_MSG_MAP(CSimpleCppAddonApp)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()
CSimpleCppAddonApp::CSimpleCppAddonApp()
{
	m_pRoot = NULL;
	m_pAddOnInterface = NULL;
	m_windowHandle = NULL;
	m_pAddOnInterfaceObj = NULL;
}
CSimpleCppAddonApp theApp;
APICLIENTAPP_API void AddOnLoad(HWND windowHandle,
	VOID *pAutomationHook,
	VOID *reserved)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())
		if (NULL != pAutomationHook)
		{
			IAutomationHook*	pHook = (IAutomationHook *)pAutomationHook;
			theApp.m_pRoot = pHook->GetRoot();
		}
	theApp.m_windowHandle = windowHandle;
}
APICLIENTAPP_API IUnknown* GetAddOnInterface()
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())
		if (theApp.m_pAddOnInterfaceObj == NULL)
		{
			theApp.m_pAddOnInterfaceObj = new CAddOnInterface();
			theApp.m_pAddOnInterface = theApp.m_pAddOnInterfaceObj;
		}
	theApp.m_pAddOnInterface->AddRef();
	return (IUnknown *)theApp.m_pAddOnInterface;
}
APICLIENTAPP_API void AddOnInvoke(HWND windowHandle,
	VOID *pAutomationHook,
	LPCSTR sessionName,
	BOOL isLicensed,
	VOID *reserved1,
	VOID *reserved2)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())
}
APICLIENTAPP_API void AddOnUnload(HWND windowHandle,
	BOOL forceUnload,
	BOOL *cancel,       // set TRUE to cancel
	VOID *reserved1,
	VOID *reserved2)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())
		if (theApp.m_pAddOnInterfaceObj != NULL)
		{
			theApp.m_pAddOnInterfaceObj->cleanUp();
		}
	*cancel = FALSE;
}
