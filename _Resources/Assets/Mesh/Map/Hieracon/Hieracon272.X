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


Material Multimaterial_Material__511Sub0 {
 1.000000;1.000000;1.000000;1.000000;;
 3.200000;
 0.000000;0.000000;0.000000;;
 0.000000;0.000000;0.000000;;

 TextureFilename {
  "LV_Hieracon_City_CastleWall02_D_KJH.tga";
 }
}

Frame LV_Hieracon_City_HallTop01_SM_KJH {
 

 FrameTransformMatrix {
  1.000000,0.000000,0.000000,0.000000,0.000000,1.000000,0.000000,0.000000,0.000000,0.000000,1.000000,0.000000,0.000000,0.000000,0.000000,1.000000;;
 }

 Mesh  {
  12;
  -200.831987;1082.11302;-267.113472;,
  -200.831987;1082.11302;270.342221;,
  200.831987;1082.11302;270.342170;,
  200.831987;1082.11302;-267.113472;,
  -200.831987;1082.11571;-979.12851;,
  -200.831987;1082.11302;-491.86621;,
  200.831987;1082.11302;-491.86621;,
  200.831987;1082.11571;-979.12851;,
  -200.831987;1082.11302;807.79782;,
  -200.831949;1082.11584;1067.59072;,
  200.831949;1082.11584;1067.59072;,
  200.831987;1082.11302;807.79782;;
  10;
  3;6,4,7;,
  3;4,6,5;,
  3;6,0,5;,
  3;0,6,3;,
  3;2,0,3;,
  3;0,2,1;,
  3;2,8,1;,
  3;8,2,11;,
  3;10,8,11;,
  3;8,10,9;;

  MeshNormals  {
   6;
   0.000000;-1.000000;-0.000004;,
   0.000000;-1.000000;-0.000006;,
   0.000000;-1.000000;-0.000003;,
   0.000000;-1.000000;0.000000;,
   0.000000;-1.000000;0.000005;,
   0.000000;-1.000000;0.000011;;
   10;
   3;0,1,1;,
   3;1,0,2;,
   3;0,3,2;,
   3;3,3,3;,
   3;3,3,3;,
   3;3,3,3;,
   3;3,4,3;,
   3;4,3,4;,
   3;5,4,4;,
   3;4,5,5;;
  }

  MeshMaterialList  {
   1;
   10;
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
   { Multimaterial_Material__511Sub0 }
  }

  MeshVertexColors  {
   12;
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
   11;1.000000;1.000000;1.000000;-1.000000;;;
  }

  MeshTextureCoords  {
   12;
   1.445313;1.966797;,
   1.445313;-0.564941;,
   -0.446045;-0.564941;,
   -0.446045;1.966797;,
   1.445313;5.320312;,
   1.445313;3.025391;,
   -0.446045;3.025391;,
   -0.446045;5.320312;,
   1.445313;-3.097656;,
   1.445313;-4.320312;,
   -0.446045;-4.320312;,
   -0.446045;-3.097656;;
  }

  FVFData  {
   770;
   48;
   1069088768,
   1073463296,
   1051852800,
   1065345024,
   1069088768,
   3205537792,
   1058816000,
   1065345024,
   3202637824,
   3205537792,
   1058816000,
   1000095744,
   3202637824,
   1073463296,
   1051852800,
   1000095744,
   1069088768,
   1084899328,
   939524096,
   1065345024,
   1069088768,
   1078042624,
   1047773184,
   1065345024,
   3202637824,
   1078042624,
   1047773184,
   1000095744,
   3202637824,
   1084899328,
   939524096,
   1000103936,
   1069088768,
   3225829376,
   1063223296,
   1065345024,
   1069088768,
   3230285824,
   1065345024,
   1065353216,
   3202637824,
   3230285824,
   1065353216,
   1000103936,
   3202637824,
   3225829376,
   1063223296,
   1000095744;
  }
 }
}