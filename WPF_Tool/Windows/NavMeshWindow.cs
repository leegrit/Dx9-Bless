
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

        private void CellSelected(object sender, RoutedEventArgs e)
        {
            TreeViewItem item = sender as TreeViewItem;
            //CellDataGroup.IsEnabled = true;
            CellData cellData = default(CellData);
            bool bFind = false;
            foreach (var data in NavMeshManager.CellDatas)
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
