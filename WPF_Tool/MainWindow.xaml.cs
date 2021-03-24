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
using Microsoft.Win32;


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

            Initialize();
            CompositionTarget.Rendering += new EventHandler(CompositionTarget_Rendering);

            _updateTimer = new DispatcherTimer();
            _updateTimer.Tick += new EventHandler(Update_Tick);
          //  60 frame
            _updateTimer.Interval = new TimeSpan(0, 0, 0, 0, 16);
            _updateTimer.Start();


            double screenWidth = System.Windows.SystemParameters.PrimaryScreenWidth;
            double screenHeight = System.Windows.SystemParameters.PrimaryScreenHeight;
            double windowWidth = this.Width;
            double windowHeight = this.Height;
            this.Left = (screenWidth / 2) - (windowWidth / 2);
            this.Top = (screenHeight / 2) - (windowHeight / 2);


            

            //AddGameObject();
        }
        ~MainWindow()
        {
            Destroy();
        }
        void Update_Tick(object sender, EventArgs e)
        {
           
           
            DxActualWidth = imgelt.ActualWidth;
            DxActualHeight = imgelt.ActualHeight;
            DxScreenSizeX.Text = DxActualWidth.ToString("N3");
            DxScreenSizeY.Text = DxActualHeight.ToString("N3");
            Update();
        }
        void CompositionTarget_Rendering(object sender, EventArgs e)
        {
            RenderingEventArgs args = (RenderingEventArgs)e;

            // It's possible for Rendering to call back twice in the same frame 
            // so only render when we haven't already rendered in this frame.
            if (d3dimg.IsFrontBufferAvailable && _lastRender != args.RenderingTime)
            {
                IntPtr pSurface = IntPtr.Zero;
                GetBackBuffer(out pSurface);
                if (pSurface != IntPtr.Zero)
                {
                    d3dimg.Lock();
                    // Repeatedly calling SetBackBuffer with the same IntPtr is 
                    // a no-op. There is no performance penalty.
                    d3dimg.SetBackBuffer(D3DResourceType.IDirect3DSurface9, pSurface);
                    Render();
                    d3dimg.AddDirtyRect(new Int32Rect(0, 0, d3dimg.PixelWidth, d3dimg.PixelHeight));
                    d3dimg.Unlock();

                    _lastRender = args.RenderingTime;
                }
            }
        }

        DispatcherTimer _updateTimer;
        TimeSpan _lastRender;
        double DxActualWidth;
        double DxActualHeight;
        string toolFolderName = "WPF_Tool";

        #region DllImports

        [DllImport("HyEngine.dll")]
        static extern void Initialize();

        [DllImport("HyEngine.dll")]
        static extern void Destroy();

        [DllImport("HyEngine.dll")]
        static extern void GetBackBuffer(out IntPtr pSurface);

        [DllImport("HyEngine.dll")]
        static extern void Update();

        [DllImport("HyEngine.dll")]
        static extern void Render();

        [DllImport("HyEngine.dll")]
        static extern void AddGameObject(int index);

        [DllImport("HyEngine.dll")]
        static extern void InsertGameData(ref GameObjectData data);

        [DllImport("HyEngine.dll")]
        static extern void InsertMeshData(ref MeshData data);

        [DllImport("HyEngine.dll")]
        static extern void SelectEditObject(int index);

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
                ofdlg.InitialDirectory = System.IO.Path.GetDirectoryName(AppDomain.CurrentDomain.BaseDirectory);
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
                ofdlg.InitialDirectory = System.IO.Path.GetDirectoryName(AppDomain.CurrentDomain.BaseDirectory);

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
            AddGameObject(index);
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
                    SelectEditObject(hierarchyItem.index);
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
                    InsertGameData(ref data);
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
                    InsertGameData(ref data);
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
                    InsertGameData(ref data);
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
                    InsertGameData(ref data);
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
                    InsertGameData(ref data);
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
                    InsertGameData(ref data);
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
                    InsertGameData(ref data);
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
                    InsertGameData(ref data);
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
                    InsertGameData(ref data);
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
                    InsertGameData(ref data.gameObjectData);
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
                    InsertMeshData(ref data.meshData);
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
                    InsertMeshData(ref data.meshData);
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


            DebugLog(message);
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
            
        }

        public void DebugLog(string message)
        {
            TextBlock element = new TextBlock();
            element.Text = message;
            ConsoleMessages.Children.Add(element);
            ConsoleScrollViewer.ScrollToBottom();
        }

        private void Assets_Mesh_MouseDown(object sender, MouseButtonEventArgs e)
        {
            string str = System.IO.Path.GetDirectoryName(AppDomain.CurrentDomain.BaseDirectory);
            int lastIndex = str.LastIndexOf(toolFolderName);

           str =  str.Substring(0, lastIndex);
            str = str + @"_Resources\Mesh";
            if (System.IO.Directory.Exists(str))
            {
                System.IO.DirectoryInfo info = new System.IO.DirectoryInfo(str);
                foreach (var item in info.GetFiles())
                {
                    // 잘 들어온다.
                    // 이어서 작업 해야함. TODO
                    // 이걸로 Unity Project 창처럼 만들어야함.
                    // 그 다음엔 XfileFormat 출력
                    string fileName = item.Name;
                    string fileType = item.Extension;
                }
            }
            else
            {
                int a = 0;
            }
        }
    }
}
