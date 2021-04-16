﻿using System;
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
    /// <summary>
    /// Interaction logic for MainWindow.xaml
    /// </summary>
    public partial class MainWindow : Window
    {
        public MainWindow()
        {
            InitializeComponent();
            InitializeWindow();

        }
        ~MainWindow()
        {
            Externs.Destroy();
        }
        void Update_Tick(object sender, EventArgs e)
        {
            if (bLateInit == false)
                LateInitialize();
            frameRateCalculator.Tick();
            EditorFrame.Text = frameRateCalculator.GetFrameRate().ToString();
            float elapsedTime = (float)frameRateCalculator.GetElapsedTime().Milliseconds / 1000;
            Timer.DeltaTime = elapsedTime;

            DxActualWidth = imgelt.ActualWidth;
            DxActualHeight = imgelt.ActualHeight;
            DxScreenSizeX.Text = DxActualWidth.ToString("N3");
            DxScreenSizeY.Text = DxActualHeight.ToString("N3");

            Point pointToWindow = Mouse.GetPosition(this);
            EditorMousePosX.Text = pointToWindow.X.ToString("N3");
            EditorMousePosY.Text = pointToWindow.Y.ToString("N3");

            cameraController.Update(elapsedTime);

            switch(ToolManager.ToolMode)
            {
                case EToolMode.HandTool:
                    HandToolButton.IsChecked = true;
                    ViewToolButton.IsChecked = false;
                    NavMeshToolButton.IsChecked = false;
                    PickToolButton.IsChecked = false;
                    break;
                case EToolMode.ViewTool:
                    HandToolButton.IsChecked = false;
                    ViewToolButton.IsChecked = true;
                    NavMeshToolButton.IsChecked = false;
                    PickToolButton.IsChecked = false;
                    break;
                case EToolMode.NavMeshTool:
                    HandToolButton.IsChecked = false;
                    ViewToolButton.IsChecked = false;
                    NavMeshToolButton.IsChecked = true;
                    PickToolButton.IsChecked = false;
                    break;
                case EToolMode.PickTool:
                    HandToolButton.IsChecked = false;
                    ViewToolButton.IsChecked = false;
                    NavMeshToolButton.IsChecked = false;
                    PickToolButton.IsChecked = true;
                    break;
            }
            

            Vector3 editCamPos = default(Vector3);
            Externs.GetEditCameraPos(ref editCamPos);
            Vector3 editCamRot = default(Vector3);
            Externs.GetEditCameraRot(ref editCamRot);
            EditCamPositionX.Text = editCamPos.x.ToString("N3");
            EditCamPositionY.Text = editCamPos.y.ToString("N3");
            EditCamPositionZ.Text = editCamPos.z.ToString("N3");
            EditCamRotationX.Text = editCamRot.x.ToString("N3");
            EditCamRotationY.Text = editCamRot.y.ToString("N3");
            EditCamRotationZ.Text = editCamRot.z.ToString("N3");

            TEXTBOX_EditCamSpeed.Text = cameraController.GetMoveSpeed().ToString("N3");
            if (GameMode == false && bUpdate == true)
                Externs.Update();
            else if(GameMode == true)
                Externs.Update();
        }
        void CompositionTarget_Rendering(object sender, EventArgs e)
        {
            RenderingEventArgs args = (RenderingEventArgs)e;

            /* SceneMode */
            if (GameMode == false && bRender == true)
            {
                // It's possible for Rendering to call back twice in the same frame 
                // so only render when we haven't already rendered in this frame.
                if (d3dimg.IsFrontBufferAvailable && _lastRender != args.RenderingTime)
                {
                    IntPtr pSurface = IntPtr.Zero;
                    Externs.GetBackBuffer(out pSurface);
                    if (pSurface != IntPtr.Zero)
                    {
                        d3dimg.Lock();
                        // Repeatedly calling SetBackBuffer with the same IntPtr is 
                        // a no-op. There is no performance penalty.
                        d3dimg.SetBackBuffer(D3DResourceType.IDirect3DSurface9, pSurface);
                        Externs.Render();
                        d3dimg.AddDirtyRect(new Int32Rect(0, 0, d3dimg.PixelWidth, d3dimg.PixelHeight));
                        d3dimg.Unlock();

                        _lastRender = args.RenderingTime;
                    }
                }
                bRender = false;
            }


            /* Game Mode */
            if (GameMode == true)
            {
                // It's possible for Rendering to call back twice in the same frame 
                // so only render when we haven't already rendered in this frame.
                if (d3dimg_Game.IsFrontBufferAvailable && _lastRender != args.RenderingTime)
                {
                    IntPtr pSurface = IntPtr.Zero;
                    Externs.GetBackBuffer(out pSurface);
                    if (pSurface != IntPtr.Zero)
                    {
                        d3dimg_Game.Lock();
                        // Repeatedly calling SetBackBuffer with the same IntPtr is 
                        // a no-op. There is no performance penalty.
                        d3dimg_Game.SetBackBuffer(D3DResourceType.IDirect3DSurface9, pSurface);
                        Externs.Render();
                        d3dimg_Game.AddDirtyRect(new Int32Rect(0, 0, d3dimg_Game.PixelWidth, d3dimg_Game.PixelHeight));
                        d3dimg_Game.Unlock();

                        _lastRender = args.RenderingTime;
                    }
                }
            }
        }
        void Scene_Rendering()
        {
            IntPtr pSurface = IntPtr.Zero;
            Externs.GetBackBuffer(out pSurface);
            if (pSurface != IntPtr.Zero)
            {
                d3dimg.Lock();
                // Repeatedly calling SetBackBuffer with the same IntPtr is 
                // a no-op. There is no performance penalty.
                d3dimg.SetBackBuffer(D3DResourceType.IDirect3DSurface9, pSurface);
                Externs.Render();
                d3dimg.AddDirtyRect(new Int32Rect(0, 0, d3dimg.PixelWidth, d3dimg.PixelHeight));
                d3dimg.Unlock();

            }

        }

        TimeSpan _lastRender;
        double DxActualWidth;
        double DxActualHeight;
        string toolFolderName = "WPF_Tool";
        //string ResourcePath;
        // string MeshPath;
        //string TexturePath;


        //Dictionary<string, BitmapSource> textureImages;
        
         
        void ValueChangeEvent()
        {
            ValueChanged = true;
        }


        void UnHandledException(object sender, UnhandledExceptionEventArgs args)
        {
            Exception e = (Exception)args.ExceptionObject;
            DebugLog(e.Message, ELogType.Error);
        }

        public void OnKeyDown(object sender, KeyEventArgs e)
        {
            switch (e.Key)
            {
                case Key.Delete:
                    if (selectedIndex == -1) return;

                    int index = 0;
                    foreach (var hierarchyItem in hierarchyList)
                    {
                        if (hierarchyItem.Index == SelectedIndex)
                        {
                            SelectedIndex = -1;
                            hierarchyList.Remove(hierarchyItem);
                            HierarchyList.Items.RemoveAt(index);
                            Externs.RemoveGameObject(hierarchyItem.Index);

                            if(hierarchyItem.type == GameObjectType.NavMesh)
                                RefreshAll();
                            break;
                        }
                        index++;
                    }
                    break;
            }
        }


        void RefreshAll()
        {
            CellList.Items.Clear();

        }

        List<HierarchyData> hierarchyList = new List<HierarchyData>();
        List<MeshData> meshDatas = new List<MeshData>();

        private bool gameMode = false;
        public bool GameMode
        {
            set;
            get;
        }
        /*  Scene 상태에서는 값이 바뀔때만 Render와 Update를 해준다. */ 
        bool bRender = false;
        bool bUpdate = false;
        private bool valueChanged = false;
        public bool ValueChanged
        {
            set
            {
                valueChanged = value;
                if (value == true)
                {
                    bRender = true;
                    bUpdate = true;
                    //Scene_Rendering();
                    valueChanged = false;
                }
            }
            get { return valueChanged; }
        }
        bool isSelecting = false;
        int gameObjectIndex = 0;
        IInputElement lastFocusedElement;
        HierarchyData selectedHierarchy;
        private int selectedIndex = -1;
        public int SelectedIndex
        {
            set
            {
                isSelecting = true;
                selectedIndex = value;
                Externs.SelectEditObject(selectedIndex);
                foreach (var item in HierarchyList.Items)
                {
                    ListBoxItem listBoxItem = item as ListBoxItem;
                    if (selectedIndex.ToString() == listBoxItem.Uid)
                    {
                        listBoxItem.IsSelected = true;

                        foreach (var data in hierarchyList)
                        {
                            if (selectedIndex == data.Index)
                            {
                                selectedHierarchy = data;
                                ShowInspector(data);
                                if (data.type == GameObjectType.NavMesh)
                                {
                                    InspectorTab.SelectedIndex = 1;
                                    ToolManager.ToolMode = EToolMode.NavMeshTool;
                                    OnInspectorTabChanged();
                                }
                                else
                                {
                                    InspectorTab.SelectedIndex = 0;
                                    ToolManager.ToolMode = EToolMode.ViewTool;
                                    OnInspectorTabChanged();
                                }
                                break;
                            }
                        }
                        break;
                    }
                }
                isSelecting = false;
            }
            get
            {
                return selectedIndex;
            }
        }
        public int SelectedNewIndex
        {
            set
            {
                selectedIndex = value;
                Externs.SelectEditObject(selectedIndex);
                foreach (var item in HierarchyList.Items)
                {
                    ListBoxItem listBoxItem = item as ListBoxItem;
                    if (selectedIndex.ToString() == listBoxItem.Uid)
                    {
                        listBoxItem.IsSelected = true;

                        foreach (var data in hierarchyList)
                        {
                            if (selectedIndex == data.Index)
                            {
                                selectedHierarchy = data;
                                ShowInspector(data);
                                if (data.type == GameObjectType.NavMesh)
                                {
                                    InspectorTab.SelectedIndex = 1;
                                    ToolManager.ToolMode = EToolMode.NavMeshTool;
                                    OnInspectorTabChanged();
                                }
                                else
                                {
                                    InspectorTab.SelectedIndex = 0;
                                    ToolManager.ToolMode = EToolMode.ViewTool;
                                    OnInspectorTabChanged();
                                }
                                break;
                            }
                        }
                        break;
                    }
                }
            }
            get
            {
                return selectedIndex;
            }
        }









        private void ObjectTag_Selected(object sender, RoutedEventArgs e)
        {

        }

        private void SceneTab_Selected(object sender, RoutedEventArgs e)
        {
           
        }

        private void SceneTab_SelectionChanged(object sender, SelectionChangedEventArgs e)
        {
            TabControl tabControl = sender as TabControl;

            /* Scene = 0, Game = 1 */
            if (tabControl.SelectedIndex == 0)
                GameMode = false;
            else if (tabControl.SelectedIndex == 1)
                GameMode = true;
        }
    }
}
