﻿using System;
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
        }

        private void Dx_MouseDown(object sender, MouseButtonEventArgs e)
        {



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
                    bool isHit = Externs.PickNavMesh((float)actualX, (float)actualY, (int)NavMeshManager.CellOption, ref pickedPos);
                    if (isHit)
                    {
                        bool isNewPrim = false;
                        isNewPrim = NavMeshManager.IsNewPrimitive();
                        if (isNewPrim == true)
                        {
                            TreeViewItem primItem = new TreeViewItem();
                            primItem.Header = "NavPrimitive_" + NavMeshManager.NavPrimIndex.ToString();
                            primItem.Uid = NavMeshManager.NavPrimIndex.ToString();
                            primItem.Selected += NavPrimSelected;
                            NavMeshManager.NavPrimIndex++;


                            CellList.Items.Add(primItem);
                        }

                        TreeViewItem cellItem = new TreeViewItem();
                        cellItem.Header = "Cell_" + NavMeshManager.CellIndex;
                        cellItem.Uid = NavMeshManager.CellIndex.ToString();
                        cellItem.Selected += CellSelected;
                        NavMeshManager.AddCell(pickedPos);

                        int primCount = CellList.Items.Count;

                        ((TreeViewItem)CellList.Items[primCount - 1]).Items.Add(cellItem);




                        DebugLog("NavMesh Picked X : " + pickedPos.x + ", " + " Y : " + pickedPos.y + ", Z : " + pickedPos.z, ELogType.Log);
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
