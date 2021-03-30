using System;
using System.Collections.Generic;
using System.Linq;
using System.Runtime.InteropServices;
using System.Text;
using System.Threading.Tasks;

namespace WPF_Tool.Data
{
    [Serializable]
    [StructLayout(LayoutKind.Sequential, Pack =1)]
    public struct AnimNameData
    {
        [MarshalAs(UnmanagedType.ByValTStr, SizeConst = 256)]
        public string name;
    }
}
