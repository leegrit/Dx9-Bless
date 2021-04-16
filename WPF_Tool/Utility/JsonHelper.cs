using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using Newtonsoft.Json.Linq;
using WPF_Tool.Data;
using System.IO;
using Microsoft.Win32;
using System.Diagnostics;
using WPF_Tool.Math;

namespace WPF_Tool.Utility
{
    public class JsonHelper
    {
        public static bool Write(HierarchyData data, ref string outFileName)
        {
            string fileName;
            fileName = data.gameObjectData.name;

            var dataJson = ConvertToJson(data);

            switch (data.type)
            {
                case GameObjectType.Mesh:
                    SaveJsonFile(EDataType.Hierarchy, dataJson, fileName, ref outFileName);
                    break;
                case GameObjectType.Pawn:
                    SaveJsonFile(EDataType.Hierarchy, dataJson, fileName, ref outFileName);
                    break;
                case GameObjectType.MapObject:
                    SaveJsonFile(EDataType.Hierarchy, dataJson, fileName, ref outFileName);
                    break;
                case GameObjectType.NavMesh:
                    SaveJsonFile(EDataType.NavMesh, dataJson, fileName, ref outFileName);
                    break;
                case GameObjectType.Terrain:
                    SaveJsonFile(EDataType.Terrain, dataJson, fileName, ref outFileName);
                    break;
                case GameObjectType.Light:
                    SaveJsonFile(EDataType.Light, dataJson, fileName, ref outFileName);
                    break;
            }
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
                var hierarchyJson = ConvertToJson(data.maps[i]);

                dataJson.Add("Hierarchy_" + i.ToString(), hierarchyJson);
            }

            SaveJsonFile(EDataType.Map, dataJson, fileName, ref outFileName);
            return true;
        }
        public static bool Write(ChunkCellData data, ref string outFileName)
        {
            // 사용 x
            Debug.Assert(false);
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
                cellJson = ConvertToJson(data.cells[i]);
                dataJson.Add("Cell_" + i, cellJson);
            }

            SaveJsonFile(EDataType.NavMesh, dataJson, fileName, ref outFileName);
            return true;
        }

        public static bool Write(List<HierarchyData> datas, ref string outFileName)
        {
            string fileName = ShowSaveFileDialog("Json files (*.json)|*.json|Text files (*.txt)|*.txt", 0, "Scene", ".json");
            outFileName = fileName;
            var sceneJson = new JObject();
            sceneJson.Add("HierarchyCount", datas.Count);
            for (int i = 0; i < datas.Count; i++)
            {
                var dataJson = ConvertToJson(datas[i]);
                
                sceneJson.Add("Hierarchy_" + i, dataJson);
            }
            SaveJsonFile(EDataType.Scene, sceneJson, fileName, ref outFileName);
            
            return true;
        }
        public static bool Read(ref HierarchyData outData, string fileName, EDataType dataType = EDataType.Hierarchy)
        {
            string text;

            ReadJsonFile(dataType, fileName, out text);

            // 읽기
            var readJson = JObject.Parse(text);
            
            InjectHierarchyData(out outData, readJson);
            return true;
        }

        public static bool Read(ref ChunkMapData outData, string fileName)
        {
           
            string text;
            ReadJsonFile(EDataType.Map, fileName, out text);

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

                HierarchyData hierarchyData;
                InjectHierarchyData(out hierarchyData, hierarchyJson);

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
                CellData cellData = new CellData();
                InjectCellData(out cellData, i, readJson);
                data.cells.Add(cellData);
            }

            outData = data;
            
            return true;

        }

        public static bool Read(ref List<HierarchyData> outData, string fileName)
        {
            bool hasExt = false;
            string ext = ".json";
            hasExt = fileName.Contains(ext);
            if (hasExt == false)
                fileName = fileName + ".json";

            FileInfo fi = new FileInfo(Paths.SceneDataPath + fileName);
            if (fi.Exists == false) return false;

            string text;
            using (StreamReader sw = new StreamReader(Paths.SceneDataPath + fileName))
            {
                text = sw.ReadToEnd();
            }

            outData = new List<HierarchyData>();
            // 읽기
            var readJson = JObject.Parse(text);
            int hierarchyCount = (int)readJson["HierarchyCount"];

            Debug.Assert(hierarchyCount > 0);
            for (int i = 0; i < hierarchyCount; i++)
            {
                HierarchyData data;

                var hierarchyJson = readJson["Hierarchy_" + i];
                InjectHierarchyData(out data, hierarchyJson);
                

                outData.Add(data);
            }
            return true;
        }
        #region Converter

        private static JObject ConvertToJson(HierarchyData hierarchyData)
        {
            var hierarchyJson = new JObject();
            hierarchyJson.Add("Type", (int)hierarchyData.type);
            hierarchyJson.Add("Index", hierarchyData.Index);
            hierarchyJson.Add("TagIndex", hierarchyData.tagIndex);
            hierarchyJson.Add("LayerIndex", hierarchyData.layerIndex);
            hierarchyJson.Add("StaticIndex", hierarchyData.staticIndex);

            var gameObjectJson = ConvertToJson(hierarchyData.gameObjectData);
            hierarchyJson.Add("GameObjectData", gameObjectJson);

            var meshJson = ConvertToJson(hierarchyData.meshData);
            hierarchyJson.Add("MeshData", meshJson);

            var mapJson = ConvertToJson(hierarchyData.mapData);
            hierarchyJson.Add("MapData", mapJson);

            var navMeshJson = ConvertToJson(hierarchyData.navMeshData);
            hierarchyJson.Add("NavMeshData", navMeshJson);

            var terrainJson = ConvertToJson(hierarchyData.terrainData);
            hierarchyJson.Add("TerrainData", terrainJson);

            var lightJson = ConvertToJson(hierarchyData.lightData);
            hierarchyJson.Add("LightData", lightJson);

            for (int i = 0; i < hierarchyData.navMeshData.cellCount; i++)
            {
                var cellJson = new JObject();
                cellJson = ConvertToJson(hierarchyData.cells[i]);
                hierarchyJson.Add("Cell_" + i, cellJson);
            }
            return hierarchyJson;
        }
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
        private static JObject ConvertToJson(CellData cellData)
        {
            var cellJson = new JObject();
            cellJson.Add("CellIndex", (int)cellData.cellIndex);
            cellJson.Add("PositionX", (int)cellData.position.x);
            cellJson.Add("PositionY", (int)cellData.position.y);
            cellJson.Add("PositionZ", (int)cellData.position.z);
            cellJson.Add("Option", (int)cellData.option);
            cellJson.Add("Group", (int)cellData.group);
            return cellJson;
        }
        private static JObject ConvertToJson(NavMeshData navMeshData)
        {
            var navMeshJson = new JObject();
            navMeshJson.Add("Index", navMeshData.index);
            navMeshJson.Add("CellCount", navMeshData.cellCount);
            return navMeshJson;
        }
        private static JObject ConvertToJson(TerrainData terrainData)
        {
            var terrainJson = new JObject();
            terrainJson.Add("VertexCountX", terrainData.vertexCountX);
            terrainJson.Add("VertexCountZ", terrainData.vertexCountZ);
            terrainJson.Add("TextureCountX", terrainData.textureCountX);
            terrainJson.Add("TextureCountZ", terrainData.textureCountZ);
            terrainJson.Add("VertexInterval", terrainData.vertexInterval);
            terrainJson.Add("DiffuseFilePath", terrainData.diffuseFilePath);
            terrainJson.Add("NormalFilePath", terrainData.normalFilePath);
            return terrainJson;
        }
        private static JObject ConvertToJson(LightData lightData)
        {
            var lightJson = new JObject();
            lightJson.Add("LightType", lightData.lightType);

            /* For Direction */ 
            var directionJson = new JObject();
            directionJson.Add("X", lightData.direction.x);
            directionJson.Add("Y", lightData.direction.y);
            directionJson.Add("Z", lightData.direction.z);
            lightJson.Add("Direction", directionJson);

            /* For Position */
            var positionJson = new JObject();
            positionJson.Add("X", lightData.position.x);
            positionJson.Add("Y", lightData.position.y);
            positionJson.Add("Z", lightData.position.z);
            lightJson.Add("Position", positionJson);

            /* For Ambient */
            var ambientJson = new JObject();
            ambientJson.Add("R", lightData.ambient.r);
            ambientJson.Add("G", lightData.ambient.g);
            ambientJson.Add("B", lightData.ambient.b);
            ambientJson.Add("A", lightData.ambient.a);
            lightJson.Add("Ambient", ambientJson);

            /* For ambient intensity */
            lightJson.Add("AmbientIntensity", lightData.ambientIntensity);

            /* For Diffuse */
            var diffuseJson = new JObject();
            diffuseJson.Add("R", lightData.diffuse.r);
            diffuseJson.Add("G", lightData.diffuse.g);
            diffuseJson.Add("B", lightData.diffuse.b);
            diffuseJson.Add("A", lightData.diffuse.a);
            lightJson.Add("Diffuse", diffuseJson);

            /* For diffuse intensity */
            lightJson.Add("DiffuseIntensity", lightData.diffuseIntensity);

            /* For Specular */
            var specularJson = new JObject();
            specularJson.Add("R", lightData.specular.r);
            specularJson.Add("G", lightData.specular.g);
            specularJson.Add("B", lightData.specular.b);
            specularJson.Add("A", lightData.specular.a);
            lightJson.Add("Specular", specularJson);

            /* For specular intensity */
            lightJson.Add("SpecularIntensity", lightData.specularIntensity);

            /* For specular power */
            lightJson.Add("SpecularPower", lightData.specularPower);

            /* For range */
            lightJson.Add("Range", lightData.range);

            /* For Cone */
            lightJson.Add("Cone", lightData.cone);

            /* For constant */
            lightJson.Add("Constant", lightData.constant);

            /* For linear */
            lightJson.Add("Linear", lightData.linear);

            /* For quadratic */
            lightJson.Add("Quadratic", lightData.quadratic);

            return lightJson;
        }
        #endregion


        // 각 Inject 함수를 통해 json 버전에 관계없이 값을 읽을 수 있게 한다.
        #region Injections
        private static bool InjectHierarchyData(out HierarchyData hierarchyData, JToken parentToken)
        {
           // var readJson = JObject.Parse(text);

            // Json Parse
            HierarchyData data = new HierarchyData();
            data.type = (GameObjectType)((int)parentToken["Type"]);
            data.Index = (int)parentToken["Index"];
            data.tagIndex = (int)parentToken["TagIndex"];
            data.layerIndex = (int)parentToken["LayerIndex"];
            data.staticIndex = (int)parentToken["StaticIndex"];




            GameObjectData gameObjectData;
            InjectGameObjectData(out gameObjectData, parentToken);
            data.gameObjectData = gameObjectData;

            MeshData meshData;
            InjectMeshData(out meshData, parentToken);
            data.meshData = meshData;

            MapData mapData;
            InjectMapData(out mapData, parentToken);
            data.mapData = mapData;

            NavMeshData navMeshData;
            InjectNavMeshData(out navMeshData, parentToken);
            data.navMeshData = navMeshData;

            TerrainData terrainData;
            InjectTerrainData(out terrainData, parentToken);
            data.terrainData = terrainData;

            LightData lightData;
            InjectLightData(out lightData, parentToken);
            data.lightData = lightData;

            data.cells = new List<CellData>();
            for (int j = 0; j < navMeshData.cellCount; j++)
            {
                CellData cellData;
                InjectCellData(out cellData, j, parentToken);
                data.cells.Add(cellData);
            }

            hierarchyData = data;
            return true;
        }

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

        private static bool InjectCellData(out CellData cellData, int index, JToken parentToken)
        {
            var jsonCellData = parentToken["Cell_" + index.ToString()];
            if (jsonCellData == null)
            {
                cellData = default(CellData);
                return false;
            }

            cellData.cellIndex = (int)jsonCellData["CellIndex"];
            cellData.position.x = (int)jsonCellData["PositionX"];
            cellData.position.y = (int)jsonCellData["PositionY"];
            cellData.position.z = (int)jsonCellData["PositionZ"];
            cellData.option = (int)jsonCellData["Option"];
            cellData.group = (int)jsonCellData["Group"];

            return true;
        }
        private static bool InjectTerrainData(out TerrainData terrainData, JToken parentToken)
        {
            var jsonTerrainData = parentToken["TerrainData"];
            if (jsonTerrainData == null)
            {
                terrainData = default(TerrainData);
                return false;
            }
            terrainData.vertexCountX = (int)jsonTerrainData["VertexCountX"];
            terrainData.vertexCountZ = (int)jsonTerrainData["VertexCountZ"];
            terrainData.textureCountX = (float)jsonTerrainData["TextureCountX"];
            terrainData.textureCountZ = (float)jsonTerrainData["TextureCountZ"];
            terrainData.vertexInterval = (float)jsonTerrainData["VertexInterval"];
            terrainData.diffuseFilePath = (string)jsonTerrainData["DiffuseFilePath"];
            terrainData.normalFilePath = (string)jsonTerrainData["NormalFilePath"];

            return true;
        }
        private static bool InjectLightData(out LightData lightData, JToken parentToken)
        {
            var lightDataJson = parentToken["LightData"];

            lightData = default(LightData);
            if (lightDataJson == null)
            {
                return false;
            }

            /* For light type */
            lightData.lightType = (int)lightDataJson["LightType"];

            /* For direction */
            var directionJson = lightDataJson["Direction"];
            lightData.direction.x = (float)directionJson["X"];
            lightData.direction.y = (float)directionJson["Y"];
            lightData.direction.z = (float)directionJson["Z"];

            /* For position */
            var positionJson = lightDataJson["Position"];
            lightData.position.x = (float)positionJson["X"];
            lightData.position.y = (float)positionJson["Y"];
            lightData.position.z = (float)positionJson["Z"];

            /* For ambient */
            var ambientJson = lightDataJson["Ambient"];
            lightData.ambient.r = (float)ambientJson["R"];
            lightData.ambient.g = (float)ambientJson["G"];
            lightData.ambient.b = (float)ambientJson["B"];
            lightData.ambient.a = (float)ambientJson["A"];

            /* For ambient intensity */
            lightData.ambientIntensity = (float)lightDataJson["AmbientIntensity"];

            /* For diffuse */
            var diffuseJson = lightDataJson["Diffuse"];
            lightData.diffuse.r = (float)diffuseJson["R"];
            lightData.diffuse.g = (float)diffuseJson["G"];
            lightData.diffuse.b = (float)diffuseJson["B"];
            lightData.diffuse.a = (float)diffuseJson["A"];

            /* For diffuse intensity */
            lightData.diffuseIntensity = (float)lightDataJson["DiffuseIntensity"];

            /* For specular */
            var specularJson = lightDataJson["Specular"];
            lightData.specular.r = (float)specularJson["R"];
            lightData.specular.g = (float)specularJson["G"];
            lightData.specular.b = (float)specularJson["B"];
            lightData.specular.a = (float)specularJson["A"];

            /* For specular intensity */
            lightData.specularIntensity = (float)lightDataJson["SpecularIntensity"];

            /* For specular power */
            lightData.specularPower = (float)lightDataJson["SpecularPower"];

            /* For Range */
            lightData.range = (float)lightDataJson["Range"];

            /* For Cone */
            lightData.cone = (float)lightDataJson["Cone"];

            /* For Constant */
            lightData.constant = (float)lightDataJson["Constant"];

            /* For Linear */
            lightData.linear = (float)lightDataJson["Linear"];

            /* For Exp */
            lightData.quadratic = (float)lightDataJson["Quadratic"];

            return true;
        }
        #endregion


        private static void SaveJsonFile(EDataType type, JObject json, string fileName, ref string outFileName)
        {
            switch (type)
            {
                case EDataType.Hierarchy:
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
                        if (count != 0)
                            fileName = fileName + count;
                    }

                    using (StreamWriter sw = new StreamWriter(Paths.HierarchyDataPath + fileName + ".json", false, new UTF8Encoding(false)))
                    {
                        sw.Write(json.ToString());
                    }
                    outFileName = fileName + ".json";
                    break;

                case EDataType.Map:
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



                            using (StreamWriter sw = new StreamWriter(Paths.BackupPath + backupFileName + ".json", false, new UTF8Encoding(false)))
                            {
                                sw.Write(json.ToString());
                            }
                        }
                    }


                    using (StreamWriter sw = new StreamWriter(Paths.MapDataPath + fileName + ".json",false, new UTF8Encoding(false)))
                    {
                        sw.Write(json.ToString());
                    }
                    outFileName = fileName + ".json";
                    break;
                case EDataType.NavMesh:
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



                            using (StreamWriter sw = new StreamWriter(Paths.BackupPath + backupFileName + ".json", false, new UTF8Encoding(false)))
                            {
                                sw.Write(json.ToString());
                            }
                        }
                    }


                    using (StreamWriter sw = new StreamWriter(Paths.NavMeshData + fileName + ".json", false, new UTF8Encoding(false)))
                    {
                        sw.Write(json.ToString());
                    }
                    outFileName = fileName + ".json";
                    break;
                case EDataType.Scene:
                    using (StreamWriter sw = new StreamWriter(fileName, false, Encoding.UTF8))
                    {
                        sw.Write(json.ToString());
                    }
                    outFileName = fileName;
                    break;
                case EDataType.Terrain:
                    if (System.IO.Directory.Exists(Paths.TerrainDataPath))
                    {
                        System.IO.DirectoryInfo info = new System.IO.DirectoryInfo(Paths.TerrainDataPath);
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
                        if (count != 0)
                            fileName = fileName + count;
                    }

                    using (StreamWriter sw = new StreamWriter(Paths.TerrainDataPath + fileName + ".json", false, new UTF8Encoding(false)))
                    {
                        sw.Write(json.ToString());
                    }
                    outFileName = fileName + ".json";
                    break;
                case EDataType.Light:
                    if (System.IO.Directory.Exists(Paths.LightDataPath))
                    {
                        System.IO.DirectoryInfo info = new System.IO.DirectoryInfo(Paths.LightDataPath);
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
                        if (count != 0)
                            fileName = fileName + count;
                    }

                    using (StreamWriter sw = new StreamWriter(Paths.LightDataPath + fileName + ".json", false, new UTF8Encoding(false)))
                    {
                        sw.Write(json.ToString());
                    }
                    outFileName = fileName + ".json";
                    break;
                default:
                    outFileName = default(string);
                    Debug.Assert(false);
                    break;
            }
        }
        private static bool ReadJsonFile(EDataType type, string fileName, out string readText)
        {
            bool hasExt = false;
            string ext = ".json";
            hasExt = fileName.Contains(ext);
            if (hasExt == false)
                fileName = fileName + ".json";

            readText = default(string);

            string defaultPath = default(string);
            switch (type)
            {
                case EDataType.Hierarchy:
                    defaultPath = Paths.HierarchyDataPath;
                    break;
                case EDataType.Map:
                    defaultPath = Paths.MapDataPath;
                    break;
                case EDataType.NavMesh:
                    defaultPath = Paths.NavMeshData;
                    break;
                case EDataType.Scene:
                    defaultPath = Paths.SceneDataPath;
                    break;
                case EDataType.Terrain:
                    defaultPath = Paths.TerrainDataPath;
                    break;
                case EDataType.Light:
                    defaultPath = Paths.LightDataPath;
                    break;
                default:
                    Debug.Assert(false);
                    break;
            }

            FileInfo fi = new FileInfo(defaultPath + fileName);
            if (fi.Exists == false) return false;
            
            using (StreamReader sw = new StreamReader(defaultPath + fileName))
            {
                readText = sw.ReadToEnd();
            }
            return true;
           
        }
        public static string ShowSaveFileDialog
        (
            string filter,
            int filterIndex,
            string defaultFileName,
            string defaultExtension
        )
        {
            SaveFileDialog saveFileDialog = new SaveFileDialog();

            saveFileDialog.InitialDirectory = Paths.SceneDataPath;
                           
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
