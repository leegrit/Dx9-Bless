using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace WPF_Tool.Utility
{
    public class UIDGenerator
    {
        public static string GetUniqueID()
        {
            return String.Format("{0:d9}", (DateTime.Now.Ticks / 10) % 1000000000);
        }
    }
}
