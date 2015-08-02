// gateCLR.h
#pragma once

using namespace System;

namespace gateCLR {
	public class Functions{

	public:
		void ShowPtr(int* value) {
			GamePadDX::PadDirectX::AddMyDevice(value);
			return;
		}
	};	
}

__declspec(dllexport) void AssignMyDirect3DPtr(int* value) {
	gateCLR::Functions functions;
	functions.ShowPtr(value);
}