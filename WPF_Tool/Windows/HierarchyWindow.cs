
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
       
        private void BTN_CreateMesh(object sender, RoutedEventArgs e)
        {
            ListBoxItem item = new ListBoxItem();
            // item.Name = "GameObject" + gameObjectIndex;
            item.Uid = gameObjectIndex.ToString();
            item.Content = HierarchyContent.GameObject;
            item.Tag = HierarchyTag.GameObject;
            item.MouseUp += SelectedGameObject;
            HierarchyList.Items.Add(item);
            HierarchyList.SelectionMode = SelectionMode.Single;
            int index = gameObjectIndex; // temp
            HierarchyData data = new HierarchyData();
            data.Index = index;
            data.type = GameObjectType.Mesh;
            data.gameObjectData = new GameObjectData(index, HierarchyContent.GameObject);
            // data.gameObjectData.tag = ;
            data.gameObjectData.tag = Strings.Tags[ObjectTag.SelectedIndex];
            data.gameObjectData.layer = ObjectLayer.SelectedIndex;
            data.gameObjectData.staticType = ObjectStatic.SelectedIndex;
            data.meshData = new MeshData(index);
            gameObjectIndex++;
            hierarchyList.Add(data);
            Externs.AddGameObject(index);
        }
        private void BTN_CreateNavMesh(object sender, RoutedEventArgs e)
        {
            ListBoxItem item = new ListBoxItem();
            // item.Name = "GameObject" + gameObjectIndex;
            item.Uid = gameObjectIndex.ToString();
            item.Content = HierarchyContent.NavMesh;
            item.Tag = HierarchyTag.NavMesh;
            item.MouseUp += SelectedNavMesh;
            HierarchyList.Items.Add(item);
            HierarchyList.SelectionMode = SelectionMode.Single;
            int index = gameObjectIndex; // temp
            HierarchyData data = new HierarchyData();
            data.Index = index;
            data.type = GameObjectType.NavMesh;
            data.tagIndex = ObjectTag.SelectedIndex;
            data.layerIndex = ObjectLayer.SelectedIndex;
            data.staticIndex = ObjectStatic.SelectedIndex;
            data.gameObjectData = new GameObjectData(index, HierarchyContent.NavMesh);
            data.gameObjectData.tag = Strings.Tags[ObjectTag.SelectedIndex];
            data.gameObjectData.layer = ObjectLayer.SelectedIndex;
            data.gameObjectData.staticType = ObjectStatic.SelectedIndex;
            data.meshData = default(MeshData);
            gameObjectIndex++;
            hierarchyList.Add(data);
            Externs.AddNavMesh(index);
        }
        private void BTN_CreateMapObject(object sender, RoutedEventArgs e)
        {
            ListBoxItem item = new ListBoxItem();
            // item.Name = "GameObject" + gameObjectIndex;
            item.Uid = gameObjectIndex.ToString();
            item.Content = HierarchyContent.MapObject;
            item.Tag = HierarchyTag.MapObject;
            item.MouseUp += SelectedGameObject;
            HierarchyList.Items.Add(item);
            HierarchyList.SelectionMode = SelectionMode.Single;
            int index = gameObjectIndex; // temp
            HierarchyData data = new HierarchyData();
            data.Index = index;
            data.type = GameObjectType.MapObject;
            data.gameObjectData = new GameObjectData(index, HierarchyContent.GameObject);

            data.gameObjectData.tag = Strings.Tags[ObjectTag.SelectedIndex];
            data.gameObjectData.layer = ObjectLayer.SelectedIndex;
            data.gameObjectData.staticType = ObjectStatic.SelectedIndex;
            data.meshData = new MeshData(index);
            data.mapData = new MapData(index);
            gameObjectIndex++;
            hierarchyList.Add(data);
            Externs.AddGameObject(index);
        }

        private void SelectedGameObject(object sender, RoutedEventArgs e)
        {
            ListBoxItem item = sender as ListBoxItem;
            foreach (var hierarchyItem in hierarchyList)
            {
                if (hierarchyItem.Index.ToString() == item.Uid.ToString())
                {
                    selectedIndex = hierarchyItem.Index;
                    Externs.SelectEditObject(hierarchyItem.Index);

                    ShowInspector(hierarchyItem);


                    // default
                    // 만약 navmesh 상태에서 일반 오브젝트를 클릭하면
                    // 원상복귀되어야한다.
                    ToolManager.ToolMode = EToolMode.HandTool;

                    break;
                }
            }

        }
        private void SelectedNavMesh(object sender, RoutedEventArgs e)
        {
            ListBoxItem item = sender as ListBoxItem;
            foreach (var hierarchyItem in hierarchyList)
            {
                if (hierarchyItem.Index.ToString() == item.Uid.ToString())
                {
                    selectedIndex = hierarchyItem.Index;
                    Externs.SelectEditObject(hierarchyItem.Index);

                    ShowInspector(hierarchyItem);

                    

                    // 여기부터 navMesh tap
                    // 강제로 탭 변경을 한다.
                    InspectorTab.SelectedIndex = 1;
                    ToolManager.ToolMode = EToolMode.NavMeshTool;



                    break;
                }
            }

        }
    }
}
