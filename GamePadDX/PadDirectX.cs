using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;
using System.IO;
using System.Runtime.InteropServices;
using SlimDX;
using SlimDX.Direct3D9;
using System.Drawing;
using System.Runtime.ExceptionServices;

namespace GamePadDX{
    public class PadDirectX{

		[HandleProcessCorruptedStateExceptions] 
		public unsafe static void AddMyDevice(ref int* value) {
			IntPtr devicePtr;
			Device _D3D9Device = null;
			
			try {
				devicePtr = new IntPtr(*value);

				//MessageBox.Show("Add the gamePad");
				//MessageBox.Show("Pointer device: "+devicePtr);

				_D3D9Device = SlimDX.Direct3D9.Device.FromPointer(devicePtr);
				Rectangle[] rectangle = new Rectangle[1];
				rectangle[0] = new Rectangle(1, 50, 100, 100);
				_D3D9Device.Clear(ClearFlags.Target, Color.Blue.ToArgb(), 100, 10, rectangle);
			}
			catch (ArgumentException ex) {
				MessageBox.Show("class PadDirectX: " + ex.StackTrace);
			}

			/*if (_D3D9Device == null) {
				MessageBox.Show("D3D9Device NULL");
			}*/
		}

    } //PadDirectX
}
