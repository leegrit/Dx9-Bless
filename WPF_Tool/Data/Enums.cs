using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace WPF_Tool.Data
{
    public enum GameObjectType
    {
        Mesh,
        NavMesh
    }
    public enum EKeyState
    {
        Down,
        Up,
        Left,
        Right,
    }
    public enum EKeyInputStatus
    {
        Up,
        Down,
        Press,
    }

    public enum ELogType
    {
        Log,
        Warning,
        Error,
    }

    public enum ETag
    {
        Default,
        UI,
        Player,
        Enemy,
    }
    public enum ELayer
    {
        Default,
        UI,
        Player,
        Enemy,
    }
    public enum EStatic
    {
        Nothing,
        Navigation,
    }

    public enum EToolMode
    {
        ViewTool,
        HandTool,
        NavMeshTool,
    }

    public enum ECellOption
    {
        NORMAL,
        TRIGGER,
        EVENT,
    }
    public enum ECellEditMode
    {
        Similar, // 주변 같이
        Selected, // 선택한 것만
    }
}
