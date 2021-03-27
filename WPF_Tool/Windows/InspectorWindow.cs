
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
                //ofdlg.InitialDirectory = @"..\..\..\_Resources\Mesh";// "../../../_Resources/Mesh";
                // ofdlg.InitialDirectory = System.IO.Path.Combine(
                //    System.IO.Path.GetDirectoryName(AppDomain.CurrentDomain.BaseDirectory), "..\\..\\..\\_Resources\\Mesh\\");
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

        private void ShowInspector(HierarchyData data)
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
                case GameObjectType.NavMesh:

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
            }

        }
    }
}
