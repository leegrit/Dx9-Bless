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
        public TerrainData(int index)
        {
            /* Default */
            vertexCountX = 10;
            vertexCountZ = 10;
            textureCountX = 20;
            textureCountZ = 20;
            vertexInterval = 1;
            diffuseFilePath = "";
            normalFilePath = "";
        }
        [MarshalAs(UnmanagedType.I4)]
        public int vertexCountX;
        [MarshalAs(UnmanagedType.I4)]
        public int vertexCountZ;
        [MarshalAs(UnmanagedType.R4)]
        public float textureCountX;
        [MarshalAs(UnmanagedType.R4)]
        public float textureCountZ;
        [MarshalAs(UnmanagedType.R4)]
        public float vertexInterval;
        [MarshalAs(UnmanagedType.ByValTStr, SizeConst = 256)]
        public string diffuseFilePath;
        [MarshalAs(UnmanagedType.ByValTStr, SizeConst = 256)]
        public string normalFilePath;
    }
}
