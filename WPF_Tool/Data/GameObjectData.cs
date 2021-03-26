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
    public struct GameObjectData
    {
        public GameObjectData(int index, string defaultName)
        {
            this.index = index;
            name = defaultName; // default
            tag = "Default"; // default
            transform = new Transform();
            transform.position = new Math.Vector3();
            transform.position.x = 0;
            transform.position.y = 0;
            transform.position.z = 0;
            transform.rotation = new Math.Vector3();
            transform.rotation.x = 0;
            transform.rotation.y = 0;
            transform.rotation.z = 0;
            transform.scale = new Math.Vector3();
            transform.scale.x = 1;
            transform.scale.y = 1;
            transform.scale.z = 1;
            layer = 0;
            staticType = 0;
        }
        [MarshalAs(UnmanagedType.I4)]
        public int index;
        [MarshalAs(UnmanagedType.ByValTStr, SizeConst = 256)]
        public string name;
        [MarshalAs(UnmanagedType.ByValTStr, SizeConst = 256)]
        public string tag;
        [MarshalAs(UnmanagedType.I4)]
        public int layer;
        [MarshalAs(UnmanagedType.I4)]
        public int staticType;
        [MarshalAs(UnmanagedType.Struct)]
        public Transform transform;
        
    }
}
