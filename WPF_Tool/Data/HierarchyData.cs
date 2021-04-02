using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using WPF_Tool.Utility;

namespace WPF_Tool.Data
{
    public class HierarchyData
    {
        public GameObjectType type;
        private int index;
        public int Index
        {
            get
            {
                return index;
            }
            set
            {
                index = value;
                gameObjectData.index = value;
                meshData.index = value;
                mapData.index = value;
            }
        }
        public int tagIndex;
        public int layerIndex;
        public int staticIndex;

        /* Serialized Data */
        public GameObjectData gameObjectData;
        public MeshData meshData;
        public MapData mapData;
        public NavMeshData navMeshData;
        public TerrainData terrainData;
        /* For Editor */
        // 에디터에서만 사용되는 데이터
        public List<CellData> cells;
    }
}
