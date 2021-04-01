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

        private void Solid_Selected(object sender, RoutedEventArgs e)
        {
            if (bWindowInit)
                Externs.SetSolidMode();
        }

        private void WireFrame_Selected(object sender, RoutedEventArgs e)
        {
            if (bWindowInit)
                Externs.SetWireFrameMode();
        }

        private void Dx_MouseMove(object sender, MouseEventArgs e)
        {
            Point mousePos = e.GetPosition((IInputElement)sender);

            double x = mousePos.X;
            double y = mousePos.Y;

            DXMousePosX.Text = x.ToString("N3");
            DXMousePosY.Text = y.ToString("N3");

            if (Keyboard.IsKeyDown(Key.LeftCtrl) && ToolManager.ToolMode != EToolMode.NavMeshTool)
            {
                ToolManager.ToolMode = EToolMode.PickTool;
            }
        }

        private void Dx_MouseDown(object sender, MouseButtonEventArgs e)
        {
            Keyboard.Focus(ViewToolButton);


            Point mousePos = e.GetPosition((IInputElement)sender);

            double x = mousePos.X;
            double y = mousePos.Y;

            double xRatio = x / imgelt.ActualWidth;
            double yRatio = y / imgelt.ActualHeight;

            double actualX = d3dimg.Width * xRatio;
            double actualY = d3dimg.Height * yRatio;

            

            if (e.ChangedButton == MouseButton.Left)
            {
                if (ToolManager.ToolMode == EToolMode.NavMeshTool)
                {


                    Vector3 pickedPos = default(Vector3);
                    bool isHit = Externs.PickNavMesh((float)actualX, (float)actualY, (int)cellOption, ref pickedPos);
                    if (isHit)
                    {
                        bool isNewPrim = false;
                        isNewPrim = IsNewPrimitive();
                        if (isNewPrim == true)
                        {
                            TreeViewItem primItem = new TreeViewItem();
                            primItem.Header = "NavPrimitive_" + NavPrimIndex.ToString();
                            primItem.Uid = NavPrimIndex.ToString();
                            primItem.Selected += NavPrimSelected;
                            NavPrimIndex++;


                            CellList.Items.Add(primItem);
                        }

                        TreeViewItem cellItem = new TreeViewItem();
                        cellItem.Header = "Cell_" + cellIndex;
                        cellItem.Uid = cellIndex.ToString();
                        cellItem.Selected += CellSelected;
                        AddCell(pickedPos);
                        selectedHierarchy.navMeshData.cellCount++;
                        int primCount = CellList.Items.Count;

                        ((TreeViewItem)CellList.Items[primCount - 1]).Items.Add(cellItem);



                        DebugLog("NavMesh Picked X : " + pickedPos.x + ", " + " Y : " + pickedPos.y + ", Z : " + pickedPos.z, ELogType.Log);
                    }
                }
                else if (ToolManager.ToolMode == EToolMode.PickTool && Keyboard.IsKeyDown(Key.LeftCtrl))
                {
                    Vector3 pickedPos = default(Vector3);
                    int temp = 0;
                    bool isHit = Externs.PickGameObject((float)actualX, (float)actualY, ref temp, ref pickedPos);
                    if (isHit)
                    {
                        HierarchyData select = selectedHierarchy;

                        select.gameObjectData.transform.position = pickedPos;

                        Externs.InsertGameData(ref select.gameObjectData);
                    }

                }
                else
                {
                    int resultIndex = -1;
                    Vector3 vec = default(Vector3);
                    bool isPicked = Externs.PickGameObject((float)actualX, (float)actualY, ref resultIndex, ref vec );
                    if (isPicked == true)
                    {
                        SelectedIndex = resultIndex;
                    }

                }
            }
            if (e.ChangedButton == MouseButton.Middle && e.ButtonState == MouseButtonState.Pressed)
            {
                cameraController.OnWheelDownInDxRect((float)mousePos.X, (float)mousePos.Y);
            }
            else if (e.ChangedButton == MouseButton.Right && e.ButtonState == MouseButtonState.Pressed)
            {
                cameraController.OnRightButtonDownInDxRect((float)mousePos.X, (float)mousePos.Y);
            }


        }

        private void Dx_MouseUp(object sender, MouseButtonEventArgs e)
        {
            Point mousePos = e.GetPosition((IInputElement)sender);

            double x = mousePos.X;
            double y = mousePos.Y;
            double xRatio = x / imgelt.ActualWidth;
            double yRatio = y / imgelt.ActualHeight;

            double actualX = d3dimg.Width * xRatio;
            double actualY = d3dimg.Height * yRatio;


            if (e.ChangedButton == MouseButton.Middle)
            {
                cameraController.OnWheelUpInDxRect();
            }
            else if (e.ChangedButton == MouseButton.Right)
            {
                cameraController.OnRightButtonUpInDxRect();
            }

        }


    }
}
