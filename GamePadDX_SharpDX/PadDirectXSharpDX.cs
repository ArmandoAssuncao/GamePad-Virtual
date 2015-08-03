using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;
using System.Runtime.InteropServices;
using System.Runtime.ExceptionServices;
using SharpDX;
using SharpDX.Direct3D9;

namespace GamePadDX_SharpDX {
	public class PadDirectXSharpDX {

		public unsafe static void AddMyDeviceSharpDX(ref int* value) {
			IntPtr devicePtr = new IntPtr(*value);

			//MessageBox.Show("Sharpdx device: " + devicePtr);
			Device _D3D9Device = SharpDX.Direct3D9.Device.FromPointer<SharpDX.Direct3D9.Device>(devicePtr);

			_D3D9Device.GetSetShowCursor(true);

			Rectangle[] rectangle = new Rectangle[1];
			rectangle[0] = new Rectangle(1, 104, 50, 50);
			_D3D9Device.Clear(ClearFlags.Target, Color.Aqua, 0, 0, rectangle);
		}
	}
}
