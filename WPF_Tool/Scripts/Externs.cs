using System;
using System.Collections.Generic;
using System.Linq;
using System.Runtime.InteropServices;
using System.Text;
using System.Threading.Tasks;
using WPF_Tool.Data;

namespace WPF_Tool.Scripts
{
    public class Externs
    {
        [DllImport("HyEngine.dll")]
        public static extern void Initialize();

        [DllImport("HyEngine.dll")]
        public static extern void Destroy();

        [DllImport("HyEngine.dll")]
        public  static extern void GetBackBuffer(out IntPtr pSurface);

        [DllImport("HyEngine.dll")]
        public static extern void Update();

        [DllImport("HyEngine.dll")]
        public static extern void Render();

        [DllImport("HyEngine.dll")]
        public static extern void AddGameObject(int index);

        [DllImport("HyEngine.dll")]
        public static extern void InsertGameData(ref GameObjectData data);

        [DllImport("HyEngine.dll")]
        public static extern void InsertMeshData(ref MeshData data);

        [DllImport("HyEngine.dll")]
        public static extern void SelectEditObject(int index);

        [DllImport("HyEngine.dll")]
        public static extern void ActiveEditObject();

        [DllImport("HyEngine.dll")]
        public static extern void InactiveEditObject();

        [DllImport("HyEngine.dll")]
        public static extern void AdjustEditCameraPos(float xPos, float yPos, float zPos);

        [DllImport("HyEngine.dll")]
        public static extern void AdjustEditCameraRot(float xRot, float yRot, float zRot);


        [DllImport("HyEngine.dll")]
        public static extern void SetSolidMode();

        [DllImport("HyEngine.dll")]
        public static extern void SetWireFrameMode();
    }
}
