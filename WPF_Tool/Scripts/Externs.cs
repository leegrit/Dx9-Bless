using System;
using System.Collections.Generic;
using System.Linq;
using System.Runtime.InteropServices;
using System.Text;
using System.Threading.Tasks;
using WPF_Tool.Data;
using WPF_Tool.Math;

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
        public static extern void AddPawn(int index);

        [DllImport("HyEngine.dll")]
        public static extern void AddNavMesh(int index);

        [DllImport("HyEngine.dll")]
        public static extern void InsertGameData(ref GameObjectData data);

        [DllImport("HyEngine.dll")]
        public static extern void InsertMeshData(ref MeshData data);

        [DllImport("HyEngine.dll")]
        public static extern void InsertCellData(ref CellData data, int cellEditMode);

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
        public static extern void GetEditCameraPos(ref Vector3 position);

        [DllImport("HyEngine.dll")]
        public static extern void GetEditCameraRot(ref Vector3 rotation);

        [DllImport("HyEngine.dll")]
        public static extern void SetEditCameraPos(float xPos, float yPos, float zPos);

        [DllImport("HyEngine.dll")]
        public static extern void SetEditCameraRot(float xRot, float yRot, float zRot);


        [DllImport("HyEngine.dll")]
        public static extern void SetSolidMode();

        [DllImport("HyEngine.dll")]
        public static extern void SetWireFrameMode();

        [DllImport("HyEngine.dll")]
        public static extern bool PickNavMesh(float xMousePos, float yMousePos, int cellOption,ref Vector3 pickedPos);

        [DllImport("HyEngine.dll")]
        public static extern void RemoveGameObject(int index);

        [DllImport("HyEngine.dll")]
        public static extern void TranslateToMesh();

        [DllImport("HyEngine.dll")]
        public static extern bool PickGameObject(float xMousePos, float yMousePos, ref int resultIndex, ref Vector3 pickedPos);

        [DllImport("HyEngine.dll")]
        public static extern void AddCell(ref CellData cellData);

        [DllImport("HyEngine.dll")]
        public static extern int GetAnimationCount();

        [DllImport("HyEngine.dll")]
        public static extern void GetAnimationName(ref AnimNameData outString, int index);

        [DllImport("HyEngine.dll")]
        public static extern void SetAnimation(int index);

        [DllImport("HyEngine.dll")]
        public static extern void RemoveNavPrim(int navPrimIndex);
    }
}
