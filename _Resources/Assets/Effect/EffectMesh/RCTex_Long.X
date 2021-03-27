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

template MeshMaterialList {
 <f6f23f42-7686-11cf-8f52-0040333594a3>
 DWORD nMaterials;
 DWORD nFaceIndexes;
 array DWORD faceIndexes[nFaceIndexes];
 [Material <3d82ab4d-62da-11cf-ab39-0020af71e433>]
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


Material material_0 {
 1.000000;1.000000;1.000000;1.000000;;
 10.000000;
 0.000000;0.000000;0.000000;;
 0.000000;0.000000;0.000000;;

 TextureFilename {
  "material_0";
 }
}

Frame FX_Explosion_001_SM_PYS {
 

 FrameTransformMatrix {
  1.000000,0.000000,0.000000,0.000000,0.000000,1.000000,0.000000,0.000000,0.000000,0.000000,1.000000,0.000000,0.000000,0.000000,0.000000,1.000000;;
 }

 Mesh FX_Explosion_001_SM_PYS {
  24;
  0.000000;0.012000;-12.500000;,
  0.000000;24.011998;12.500000;,
  0.000000;0.012000;12.500000;,
  0.000000;24.011998;-12.500000;,
  0.000000;48.012000;12.500000;,
  0.000000;48.012000;-12.500000;,
  0.000000;72.012000;12.500000;,
  0.000000;72.012000;-12.500000;,
  0.000000;96.012000;12.500000;,
  0.000000;96.012000;-12.500000;,
  0.000000;120.012006;12.500000;,
  0.000000;120.012006;-12.500000;,
  -12.500000;0.012000;0.000000;,
  12.500000;24.011998;0.000000;,
  12.500000;0.012000;0.000000;,
  -12.500000;24.011998;0.000000;,
  12.500000;48.012000;0.000000;,
  -12.500000;48.012000;0.000000;,
  12.500000;72.012000;0.000000;,
  -12.500000;72.012000;0.000000;,
  12.500000;96.012000;0.000000;,
  -12.500000;96.012000;0.000000;,
  12.500000;120.012006;0.000000;,
  -12.500000;120.012006;0.000000;;
  20;
  3;0,1,2;,
  3;1,0,3;,
  3;3,4,1;,
  3;4,3,5;,
  3;5,6,4;,
  3;6,5,7;,
  3;7,8,6;,
  3;8,7,9;,
  3;9,10,8;,
  3;10,9,11;,
  3;12,13,14;,
  3;13,12,15;,
  3;15,16,13;,
  3;16,15,17;,
  3;17,18,16;,
  3;18,17,19;,
  3;19,20,18;,
  3;20,19,21;,
  3;21,22,20;,
  3;22,21,23;;

  MeshMaterialList {
   1;
   20;
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
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0;
   { material_0 }
  }

  MeshTextureCoords c1 {
   24;
   0.000031;1.000000;,
   1.000000;0.799805;,
   1.000000;1.000000;,
   0.000031;0.799805;,
   1.000000;0.599609;,
   0.000031;0.599609;,
   1.000000;0.399902;,
   0.000031;0.399902;,
   1.000000;0.199951;,
   0.000031;0.199951;,
   1.000000;0.000031;,
   0.000031;0.000031;,
   0.000031;1.000000;,
   1.000000;0.799805;,
   1.000000;1.000000;,
   0.000031;0.799805;,
   1.000000;0.599609;,
   0.000031;0.599609;,
   1.000000;0.399902;,
   0.000031;0.399902;,
   1.000000;0.199951;,
   0.000031;0.199951;,
   1.000000;0.000031;,
   0.000031;0.000031;;
  }
 }
}