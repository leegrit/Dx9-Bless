using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Runtime.InteropServices;

namespace WPF_Tool.Math
{

    [Serializable]
    [StructLayout(LayoutKind.Sequential, Pack = 1)]
    class Vector2
    {
        [MarshalAs(UnmanagedType.R4)]
        public float x;
        [MarshalAs(UnmanagedType.R4)]
        public float y;
    }
    [Serializable]
    [StructLayout(LayoutKind.Sequential, Pack = 1)]
    class Vector3
    {
        [MarshalAs(UnmanagedType.R4)]
        public float x;
        [MarshalAs(UnmanagedType.R4)]
        public float y;
        [MarshalAs(UnmanagedType.R4)]
        public float z;
    }
}
