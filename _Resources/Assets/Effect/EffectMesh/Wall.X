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


Material DefaultMaterial {
 1.000000;1.000000;1.000000;1.000000;;
 10.000000;
 0.000000;0.000000;0.000000;;
 0.000000;0.000000;0.000000;;

 TextureFilename {
  "material_0";
 }
}

Frame FX_Pattern_001_SM_KKJ {
 

 FrameTransformMatrix {
  1.000000,0.000000,0.000000,0.000000,0.000000,1.000000,0.000000,0.000000,0.000000,0.000000,1.000000,0.000000,0.000000,0.000000,0.000000,1.000000;;
 }

 Mesh FX_Pattern_001_SM_KKJ {
  16;
  -11.352682;15.021366;-32.458598;,
  -2.280718;15.021366;-50.660557;,
  -11.352682;-14.978634;-32.458598;,
  -2.280718;-14.978634;-50.660557;,
  10.469114;15.021366;-66.388141;,
  10.469114;-14.978634;-66.388141;,
  9.737597;15.021366;64.275098;,
  -2.903540;15.021366;48.343578;,
  9.737597;-14.978634;64.275098;,
  -2.903540;-14.978634;48.343578;,
  -11.846206;15.021366;29.726550;,
  -11.846206;-14.978634;29.726550;,
  -16.478302;15.021366;8.920202;,
  -16.478302;-14.978634;8.920202;,
  -16.250602;15.021366;-12.394326;,
  -16.250602;-14.978634;-12.394326;;
  14;
  3;0,1,2;,
  3;1,3,2;,
  3;1,4,3;,
  3;4,5,3;,
  3;6,7,8;,
  3;7,9,8;,
  3;10,9,7;,
  3;10,11,9;,
  3;12,11,10;,
  3;12,13,11;,
  3;14,13,12;,
  3;14,15,13;,
  3;0,15,14;,
  3;0,2,15;;

  MeshMaterialList {
   1;
   14;
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
   { DefaultMaterial }
  }

  MeshTextureCoords c1 {
   16;
   0.285645;0.000031;,
   0.142822;0.000031;,
   0.285645;1.000000;,
   0.142822;1.000000;,
   0.000031;0.000031;,
   0.000031;1.000000;,
   1.000000;0.000031;,
   0.856934;0.000031;,
   1.000000;1.000000;,
   0.856934;1.000000;,
   0.713867;0.000031;,
   0.713867;1.000000;,
   0.571289;0.000031;,
   0.571289;1.000000;,
   0.428467;0.000031;,
   0.428467;1.000000;;
  }
 }
}