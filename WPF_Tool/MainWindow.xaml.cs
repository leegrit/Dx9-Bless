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
    /// <summary>
    /// Interaction logic for MainWindow.xaml
    /// </summary>
    public partial class MainWindow : Window
    {
        public MainWindow()
        {
            InitializeComponent();

            AppDomain currentDomain = AppDomain.CurrentDomain;
            currentDomain.UnhandledException += new UnhandledExceptionEventHandler(UnHandledException);

            Externs.Initialize();
            CompositionTarget.Rendering += new EventHandler(CompositionTarget_Rendering);
            CompositionTarget.Rendering += new EventHandler(Update_Tick);
            //  _updateTimer = new DispatcherTimer();
            //  _updateTimer.Tick += new EventHandler(Update_Tick);
            ////  60 frame
            //  _updateTimer.Interval = new TimeSpan(0, 0, 0, 0, 16);
            //  _updateTimer.Start();


            double screenWidth = System.Windows.SystemParameters.PrimaryScreenWidth;
            double screenHeight = System.Windows.SystemParameters.PrimaryScreenHeight;
            double windowWidth = this.Width;
            double windowHeight = this.Height;
            this.Left = (screenWidth / 2) - (windowWidth / 2);
            this.Top = (screenHeight / 2) - (windowHeight / 2);

            string baseDirectory = System.IO.Path.GetDirectoryName(AppDomain.CurrentDomain.BaseDirectory);
            int lastIndex = baseDirectory.LastIndexOf(toolFolderName);

            string tempString;
            tempString = baseDirectory.Substring(0, lastIndex);
            // ResourcePath = tempString + @"_Resources\";
            Paths.ResourcePath = tempString + @"_Resources\";
            // MeshPath = tempString + @"_Resources\Mesh\";
            Paths.MeshPath = tempString + @"_Resources\Mesh\";

            //TexturePath = tempString + @"_Resources\Texture\";
            Paths.TexturePath = tempString + @"_Resources\Texture\";

            Paths.DataPath = tempString + @"_Resources\Datas\";
       
            Paths.HierarchyDataPath = tempString + @"_Resources\Datas\HierarchyData\";
            Paths.SystemPath = tempString + @"_Resources\System\";
            Paths.MapDataPath = tempString + @"_Resources\Datas\MapData\";
            Paths.BackupPath = tempString + @"_Resources\Backup\";
            Paths.AssetPath = tempString + @"_Resources\Assets\";

            frameRateCalculator = new FrameRateCalculator();
            cameraController = new CameraController(this);
            Keyboard.AddKeyDownHandler(this, OnKeyDown);

            SimilarVTX.IsChecked = true;



            //TexturesLoad();
            bWindowInit = true;

            //AddGameObject();
        }
        ~MainWindow()
        {
            Externs.Destroy();
        }
        void Update_Tick(object sender, EventArgs e)
        {
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
                    break;
                case EToolMode.ViewTool:
                    HandToolButton.IsChecked = false;
                    ViewToolButton.IsChecked = true;
                    NavMeshToolButton.IsChecked = false;
                    break;
                case EToolMode.NavMeshTool:
                    HandToolButton.IsChecked = false;
                    ViewToolButton.IsChecked = false;
                    NavMeshToolButton.IsChecked = true;
                    break;
            }

            Externs.Update();
        }

        void CompositionTarget_Rendering(object sender, EventArgs e)
        {
            RenderingEventArgs args = (RenderingEventArgs)e;

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
        }

        TimeSpan _lastRender;
        double DxActualWidth;
        double DxActualHeight;
        string toolFolderName = "WPF_Tool";
        //string ResourcePath;
        // string MeshPath;
        //string TexturePath;
        bool bWindowInit = false;
        FrameRateCalculator frameRateCalculator;
        CameraController cameraController;
        //Dictionary<string, BitmapSource> textureImages;



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
                            break;
                        }
                        index++;
                    }
                    break;
            }
        }

       


        List<HierarchyData> hierarchyList = new List<HierarchyData>();
        List<MeshData> meshDatas = new List<MeshData>();
        
        int gameObjectIndex = 0;
        private int selectedIndex = -1;
        public int SelectedIndex
        {
            set
            {
                selectedIndex = value;
                
                foreach (var item in HierarchyList.Items)
                {
                    ListBoxItem listBoxItem = item as ListBoxItem;
                    if (selectedIndex.ToString() == listBoxItem.Uid)
                    {
                        listBoxItem.IsSelected = true;
                        break;
                    }
                }
            }
            get
            {
                return selectedIndex;
            }
        }


        private void NavPrimSelected(object sender, RoutedEventArgs e)
        {
            //CellDataGroup.IsEnabled = false;
        }
      
       
      

       

        

        private void ObjectTag_Selected(object sender, RoutedEventArgs e)
        {

        }



    }
}
