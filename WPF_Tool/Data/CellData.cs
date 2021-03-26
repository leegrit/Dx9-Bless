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
    public struct CellData
    {
        [MarshalAs(UnmanagedType.I4)]
        public int cellIndex;
        [MarshalAs(UnmanagedType.Struct)]
        public Vector3 position;
        [MarshalAs(UnmanagedType.I4)]
        public int option;
        [MarshalAs(UnmanagedType.I4)]
        public int group;
    }
}
