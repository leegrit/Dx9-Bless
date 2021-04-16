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
    public struct DxColor
    {
        [MarshalAs(UnmanagedType.R4)]
        public float r;
        [MarshalAs(UnmanagedType.R4)]
        public float g;
        [MarshalAs(UnmanagedType.R4)]
        public float b;
        [MarshalAs(UnmanagedType.R4)]
        public float a;
    }
}
