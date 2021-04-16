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
    public struct LightData
    {
        [MarshalAs(UnmanagedType.I4)]
        public int lightType;
        [MarshalAs(UnmanagedType.Struct)]
        public Vector3 direction;
        [MarshalAs(UnmanagedType.Struct)]
        public Vector3 position;
        [MarshalAs(UnmanagedType.Struct)]
        public DxColor ambient;
        [MarshalAs(UnmanagedType.R4)]
        public float ambientIntensity;
        [MarshalAs(UnmanagedType.Struct)]
        public DxColor diffuse;
        [MarshalAs(UnmanagedType.R4)]
        public float diffuseIntensity;
        [MarshalAs(UnmanagedType.Struct)]
        public DxColor specular;
        [MarshalAs(UnmanagedType.R4)]
        public float specularIntensity;
        [MarshalAs(UnmanagedType.R4)]
        public float specularPower;
        [MarshalAs(UnmanagedType.R4)]
        public float range;
        [MarshalAs(UnmanagedType.R4)]
        public float cone;
        [MarshalAs(UnmanagedType.R4)]
        public float constant;
        [MarshalAs(UnmanagedType.R4)]
        public float linear;
        [MarshalAs(UnmanagedType.R4)]
        public float quadratic;
    }
}
