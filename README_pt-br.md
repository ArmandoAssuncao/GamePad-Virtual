# GamePad-Virtual
GamePad-Virtual é um software de código aberto desenvolvido o sistema operacional Windows para melhora as experiências em jogos rodando em tablets.
Desenvolvido em C++, C#, DirectX and SharpDX.

### Como Funciona
Para mostrar o gamepad na tela, o programa cria DLLs (d3d9.dll, dxgi.dll, gamepadX.dll) dentro da pasta do jogo selecionado. Quando o programa Gamepad inicia o jogo é feito uma chamada a DLL d3d9.dll(se o jogo usa DirectX9) ou dxgi.dll(se o jogo usa directX10/11), então esta DLL faz uma outra chamada para a DLL gamepadX.dll. A DLL gamepadX.dll por fim adiciona o gamepad virtual na tela do dispositivo.

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
