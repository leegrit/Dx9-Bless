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
        private void EffectType_Selected(object sender, RoutedEventArgs e)
        {
            if (bWindowInit == false)
                return;
            ComboBox item = sender as ComboBox;
            int comboBoxIndex = item.SelectedIndex;

            selectedHierarchy.effectData.effectType = comboBoxIndex;

            Externs.InsertEffectData(ref selectedHierarchy.effectData);
        }
        private void BTN_EffectMeshFile(object sender, RoutedEventArgs e)
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

                    EffectMeshFilePath.Text = onlyName;

                    selectedHierarchy.effectData.meshPath = filePath;
                    Externs.InsertEffectData(ref selectedHierarchy.effectData);
                    ShowInspector(selectedHierarchy);
                }
            }
        }
        private void BTN_EffectAlbedoFile(object sender, RoutedEventArgs e)
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

                    EffectAlbedoFilePath.Text = onlyName;

                    selectedHierarchy.effectData.diffusePath = filePath;
                    Externs.InsertEffectData(ref selectedHierarchy.effectData);
                    ShowInspector(selectedHierarchy);
                }
            }
        }
        private void BTN_EffectAlphaFile(object sender, RoutedEventArgs e)
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

                    EffectAlphaFilePath.Text = onlyName;

                    selectedHierarchy.effectData.alphaMaskPath = filePath;
                    Externs.InsertEffectData(ref selectedHierarchy.effectData);
                    ShowInspector(selectedHierarchy);
                }
            }
        }
        private void BTN_EffectSpriteFile(object sender, RoutedEventArgs e)
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

                    EffectSpriteFilePath.Text = onlyName;

                    selectedHierarchy.effectData.spritePath = filePath;
                    Externs.InsertEffectData(ref selectedHierarchy.effectData);
                    ShowInspector(selectedHierarchy);
                }
            }
        }
        private void EffectFadeIn_Checked(object sender, RoutedEventArgs e)
        {
            CheckBox item = sender as CheckBox;

            selectedHierarchy.effectData.fadeIn = (bool)item.IsChecked;
            Externs.InsertEffectData(ref selectedHierarchy.effectData);
        }
        private void EffectFadeOut_Checked(object sender, RoutedEventArgs e)
        {
            CheckBox item = sender as CheckBox;

            selectedHierarchy.effectData.fadeOut = (bool)item.IsChecked;
            Externs.InsertEffectData(ref selectedHierarchy.effectData);
        }

        private void EffectRepeat_Checked(object sender, RoutedEventArgs e)
        {
            CheckBox item = sender as CheckBox;

            selectedHierarchy.effectData.isRepeat = (bool)item.IsChecked;
            Externs.InsertEffectData(ref selectedHierarchy.effectData);
        }
        private void EffectBillboard_Checked(object sender, RoutedEventArgs e)
        {
            CheckBox item = sender as CheckBox;

            selectedHierarchy.effectData.isBillboard = (bool)item.IsChecked;
            Externs.InsertEffectData(ref selectedHierarchy.effectData);
        }
        private void EffectUVAnimation_Checked(object sender, RoutedEventArgs e)
        {
            CheckBox item = sender as CheckBox;

            selectedHierarchy.effectData.uvAnimation = (bool)item.IsChecked;
            Externs.InsertEffectData(ref selectedHierarchy.effectData);
        }

        #region TextChanged
        private void EffectUVDirectionX_TextChanged(object sender, TextChangedEventArgs e)
        {
            if (!bWindowInit)
                return;
            TextBox item = sender as TextBox;
            float result;
            bool isSucceeded =  float.TryParse(item.Text, out result);

            if (isSucceeded == false) return;

            selectedHierarchy.effectData.uvDirection.x = result;

            Externs.InsertEffectData(ref selectedHierarchy.effectData);
        }
        private void EffectUVDirectionY_TextChanged(object sender, TextChangedEventArgs e)
        {
            if (!bWindowInit)
                return;
            TextBox item = sender as TextBox;
            float result;
            bool isSucceeded = float.TryParse(item.Text, out result);

            if (isSucceeded == false) return;

            selectedHierarchy.effectData.uvDirection.y = result;

            Externs.InsertEffectData(ref selectedHierarchy.effectData);
        }
        private void EffectUVDirectionZ_TextChanged(object sender, TextChangedEventArgs e)
        {
            if (!bWindowInit)
                return;
            TextBox item = sender as TextBox;
            float result;
            bool isSucceeded = float.TryParse(item.Text, out result);

            if (isSucceeded == false) return;

            selectedHierarchy.effectData.uvDirection.z = result;

            Externs.InsertEffectData(ref selectedHierarchy.effectData);
        }

        private void EffectLifeTime_TextChanged(object sender, TextChangedEventArgs e)
        {
            if (!bWindowInit)
                return;
            TextBox item = sender as TextBox;
            float result;
            bool isSucceeded = float.TryParse(item.Text, out result);

            if (isSucceeded == false) return;

            selectedHierarchy.effectData.lifeTime = result;

            Externs.InsertEffectData(ref selectedHierarchy.effectData);
        }
        private void EffectLoopTime_TextChanged(object sender, TextChangedEventArgs e)
        {
            if (!bWindowInit)
                return;
            TextBox item = sender as TextBox;
            float result;
            bool isSucceeded = float.TryParse(item.Text, out result);

            if (isSucceeded == false) return;

            selectedHierarchy.effectData.loopTime = result;

            Externs.InsertEffectData(ref selectedHierarchy.effectData);
        }
        private void EffectBeginPositionX_TextChanged(object sender, TextChangedEventArgs e)
        {
            if (!bWindowInit)
                return;
            TextBox item = sender as TextBox;
            float result;
            bool isSucceeded = float.TryParse(item.Text, out result);

            if (isSucceeded == false) return;

            selectedHierarchy.effectData.startPos.x = result;

            Externs.InsertEffectData(ref selectedHierarchy.effectData);
        }
        private void EffectBeginPositionY_TextChanged(object sender, TextChangedEventArgs e)
        {
            if (!bWindowInit)
                return;
            TextBox item = sender as TextBox;
            float result;
            bool isSucceeded = float.TryParse(item.Text, out result);

            if (isSucceeded == false) return;

            selectedHierarchy.effectData.startPos.y = result;

            Externs.InsertEffectData(ref selectedHierarchy.effectData);
        }
        private void EffectBeginPositionZ_TextChanged(object sender, TextChangedEventArgs e)
        {
            if (!bWindowInit)
                return;
            TextBox item = sender as TextBox;
            float result;
            bool isSucceeded = float.TryParse(item.Text, out result);

            if (isSucceeded == false) return;

            selectedHierarchy.effectData.startPos.z = result;

            Externs.InsertEffectData(ref selectedHierarchy.effectData);
        }
        private void EffectBeginRotationX_TextChanged(object sender, TextChangedEventArgs e)
        {
            if (!bWindowInit)
                return;
            TextBox item = sender as TextBox;
            float result;
            bool isSucceeded = float.TryParse(item.Text, out result);

            if (isSucceeded == false) return;

            selectedHierarchy.effectData.startRot.x = result;

            Externs.InsertEffectData(ref selectedHierarchy.effectData);
        }
        private void EffectBeginRotationY_TextChanged(object sender, TextChangedEventArgs e)
        {
            if (!bWindowInit)
                return;
            TextBox item = sender as TextBox;
            float result;
            bool isSucceeded = float.TryParse(item.Text, out result);

            if (isSucceeded == false) return;

            selectedHierarchy.effectData.startRot.y = result;

            Externs.InsertEffectData(ref selectedHierarchy.effectData);
        }
        private void EffectBeginRotationZ_TextChanged(object sender, TextChangedEventArgs e)
        {
            if (!bWindowInit)
                return;
            TextBox item = sender as TextBox;
            float result;
            bool isSucceeded = float.TryParse(item.Text, out result);

            if (isSucceeded == false) return;

            selectedHierarchy.effectData.startRot.z = result;

            Externs.InsertEffectData(ref selectedHierarchy.effectData);
        }
        private void EffectBeginScaleX_TextChanged(object sender, TextChangedEventArgs e)
        {
            if (!bWindowInit)
                return;
            TextBox item = sender as TextBox;
            float result;
            bool isSucceeded = float.TryParse(item.Text, out result);

            if (isSucceeded == false) return;

            selectedHierarchy.effectData.startScale.x = result;

            Externs.InsertEffectData(ref selectedHierarchy.effectData);
        }
        private void EffectBeginScaleY_TextChanged(object sender, TextChangedEventArgs e)
        {
            if (!bWindowInit)
                return;
            TextBox item = sender as TextBox;
            float result;
            bool isSucceeded = float.TryParse(item.Text, out result);

            if (isSucceeded == false) return;

            selectedHierarchy.effectData.startScale.y = result;

            Externs.InsertEffectData(ref selectedHierarchy.effectData);
        }
        private void EffectBeginScaleZ_TextChanged(object sender, TextChangedEventArgs e)
        {
            if (!bWindowInit)
                return;
            TextBox item = sender as TextBox;
            float result;
            bool isSucceeded = float.TryParse(item.Text, out result);

            if (isSucceeded == false) return;

            selectedHierarchy.effectData.startScale.z = result;

            Externs.InsertEffectData(ref selectedHierarchy.effectData);
        }
        private void EffectEndPositionX_TextChanged(object sender, TextChangedEventArgs e)
        {
            if (!bWindowInit)
                return;
            TextBox item = sender as TextBox;
            float result;
            bool isSucceeded = float.TryParse(item.Text, out result);

            if (isSucceeded == false) return;

            selectedHierarchy.effectData.endPos.x = result;

            Externs.InsertEffectData(ref selectedHierarchy.effectData);
        }
        private void EffectEndPositionY_TextChanged(object sender, TextChangedEventArgs e)
        {
            if (!bWindowInit)
                return;
            TextBox item = sender as TextBox;
            float result;
            bool isSucceeded = float.TryParse(item.Text, out result);

            if (isSucceeded == false) return;

            selectedHierarchy.effectData.endPos.y = result;

            Externs.InsertEffectData(ref selectedHierarchy.effectData);
        }
        private void EffectEndPositionZ_TextChanged(object sender, TextChangedEventArgs e)
        {
            if (!bWindowInit)
                return;
            TextBox item = sender as TextBox;
            float result;
            bool isSucceeded = float.TryParse(item.Text, out result);

            if (isSucceeded == false) return;

            selectedHierarchy.effectData.endPos.z = result;

            Externs.InsertEffectData(ref selectedHierarchy.effectData);
        }
        private void EffectEndRotationX_TextChanged(object sender, TextChangedEventArgs e)
        {
            if (!bWindowInit)
                return;
            TextBox item = sender as TextBox;
            float result;
            bool isSucceeded = float.TryParse(item.Text, out result);

            if (isSucceeded == false) return;

            selectedHierarchy.effectData.endRot.x = result;

            Externs.InsertEffectData(ref selectedHierarchy.effectData);
        }
        private void EffectEndRotationY_TextChanged(object sender, TextChangedEventArgs e)
        {
            if (!bWindowInit)
                return;
            TextBox item = sender as TextBox;
            float result;
            bool isSucceeded = float.TryParse(item.Text, out result);

            if (isSucceeded == false) return;

            selectedHierarchy.effectData.endRot.y = result;

            Externs.InsertEffectData(ref selectedHierarchy.effectData);
        }
        private void EffectEndRotationZ_TextChanged(object sender, TextChangedEventArgs e)
        {
            if (!bWindowInit)
                return;
            TextBox item = sender as TextBox;
            float result;
            bool isSucceeded = float.TryParse(item.Text, out result);

            if (isSucceeded == false) return;

            selectedHierarchy.effectData.endRot.z = result;

            Externs.InsertEffectData(ref selectedHierarchy.effectData);
        }
        private void EffectEndScaleX_TextChanged(object sender, TextChangedEventArgs e)
        {
            if (!bWindowInit)
                return;
            TextBox item = sender as TextBox;
            float result;
            bool isSucceeded = float.TryParse(item.Text, out result);

            if (isSucceeded == false) return;

            selectedHierarchy.effectData.endScale.x = result;

            Externs.InsertEffectData(ref selectedHierarchy.effectData);
        }
        private void EffectEndScaleY_TextChanged(object sender, TextChangedEventArgs e)
        {
            if (!bWindowInit)
                return;
            TextBox item = sender as TextBox;
            float result;
            bool isSucceeded = float.TryParse(item.Text, out result);

            if (isSucceeded == false) return;

            selectedHierarchy.effectData.endScale.y = result;

            Externs.InsertEffectData(ref selectedHierarchy.effectData);
        }
        private void EffectEndScaleZ_TextChanged(object sender, TextChangedEventArgs e)
        {
            if (!bWindowInit)
                return;
            TextBox item = sender as TextBox;
            float result;
            bool isSucceeded = float.TryParse(item.Text, out result);

            if (isSucceeded == false) return;

            selectedHierarchy.effectData.endScale.z = result;

            Externs.InsertEffectData(ref selectedHierarchy.effectData);
        }
        #endregion

    }
}
