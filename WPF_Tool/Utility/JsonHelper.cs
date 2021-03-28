using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using Newtonsoft.Json.Linq;
using WPF_Tool.Data;
using System.IO;
using Microsoft.Win32;

namespace WPF_Tool.Utility
{
    public class JsonHelper
    {
        public static bool Write(HierarchyData data, ref string outFileName)
        {
            string fileName;
            fileName = data.gameObjectData.name;

            var dataJson = new JObject();
            dataJson.Add("Type", (int)data.type);
            dataJson.Add("Index", data.Index);
            dataJson.Add("TagIndex", data.tagIndex);
            dataJson.Add("LayerIndex", data.layerIndex);
            dataJson.Add("StaticIndex", data.staticIndex);

            var gameObjectJson = ConvertToJson(data.gameObjectData);
            dataJson.Add("GameObjectData", gameObjectJson);

            var meshJson = ConvertToJson(data.meshData);
            dataJson.Add("MeshData", meshJson);

            var mapJson = ConvertToJson(data.mapData);
            dataJson.Add("MapData", mapJson);

            // 여기서 같은 파일 이름이 있을 경우
            // 이름 뒤에 번호 0 ~ 붙여서 fileName 최종 결정

            if (System.IO.Directory.Exists(Paths.HierarchyDataPath))
            {
                System.IO.DirectoryInfo info = new System.IO.DirectoryInfo(Paths.HierarchyDataPath);
                int count = 0;
                foreach (var item in info.GetFiles())
                {
                    if (item.Name == fileName + ".json" || item.Name == fileName + count + ".json")
                    {
                        count++;
                        // 같은게 있으면 count를 늘려준다.
                        // 중복이 여러 개 있을 수도 있기 때문.
                    }
                }
                if(count !=0)
                    fileName = fileName + count;
            }

            using (StreamWriter sw = new StreamWriter(Paths.HierarchyDataPath + fileName + ".json", false, Encoding.UTF8))
            {
                sw.Write(dataJson.ToString());
            }
            outFileName = fileName + ".json";
            return true;
        }
        public static bool Write(ChunkMapData data, ref string outFileName)
        {
            string fileName;
            fileName = "ChunkMap_" + data.group.ToString();


            var dataJson = new JObject();
            dataJson.Add("Group", data.group);
            dataJson.Add("MapCount", data.mapCount);

            // 맵 개수만큼 hierarchyData를 json에 써준다.
            for (int i = 0; i < data.mapCount; i++)
            {

                var hierarchyJson = new JObject();
                hierarchyJson.Add("Type", (int)data.maps[i].type);
                hierarchyJson.Add("Index", data.maps[i].Index);
                hierarchyJson.Add("TagIndex", data.maps[i].tagIndex);
                hierarchyJson.Add("LayerIndex", data.maps[i].layerIndex);
                hierarchyJson.Add("StaticIndex", data.maps[i].staticIndex);

                var gameObjectJson = ConvertToJson(data.maps[i].gameObjectData);
                hierarchyJson.Add("GameObjectData", gameObjectJson);

                var meshJson = ConvertToJson(data.maps[i].meshData);
                hierarchyJson.Add("MeshData", meshJson);

                var mapJson = ConvertToJson(data.maps[i].mapData);
                hierarchyJson.Add("MapData", mapJson);

                dataJson.Add("Hierarchy_" + i.ToString(), hierarchyJson);
            }

            // map data는 만약 중복일 경우 덮어쓰는데
            // 실수를 방지하기 위해 backup폴더에 저장해두고 덮어쓴다.
            if (System.IO.Directory.Exists(Paths.MapDataPath))
            {
                string backupFileName = fileName;
                System.IO.DirectoryInfo info = new System.IO.DirectoryInfo(Paths.MapDataPath);
               
                int count = 0;
                foreach (var item in info.GetFiles())
                {
                    if (item.Name == backupFileName + ".json" || item.Name == backupFileName + count + ".json")
                    {
                        count++;
                    }
                }
                if (count != 0)
                {
                    backupFileName = backupFileName + count;



                    using (StreamWriter sw = new StreamWriter(Paths.BackupPath + backupFileName + ".json", false, Encoding.UTF8))
                    {
                        sw.Write(dataJson.ToString());
                    }
                }
            }


            using (StreamWriter sw = new StreamWriter(Paths.MapDataPath + fileName + ".json", false, Encoding.UTF8))
            {
                sw.Write(dataJson.ToString());
            }
            outFileName = fileName + ".json";
            return true;
        }
        public static bool Write(ChunkCellData data, ref string outFileName)
        {
            string fileName;
            fileName = data.navMeshObject.gameObjectData.name;

            var dataJson = new JObject();
            dataJson.Add("Type", (int)data.navMeshObject.type);
            dataJson.Add("Index", data.navMeshObject.Index);
            dataJson.Add("TagIndex", data.navMeshObject.tagIndex);
            dataJson.Add("LayerIndex", data.navMeshObject.layerIndex);
            dataJson.Add("StaticIndex", data.navMeshObject.staticIndex);

            var gameObjectJson = ConvertToJson(data.navMeshObject.gameObjectData);
            dataJson.Add("GameObjectData", gameObjectJson);

            var meshJson = ConvertToJson(data.navMeshObject.meshData);
            dataJson.Add("MeshData", meshJson);

            var mapJson = ConvertToJson(data.navMeshObject.mapData);
            dataJson.Add("MapData", mapJson);

            var navMeshJson = ConvertToJson(data.navMeshObject.navMeshData);
            dataJson.Add("NavMeshData", navMeshJson);


            for (int i = 0; i < data.navMeshObject.navMeshData.cellCount; i++)
            {

                var cellJson = new JObject();
                cellJson.Add("CellIndex", (int)data.cells[i].cellIndex);
                cellJson.Add("PositionX", (int)data.cells[i].position.x);
                cellJson.Add("PositionY", (int)data.cells[i].position.y);
                cellJson.Add("PositionZ", (int)data.cells[i].position.z);
                cellJson.Add("Option", (int)data.cells[i].option);
                cellJson.Add("Group", (int)data.cells[i].group);
                dataJson.Add("Cell_" + i, cellJson);
            }

            // map data는 만약 중복일 경우 덮어쓰는데
            // 실수를 방지하기 위해 backup폴더에 저장해두고 덮어쓴다.
            if (System.IO.Directory.Exists(Paths.NavMeshData))
            {
                string backupFileName = fileName;
                System.IO.DirectoryInfo info = new System.IO.DirectoryInfo(Paths.NavMeshData);

                int count = 0;
                foreach (var item in info.GetFiles())
                {
                    if (item.Name == backupFileName + ".json" || item.Name == backupFileName + count + ".json")
                    {
                        count++;
                    }
                }
                if (count != 0)
                {
                    backupFileName = backupFileName + count;



                    using (StreamWriter sw = new StreamWriter(Paths.BackupPath + backupFileName + ".json", false, Encoding.UTF8))
                    {
                        sw.Write(dataJson.ToString());
                    }
                }
            }


            using (StreamWriter sw = new StreamWriter(Paths.NavMeshData + fileName + ".json", false, Encoding.UTF8))
            {
                sw.Write(dataJson.ToString());
            }
            outFileName = fileName + ".json";
            return true;
        }
        public static bool Write(List<HierarchyData> datas, ref string outFileName)
        {
            string fileName = ShowSaveFileDialog("*.json", 1, "Scene", ".json");

            var sceneJson = new JObject();
            for (int i = 0; i < datas.Count; i++)
            {
                var dataJson = new JObject();
                dataJson.Add("Type", (int)datas[i].type);
                dataJson.Add("Index", datas[i].Index);
                dataJson.Add("TagIndex", datas[i].tagIndex);
                dataJson.Add("LayerIndex", datas[i].layerIndex);
                dataJson.Add("StaticIndex", datas[i].staticIndex);

                var gameObjectJson = ConvertToJson(datas[i].gameObjectData);
                dataJson.Add("GameObjectData", gameObjectJson);

                var meshJson = ConvertToJson(datas[i].meshData);
                dataJson.Add("MeshData", meshJson);

                var mapJson = ConvertToJson(datas[i].mapData);
                dataJson.Add("MapData", mapJson);

                switch (datas[i].type)
                {
                    case GameObjectType.NavMesh:
                        // ~~~ TODO 
                        break;

                }

                sceneJson.Add("Hierarchy_" + i, dataJson);
            }
            return true;
        }
        public static bool Read(ref HierarchyData outData, string fileName)
        {
            bool hasExt = false;
            string ext = ".json";
            hasExt = fileName.Contains(ext);
            if (hasExt == false)
                fileName = fileName + ".json";

            FileInfo fi = new FileInfo(Paths.HierarchyDataPath + fileName);
            if (fi.Exists == false) return false;

            string text;
            using (StreamReader sw = new StreamReader(Paths.HierarchyDataPath + fileName))
            {
                text = sw.ReadToEnd();
            }

            // 읽기
            var readJson = JObject.Parse(text);

            // Json Parse
            HierarchyData data = new HierarchyData();
            data.type = (GameObjectType)((int)readJson["Type"]);
            data.Index = (int)readJson["Index"];
            data.tagIndex = (int)readJson["TagIndex"];
            data.layerIndex = (int)readJson["LayerIndex"];
            data.staticIndex = (int)readJson["StaticIndex"];




            GameObjectData gameObjectData;
            InjectGameObjectData(out gameObjectData, readJson);
            data.gameObjectData = gameObjectData;

            MeshData meshData;
            InjectMeshData(out meshData, readJson);
            data.meshData = meshData;

            MapData mapData;
            InjectMapData(out mapData, readJson);
            data.mapData = mapData;

            outData = data;
            return true;

            

        }

        public static bool Read(ref ChunkMapData outData, string fileName)
        {
            bool hasExt = false;
            string ext = ".json";
            hasExt = fileName.Contains(ext);
            if (hasExt == false)
                fileName = fileName + ".json";

            FileInfo fi = new FileInfo(Paths.MapDataPath + fileName);
            if (fi.Exists == false) return false;

            string text;
            using (StreamReader sw = new StreamReader(Paths.MapDataPath + fileName))
            {
                text = sw.ReadToEnd();
            }

            // 읽기
            var readJson = JObject.Parse(text);

            // Json Parse
            ChunkMapData data = new ChunkMapData();
            data.group = (int)readJson["Group"];
            data.mapCount = (int)readJson["MapCount"];
            data.maps = new List<HierarchyData>();

            for (int i = 0; i < data.mapCount; i++)
            {
                var hierarchyJson = readJson["Hierarchy_" + i.ToString()];

                HierarchyData hierarchyData = new HierarchyData();
                
                hierarchyData.type = (GameObjectType)((int)hierarchyJson["Type"]);
                hierarchyData.Index = (int)hierarchyJson["Index"];
                hierarchyData.tagIndex = (int)hierarchyJson["TagIndex"];
                hierarchyData.layerIndex = (int)hierarchyJson["LayerIndex"];
                hierarchyData.staticIndex = (int)hierarchyJson["StaticIndex"];

                GameObjectData gameObjectData;
                InjectGameObjectData(out gameObjectData, hierarchyJson);
                hierarchyData.gameObjectData = gameObjectData;

                MeshData meshData;
                InjectMeshData(out meshData, hierarchyJson);
                hierarchyData.meshData = meshData;

                MapData mapData;
                InjectMapData(out mapData, hierarchyJson);
                hierarchyData.mapData = mapData;


                data.maps.Add(hierarchyData);
            }
            outData = data;

            return true;
        }
        public static bool Read(ref ChunkCellData outData, string fileName)
        {
            bool hasExt = false;
            string ext = ".json";
            hasExt = fileName.Contains(ext);
            if (hasExt == false)
                fileName = fileName + ".json";

            FileInfo fi = new FileInfo(Paths.NavMeshData + fileName);
            if (fi.Exists == false) return false;

            string text;
            using (StreamReader sw = new StreamReader(Paths.NavMeshData + fileName))
            {
                text = sw.ReadToEnd();
            }

            // 읽기
            var readJson = JObject.Parse(text);

            // Json Parse
            ChunkCellData data = new ChunkCellData();
            data.navMeshObject = new HierarchyData();
            data.navMeshObject.type = (GameObjectType)((int)readJson["Type"]);
            data.navMeshObject.Index = (int)readJson["Index"];
            data.navMeshObject.tagIndex = (int)readJson["TagIndex"];
            data.navMeshObject.layerIndex = (int)readJson["LayerIndex"];
            data.navMeshObject.staticIndex = (int)readJson["StaticIndex"];

            GameObjectData gameObjectData;
            InjectGameObjectData(out gameObjectData, readJson);
            data.navMeshObject.gameObjectData = gameObjectData;
            
            MeshData meshData;
            InjectMeshData(out meshData, readJson);
            data.navMeshObject.meshData = meshData;

            MapData mapData;
            InjectMapData(out mapData, readJson);
            data.navMeshObject.mapData = mapData;

            NavMeshData navMeshData;
            InjectNavMeshData(out navMeshData, readJson);
            data.navMeshObject.navMeshData = navMeshData;

            data.cells = new List<CellData>();
            for (int i = 0; i < data.navMeshObject.navMeshData.cellCount; i++)
            {

                var cellJson = readJson["Cell_" + i.ToString()];

                CellData cellData = new CellData();
                cellData.cellIndex = (int)cellJson["CellIndex"];
                cellData.position.x = (int)cellJson["PositionX"];
                cellData.position.y = (int)cellJson["PositionY"];
                cellData.position.z = (int)cellJson["PositionZ"];
                cellData.option = (int)cellJson["Option"];
                cellData.group = (int)cellJson["Group"];

                data.cells.Add(cellData);
            }

            outData = data;
            
            return true;

        }

        #region Converter
        private static JObject ConvertToJson(GameObjectData gameObjectData)
        {
            var gameObjectJson = new JObject();
            gameObjectJson.Add("Index", gameObjectData.index);
            gameObjectJson.Add("Name", gameObjectData.name);
            gameObjectJson.Add("Tag", gameObjectData.tag);
            gameObjectJson.Add("Layer", gameObjectData.layer);
            gameObjectJson.Add("StaticType", gameObjectData.staticType);
            var transformJson = new JObject();

            var positionJson = new JObject();
            positionJson.Add("X", gameObjectData.transform.position.x);
            positionJson.Add("Y", gameObjectData.transform.position.y);
            positionJson.Add("Z", gameObjectData.transform.position.z);

            var rotationJson = new JObject();
            rotationJson.Add("X", gameObjectData.transform.rotation.x);
            rotationJson.Add("Y", gameObjectData.transform.rotation.y);
            rotationJson.Add("Z", gameObjectData.transform.rotation.z);

            var scaleJson = new JObject();
            scaleJson.Add("X", gameObjectData.transform.scale.x);
            scaleJson.Add("Y", gameObjectData.transform.scale.y);
            scaleJson.Add("Z", gameObjectData.transform.scale.z);


            transformJson.Add("Position", positionJson);
            transformJson.Add("Rotation", rotationJson);
            transformJson.Add("Scale", scaleJson);

            gameObjectJson.Add("Transform", transformJson);

            return gameObjectJson;
        }

        private static JObject ConvertToJson(MeshData meshData)
        {
            var meshJson = new JObject();
            meshJson.Add("Index", meshData.index);
            meshJson.Add("MeshFilePath", meshData.meshFilePath);
            meshJson.Add("DiffuseTexturePath", meshData.diffuseTexturePath);

            return meshJson;
        }
        private static JObject ConvertToJson(MapData mapData)
        {
            var mapJson = new JObject();
            mapJson.Add("Index", mapData.index);
            mapJson.Add("Group", mapData.group);
            return mapJson;
        }
        private static JObject ConvertToJson(NavMeshData navMeshData)
        {
            var navMeshJson = new JObject();
            navMeshJson.Add("Index", navMeshData.index);
            navMeshJson.Add("CellCount", navMeshData.cellCount);
            return navMeshJson;
        }
        #endregion


        // 각 Inject 함수를 통해 json 버전에 관계없이 값을 읽을 수 있게 한다.
        #region Injections

        private static bool InjectGameObjectData(out GameObjectData gameObjectData, JToken parentToken)
        {
            var jsonGameObjectData = parentToken["GameObjectData"];
            if (jsonGameObjectData == null)
            {
                gameObjectData = default(GameObjectData);
                return false;
            }

            gameObjectData.index = (int)jsonGameObjectData["Index"];
            gameObjectData.name = (string)jsonGameObjectData["Name"];
            gameObjectData.tag = (string)jsonGameObjectData["Tag"];
            gameObjectData.layer = (int)jsonGameObjectData["Layer"];
            gameObjectData.staticType = (int)jsonGameObjectData["StaticType"];

            var jsonTr = jsonGameObjectData["Transform"];
            var jsonPos = jsonTr["Position"];
            var jsonRot = jsonTr["Rotation"];
            var jsonScale = jsonTr["Scale"];

            gameObjectData.transform.position.x = (float)jsonPos["X"];
            gameObjectData.transform.position.y = (float)jsonPos["Y"];
            gameObjectData.transform.position.z = (float)jsonPos["Z"];
            gameObjectData.transform.rotation.x = (float)jsonRot["X"];
            gameObjectData.transform.rotation.y = (float)jsonRot["Y"];
            gameObjectData.transform.rotation.z = (float)jsonRot["Z"];
            gameObjectData.transform.scale.x = (float)jsonScale["X"];
            gameObjectData.transform.scale.y = (float)jsonScale["Y"];
            gameObjectData.transform.scale.z = (float)jsonScale["Z"];

            return true;
        }

        private static bool InjectMeshData(out MeshData meshData, JToken parentToken)
        {

            var jsonMeshData = parentToken["MeshData"];
            if (jsonMeshData == null)
            {
                meshData = default(MeshData);
                return false;
            }
            meshData.index = (int)jsonMeshData["Index"];
            meshData.meshFilePath = (string)jsonMeshData["MeshFilePath"];
            meshData.diffuseTexturePath = (string)jsonMeshData["DiffuseTexturePath"];
            
            return true;
        }

        private static bool InjectMapData(out MapData mapData, JToken parentToken)
        {
            var jsonMapData = parentToken["MapData"];
            if (jsonMapData == null)
            {
                mapData = default(MapData);
                return false;
            }
            mapData.index = (int)jsonMapData["Index"];
            mapData.group = (int)jsonMapData["Group"];

            return true;
        }

        private static bool InjectNavMeshData(out NavMeshData navMeshData, JToken parentToken)
        {
            var jsonNavMeshData = parentToken["NavMeshData"];
            if (jsonNavMeshData == null)
            {
                navMeshData = default(NavMeshData);
                return false;
            }
            navMeshData.index = (int)jsonNavMeshData["Index"];
            navMeshData.cellCount = (int)jsonNavMeshData["CellCount"];

            return true;
        }
        #endregion



        public static string ShowSaveFileDialog
        (
            string filter,
            int filterIndex,
            string defaultFileName,
            string defaultExtension
        )
        {
            SaveFileDialog saveFileDialog = new SaveFileDialog();
                        
            saveFileDialog.Filter = filter;
            saveFileDialog.FilterIndex = filterIndex + 1;
            saveFileDialog.FileName = defaultFileName;
            saveFileDialog.DefaultExt = defaultExtension;

            Nullable<bool> result = saveFileDialog.ShowDialog();

            if (result == true)
            {
                return saveFileDialog.FileName;
            }
            else
            {
                return null;
            }
        }
    }
}
