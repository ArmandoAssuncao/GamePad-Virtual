#include "StdAfx.h"
#include "MyIDirect3DDevice9.h"

_declspec(dllexport) void AssignMyD3DDeviceSlimDX(int *value);
_declspec(dllexport) void AssignMyD3DDeviceSharpDX(int *value);

// Function test
void MyIDirect3DDevice9::testCreateBox(void) {
	D3DRECT rec = { 1, 1, 50, 50 };
	ID3DDevice9->Clear(1, &rec, D3DCLEAR_TARGET, D3DCOLOR_ARGB(255, 255, 0, 0), 0, 0);
}



////////////////////////////////// Functions of the interface IDirect3DDevice9 //////////////////////////////////

MyIDirect3DDevice9::MyIDirect3DDevice9(IDirect3DDevice9* ID3DDevice9Original) {
	ID3DDevice9 = ID3DDevice9Original; // store original object
}

MyIDirect3DDevice9::~MyIDirect3DDevice9(void) {
}

HRESULT MyIDirect3DDevice9::QueryInterface(REFIID riid, void** ppvObj) {
	//MessageBox(NULL, LPCSTR("QUERYINTERFACE DIRECT3DDEVICE"), LPCSTR("proxy dll"), 0); //TODO

	int devicePtr = (int)ID3DDevice9;
	AssignMyD3DDeviceSlimDX(&devicePtr); // draw in device
	AssignMyD3DDeviceSharpDX(&devicePtr);

	*ppvObj = NULL;

	HRESULT hRes = ID3DDevice9->QueryInterface(riid, ppvObj);

	if (hRes == NOERROR) {
		*ppvObj = this;
	}

	return hRes;
}

ULONG MyIDirect3DDevice9::AddRef(void)
{
    return(ID3DDevice9->AddRef());
}

ULONG MyIDirect3DDevice9::Release(void) {
	// ATTENTION: This is a booby-trap ! Watch out !
	// If we create our own sprites, surfaces, etc. (thus increasing the ref counter
	// by external action), we need to delete that objects before calling the original
	// Release function	
	
	// global var
	extern MyIDirect3DDevice9* gl_pMyIDirect3DDevice9;

    // release/delete own objects
    // .....
	
	// Calling original function now
	ULONG count = ID3DDevice9->Release();
		
    // now, the Original Object has deleted itself, so do we here
	gl_pMyIDirect3DDevice9 = NULL;
	delete(this);  // destructor will be called automatically

	return (count);
}

HRESULT MyIDirect3DDevice9::Present(CONST RECT* pSourceRect, CONST RECT* pDestRect, HWND hDestWindowOverride, CONST RGNDATA* pDirtyRegion) {
	this->testCreateBox(); // draw in device

	int devicePtr = (int)ID3DDevice9;
	AssignMyD3DDeviceSlimDX(&devicePtr); // draw in device
	AssignMyD3DDeviceSharpDX(&devicePtr);

	// call original routine
	HRESULT hres = ID3DDevice9->Present(pSourceRect, pDestRect, hDestWindowOverride, pDirtyRegion);

	return (hres);
}

HRESULT MyIDirect3DDevice9::TestCooperativeLevel(void)
{
    return(ID3DDevice9->TestCooperativeLevel());
}

UINT MyIDirect3DDevice9::GetAvailableTextureMem(void)
{
    return(ID3DDevice9->GetAvailableTextureMem());
}

HRESULT MyIDirect3DDevice9::EvictManagedResources(void)
{
    return(ID3DDevice9->EvictManagedResources());
}

HRESULT MyIDirect3DDevice9::GetDirect3D(IDirect3D9** ppD3D9)
{
    return(ID3DDevice9->GetDirect3D(ppD3D9));
}

HRESULT MyIDirect3DDevice9::GetDeviceCaps(D3DCAPS9* pCaps)
{
    return(ID3DDevice9->GetDeviceCaps(pCaps));
}

HRESULT MyIDirect3DDevice9::GetDisplayMode(UINT iSwapChain,D3DDISPLAYMODE* pMode)
{
    return(ID3DDevice9->GetDisplayMode(iSwapChain, pMode));
}

HRESULT MyIDirect3DDevice9::GetCreationParameters(D3DDEVICE_CREATION_PARAMETERS *pParameters)
{
    return(ID3DDevice9->GetCreationParameters(pParameters));
}

HRESULT MyIDirect3DDevice9::SetCursorProperties(UINT XHotSpot,UINT YHotSpot,IDirect3DSurface9* pCursorBitmap)
{
    return(ID3DDevice9->SetCursorProperties(XHotSpot,YHotSpot,pCursorBitmap));
}

void    MyIDirect3DDevice9::SetCursorPosition(int X,int Y,DWORD Flags)
{
    return(ID3DDevice9->SetCursorPosition(X,Y,Flags));
}

BOOL    MyIDirect3DDevice9::ShowCursor(BOOL bShow)
{
    return(ID3DDevice9->ShowCursor(bShow));
}

HRESULT MyIDirect3DDevice9::CreateAdditionalSwapChain(D3DPRESENT_PARAMETERS* pPresentationParameters,IDirect3DSwapChain9** pSwapChain)  
{
    return(ID3DDevice9->CreateAdditionalSwapChain(pPresentationParameters,pSwapChain));
}

HRESULT MyIDirect3DDevice9::GetSwapChain(UINT iSwapChain,IDirect3DSwapChain9** pSwapChain)
{
    return(ID3DDevice9->GetSwapChain(iSwapChain,pSwapChain));
}

UINT    MyIDirect3DDevice9::GetNumberOfSwapChains(void)
{
    return(ID3DDevice9->GetNumberOfSwapChains());
}

HRESULT MyIDirect3DDevice9::Reset(D3DPRESENT_PARAMETERS* pPresentationParameters)
{
    return(ID3DDevice9->Reset(pPresentationParameters));
}

HRESULT MyIDirect3DDevice9::GetBackBuffer(UINT iSwapChain,UINT iBackBuffer,D3DBACKBUFFER_TYPE Type,IDirect3DSurface9** ppBackBuffer)
{
    return(ID3DDevice9->GetBackBuffer(iSwapChain,iBackBuffer,Type,ppBackBuffer));
}

HRESULT MyIDirect3DDevice9::GetRasterStatus(UINT iSwapChain,D3DRASTER_STATUS* pRasterStatus)
{
    return(ID3DDevice9->GetRasterStatus(iSwapChain,pRasterStatus));
}

HRESULT MyIDirect3DDevice9::SetDialogBoxMode(BOOL bEnableDialogs)
{
    return(ID3DDevice9->SetDialogBoxMode(bEnableDialogs));
}

void    MyIDirect3DDevice9::SetGammaRamp(UINT iSwapChain,DWORD Flags,CONST D3DGAMMARAMP* pRamp)
{
    return(ID3DDevice9->SetGammaRamp(iSwapChain,Flags,pRamp));
}

void    MyIDirect3DDevice9::GetGammaRamp(UINT iSwapChain,D3DGAMMARAMP* pRamp)
{
    return(ID3DDevice9->GetGammaRamp(iSwapChain,pRamp));
}

HRESULT MyIDirect3DDevice9::CreateTexture(UINT Width,UINT Height,UINT Levels,DWORD Usage,D3DFORMAT Format,D3DPOOL Pool,IDirect3DTexture9** ppTexture,HANDLE* pSharedHandle)
{
    return(ID3DDevice9->CreateTexture(Width,Height,Levels,Usage,Format,Pool,ppTexture,pSharedHandle));
}

HRESULT MyIDirect3DDevice9::CreateVolumeTexture(UINT Width,UINT Height,UINT Depth,UINT Levels,DWORD Usage,D3DFORMAT Format,D3DPOOL Pool,IDirect3DVolumeTexture9** ppVolumeTexture,HANDLE* pSharedHandle)
{
    return(ID3DDevice9->CreateVolumeTexture(Width,Height,Depth,Levels,Usage,Format,Pool,ppVolumeTexture,pSharedHandle));
}

HRESULT MyIDirect3DDevice9::CreateCubeTexture(UINT EdgeLength,UINT Levels,DWORD Usage,D3DFORMAT Format,D3DPOOL Pool,IDirect3DCubeTexture9** ppCubeTexture,HANDLE* pSharedHandle)
{
    return(ID3DDevice9->CreateCubeTexture(EdgeLength,Levels,Usage,Format,Pool,ppCubeTexture,pSharedHandle));
}

HRESULT MyIDirect3DDevice9::CreateVertexBuffer(UINT Length,DWORD Usage,DWORD FVF,D3DPOOL Pool,IDirect3DVertexBuffer9** ppVertexBuffer,HANDLE* pSharedHandle)
{
    return(ID3DDevice9->CreateVertexBuffer(Length,Usage,FVF,Pool,ppVertexBuffer,pSharedHandle));
}

HRESULT MyIDirect3DDevice9::CreateIndexBuffer(UINT Length,DWORD Usage,D3DFORMAT Format,D3DPOOL Pool,IDirect3DIndexBuffer9** ppIndexBuffer,HANDLE* pSharedHandle)
{
    return(ID3DDevice9->CreateIndexBuffer(Length,Usage,Format,Pool,ppIndexBuffer,pSharedHandle));
}

HRESULT MyIDirect3DDevice9::CreateRenderTarget(UINT Width,UINT Height,D3DFORMAT Format,D3DMULTISAMPLE_TYPE MultiSample,DWORD MultisampleQuality,BOOL Lockable,IDirect3DSurface9** ppSurface,HANDLE* pSharedHandle)
{
    return(ID3DDevice9->CreateRenderTarget(Width,Height,Format,MultiSample,MultisampleQuality,Lockable,ppSurface,pSharedHandle));
}

HRESULT MyIDirect3DDevice9::CreateDepthStencilSurface(UINT Width,UINT Height,D3DFORMAT Format,D3DMULTISAMPLE_TYPE MultiSample,DWORD MultisampleQuality,BOOL Discard,IDirect3DSurface9** ppSurface,HANDLE* pSharedHandle)
{
    return(ID3DDevice9->CreateDepthStencilSurface(Width,Height,Format,MultiSample,MultisampleQuality,Discard,ppSurface,pSharedHandle));
}

HRESULT MyIDirect3DDevice9::UpdateSurface(IDirect3DSurface9* pSourceSurface,CONST RECT* pSourceRect,IDirect3DSurface9* pDestinationSurface,CONST POINT* pDestPoint)
{
    return(ID3DDevice9->UpdateSurface(pSourceSurface,pSourceRect,pDestinationSurface,pDestPoint));
}

HRESULT MyIDirect3DDevice9::UpdateTexture(IDirect3DBaseTexture9* pSourceTexture,IDirect3DBaseTexture9* pDestinationTexture)
{
    return(ID3DDevice9->UpdateTexture(pSourceTexture,pDestinationTexture));
}

HRESULT MyIDirect3DDevice9::GetRenderTargetData(IDirect3DSurface9* pRenderTarget,IDirect3DSurface9* pDestSurface)
{
    return(ID3DDevice9->GetRenderTargetData(pRenderTarget,pDestSurface));
}

HRESULT MyIDirect3DDevice9::GetFrontBufferData(UINT iSwapChain,IDirect3DSurface9* pDestSurface)
{
    return(ID3DDevice9->GetFrontBufferData(iSwapChain,pDestSurface));
}

HRESULT MyIDirect3DDevice9::StretchRect(IDirect3DSurface9* pSourceSurface,CONST RECT* pSourceRect,IDirect3DSurface9* pDestSurface,CONST RECT* pDestRect,D3DTEXTUREFILTERTYPE Filter)
{
    return(ID3DDevice9->StretchRect(pSourceSurface,pSourceRect,pDestSurface,pDestRect,Filter));
}

HRESULT MyIDirect3DDevice9::ColorFill(IDirect3DSurface9* pSurface,CONST RECT* pRect,D3DCOLOR color)
{
    return(ID3DDevice9->ColorFill(pSurface,pRect,color));
}

HRESULT MyIDirect3DDevice9::CreateOffscreenPlainSurface(UINT Width,UINT Height,D3DFORMAT Format,D3DPOOL Pool,IDirect3DSurface9** ppSurface,HANDLE* pSharedHandle)
{
    return(ID3DDevice9->CreateOffscreenPlainSurface(Width,Height,Format,Pool,ppSurface,pSharedHandle));
}

HRESULT MyIDirect3DDevice9::SetRenderTarget(DWORD RenderTargetIndex,IDirect3DSurface9* pRenderTarget)
{
    return(ID3DDevice9->SetRenderTarget(RenderTargetIndex,pRenderTarget));
}

HRESULT MyIDirect3DDevice9::GetRenderTarget(DWORD RenderTargetIndex,IDirect3DSurface9** ppRenderTarget)
{
    return(ID3DDevice9->GetRenderTarget(RenderTargetIndex,ppRenderTarget));
}

HRESULT MyIDirect3DDevice9::SetDepthStencilSurface(IDirect3DSurface9* pNewZStencil)
{
    return(ID3DDevice9->SetDepthStencilSurface(pNewZStencil));
}

HRESULT MyIDirect3DDevice9::GetDepthStencilSurface(IDirect3DSurface9** ppZStencilSurface)
{
    return(ID3DDevice9->GetDepthStencilSurface(ppZStencilSurface));
}

HRESULT MyIDirect3DDevice9::BeginScene(void)
{
	//MessageBox(NULL, LPCSTR("BEGINSCENE"), LPCSTR("proxy dll"), 0); //TODO
    return(ID3DDevice9->BeginScene());
}

HRESULT MyIDirect3DDevice9::EndScene(void)
{
	//MessageBox(NULL, LPCSTR("ENDSCENE"), LPCSTR("proxy dll"), 0); //TODO
    return(ID3DDevice9->EndScene());
}

HRESULT MyIDirect3DDevice9::Clear(DWORD Count,CONST D3DRECT* pRects,DWORD Flags,D3DCOLOR Color,float Z,DWORD Stencil)
{
    return(ID3DDevice9->Clear(Count,pRects,Flags,Color,Z,Stencil));
}

HRESULT MyIDirect3DDevice9::SetTransform(D3DTRANSFORMSTATETYPE State,CONST D3DMATRIX* pMatrix)
{
    return(ID3DDevice9->SetTransform(State,pMatrix));
}

HRESULT MyIDirect3DDevice9::GetTransform(D3DTRANSFORMSTATETYPE State,D3DMATRIX* pMatrix)
{
    return(ID3DDevice9->GetTransform(State,pMatrix));
}

HRESULT MyIDirect3DDevice9::MultiplyTransform(D3DTRANSFORMSTATETYPE State,CONST D3DMATRIX* pMatrix)
{
    return(ID3DDevice9->MultiplyTransform(State,pMatrix));
}

HRESULT MyIDirect3DDevice9::SetViewport(CONST D3DVIEWPORT9* pViewport)
{
    return(ID3DDevice9->SetViewport(pViewport));
}

HRESULT MyIDirect3DDevice9::GetViewport(D3DVIEWPORT9* pViewport)
{
    return(ID3DDevice9->GetViewport(pViewport));
}

HRESULT MyIDirect3DDevice9::SetMaterial(CONST D3DMATERIAL9* pMaterial)
{
    return(ID3DDevice9->SetMaterial(pMaterial));
}

HRESULT MyIDirect3DDevice9::GetMaterial(D3DMATERIAL9* pMaterial)
{
    return(ID3DDevice9->GetMaterial(pMaterial));
}

HRESULT MyIDirect3DDevice9::SetLight(DWORD Index,CONST D3DLIGHT9* pLight)
{
    return(ID3DDevice9->SetLight(Index,pLight));
}

HRESULT MyIDirect3DDevice9::GetLight(DWORD Index,D3DLIGHT9* pLight)
{
    return(ID3DDevice9->GetLight(Index,pLight));
}

HRESULT MyIDirect3DDevice9::LightEnable(DWORD Index,BOOL Enable)
{
    return(ID3DDevice9->LightEnable(Index,Enable));
}

HRESULT MyIDirect3DDevice9::GetLightEnable(DWORD Index,BOOL* pEnable)
{
    return(ID3DDevice9->GetLightEnable(Index, pEnable));
}

HRESULT MyIDirect3DDevice9::SetClipPlane(DWORD Index,CONST float* pPlane)
{
    return(ID3DDevice9->SetClipPlane(Index, pPlane));
}

HRESULT MyIDirect3DDevice9::GetClipPlane(DWORD Index,float* pPlane)
{
    return(ID3DDevice9->GetClipPlane(Index,pPlane));
}

HRESULT MyIDirect3DDevice9::SetRenderState(D3DRENDERSTATETYPE State,DWORD Value)
{
    return(ID3DDevice9->SetRenderState(State, Value));
}

HRESULT MyIDirect3DDevice9::GetRenderState(D3DRENDERSTATETYPE State,DWORD* pValue)
{
    return(ID3DDevice9->GetRenderState(State, pValue));
}

HRESULT MyIDirect3DDevice9::CreateStateBlock(D3DSTATEBLOCKTYPE Type,IDirect3DStateBlock9** ppSB)
{
    return(ID3DDevice9->CreateStateBlock(Type,ppSB));
}

HRESULT MyIDirect3DDevice9::BeginStateBlock(void)
{
    return(ID3DDevice9->BeginStateBlock());
}

HRESULT MyIDirect3DDevice9::EndStateBlock(IDirect3DStateBlock9** ppSB)
{
    return(ID3DDevice9->EndStateBlock(ppSB));
}

HRESULT MyIDirect3DDevice9::SetClipStatus(CONST D3DCLIPSTATUS9* pClipStatus)
{
    return(ID3DDevice9->SetClipStatus(pClipStatus));
}

HRESULT MyIDirect3DDevice9::GetClipStatus(D3DCLIPSTATUS9* pClipStatus)
{
    return(ID3DDevice9->GetClipStatus( pClipStatus));
}

HRESULT MyIDirect3DDevice9::GetTexture(DWORD Stage,IDirect3DBaseTexture9** ppTexture)
{
    return(ID3DDevice9->GetTexture(Stage,ppTexture));
}

HRESULT MyIDirect3DDevice9::SetTexture(DWORD Stage,IDirect3DBaseTexture9* pTexture)
{
    return(ID3DDevice9->SetTexture(Stage,pTexture));
}

HRESULT MyIDirect3DDevice9::GetTextureStageState(DWORD Stage,D3DTEXTURESTAGESTATETYPE Type,DWORD* pValue)
{
    return(ID3DDevice9->GetTextureStageState(Stage,Type, pValue));
}

HRESULT MyIDirect3DDevice9::SetTextureStageState(DWORD Stage,D3DTEXTURESTAGESTATETYPE Type,DWORD Value)
{
    return(ID3DDevice9->SetTextureStageState(Stage,Type,Value));
}

HRESULT MyIDirect3DDevice9::GetSamplerState(DWORD Sampler,D3DSAMPLERSTATETYPE Type,DWORD* pValue)
{
    return(ID3DDevice9->GetSamplerState(Sampler,Type, pValue));
}

HRESULT MyIDirect3DDevice9::SetSamplerState(DWORD Sampler,D3DSAMPLERSTATETYPE Type,DWORD Value)
{
    return(ID3DDevice9->SetSamplerState(Sampler,Type,Value));
}

HRESULT MyIDirect3DDevice9::ValidateDevice(DWORD* pNumPasses)
{
    return(ID3DDevice9->ValidateDevice( pNumPasses));
}

HRESULT MyIDirect3DDevice9::SetPaletteEntries(UINT PaletteNumber,CONST PALETTEENTRY* pEntries)
{
    return(ID3DDevice9->SetPaletteEntries(PaletteNumber, pEntries));
}

HRESULT MyIDirect3DDevice9::GetPaletteEntries(UINT PaletteNumber,PALETTEENTRY* pEntries)
{
    return(ID3DDevice9->GetPaletteEntries(PaletteNumber, pEntries));
}

HRESULT MyIDirect3DDevice9::SetCurrentTexturePalette(UINT PaletteNumber)
{
    return(ID3DDevice9->SetCurrentTexturePalette(PaletteNumber));
}

HRESULT MyIDirect3DDevice9::GetCurrentTexturePalette(UINT *PaletteNumber)
{
    return(ID3DDevice9->GetCurrentTexturePalette(PaletteNumber));
}

HRESULT MyIDirect3DDevice9::SetScissorRect(CONST RECT* pRect)
{
    return(ID3DDevice9->SetScissorRect( pRect));
}

HRESULT MyIDirect3DDevice9::GetScissorRect( RECT* pRect)
{
    return(ID3DDevice9->GetScissorRect( pRect));
}

HRESULT MyIDirect3DDevice9::SetSoftwareVertexProcessing(BOOL bSoftware)
{
    return(ID3DDevice9->SetSoftwareVertexProcessing(bSoftware));
}

BOOL    MyIDirect3DDevice9::GetSoftwareVertexProcessing(void)
{
    return(ID3DDevice9->GetSoftwareVertexProcessing());
}

HRESULT MyIDirect3DDevice9::SetNPatchMode(float nSegments)
{
    return(ID3DDevice9->SetNPatchMode(nSegments));
}

float   MyIDirect3DDevice9::GetNPatchMode(void)
{
    return(ID3DDevice9->GetNPatchMode());
}

HRESULT MyIDirect3DDevice9::DrawPrimitive(D3DPRIMITIVETYPE PrimitiveType,UINT StartVertex,UINT PrimitiveCount)
{
    return(ID3DDevice9->DrawPrimitive(PrimitiveType,StartVertex,PrimitiveCount));
}

HRESULT MyIDirect3DDevice9::DrawIndexedPrimitive(D3DPRIMITIVETYPE PrimitiveType,INT BaseVertexIndex,UINT MinVertexIndex,UINT NumVertices,UINT startIndex,UINT primCount)
{
    return(ID3DDevice9->DrawIndexedPrimitive(PrimitiveType,BaseVertexIndex,MinVertexIndex,NumVertices,startIndex,primCount));
}

HRESULT MyIDirect3DDevice9::DrawPrimitiveUP(D3DPRIMITIVETYPE PrimitiveType,UINT PrimitiveCount,CONST void* pVertexStreamZeroData,UINT VertexStreamZeroStride)
{
    return(ID3DDevice9->DrawPrimitiveUP(PrimitiveType,PrimitiveCount,pVertexStreamZeroData,VertexStreamZeroStride));
}

HRESULT MyIDirect3DDevice9::DrawIndexedPrimitiveUP(D3DPRIMITIVETYPE PrimitiveType,UINT MinVertexIndex,UINT NumVertices,UINT PrimitiveCount,CONST void* pIndexData,D3DFORMAT IndexDataFormat,CONST void* pVertexStreamZeroData,UINT VertexStreamZeroStride)
{
    return(ID3DDevice9->DrawIndexedPrimitiveUP(PrimitiveType,MinVertexIndex,NumVertices,PrimitiveCount, pIndexData, IndexDataFormat, pVertexStreamZeroData,VertexStreamZeroStride));
}

HRESULT MyIDirect3DDevice9::ProcessVertices(UINT SrcStartIndex,UINT DestIndex,UINT VertexCount,IDirect3DVertexBuffer9* pDestBuffer,IDirect3DVertexDeclaration9* pVertexDecl,DWORD Flags)
{
    return(ID3DDevice9->ProcessVertices( SrcStartIndex, DestIndex, VertexCount, pDestBuffer, pVertexDecl, Flags));
}

HRESULT MyIDirect3DDevice9::CreateVertexDeclaration(CONST D3DVERTEXELEMENT9* pVertexElements,IDirect3DVertexDeclaration9** ppDecl)
{
    return(ID3DDevice9->CreateVertexDeclaration( pVertexElements,ppDecl));
}

HRESULT MyIDirect3DDevice9::SetVertexDeclaration(IDirect3DVertexDeclaration9* pDecl)
{
    return(ID3DDevice9->SetVertexDeclaration(pDecl));
}

HRESULT MyIDirect3DDevice9::GetVertexDeclaration(IDirect3DVertexDeclaration9** ppDecl)
{
    return(ID3DDevice9->GetVertexDeclaration(ppDecl));
}

HRESULT MyIDirect3DDevice9::SetFVF(DWORD FVF)
{
    return(ID3DDevice9->SetFVF(FVF));
}

HRESULT MyIDirect3DDevice9::GetFVF(DWORD* pFVF)
{
    return(ID3DDevice9->GetFVF(pFVF));
}

HRESULT MyIDirect3DDevice9::CreateVertexShader(CONST DWORD* pFunction,IDirect3DVertexShader9** ppShader)
{
    return(ID3DDevice9->CreateVertexShader(pFunction,ppShader));
}

HRESULT MyIDirect3DDevice9::SetVertexShader(IDirect3DVertexShader9* pShader)
{
    return(ID3DDevice9->SetVertexShader(pShader));
}

HRESULT MyIDirect3DDevice9::GetVertexShader(IDirect3DVertexShader9** ppShader)
{
    return(ID3DDevice9->GetVertexShader(ppShader));
}

HRESULT MyIDirect3DDevice9::SetVertexShaderConstantF(UINT StartRegister,CONST float* pConstantData,UINT Vector4fCount)
{
    return(ID3DDevice9->SetVertexShaderConstantF(StartRegister,pConstantData, Vector4fCount));
}

HRESULT MyIDirect3DDevice9::GetVertexShaderConstantF(UINT StartRegister,float* pConstantData,UINT Vector4fCount)
{
    return(ID3DDevice9->GetVertexShaderConstantF(StartRegister,pConstantData,Vector4fCount));
}

HRESULT MyIDirect3DDevice9::SetVertexShaderConstantI(UINT StartRegister,CONST int* pConstantData,UINT Vector4iCount)
{
    return(ID3DDevice9->SetVertexShaderConstantI(StartRegister,pConstantData,Vector4iCount));
}

HRESULT MyIDirect3DDevice9::GetVertexShaderConstantI(UINT StartRegister,int* pConstantData,UINT Vector4iCount)
{
    return(ID3DDevice9->GetVertexShaderConstantI(StartRegister,pConstantData,Vector4iCount));
}

HRESULT MyIDirect3DDevice9::SetVertexShaderConstantB(UINT StartRegister,CONST BOOL* pConstantData,UINT  BoolCount)
{
    return(ID3DDevice9->SetVertexShaderConstantB(StartRegister,pConstantData,BoolCount));
}

HRESULT MyIDirect3DDevice9::GetVertexShaderConstantB(UINT StartRegister,BOOL* pConstantData,UINT BoolCount)
{
    return(ID3DDevice9->GetVertexShaderConstantB(StartRegister,pConstantData,BoolCount));
}

HRESULT MyIDirect3DDevice9::SetStreamSource(UINT StreamNumber,IDirect3DVertexBuffer9* pStreamData,UINT OffsetInBytes,UINT Stride)
{
    return(ID3DDevice9->SetStreamSource(StreamNumber,pStreamData,OffsetInBytes,Stride));
}

HRESULT MyIDirect3DDevice9::GetStreamSource(UINT StreamNumber,IDirect3DVertexBuffer9** ppStreamData,UINT* OffsetInBytes,UINT* pStride)
{
    return(ID3DDevice9->GetStreamSource(StreamNumber,ppStreamData,OffsetInBytes,pStride));
}

HRESULT MyIDirect3DDevice9::SetStreamSourceFreq(UINT StreamNumber,UINT Divider)
{
    return(ID3DDevice9->SetStreamSourceFreq(StreamNumber,Divider));
}

HRESULT MyIDirect3DDevice9::GetStreamSourceFreq(UINT StreamNumber,UINT* Divider)
{
    return(ID3DDevice9->GetStreamSourceFreq(StreamNumber,Divider));
}

HRESULT MyIDirect3DDevice9::SetIndices(IDirect3DIndexBuffer9* pIndexData)
{
    return(ID3DDevice9->SetIndices(pIndexData));
}

HRESULT MyIDirect3DDevice9::GetIndices(IDirect3DIndexBuffer9** ppIndexData)
{
    return(ID3DDevice9->GetIndices(ppIndexData));
}

HRESULT MyIDirect3DDevice9::CreatePixelShader(CONST DWORD* pFunction,IDirect3DPixelShader9** ppShader)
{
    return(ID3DDevice9->CreatePixelShader(pFunction,ppShader));
}

HRESULT MyIDirect3DDevice9::SetPixelShader(IDirect3DPixelShader9* pShader)
{
    return(ID3DDevice9->SetPixelShader(pShader));
}

HRESULT MyIDirect3DDevice9::GetPixelShader(IDirect3DPixelShader9** ppShader)
{
    return(ID3DDevice9->GetPixelShader(ppShader));
}

HRESULT MyIDirect3DDevice9::SetPixelShaderConstantF(UINT StartRegister,CONST float* pConstantData,UINT Vector4fCount)
{
    return(ID3DDevice9->SetPixelShaderConstantF(StartRegister,pConstantData,Vector4fCount));
}

HRESULT MyIDirect3DDevice9::GetPixelShaderConstantF(UINT StartRegister,float* pConstantData,UINT Vector4fCount)
{
    return(ID3DDevice9->GetPixelShaderConstantF(StartRegister,pConstantData,Vector4fCount));
}

HRESULT MyIDirect3DDevice9::SetPixelShaderConstantI(UINT StartRegister,CONST int* pConstantData,UINT Vector4iCount)
{
    return(ID3DDevice9->SetPixelShaderConstantI(StartRegister,pConstantData,Vector4iCount));
}

HRESULT MyIDirect3DDevice9::GetPixelShaderConstantI(UINT StartRegister,int* pConstantData,UINT Vector4iCount)
{
    return(ID3DDevice9->GetPixelShaderConstantI(StartRegister,pConstantData,Vector4iCount));
}

HRESULT MyIDirect3DDevice9::SetPixelShaderConstantB(UINT StartRegister,CONST BOOL* pConstantData,UINT  BoolCount)
{
    return(ID3DDevice9->SetPixelShaderConstantB(StartRegister,pConstantData,BoolCount));
}

HRESULT MyIDirect3DDevice9::GetPixelShaderConstantB(UINT StartRegister,BOOL* pConstantData,UINT BoolCount)
{
    return(ID3DDevice9->GetPixelShaderConstantB(StartRegister,pConstantData,BoolCount));
}

HRESULT MyIDirect3DDevice9::DrawRectPatch(UINT Handle,CONST float* pNumSegs,CONST D3DRECTPATCH_INFO* pRectPatchInfo)
{
    return(ID3DDevice9->DrawRectPatch(Handle,pNumSegs, pRectPatchInfo));
}

HRESULT MyIDirect3DDevice9::DrawTriPatch(UINT Handle,CONST float* pNumSegs,CONST D3DTRIPATCH_INFO* pTriPatchInfo)
{
    return(ID3DDevice9->DrawTriPatch(Handle, pNumSegs, pTriPatchInfo));
}

HRESULT MyIDirect3DDevice9::DeletePatch(UINT Handle)
{
    return(ID3DDevice9->DeletePatch(Handle));
}

HRESULT MyIDirect3DDevice9::CreateQuery(D3DQUERYTYPE Type,IDirect3DQuery9** ppQuery)
{
    return(ID3DDevice9->CreateQuery(Type,ppQuery));
}