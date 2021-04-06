
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Data;
using System.Windows.Documents;
using System.Windows.Input;
using System.Windows.Media;
using System.Windows.Media.Imaging;
using System.Windows.Navigation;
using System.Windows.Shapes;
using System.Windows.Threading;
using System.Windows.Interop;
using System.Runtime.InteropServices;
using System.Security.Permissions;
using WPF_Tool.Data;
using WPF_Tool.Utility;
using WPF_Tool.Scripts;
using Microsoft.Win32;
using System.IO;
using System.Diagnostics;
using Newtonsoft.Json.Linq;
using WPF_Tool.Math;

namespace WPF_Tool
{
    public partial class MainWindow
    {
        private void BTN_MeshFile(object sender, RoutedEventArgs e)
        {
            OpenFileDialog ofdlg = new OpenFileDialog();
            {
                // 기본 폴더
                ofdlg.InitialDirectory = Paths.AssetPath;
                ofdlg.CheckFileExists = true; // 파일 존재여부 확인
                ofdlg.CheckPathExists = true; // 폴더 존재여부 확인

                // 파일 열기(값의 유무 확인)
                if (ofdlg.ShowDialog().GetValueOrDefault())
                {
                    for (int i = 0; i < hierarchyList.Count; i++)
                    {
                        if (hierarchyList[i].Index == selectedIndex)
                        {
                            //int filePathIndex = ofdlg.FileName.LastIndexOf(Paths.ResourcePath);
                            string filePath = ofdlg.FileName.Substring(Paths.ResourcePath.Count());

                            int index = ofdlg.FileName.LastIndexOf("\\");
                            string onlyName = ofdlg.FileName.Substring(index + 1);
                            int extIndex = onlyName.LastIndexOf(".");
                            string ext = onlyName.Substring(extIndex);
                            hierarchyList[i].meshData.meshFilePath = onlyName;
                            MeshFilePath.Text = onlyName;
                            // x file은 따로 텍스처가 필요 없기 때문
                            if (ext == ".X" || ext == ".x")
                                DiffuseFilePath.Text = onlyName;


                            HierarchyData data = hierarchyList[i];
                            data.meshData.meshFilePath = filePath;
                            hierarchyList[i] = data;

                            Externs.InsertMeshData(ref data.meshData);
                            ShowInspector(data);
//                             if (data.type == GameObjectType.Pawn)
//                             {
//                                 // 여기서 애니메이션 개수를 구한 후 
//                                 // 각 애니메이션의 이름을 얻어와서 띄워줘야한다.
//                                 int animCount = Externs.GetAnimationCount();
//                                 AnimationCount.Text = animCount.ToString();
//                                 AnimationIndex.Text = (0).ToString(); // 기본값 0
// 
//                                 // 여기서 비우고 아래에서 다시 채워준다.
//                                 AnimationComboBox.Items.Clear();
//                                 for (int animIndex = 0; animIndex < animCount; animIndex++)
//                                 {
//                                     IntPtr animName = Externs.GetAnimationName(animIndex);
//                                     if (animName == null) continue;
// 
//                                     string convertedName = Marshal.PtrToStringUni(animName);
// 
//                                     ComboBoxItem item = new ComboBoxItem();
//                                     item.Uid = animIndex.ToString();
//                                     item.Content = convertedName;
//                                     item.Selected += Animation_Selected;
//                                     AnimationComboBox.Items.Add(item);
//                                 }
// 
//                             }

                            break;
                        }
                    }
                }
            }
        }
        private void BTN_Diffuse(object sender, RoutedEventArgs e)
        {
            OpenFileDialog ofdlg = new OpenFileDialog();
            {
                // 기본 폴더
                //ofdlg.InitialDirectory = System.IO.Path.GetDirectoryName(AppDomain.CurrentDomain.BaseDirectory);
                ofdlg.InitialDirectory = Paths.AssetPath;
                ofdlg.CheckFileExists = true; // 파일 존재여부 확인
                ofdlg.CheckPathExists = true; // 폴더 존재여부 확인

                // 파일 열기(값의 유무 확인)
                if (ofdlg.ShowDialog().GetValueOrDefault())
                {
                    for (int i = 0; i < hierarchyList.Count; i++)
                    {
                        if (hierarchyList[i].Index == selectedIndex)
                        {
                            int filePathIndex = ofdlg.FileName.LastIndexOf(Paths.ResourcePath);
                            string filePath = ofdlg.FileName.Substring(Paths.ResourcePath.Count());


                            int index = ofdlg.FileName.LastIndexOf("\\");
                            string text = ofdlg.FileName.Substring(index + 1);

                            hierarchyList[i].meshData.diffuseTexturePath = text;
                            DiffuseFilePath.Text = text;

                            HierarchyData data = hierarchyList[i];
                            data.meshData.diffuseTexturePath = filePath;
                            hierarchyList[i] = data;
                            Externs.InsertMeshData(ref data.meshData);

                            break;
                        }
                    }
                }
            }
        }
        private void BTN_NavPrimDelete(object sender, RoutedEventArgs e)
        {
            var focusedElement = lastFocusedElement;
            TreeViewItem selectedItem = focusedElement as TreeViewItem;
            if (selectedItem == null) return;
            string navPrimStr = "NavPrimitive";
            bool isNavPrim = false;
            isNavPrim = ((string)selectedItem.Header).Contains(navPrimStr);

            if (isNavPrim == false) return;



            HierarchyData selected = selectedHierarchy;
            if (selected.type != GameObjectType.NavMesh)
            {
                Debug.Assert(false);
            }

            // 3개 모두 완성된 primitive만 지울 수 있다.
            // C++ engine과 index를 맞추기 위함
            if (selectedItem.Items.Count != 3)
                return;
            // Inspector 상에서 해당 prim 하위에 있는
            // 모든 셀을 지운다.
            for (int i = 0; i < selectedItem.Items.Count; i++)
            {
                TreeViewItem cellItem = selectedItem.Items[i] as TreeViewItem;
                for (int j = 0; j < selected.cells.Count; j++)
                {
                    if (selected.cells[j].cellIndex.ToString() == cellItem.Uid)
                    {
                        selected.cells.RemoveAt(j);
                        break;
                    }
                }
            }
            for (int i = 0; i < CellList.Items.Count; i++)
            {
                TreeViewItem navPrimItem = CellList.Items[i] as TreeViewItem;
                if (navPrimItem.Uid == selectedItem.Uid)
                {
                    CellList.Items.RemoveAt(i);
                    break;
                }
            }

            selectedItem.Items.Clear();
            Externs.RemoveNavPrim(Int32.Parse(selectedItem.Uid));

            selected.navMeshData.cellCount = selected.cells.Count;
        }
        private void BTN_TerrainDiffuseLoad(object sender, RoutedEventArgs e)
        {
            OpenFileDialog ofdlg = new OpenFileDialog();
            {
                ofdlg.InitialDirectory = Paths.AssetPath;
                ofdlg.CheckFileExists = true;
                ofdlg.CheckPathExists = true;

                if (ofdlg.ShowDialog().GetValueOrDefault())
                {
                    string filePath = ofdlg.FileName.Substring(Paths.ResourcePath.Count());

                    int index = ofdlg.FileName.LastIndexOf("\\");
                    string onlyName = ofdlg.FileName.Substring(index + 1);

                    Debug.Assert(selectedHierarchy.type == GameObjectType.Terrain);
                    selectedHierarchy.terrainData.diffuseFilePath = filePath;

                    TerrainDiffuseFilePath.Text = onlyName;

                    Externs.InsertTerrainData(ref selectedHierarchy.terrainData);
                }
            }
        }
        private void BTN_TerrainNormalLoad(object sender, RoutedEventArgs e)
        {
            OpenFileDialog ofdlg = new OpenFileDialog();
            {
                ofdlg.InitialDirectory = Paths.AssetPath;
                ofdlg.CheckFileExists = true;
                ofdlg.CheckPathExists = true;

                if (ofdlg.ShowDialog().GetValueOrDefault())
                {
                    string filePath = ofdlg.FileName.Substring(Paths.ResourcePath.Count());

                    int index = ofdlg.FileName.LastIndexOf("\\");
                    string onlyName = ofdlg.FileName.Substring(index + 1);

                    Debug.Assert(selectedHierarchy.type == GameObjectType.Terrain);
                    selectedHierarchy.terrainData.normalFilePath = filePath;

                    TerrainNormalFilePath.Text = onlyName;

                    Externs.InsertTerrainData(ref selectedHierarchy.terrainData);
                }
            }
        }
        private void SLT_MapGroup(object sender, RoutedEventArgs e)
        {
            ComboBox item = sender as ComboBox;
            int comboBoxIndex = item.SelectedIndex;

            for (int i = 0; i < hierarchyList.Count; i++)
            {
                if (hierarchyList[i].Index == selectedIndex)
                {
                    HierarchyData data = hierarchyList[i];
                    data.mapData.group = comboBoxIndex;
                    hierarchyList[i] = data;
                    break;
                }
            }
        }
        
        private void Tag_Selected(object sender, RoutedEventArgs e)
        {
            ComboBox item = sender as ComboBox;
            int comboBoxIndex = item.SelectedIndex;

            for (int i = 0; i < hierarchyList.Count; i++)
            {
                if (hierarchyList[i].Index == SelectedIndex)
                {
                    HierarchyData data = hierarchyList[i];
                    data.tagIndex = comboBoxIndex;
                    data.gameObjectData.tag = Strings.Tags[comboBoxIndex];
                    hierarchyList[i] = data;
                    Externs.InsertGameData(ref data.gameObjectData);
                    break;
                }
            }

        }

        private void Layer_Selected(object sender, RoutedEventArgs e)
        {
            ComboBox item = sender as ComboBox;
            int comboBoxIndex = item.SelectedIndex;
            for (int i = 0; i < hierarchyList.Count; i++)
            {
                if (hierarchyList[i].Index == selectedIndex)
                {
                    HierarchyData data = hierarchyList[i];
                    data.layerIndex = comboBoxIndex;
                    data.gameObjectData.layer = comboBoxIndex;
                    hierarchyList[i] = data;
                    Externs.InsertGameData(ref data.gameObjectData);
                    break;
                }
            }
        }

        private void Static_Selected(object sender, RoutedEventArgs e)
        {
            ComboBox item = sender as ComboBox;
            int comboBoxIndex = item.SelectedIndex;
            for (int i = 0; i < hierarchyList.Count; i++)
            {
                if (hierarchyList[i].Index == selectedIndex)
                {
                    HierarchyData data = hierarchyList[i];
                    data.staticIndex = comboBoxIndex;
                    data.gameObjectData.staticType = comboBoxIndex;
                    hierarchyList[i] = data;
                    Externs.InsertGameData(ref data.gameObjectData);
                    break;
                }
            }
        }
        private void Animation_Selected(object sender, RoutedEventArgs e)
        {
            ComboBoxItem item = sender as ComboBoxItem;
            int index = Int32.Parse(item.Uid);
            AnimationIndex.Text = item.Uid;
            Externs.SetAnimation(index);
        }
        private void Active_Checked(object sender, RoutedEventArgs e)
        {
            if (bWindowInit)
                Externs.ActiveEditObject();
        }

        private void Active_Unchecked(object sender, RoutedEventArgs e)
        {
            if (bWindowInit)
                Externs.InactiveEditObject();
        }

        public void ShowInspector(HierarchyData data)
        {
            GameObjectName.Text = data.gameObjectData.name;
            ObjectTag.SelectedIndex = data.tagIndex;
            ObjectLayer.SelectedIndex = data.layerIndex;
            ObjectStatic.SelectedIndex = data.staticIndex;
            PositionX.Text = data.gameObjectData.transform.position.x.ToString();
            PositionY.Text = data.gameObjectData.transform.position.y.ToString();
            PositionZ.Text = data.gameObjectData.transform.position.z.ToString();
            RotationX.Text = data.gameObjectData.transform.rotation.x.ToString();
            RotationY.Text = data.gameObjectData.transform.rotation.y.ToString();
            RotationZ.Text = data.gameObjectData.transform.rotation.z.ToString();
            ScaleX.Text = data.gameObjectData.transform.scale.x.ToString();
            ScaleY.Text = data.gameObjectData.transform.scale.y.ToString();
            ScaleZ.Text = data.gameObjectData.transform.scale.z.ToString();

            MeshData.Visibility = Visibility.Collapsed;
            TransformData.Visibility = Visibility.Collapsed;
            MapData.Visibility = Visibility.Collapsed;
            CellData.Visibility = Visibility.Collapsed;
            AnimationData.Visibility = Visibility.Collapsed;
            TerrainData.Visibility = Visibility.Collapsed;
            LightData.Visibility = Visibility.Collapsed;
            switch (data.type)
            {
                case GameObjectType.Mesh:
                    {
                        MeshData.Visibility = Visibility.Visible;
                        TransformData.Visibility = Visibility.Visible;

                        string meshOnlyName = "";
                        string ext = "";
                        int meshIndex = data.meshData.meshFilePath.LastIndexOf("\\");

                        if(meshIndex > 0)
                            meshOnlyName = data.meshData.meshFilePath.Substring(meshIndex + 1);

                        int extIndex = meshOnlyName.LastIndexOf(".");

                        if(extIndex > 0)
                            ext = meshOnlyName.Substring(extIndex);

                        string diffuseOnlyName = "";
                        int diffuseIndex = data.meshData.diffuseTexturePath.LastIndexOf("\\");
                        if(diffuseIndex > 0)
                            diffuseOnlyName = data.meshData.diffuseTexturePath.Substring(diffuseIndex + 1);

                        MeshFilePath.Text = meshOnlyName;
                        if (ext == ".X" || ext == ".x")
                        {
                            DiffuseFilePath.Text = meshOnlyName;
                        }
                        else
                        {
                            DiffuseFilePath.Text = diffuseOnlyName;
                        }

                        Externs.InsertGameData(ref data.gameObjectData);
                        Externs.InsertMeshData(ref data.meshData);
                        break;
                    }
                case GameObjectType.Pawn:
                    {
                        MeshData.Visibility = Visibility.Visible;
                        TransformData.Visibility = Visibility.Visible;
                        AnimationData.Visibility = Visibility.Visible;

                        string meshOnlyName = "";
                        string ext = "";
                        int meshIndex = data.meshData.meshFilePath.LastIndexOf("\\");

                        if (meshIndex > 0)
                            meshOnlyName = data.meshData.meshFilePath.Substring(meshIndex + 1);

                        int extIndex = meshOnlyName.LastIndexOf(".");

                        if (extIndex > 0)
                            ext = meshOnlyName.Substring(extIndex);

                        string diffuseOnlyName = "";
                        int diffuseIndex = data.meshData.diffuseTexturePath.LastIndexOf("\\");
                        if (diffuseIndex > 0)
                            diffuseOnlyName = data.meshData.diffuseTexturePath.Substring(diffuseIndex + 1);

                        MeshFilePath.Text = meshOnlyName;
                        if (ext == ".X" || ext == ".x")
                        {
                            DiffuseFilePath.Text = meshOnlyName;
                        }
                        else
                        {
                            DiffuseFilePath.Text = diffuseOnlyName;
                        }


                        Externs.InsertGameData(ref data.gameObjectData);
                        Externs.InsertMeshData(ref data.meshData);

                        // 아래 데이터들은 Insert를 마친 후 세팅되어야한다.
                        // 여기서 애니메이션 개수를 구한 후 
                        // 각 애니메이션의 이름을 얻어와서 띄워줘야한다.
                        int animCount = Externs.GetAnimationCount();
                        AnimationCount.Text = animCount.ToString();
                        AnimationIndex.Text = (0).ToString(); // 기본값 0

                        // 여기서 비우고 아래에서 다시 채워준다.
                        AnimationComboBox.Items.Clear();
                        for (int animIndex = 0; animIndex < animCount; animIndex++)
                        {
                            AnimNameData animName = default(AnimNameData);
                           Externs.GetAnimationName(ref animName, animIndex);
                            
                            //String convertedName = Marshal.PtrToStringUni(animName);
                            ComboBoxItem item = new ComboBoxItem();
                            item.Uid = animIndex.ToString();
                            item.Content = animName.name;
                            item.Selected += Animation_Selected;

                            AnimationComboBox.Items.Add(item);
                        }
                        // 기본값
                        AnimationComboBox.SelectedIndex = 0;
                        break;
                    }
                case GameObjectType.NavMesh:
                    CellData.Visibility = Visibility.Visible;
                    CellCount.Text = data.navMeshData.cellCount.ToString();
                    break;
                case GameObjectType.MapObject:
                    {
                        MeshData.Visibility = Visibility.Visible;
                        TransformData.Visibility = Visibility.Visible;
                        MapData.Visibility = Visibility.Visible;


                        string meshOnlyName = "";
                        string ext = "";
                        int meshIndex = data.meshData.meshFilePath.LastIndexOf("\\");

                        if (meshIndex > 0)
                            meshOnlyName = data.meshData.meshFilePath.Substring(meshIndex + 1);

                        int extIndex = meshOnlyName.LastIndexOf(".");

                        if (extIndex > 0)
                            ext = meshOnlyName.Substring(extIndex);

                        string diffuseOnlyName = "";
                        int diffuseIndex = data.meshData.diffuseTexturePath.LastIndexOf("\\");
                        if (diffuseIndex > 0)
                            diffuseOnlyName = data.meshData.diffuseTexturePath.Substring(diffuseIndex + 1);

                        MeshFilePath.Text = meshOnlyName;
                        if (ext == ".X" || ext == ".x")
                        {
                            DiffuseFilePath.Text = meshOnlyName;
                        }
                        else
                        {
                            DiffuseFilePath.Text = diffuseOnlyName;
                        }

                        MapGroupComboBox.SelectedIndex = data.mapData.group;

                        Externs.InsertGameData(ref data.gameObjectData);
                        Externs.InsertMeshData(ref data.meshData);
                        break;
                    }
                case GameObjectType.Terrain:
                    {
                        TransformData.Visibility = Visibility.Visible;
                        TerrainData.Visibility = Visibility.Visible;
                        
                        TerrainX.Text = data.terrainData.vertexCountX.ToString();
                        TerrainZ.Text = data.terrainData.vertexCountZ.ToString();
                        TerrainInterval.Text = data.terrainData.vertexInterval.ToString();

                        string diffuseOnlyName = "";
                        int diffuseIndex = data.terrainData.diffuseFilePath.LastIndexOf("\\");
                        if (diffuseIndex > 0)
                            diffuseOnlyName = data.terrainData.diffuseFilePath.Substring(diffuseIndex + 1);
                        else
                            DebugLog("Terrain DiffuseName was invalid", ELogType.Warning);

                        string normalOnlyName = "";
                        int normalIndex = data.terrainData.normalFilePath.LastIndexOf("\\");
                        if (normalIndex > 0)
                            normalOnlyName = data.terrainData.normalFilePath.Substring(normalIndex + 1);
                        else
                            DebugLog("Terrain NormalName was invalid", ELogType.Warning);


                        TerrainDiffuseFilePath.Text = diffuseOnlyName;
                        TerrainNormalFilePath.Text = normalOnlyName;

                        Externs.InsertGameData(ref data.gameObjectData);
                        Externs.InsertTerrainData(ref data.terrainData);

                        break;
                    }
                case GameObjectType.Light:
                    {
                        TransformData.Visibility = Visibility.Visible;
                        LightData.Visibility = Visibility.Visible;

                        /* LightType */
                        LightType.SelectedIndex = data.lightData.lightType;

                        /* Direction */
                        DirectionX.Text = data.lightData.direction.x.ToString();
                        DirectionY.Text = data.lightData.direction.y.ToString();
                        DirectionZ.Text = data.lightData.direction.z.ToString();

                        /* Position */
                        LightPositionX.Text = data.lightData.position.x.ToString();
                        LightPositionY.Text = data.lightData.position.y.ToString();
                        LightPositionZ.Text = data.lightData.position.z.ToString();

                        /* Ambient */
                        AmbientR.Text = data.lightData.ambient.r.ToString();
                        AmbientG.Text = data.lightData.ambient.g.ToString();
                        AmbientB.Text = data.lightData.ambient.b.ToString();
                        AmbientA.Text = data.lightData.ambient.a.ToString();

                        /* Ambient Intensity */
                        AmbientIntensitySlider.Value = data.lightData.ambientIntensity;
                        AmbientIntensityTextBox.Text = data.lightData.ambientIntensity.ToString();

                        /* Diffuse */
                        DiffuseR.Text = data.lightData.diffuse.r.ToString();
                        DiffuseG.Text = data.lightData.diffuse.g.ToString();
                        DiffuseB.Text = data.lightData.diffuse.b.ToString();
                        DiffuseA.Text = data.lightData.diffuse.a.ToString();

                        /* Diffuse Intensity */
                        DiffuseIntensitySlider.Value = data.lightData.diffuseIntensity;
                        DiffuseIntensityTextBox.Text = data.lightData.diffuseIntensity.ToString();

                        /* Specular */
                        SpecularR.Text = data.lightData.specular.r.ToString();
                        SpecularG.Text = data.lightData.specular.g.ToString();
                        SpecularB.Text = data.lightData.specular.b.ToString();
                        SpecularA.Text = data.lightData.specular.a.ToString();

                        /* Specular Intensity */
                        SpecularIntensitySlider.Value = data.lightData.specularIntensity;
                        SpecularIntensityTextBox.Text = data.lightData.specularIntensity.ToString();

                        /* Specular Power */
                        SpecularPowerSlider.Value = data.lightData.specularPower;
                        SpecularPowerTextBox.Text = data.lightData.specularPower.ToString();

                        /* Range */
                        LightRange.Text = data.lightData.range.ToString();

                        /* Cone */
                        Cone.Text = data.lightData.cone.ToString();

                        /* Constant */
                        Constant.Text = data.lightData.constant.ToString();

                        /* Linear */
                        Linear.Text = data.lightData.linear.ToString();

                        /* Quadratic */
                        Quadratic.Text = data.lightData.quadratic.ToString();

                        Externs.InsertGameData(ref data.gameObjectData);
                        Externs.InsertLightData(ref data.lightData);
                        break;
                    }
            }

        }
        private void OnInspectorTabChanged()
        {
            foreach (var item in hierarchyList)
            {
                if (item.Index == SelectedIndex)
                {
                    ShowInspector(item);
                    break;
                }
            }
           
        }
        private void PositionX_MouseDown(object sender, MouseButtonEventArgs e)
        {
            for (int i = 0; i < hierarchyList.Count; i++)
            {
                if (hierarchyList[i].Index == SelectedIndex)
                {
                    HierarchyData data = hierarchyList[i];
                    gameObjectController.PickPositionX(data);
                    return;
                }
            }
        }
        private void PositionY_MouseDown(object sender, MouseButtonEventArgs e)
        {
            for (int i = 0; i < hierarchyList.Count; i++)
            {
                if (hierarchyList[i].Index == SelectedIndex)
                {
                    HierarchyData data = hierarchyList[i];
                    gameObjectController.PickPositionY(data);
                    return;
                }
            }
        }
        private void PositionZ_MouseDown(object sender, MouseButtonEventArgs e)
        {
            for (int i = 0; i < hierarchyList.Count; i++)
            {
                if (hierarchyList[i].Index == SelectedIndex)
                {
                    HierarchyData data = hierarchyList[i];
                    gameObjectController.PickPositionZ(data);
                    return;
                }
            }
        }

        private void RotationX_MouseDown(object sender, MouseButtonEventArgs e)
        {
            for (int i = 0; i < hierarchyList.Count; i++)
            {
                if (hierarchyList[i].Index == SelectedIndex)
                {
                    HierarchyData data = hierarchyList[i];
                    gameObjectController.PickRotationX(data);
                    return;
                }
            }
        }
        private void RotationY_MouseDown(object sender, MouseButtonEventArgs e)
        {
            for (int i = 0; i < hierarchyList.Count; i++)
            {
                if (hierarchyList[i].Index == SelectedIndex)
                {
                    HierarchyData data = hierarchyList[i];
                    gameObjectController.PickRotationY(data);
                    return;
                }
            }
        }
        private void RotationZ_MouseDown(object sender, MouseButtonEventArgs e)
        {
            for (int i = 0; i < hierarchyList.Count; i++)
            {
                if (hierarchyList[i].Index == SelectedIndex)
                {
                    HierarchyData data = hierarchyList[i];
                    gameObjectController.PickRotationZ(data);
                    return;
                }
            }
        }
        private void ScaleX_MouseDown(object sender, MouseButtonEventArgs e)
        {
            for (int i = 0; i < hierarchyList.Count; i++)
            {
                if (hierarchyList[i].Index == SelectedIndex)
                {
                    HierarchyData data = hierarchyList[i];
                    gameObjectController.PickScaleX(data);
                    return;
                }
            }
        }
        private void ScaleY_MouseDown(object sender, MouseButtonEventArgs e)
        {
            for (int i = 0; i < hierarchyList.Count; i++)
            {
                if (hierarchyList[i].Index == SelectedIndex)
                {
                    HierarchyData data = hierarchyList[i];
                    gameObjectController.PickScaleY(data);
                    return;
                }
            }
        }
        private void ScaleZ_MouseDown(object sender, MouseButtonEventArgs e)
        {
            for (int i = 0; i < hierarchyList.Count; i++)
            {
                if (hierarchyList[i].Index == SelectedIndex)
                {
                    HierarchyData data = hierarchyList[i];
                    gameObjectController.PickScaleZ(data);
                    return;
                }
            }
        }

        #region Text Changed


        private void CellPositionX_TextChanged(object sender, TextChangedEventArgs e)
        {
            if (ToolManager.ToolMode != EToolMode.NavMeshTool)
                return;
            TextBox textBox = sender as TextBox;


            CellData data = default(CellData);
            ECellEditMode editMode = ECellEditMode.Similar;

            bool bFound = false;
            foreach (var cellData in selectedHierarchy.cells)
            {
                if (cellData .cellIndex == SelectedCellIndex)
                {
                    data = cellData ;
                    editMode = CellEditMode;
                    bFound = true;
                    break;
                }
            }
            Debug.Assert(bFound);

            float xPos;
            float.TryParse(textBox.Text, out xPos);

            data.position.x = xPos;

            Externs.InsertCellData(ref data, (int)editMode);
        }
        private void CellPositionY_TextChanged(object sender, TextChangedEventArgs e)
        {
            if (ToolManager.ToolMode != EToolMode.NavMeshTool)
                return;
            TextBox textBox = sender as TextBox;


            CellData data = default(CellData);
            ECellEditMode editMode = ECellEditMode.Similar;

            bool bFound = false;
            foreach (var cellData in selectedHierarchy.cells)
            {
                if (cellData .cellIndex == SelectedCellIndex)
                {
                    data = cellData ;
                    editMode = CellEditMode;
                    bFound = true;
                    break;
                }
            }
            Debug.Assert(bFound);

            float yPos;
            float.TryParse(textBox.Text, out yPos);

            data.position.y = yPos;

            Externs.InsertCellData(ref data, (int)editMode);
        }
        private void CellPositionZ_TextChanged(object sender, TextChangedEventArgs e)
        {
            if (ToolManager.ToolMode != EToolMode.NavMeshTool)
                return;
            TextBox textBox = sender as TextBox;

            CellData data = default(CellData);
            ECellEditMode editMode = ECellEditMode.Similar;

            bool bFound = false;
            foreach (var cellData in selectedHierarchy.cells)
            {
                if (cellData .cellIndex == SelectedCellIndex)
                {
                    data = cellData ;
                    editMode = CellEditMode;
                    bFound = true;
                    break;
                }
            }
            Debug.Assert(bFound);

            float zPos;
            float.TryParse(textBox.Text, out zPos);

            data.position.z = zPos;

            Externs.InsertCellData(ref data, (int)editMode);
        }

        private void PositionX_TextChanged(object sender, TextChangedEventArgs e)
        {
            TextBox textBox = sender as TextBox;

            foreach (var hierarchyItem in hierarchyList)
            {
                if (hierarchyItem.Index == SelectedIndex)
                {
                    float xPos = 0;
                    float.TryParse(textBox.Text, out xPos);
                    hierarchyItem.gameObjectData.transform.position.x = xPos;
                    GameObjectData data = hierarchyItem.gameObjectData;
                    Externs.InsertGameData(ref data);
                    break;
                }
            }
        }
        private void PositionY_TextChanged(object sender, TextChangedEventArgs e)
        {
            TextBox textBox = sender as TextBox;

            foreach (var hierarchyItem in hierarchyList)
            {
                if (hierarchyItem.Index == SelectedIndex)
                {
                    float yPos = 0;
                    float.TryParse(textBox.Text, out yPos);
                    hierarchyItem.gameObjectData.transform.position.y = yPos;
                    GameObjectData data = hierarchyItem.gameObjectData;
                    Externs.InsertGameData(ref data);
                    break;
                }
            }
        }

        private void PositionZ_TextChanged(object sender, TextChangedEventArgs e)
        {
            TextBox textBox = sender as TextBox;

            foreach (var hierarchyItem in hierarchyList)
            {
                if (hierarchyItem.Index == selectedIndex)
                {
                    float zPos = 0;
                    float.TryParse(textBox.Text, out zPos);
                    hierarchyItem.gameObjectData.transform.position.z = zPos;
                    GameObjectData data = hierarchyItem.gameObjectData;
                    Externs.InsertGameData(ref data);
                    break;
                }
            }
        }

        private void RotationX_TextChanged(object sender, TextChangedEventArgs e)
        {
            TextBox textBox = sender as TextBox;

            foreach (var hierarchyItem in hierarchyList)
            {
                if (hierarchyItem.Index == selectedIndex)
                {
                    float xRot = 0;
                    float.TryParse(textBox.Text, out xRot);
                    hierarchyItem.gameObjectData.transform.rotation.x = xRot;
                    GameObjectData data = hierarchyItem.gameObjectData;
                    Externs.InsertGameData(ref data);
                    break;
                }
            }
        }

        private void RotationY_TextChanged(object sender, TextChangedEventArgs e)
        {
            TextBox textBox = sender as TextBox;

            foreach (var hierarchyItem in hierarchyList)
            {
                if (hierarchyItem.Index == selectedIndex)
                {
                    float yRot = 0;
                    float.TryParse(textBox.Text, out yRot);
                    hierarchyItem.gameObjectData.transform.rotation.y = yRot;
                    GameObjectData data = hierarchyItem.gameObjectData;
                    Externs.InsertGameData(ref data);
                    break;
                }
            }
        }

        private void RotationZ_TextChanged(object sender, TextChangedEventArgs e)
        {
            TextBox textBox = sender as TextBox;

            foreach (var hierarchyItem in hierarchyList)
            {
                if (hierarchyItem.Index == selectedIndex)
                {
                    float zRot = 0;
                    float.TryParse(textBox.Text, out zRot);
                    hierarchyItem.gameObjectData.transform.rotation.z = zRot;
                    GameObjectData data = hierarchyItem.gameObjectData;
                    Externs.InsertGameData(ref data);
                    break;
                }
            }
        }

        private void ScaleX_TextChanged(object sender, TextChangedEventArgs e)
        {
            TextBox textBox = sender as TextBox;

            foreach (var hierarchyItem in hierarchyList)
            {
                if (hierarchyItem.Index == selectedIndex)
                {
                    float xScale = 0;
                    float.TryParse(textBox.Text, out xScale);
                    hierarchyItem.gameObjectData.transform.scale.x = xScale;
                    GameObjectData data = hierarchyItem.gameObjectData;
                    Externs.InsertGameData(ref data);
                    break;
                }
            }
        }

        private void ScaleY_TextChanged(object sender, TextChangedEventArgs e)
        {
            TextBox textBox = sender as TextBox;

            foreach (var hierarchyItem in hierarchyList)
            {
                if (hierarchyItem.Index == selectedIndex)
                {
                    float yScale = 0;
                    float.TryParse(textBox.Text, out yScale);
                    hierarchyItem.gameObjectData.transform.scale.y = yScale;
                    GameObjectData data = hierarchyItem.gameObjectData;
                    Externs.InsertGameData(ref data);
                    break;
                }
            }
        }

        private void ScaleZ_TextChanged(object sender, TextChangedEventArgs e)
        {
            TextBox textBox = sender as TextBox;

            foreach (var hierarchyItem in hierarchyList)
            {
                if (hierarchyItem.Index == selectedIndex)
                {
                    float zScale = 0;
                    float.TryParse(textBox.Text, out zScale);
                    hierarchyItem.gameObjectData.transform.scale.z = zScale;
                    GameObjectData data = hierarchyItem.gameObjectData;
                    Externs.InsertGameData(ref data);
                    break;
                }
            }
        }

        private void EditCamPositionX_TextChanged(object sender, TextChangedEventArgs e)
        {
            if (!bWindowInit)
                return;
            TextBox textBox = sender as TextBox;

            float value;
            value = float.Parse(textBox.Text);

            Vector3 editCamPos = default(Vector3);
            Externs.GetEditCameraPos(ref editCamPos);
            editCamPos.x = value;
            Externs.SetEditCameraPos(editCamPos.x, editCamPos.y, editCamPos.z); 
        }
        private void EditCamPositionY_TextChanged(object sender, TextChangedEventArgs e)
        {
            if (!bWindowInit)
                return;
            TextBox textBox = sender as TextBox;

            float value;
            value = float.Parse(textBox.Text);

            Vector3 editCamPos = default(Vector3);
            Externs.GetEditCameraPos(ref editCamPos);
            editCamPos.y = value;
            Externs.SetEditCameraPos(editCamPos.x, editCamPos.y, editCamPos.z);
        }

        private void EditCamPositionZ_TextChanged(object sender, TextChangedEventArgs e)
        {
            if (!bWindowInit)
                return;
            TextBox textBox = sender as TextBox;

            float value;
            value = float.Parse(textBox.Text);

            Vector3 editCamPos = default(Vector3);
            Externs.GetEditCameraPos(ref editCamPos);
            editCamPos.z = value;
            Externs.SetEditCameraPos(editCamPos.x, editCamPos.y, editCamPos.z);
        }
        private void EditCamRotationX_TextChanged(object sender, TextChangedEventArgs e)
        {
            if (!bWindowInit)
                return;
            TextBox textBox = sender as TextBox;

            float value;
            value = float.Parse(textBox.Text);

            Vector3 editCamRot = default(Vector3);
            Externs.GetEditCameraRot(ref editCamRot);
            editCamRot.x = value;
            Externs.SetEditCameraRot(editCamRot.x, editCamRot.y, editCamRot.z);
        }
        private void EditCamRotationY_TextChanged(object sender, TextChangedEventArgs e)
        {
            if (!bWindowInit)
                return;
            TextBox textBox = sender as TextBox;

            float value;
            value = float.Parse(textBox.Text);

            Vector3 editCamRot = default(Vector3);
            Externs.GetEditCameraRot(ref editCamRot);
            editCamRot.y = value;
            Externs.SetEditCameraRot(editCamRot.x, editCamRot.y, editCamRot.z);
        }
        private void EditCamRotationZ_TextChanged(object sender, TextChangedEventArgs e)
        {
            if (!bWindowInit)
                return;
            TextBox textBox = sender as TextBox;

            float value;
            value = float.Parse(textBox.Text);

            Vector3 editCamRot = default(Vector3);
            Externs.GetEditCameraRot(ref editCamRot);
            editCamRot.z = value;
            Externs.SetEditCameraRot(editCamRot.x, editCamRot.y, editCamRot.z);
        }
        private void EditCamMoveSpeed_TextChanged(object sender, TextChangedEventArgs e)
        {
            if (!bWindowInit)
                return;
            TextBox textBox = sender as TextBox;

            float value;
            value = float.Parse(textBox.Text);

            cameraController.SetMoveSpeed(value);
        }
        private void GameObjectName_TextChanged(object sender, TextChangedEventArgs e)
        {
            if (!bWindowInit)
                return;
            TextBox textBox = sender as TextBox;
            for (int i = 0; i < hierarchyList.Count; i++)
            {
                if (hierarchyList[i].Index == selectedIndex)
                {
                    HierarchyData data = hierarchyList[i];
                    data.gameObjectData.name = textBox.Text;
                    hierarchyList[i] = data;
                    ListBoxItem item = (ListBoxItem)HierarchyList.Items.GetItemAt(i);
                    item.Content = textBox.Text;
                    Externs.InsertGameData(ref data.gameObjectData);
                    break;
                }
            }
        }
        private void MeshFile_TextChanged(object sender, TextChangedEventArgs e)
        {
            if (!bWindowInit)
                return;
            TextBox textBox = sender as TextBox;
            for (int i = 0; i < hierarchyList.Count; i++)
            {
                if (hierarchyList[i].Index == selectedIndex)
                {
                    HierarchyData data = hierarchyList[i];
                    data.meshData.meshFilePath = textBox.Text;
                    hierarchyList[i] = data;
                    Externs.InsertMeshData(ref data.meshData);
                    break;
                }
            }
        }
        private void DiffuseFile_TextChanged(object sender, TextChangedEventArgs e)
        {
            if (!bWindowInit)
                return;
            TextBox textBox = sender as TextBox;
            for (int i = 0; i < hierarchyList.Count; i++)
            {
                if (hierarchyList[i].Index == selectedIndex)
                {
                    HierarchyData data = hierarchyList[i];
                    data.meshData.diffuseTexturePath = textBox.Text;
                    hierarchyList[i] = data;
                    Externs.InsertMeshData(ref data.meshData);
                    break;
                }
            }
        }
        private void TerrainX_TextChanged(object sender, TextChangedEventArgs e)
        {
            if (!bWindowInit)
                return;
            TextBox item = sender as TextBox;
            selectedHierarchy.terrainData.vertexCountX = UInt32.Parse( item.Text);
            Externs.InsertTerrainData(ref selectedHierarchy.terrainData);
        }
        private void TerrainZ_TextChanged(object sender, TextChangedEventArgs e)
        {
            if (!bWindowInit)
                return;
            TextBox item = sender as TextBox;
            selectedHierarchy.terrainData.vertexCountZ = UInt32.Parse(item.Text);
            Externs.InsertTerrainData(ref selectedHierarchy.terrainData);
        }
        private void TerrainTextureX_TextChanged(object sender, TextChangedEventArgs e)
        {
            if (!bWindowInit)
                return;
            TextBox item = sender as TextBox;
            selectedHierarchy.terrainData.textureCountX = UInt32.Parse(item.Text);
            Externs.InsertTerrainData(ref selectedHierarchy.terrainData);
        }
        private void TerrainTextureZ_TextChanged(object sender, TextChangedEventArgs e)
        {
            if (!bWindowInit)
                return;
            TextBox item = sender as TextBox;
            selectedHierarchy.terrainData.textureCountZ = UInt32.Parse(item.Text);
            Externs.InsertTerrainData(ref selectedHierarchy.terrainData);
        }
        private void TerrainInterval_TextChanged(object sender, TextChangedEventArgs e)
        {
            if (!bWindowInit)
                return;
            TextBox item = sender as TextBox;
            float result;
            bool bSuccess = float.TryParse(item.Text, out result);
            if (bSuccess)
                selectedHierarchy.terrainData.vertexInterval = result;
            Externs.InsertTerrainData(ref selectedHierarchy.terrainData);
        }
        #endregion TextChanged

    }
}
