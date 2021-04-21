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
        bool isPaste = false;

        public void HotKeyUpdate()
        {
            /* Hot key */
            if (Keyboard.IsKeyDown(Key.LeftCtrl) && Keyboard.IsKeyDown(Key.C))
            {
                /* Copy */
                copyHierarchy = selectedHierarchy;
            }
            // 복사는 누를 때 한번만 수행되어야 한다.
            if (Keyboard.IsKeyDown(Key.LeftCtrl) && Keyboard.IsKeyDown(Key.V) && isPaste == false)
            {
                /* Paste */
                AddHierarchy(new HierarchyData(copyHierarchy));
                isPaste = true;
            }
            if (Keyboard.IsKeyUp(Key.V))
            {
                isPaste = false;
            }

        }
    }
}
