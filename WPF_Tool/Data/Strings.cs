using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace WPF_Tool.Data
{
    public class Strings
    {
        public static string[] Tags = new string[] 
        {
            "Default",
            "UI",
            "Player",
            "Enemy"
        };

    }

    public class HierarchyTag
    {
        public static string GameObject = "GameObject";
        public static string NavMesh = "NavMesh";
    }
    public class HierarchyContent
    {
        public static string GameObject = "GameObject";
        public static string NavMesh = "NavMesh";
    }
    public class Paths
    {
        public static string ResourcePath;
        public static string MeshPath;
        public static string TexturePath;
        public static string DataPath;
        public static string GameObjectDataPath;
        public static string MeshDataPath;
        public static string HierarchyDataPath;

    }

}
