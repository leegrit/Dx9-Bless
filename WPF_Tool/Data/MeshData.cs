using System;
using System.Collections.Generic;
using System.Linq;
using System.Runtime.InteropServices;
using System.Text;
using System.Threading.Tasks;

namespace WPF_Tool.Data
{
    [Serializable]
    [StructLayout(LayoutKind.Sequential, Pack = 1)]
    struct MeshData
    {
        public MeshData(int index)
        {
            this.index = index;
            meshFilePath = "";
            diffuseTexturePath = "";
        }
        [MarshalAs(UnmanagedType.I4)]
        public int index;
        [MarshalAs(UnmanagedType.ByValTStr, SizeConst = 256)]
        public string meshFilePath;
        [MarshalAs(UnmanagedType.ByValTStr, SizeConst = 256)]
        public string diffuseTexturePath;
    }
}
