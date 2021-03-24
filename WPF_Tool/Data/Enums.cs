﻿using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace WPF_Tool.Data
{
    public enum GameObjectType
    {
        Mesh,
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
}
