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
            ResourcePath = tempString + @"_Resources\";
            MeshPath = tempString + @"_Resources\Mesh\";
            TexturePath = tempString + @"_Resources\Texture\";


            frameRateCalculator = new FrameRateCalculator();
            cameraController = new CameraController(this);


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
        string ResourcePath;
        string MeshPath;
        string TexturePath;
        bool bWindowInit = false;
        FrameRateCalculator frameRateCalculator;
        CameraController cameraController;

        #region DllImports

     
        #endregion

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
                ofdlg.InitialDirectory = MeshPath;
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

                            hierarchyItem.meshData.meshFilePath = text;
                            MeshFilePath.Text = text;
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
                ofdlg.InitialDirectory = TexturePath;
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
            item.Content = "GameObject";
            item.MouseUp += SelectedGameObject;
            HierarchyList.Items.Add(item);
            HierarchyList.SelectionMode = SelectionMode.Single;
            int index = gameObjectIndex; // temp
            HierarchyData data = new HierarchyData();
            data.index = index;
            data.type = GameObjectType.Mesh;
            data.gameObjectData = new GameObjectData(index);
            data.meshData = new MeshData(index);
            gameObjectIndex++;
            hierarchyList.Add(data);
            Externs.AddGameObject(index);
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
                    MeshData.IsEnabled = false;

                    switch (hierarchyItem.type)
                    {
                        case GameObjectType.Mesh:
                            MeshData.IsEnabled = true;
                            MeshFilePath.Text = hierarchyItem.meshData.meshFilePath;
                            DiffuseFilePath.Text = hierarchyItem.meshData.diffuseTexturePath;
                            break;
                    }
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
            Point mousePos = e.GetPosition((IInputElement)sender);

            double x = mousePos.X;
            double y = mousePos.Y;

            double xRatio = x / imgelt.ActualWidth;
            double yRatio = y / imgelt.ActualHeight;

            double actualX = d3dimg.Width * xRatio;
            double actualY = d3dimg.Height * yRatio;

            string message = "DxMouseDown - X : " + actualX.ToString("N3") + ", Y : " + actualY.ToString("N3");

            if (e.ChangedButton == MouseButton.Middle && e.ButtonState == MouseButtonState.Pressed)
            {
                cameraController.OnWheelDownInDxRect((float)mousePos.X, (float)mousePos.Y);
            }
            else if (e.ChangedButton == MouseButton.Right && e.ButtonState == MouseButtonState.Pressed)
            {
                cameraController.OnRightButtonDownInDxRect((float)mousePos.X, (float)mousePos.Y);
            }

            DebugLog(message, ELogType.Log);
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
            switch(logType)
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

        private void Assets_Mesh_MouseDown(object sender, MouseButtonEventArgs e)
        {
            ProjectItems.Children.Clear();
            if (System.IO.Directory.Exists(MeshPath))
            {
                System.IO.DirectoryInfo info = new System.IO.DirectoryInfo(MeshPath);
                foreach (var item in info.GetFiles())
                {
                    // 잘 들어온다.
                    // 이어서 작업 해야함. TODO
                    // 이걸로 Unity Project 창처럼 만들어야함.
                    // 그 다음엔 XfileFormat 출력
                    Stream imageStreamSource = new FileStream(TexturePath + @"MeshIcon.png", FileMode.Open, FileAccess.Read, FileShare.Read);
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
        private void Assets_Texture_MouseDown(object sender, MouseButtonEventArgs e)
        {
            ProjectItems.Children.Clear();
            if (System.IO.Directory.Exists(TexturePath))
            {
                System.IO.DirectoryInfo info = new System.IO.DirectoryInfo(TexturePath);
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
                    else
                    {
                        Stream imageStreamSource = new FileStream(TexturePath + "NoImage.png", FileMode.Open, FileAccess.Read, FileShare.Read);
                        PngBitmapDecoder decoder = new PngBitmapDecoder(imageStreamSource, BitmapCreateOptions.PreservePixelFormat, BitmapCacheOption.Default);
                        bitmapSource = decoder.Frames[0];
                    }
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
            if(bWindowInit)
                Externs.ActiveEditObject();
        }

        private void Active_Unchecked(object sender, RoutedEventArgs e)
        {
            if(bWindowInit)
                Externs.InactiveEditObject();
        }

        
    }
}
