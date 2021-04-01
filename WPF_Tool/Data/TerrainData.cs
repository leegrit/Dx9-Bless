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
    public struct TerrainData
    {
        [MarshalAs(UnmanagedType.U4)]
        public uint vertexCountX;
        [MarshalAs(UnmanagedType.U4)]
        public uint vertexCountZ;
        [MarshalAs(UnmanagedType.R4)]
        public float vertexInterval;
        [MarshalAs(UnmanagedType.ByValTStr, SizeConst = 256)]
        public string diffuseFilePath;
        [MarshalAs(UnmanagedType.ByValTStr, SizeConst = 256)]
        public string normalFilePath;
    }
}
