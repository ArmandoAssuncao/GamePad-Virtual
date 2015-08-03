using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;
using SharpDX;

namespace GamePadDX_SharpDX {

	public class PadDirectXSharpDX {

		public unsafe static void AddMyDeviceSharpDX(ref int* value) {

			IntPtr devicePtr = new IntPtr(*value);

			MessageBox.Show("" + devicePtr);
			new SharpDX.Direct3D9.Device(devicePtr);
		}
	}
}
