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
        MapObject,
        NavMesh
    }
    public enum EDataType
    {
        Hierarchy,
        Map,
        NavMesh,
        Scene,

    }
    public enum EKeyState
    {
        Down,
        Up,
        Left,
        Right,
        LeftShift,
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
    public enum EMapGroup
    {
        Group1,
        Group2,
        Group3,
        Group4,
        Group5,
        Group6,
        Group7,
        Group8,
        Group9,
    }
}
