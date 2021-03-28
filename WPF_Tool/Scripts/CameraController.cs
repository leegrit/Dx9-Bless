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
    public class CameraController
    {
        private bool m_bRightButtonClicked = false;
        private bool m_bWheelClicked = false;
        private bool m_bMouseMoving = false;

        private Vector2 m_clickedPos;
        private Vector2 m_clickedWindowPos;
        private Vector2 m_lastPos;

        private Vector3 m_cameraLastPos;
        private Vector3 m_cameraLastRot;
        private float m_deltaTime;
        //public static EKeyInputStatus[] m_currentKeyState = new EKeyInputStatus[4] { EKeyInputStatus.Up, EKeyInputStatus.Up, EKeyInputStatus.Up, EKeyInputStatus.Up};
        private EKeyInputStatus[] m_currentKeyState = new EKeyInputStatus[5] { EKeyInputStatus.Up, EKeyInputStatus.Up, EKeyInputStatus.Up, EKeyInputStatus.Up, EKeyInputStatus.Up};
        private DependencyObject m_dependencyObject;

        private float m_moveSpeed = 10;
        private float m_fastSpeed = 30;

        private float m_wheelMoveSpeed = 0.1f;
        private float m_wheelFastSpeed = 0.5f;



       
        public CameraController(DependencyObject obj)
        {
            m_dependencyObject = obj;
            Point mousePos = Mouse.GetPosition((IInputElement)obj);
            m_lastPos.x = (float)mousePos.X;
            m_lastPos.y = (float)mousePos.Y;
            Mouse.AddMouseMoveHandler(obj, OnMouseMove);
            Mouse.AddMouseUpHandler(obj, OnMouseUp);
            Keyboard.AddKeyDownHandler(obj, OnKeyDown);
            Keyboard.AddKeyUpHandler(obj, OnKeyUp);
        }
        ~CameraController()
        {
            Mouse.RemoveMouseMoveHandler(m_dependencyObject, OnMouseMove);
        }

        public void Update(float deltaTime)
        {
            m_deltaTime = deltaTime;
            Vector3 movePos;
            movePos.x = 0;
            movePos.y = 0;
            movePos.z = 0;
            if (m_bRightButtonClicked)
            {
                if(ToolManager.ToolMode != EToolMode.NavMeshTool)
                    ToolManager.ToolMode = EToolMode.ViewTool;
                if (m_currentKeyState[(int)EKeyState.Down] == EKeyInputStatus.Down)
                {
                    if(m_currentKeyState[(int)EKeyState.LeftShift] == EKeyInputStatus.Down)
                    {
                        movePos.z -= m_fastSpeed * deltaTime;
                    }
                    else
                        movePos.z -= m_moveSpeed * deltaTime;
                }
                if (m_currentKeyState[(int)EKeyState.Up] == EKeyInputStatus.Down)
                {
                    if (m_currentKeyState[(int)EKeyState.LeftShift] == EKeyInputStatus.Down)
                    {
                        movePos.z += m_fastSpeed * deltaTime;
                    }
                    else
                        movePos.z += m_moveSpeed * deltaTime;

                }
                if (m_currentKeyState[(int)EKeyState.Right] == EKeyInputStatus.Down)
                {
                    if (m_currentKeyState[(int)EKeyState.LeftShift] == EKeyInputStatus.Down)
                    {
                        movePos.x += m_fastSpeed * deltaTime;
                    }
                    else
                        movePos.x += m_moveSpeed * deltaTime;

                }
                if (m_currentKeyState[(int)EKeyState.Left] == EKeyInputStatus.Down)
                {
                    if (m_currentKeyState[(int)EKeyState.LeftShift] == EKeyInputStatus.Down)
                    {
                        movePos.x -= m_fastSpeed * deltaTime;
                    }
                    else
                        movePos.x -= m_moveSpeed * deltaTime;

                }
            }

            Externs.AdjustEditCameraPos(movePos.x, 0, movePos.z);
        }
        public void OnMouseUp(object sender, MouseButtonEventArgs e)
        {
            if (e.ChangedButton == MouseButton.Middle)
            {
                m_bWheelClicked = false;
            }
            if (e.ChangedButton == MouseButton.Right)
            {
                m_bRightButtonClicked = false;
            }

        }
        public void OnMouseDown(object sender, EventArgs e)
        {
           
        }
        public void OnMouseMove(object sender, EventArgs e)
        {
            /* Rotation */
            if (m_bRightButtonClicked)
            {
                if (ToolManager.ToolMode != EToolMode.NavMeshTool)
                    ToolManager.ToolMode = EToolMode.ViewTool;

                Point point = Mouse.GetPosition((IInputElement)m_dependencyObject);
                Vector2 curPos;
                curPos.x = (float)point.X;
                curPos.y = (float)point.Y;
                Vector2 result =curPos - m_clickedPos;


                result.x = result.x * 0.3f; // 속도 조절
                result.y = result.y * 0.3f; // 속도 조절

                Vector3 rot;
                rot.x =  m_cameraLastRot.x;
                rot.y = m_cameraLastRot.y;
                rot.z = m_cameraLastRot.z;

                rot.y = m_cameraLastRot.y + result.x;
                rot.x = m_cameraLastRot.x + (result.y);

                Externs.SetEditCameraRot(rot.x, rot.y, rot.z);
                /*
                Vector3 rot;
                rot.x = 0;
                rot.y = 0;
                rot.z = 0;

                Point point = Mouse.GetPosition((IInputElement)m_dependencyObject);
                Vector2 curPos;
                curPos.x = (float)point.X;
                curPos.y = (float)point.Y;
                Vector2 result = m_lastPos - curPos;
                m_lastPos = curPos;
                result = Vector2.Normalize(result);
                rot.y = result.x;
                rot.x = result.y;
                Externs.AdjustEditCameraRot(rot.x, -rot.y, rot.z);
                */




            }
            else if (m_bWheelClicked)
            {
                if (ToolManager.ToolMode != EToolMode.NavMeshTool)
                    ToolManager.ToolMode = EToolMode.HandTool;
                Point point = Mouse.GetPosition((IInputElement)m_dependencyObject);
                Vector2 curPos;
                curPos.x = (float)point.X;
                curPos.y = (float)point.Y;

                Vector2 result = curPos - m_clickedPos;

                if (m_currentKeyState[(int)EKeyState.LeftShift] == EKeyInputStatus.Down)
                {
                    result.x = result.x * m_wheelFastSpeed; // 속도 조절
                    result.y = result.y * m_wheelFastSpeed; // 속도 조절
                }
                else
                {
                    result.x = result.x * m_wheelMoveSpeed; // 속도 조절
                    result.y = result.y * m_wheelMoveSpeed; // 속도 조절
                }

                Vector3 pos;
                pos.x = m_cameraLastPos.x;
                pos.y = m_cameraLastPos.y;
                pos.z = m_cameraLastPos.z;

                pos.y = m_cameraLastPos.y - result.y;
                pos.x = m_cameraLastPos.x + (result.x);

                Externs.SetEditCameraPos(pos.x, pos.y, pos.z);
                /*
                Vector2 pos;
                pos.x = 0;
                pos.y = 0;

                Point point = Mouse.GetPosition((IInputElement)m_dependencyObject);
                Vector2 curPos;
                curPos.x = (float)point.X;
                curPos.y = (float)point.Y;
                Vector2 result = curPos - m_lastPos;
                m_lastPos = curPos;
                result = Vector2.Normalize(result);
                Externs.AdjustEditCameraPos(-result.x, result.y , 0);
                */
            }
        }
        public void OnRightButtonDownInDxRect(float xPos, float yPos)
        {
            if (m_bWheelClicked) return;
            m_bRightButtonClicked = true;
            Externs.GetEditCameraRot(ref m_cameraLastRot);
            Vector2 pos = default(Vector2);
            pos.x = xPos;
            pos.y = yPos;
            Point p = Mouse.GetPosition((IInputElement)m_dependencyObject);
            m_clickedPos.x = (float)p.X;
            m_clickedPos.y = (float)p.Y;


        }
        public void OnRightButtonUpInDxRect()
        {
            m_bRightButtonClicked = false;

        }

        public void OnWheelDownInDxRect(float xPos, float yPos)
        {
            if (m_bRightButtonClicked) return;
            m_bWheelClicked = true;
            Vector2 pos = default(Vector2);
            pos.x = xPos;
            pos.y = yPos;

            Point p = Mouse.GetPosition((IInputElement)m_dependencyObject);
            m_clickedPos.x = (float)p.X;
            m_clickedPos.y = (float)p.Y;

            Externs.GetEditCameraPos(ref m_cameraLastPos);

            Point point = Mouse.GetPosition((IInputElement)m_dependencyObject);
            m_clickedWindowPos.x = (float)point.X;
            m_clickedWindowPos.y = (float)point.Y;
        }
        public void OnWheelUpInDxRect()
        {
            m_bWheelClicked = false;
        }
        public void OnKeyDown(object sender, KeyEventArgs e)
        {
            switch (e.Key)
            {
                case Key.W:
                    m_currentKeyState[(int)EKeyState.Up] = EKeyInputStatus.Down;
                    break;
                case Key.S:
                    m_currentKeyState[(int)EKeyState.Down] = EKeyInputStatus.Down;
                    break;
                case Key.A:
                    m_currentKeyState[(int)EKeyState.Left] = EKeyInputStatus.Down;
                    break;
                case Key.D:
                    m_currentKeyState[(int)EKeyState.Right] = EKeyInputStatus.Down;
                    break;
                case Key.LeftShift:
                    m_currentKeyState[(int)EKeyState.LeftShift] = EKeyInputStatus.Down;
                    break;
            }
        }
        public void OnKeyUp(object sender, KeyEventArgs e)
        {
            switch (e.Key)
            {
                case Key.W:
                    m_currentKeyState[(int)EKeyState.Up] = EKeyInputStatus.Up;
                    break;
                case Key.S:
                    m_currentKeyState[(int)EKeyState.Down] = EKeyInputStatus.Up;
                    break;
                case Key.A:
                    m_currentKeyState[(int)EKeyState.Left] = EKeyInputStatus.Up;
                    break;
                case Key.D:
                    m_currentKeyState[(int)EKeyState.Right] = EKeyInputStatus.Up;
                    break;
                case Key.LeftShift:
                    m_currentKeyState[(int)EKeyState.LeftShift] = EKeyInputStatus.Up;
                    break;
            }
        }
    }
}
