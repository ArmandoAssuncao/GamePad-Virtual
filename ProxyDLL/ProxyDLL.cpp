//proxyDLL.cpp
#include "stdafx.h"
#include "proxydll.h"

// global variables
#pragma data_seg (".d3d9_shared")
MyIDirect3DDevice9* gl_pMyIDirect3DDevice9;
MyIDirect3D9*		gl_pMyIDirect3D9;
HMODULE				original_D3D9_DLL;
#pragma data_seg ()

_declspec(dllexport) void AssignMyDirect3DPtr(int *value);

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