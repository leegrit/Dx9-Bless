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
        bool bWindowInit = false;
        bool bLateInit = false;
        FrameRateCalculator frameRateCalculator;
        CameraController cameraController;
        GameObjectController gameObjectController;
        private void InitializeWindow()
        {

            AppDomain currentDomain = AppDomain.CurrentDomain;
            currentDomain.UnhandledException += new UnhandledExceptionEventHandler(UnHandledException);

            Externs.Initialize();
            CompositionTarget.Rendering += new EventHandler(CompositionTarget_Rendering);
            CompositionTarget.Rendering += new EventHandler(Update_Tick);



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

            Paths.ResourcePath = tempString + @"_Resources\";
            Paths.MeshPath = tempString + @"_Resources\Mesh\";
            Paths.TexturePath = tempString + @"_Resources\Texture\";
            Paths.DataPath = tempString + @"_Resources\Datas\";
            Paths.HierarchyDataPath = tempString + @"_Resources\Datas\HierarchyData\";
            Paths.NavMeshData = tempString + @"_Resources\Datas\NavMeshData\";
            Paths.SystemPath = tempString + @"_Resources\System\";
            Paths.MapDataPath = tempString + @"_Resources\Datas\MapData\";
            Paths.BackupPath = tempString + @"_Resources\Backup\";
            Paths.AssetPath = tempString + @"_Resources\Assets\";
            Paths.SceneDataPath = tempString + @"_Resources\Datas\SceneData\";
            Paths.TerrainDataPath = tempString + @"_Resources\Datas\TerrainData\";

            frameRateCalculator = new FrameRateCalculator();
            cameraController = new CameraController(this);
            gameObjectController = new GameObjectController(this);

            Keyboard.AddKeyDownHandler(this, OnKeyDown);

            SimilarVTX.IsChecked = true;


            
            bWindowInit = true;
        }
        private void LateInitialize()
        {
            ProjectViewInit();
            bLateInit = true;
        }
    }
}
