using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using SlimDX;
using System.Windows.Forms;
using SlimDX.Direct3D9;
using System.Runtime.InteropServices;

namespace DebuggerD3D9 {

	class Program {

		[STAThread]
		static unsafe void Main(string[] args) {

			Direct3D direct3D = new Direct3D();
			/*PresentParameters presentP = new PresentParameters();
			presentP.Windowed = true;
			presentP.SwapEffect = SwapEffect.Discard;
			Form form = new Form();
			Device device2 = new Device(direct3D, 0, DeviceType.Hardware, form.Handle, CreateFlags.SoftwareVertexProcessing, presentP);*/

			Console.WriteLine("--------------------------");
			//Device device = SlimDX.Direct3D9.Device.FromPointer(intPtr2);
			MessageBox.Show("D3D9Device ok");

		}
	}
}