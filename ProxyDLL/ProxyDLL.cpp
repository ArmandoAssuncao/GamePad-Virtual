//proxyDLL.cpp
#include "stdafx.h"
#include "proxydll.h"

// global variables
#pragma data_seg (".d3d9_shared")
MyIDirect3DDevice9* gl_pMyIDirect3DDevice9;
MyIDirect3D9*		gl_pMyIDirect3D9;
HMODULE				original_D3D9_DLL;
#pragma data_seg ()

_declspec(dllexport) void AssignMyD3DDeviceSlimDX(int *value);
_declspec(dllexport) void AssignMyD3DDeviceSharpDX(int *value);

BOOL APIENTRY DllMain(HANDLE hModule, DWORD ul_reason_for_call, LPVOID lpReserved) {
	// to avoid compiler lvl4 warnings
	LPVOID lpDummy = lpReserved;
	lpDummy = NULL;

	switch (ul_reason_for_call) {
		case DLL_PROCESS_ATTACH: InitInstance(hModule); break;
		case DLL_PROCESS_DETACH: ExitInstance(); break;
		case DLL_THREAD_ATTACH: break;
		case DLL_THREAD_DETACH: break;
	}
	return TRUE;
}

IDirect3D9* WINAPI Direct3DCreate9(UINT SDKVersion) {
	//MessageBox(NULL, LPCSTR("Direct3DCreate9"), LPCSTR("proxy dll"), 0); //TODO
	//char strPtrDevice[60]; //TODO

	if (!original_D3D9_DLL) LoadOriginalDll();

	typedef IDirect3D9* (WINAPI *DIRECT3DCREATE9)(UINT);
	DIRECT3DCREATE9 original_Direct3DCreate9 = (DIRECT3DCREATE9)GetProcAddress(original_D3D9_DLL, "Direct3DCreate9");

	if (!original_Direct3DCreate9) {
		OutputDebugString("ProxyDLL: original_Direct3DCreate9 ERROR ****\r\n");
		::ExitProcess(0);
	}

	IDirect3D9 *pIDirect3D9_orig = original_Direct3DCreate9(SDKVersion);
	
	// Create my IDirect3D9 object and store pointer to original object there.
	// note: the object will delete itself once Ref count is zero (similar to COM objects)
	//if (!gl_pMyIDirect3D9)
		gl_pMyIDirect3D9 = new MyIDirect3D9(pIDirect3D9_orig);
		
	//MessageBox(NULL, LPCSTR("Running my d3d9.dll"), LPCSTR("proxy dll"), 0); //TODO

	return gl_pMyIDirect3D9; //return with the modifications
	//return pIDirect3D9_orig; //without proxy, continues normally
}

int WINAPI D3DPERF_BeginEvent(D3DCOLOR col, LPCWSTR wszName) {
	typedef int (WINAPI *D3DPERF_BEGINEVENT)(DWORD, LPCWSTR);
	D3DPERF_BEGINEVENT original_D3DPREF_BeginEvent = (D3DPERF_BEGINEVENT)GetProcAddress(original_D3D9_DLL, "D3DPERF_BeginEvent");

	return original_D3DPREF_BeginEvent(col, wszName);
}

int WINAPI D3DPERF_EndEvent(void){
	typedef int (WINAPI *D3DPERF_ENDEVENT)();
	D3DPERF_ENDEVENT original_D3DPREF_EndEvent = (D3DPERF_ENDEVENT)GetProcAddress(original_D3D9_DLL, "D3DPERF_EndEvent");

	return original_D3DPREF_EndEvent();
}

void WINAPI D3DPERF_SetMarker(D3DCOLOR col, LPCWSTR wszName) {
	typedef void (WINAPI *D3DPERF_SETMARKER)(D3DCOLOR, LPCWSTR);
	D3DPERF_SETMARKER original_D3DPERF_SetMarker = (D3DPERF_SETMARKER)GetProcAddress(original_D3D9_DLL, "D3DPERF_SetMarker");

	original_D3DPERF_SetMarker(col, wszName);
}

void WINAPI D3DPERF_SetRegion(D3DCOLOR col, LPCWSTR wszName) {
	typedef void (WINAPI *D3DPERF_SETREGION)(D3DCOLOR, LPCWSTR);
	D3DPERF_SETREGION original_D3DPERF_SetRegion = (D3DPERF_SETREGION)GetProcAddress(original_D3D9_DLL, "D3DPERF_SetRegion");

	original_D3DPERF_SetRegion(col, wszName);
}

BOOL WINAPI D3DPERF_QueryRepeatFrame(void) {
	typedef BOOL(WINAPI *D3DPERF_QUERY_REPEATFRAME)();
	D3DPERF_QUERY_REPEATFRAME original_D3DPERF_QueryRepeatFrame = (D3DPERF_QUERY_REPEATFRAME)GetProcAddress(original_D3D9_DLL, "D3DPERF_QueryRepeatFrame");

	return original_D3DPERF_QueryRepeatFrame();
}

void WINAPI D3DPERF_SetOptions(DWORD dwOptions) {
	typedef void (WINAPI *D3DPERF_SETOPTIONS)(DWORD);
	D3DPERF_SETOPTIONS original_D3DPERF_SetOptions = (D3DPERF_SETOPTIONS)GetProcAddress(original_D3D9_DLL, "D3DPERF_SetOptions");

	original_D3DPERF_SetOptions(dwOptions);
}

DWORD WINAPI D3DPERF_GetStatus(void) {
	typedef DWORD (WINAPI *D3DPERF_GETSTATUS)();
	D3DPERF_GETSTATUS original_D3DPERF_GetStatus = (D3DPERF_GETSTATUS)GetProcAddress(original_D3D9_DLL, "D3DPERF_GetStatus");

	return original_D3DPERF_GetStatus();
}

void InitInstance(HANDLE hModule) {
	OutputDebugString("ProxyDLL: InitInstance called.\r\n");

	original_D3D9_DLL = NULL;
	gl_pMyIDirect3DDevice9 = NULL;
	gl_pMyIDirect3D9 = NULL;

	if (!original_D3D9_DLL) LoadOriginalDll();
}

void LoadOriginalDll(void) {
	char buffer[MAX_PATH];

	// Getting path to system dir
	::GetSystemDirectory(buffer, MAX_PATH);

	// Append dll name
	strcat_s(buffer, MAX_PATH, "\\d3d9.dll");

	// try to load the system's d3d9.dll, if pointer empty
	if (!original_D3D9_DLL) original_D3D9_DLL = ::LoadLibrary(buffer);

	// Debug
	if (!original_D3D9_DLL) {
		OutputDebugString("ProxyDLL: Load d3d9.dll ERROR ****\r\n");
		::ExitProcess(0);
	}
}

void ExitInstance() {
	OutputDebugString("ProxyDLL: ExitInstance called.\r\n");

	// Release the system's d3d9.dll
	if (original_D3D9_DLL) {
		::FreeLibrary(original_D3D9_DLL);
		original_D3D9_DLL = NULL;
	}
}

//Function only for test
void testDebug() {
	if (!original_D3D9_DLL) LoadOriginalDll();

	typedef IDirect3D9* (WINAPI *DIRECT3DCREATE9)(UINT);
	DIRECT3DCREATE9 original_Direct3DCreate9 = (DIRECT3DCREATE9)GetProcAddress(original_D3D9_DLL, "Direct3DCreate9");

	if (!original_Direct3DCreate9) {
		OutputDebugString("ProxyDLL: original_Direct3DCreate9 ERROR ****\r\n");
		::ExitProcess(0);
	}

	IDirect3D9 *pIDirect3D9_orig = original_Direct3DCreate9(D3D_SDK_VERSION);

	// CREATE DEVICE ///////////////////////////////////////////////////////////////////////////////
	HWND hWnd = CreateWindowA("BUTTON", "Temporary Window", WS_OVERLAPPEDWINDOW, 400, 500, 300, 300, NULL, NULL, original_D3D9_DLL, NULL);

	D3DDISPLAYMODE d3dDMODE;

	if (FAILED(pIDirect3D9_orig->GetAdapterDisplayMode(D3DADAPTER_DEFAULT, &d3dDMODE))) {
		MessageBox(NULL, LPCSTR("ProxyDLL: GetAdapterDisplayMode ERROR"), LPCSTR("proxy dll"), 0); //TODO
		::ExitProcess(0);
	}

	D3DCAPS9 d3dCaps;
	if (FAILED(pIDirect3D9_orig->GetDeviceCaps(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, &d3dCaps))) {
		MessageBox(NULL, LPCSTR("ProxyDLL: GetAdapterDisplayMode ERROR"), LPCSTR("proxy dll"), 0); //TODO
		::ExitProcess(0); 
	}

	DWORD dwBehaviorFlags = 0;
	if (d3dCaps.VertexProcessingCaps != 0) {
		dwBehaviorFlags = D3DCREATE_HARDWARE_VERTEXPROCESSING;
		//MessageBox(NULL, LPCSTR("HARDWARE_VERTEXPROCESSING"), LPCSTR("proxy dll"), 0); //TODO
	}
	else {
		dwBehaviorFlags = D3DCREATE_SOFTWARE_VERTEXPROCESSING;
		MessageBox(NULL, LPCSTR("SOFTWARE_VERTEXPROCESSING"), LPCSTR("proxy dll"), 0); //TODO
	}

	D3DPRESENT_PARAMETERS d3dpp;
	memset(&d3dpp, 0, sizeof(d3dpp));

	/*//d3dpp.AutoDepthStencilFormat = D3DFMT_D16;
	//d3dpp.BackBufferCount = 3;
	d3dpp.BackBufferFormat = d3dDMODE.Format;
	//d3dpp.BackBufferHeight = d3dDMODE.Height;
	//d3dpp.BackBufferWidth = d3dDMODE.Width;
	d3dpp.EnableAutoDepthStencil = FALSE;
	//d3dpp.Flags = D3DPRESENTFLAG_VIDEO;
	//d3dpp.FullScreen_RefreshRateInHz = 0;
	d3dpp.hDeviceWindow;
	d3dpp.MultiSampleQuality = 0;
	d3dpp.MultiSampleType = D3DMULTISAMPLE_2_SAMPLES;
	d3dpp.PresentationInterval = D3DPRESENT_INTERVAL_IMMEDIATE;
	d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;
	d3dpp.Windowed = TRUE;*/


	d3dpp.BackBufferFormat = d3dDMODE.Format;
	d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;
	d3dpp.Windowed = TRUE;
	d3dpp.EnableAutoDepthStencil = TRUE;
	d3dpp.AutoDepthStencilFormat = D3DFMT_D16;
	d3dpp.PresentationInterval = D3DPRESENT_INTERVAL_IMMEDIATE;

	IDirect3DDevice9 *pd3dDevice = NULL;
	HRESULT hResCreateDevice = pIDirect3D9_orig->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, hWnd, dwBehaviorFlags, &d3dpp, &pd3dDevice);
	if (FAILED(hResCreateDevice)) {
		MessageBox(NULL, LPCSTR("Error CreateDevice"), LPCSTR("proxy dll"), 0); //TODO
		::ExitProcess(0);//TODO
	}

	//All Formats
	/*long D3DFormats[] = {
	_D3DFORMAT::D3DFMT_A1, _D3DFORMAT::D3DFMT_A16B16G16R16, _D3DFORMAT::D3DFMT_A16B16G16R16F, _D3DFORMAT::D3DFMT_A1R5G5B5
	, _D3DFORMAT::D3DFMT_A2B10G10R10, _D3DFORMAT::D3DFMT_A2B10G10R10_XR_BIAS, _D3DFORMAT::D3DFMT_A2R10G10B10, _D3DFORMAT::D3DFMT_L6V5U5
	, _D3DFORMAT::D3DFMT_A2W10V10U10, _D3DFORMAT::D3DFMT_A32B32G32R32F, _D3DFORMAT::D3DFMT_A4L4, _D3DFORMAT::D3DFMT_A4R4G4B4
	, _D3DFORMAT::D3DFMT_A8, _D3DFORMAT::D3DFMT_A8B8G8R8, _D3DFORMAT::D3DFMT_A8L8, _D3DFORMAT::D3DFMT_A8P8
	, _D3DFORMAT::D3DFMT_A8R3G3B2, _D3DFORMAT::D3DFMT_A8R8G8B8, _D3DFORMAT::D3DFMT_BINARYBUFFER, _D3DFORMAT::D3DFMT_CxV8U8
	, _D3DFORMAT::D3DFMT_D15S1, _D3DFORMAT::D3DFMT_D16, _D3DFORMAT::D3DFMT_D16_LOCKABLE, _D3DFORMAT::D3DFMT_D24FS8
	, _D3DFORMAT::D3DFMT_D24S8, _D3DFORMAT::D3DFMT_D24X4S4, _D3DFORMAT::D3DFMT_D24X8, _D3DFORMAT::D3DFMT_D32
	, _D3DFORMAT::D3DFMT_D32F_LOCKABLE, _D3DFORMAT::D3DFMT_D32_LOCKABLE, _D3DFORMAT::D3DFMT_DXT1, _D3DFORMAT::D3DFMT_DXT2
	, _D3DFORMAT::D3DFMT_DXT3, _D3DFORMAT::D3DFMT_DXT4, _D3DFORMAT::D3DFMT_DXT5, _D3DFORMAT::D3DFMT_FORCE_DWORD
	, _D3DFORMAT::D3DFMT_G16R16, _D3DFORMAT::D3DFMT_G16R16F, _D3DFORMAT::D3DFMT_G32R32F, _D3DFORMAT::D3DFMT_G8R8_G8B8
	, _D3DFORMAT::D3DFMT_INDEX16, _D3DFORMAT::D3DFMT_INDEX32, _D3DFORMAT::D3DFMT_L16, _D3DFORMAT::D3DFMT_L8
	, _D3DFORMAT::D3DFMT_MULTI2_ARGB8, _D3DFORMAT::D3DFMT_P8, _D3DFORMAT::D3DFMT_Q16W16V16U16, _D3DFORMAT::D3DFMT_Q8W8V8U8
	, _D3DFORMAT::D3DFMT_R16F, _D3DFORMAT::D3DFMT_R32F, _D3DFORMAT::D3DFMT_R3G3B2, _D3DFORMAT::D3DFMT_R5G6B5
	, _D3DFORMAT::D3DFMT_R8G8B8, _D3DFORMAT::D3DFMT_R8G8_B8G8, _D3DFORMAT::D3DFMT_S8_LOCKABLE, _D3DFORMAT::D3DFMT_UNKNOWN
	, _D3DFORMAT::D3DFMT_UYVY, _D3DFORMAT::D3DFMT_V16U16, _D3DFORMAT::D3DFMT_V8U8, _D3DFORMAT::D3DFMT_VERTEXDATA
	, _D3DFORMAT::D3DFMT_X1R5G5B5, _D3DFORMAT::D3DFMT_X4R4G4B4, _D3DFORMAT::D3DFMT_X8B8G8R8, _D3DFORMAT::D3DFMT_X8L8V8U8
	, _D3DFORMAT::D3DFMT_X8R8G8B8, _D3DFORMAT::D3DFMT_YUY2
	//, _D3DFORMAT:, _D3DFORMAT:, _D3DFORMAT:, _D3DFORMAT:
	};
	for (int i = 0; i < 66; i++) {
	d3dpp.AutoDepthStencilFormat = (_D3DFORMAT)D3DFormats[i];

	HRESULT hResCreateDevice = pIDirect3D9_orig->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, hWnd, dwBehaviorFlags, &d3dpp, &pd3dDevice);
	if (!FAILED(hResCreateDevice)) {
	//_ltoa_s(D3DFormats[i], strDevice, 60, 10);
	//MessageBox(NULL, LPCSTR(strDevice), LPCSTR("TESTE"), MB_OK);
	_itoa_s(i + 1, strDevice, 60, 10);
	MessageBox(NULL, LPCSTR(strDevice), LPCSTR("FORMAT SUPPORT"), MB_OK);
	}
	}*/


	//pd3dDevice->Release();
	//pIDirect3D9_orig->Release();
	//DestroyWindow(hWnd);

	//////////////////////////////////////////////////////////////

	int dev = (int)pd3dDevice;
	AssignMyD3DDeviceSlimDX(&dev); //SlimDX
	AssignMyD3DDeviceSharpDX(&dev); //SharpDX

}