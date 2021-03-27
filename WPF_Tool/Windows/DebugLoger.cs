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
        public void DebugLog(string message, ELogType logType = ELogType.Log)
        {
            TextBlock element = new TextBlock();
            switch (logType)
            {
                case ELogType.Log:
                    string logLabel = "[Log] ";
                    element.Text = logLabel + message;
                    element.Foreground = Brushes.White;
                    break;
                case ELogType.Warning:
                    string warningLabel = "[Warning] ";
                    element.Text = warningLabel + message;
                    element.Foreground = Brushes.Yellow;
                    break;
                case ELogType.Error:
                    string errorLabel = "[Error] ";
                    element.Text = errorLabel + message;
                    element.Foreground = Brushes.Red;
                    break;
                default:
                    Debug.Assert(false);
                    break;
            }
            ConsoleMessages.Children.Add(element);
            ConsoleScrollViewer.ScrollToBottom();
        }

    }
}
