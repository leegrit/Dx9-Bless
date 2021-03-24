using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Runtime.InteropServices;
using WPF_Tool.Math;

namespace WPF_Tool.Data
{
    [Serializable]
    [StructLayout(LayoutKind.Sequential, Pack = 1)]
    struct Transform
    {
        [MarshalAs(UnmanagedType.Struct)]
        public Vector3 position;
        [MarshalAs(UnmanagedType.Struct)]
        public Vector3 rotation;
        [MarshalAs(UnmanagedType.Struct)]
        public Vector3 scale;
      
    }
}
