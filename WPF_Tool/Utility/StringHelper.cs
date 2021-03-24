using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using WPF_Tool.Data;

namespace WPF_Tool.Utility
{
    class StringHelper
    {
        public  static void ChangeText( GameObjectData data, string change)
        {
           data.name = change;
        }
    }
}
