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
        // ---------------------------------------------------------------------------------------------
        // EXPORTS
        // --------------------------------------------------------------------------------------------

        private void BTN_ExportHierarchy(object sender, RoutedEventArgs e)
        {
            if (selectedIndex == -1) return;

            bool result;
            string fileName = "";
            result = JsonHelper.Write(selectedHierarchy, ref fileName);
            if (result)
            {
                MessageBox.Show("Hierarchy 정보 저장에 성공했습니다.\n FileName : " + fileName, "Hierarchy Save 성공");
            }

            return;
        }

        private void BTN_ExportMapData(object sender, RoutedEventArgs e)
        {
            if (selectedIndex == -1) return;

            HierarchyData selectedData = new HierarchyData();
            bool bFind = false;
            foreach (var hierarchyData in hierarchyList)
            {
                if (hierarchyData.Index == SelectedIndex)
                {
                    selectedData = hierarchyData;
                    bFind = true;
                    break;
                }
            }
            Debug.Assert(bFind);
            if (selectedData.type != GameObjectType.MapObject)
                return;

            ChunkMapData data = new ChunkMapData();
            data.maps = new List<HierarchyData>();

            // 현재 선택된 오브젝트의 group을 찾는다.
            foreach (var hierarchyItem in hierarchyList)
            {
                if (hierarchyItem.Index == selectedIndex)
                {
                    data.group = hierarchyItem.mapData.group;
                }
            }

            foreach (var hierarchyItem in hierarchyList)
            {
                if (hierarchyItem.type == GameObjectType.MapObject)
                {
                    if (hierarchyItem.mapData.group == data.group)
                    {
                        data.maps.Add(hierarchyItem);
                    }
                }
            }
            data.mapCount = data.maps.Count;

            // chunk map data 구성 끝

            string fileName = default(string);
            bool result;
            result = JsonHelper.Write(data, ref fileName);
            if (result)
            {
                MessageBox.Show("Hierarchy 정보 저장에 성공했습니다.\n FileName : " + fileName, "MapData Save 성공");
            }

            return;



        }

        private void BTN_ExportNavMesh(object sender, RoutedEventArgs e)
        {
            if (SelectedIndex == -1) return;
            

            if (selectedHierarchy.type != GameObjectType.NavMesh)
                return;

            string fileName = default(string);
            bool result;
            result = JsonHelper.Write(selectedHierarchy, ref fileName);
            if (result)
            {
                MessageBox.Show("NavMesh 정보 저장에 성공했습니다.\n FileName : " + fileName, "NavMesh Save 성공");
            }

            return;


        }

        private void BTN_ExportScene(object sender, RoutedEventArgs e)
        {
            if (hierarchyList.Count == 0) return;

            bool result;
            string fileName = "";
            result = JsonHelper.Write(hierarchyList, ref fileName);
            if (result)
            {
                MessageBox.Show("Hierarchy 정보 저장에 성공했습니다.\n FileName : " + fileName, "Hierarchy Save 성공");
            }
        }
        // ---------------------------------------------------------------------------------------------
        // IMPORTS
        // --------------------------------------------------------------------------------------------
        private void BTN_ImportHierarchy(object sender, RoutedEventArgs e)
        {
            OpenFileDialog ofdlg = new OpenFileDialog();
            {

                ofdlg.InitialDirectory = Paths.HierarchyDataPath;
                ofdlg.CheckFileExists = true; // 파일 존재여부 확인
                ofdlg.CheckPathExists = true; // 폴더 존재여부 확인

                // 파일 열기(값의 유무 확인)
                if (ofdlg.ShowDialog().GetValueOrDefault())
                {
                    int lastIndex = ofdlg.FileName.LastIndexOf("\\");
                    string text = ofdlg.FileName.Substring(lastIndex + 1);
                    int extIndex = text.LastIndexOf(".");
                    string ext = text.Substring(extIndex);

                    if (ext != ".json")
                    {
                        // 실패 / 잘못된 포맷
                        MessageBox.Show("Load에 실패했습니다. 잘못된 format입니다. \n선택한 파일 : " + text, "HierarchyData Load Failed");
                        DebugLog("HierarchyLoadFailed : " + text, ELogType.Warning);
                        return;
                    }

                    HierarchyData hierarchyData = new HierarchyData();

                    bool result = JsonHelper.Read(ref hierarchyData, text);
                    if (result == false)
                    {
                        MessageBox.Show("Load에 실패했습니다.\n선택한 파일 :  " + text, "HierarchyData Load Failed");
                        DebugLog("HierarchyLoadFailed : " + text, ELogType.Warning);
                        return;
                    }

                    AddHierarchy(hierarchyData);
                    
                    return;
                }
            }
        }

        private void BTN_ImportMapData(object sender, RoutedEventArgs e)
        {
            OpenFileDialog ofdlg = new OpenFileDialog();
            {

                ofdlg.InitialDirectory = Paths.MapDataPath;
                ofdlg.CheckFileExists = true; // 파일 존재여부 확인
                ofdlg.CheckPathExists = true; // 폴더 존재여부 확인

                // 파일 열기(값의 유무 확인)
                if (ofdlg.ShowDialog().GetValueOrDefault())
                {
                    int lastIndex = ofdlg.FileName.LastIndexOf("\\");
                    string text = ofdlg.FileName.Substring(lastIndex + 1);
                    int extIndex = text.LastIndexOf(".");
                    string ext = text.Substring(extIndex);

                    if (ext != ".json")
                    {
                        // 실패 / 잘못된 포맷
                        MessageBox.Show("Load에 실패했습니다. 잘못된 format입니다. \n선택한 파일 : " + text, "HierarchyData Load Failed");
                        DebugLog("HierarchyLoadFailed : " + text, ELogType.Warning);
                        return;
                    }

                    ChunkMapData chunkMapData = new ChunkMapData();

                    bool result = JsonHelper.Read(ref chunkMapData, text);
                    if (result == false)
                    {
                        MessageBox.Show("Load에 실패했습니다.\n선택한 파일 :  " + text, "HierarchyData Load Failed");
                        DebugLog("HierarchyLoadFailed : " + text, ELogType.Warning);
                        return;
                    }

                    for (int i = 0; i < chunkMapData.mapCount; i++)
                    {

                        AddHierarchy(chunkMapData.maps[i]);
                    }
                    SelectedIndex = chunkMapData.maps[0].Index;
                   // Externs.SelectEditObject(SelectedIndex);

                    //ShowInspector(chunkMapData.maps[0]);



                    return;
                }
            }
        }

        private void BTN_ImportNavMesh(object sender, RoutedEventArgs e)
        {
            OpenFileDialog ofdlg = new OpenFileDialog();
            {

                ofdlg.InitialDirectory = Paths.NavMeshData;
                ofdlg.CheckFileExists = true; // 파일 존재여부 확인
                ofdlg.CheckPathExists = true; // 폴더 존재여부 확인

                // 파일 열기(값의 유무 확인)
                if (ofdlg.ShowDialog().GetValueOrDefault())
                {
                    int lastIndex = ofdlg.FileName.LastIndexOf("\\");
                    string text = ofdlg.FileName.Substring(lastIndex + 1);
                    int extIndex = text.LastIndexOf(".");
                    string ext = text.Substring(extIndex);

                    if (ext != ".json")
                    {
                        // 실패 / 잘못된 포맷
                        MessageBox.Show("Load에 실패했습니다. 잘못된 format입니다. \n선택한 파일 : " + text, "HierarchyData Load Failed");
                        DebugLog("HierarchyLoadFailed : " + text, ELogType.Warning);
                        return;
                    }

                    HierarchyData hierarchyData = new HierarchyData();
                    bool result = JsonHelper.Read(ref hierarchyData, text, EDataType.NavMesh);
                    if (result == false)
                    {
                        MessageBox.Show("Load에 실패했습니다.\n선택한 파일 :  " + text, "HierarchyData Load Failed");
                        DebugLog("HierarchyLoadFailed : " + text, ELogType.Warning);
                        return;
                    }

                    AddHierarchy(hierarchyData);
                    

                    return;
                }
            }
        }

        private void BTN_ImportScene(object sender, RoutedEventArgs e)
        {
            OpenFileDialog ofdlg = new OpenFileDialog();
            {

                ofdlg.InitialDirectory = Paths.SceneDataPath;
                ofdlg.CheckFileExists = true; // 파일 존재여부 확인
                ofdlg.CheckPathExists = true; // 폴더 존재여부 확인

                // 파일 열기(값의 유무 확인)
                if (ofdlg.ShowDialog().GetValueOrDefault())
                {
                    int lastIndex = ofdlg.FileName.LastIndexOf("\\");
                    string text = ofdlg.FileName.Substring(lastIndex + 1);
                    int extIndex = text.LastIndexOf(".");
                    string ext = text.Substring(extIndex);

                    if (ext != ".json")
                    {
                        // 실패 / 잘못된 포맷
                        MessageBox.Show("Load에 실패했습니다. 잘못된 format입니다. \n선택한 파일 : " + text, "HierarchyData Load Failed");
                        DebugLog("HierarchyLoadFailed : " + text, ELogType.Warning);
                        return;
                    }

                    List<HierarchyData> hierarchyDatas = new List<HierarchyData>();

                    bool result = JsonHelper.Read(ref hierarchyDatas, text);
                    if (result == false)
                    {
                        MessageBox.Show("Load에 실패했습니다.\n선택한 파일 :  " + text, "HierarchyData Load Failed");
                        DebugLog("HierarchyLoadFailed : " + text, ELogType.Warning);
                        return;
                    }

                    for (int i = 0; i < hierarchyDatas.Count; i++)
                    {
                        AddHierarchy(hierarchyDatas[i]);
                    }
                    
                    return;
                }
            }
        }
    }
}
