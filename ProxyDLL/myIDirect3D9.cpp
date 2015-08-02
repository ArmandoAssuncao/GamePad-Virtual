// myIDirect3D9.cpp

#include "StdAfx.h"

MyIDirect3D9::MyIDirect3D9(IDirect3D9 *ID3D9Original){
    ID3D9 = ID3D9Original;
}

MyIDirect3D9::~MyIDirect3D9(void){ }

HRESULT  __stdcall MyIDirect3D9::QueryInterface(REFIID riid, void** ppvObj){
	//MessageBox(NULL, LPCSTR("MyIDirect3D9: QUERY INTERFACE"), LPCSTR("proxy"), MB_OK);

	*ppvObj = NULL;

	// Always set out parameter to NULL, validating it first.
	if (!ppvObj) {
		return E_INVALIDARG;
	}

	if (riid == IID_IUnknown) {
		*ppvObj = this;
		ID3D9->QueryInterface(riid, ppvObj);
		return NOERROR;
	}

	return E_NOINTERFACE;
}

ULONG    __stdcall MyIDirect3D9::AddRef(void){
	//MessageBox(NULL, LPCSTR("MyIDirect3D9: AddRef"), LPCSTR("proxy dll"), 0);//TODO

    return(ID3D9->AddRef());
}

ULONG    __stdcall MyIDirect3D9::Release(void){
	//MessageBox(NULL, LPCSTR("MyIDirect3D9: Release"), LPCSTR("proxy dll"), 0);//TODO

	// call original routine
	ULONG count = ID3D9->Release();
	
	if (count == 0){
  	    delete(this); 
	}

	return(count);
}

HRESULT __stdcall MyIDirect3D9::RegisterSoftwareDevice(void* pInitializeFunction){
	return(ID3D9->RegisterSoftwareDevice(pInitializeFunction));
}

UINT __stdcall MyIDirect3D9::GetAdapterCount(void){
	return(ID3D9->GetAdapterCount());
}

HRESULT __stdcall MyIDirect3D9::GetAdapterIdentifier(UINT Adapter,DWORD Flags,D3DADAPTER_IDENTIFIER9* pIdentifier){
	return(ID3D9->GetAdapterIdentifier(Adapter,Flags,pIdentifier));
}

UINT __stdcall MyIDirect3D9::GetAdapterModeCount(UINT Adapter, D3DFORMAT Format){
	return(ID3D9->GetAdapterModeCount(Adapter, Format));
}

HRESULT __stdcall MyIDirect3D9::EnumAdapterModes(UINT Adapter,D3DFORMAT Format,UINT Mode,D3DDISPLAYMODE* pMode){
	return(ID3D9->EnumAdapterModes(Adapter,Format,Mode,pMode));
}

HRESULT __stdcall MyIDirect3D9::GetAdapterDisplayMode( UINT Adapter,D3DDISPLAYMODE* pMode){
	return(ID3D9->GetAdapterDisplayMode(Adapter,pMode));
}

HRESULT __stdcall MyIDirect3D9::CheckDeviceType(UINT iAdapter,D3DDEVTYPE DevType,D3DFORMAT DisplayFormat,D3DFORMAT BackBufferFormat,BOOL bWindowed){
	return(ID3D9->CheckDeviceType(iAdapter,DevType,DisplayFormat,BackBufferFormat,bWindowed));
}

HRESULT __stdcall MyIDirect3D9::CheckDeviceFormat(UINT Adapter,D3DDEVTYPE DeviceType,D3DFORMAT AdapterFormat,DWORD Usage,D3DRESOURCETYPE RType,D3DFORMAT CheckFormat){
	return(ID3D9->CheckDeviceFormat(Adapter,DeviceType,AdapterFormat,Usage,RType,CheckFormat));
}

HRESULT __stdcall MyIDirect3D9::CheckDeviceMultiSampleType(UINT Adapter,D3DDEVTYPE DeviceType,D3DFORMAT SurfaceFormat,BOOL Windowed,D3DMULTISAMPLE_TYPE MultiSampleType,DWORD* pQualityLevels){
	return(ID3D9->CheckDeviceMultiSampleType(Adapter,DeviceType,SurfaceFormat,Windowed,MultiSampleType,pQualityLevels));
}

HRESULT __stdcall MyIDirect3D9::CheckDepthStencilMatch(UINT Adapter,D3DDEVTYPE DeviceType,D3DFORMAT AdapterFormat,D3DFORMAT RenderTargetFormat,D3DFORMAT DepthStencilFormat){
	return(ID3D9->CheckDepthStencilMatch(Adapter,DeviceType,AdapterFormat,RenderTargetFormat,DepthStencilFormat));
}

HRESULT __stdcall MyIDirect3D9::CheckDeviceFormatConversion(UINT Adapter,D3DDEVTYPE DeviceType,D3DFORMAT SourceFormat,D3DFORMAT TargetFormat){
	return(ID3D9->CheckDeviceFormatConversion(Adapter,DeviceType,SourceFormat,TargetFormat));
}

HRESULT __stdcall MyIDirect3D9::GetDeviceCaps(UINT Adapter,D3DDEVTYPE DeviceType,D3DCAPS9* pCaps){
	return(ID3D9->GetDeviceCaps(Adapter,DeviceType,pCaps));
}

HMONITOR __stdcall MyIDirect3D9::GetAdapterMonitor(UINT Adapter){
	return(ID3D9->GetAdapterMonitor(Adapter));
}

HRESULT __stdcall MyIDirect3D9::CreateDevice(UINT Adapter,D3DDEVTYPE DeviceType,HWND hFocusWindow,DWORD BehaviorFlags,D3DPRESENT_PARAMETERS* pPresentationParameters,IDirect3DDevice9** ppReturnedDeviceInterface){
	//MessageBox(NULL, LPCSTR("MyIDirect3D9: CREATE DEVICE"), LPCSTR("MyIDirect3D9"), 0);

	// we intercept this call and provide our own "fake" Device Object
	HRESULT hres = ID3D9->CreateDevice(Adapter, DeviceType, hFocusWindow, BehaviorFlags, pPresentationParameters, ppReturnedDeviceInterface);

	// global var
	extern MyIDirect3DDevice9* gl_pMyIDirect3DDevice9;
	
	// Create our own Device object and store it in global pointer
	// note: the object will delete itself once Ref count is zero (similar to COM objects)
	gl_pMyIDirect3DDevice9 = new MyIDirect3DDevice9(*ppReturnedDeviceInterface);

	// store our pointer (the fake one) for returning it to the calling program
	*ppReturnedDeviceInterface = gl_pMyIDirect3DDevice9;

	return(hres);
}