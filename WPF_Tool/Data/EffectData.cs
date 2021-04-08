using System;
using System.Collections.Generic;
using System.Linq;
using System.Runtime.InteropServices;
using System.Text;
using System.Threading.Tasks;
using WPF_Tool.Math;

namespace WPF_Tool.Data
{
    [Serializable]
    [StructLayout(LayoutKind.Sequential, Pack = 1)]
    public struct EffectData
    {
        /* 통일성을 위해 index를 받는다. */
        public EffectData(int index)
        {
            effectType = 0;
            
            startPos = default(Vector3);
            startRot = default(Vector3);
            startScale = default(Vector3);

            endPos = default(Vector3);
            endRot = default(Vector3);
            endScale = default(Vector3);

            fadeIn = false;
            fadeOut = false;

            lifeTime = 0;
            loopTime = 0;

            isRepeat = false;
            isBillboard = false;

            diffusePath = "";
            alphaMaskPath = "";

            uvAnimation = false;
            uvDirection = default(Vector3);

            uvMoveSpeed = 0;

            meshPath = "";
            spritePath = "";
        }

        /* EffectType */
        // 0. MeshEffect
        // 1. TextureEffect 
        [MarshalAs(UnmanagedType.I4)]
        public int effectType;

        /* Start */
        [MarshalAs(UnmanagedType.Struct)]
        public Vector3 startPos;
        [MarshalAs(UnmanagedType.Struct)]
        public Vector3 startRot;
        [MarshalAs(UnmanagedType.Struct)]
        public Vector3 startScale;

        /* End */
        [MarshalAs(UnmanagedType.Struct)]
        public Vector3 endPos;
        [MarshalAs(UnmanagedType.Struct)]
        public Vector3 endRot;
        [MarshalAs(UnmanagedType.Struct)]
        public Vector3 endScale;

        /* Fade */
        [MarshalAs(UnmanagedType.I1)]
        public bool fadeIn;
        [MarshalAs(UnmanagedType.I1)]
        public bool fadeOut;

        /* Time */
        [MarshalAs(UnmanagedType.R4)]
        public float lifeTime;
        [MarshalAs(UnmanagedType.R4)]
        public float loopTime;

        /* Repeat */
        [MarshalAs(UnmanagedType.I1)]
        public bool isRepeat;

        /* Billboard */
        [MarshalAs(UnmanagedType.I1)]
        public bool isBillboard;

        /* Textures */
        [MarshalAs(UnmanagedType.ByValTStr, SizeConst = 256)]
        public string diffusePath;
        [MarshalAs(UnmanagedType.ByValTStr, SizeConst = 256)]
        public string alphaMaskPath;

        /* For TextureEffect */
        [MarshalAs(UnmanagedType.I1)]
        public bool uvAnimation;
        [MarshalAs(UnmanagedType.Struct)]
        public Vector3 uvDirection;
        [MarshalAs(UnmanagedType.R4)]
        public float uvMoveSpeed;

        /* For Mesh Effect */
        [MarshalAs(UnmanagedType.ByValTStr, SizeConst = 256)]
        public string meshPath;

        /* For Sprite Effect */
        [MarshalAs(UnmanagedType.ByValTStr, SizeConst = 256)]
        public string spritePath;

    }
}
