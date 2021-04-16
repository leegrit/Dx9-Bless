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
using System.Windows.Controls;
using System.Windows;
using System.Linq;


namespace WPF_Tool
{
    public partial class MainWindow
    {
        private void BTN_UITextureLoad(object sender, RoutedEventArgs e)
        {
            OpenFileDialog ofdlg = new OpenFileDialog();
            {
                // 기본 폴더
                ofdlg.InitialDirectory = Paths.AssetPath;
                ofdlg.CheckFileExists = true; // 파일 존재여부 확인
                ofdlg.CheckPathExists = true; // 폴더 존재여부 확인

                // 파일 열기(값의 유무 확인)
                if (ofdlg.ShowDialog().GetValueOrDefault())
                {
                    string filePath = ofdlg.FileName.Substring(Paths.ResourcePath.Count());

                    int index = ofdlg.FileName.LastIndexOf("\\");
                    string onlyName = ofdlg.FileName.Substring(index + 1);
                    int extIndex = onlyName.LastIndexOf(".");
                    string ext = onlyName.Substring(extIndex);

                    UITextureName.Text = onlyName;

                    selectedHierarchy.uiData.textureFilePath = filePath;
                    Externs.InsertUIData(ref selectedHierarchy.uiData);
                    ShowInspector(selectedHierarchy);
                }
            }
        }
    }
}
