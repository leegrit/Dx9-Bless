
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
            CreateHierarchy(GameObjectType.Mesh);
        }
        private void BTN_CreateNavMesh(object sender, RoutedEventArgs e)
        {
            foreach (var item in hierarchyList)
            {
                if (item.type == GameObjectType.NavMesh)
                {
                    return;
                }
            }
            CreateHierarchy(GameObjectType.NavMesh);
        }
        private void BTN_CreateMapObject(object sender, RoutedEventArgs e)
        {
            CreateHierarchy(GameObjectType.MapObject);
        }

        private void CreateHierarchy(GameObjectType gameObjectType)
        {
            ListBoxItem item = new ListBoxItem();
            // item.Name = "GameObject" + gameObjectIndex;
            int index = gameObjectIndex++; // temp
            item.Uid = index.ToString();
            switch (gameObjectType)
            {
                case GameObjectType.Mesh:
                    item.Content = HierarchyContent.GameObject;
                    item.Tag = HierarchyTag.GameObject;
                    break;
                case GameObjectType.MapObject:
                    item.Content = HierarchyContent.MapObject;
                    item.Tag = HierarchyTag.MapObject;
                    break;
                case GameObjectType.NavMesh:
                    item.Content = HierarchyContent.NavMesh;
                    item.Tag = HierarchyTag.NavMesh;
                    break;
            }


            switch (gameObjectType)
            {
                case GameObjectType.Mesh:
                    item.MouseUp += SelectedGameObject;
                    break;
                case GameObjectType.NavMesh:
                    item.MouseUp += SelectedNavMesh;
                    break;
                case GameObjectType.MapObject:
                    item.MouseUp += SelectedGameObject;
                    break;

            }
            


            item.MouseDoubleClick += DoubleClickGameObject;
            HierarchyList.Items.Add(item);
            HierarchyList.SelectionMode = SelectionMode.Single;
           
            HierarchyData data = new HierarchyData();
            data.Index = index;
            data.type = gameObjectType;

            data.gameObjectData = new GameObjectData(index, item.Content.ToString());
            data.gameObjectData.tag = Strings.Tags[ObjectTag.SelectedIndex];
            data.gameObjectData.layer = ObjectLayer.SelectedIndex;
            data.gameObjectData.staticType = ObjectStatic.SelectedIndex;


            data.meshData = new MeshData(index);
            data.mapData = new MapData(index);
            data.navMeshData = new NavMeshData(index);
            hierarchyList.Add(data);

            switch (gameObjectType)
            {
                case GameObjectType.Mesh:
                    Externs.AddGameObject(index);
                    break;
                case GameObjectType.NavMesh:
                    data.cells = new List<Data.CellData>();
                    Externs.AddNavMesh(index);
                    break;
                case GameObjectType.MapObject:
                    Externs.AddGameObject(index);
                    break;

            }
         
            SelectedIndex = index;
        }

        private void AddHierarchy(HierarchyData hierarchyData)
        {
            // 여기서 값을 넣으면 정상적으로 hierarchy에 추가해준다.
            // TODO
            int index = gameObjectIndex++;
            ListBoxItem item = new ListBoxItem();
            item.Uid = index.ToString();
            item.Content = hierarchyData.gameObjectData.name;
            item.Tag = hierarchyData.gameObjectData.tag;
            hierarchyData.Index = index;
            switch (hierarchyData.type)
            {
                case GameObjectType.Mesh:
                    item.MouseUp += SelectedGameObject;
                    break;
                case GameObjectType.NavMesh:
                    item.MouseUp += SelectedNavMesh;
                    break;
                case GameObjectType.MapObject:
                    item.MouseUp += SelectedGameObject;
                    break;
                default:
                    Debug.Assert(false);
                    break;
            }
            item.MouseDoubleClick += DoubleClickGameObject;

            HierarchyList.Items.Add(item);
            HierarchyList.SelectionMode = SelectionMode.Single;
            hierarchyList.Add(hierarchyData);
            switch (hierarchyData.type)
            {
                case GameObjectType.Mesh:
                    Externs.AddGameObject(index);
                    break;
                case GameObjectType.NavMesh:
                    Externs.AddNavMesh(index);
                    break;
                case GameObjectType.MapObject:
                    Externs.AddGameObject(index);
                    break;
                default:
                    Debug.Assert(false);
                    break;
            }
            // SelectedIndex Property에서 Select, ShowInspector, InsertData 모두 해준다.
            SelectedIndex = index;

            for (int i = 0; i < hierarchyData.navMeshData.cellCount; i++)
            {
                Debug.Assert(hierarchyData.type == GameObjectType.NavMesh);

                CellData cellData = hierarchyData.cells[i];
                Externs.AddCell(ref cellData);

                Vector3 position;
                position = hierarchyData.cells[i].position;

                bool isNewPrim = IsNewPrimitive();
                if (isNewPrim)
                {
                    TreeViewItem primItem = new TreeViewItem();
                    primItem.Header = "NavPrimitive_" + NavPrimIndex.ToString();
                    primItem.Uid = NavPrimIndex.ToString();
                    primItem.Selected += NavPrimSelected;
                    NavPrimIndex++;

                    CellList.Items.Add(primItem);
                }
                TreeViewItem cellItem = new TreeViewItem();
                cellItem.Header = "Cell_" + cellIndex;
                cellItem.Uid = cellIndex.ToString();
                cellItem.Selected += CellSelected;
                AddCell(position);

                int primCount = CellList.Items.Count;
                ((TreeViewItem)CellList.Items[primCount - 1]).Items.Add(cellItem);
               
                
            }




        }
        private void SelectedGameObject(object sender, RoutedEventArgs e)
        {
            ListBoxItem item = sender as ListBoxItem;
            foreach (var hierarchyItem in hierarchyList)
            {
                if (hierarchyItem.Index.ToString() == item.Uid.ToString())
                {
                    SelectedIndex = hierarchyItem.Index;


                    // default
                    // 만약 navmesh 상태에서 일반 오브젝트를 클릭하면
                    // 원상복귀되어야한다.
                    ToolManager.ToolMode = EToolMode.HandTool;

                    break;
                }
            }
        }
        private void DoubleClickGameObject(object sender, RoutedEventArgs e)
        {
            Externs.TranslateToMesh();
        }
        private void SelectedNavMesh(object sender, RoutedEventArgs e)
        {
            ListBoxItem item = sender as ListBoxItem;
            foreach (var hierarchyItem in hierarchyList)
            {
                if (hierarchyItem.Index.ToString() == item.Uid.ToString())
                {
                    SelectedIndex = hierarchyItem.Index;


                    

                    // 여기부터 navMesh tap
                    // 강제로 탭 변경을 한다.
                    InspectorTab.SelectedIndex = 1;
                    ToolManager.ToolMode = EToolMode.NavMeshTool;
                    OnInspectorTabChanged();


                    break;
                }
            }

        }
    }
}
