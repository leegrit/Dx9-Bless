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
        public static string MapObject = "MapObject";
        public static string NavMesh = "NavMesh";
        public static string Terrain = "Terrain";
    }
    public class HierarchyContent
    {
        public static string GameObject = "GameObject";
        public static string MapObject = "MapObject";
        public static string NavMesh = "NavMesh";
        public static string Terrain = "Terrain";
    }
    public class Paths
    {
        public static string ResourcePath;
        public static string MeshPath;
        public static string TexturePath;
        public static string DataPath;
        public static string HierarchyDataPath;
        public static string SystemPath;
        public static string MapDataPath;
        public static string BackupPath;
        public static string AssetPath;
        public static string NavMeshData;
        public static string SceneDataPath;

    }

}
