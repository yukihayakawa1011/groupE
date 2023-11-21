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
 26;
 -3.52968;-3.09214;3.50922;,
 -0.02046;-3.09214;4.96278;,
 -0.02046;-1.77196;4.96278;,
 -3.52968;-1.77196;3.50922;,
 3.48874;-3.09214;3.50922;,
 3.48874;-1.77196;3.50922;,
 4.94230;-3.09214;0.00000;,
 4.94230;-1.77196;0.00000;,
 3.48874;-3.09214;-10.37420;,
 3.48874;-1.77196;-10.37420;,
 -0.02046;-3.09214;-11.96462;,
 -0.02046;-1.77196;-11.96462;,
 -3.52968;-3.09214;-10.37420;,
 -3.52968;-1.77196;-10.37420;,
 -4.98324;-3.09214;0.00000;,
 -4.98324;-1.77196;0.00000;,
 -0.02046;0.59686;4.96278;,
 -3.52968;0.59686;3.50922;,
 3.48874;0.59686;3.50922;,
 4.94230;0.59686;0.00000;,
 3.48874;0.59686;-3.50922;,
 -0.02046;0.59686;-4.96278;,
 -3.52968;0.59686;-3.50922;,
 -4.98324;0.59686;0.00000;,
 -0.02046;-3.09214;0.00000;,
 -0.02046;-0.45178;0.00000;;
 
 32;
 4;0,1,2,3;,
 4;1,4,5,2;,
 4;4,6,7,5;,
 4;6,8,9,7;,
 4;8,10,11,9;,
 4;10,12,13,11;,
 4;12,14,15,13;,
 4;14,0,3,15;,
 4;3,2,16,17;,
 4;2,5,18,16;,
 4;5,7,19,18;,
 4;7,9,20,19;,
 4;9,11,21,20;,
 4;11,13,22,21;,
 4;13,15,23,22;,
 4;15,3,17,23;,
 3;1,0,24;,
 3;4,1,24;,
 3;6,4,24;,
 3;8,6,24;,
 3;10,8,24;,
 3;12,10,24;,
 3;14,12,24;,
 3;0,14,24;,
 3;17,16,25;,
 3;16,18,25;,
 3;18,19,25;,
 3;19,20,25;,
 3;20,21,25;,
 3;21,22,25;,
 3;22,23,25;,
 3;23,17,25;;
 
 MeshMaterialList {
  1;
  32;
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
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0;;
  Material {
   0.800000;0.800000;0.800000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
   TextureFilename {
    "data\\TEXTURE\\UV\\ninja_black.jpg";
   }
  }
 }
 MeshNormals {
  32;
  -0.707107;0.000000;0.707107;,
  0.000001;0.000000;1.000000;,
  0.707107;0.000000;0.707106;,
  0.991979;0.000000;0.126406;,
  0.800756;0.000000;-0.598990;,
  0.000001;0.000000;-1.000000;,
  -0.800756;0.000000;-0.598991;,
  -0.991979;0.000000;0.126406;,
  0.000001;0.000000;1.000000;,
  0.707108;0.000000;0.707106;,
  0.994141;0.050310;0.095668;,
  0.870827;0.070992;-0.486437;,
  -0.870826;0.070992;-0.486438;,
  -0.994141;0.050310;0.095668;,
  0.000001;0.000000;1.000000;,
  0.992768;0.101678;0.063826;,
  0.945747;0.191486;-0.262481;,
  0.000000;0.998220;-0.059633;,
  0.052746;0.998558;-0.009996;,
  -0.992768;0.101678;0.063826;,
  0.000000;-1.000000;-0.000000;,
  -0.000000;1.000000;-0.000000;,
  0.138816;0.937124;-0.320201;,
  0.000000;0.946286;-0.323332;,
  -0.052747;0.998558;-0.009996;,
  -0.138816;0.937124;-0.320201;,
  -0.945747;0.191486;-0.262481;,
  0.146184;0.978397;-0.146184;,
  -0.000000;0.978397;-0.206736;,
  -0.146185;0.978397;-0.146185;,
  -0.206737;0.978396;0.000000;,
  0.206736;0.978397;0.000000;;
  32;
  4;0,1,8,0;,
  4;1,2,9,8;,
  4;2,3,10,9;,
  4;3,4,11,10;,
  4;4,5,5,11;,
  4;5,6,12,5;,
  4;6,7,13,12;,
  4;7,0,0,13;,
  4;0,8,14,0;,
  4;8,9,9,14;,
  4;9,10,15,9;,
  4;10,11,16,15;,
  4;22,23,17,24;,
  4;23,25,18,17;,
  4;12,13,19,26;,
  4;13,0,0,19;,
  3;20,20,20;,
  3;20,20,20;,
  3;20,20,20;,
  3;20,20,20;,
  3;20,20,20;,
  3;20,20,20;,
  3;20,20,20;,
  3;20,20,20;,
  3;27,28,21;,
  3;28,29,21;,
  3;29,30,21;,
  3;30,24,21;,
  3;24,17,21;,
  3;17,18,21;,
  3;18,31,21;,
  3;31,27,21;;
 }
 MeshTextureCoords {
  26;
  0.302092;0.550005;,
  0.281285;0.550005;,
  0.281285;0.542127;,
  0.302092;0.542127;,
  0.260478;0.550005;,
  0.260478;0.542127;,
  0.251860;0.550005;,
  0.251860;0.542127;,
  0.260478;0.550005;,
  0.260478;0.542127;,
  0.281285;0.550005;,
  0.281285;0.542127;,
  0.302092;0.550005;,
  0.302092;0.542127;,
  0.310711;0.550005;,
  0.310711;0.542127;,
  0.281285;0.527990;,
  0.302092;0.527990;,
  0.260478;0.527990;,
  0.251860;0.527990;,
  0.260478;0.527990;,
  0.281285;0.527990;,
  0.302092;0.527990;,
  0.310711;0.527990;,
  0.281285;0.550005;,
  0.281285;0.534248;;
 }
}
