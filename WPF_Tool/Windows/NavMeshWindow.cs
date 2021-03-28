
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
        public int NavPrimIndex = 0;
        public int cellIndex = 0;
        public int SelectedCellIndex = 0;
        public ECellOption cellOption = ECellOption.NORMAL;
        public ECellEditMode CellEditMode = ECellEditMode.Similar;
        public List<CellData> CellDatas = new List<CellData>();
        public bool IsNewPrimitive()
        {
            if (CellDatas.Count == 0)
                return true;

            if (CellDatas.Count % 3 == 0)
                return true;

            return false;
        }

        public void AddCell(Vector3 position)
        {
            CellData data = new Data.CellData();
            data.cellIndex = cellIndex++;
            data.position = position;
            data.option = (int)cellOption;
            data.group = 100; // 지금은 사용하지않는다.


            CellDatas.Add(data);
        }

        // cell만 지우기 불가능 
        public void RemovePrim(int primIndex)
        {

            //Externs.RemovePrim
        }

        private void CellSelected(object sender, RoutedEventArgs e)
        {
            TreeViewItem item = sender as TreeViewItem;
            //CellDataGroup.IsEnabled = true;
            CellData cellData = default(CellData);
            bool bFind = false;
            foreach (var data in CellDatas)
            {
                if (item.Uid == data.cellIndex.ToString())
                {
                    cellData = data ;
                    bFind = true;
                    break;
                }
            }
            Debug.Assert(bFind);
            SelectedCellIndex = cellData.cellIndex;
            CellIndex.Text = item.Uid;

            CellOption.SelectedIndex = cellData.option;
            CellPositionX.Text = cellData.position.x.ToString();
            CellPositionY.Text = cellData.position.y.ToString();
            CellPositionZ.Text = cellData.position.z.ToString();
        }

        private void SimilarVTX_Checked(object sender, RoutedEventArgs e)
        {
            CellEditMode = ECellEditMode.Similar;
        }

        private void SelectedVTX_Checked(object sender, RoutedEventArgs e)
        {
            CellEditMode = ECellEditMode.Selected;
        }
    }
}
