using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using Newtonsoft.Json.Linq;
using WPF_Tool.Data;
using System.IO;

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
            dataJson.Add("Index", data.index);
            dataJson.Add("TagIndex", data.tagIndex);
            dataJson.Add("LayerIndex", data.layerIndex);
            dataJson.Add("StaticIndex", data.staticIndex);

            var gameObjectJson = new JObject();
            gameObjectJson.Add("Index", data.gameObjectData.index);
            gameObjectJson.Add("Name", data.gameObjectData.name);
            gameObjectJson.Add("Tag", data.gameObjectData.tag);
            gameObjectJson.Add("Layer", data.gameObjectData.layer);
            gameObjectJson.Add("StaticType", data.gameObjectData.staticType);
            var transformJson = new JObject();

            var positionJson = new JObject();
            positionJson.Add("X", data.gameObjectData.transform.position.x);
            positionJson.Add("Y", data.gameObjectData.transform.position.y);
            positionJson.Add("Z", data.gameObjectData.transform.position.z);

            var rotationJson = new JObject();
            rotationJson.Add("X", data.gameObjectData.transform.rotation.x);
            rotationJson.Add("Y", data.gameObjectData.transform.rotation.y);
            rotationJson.Add("Z", data.gameObjectData.transform.rotation.z);

            var scaleJson = new JObject();
            scaleJson.Add("X", data.gameObjectData.transform.scale.x);
            scaleJson.Add("Y", data.gameObjectData.transform.scale.y);
            scaleJson.Add("Z", data.gameObjectData.transform.scale.z);


            transformJson.Add("Position", positionJson);
            transformJson.Add("Rotation", rotationJson);
            transformJson.Add("Scale", scaleJson);

            gameObjectJson.Add("Transform", transformJson);

            dataJson.Add("GameObjectData", gameObjectJson);

            var meshJson = new JObject();
            meshJson.Add("Index", data.meshData.index);
            meshJson.Add("MeshFilePath", data.meshData.meshFilePath);
            meshJson.Add("DiffuseTexturePath", data.meshData.diffuseTexturePath);

            dataJson.Add("MeshData", meshJson);

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
        //public static void Write(GameObjectData data)
        //{
        //    string fileName;

        //    fileName = data.name;

        //    var dataJson = new JObject();
        //    dataJson.Add("Index", data.index);
        //    dataJson.Add("Name", data.name);
        //    dataJson.Add("Tag", data.tag);
        //    dataJson.Add("Layer", data.layer);
        //    dataJson.Add("StaticType", data.staticType);
        //    var transformJson = new JObject();

        //    var positionJson = new JObject();
        //    positionJson.Add("X", data.transform.position.x);
        //    positionJson.Add("Y", data.transform.position.y);
        //    positionJson.Add("Z", data.transform.position.z);

        //    var rotationJson = new JObject();
        //    rotationJson.Add("X", data.transform.rotation.x);
        //    rotationJson.Add("Y", data.transform.rotation.y);
        //    rotationJson.Add("Z", data.transform.rotation.z);

        //    var scaleJson = new JObject();
        //    scaleJson.Add("X", data.transform.scale.x);
        //    scaleJson.Add("Y", data.transform.scale.y);
        //    scaleJson.Add("Z", data.transform.scale.z);


        //    transformJson.Add("Position", positionJson);
        //    transformJson.Add("Rotation", rotationJson);
        //    transformJson.Add("Scale", scaleJson);

        //    dataJson.Add(transformJson);

        //    // 여기서 같은 파일 이름이 있을 경우
        //    // 이름 뒤에 번호 0 ~ 붙여서 fileName 최종 결정

        //    if (System.IO.Directory.Exists(Paths.GameObjectDataPath))
        //    {
        //        System.IO.DirectoryInfo info = new System.IO.DirectoryInfo(Paths.GameObjectDataPath);
        //        int count = 0;
        //        foreach (var item in info.GetFiles())
        //        {
        //            if (item.Name == fileName + ".json" || item.Name == fileName + count + ".json")
        //            {
        //                count++;
        //                // 같은게 있으면 count를 늘려준다.
        //                // 중복이 여러 개 있을 수도 있기 때문.
        //            }
        //        }
        //        fileName = fileName + count;
        //    }

        //    using (StreamWriter sw = new StreamWriter(Paths.GameObjectDataPath + fileName + ".json", false, Encoding.UTF8))
        //    {
        //        sw.Write(dataJson.ToString());
        //    }
        //}
        //public static void Write(MeshData data)
        //{
        //    //string fileName;



        //    //var dataJson = new JObject();
        //    //dataJson.Add("Index", data.index);
        //    //dataJson.Add("Name", data.name);
        //    //dataJson.Add("Tag", data.tag);
        //    //dataJson.Add("Layer", data.layer);
        //    //dataJson.Add("StaticType", data.staticType);
        //    //var transformJson = new JObject();

        //    //// 여기서 같은 파일 이름이 있을 경우
        //    //// 이름 뒤에 번호 0 ~ 붙여서 fileName 최종 결정

        //    //if (System.IO.Directory.Exists(Paths.MeshDataPath))
        //    //{
        //    //    System.IO.DirectoryInfo info = new System.IO.DirectoryInfo(Paths.MeshDataPath);
        //    //    int count = 0;
        //    //    foreach (var item in info.GetFiles())
        //    //    {
        //    //        if (item.Name == fileName + ".json" || item.Name == fileName + count + ".json")
        //    //        {
        //    //            count++;
        //    //            // 같은게 있으면 count를 늘려준다.
        //    //            // 중복이 여러 개 있을 수도 있기 때문.
        //    //        }
        //    //    }
        //    //    fileName = fileName + count;
        //    //}

        //    //using (StreamWriter sw = new StreamWriter(Paths.MeshDataPath + fileName + ".json", false, Encoding.UTF8))
        //    //{
        //    //    sw.Write(dataJson.ToString());
        //    //}
        //}
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
            data.index = (int)readJson["Index"];
            data.tagIndex = (int)readJson["TagIndex"];
            data.layerIndex = (int)readJson["LayerIndex"];
            data.staticIndex = (int)readJson["StaticIndex"];




            GameObjectData gameObjectData;

            var jsonGameObjectData = readJson["GameObjectData"];

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

            data.gameObjectData = gameObjectData;


            var jsonMeshData = readJson["MeshData"];

            MeshData meshData = default(MeshData);
            meshData.index = (int)jsonMeshData["Index"];
            meshData.meshFilePath = (string)jsonMeshData["MeshFilePath"];
            meshData.diffuseTexturePath = (string)jsonMeshData["DiffuseTexturePath"];

            data.meshData = meshData;

            outData = data;
            return true;

            
            //// json 파싱
            //GameObjectData data;
            //data.index = (int)readJson["Index"];
            //data.name = (string)readJson["Name"];
        }
        //public static bool Read(ref GameObjectData outData,  string fileName)
        //{
        //    bool hasExt = false;
        //    string ext = ".json";
        //    hasExt = fileName.Contains(ext);
        //    if (hasExt == false)
        //        fileName = fileName+ ".json";

        //    FileInfo fi = new FileInfo(Paths.GameObjectDataPath + fileName);
        //    if (fi.Exists == false) return false;

        //    string text;
        //    using (StreamReader sw = new StreamReader(Paths.GameObjectDataPath + fileName))
        //    {
        //        text = sw.ReadToEnd();
        //    }

        //    // 읽기
        //    var readJson = JObject.Parse(text);

        //    // json 파싱
        //    GameObjectData data;
        //    data.index = (int)readJson["Index"];
        //    data.name = (string)readJson["Name"];
        //    data.tag = (string)readJson["Tag"];
        //    data.layer = (int)readJson["Layer"];
        //    data.staticType = (int)readJson["StaticType"];

        //    var jsonTr = readJson["Transform"];

        //    var jsonPos = jsonTr["Position"];
        //    var jsonRot = jsonTr["Rotation"];
        //    var jsonScale = jsonTr["Scale"];

        //    Transform dataTr;
        //    dataTr.position.x = (int)jsonPos["X"];
        //    dataTr.position.y = (int)jsonPos["Y"];
        //    dataTr.position.z = (int)jsonPos["Z"];
        //    dataTr.rotation.x = (int)jsonRot["X"];
        //    dataTr.rotation.y = (int)jsonRot["Y"];
        //    dataTr.rotation.z = (int)jsonRot["Z"];
        //    dataTr.scale.x = (int)jsonScale["X"];
        //    dataTr.scale.y = (int)jsonScale["Y"];
        //    dataTr.scale.z = (int)jsonScale["Z"];

        //    data.transform = dataTr;

        //    outData = data;
        //    return true;
        //}
        //public static MeshData Read(string fileName)
        //{

        //}
    }
}
