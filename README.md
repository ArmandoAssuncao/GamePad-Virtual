# GamePad-Virtual
Select language:[ [en-us](https://github.com/ArmandoAssuncao/GamePad-Virtual/blob/master/README.md) | [pt-br](https://github.com/ArmandoAssuncao/GamePad-Virtual/blob/master/README_pt-br.md)]

GamePad-Virtual is one software open-source developed for operation system Windows that allows better experiences in games that are played in tablets.
Developed in C++, C#, DirectX and SharpDX.

### How it Works
For show the gamepad in the screen, the program creates DLLs (d3d9.dll, dxgi.dll, gamepadX.dll) inside the folder of the game selected. When the program Gamepad starts the game is made a call the DLL d3d9.dll(if the game uses DirectX9) or dxgi.dll(if the game uses DirectX10/11), then this DLL does a another call for the DLL gamepadX.dll. The DLL gamepadX.dll finally adds the gamepad virtual in the screen of the device.

### technologies
- C++
- C#
- DirectX
- SharpDX

### Supports:
- DirectX9
- DirectX10 (comming soon)
- DirectX11 (comming soon)

### Screenshots:
