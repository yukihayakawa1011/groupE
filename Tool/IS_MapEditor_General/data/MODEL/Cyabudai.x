xof 0302txt 0064
template Header {
 <3D82AB43-62DA-11cf-AB39-0020AF71E433>
 WORD major;
 WORD minor;
 DWORD flags;
}

template Vector {
 <3D82AB5E-62DA-11cf-AB39-0020AF71E433>
 FLOAT x;
 FLOAT y;
 FLOAT z;
}

template Coords2d {
 <F6F23F44-7686-11cf-8F52-0040333594A3>
 FLOAT u;
 FLOAT v;
}

template Matrix4x4 {
 <F6F23F45-7686-11cf-8F52-0040333594A3>
 array FLOAT matrix[16];
}

template ColorRGBA {
 <35FF44E0-6C7C-11cf-8F52-0040333594A3>
 FLOAT red;
 FLOAT green;
 FLOAT blue;
 FLOAT alpha;
}

template ColorRGB {
 <D3E16E81-7835-11cf-8F52-0040333594A3>
 FLOAT red;
 FLOAT green;
 FLOAT blue;
}

template IndexedColor {
 <1630B820-7842-11cf-8F52-0040333594A3>
 DWORD index;
 ColorRGBA indexColor;
}

template Boolean {
 <4885AE61-78E8-11cf-8F52-0040333594A3>
 WORD truefalse;
}

template Boolean2d {
 <4885AE63-78E8-11cf-8F52-0040333594A3>
 Boolean u;
 Boolean v;
}

template MaterialWrap {
 <4885AE60-78E8-11cf-8F52-0040333594A3>
 Boolean u;
 Boolean v;
}

template TextureFilename {
 <A42790E1-7810-11cf-8F52-0040333594A3>
 STRING filename;
}

template Material {
 <3D82AB4D-62DA-11cf-AB39-0020AF71E433>
 ColorRGBA faceColor;
 FLOAT power;
 ColorRGB specularColor;
 ColorRGB emissiveColor;
 [...]
}

template MeshFace {
 <3D82AB5F-62DA-11cf-AB39-0020AF71E433>
 DWORD nFaceVertexIndices;
 array DWORD faceVertexIndices[nFaceVertexIndices];
}

template MeshFaceWraps {
 <4885AE62-78E8-11cf-8F52-0040333594A3>
 DWORD nFaceWrapValues;
 Boolean2d faceWrapValues;
}

template MeshTextureCoords {
 <F6F23F40-7686-11cf-8F52-0040333594A3>
 DWORD nTextureCoords;
 array Coords2d textureCoords[nTextureCoords];
}

template MeshMaterialList {
 <F6F23F42-7686-11cf-8F52-0040333594A3>
 DWORD nMaterials;
 DWORD nFaceIndexes;
 array DWORD faceIndexes[nFaceIndexes];
 [Material]
}

template MeshNormals {
 <F6F23F43-7686-11cf-8F52-0040333594A3>
 DWORD nNormals;
 array Vector normals[nNormals];
 DWORD nFaceNormals;
 array MeshFace faceNormals[nFaceNormals];
}

template MeshVertexColors {
 <1630B821-7842-11cf-8F52-0040333594A3>
 DWORD nVertexColors;
 array IndexedColor vertexColors[nVertexColors];
}

template Mesh {
 <3D82AB44-62DA-11cf-AB39-0020AF71E433>
 DWORD nVertices;
 array Vector vertices[nVertices];
 DWORD nFaces;
 array MeshFace faces[nFaces];
 [...]
}

Header{
1;
0;
1;
}

Mesh {
 98;
 0.00000;29.89056;-106.71153;,
 75.45648;29.89056;-75.45648;,
 75.45648;22.11058;-75.45648;,
 0.00000;22.11058;-106.71153;,
 106.71153;29.89056;0.00000;,
 106.71153;22.11058;0.00000;,
 75.45648;29.89056;75.45648;,
 75.45648;22.11058;75.45648;,
 0.00000;29.89056;106.71153;,
 0.00000;22.11058;106.71153;,
 -75.45653;29.89056;75.45648;,
 -75.45653;22.11058;75.45648;,
 -106.71153;29.89056;0.00000;,
 -106.71153;22.11058;0.00000;,
 -75.45648;29.89056;-75.45648;,
 -75.45648;22.11058;-75.45648;,
 0.00000;29.89056;0.00000;,
 0.00000;22.11058;0.00000;,
 -77.43811;27.06136;-57.20818;,
 -58.62906;27.06136;-57.20818;,
 -58.62906;-45.24997;-57.20818;,
 -77.43811;-45.24997;-57.20818;,
 -58.62906;27.06136;-57.20818;,
 -58.62906;27.06136;-38.58567;,
 -58.62906;-45.24997;-38.58567;,
 -58.62906;-45.24997;-57.20818;,
 -58.62906;27.06136;-38.58567;,
 -77.43811;27.06136;-38.58567;,
 -77.43811;-45.24997;-38.58567;,
 -58.62906;-45.24997;-38.58567;,
 -77.43811;27.06136;-38.58567;,
 -77.43811;27.06136;-57.20818;,
 -77.43811;-45.24997;-57.20818;,
 -77.43811;-45.24997;-38.58567;,
 -58.62906;27.06136;-57.20818;,
 -77.43811;27.06136;-57.20818;,
 -77.43811;-45.24997;-57.20818;,
 -58.62906;-45.24997;-57.20818;,
 -77.43811;27.06136;35.38388;,
 -58.62906;27.06136;35.38388;,
 -58.62906;-45.24997;35.38388;,
 -77.43811;-45.24997;35.38388;,
 -58.62906;27.06136;35.38388;,
 -58.62906;27.06136;54.00640;,
 -58.62906;-45.24997;54.00640;,
 -58.62906;-45.24997;35.38388;,
 -58.62906;27.06136;54.00640;,
 -77.43811;27.06136;54.00640;,
 -77.43811;-45.24997;54.00640;,
 -58.62906;-45.24997;54.00640;,
 -77.43811;27.06136;54.00640;,
 -77.43811;27.06136;35.38388;,
 -77.43811;-45.24997;35.38388;,
 -77.43811;-45.24997;54.00640;,
 -58.62906;27.06136;35.38388;,
 -77.43811;27.06136;35.38388;,
 -77.43811;-45.24997;35.38388;,
 -58.62906;-45.24997;35.38388;,
 55.49534;27.06136;35.38388;,
 74.30438;27.06136;35.38388;,
 74.30438;-45.24997;35.38388;,
 55.49534;-45.24997;35.38388;,
 74.30438;27.06136;35.38388;,
 74.30438;27.06136;54.00640;,
 74.30438;-45.24997;54.00640;,
 74.30438;-45.24997;35.38388;,
 74.30438;27.06136;54.00640;,
 55.49534;27.06136;54.00640;,
 55.49534;-45.24997;54.00640;,
 74.30438;-45.24997;54.00640;,
 55.49534;27.06136;54.00640;,
 55.49534;27.06136;35.38388;,
 55.49534;-45.24997;35.38388;,
 55.49534;-45.24997;54.00640;,
 74.30438;27.06136;35.38388;,
 55.49534;27.06136;35.38388;,
 55.49534;-45.24997;35.38388;,
 74.30438;-45.24997;35.38388;,
 55.49534;27.06136;-57.56891;,
 74.30438;27.06136;-57.56891;,
 74.30438;-45.24997;-57.56891;,
 55.49534;-45.24997;-57.56891;,
 74.30438;27.06136;-57.56891;,
 74.30438;27.06136;-38.94638;,
 74.30438;-45.24997;-38.94638;,
 74.30438;-45.24997;-57.56891;,
 74.30438;27.06136;-38.94638;,
 55.49534;27.06136;-38.94638;,
 55.49534;-45.24997;-38.94638;,
 74.30438;-45.24997;-38.94638;,
 55.49534;27.06136;-38.94638;,
 55.49534;27.06136;-57.56891;,
 55.49534;-45.24997;-57.56891;,
 55.49534;-45.24997;-38.94638;,
 74.30438;27.06136;-57.56891;,
 55.49534;27.06136;-57.56891;,
 55.49534;-45.24997;-57.56891;,
 74.30438;-45.24997;-57.56891;;
 
 48;
 4;0,1,2,3;,
 4;1,4,5,2;,
 4;4,6,7,5;,
 4;6,8,9,7;,
 4;8,10,11,9;,
 4;10,12,13,11;,
 4;12,14,15,13;,
 4;14,0,3,15;,
 3;16,1,0;,
 3;16,4,1;,
 3;16,6,4;,
 3;16,8,6;,
 3;16,10,8;,
 3;16,12,10;,
 3;16,14,12;,
 3;16,0,14;,
 3;17,3,2;,
 3;17,2,5;,
 3;17,5,7;,
 3;17,7,9;,
 3;17,9,11;,
 3;17,11,13;,
 3;17,13,15;,
 3;17,15,3;,
 4;18,19,20,21;,
 4;22,23,24,25;,
 4;26,27,28,29;,
 4;30,31,32,33;,
 4;30,23,34,35;,
 4;36,37,24,33;,
 4;38,39,40,41;,
 4;42,43,44,45;,
 4;46,47,48,49;,
 4;50,51,52,53;,
 4;50,43,54,55;,
 4;56,57,44,53;,
 4;58,59,60,61;,
 4;62,63,64,65;,
 4;66,67,68,69;,
 4;70,71,72,73;,
 4;70,63,74,75;,
 4;76,77,64,73;,
 4;78,79,80,81;,
 4;82,83,84,85;,
 4;86,87,88,89;,
 4;90,91,92,93;,
 4;90,83,94,95;,
 4;96,97,84,93;;
 
 MeshMaterialList {
  2;
  48;
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
  0,
  0,
  0,
  0,
  0,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1;;
  Material {
   0.800000;0.800000;0.800000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
   TextureFilename {
    "af18.jpg";
   }
  }
  Material {
   0.460800;0.216800;0.153600;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
 }
 MeshNormals {
  34;
  0.000000;1.000000;0.000000;,
  0.000000;0.000000;-1.000000;,
  0.707107;0.000000;-0.707107;,
  1.000000;0.000000;0.000000;,
  0.707107;0.000000;0.707107;,
  0.000000;0.000000;1.000000;,
  -0.707107;0.000000;0.707107;,
  -1.000000;0.000000;-0.000000;,
  -0.707107;0.000000;-0.707107;,
  0.000000;-1.000000;-0.000000;,
  0.000000;0.000000;-1.000000;,
  1.000000;0.000000;0.000000;,
  0.000000;0.000000;1.000000;,
  -1.000000;0.000000;0.000000;,
  0.000000;1.000000;0.000000;,
  0.000000;-1.000000;-0.000000;,
  0.000000;0.000000;-1.000000;,
  1.000000;0.000000;0.000000;,
  0.000000;0.000000;1.000000;,
  -1.000000;0.000000;0.000000;,
  0.000000;1.000000;0.000000;,
  0.000000;-1.000000;-0.000000;,
  0.000000;0.000000;-1.000000;,
  1.000000;0.000000;0.000000;,
  0.000000;0.000000;1.000000;,
  -1.000000;0.000000;0.000000;,
  0.000000;1.000000;0.000000;,
  0.000000;-1.000000;-0.000000;,
  0.000000;0.000000;-1.000000;,
  1.000000;0.000000;0.000000;,
  0.000000;0.000000;1.000000;,
  -1.000000;0.000000;0.000000;,
  0.000000;1.000000;0.000000;,
  0.000000;-1.000000;-0.000000;;
  48;
  4;1,2,2,1;,
  4;2,3,3,2;,
  4;3,4,4,3;,
  4;4,5,5,4;,
  4;5,6,6,5;,
  4;6,7,7,6;,
  4;7,8,8,7;,
  4;8,1,1,8;,
  3;0,0,0;,
  3;0,0,0;,
  3;0,0,0;,
  3;0,0,0;,
  3;0,0,0;,
  3;0,0,0;,
  3;0,0,0;,
  3;0,0,0;,
  3;9,9,9;,
  3;9,9,9;,
  3;9,9,9;,
  3;9,9,9;,
  3;9,9,9;,
  3;9,9,9;,
  3;9,9,9;,
  3;9,9,9;,
  4;10,10,10,10;,
  4;11,11,11,11;,
  4;12,12,12,12;,
  4;13,13,13,13;,
  4;14,14,14,14;,
  4;15,15,15,15;,
  4;16,16,16,16;,
  4;17,17,17,17;,
  4;18,18,18,18;,
  4;19,19,19,19;,
  4;20,20,20,20;,
  4;21,21,21,21;,
  4;22,22,22,22;,
  4;23,23,23,23;,
  4;24,24,24,24;,
  4;25,25,25,25;,
  4;26,26,26,26;,
  4;27,27,27,27;,
  4;28,28,28,28;,
  4;29,29,29,29;,
  4;30,30,30,30;,
  4;31,31,31,31;,
  4;32,32,32,32;,
  4;33,33,33,33;;
 }
 MeshTextureCoords {
  98;
  0.500000;-0.400671;,
  0.988933;-0.136871;,
  0.988933;-0.136871;,
  0.500000;-0.400671;,
  1.191455;0.500000;,
  1.191455;0.500000;,
  0.988933;1.136871;,
  0.988933;1.136871;,
  0.500000;1.400671;,
  0.500000;1.400671;,
  0.011067;1.136871;,
  0.011067;1.136871;,
  -0.191455;0.500000;,
  -0.191455;0.500000;,
  0.011067;-0.136871;,
  0.011067;-0.136871;,
  0.500000;0.500000;,
  0.500000;0.500000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;;
 }
}
