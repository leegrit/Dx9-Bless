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
    public struct MapData
    {
        public MapData(int index)
        {
            this.index = index;
            group = (int)EMapGroup.Group1;
        }
        [MarshalAs(UnmanagedType.I4)]
        public int index;
        [MarshalAs(UnmanagedType.I4)]
        public int group;
    }
}
