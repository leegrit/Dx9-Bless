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

            Paths.DataPath = tempString + @"_Resources\Data\";
            Paths.GameObjectDataPath = tempString + @"_Resources\Data\GameObjectData\";
            Paths.MeshDataPath = tempString + @"_Resources\Data\MeshData\";
            Paths.HierarchyDataPath = tempString + @"_Resources\Data\HierarchyData\";

            frameRateCalculator = new FrameRateCalculator();
            cameraController = new CameraController(this);
            Keyboard.AddKeyDownHandler(this, OnKeyDown);

            SimilarVTX.IsChecked = true;

            TexturesLoad();
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
        Dictionary<string, BitmapSource> textureImages;


        public void TexturesLoad()
        {
            textureImages = new Dictionary<string, BitmapSource>();
            if (System.IO.Directory.Exists(Paths.TexturePath))
            {
                System.IO.DirectoryInfo info = new System.IO.DirectoryInfo(Paths.TexturePath);
                foreach (var item in info.GetFiles())
                {
                    // 잘 들어온다.
                    // 이어서 작업 해야함. TODO
                    // 이걸로 Unity Project 창처럼 만들어야함.
                    // 그 다음엔 XfileFormat 출력

                    // png만 출력할 수 있음
                    BitmapSource bitmapSource;
                    if (item.Extension == ".png")
                    {
                        Stream imageStreamSource = new FileStream(item.FullName, FileMode.Open, FileAccess.Read, FileShare.Read);
                        PngBitmapDecoder decoder = new PngBitmapDecoder(imageStreamSource, BitmapCreateOptions.PreservePixelFormat, BitmapCacheOption.Default);
                        bitmapSource = decoder.Frames[0];
                       
                    }
                    else if (item.Extension == ".tga")
                    {
                        // 이거 해결해야함.
                        // tga loader에서 간헐적으로 tga.image를 로드하지 못하는 문제가 있음
                        // 아마 stride가 큰건 못읽어서 그런듯?


                        //Stream imageStreamSource = new FileStream(Paths.TexturePath + "NoImage.png", FileMode.Open, FileAccess.Read, FileShare.Read);
                        //PngBitmapDecoder decoder = new PngBitmapDecoder(imageStreamSource, BitmapCreateOptions.PreservePixelFormat, BitmapCacheOption.Default);
                        //bitmapSource = decoder.Frames[0];
                        bitmapSource = default(BitmapSource);
                        System.Drawing.Bitmap bitMap;

                        //bitMap = Paloma.TargaImage.LoadTargaImage(item.FullName);

                        Paloma.TargaImage tgaImage = new Paloma.TargaImage(item.FullName);
                        bitMap = tgaImage.Image;
                        if (tgaImage.Stride < 3070)
                        {
                            var handle = bitMap.GetHbitmap();


                            bitmapSource = Imaging.CreateBitmapSourceFromHBitmap(handle, IntPtr.Zero, Int32Rect.Empty, BitmapSizeOptions.FromEmptyOptions());
                        }
                        else
                        {
                            Stream imageStreamSource = new FileStream(Paths.TexturePath + "NoImage.png", FileMode.Open, FileAccess.Read, FileShare.Read);
                            PngBitmapDecoder decoder = new PngBitmapDecoder(imageStreamSource, BitmapCreateOptions.PreservePixelFormat, BitmapCacheOption.Default);
                            bitmapSource = decoder.Frames[0];
                        }
                        tgaImage.Dispose();

                    }
                    else
                    {
                        Stream imageStreamSource = new FileStream(Paths.TexturePath + "NoImage.png", FileMode.Open, FileAccess.Read, FileShare.Read);
                        PngBitmapDecoder decoder = new PngBitmapDecoder(imageStreamSource, BitmapCreateOptions.PreservePixelFormat, BitmapCacheOption.Default);
                        bitmapSource = decoder.Frames[0];
                    }
                    textureImages.Add(item.FullName, bitmapSource);
                   

                }
            }
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
                        if (hierarchyItem.index == selectedIndex)
                        {
                            selectedIndex = -1;
                            hierarchyList.Remove(hierarchyItem);
                            HierarchyList.Items.RemoveAt(index);
                            Externs.RemoveGameObject(hierarchyItem.index);
                            break;
                        }
                        index++;
                    }
                    break;
            }
        }

        #region ButtonEvent
        private void Button_Click(object sender, RoutedEventArgs e)
        {
            //AddGameObject();
        }

        private void btn_File_Click(object sender, RoutedEventArgs e)
        {

        }

        private void GameObject_Click(object sender, RoutedEventArgs e)
        {

        }

        private void btn_GameObject_Click(object sender, RoutedEventArgs e)
        {

        }

        private void btn_Help_Click(object sender, RoutedEventArgs e)
        {


        }

        private void MenuItem_Click(object sender, RoutedEventArgs e)
        {

        }

        private void MenuItem_Click_1(object sender, RoutedEventArgs e)
        {

        }

        private void MenuItem_Click_2(object sender, RoutedEventArgs e)
        {

        }

        private void Button_MeshLoad(object sender, RoutedEventArgs e)
        {
            OpenFileDialog ofdlg = new OpenFileDialog();
            {
                // 기본 폴더
                //ofdlg.InitialDirectory = @"..\..\..\_Resources\Mesh";// "../../../_Resources/Mesh";
                // ofdlg.InitialDirectory = System.IO.Path.Combine(
                //    System.IO.Path.GetDirectoryName(AppDomain.CurrentDomain.BaseDirectory), "..\\..\\..\\_Resources\\Mesh\\");
                //ofdlg.InitialDirectory = System.IO.Path.GetDirectoryName(AppDomain.CurrentDomain.BaseDirectory);
                ofdlg.InitialDirectory = Paths.MeshPath;
                ofdlg.CheckFileExists = true; // 파일 존재여부 확인
                ofdlg.CheckPathExists = true; // 폴더 존재여부 확인

                // 파일 열기(값의 유무 확인)
                if (ofdlg.ShowDialog().GetValueOrDefault())
                {
                    foreach (var hierarchyItem in hierarchyList)
                    {
                        if (hierarchyItem.index == selectedIndex)
                        {
                            int index = ofdlg.FileName.LastIndexOf("\\");
                            string text = ofdlg.FileName.Substring(index + 1);
                            int extIndex = text.LastIndexOf(".");
                            string ext = text.Substring(extIndex);
                            hierarchyItem.meshData.meshFilePath = text;
                            MeshFilePath.Text = text;
                            // x file은 따로 텍스처가 필요 없기 때문
                            if (ext == ".X" || ext == ".x")
                                DiffuseFilePath.Text = text;
                            break;
                        }
                    }
                }
            }
        }
        private void Button_DiffuseLoad(object sender, RoutedEventArgs e)
        {
            OpenFileDialog ofdlg = new OpenFileDialog();
            {
                // 기본 폴더
                //ofdlg.InitialDirectory = System.IO.Path.GetDirectoryName(AppDomain.CurrentDomain.BaseDirectory);
                ofdlg.InitialDirectory = Paths.TexturePath;
                ofdlg.CheckFileExists = true; // 파일 존재여부 확인
                ofdlg.CheckPathExists = true; // 폴더 존재여부 확인

                // 파일 열기(값의 유무 확인)
                if (ofdlg.ShowDialog().GetValueOrDefault())
                {
                    foreach (var hierarchyItem in hierarchyList)
                    {
                        if (hierarchyItem.index == selectedIndex)
                        {
                            int index = ofdlg.FileName.LastIndexOf("\\");
                            string text = ofdlg.FileName.Substring(index + 1);

                            hierarchyItem.meshData.diffuseTexturePath = text;
                            DiffuseFilePath.Text = text;
                            break;
                        }
                    }
                }
            }
        }
        private void Btn_CreateMesh(object sender, RoutedEventArgs e)
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
            data.index = index;
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
        private void Btn_CreateNavMesh(object sender, RoutedEventArgs e)
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
            data.index = index;
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
        #endregion

        private void SelectedGameObject(object sender, RoutedEventArgs e)
        {
            ListBoxItem item = sender as ListBoxItem;
            foreach (var hierarchyItem in hierarchyList)
            {
                if (hierarchyItem.index.ToString() == item.Uid.ToString())
                {
                    selectedIndex = hierarchyItem.index;
                    Externs.SelectEditObject(hierarchyItem.index);
                    GameObjectName.Text = hierarchyItem.gameObjectData.name;
                    ObjectTag.SelectedIndex = hierarchyItem.tagIndex;
                    ObjectLayer.SelectedIndex = hierarchyItem.layerIndex;
                    ObjectStatic.SelectedIndex = hierarchyItem.staticIndex;
                    PositionX.Text = hierarchyItem.gameObjectData.transform.position.x.ToString();
                    PositionY.Text = hierarchyItem.gameObjectData.transform.position.y.ToString();
                    PositionZ.Text = hierarchyItem.gameObjectData.transform.position.z.ToString();
                    RotationX.Text = hierarchyItem.gameObjectData.transform.rotation.x.ToString();
                    RotationY.Text = hierarchyItem.gameObjectData.transform.rotation.y.ToString();
                    RotationZ.Text = hierarchyItem.gameObjectData.transform.rotation.z.ToString();
                    ScaleX.Text = hierarchyItem.gameObjectData.transform.scale.x.ToString();
                    ScaleY.Text = hierarchyItem.gameObjectData.transform.scale.y.ToString();
                    ScaleZ.Text = hierarchyItem.gameObjectData.transform.scale.z.ToString();


                    // default
                    // 만약 navmesh 상태에서 일반 오브젝트를 클릭하면
                    // 원상복귀되어야한다.
                    ToolManager.ToolMode = EToolMode.HandTool;

                    // 여기서 각 데이터 그룹박스를 비활성화 하고
                    // 선택한 오브젝트 타입에 따라 활성화해준다.
                    MeshData.Visibility = Visibility.Hidden;
                    TransformData.Visibility = Visibility.Hidden;

                    switch (hierarchyItem.type)
                    {
                        case GameObjectType.Mesh:
                            MeshData.Visibility = Visibility.Visible;
                            TransformData.Visibility = Visibility.Visible;
                            MeshFilePath.Text = hierarchyItem.meshData.meshFilePath;
                            DiffuseFilePath.Text = hierarchyItem.meshData.diffuseTexturePath;
                            break;
                        case GameObjectType.NavMesh:

                            break;
                    }
                    break;
                }
            }

        }
        private void SelectedNavMesh(object sender, RoutedEventArgs e)
        {
            ListBoxItem item = sender as ListBoxItem;
            foreach (var hierarchyItem in hierarchyList)
            {
                if (hierarchyItem.index.ToString() == item.Uid.ToString())
                {
                    selectedIndex = hierarchyItem.index;
                    Externs.SelectEditObject(hierarchyItem.index);
                    GameObjectName.Text = hierarchyItem.gameObjectData.name;
                    ObjectTag.SelectedIndex = hierarchyItem.tagIndex;
                    ObjectLayer.SelectedIndex = hierarchyItem.layerIndex;
                    ObjectStatic.SelectedIndex = hierarchyItem.staticIndex;
                    PositionX.Text = hierarchyItem.gameObjectData.transform.position.x.ToString();
                    PositionY.Text = hierarchyItem.gameObjectData.transform.position.y.ToString();
                    PositionZ.Text = hierarchyItem.gameObjectData.transform.position.z.ToString();
                    RotationX.Text = hierarchyItem.gameObjectData.transform.rotation.x.ToString();
                    RotationY.Text = hierarchyItem.gameObjectData.transform.rotation.y.ToString();
                    RotationZ.Text = hierarchyItem.gameObjectData.transform.rotation.z.ToString();
                    ScaleX.Text = hierarchyItem.gameObjectData.transform.scale.x.ToString();
                    ScaleY.Text = hierarchyItem.gameObjectData.transform.scale.y.ToString();
                    ScaleZ.Text = hierarchyItem.gameObjectData.transform.scale.z.ToString();


                    // 여기서 각 데이터 그룹박스를 비활성화 하고
                    // 선택한 오브젝트 타입에 따라 활성화해준다.
                    MeshData.Visibility = Visibility.Hidden;
                    TransformData.Visibility = Visibility.Hidden;

                    switch (hierarchyItem.type)
                    {
                        case GameObjectType.Mesh:
                            MeshData.Visibility = Visibility.Visible;
                            TransformData.Visibility = Visibility.Visible;
                            MeshFilePath.Text = hierarchyItem.meshData.meshFilePath;
                            DiffuseFilePath.Text = hierarchyItem.meshData.diffuseTexturePath;
                            break;
                        case GameObjectType.NavMesh:

                            break;
                    }


                    // 여기부터 navMesh tap
                    // 강제로 탭 변경을 한다.
                    InspectorTab.SelectedIndex = 1;
                    ToolManager.ToolMode = EToolMode.NavMeshTool;



                    break;
                }
            }

        }


        List<HierarchyData> hierarchyList = new List<HierarchyData>();
        List<MeshData> meshDatas = new List<MeshData>();
        
        int gameObjectIndex = 0;
        int selectedIndex = -1;
        private void RenderStateBox_SelectionChanged(object sender, SelectionChangedEventArgs e)
        {

        }

        private void CellPositionX_TextChanged(object sender, TextChangedEventArgs e)
        {
            if (ToolManager.ToolMode != EToolMode.NavMeshTool)
                return;
            TextBox textBox = sender as TextBox;


            CellData data = default(CellData);
            ECellEditMode editMode = ECellEditMode.Similar;

            bool bFound = false;
            foreach (var cellData in NavMeshManager.CellDatas)
            {
                if (cellData.cellIndex == NavMeshManager.SelectedCellIndex)
                {
                    data = cellData;
                    editMode = NavMeshManager.CellEditMode;
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
            foreach (var cellData in NavMeshManager.CellDatas)
            {
                if (cellData.cellIndex == NavMeshManager.SelectedCellIndex)
                {
                    data = cellData;
                    editMode = NavMeshManager.CellEditMode;
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
            foreach (var cellData in NavMeshManager.CellDatas)
            {
                if (cellData.cellIndex == NavMeshManager.SelectedCellIndex)
                {
                    data = cellData;
                    editMode = NavMeshManager.CellEditMode;
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
                if (hierarchyItem.index == selectedIndex)
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
                if (hierarchyItem.index == selectedIndex)
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
                if (hierarchyItem.index == selectedIndex)
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
                if (hierarchyItem.index == selectedIndex)
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
                if (hierarchyItem.index == selectedIndex)
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
                if (hierarchyItem.index == selectedIndex)
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
                if (hierarchyItem.index == selectedIndex)
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
                if (hierarchyItem.index == selectedIndex)
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
                if (hierarchyItem.index == selectedIndex)
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

        private void GameObjectName_TextChanged(object sender, TextChangedEventArgs e)
        {
            TextBox textBox = sender as TextBox;
            for (int i = 0; i < hierarchyList.Count; i++)
            {
                if (hierarchyList[i].index == selectedIndex)
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
            TextBox textBox = sender as TextBox;
            for (int i = 0; i < hierarchyList.Count; i++)
            {
                if (hierarchyList[i].index == selectedIndex)
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
            TextBox textBox = sender as TextBox;
            for (int i = 0; i < hierarchyList.Count; i++)
            {
                if (hierarchyList[i].index == selectedIndex)
                {
                    HierarchyData data = hierarchyList[i];
                    data.meshData.diffuseTexturePath = textBox.Text;
                    hierarchyList[i] = data;
                    Externs.InsertMeshData(ref data.meshData);
                    break;
                }
            }
        }
        private void Button_Click_1(object sender, RoutedEventArgs e)
        {

        }
        private void NavPrimSelected(object sender, RoutedEventArgs e)
        {
            //CellDataGroup.IsEnabled = false;
        }
        private void CellSelected(object sender, RoutedEventArgs e)
        {
            TreeViewItem item = sender as TreeViewItem;
            //CellDataGroup.IsEnabled = true;
            CellData cellData = default(CellData);
            bool bFind = false;
            foreach(var data in NavMeshManager.CellDatas)
            {
                if (item.Uid == data.cellIndex.ToString())
                {
                    cellData = data;
                    bFind = true;
                    break;
                }
            }
            Debug.Assert(bFind);
            NavMeshManager.SelectedCellIndex = cellData.cellIndex;
            CellIndex.Text = item.Uid;

            CellOption.SelectedIndex = cellData.option;
            CellPositionX.Text = cellData.position.x.ToString();
            CellPositionY.Text = cellData.position.y.ToString();
            CellPositionZ.Text = cellData.position.z.ToString();
        }
        private void Dx_MouseMove(object sender, MouseEventArgs e)
        {
            Point mousePos = e.GetPosition((IInputElement)sender);

            double x = mousePos.X;
            double y = mousePos.Y;

            DXMousePosX.Text = x.ToString("N3");
            DXMousePosY.Text = y.ToString("N3");
        }

        private void Dx_MouseDown(object sender, MouseButtonEventArgs e)
        {

            // Dx 화면을 클릭하면 모든 포커스를 없앤다.

            //IInputElement logicFocusedControl = FocusManager.GetFocusedElement(this);
            //Keyboard.ClearFocus();


            // Keyboard.Focus(this);

            //Keyboard.Focus(this);
            // Image i = sender as Image;

            // IInputElement keyboardFocusedControl = Keyboard.FocusedElement;
            //keyboardFocusedControl.Focusable = false;
            //  keyboardFocusedControl


            Point mousePos = e.GetPosition((IInputElement)sender);

            double x = mousePos.X;
            double y = mousePos.Y;

            double xRatio = x / imgelt.ActualWidth;
            double yRatio = y / imgelt.ActualHeight;

            double actualX = d3dimg.Width * xRatio;
            double actualY = d3dimg.Height * yRatio;
            

            if (e.ChangedButton == MouseButton.Left)
            {
                if (ToolManager.ToolMode == EToolMode.NavMeshTool)
                {
                    Vector3 pickedPos = default(Vector3);
                    bool isHit = Externs.PickNavMesh((float)actualX, (float)actualY, (int)NavMeshManager.CellOption ,ref pickedPos);
                    if (isHit)
                    {
                        bool isNewPrim = false;
                        isNewPrim = NavMeshManager.IsNewPrimitive();
                        if (isNewPrim == true)
                        {
                            TreeViewItem primItem = new TreeViewItem();
                            primItem.Header = "NavPrimitive_" + NavMeshManager.NavPrimIndex.ToString();
                            primItem.Uid = NavMeshManager.NavPrimIndex.ToString();
                            primItem.Selected += NavPrimSelected;
                            NavMeshManager.NavPrimIndex++;


                            CellList.Items.Add(primItem);
                        }

                        TreeViewItem cellItem = new TreeViewItem();
                        cellItem.Header = "Cell_" + NavMeshManager.CellIndex;
                        cellItem.Uid = NavMeshManager.CellIndex.ToString();
                        cellItem.Selected += CellSelected;
                        NavMeshManager.AddCell(pickedPos);

                        int primCount = CellList.Items.Count;

                        ((TreeViewItem)CellList.Items[primCount - 1]).Items.Add(cellItem);




                        DebugLog("NavMesh Picked X : " + pickedPos.x + ", " + " Y : " + pickedPos.y + ", Z : " + pickedPos.z, ELogType.Log);
                    }
                }
            }
            if (e.ChangedButton == MouseButton.Middle && e.ButtonState == MouseButtonState.Pressed)
            {
                cameraController.OnWheelDownInDxRect((float)mousePos.X, (float)mousePos.Y);
            }
            else if (e.ChangedButton == MouseButton.Right && e.ButtonState == MouseButtonState.Pressed)
            {
                cameraController.OnRightButtonDownInDxRect((float)mousePos.X, (float)mousePos.Y);
            }

            
        }

        private void Dx_MouseUp(object sender, MouseButtonEventArgs e)
        {
            Point mousePos = e.GetPosition((IInputElement)sender);

            double x = mousePos.X;
            double y = mousePos.Y;
            double xRatio = x / imgelt.ActualWidth;
            double yRatio = y / imgelt.ActualHeight;

            double actualX = d3dimg.Width * xRatio;
            double actualY = d3dimg.Height * yRatio;


            if (e.ChangedButton == MouseButton.Middle)
            {
                cameraController.OnWheelUpInDxRect();
            }
            else if (e.ChangedButton == MouseButton.Right)
            {
                cameraController.OnRightButtonUpInDxRect();
            }

        }

        public void DebugLog(string message, ELogType logType = ELogType.Log)
        {
            TextBlock element = new TextBlock();
            switch (logType)
            {
                case ELogType.Log:
                    string logLabel = "[Log] ";
                    element.Text = logLabel + message;
                    element.Foreground = Brushes.White;
                    break;
                case ELogType.Warning:
                    string warningLabel = "[Warning] ";
                    element.Text = warningLabel + message;
                    element.Foreground = Brushes.Yellow;
                    break;
                case ELogType.Error:
                    string errorLabel = "[Error] ";
                    element.Text = errorLabel + message;
                    element.Foreground = Brushes.Red;
                    break;
                default:
                    Debug.Assert(false);
                    break;
            }
            ConsoleMessages.Children.Add(element);
            ConsoleScrollViewer.ScrollToBottom();
        }

        private void Assets_Mesh_MouseDown(object sender, RoutedEventArgs e)
        {
            ProjectItems.Children.Clear();
            if (System.IO.Directory.Exists(Paths.MeshPath))
            {
                System.IO.DirectoryInfo info = new System.IO.DirectoryInfo(Paths.MeshPath);
                foreach (var item in info.GetFiles())
                {
                    // 잘 들어온다.
                    // 이어서 작업 해야함. TODO
                    // 이걸로 Unity Project 창처럼 만들어야함.
                    // 그 다음엔 XfileFormat 출력
                    Stream imageStreamSource = new FileStream(Paths.TexturePath + @"MeshIcon.png", FileMode.Open, FileAccess.Read, FileShare.Read);
                    PngBitmapDecoder decoder = new PngBitmapDecoder(imageStreamSource, BitmapCreateOptions.PreservePixelFormat, BitmapCacheOption.Default);
                    BitmapSource bitmapSource = decoder.Frames[0];
                    Image itemImage = new Image();
                    itemImage.Source = bitmapSource;
                    itemImage.Width = 95;
                    itemImage.Height = 75;

                    TextBlock itemText = new TextBlock();
                    itemText.Text = item.Name;
                    itemText.TextAlignment = TextAlignment.Center;
                    itemText.Foreground = Brushes.White;
                    itemText.Width = 95;
                    itemText.Height = 20;

                    StackPanel itemPanel = new StackPanel();
                    itemPanel.VerticalAlignment = VerticalAlignment.Center;
                    itemPanel.HorizontalAlignment = HorizontalAlignment.Center;
                    itemPanel.Children.Add(itemImage);
                    itemPanel.Children.Add(itemText);

                    ProjectItems.Children.Add(itemPanel);

                    // string fileName = item.Name;
                    //string fileType = item.Extension;
                }
            }
        }
        private void Assets_Texture_MouseDown(object sender, RoutedEventArgs e)
        {
            ProjectItems.Children.Clear();
            if (System.IO.Directory.Exists(Paths.TexturePath))
            {
                System.IO.DirectoryInfo info = new System.IO.DirectoryInfo(Paths.TexturePath);
                foreach (var item in info.GetFiles())
                {
                    // 잘 들어온다.
                    // 이어서 작업 해야함. TODO
                    // 이걸로 Unity Project 창처럼 만들어야함.
                    // 그 다음엔 XfileFormat 출력

                    // png만 출력할 수 있음
                    BitmapSource bitmapSource;
                    bitmapSource = textureImages[item.FullName];
                    //if (item.Extension == ".png")
                    //{
                    //    bitmapSource = textureImages[item.FullName];
                    //    //Stream imageStreamSource = new FileStream(item.FullName, FileMode.Open, FileAccess.Read, FileShare.Read);
                    //    //PngBitmapDecoder decoder = new PngBitmapDecoder(imageStreamSource, BitmapCreateOptions.PreservePixelFormat, BitmapCacheOption.Default);
                    //    //bitmapSource = decoder.Frames[0];
                    //}
                    //else if (item.Extension == ".tga")
                    //{
                    //    bitmapSource = default(BitmapSource);
                    //    System.Drawing.Bitmap bitMap;
                    //    try
                    //    {
                    //        bitMap = Paloma.TargaImage.LoadTargaImage(item.FullName);
                    //        if (bitMap != null)
                    //        {
                    //            var handle = bitMap.GetHbitmap();

                    //            bitmapSource = Imaging.CreateBitmapSourceFromHBitmap(handle, IntPtr.Zero, Int32Rect.Empty, BitmapSizeOptions.FromEmptyOptions());
                    //        }
                    //    }
                    //    catch (Exception ex)
                    //    {
                    //        DebugLog(ex.Message, ELogType.Error);

                    //    }
                    //    finally
                    //    {
                           
                    //    }
                    //}
                    //else
                    //{
                    //    Stream imageStreamSource = new FileStream(Paths.TexturePath + "NoImage.png", FileMode.Open, FileAccess.Read, FileShare.Read);
                    //    PngBitmapDecoder decoder = new PngBitmapDecoder(imageStreamSource, BitmapCreateOptions.PreservePixelFormat, BitmapCacheOption.Default);
                    //    bitmapSource = decoder.Frames[0];
                    //}
                    Image itemImage = new Image();
                    
                    itemImage.Source = bitmapSource;
                    itemImage.Width = 95;
                    itemImage.Height = 75;

                    TextBlock itemText = new TextBlock();
                    itemText.Text = item.Name;
                    itemText.TextAlignment = TextAlignment.Center;
                    itemText.Foreground = Brushes.White;
                    itemText.Width = 95;
                    itemText.Height = 20;

                    StackPanel itemPanel = new StackPanel();
                    itemPanel.VerticalAlignment = VerticalAlignment.Center;
                    itemPanel.HorizontalAlignment = HorizontalAlignment.Center;
                    itemPanel.Children.Add(itemImage);
                    itemPanel.Children.Add(itemText);

                    ProjectItems.Children.Add(itemPanel);

                    // string fileName = item.Name;
                    //string fileType = item.Extension;
                }
            }
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

        private void Solid_Selected(object sender, RoutedEventArgs e)
        {
            if (bWindowInit)
                Externs.SetSolidMode();
        }

        private void WireFrame_Selected(object sender, RoutedEventArgs e)
        {
            if (bWindowInit)
                Externs.SetWireFrameMode();
        }

        private void Tag_Selected(object sender, RoutedEventArgs e)
        {
            ComboBox item = sender as ComboBox;
            int comboBoxIndex = item.SelectedIndex;

            for (int i = 0; i < hierarchyList.Count; i++)
            {
                if (hierarchyList[i].index == selectedIndex)
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
                if (hierarchyList[i].index == selectedIndex)
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
                if (hierarchyList[i].index == selectedIndex)
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

        private void ObjectTag_Selected(object sender, RoutedEventArgs e)
        {

        }

        private void Btn_HierarchySave(object sender, RoutedEventArgs e)
        {
            if (selectedIndex == -1) return;

            foreach (var hierarchyItem in hierarchyList)
            {
                if (hierarchyItem.index == selectedIndex)
                {
                    bool result;
                    string fileName = "";
                    result = JsonHelper.Write(hierarchyItem, ref fileName);
                    if (result)
                    {
                        MessageBox.Show("Hierarchy 정보 저장에 성공했습니다.\n FileName : " + fileName, "Hierarchy Save 성공");
                    }

                    return;
                }
            }
        }
        private void Btn_HierarchyLoad(object sender, RoutedEventArgs e)
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

                    ListBoxItem item = new ListBoxItem();
                    // item.Name = "GameObject" + gameObjectIndex;
                    item.Uid = gameObjectIndex.ToString();
                    item.Content = hierarchyData.gameObjectData.name;
                    item.Tag = hierarchyData.gameObjectData.tag;
                    item.MouseUp += SelectedGameObject;
                    HierarchyList.Items.Add(item);
                    HierarchyList.SelectionMode = SelectionMode.Single;
                    int index = gameObjectIndex; // temp
                    HierarchyData data = hierarchyData;
                    data.index = index;
                    gameObjectIndex++;
                    hierarchyList.Add(data);
                    Externs.AddGameObject(index);


                    selectedIndex = data.index;
                    Externs.SelectEditObject(data.index);
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


                    // 여기서 각 데이터 그룹박스를 비활성화 하고
                    // 선택한 오브젝트 타입에 따라 활성화해준다.
                    MeshData.Visibility = Visibility.Hidden;
                    TransformData.Visibility = Visibility.Hidden;

                    switch (data.type)
                    {
                        case GameObjectType.Mesh:
                            MeshData.Visibility = Visibility.Visible;
                            TransformData.Visibility = Visibility.Visible;
                            MeshFilePath.Text = data.meshData.meshFilePath;
                            DiffuseFilePath.Text = data.meshData.diffuseTexturePath;
                            break;
                        case GameObjectType.NavMesh:

                            break;
                    }
                    return;
                }
            }
        }

        private void Datas_HierarchyData_MouseDown(object sender, RoutedEventArgs e)
        {
            ProjectItems.Children.Clear();
            if (System.IO.Directory.Exists(Paths.HierarchyDataPath))
            {
                System.IO.DirectoryInfo info = new System.IO.DirectoryInfo(Paths.HierarchyDataPath);
                foreach (var item in info.GetFiles())
                {
                    // 잘 들어온다.
                    // 이어서 작업 해야함. TODO
                    // 이걸로 Unity Project 창처럼 만들어야함.
                    // 그 다음엔 XfileFormat 출력

                    // png만 출력할 수 있음
                    BitmapSource bitmapSource;
                    //if (item.Extension == ".png")
                    //{
                    //    Stream imageStreamSource = new FileStream(item.FullName, FileMode.Open, FileAccess.Read, FileShare.Read);
                    //    PngBitmapDecoder decoder = new PngBitmapDecoder(imageStreamSource, BitmapCreateOptions.PreservePixelFormat, BitmapCacheOption.Default);
                    //    bitmapSource = decoder.Frames[0];
                    //}
                    //else
                    //{
                    //    Stream imageStreamSource = new FileStream(Paths.TexturePath + "NoImage.png", FileMode.Open, FileAccess.Read, FileShare.Read);
                    //    PngBitmapDecoder decoder = new PngBitmapDecoder(imageStreamSource, BitmapCreateOptions.PreservePixelFormat, BitmapCacheOption.Default);
                    //    bitmapSource = decoder.Frames[0];
                    //}

                    Stream imageStreamSource = new FileStream(Paths.TexturePath + "JsonIcon.png", FileMode.Open, FileAccess.Read, FileShare.Read);
                    PngBitmapDecoder decoder = new PngBitmapDecoder(imageStreamSource, BitmapCreateOptions.PreservePixelFormat, BitmapCacheOption.Default);
                    bitmapSource = decoder.Frames[0];

                    Image itemImage = new Image();
                    itemImage.Source = bitmapSource;
                    itemImage.Width = 95;
                    itemImage.Height = 75;

                    TextBlock itemText = new TextBlock();
                    itemText.Text = item.Name;
                    itemText.TextAlignment = TextAlignment.Center;
                    itemText.Foreground = Brushes.White;
                    itemText.Width = 95;
                    itemText.Height = 20;

                    StackPanel itemPanel = new StackPanel();
                    itemPanel.VerticalAlignment = VerticalAlignment.Center;
                    itemPanel.HorizontalAlignment = HorizontalAlignment.Center;
                    itemPanel.Children.Add(itemImage);
                    itemPanel.Children.Add(itemText);

                    ProjectItems.Children.Add(itemPanel);

                    // string fileName = item.Name;
                    //string fileType = item.Extension;
                }
            }
        }

        private void SimilarVTX_Checked(object sender, RoutedEventArgs e)
        {
            NavMeshManager.CellEditMode = ECellEditMode.Similar;
        }

        private void SelectedVTX_Checked(object sender, RoutedEventArgs e)
        {
            NavMeshManager.CellEditMode = ECellEditMode.Selected;
        }
    }
}
