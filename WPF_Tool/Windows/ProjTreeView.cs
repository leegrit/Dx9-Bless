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
    /// <summary>
    /// 이 클래스는 Project의 TreeView 관련 이벤트를 관리한다.
    /// </summary>
    public partial class MainWindow
    {


        Dictionary<string, BitmapSource> IconImages = new Dictionary<string, BitmapSource>();

        private void SLT_Assets(object sender, RoutedEventArgs e)
        {

            TreeViewItem parent = sender as TreeViewItem;
            TreeViewItem selectedItem = new TreeViewItem();


            bool bFind = FindSelectedItemRecursive(out selectedItem, parent);
            //Debug.Assert(bFind);
            // 못찾았을 경우 "Assets" 본인이 선택된 것
            if (bFind == false)
                selectedItem = parent;

            // 선택된 item을 찾았을 경우
            Stack<string> names = new Stack<string>();

            TreeViewItem temp = selectedItem;

            // 우선 본인 header를 넣어준다.
            names.Push(temp.Header.ToString());
            while (temp.Header != parent.Header)
            {
                TreeViewItem p = temp.Parent as TreeViewItem;
                temp = temp.Parent as TreeViewItem;
                names.Push(temp.Header.ToString());
            }

            // 위 반복이 끝나면
            // 아래부터 차례대로 본인->부모->Assets(최상단)
            // 이와같이 문자가 들어가게된다.
            string path = Paths.ResourcePath;

            // 차례대로 path에 넣어준다.
            while (names.Count != 0)
            {
                path = path + names.Pop() + @"\";
            }

            ProjectItems.Children.Clear();

            if (System.IO.Directory.Exists(path))
            {
                System.IO.DirectoryInfo info = new System.IO.DirectoryInfo(path);

                foreach (var folderItem in info.GetDirectories())
                {
                    BitmapSource bitmapSource;
                    bool isExist = false;
                    isExist = IconImages.TryGetValue(folderItem.FullName, out bitmapSource);
                    if (isExist == false)
                    {
                        // 이 경우 폴더
                        Stream imageStreamSource = new FileStream(Paths.SystemPath + @"FolderIcon.png", FileMode.Open, FileAccess.Read, FileShare.Read);
                        PngBitmapDecoder decoder = new PngBitmapDecoder(imageStreamSource, BitmapCreateOptions.PreservePixelFormat, BitmapCacheOption.Default);
                        bitmapSource = decoder.Frames[0];
                    }

                    Image itemImage = new Image();
                    itemImage.Source = bitmapSource;
                    itemImage.Width = 90;
                    itemImage.Height = 70;

                    TextBlock itemText = new TextBlock();
                    itemText.Text = folderItem.Name;
                    itemText.TextAlignment = TextAlignment.Center;
                    itemText.Foreground = Brushes.White;
                    itemText.Width = 90;
                    itemText.Height = 20;

                    StackPanel itemPanel = new StackPanel();
                    itemPanel.VerticalAlignment = VerticalAlignment.Center;
                    itemPanel.HorizontalAlignment = HorizontalAlignment.Center;
                    itemPanel.Children.Add(itemImage);
                    itemPanel.Children.Add(itemText);

                    ProjectItems.Children.Add(itemPanel);
                }
                foreach (var fileItem in info.GetFiles())
                {
                    BitmapSource bitmapSource;
                    if (fileItem.Extension == ".png")
                    {
                        bool isExist = false;
                        isExist = IconImages.TryGetValue(fileItem.FullName, out bitmapSource);
                        if (isExist == false)
                        {
                            Stream imageStreamSource = new FileStream(fileItem.FullName, FileMode.Open, FileAccess.Read, FileShare.Read);
                            PngBitmapDecoder decoder = new PngBitmapDecoder(imageStreamSource, BitmapCreateOptions.PreservePixelFormat, BitmapCacheOption.Default);
                            bitmapSource = decoder.Frames[0];
                            IconImages.Add(fileItem.FullName, bitmapSource);
                        }
                    }
                    else if (fileItem.Extension == ".tga")
                    {
                        bool isExist = false;
                        isExist = IconImages.TryGetValue(fileItem.FullName, out bitmapSource);

                        if (isExist == false)
                        {
                            bitmapSource = default(BitmapSource);
                            System.Drawing.Bitmap bitMap;

                            Paloma.TargaImage tgaImage = new Paloma.TargaImage(fileItem.FullName);
                            bitMap = tgaImage.Image;
                            if (tgaImage.Stride < 3070)
                            {
                                var handle = bitMap.GetHbitmap();


                                bitmapSource = Imaging.CreateBitmapSourceFromHBitmap(handle, IntPtr.Zero, Int32Rect.Empty, BitmapSizeOptions.FromEmptyOptions());
                            }
                            else
                            {
                                Stream imageStreamSource = new FileStream(Paths.SystemPath + "NoImage.png", FileMode.Open, FileAccess.Read, FileShare.Read);
                                PngBitmapDecoder decoder = new PngBitmapDecoder(imageStreamSource, BitmapCreateOptions.PreservePixelFormat, BitmapCacheOption.Default);
                                bitmapSource = decoder.Frames[0];
                            }
                            tgaImage.Dispose();

                            IconImages.Add(fileItem.FullName, bitmapSource);
                        }
                    }
                    else if (fileItem.Extension == ".x" ||
                        fileItem.Extension == ".X" ||
                        fileItem.Extension == ".obj")
                    {
                        bool isExist = false;
                        isExist = IconImages.TryGetValue(fileItem.FullName, out bitmapSource);
                        if (isExist == false)
                        {
                            Stream imageStreamSource = new FileStream(Paths.SystemPath + @"MeshIcon.png", FileMode.Open, FileAccess.Read, FileShare.Read);
                            PngBitmapDecoder decoder = new PngBitmapDecoder(imageStreamSource, BitmapCreateOptions.PreservePixelFormat, BitmapCacheOption.Default);
                            bitmapSource = decoder.Frames[0];

                            IconImages.Add(fileItem.FullName, bitmapSource);
                        }
                    }
                    else if (fileItem.Extension == ".mp3")
                    {
                        bool isExist = false;
                        isExist = IconImages.TryGetValue(fileItem.FullName, out bitmapSource);
                        if (isExist == false)
                        {
                            Stream imageStreamSource = new FileStream(Paths.SystemPath + @"Mp3Icon.png", FileMode.Open, FileAccess.Read, FileShare.Read);
                            PngBitmapDecoder decoder = new PngBitmapDecoder(imageStreamSource, BitmapCreateOptions.PreservePixelFormat, BitmapCacheOption.Default);
                            bitmapSource = decoder.Frames[0];

                            IconImages.Add(fileItem.FullName, bitmapSource);
                        }
                    }
                    else
                    {
                        bool isExist = false;
                        isExist = IconImages.TryGetValue(fileItem.FullName, out bitmapSource);
                        if (isExist == false)
                        {
                            Stream imageStreamSource = new FileStream(Paths.SystemPath + "NoImage.png", FileMode.Open, FileAccess.Read, FileShare.Read);
                            PngBitmapDecoder decoder = new PngBitmapDecoder(imageStreamSource, BitmapCreateOptions.PreservePixelFormat, BitmapCacheOption.Default);
                            bitmapSource = decoder.Frames[0];

                            IconImages.Add(fileItem.FullName, bitmapSource);
                        }
                       
                    }

                    Image itemImage = new Image();
                    itemImage.Source = bitmapSource;
                    itemImage.Width = 90;
                    itemImage.Height = 70;

                    TextBlock itemText = new TextBlock();
                    itemText.Text = fileItem.Name;
                    itemText.TextAlignment = TextAlignment.Center;
                    itemText.Foreground = Brushes.White;
                    itemText.Width = 90;
                    itemText.Height = 20;

                    StackPanel itemPanel = new StackPanel();
                    itemPanel.VerticalAlignment = VerticalAlignment.Center;
                    itemPanel.HorizontalAlignment = HorizontalAlignment.Center;
                    itemPanel.Children.Add(itemImage);
                    itemPanel.Children.Add(itemText);

                    ProjectItems.Children.Add(itemPanel);
                }
            }



        }
        private void SLT_Datas(object sender, RoutedEventArgs e)
        {

            TreeViewItem parent = sender as TreeViewItem;
            TreeViewItem selectedItem = new TreeViewItem();


            bool bFind = FindSelectedItemRecursive(out selectedItem, parent);
            //Debug.Assert(bFind);
            // 못찾았을 경우 "Assets" 본인이 선택된 것
            if (bFind == false)
                selectedItem = parent;

            // 선택된 item을 찾았을 경우
            Stack<string> names = new Stack<string>();

            TreeViewItem temp = selectedItem;

            // 우선 본인 header를 넣어준다.
            names.Push(temp.Header.ToString());
            while (temp.Header != parent.Header)
            {
                TreeViewItem p = temp.Parent as TreeViewItem;
                temp = temp.Parent as TreeViewItem;
                names.Push(temp.Header.ToString());
            }

            // 위 반복이 끝나면
            // 아래부터 차례대로 본인->부모->Assets(최상단)
            // 이와같이 문자가 들어가게된다.
            string path = Paths.ResourcePath;

            // 차례대로 path에 넣어준다.
            while (names.Count != 0)
            {
                path = path + names.Pop() + @"\";
            }

            ProjectItems.Children.Clear();
            if (System.IO.Directory.Exists(path))
            {
                System.IO.DirectoryInfo info = new System.IO.DirectoryInfo(path);

                foreach (var folderItem in info.GetDirectories())
                {
                    BitmapSource bitmapSource;
                    bool isExist = false;
                    isExist = IconImages.TryGetValue(folderItem.FullName, out bitmapSource);
                    if (isExist == false)
                    {
                        // 이 경우 폴더
                        Stream imageStreamSource = new FileStream(Paths.SystemPath + @"FolderIcon.png", FileMode.Open, FileAccess.Read, FileShare.Read);
                        PngBitmapDecoder decoder = new PngBitmapDecoder(imageStreamSource, BitmapCreateOptions.PreservePixelFormat, BitmapCacheOption.Default);
                        bitmapSource = decoder.Frames[0];

                        IconImages.Add(folderItem.FullName, bitmapSource);
                    }

                    Image itemImage = new Image();
                    itemImage.Source = bitmapSource;
                    itemImage.Width = 75;
                    itemImage.Height = 55;

                    TextBlock itemText = new TextBlock();
                    itemText.Text = folderItem.Name;
                    itemText.TextAlignment = TextAlignment.Center;
                    itemText.Foreground = Brushes.White;
                    itemText.Width = 75;
                    itemText.Height = 20;

                    StackPanel itemPanel = new StackPanel();
                    itemPanel.VerticalAlignment = VerticalAlignment.Center;
                    itemPanel.HorizontalAlignment = HorizontalAlignment.Center;
                    itemPanel.Children.Add(itemImage);
                    itemPanel.Children.Add(itemText);

                    ProjectItems.Children.Add(itemPanel);
                }
                foreach (var fileItem in info.GetFiles())
                {
                    BitmapSource bitmapSource;
                    if (fileItem.Extension == ".json")
                    {
                        bool isExist = false;
                        isExist = IconImages.TryGetValue(fileItem.FullName, out bitmapSource);
                        if (isExist == false)
                        {
                            Stream imageStreamSource = new FileStream(Paths.SystemPath + "JsonIcon.png", FileMode.Open, FileAccess.Read, FileShare.Read);
                            PngBitmapDecoder decoder = new PngBitmapDecoder(imageStreamSource, BitmapCreateOptions.PreservePixelFormat, BitmapCacheOption.Default);
                            bitmapSource = decoder.Frames[0];
                            IconImages.Add(fileItem.FullName, bitmapSource);

                        }
                    }
                    else
                    {
                        bool isExist = false;
                        isExist = IconImages.TryGetValue(fileItem.FullName, out bitmapSource);
                        if (isExist == false)
                        {
                            Stream imageStreamSource = new FileStream(Paths.SystemPath + "NoImage.png", FileMode.Open, FileAccess.Read, FileShare.Read);
                            PngBitmapDecoder decoder = new PngBitmapDecoder(imageStreamSource, BitmapCreateOptions.PreservePixelFormat, BitmapCacheOption.Default);
                            bitmapSource = decoder.Frames[0];

                            IconImages.Add(fileItem.FullName, bitmapSource);
                        }

                    }

                    Image itemImage = new Image();
                    itemImage.Source = bitmapSource;
                    itemImage.Width = 75;
                    itemImage.Height = 55;

                    TextBlock itemText = new TextBlock();
                    itemText.Text = fileItem.Name;
                    itemText.TextAlignment = TextAlignment.Center;
                    itemText.Foreground = Brushes.White;
                    itemText.Width = 75;
                    itemText.Height = 20;

                    StackPanel itemPanel = new StackPanel();
                    itemPanel.VerticalAlignment = VerticalAlignment.Center;
                    itemPanel.HorizontalAlignment = HorizontalAlignment.Center;
                    itemPanel.Children.Add(itemImage);
                    itemPanel.Children.Add(itemText);

                    ProjectItems.Children.Add(itemPanel);
                }
            }



        }

        bool FindSelectedItemRecursive(out TreeViewItem outResult, TreeViewItem parent)
        {
            foreach (var it in parent.Items)
            {
                TreeViewItem treeViewIt = it as TreeViewItem;

                // 선택된 아이템인지 확인
                if (treeViewIt.IsSelected == true)
                {
                    outResult = treeViewIt;
                    return true;
                }
                // 아니라면 자식이 있는지 확인한다.
                if (treeViewIt.HasItems)
                {
                    TreeViewItem findIt = new TreeViewItem();
                    bool isFind = FindSelectedItemRecursive(out findIt, treeViewIt);
                    if (isFind)
                    {
                        outResult = findIt;
                        return true;
                    }
                }
            }
            outResult = null;
            return false;
        }
    }
}