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
    public struct Vector2
    {
        [MarshalAs(UnmanagedType.R4)]
        public float x;
        [MarshalAs(UnmanagedType.R4)]
        public float y;

        public static Vector2 operator -(Vector2 a, Vector2 b)
        {
            Vector2 result;
            result.x = a.x - b.x;
            result.y = a.y - b.y;
            return result;
        }
        public static Vector2 operator +(Vector2 a, Vector2 b)
        {
            Vector2 result;
            result.x = a.x + b.x;
            result.y = a.y + b.y;
            return result;
        }
        public static Vector2 operator *(Vector2 a, Vector2 b)
        {
            Vector2 result;
            result.x = a.x * b.x;
            result.y = a.y * b.y;
            return result;
        }
        public static Vector2 operator /(Vector2 a, Vector2 b)
        {
            Vector2 result;
            result.x = a.x / b.x;
            result.y = a.y / b.y;
            return result;
        }
        public static Vector2 Normalize(Vector2 vec)
        {
            float distance = (float)System.Math.Sqrt(vec.x * vec.x + vec.y * vec.y);
            Vector2 result;
            result.x = vec.x / distance;
            result.y = vec.y / distance;
            return result;
        }
    }
    [Serializable]
    [StructLayout(LayoutKind.Sequential, Pack = 1)]
    public struct Vector3
    {
        [MarshalAs(UnmanagedType.R4)]
        public float x;
        [MarshalAs(UnmanagedType.R4)]
        public float y;
        [MarshalAs(UnmanagedType.R4)]
        public float z;

        public static Vector3 operator -(Vector3 a, Vector3 b)
        {
            Vector3 result;
            result.x = a.x - b.x;
            result.y = a.y - b.y;
            result.z = a.z - b.z;
            return result;
        }
        public static Vector3 operator +(Vector3 a, Vector3 b)
        {
            Vector3 result;
            result.x = a.x + b.x;
            result.y = a.y + b.y;
            result.z = a.z + b.z;
            return result;
        }
        public static Vector3 operator *(Vector3 a, Vector3 b)
        {
            Vector3 result;
            result.x = a.x * b.x;
            result.y = a.y * b.y;
            result.z = a.z * b.z;
            return result;
        }
        public static Vector3 operator /(Vector3 a, Vector3 b)
        {
            Vector3 result;
            result.x = a.x / b.x;
            result.y = a.y / b.y;
            result.z = a.z / b.z;
            return result;
        }
        public static Vector3 Normalize(Vector3 vec)
        {
            float distance = (float)System.Math.Sqrt(vec.x * vec.x + vec.y * vec.y + vec.z * vec.z);
            Vector3 result;
            result.x = vec.x / distance;
            result.y = vec.y / distance;
            result.z = vec.z / distance;
            return result;
        }
    }
}
