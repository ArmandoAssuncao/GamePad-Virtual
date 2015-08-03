// gateCLR.h
#pragma once

using namespace System;

namespace gateCLR {
	public class Functions{

	public:
		void Caller(int* value) {
			GamePadDX::PadDirectX::AddMyDevice(value);
			return;
		}

		void CallerSharpDX(int* value) {
			GamePadDX_SharpDX::PadDirectXSharpDX::AddMyDeviceSharpDX(value);
			return;
		}
	};	
}

__declspec(dllexport) void AssignMyD3DDeviceSlimDX(int* value) {
	gateCLR::Functions functions;
	functions.Caller(value);
}

__declspec(dllexport) void AssignMyD3DDeviceSharpDX(int* value) {
	gateCLR::Functions functions;
	functions.CallerSharpDX(value);
}