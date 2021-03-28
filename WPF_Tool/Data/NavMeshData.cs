using System;
using System.Collections.Generic;
using System.Linq;
using System.Runtime.InteropServices;
using System.Text;
using System.Threading.Tasks;
using WPF_Tool.Math;

namespace WPF_Tool.Data
{
    [Serializable]
    [StructLayout(LayoutKind.Sequential, Pack = 1)]
    public struct NavMeshData
    {
        public NavMeshData(int index)
        {
            this.index = index;
            this.cellCount = 0;
        }
        [MarshalAs(UnmanagedType.I4)]
        public int index;
        [MarshalAs(UnmanagedType.I4)]
        public int cellCount;
    }
}
