using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using WPF_Tool.Data;
using WPF_Tool.Math;

namespace WPF_Tool.Scripts
{
    public class NavMeshManager
    {
        public static bool IsNewPrimitive()
        {
            if (CellDatas.Count == 0)
                return true;

            if (CellDatas.Count % 3 == 0)
                return true;

            return false;
        }

        public static void AddCell(Vector3 position)
        {
            CellData data = new Data.CellData();
            data.cellIndex = CellIndex++;
            data.position = position;
            data.option = (int)CellOption;
            data.group = 100; // 지금은 사용하지않는다.

            CellDatas.Add(data);
        }

        // cell만 지우기 불가능 
        public static void RemovePrim(int primIndex)
        {
            
            //Externs.RemovePrim
        }

        public static int NavPrimIndex = 0;
        public static int CellIndex = 0;
        public static int SelectedCellIndex = 0;
        public static ECellOption CellOption = ECellOption.NORMAL;
        public static ECellEditMode CellEditMode = ECellEditMode.Similar;
        public static List<CellData> CellDatas = new List<CellData>();
    }
}
