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
        public HierarchyData()
        {

        }
        public HierarchyData(HierarchyData data)
        {
            type = data.type;
            Index = data.index;
            tagIndex = data.tagIndex;
            layerIndex = data.layerIndex;
            staticIndex = data.staticIndex;
            gameObjectData = data.gameObjectData;
            meshData = data.meshData;
            mapData = data.mapData;
            navMeshData = data.navMeshData;
            terrainData = data.terrainData;
            lightData = data.lightData;
            effectData = data.effectData;
            uiData = data.uiData;
            if (data.cells != null)
            {
                for (int i = 0; i < data.cells.Count; i++)
                {
                    cells.Add(data.cells[i]);
                }
            }
        }
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
        /* Fix가 true일 때 다른 값 변경 불가능하다. */
        public bool bFix; 

        /* Serialized Data */
        public GameObjectData gameObjectData;
        public MeshData meshData;
        public MapData mapData;
        public NavMeshData navMeshData;
        public TerrainData terrainData;
        public LightData lightData;
        public EffectData effectData;
        public UIData uiData;

        /* For Editor */
        // 에디터에서만 사용되는 데이터
        public List<CellData> cells;
    }
}
