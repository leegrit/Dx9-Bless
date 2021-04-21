using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using WPF_Tool.Math;
using WPF_Tool.Data;
using WPF_Tool;
using System.Windows.Input;
using System.Windows;
using WPF_Tool.Utility;


namespace WPF_Tool.Scripts
{
    public class GameObjectController
    {
        private enum EClickState
        {
            PosX,
            PosY,
            PosZ,
            RotX,
            RotY,
            RotZ,
            ScaleX,
            ScaleY,
            ScaleZ,
            None,
        }


        EClickState clickState = EClickState.None;

        private Vector2 clickedPos;
        private Vector3 lastPos;
        private Vector3 lastRot;
        private Vector3 lastScale;
        private HierarchyData clickedData;
        private float moveSpeed = 0.1f;
        private float fastSpeed = 0.3f;
        DependencyObject dependencyObject;
        public GameObjectController(DependencyObject obj)
        {
            dependencyObject = obj;
            Mouse.AddMouseMoveHandler(obj, OnMouseMove);
            Mouse.AddMouseUpHandler(obj, OnMouseUp);
        }

        public void SetMoveSpeed(float speed)
        {
            moveSpeed = speed;
        }


        public void PickPositionX(HierarchyData data)
        {
            clickState = EClickState.PosX;


            Point point = Mouse.GetPosition((IInputElement)dependencyObject);
            clickedPos.x = (float)point.X;
            clickedPos.y = (float)point.Y;
            lastPos = data.gameObjectData.transform.position;
            lastRot = data.gameObjectData.transform.rotation;
            lastScale = data.gameObjectData.transform.scale;
            clickedData = data;

        }
        public void PickPositionY(HierarchyData data)
        {
            clickState = EClickState.PosY;

            Point point = Mouse.GetPosition((IInputElement)dependencyObject);
            clickedPos.x = (float)point.X;
            clickedPos.y = (float)point.Y;
            lastPos = data.gameObjectData.transform.position;
            lastRot = data.gameObjectData.transform.rotation;
            lastScale = data.gameObjectData.transform.scale;
            clickedData = data;
        }
        public void PickPositionZ(HierarchyData data)
        {
            clickState = EClickState.PosZ;

            Point point = Mouse.GetPosition((IInputElement)dependencyObject);
            clickedPos.x = (float)point.X;
            clickedPos.y = (float)point.Y;
            lastPos = data.gameObjectData.transform.position;
            lastRot = data.gameObjectData.transform.rotation;
            lastScale = data.gameObjectData.transform.scale;
            clickedData = data;

        }
        public void PickRotationX(HierarchyData data)
        {
            clickState = EClickState.RotX;

            Point point = Mouse.GetPosition((IInputElement)dependencyObject);
            clickedPos.x = (float)point.X;
            clickedPos.y = (float)point.Y;
            lastPos = data.gameObjectData.transform.position;
            lastRot = data.gameObjectData.transform.rotation;
            lastScale = data.gameObjectData.transform.scale;
            clickedData = data;
        }
        public void PickRotationY(HierarchyData data)
        {
            clickState = EClickState.RotY;

            Point point = Mouse.GetPosition((IInputElement)dependencyObject);
            clickedPos.x = (float)point.X;
            clickedPos.y = (float)point.Y;
            lastPos = data.gameObjectData.transform.position;
            lastRot = data.gameObjectData.transform.rotation;
            lastScale = data.gameObjectData.transform.scale;
            clickedData = data;
        }
        public void PickRotationZ(HierarchyData data)
        {
            clickState = EClickState.RotZ;

            Point point = Mouse.GetPosition((IInputElement)dependencyObject);
            clickedPos.x = (float)point.X;
            clickedPos.y = (float)point.Y;
            lastPos = data.gameObjectData.transform.position;
            lastRot = data.gameObjectData.transform.rotation;
            lastScale = data.gameObjectData.transform.scale;
            clickedData = data;
        }
        public void PickScaleX(HierarchyData data)
        {
            clickState = EClickState.ScaleX;

            Point point = Mouse.GetPosition((IInputElement)dependencyObject);
            clickedPos.x = (float)point.X;
            clickedPos.y = (float)point.Y;
            lastPos = data.gameObjectData.transform.position;
            lastRot = data.gameObjectData.transform.rotation;
            lastScale = data.gameObjectData.transform.scale;
            clickedData = data;
        }
        public void PickScaleY(HierarchyData data)
        {
            clickState = EClickState.ScaleY;

            Point point = Mouse.GetPosition((IInputElement)dependencyObject);
            clickedPos.x = (float)point.X;
            clickedPos.y = (float)point.Y;
            lastPos = data.gameObjectData.transform.position;
            lastRot = data.gameObjectData.transform.rotation;
            lastScale = data.gameObjectData.transform.scale;
            clickedData = data;
        }
        public void PickScaleZ(HierarchyData data)
        {
            clickState = EClickState.ScaleZ;

            Point point = Mouse.GetPosition((IInputElement)dependencyObject);
            clickedPos.x = (float)point.X;
            clickedPos.y = (float)point.Y;
            lastPos = data.gameObjectData.transform.position;
            lastRot = data.gameObjectData.transform.rotation;
            lastScale = data.gameObjectData.transform.scale;
            clickedData = data;
        }

        public void OnMouseMove(object sender, EventArgs e)
        {
            if (clickState == EClickState.None)
                return;

            if (clickedData.bFix == true)
                return;


            Point point = Mouse.GetPosition((IInputElement)dependencyObject);
            Vector2 curPos;
            curPos.x = (float)point.X;
            curPos.y = (float)point.Y;

            Vector2 result = curPos - clickedPos;
            // only x 
            result.y = 0;

            // 속도 조절
            if (Keyboard.GetKeyStates(Key.LeftShift) == KeyStates.Down)
            {
                result.x = result.x * fastSpeed;
            }
            else
            {
                result.x = result.x * moveSpeed;

            }


            Vector3 gameObjectPos = lastPos;
            Vector3 gameObjectRot = lastRot;
            Vector3 gameObjectScale = lastScale;



            switch(clickState)
            {
                case EClickState.PosX:
                    gameObjectPos.x = gameObjectPos.x + result.x;
                    break;
                case EClickState.PosY:
                    gameObjectPos.y = gameObjectPos.y + result.x;
                    break;
                case EClickState.PosZ:
                    gameObjectPos.z = gameObjectPos.z + result.x;
                    break;
                case EClickState.RotX:
                    gameObjectRot.x = gameObjectRot.x + result.x;
                    break;
                case EClickState.RotY:
                    gameObjectRot.y = gameObjectRot.y + result.x;
                    break;
                case EClickState.RotZ:
                    gameObjectRot.z = gameObjectRot.z + result.x;
                    break;
                case EClickState.ScaleX:
                    gameObjectScale.x = gameObjectScale.x + result.x;
                    break;
                case EClickState.ScaleY:
                    gameObjectScale.y = gameObjectScale.y + result.x;
                    break;
                case EClickState.ScaleZ:
                    gameObjectScale.z = gameObjectScale.z + result.x;
                    break;
            }

            clickedData.gameObjectData.transform.position = gameObjectPos;
            clickedData.gameObjectData.transform.rotation = gameObjectRot;
            clickedData.gameObjectData.transform.scale = gameObjectScale;

            Externs.InsertGameData(ref clickedData.gameObjectData);
            MainWindow window = dependencyObject as MainWindow;
            window.ShowInspector(clickedData);
        }
        public void OnMouseUp(object sender, EventArgs e)
        {
            clickState = EClickState.None;
        }

    }
}
