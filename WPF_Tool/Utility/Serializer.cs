using System;
using System.Collections.Generic;
using System.Linq;
using System.Runtime.InteropServices;
using System.Text;
using System.Threading.Tasks;

namespace WPF_Tool.Utility
{
    class Serializer
    {

        //https://softworld.tistory.com/67
        public static byte[] RawSerialize<T>(object data)
       {
            int size = Marshal.SizeOf(data);

            IntPtr buffer = Marshal.AllocHGlobal(size);
            Marshal.StructureToPtr(data, buffer, false);
            byte[] rawData = new byte[size];
            Marshal.Copy(buffer, rawData, 0, size);
            Marshal.FreeHGlobal(buffer);
            return rawData;
        }

        public static object RawDeSerialize(byte[] rawData, Type dataType)
        {
            int rawSize = Marshal.SizeOf(dataType);

            // Size over
            if (rawSize > rawData.Length)
                return null;

            IntPtr buffer = Marshal.AllocHGlobal(rawSize);
            Marshal.Copy(rawData, 0, buffer, rawSize);
            object retObj = Marshal.PtrToStructure(buffer, dataType);
            Marshal.FreeHGlobal(buffer);
            return retObj;
        }
    }
}
