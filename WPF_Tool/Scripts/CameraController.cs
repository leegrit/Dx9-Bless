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
        private float m_deltaTime;
        //public static EKeyInputStatus[] m_currentKeyState = new EKeyInputStatus[4] { EKeyInputStatus.Up, EKeyInputStatus.Up, EKeyInputStatus.Up, EKeyInputStatus.Up};
        private EKeyInputStatus[] m_currentKeyState = new EKeyInputStatus[4] { EKeyInputStatus.Up, EKeyInputStatus.Up, EKeyInputStatus.Up, EKeyInputStatus.Up };
        private DependencyObject m_dependencyObject;

        private float m_moveSpeed = 5;

        private int[] a = new int[4];
        private EKeyInputStatus[] aa = new EKeyInputStatus[4];
       
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
                if (m_currentKeyState[(int)EKeyState.Down] == EKeyInputStatus.Down)
                {
                    movePos.z -= m_moveSpeed * deltaTime;
                }
                if (m_currentKeyState[(int)EKeyState.Up] == EKeyInputStatus.Down)
                {
                    movePos.z += m_moveSpeed * deltaTime;
                }
                if (m_currentKeyState[(int)EKeyState.Right] == EKeyInputStatus.Down)
                {
                    movePos.x += m_moveSpeed * deltaTime;
                }
                if (m_currentKeyState[(int)EKeyState.Left] == EKeyInputStatus.Down)
                {
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
            if (m_bRightButtonClicked)
            {
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
                Externs.AdjustEditCameraRot(rot.x, rot.y, rot.z);
            }
            else if (m_bWheelClicked)
            {
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
                result.x = 0;
                Externs.AdjustEditCameraPos(result.x, result.y , 0);
            }
        }
        public void OnRightButtonDownInDxRect(float xPos, float yPos)
        {
            if (m_bWheelClicked) return;
            m_bRightButtonClicked = true;
            Vector2 pos = default(Vector2);
            pos.x = xPos;
            pos.y = yPos;
            m_clickedPos = pos;

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
            m_clickedPos = pos;

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
            }
        }
    }
}
