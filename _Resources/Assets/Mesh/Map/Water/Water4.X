xof 0303txt 0032
template ColorRGBA {
 <35ff44e0-6c7c-11cf-8f52-0040333594a3>
 FLOAT red;
 FLOAT green;
 FLOAT blue;
 FLOAT alpha;
}

template ColorRGB {
 <d3e16e81-7835-11cf-8f52-0040333594a3>
 FLOAT red;
 FLOAT green;
 FLOAT blue;
}

template Material {
 <3d82ab4d-62da-11cf-ab39-0020af71e433>
 ColorRGBA faceColor;
 FLOAT power;
 ColorRGB specularColor;
 ColorRGB emissiveColor;
 [...]
}

template TextureFilename {
 <a42790e1-7810-11cf-8f52-0040333594a3>
 STRING filename;
}

template Frame {
 <3d82ab46-62da-11cf-ab39-0020af71e433>
 [...]
}

template Matrix4x4 {
 <f6f23f45-7686-11cf-8f52-0040333594a3>
 array FLOAT matrix[16];
}

template FrameTransformMatrix {
 <f6f23f41-7686-11cf-8f52-0040333594a3>
 Matrix4x4 frameMatrix;
}

template Vector {
 <3d82ab5e-62da-11cf-ab39-0020af71e433>
 FLOAT x;
 FLOAT y;
 FLOAT z;
}

template MeshFace {
 <3d82ab5f-62da-11cf-ab39-0020af71e433>
 DWORD nFaceVertexIndices;
 array DWORD faceVertexIndices[nFaceVertexIndices];
}

template Mesh {
 <3d82ab44-62da-11cf-ab39-0020af71e433>
 DWORD nVertices;
 array Vector vertices[nVertices];
 DWORD nFaces;
 array MeshFace faces[nFaces];
 [...]
}

template MeshNormals {
 <f6f23f43-7686-11cf-8f52-0040333594a3>
 DWORD nNormals;
 array Vector normals[nNormals];
 DWORD nFaceNormals;
 array MeshFace faceNormals[nFaceNormals];
}

template MeshMaterialList {
 <f6f23f42-7686-11cf-8f52-0040333594a3>
 DWORD nMaterials;
 DWORD nFaceIndexes;
 array DWORD faceIndexes[nFaceIndexes];
 [Material <3d82ab4d-62da-11cf-ab39-0020af71e433>]
}

template IndexedColor {
 <1630b820-7842-11cf-8f52-0040333594a3>
 DWORD index;
 ColorRGBA indexColor;
}

template MeshVertexColors {
 <1630b821-7842-11cf-8f52-0040333594a3>
 DWORD nVertexColors;
 array IndexedColor vertexColors[nVertexColors];
}

template Coords2d {
 <f6f23f44-7686-11cf-8f52-0040333594a3>
 FLOAT u;
 FLOAT v;
}

template MeshTextureCoords {
 <f6f23f40-7686-11cf-8f52-0040333594a3>
 DWORD nTextureCoords;
 array Coords2d textureCoords[nTextureCoords];
}

template FVFData {
 <b6e70a0e-8ef9-4e83-94ad-ecc8b0c04897>
 DWORD dwFVF;
 DWORD nDWords;
 array DWORD data[nDWords];
}


Material Multimaterial_Material__39Sub0 {
 1.000000;1.000000;1.000000;1.000000;;
 3.200000;
 0.000000;0.000000;0.000000;;
 0.000000;0.000000;0.000000;;

 TextureFilename {
  "Fx_Water_002_Tex_D_Pys.tga";
 }
}

Frame LV_Common_Env_Circleplane_SM_PYO {
 

 FrameTransformMatrix {
  1.000000,0.000000,0.000000,0.000000,0.000000,1.000000,0.000000,0.000000,0.000000,0.000000,1.000000,0.000000,0.000000,0.000000,0.000000,1.000000;;
 }

 Mesh  {
  13;
  23.069286;0.000000;0.000000;,
  -0.000008;0.000000;0.000001;,
  19.978582;0.000000;-11.534658;,
  11.534632;0.000000;-19.978595;,
  -0.000011;0.000000;-23.069286;,
  -11.534651;0.000000;-19.978582;,
  -19.978590;0.000000;-11.534638;,
  -23.069286;0.000000;0.000003;,
  -19.978589;0.000000;11.534644;,
  -11.534644;0.000000;19.978589;,
  -0.000001;0.000000;23.069286;,
  11.534642;0.000000;19.978589;,
  19.978589;0.000000;11.534643;;
  12;
  3;0,2,1;,
  3;1,2,3;,
  3;1,3,4;,
  3;5,1,4;,
  3;1,5,6;,
  3;7,1,6;,
  3;8,1,7;,
  3;1,8,9;,
  3;10,1,9;,
  3;11,1,10;,
  3;12,1,11;,
  3;0,1,12;;

  MeshNormals  {
   1;
   0.000000;1.000000;0.000000;;
   12;
   3;0,0,0;,
   3;0,0,0;,
   3;0,0,0;,
   3;0,0,0;,
   3;0,0,0;,
   3;0,0,0;,
   3;0,0,0;,
   3;0,0,0;,
   3;0,0,0;,
   3;0,0,0;,
   3;0,0,0;,
   3;0,0,0;;
  }

  MeshMaterialList  {
   1;
   12;
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0;
   { Multimaterial_Material__39Sub0 }
  }

  MeshVertexColors  {
   13;
   0;1.000000;1.000000;1.000000;-1.000000;;,
   1;1.000000;1.000000;1.000000;-1.000000;;,
   2;1.000000;1.000000;1.000000;-1.000000;;,
   3;1.000000;1.000000;1.000000;-1.000000;;,
   4;1.000000;1.000000;1.000000;-1.000000;;,
   5;1.000000;1.000000;1.000000;-1.000000;;,
   6;1.000000;1.000000;1.000000;-1.000000;;,
   7;1.000000;1.000000;1.000000;-1.000000;;,
   8;1.000000;1.000000;1.000000;-1.000000;;,
   9;1.000000;1.000000;1.000000;-1.000000;;,
   10;1.000000;1.000000;1.000000;-1.000000;;,
   11;1.000000;1.000000;1.000000;-1.000000;;,
   12;1.000000;1.000000;1.000000;-1.000000;;;
  }

  MeshTextureCoords  {
   13;
   0.499756;0.000031;,
   0.499756;0.500000;,
   0.750000;0.066956;,
   0.932617;0.250000;,
   1.000000;0.500000;,
   0.932617;0.750000;,
   0.749512;0.932617;,
   0.499756;1.000000;,
   0.250000;0.932617;,
   0.066956;0.750000;,
   0.000031;0.500000;,
   0.066956;0.250000;,
   0.249878;0.066956;;
  }

  FVFData  {
   770;
   52;
   1056956416,
   939524096,
   1065353216,
   1056964608,
   1056956416,
   1056964608,
   1056956416,
   1056964608,
   1061158912,
   1032396800,
   1064222720,
   1061158912,
   1064222720,
   1048576000,
   1061150720,
   1064222720,
   1065353216,
   1056964608,
   1056956416,
   1065353216,
   1064222720,
   1061158912,
   1048567808,
   1064222720,
   1061150720,
   1064222720,
   1032396800,
   1061150720,
   1056956416,
   1065353216,
   939524096,
   1056956416,
   1048576000,
   1064222720,
   1032396800,
   1048576000,
   1032396800,
   1061158912,
   1048567808,
   1032396800,
   939524096,
   1056964608,
   1056956416,
   939524096,
   1032396800,
   1048576000,
   1061158912,
   1032396800,
   1048567808,
   1032396800,
   1064222720,
   1048576000;
  }
 }
}