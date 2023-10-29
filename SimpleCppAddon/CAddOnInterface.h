#pragma once
// CMotionAddOnInterface.h: interface for the CMotionAddOnInterface class.
//
//////////////////////////////////////////////////////////////////////
#if !defined(AFX_CMOTIONADDONINTERFACE_H__CF0F6671_6A1F_4CBC_9BB2_2FF1909A2DD8__INCLUDED_)
#define AFX_CMOTIONADDONINTERFACE_H__CF0F6671_6A1F_4CBC_9BB2_2FF1909A2DD8__INCLUDED_
#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
class CShowUICommand;
class CAddOnInterface : public IAlibreAddOn
{
public:
	CAddOnInterface();
	virtual ~CAddOnInterface();
public:
	// IUnknown
	HRESULT _stdcall QueryInterface(REFIID riid, void **ppObj);
	ULONG _stdcall AddRef();
	ULONG _stdcall Release();
	// IDispatch
	long _stdcall GetTypeInfoCount(UINT FAR* pctinfo);
	long _stdcall GetTypeInfo(
		UINT iTInfo,
		LCID lcid,
		ITypeInfo FAR* FAR* ppTInfo);
	long _stdcall GetIDsOfNames(
		REFIID riid,
		OLECHAR FAR* FAR* rgszNames,
		UINT cNames,
		LCID lcid,
		DISPID FAR* rgDispId);
	long _stdcall Invoke(
		DISPID dispidMember,
		REFIID riid,
		LCID lcid,
		WORD wFlags,
		DISPPARAMS FAR* pDispParams,
		VARIANT FAR* pVarResult,
		EXCEPINFO FAR* pExcepInfo,
		UINT FAR* puArgErr);
	// Methods from IAlibreAddOn
	HRESULT _stdcall get_RootMenuItem(/*[out,retval]*/ long *pRootMenuID);
	HRESULT _stdcall HasSubMenus(/*[in]*/ long menuID, /*[out,retval]*/ VARIANT_BOOL *pHasSubMenus);
	HRESULT _stdcall SubMenuItems(/*[in]*/ long menuID, /*[out,retval]*/ SAFEARRAY **pSubMenuIDs);
	HRESULT _stdcall MenuItemText(/*[in]*/ long menuID, /*[out,retval]*/ BSTR* pMenuDisplayText);
	HRESULT _stdcall HasPersistentDataToSave(/* [in] */ BSTR sessionIdentifier, /*[retval][out] */ VARIANT_BOOL *IsPopup);
	HRESULT _stdcall PopupMenu(/*[in]*/ long menuID, /*[out,retval]*/ VARIANT_BOOL *IsPopup);
	HRESULT _stdcall MenuItemState(/*[in]*/ long menuID,
		/*[in] */ BSTR sessionIdentifier,
		/*[out, retval]*/ enum ADDONMenuStates *pType);
	HRESULT _stdcall MenuItemToolTip(/*[in]*/ long menuID, /*[out, retval]*/ BSTR *pToolTip);
	HRESULT _stdcall InvokeCommand(/*[in]*/ long menuID,
		/* [in] */ BSTR sessionIdentifier,
		/*[out, retval]*/ IAlibreAddOnCommand **pCommand);
	HRESULT _stdcall LoadData(/*[in]*/ struct IStream * ppCustomData, /*[in]*/ BSTR sessionIdentifier);
	HRESULT _stdcall SaveData(/*[in]*/ struct IStream * pCustomData, /*[in]*/ BSTR sessionIdentifier);
	HRESULT _stdcall setIsAddOnLicensed(/*[in]*/ VARIANT_BOOL isLicensed);
	HRESULT _stdcall MenuIcon(/*[in]*/ long menuID, /*[out,retval]*/ BSTR *pMenuIconPath);
	HRESULT _stdcall UseDedicatedRibbonTab(/*[out,retval]*/ VARIANT_BOOL *pFlag);
public:
	void cleanUp();
private:
	long			m_nRefCount;
	ITypeInfo		*m_ptinfo;
	SAFEARRAY		*m_RootSubMenuIDs;
	CMap<CString, LPCTSTR, CShowUICommand*, CShowUICommand*& > m_MapSesIDToShowUICmd; // maps the session-id to its "Activate UI" command, if activated
	void			initializeMenus();
public:
	void RemoveUICommandForSession(CString strSessionID);
};
#endif // !defined(AFX_CMOTIONADDONINTERFACE_H__CF0F6671_6A1F_4CBC_9BB2_2FF1909A2DD8__INCLUDED_)
