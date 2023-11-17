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
 18;
 0.00000;11.14816;-0.03075;,
 0.00000;11.14816;-11.93657;,
 -8.41868;11.14816;-8.44943;,
 -11.90582;11.14816;-0.03075;,
 -8.41868;11.14816;8.38793;,
 0.00000;11.14816;11.87507;,
 8.41868;11.14816;8.38793;,
 11.90582;11.14816;-0.03075;,
 8.41868;11.14816;-8.44943;,
 0.00000;5.57947;-16.80875;,
 0.00000;-11.14671;-0.03075;,
 -12.00000;5.57947;-12.03075;,
 -16.77800;5.57947;-0.03075;,
 -12.00000;5.57947;11.96925;,
 0.00000;5.57947;16.74725;,
 12.00000;5.57947;11.96925;,
 16.77800;5.57947;-0.03075;,
 12.00000;5.57947;-12.03075;;
 
 24;
 3;0,1,2;,
 3;0,2,3;,
 3;0,3,4;,
 3;0,4,5;,
 3;0,5,6;,
 3;0,6,7;,
 3;0,7,8;,
 3;0,8,1;,
 3;9,10,11;,
 4;9,11,2,1;,
 3;11,10,12;,
 4;11,12,3,2;,
 3;12,10,13;,
 4;12,13,4,3;,
 3;13,10,14;,
 4;13,14,5,4;,
 3;14,10,15;,
 4;14,15,6,5;,
 3;15,10,16;,
 4;15,16,7,6;,
 3;16,10,17;,
 4;16,17,8,7;,
 3;17,10,9;,
 4;17,9,1,8;;
 
 MeshMaterialList {
  1;
  24;
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
  0;;
  Material {
   0.650000;0.000000;0.000000;1.000000;;
   16.000000;
   1.000000;1.000000;1.000000;;
   0.910000;0.000000;0.000000;;
   TextureFilename {
    "data\\TEXTURE\\Marbl24l.jpg";
   }
  }
 }
 MeshNormals {
  27;
  0.000000;0.916052;-0.401060;,
  -0.282245;0.916883;-0.282245;,
  -0.401060;0.916052;0.000000;,
  -0.282245;0.916883;0.282245;,
  0.000000;0.916052;0.401060;,
  0.282245;0.916883;0.282245;,
  0.401060;0.916052;0.000000;,
  0.282245;0.916883;-0.282245;,
  -0.571768;-0.820416;0.000000;,
  0.000000;1.000000;0.000000;,
  0.000000;-0.708200;-0.706012;,
  -0.496361;-0.712216;-0.496361;,
  -0.706012;-0.708200;0.000000;,
  -0.496361;-0.712216;0.496361;,
  0.000000;-0.708200;0.706012;,
  0.496361;-0.712216;0.496361;,
  0.706012;-0.708200;-0.000000;,
  0.496361;-0.712216;-0.496361;,
  0.000000;0.663578;-0.748107;,
  -0.527669;0.665681;-0.527669;,
  -0.748107;0.663578;0.000000;,
  -0.527669;0.665681;0.527669;,
  0.000000;0.663578;0.748107;,
  0.571768;-0.820416;-0.000000;,
  0.527669;0.665681;0.527669;,
  0.748107;0.663578;0.000000;,
  0.527669;0.665681;-0.527669;;
  24;
  3;9,0,1;,
  3;9,1,2;,
  3;9,2,3;,
  3;9,3,4;,
  3;9,4,5;,
  3;9,5,6;,
  3;9,6,7;,
  3;9,7,0;,
  3;10,8,11;,
  4;18,19,1,0;,
  3;11,8,12;,
  4;19,20,2,1;,
  3;12,8,13;,
  4;20,21,3,2;,
  3;13,8,14;,
  4;21,22,4,3;,
  3;14,23,15;,
  4;22,24,5,4;,
  3;15,23,16;,
  4;24,25,6,5;,
  3;16,23,17;,
  4;25,26,7,6;,
  3;17,23,10;,
  4;26,18,0,7;;
 }
 MeshTextureCoords {
  18;
  0.500000;0.450755;,
  0.500000;0.450755;,
  -0.001769;0.450755;,
  -0.209609;0.450755;,
  -0.001769;0.450755;,
  0.500000;0.450755;,
  1.001769;0.450755;,
  1.209609;0.450755;,
  1.001769;0.450755;,
  0.500000;0.950305;,
  0.500000;2.450760;,
  -0.215222;0.950305;,
  -0.500000;0.950305;,
  -0.215222;0.950305;,
  0.500000;0.950305;,
  1.215222;0.950305;,
  1.500000;0.950305;,
  1.215222;0.950305;;
 }
}
