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
 274;
 4.78272;42.14666;-4.80662;,
 9.65446;40.46198;-9.70272;,
 0.00000;40.46198;-13.72172;,
 0.00000;42.14666;-6.79758;,
 6.76376;42.14666;0.00000;,
 13.65346;40.46198;0.00000;,
 4.78272;42.14666;4.80662;,
 9.65444;40.46198;9.70272;,
 0.00000;42.14666;6.79758;,
 0.00000;40.46198;13.72172;,
 -4.78272;42.14666;4.80662;,
 -9.65446;40.46198;9.70272;,
 -6.76376;42.14666;0.00000;,
 -13.65346;40.46198;0.00000;,
 -4.78272;42.14666;-4.80662;,
 -9.65446;40.46198;-9.70272;,
 10.02436;38.28240;-10.07448;,
 0.00000;38.28240;-14.24748;,
 14.17660;38.28240;0.00000;,
 10.02436;38.28240;10.07448;,
 0.00000;38.28240;14.24748;,
 -10.02436;38.28240;10.07448;,
 -14.17660;38.28240;0.00000;,
 -10.02436;38.28240;-10.07448;,
 10.02436;6.28240;-10.07448;,
 0.00000;6.28240;-14.24748;,
 14.17660;6.28240;0.00000;,
 10.02436;6.28240;10.07448;,
 0.00000;6.28240;14.24748;,
 -10.02436;6.28240;10.07448;,
 -14.17660;6.28240;0.00000;,
 -10.02436;6.28240;-10.07448;,
 4.73524;2.42762;-4.75892;,
 0.00000;4.11230;-13.72172;,
 9.65446;4.11230;-9.70272;,
 0.00000;2.42762;-6.73012;,
 6.69664;2.42762;0.00000;,
 13.65346;4.11230;0.00000;,
 4.73524;2.42762;4.75892;,
 9.65444;4.11230;9.70272;,
 0.00000;2.42762;6.73012;,
 0.00000;4.11230;13.72172;,
 -4.73524;2.42762;4.75892;,
 -9.65446;4.11230;9.70272;,
 -6.69664;2.42762;0.00000;,
 -13.65346;4.11230;0.00000;,
 -4.73524;2.42762;-4.75892;,
 -9.65446;4.11230;-9.70272;,
 0.00000;6.29188;-14.24748;,
 10.02436;6.29188;-10.07448;,
 14.17660;6.29188;0.00000;,
 10.02436;6.29188;10.07448;,
 0.00000;6.29188;14.24748;,
 -10.02436;6.29188;10.07448;,
 -14.17660;6.29188;0.00000;,
 -10.02436;6.29188;-10.07448;,
 -0.12122;45.20262;-7.39068;,
 4.94056;45.20262;-5.23032;,
 4.94056;42.18237;-5.23032;,
 -0.12122;42.18237;-7.39068;,
 7.03724;45.20262;-0.01474;,
 7.03724;42.18237;-0.01474;,
 4.94056;45.20262;5.20084;,
 4.94056;42.18237;5.20084;,
 -0.12122;45.20262;7.36120;,
 -0.12122;42.18237;7.36120;,
 -5.18306;45.20262;5.20084;,
 -5.18306;42.18237;5.20084;,
 -7.27972;45.20262;-0.01474;,
 -7.27972;42.18237;-0.01474;,
 -5.18306;45.20262;-5.23032;,
 -5.18306;42.18237;-5.23032;,
 -0.12122;45.20262;-7.39068;,
 -0.12122;42.18237;-7.39068;,
 2.40968;45.20262;2.59306;,
 -0.12122;45.20262;3.67324;,
 -0.12122;45.20262;3.67324;,
 -2.65216;45.20262;2.59306;,
 -2.65216;45.20262;2.59306;,
 -3.70048;45.20262;-0.01474;,
 -3.70048;45.20262;-0.01474;,
 -2.65216;45.20262;-2.62252;,
 -0.12122;45.20262;-3.70270;,
 -2.65216;45.20262;-2.62252;,
 2.40968;45.20262;-2.62252;,
 -0.12122;45.20262;-3.70270;,
 3.45800;45.20262;-0.01474;,
 2.40968;45.20262;-2.62252;,
 3.45800;45.20262;-0.01474;,
 2.40968;45.20262;2.59306;,
 -2.65216;42.18237;2.59306;,
 -0.12122;42.18237;3.67324;,
 -0.12122;42.18237;3.67324;,
 2.40968;42.18237;2.59306;,
 2.40968;42.18237;2.59306;,
 3.45800;42.18237;-0.01474;,
 3.45800;42.18237;-0.01474;,
 2.40968;42.18237;-2.62252;,
 2.40968;42.18237;-2.62252;,
 -0.12122;42.18237;-3.70270;,
 -0.12122;42.18237;-3.70270;,
 -2.65216;42.18237;-2.62252;,
 -2.65216;42.18237;-2.62252;,
 -3.70048;42.18237;-0.01474;,
 -3.70048;42.18237;-0.01474;,
 -2.65216;42.18237;2.59306;,
 -0.12122;2.90108;-7.39068;,
 4.94056;2.90108;-5.23032;,
 4.94056;-0.11914;-5.23032;,
 -0.12122;-0.11914;-7.39068;,
 7.03724;2.90108;-0.01474;,
 7.03724;-0.11914;-0.01474;,
 4.94056;2.90108;5.20084;,
 4.94056;-0.11914;5.20084;,
 -0.12122;2.90108;7.36120;,
 -0.12122;-0.11914;7.36120;,
 -5.18306;2.90108;5.20084;,
 -5.18306;-0.11914;5.20084;,
 -7.27972;2.90108;-0.01474;,
 -7.27972;-0.11914;-0.01474;,
 -5.18306;2.90108;-5.23032;,
 -5.18306;-0.11914;-5.23032;,
 -0.12122;2.90108;-7.39068;,
 -0.12122;-0.11914;-7.39068;,
 2.40968;2.90108;2.59306;,
 -0.12122;2.90108;3.67324;,
 -0.12122;2.90108;3.67324;,
 -2.65216;2.90108;2.59306;,
 -2.65216;2.90108;2.59306;,
 -3.70048;2.90108;-0.01474;,
 -3.70048;2.90108;-0.01474;,
 -2.65216;2.90108;-2.62252;,
 -0.12122;2.90108;-3.70270;,
 -2.65216;2.90108;-2.62252;,
 2.40968;2.90108;-2.62252;,
 -0.12122;2.90108;-3.70270;,
 3.45800;2.90108;-0.01474;,
 2.40968;2.90108;-2.62252;,
 3.45800;2.90108;-0.01474;,
 2.40968;2.90108;2.59306;,
 -2.65216;-0.11914;2.59306;,
 -0.12122;-0.11914;3.67324;,
 -0.12122;-0.11914;3.67324;,
 2.40968;-0.11914;2.59306;,
 2.40968;-0.11914;2.59306;,
 3.45800;-0.11914;-0.01474;,
 3.45800;-0.11914;-0.01474;,
 2.40968;-0.11914;-2.62252;,
 2.40968;-0.11914;-2.62252;,
 -0.12122;-0.11914;-3.70270;,
 -0.12122;-0.11914;-3.70270;,
 -2.65216;-0.11914;-2.62252;,
 -2.65216;-0.11914;-2.62252;,
 -3.70048;-0.11914;-0.01474;,
 -3.70048;-0.11914;-0.01474;,
 -2.65216;-0.11914;2.59306;,
 -0.12122;2.90108;-7.39068;,
 4.94056;2.90108;-5.23032;,
 4.94056;-0.11914;-5.23032;,
 -0.12122;-0.11914;-7.39068;,
 7.03724;2.90108;-0.01474;,
 7.03724;-0.11914;-0.01474;,
 4.94056;2.90108;5.20084;,
 4.94056;-0.11914;5.20084;,
 -0.12122;2.90108;7.36120;,
 -0.12122;-0.11914;7.36120;,
 -5.18306;2.90108;5.20084;,
 -5.18306;-0.11914;5.20084;,
 -7.27972;2.90108;-0.01474;,
 -7.27972;-0.11914;-0.01474;,
 -5.18306;2.90108;-5.23032;,
 -5.18306;-0.11914;-5.23032;,
 -0.12122;2.90108;-7.39068;,
 -0.12122;-0.11914;-7.39068;,
 2.40968;2.90108;2.59306;,
 -0.12122;2.90108;3.67324;,
 -0.12122;2.90108;3.67324;,
 -2.65216;2.90108;2.59306;,
 -2.65216;2.90108;2.59306;,
 -3.70048;2.90108;-0.01474;,
 -3.70048;2.90108;-0.01474;,
 -2.65216;2.90108;-2.62252;,
 -0.12122;2.90108;-3.70270;,
 -2.65216;2.90108;-2.62252;,
 2.40968;2.90108;-2.62252;,
 -0.12122;2.90108;-3.70270;,
 3.45800;2.90108;-0.01474;,
 2.40968;2.90108;-2.62252;,
 3.45800;2.90108;-0.01474;,
 2.40968;2.90108;2.59306;,
 -2.65216;-0.11914;2.59306;,
 -0.12122;-0.11914;3.67324;,
 -0.12122;-0.11914;3.67324;,
 2.40968;-0.11914;2.59306;,
 2.40968;-0.11914;2.59306;,
 3.45800;-0.11914;-0.01474;,
 3.45800;-0.11914;-0.01474;,
 2.40968;-0.11914;-2.62252;,
 2.40968;-0.11914;-2.62252;,
 -0.12122;-0.11914;-3.70270;,
 -0.12122;-0.11914;-3.70270;,
 -2.65216;-0.11914;-2.62252;,
 -2.65216;-0.11914;-2.62252;,
 -3.70048;-0.11914;-0.01474;,
 -3.70048;-0.11914;-0.01474;,
 -2.65216;-0.11914;2.59306;,
 5.94832;44.96562;-0.65984;,
 5.94832;44.96562;0.65984;,
 5.94832;44.39758;0.65984;,
 5.94832;44.39758;-0.65984;,
 -6.13550;44.96562;0.65984;,
 -6.13550;44.96562;-0.65984;,
 -6.13550;44.39758;-0.65984;,
 -6.13550;44.39758;0.65984;,
 -0.17168;50.30774;0.65984;,
 5.94832;44.96562;-0.65984;,
 -0.17168;50.30774;-0.65984;,
 -6.13550;44.96562;-0.65984;,
 -0.17168;50.30774;0.65984;,
 -6.13550;44.96562;0.65984;,
 -6.13550;44.39758;0.65984;,
 -0.17168;49.73970;0.65984;,
 5.94832;44.39758;0.65984;,
 5.94832;44.96562;0.65984;,
 -0.17168;50.30774;-0.65984;,
 5.94832;44.96562;-0.65984;,
 5.94832;44.39758;-0.65984;,
 -0.17168;49.73970;-0.65984;,
 -6.13550;44.39758;-0.65984;,
 -6.13550;44.96562;-0.65984;,
 -0.17168;49.73970;0.65984;,
 -6.13550;44.39758;-0.65984;,
 -0.17168;49.73970;-0.65984;,
 5.94832;44.39758;-0.65984;,
 -1.72390;50.82624;-1.10294;,
 1.23666;50.82624;-1.10294;,
 1.23666;49.91834;-1.10294;,
 -1.72390;49.91834;-1.10294;,
 1.23666;50.82624;-1.10294;,
 1.23666;50.82624;1.10294;,
 1.23666;49.91834;1.10294;,
 1.23666;49.91834;-1.10294;,
 1.23666;50.82624;1.10294;,
 -1.72390;50.82624;1.10294;,
 -1.72390;49.91834;1.10294;,
 1.23666;49.91834;1.10294;,
 -1.72390;50.82624;1.10294;,
 -1.72390;50.82624;-1.10294;,
 -1.72390;49.91834;-1.10294;,
 -1.72390;49.91834;1.10294;,
 1.23666;50.82624;-1.10294;,
 -1.72390;50.82624;-1.10294;,
 -1.72390;49.91834;-1.10294;,
 1.23666;49.91834;-1.10294;,
 0.18210;50.82624;-0.61720;,
 15.53626;52.11824;25.97700;,
 15.53626;51.21038;25.97700;,
 0.18210;49.91834;-0.61720;,
 15.53626;52.11824;25.97700;,
 13.79168;52.11824;27.07994;,
 13.79168;51.21038;27.07994;,
 15.53626;51.21038;25.97700;,
 13.79168;52.11824;27.07994;,
 -1.56250;50.82624;0.48574;,
 -1.56250;49.91834;0.48574;,
 13.79168;51.21038;27.07994;,
 -1.56250;50.82624;0.48574;,
 0.18210;50.82624;-0.61720;,
 0.18210;49.91834;-0.61720;,
 -1.56250;49.91834;0.48574;,
 15.53626;52.11824;25.97700;,
 0.18210;50.82624;-0.61720;,
 0.18210;49.91834;-0.61720;,
 15.53626;51.21038;25.97700;;
 
 246;
 3;0,1,2;,
 3;0,2,3;,
 3;4,5,1;,
 3;4,1,0;,
 3;6,7,5;,
 3;6,5,4;,
 3;8,9,7;,
 3;8,7,6;,
 3;10,11,9;,
 3;10,9,8;,
 3;12,13,11;,
 3;12,11,10;,
 3;14,15,13;,
 3;14,13,12;,
 3;3,2,15;,
 3;3,15,14;,
 3;1,16,17;,
 3;1,17,2;,
 3;5,18,16;,
 3;5,16,1;,
 3;7,19,18;,
 3;7,18,5;,
 3;9,20,19;,
 3;9,19,7;,
 3;11,21,20;,
 3;11,20,9;,
 3;13,22,21;,
 3;13,21,11;,
 3;15,23,22;,
 3;15,22,13;,
 3;2,17,23;,
 3;2,23,15;,
 3;16,24,25;,
 3;16,25,17;,
 3;18,26,24;,
 3;18,24,16;,
 3;19,27,26;,
 3;19,26,18;,
 3;20,28,27;,
 3;20,27,19;,
 3;21,29,28;,
 3;21,28,20;,
 3;22,30,29;,
 3;22,29,21;,
 3;23,31,30;,
 3;23,30,22;,
 3;17,25,31;,
 3;17,31,23;,
 3;32,33,34;,
 3;32,35,33;,
 3;36,34,37;,
 3;36,32,34;,
 3;38,37,39;,
 3;38,36,37;,
 3;40,39,41;,
 3;40,38,39;,
 3;42,41,43;,
 3;42,40,41;,
 3;44,43,45;,
 3;44,42,43;,
 3;46,45,47;,
 3;46,44,45;,
 3;35,47,33;,
 3;35,46,47;,
 3;34,48,49;,
 3;34,33,48;,
 3;37,49,50;,
 3;37,34,49;,
 3;39,50,51;,
 3;39,37,50;,
 3;41,51,52;,
 3;41,39,51;,
 3;43,52,53;,
 3;43,41,52;,
 3;45,53,54;,
 3;45,43,53;,
 3;47,54,55;,
 3;47,45,54;,
 3;33,55,48;,
 3;33,47,55;,
 4;56,57,58,59;,
 4;57,60,61,58;,
 4;60,62,63,61;,
 4;62,64,65,63;,
 4;64,66,67,65;,
 4;66,68,69,67;,
 4;68,70,71,69;,
 4;70,72,73,71;,
 4;62,74,75,64;,
 4;64,76,77,66;,
 4;66,78,79,68;,
 4;68,80,81,70;,
 4;82,72,70,83;,
 4;84,57,56,85;,
 4;86,60,57,87;,
 4;62,60,88,89;,
 4;65,67,90,91;,
 4;65,92,93,63;,
 4;61,63,94,95;,
 4;96,97,58,61;,
 4;59,58,98,99;,
 4;100,101,71,73;,
 4;69,71,102,103;,
 4;67,69,104,105;,
 4;59,58,57,56;,
 4;58,61,60,57;,
 4;61,63,62,60;,
 4;63,65,64,62;,
 4;65,67,66,64;,
 4;67,69,68,66;,
 4;69,71,70,68;,
 4;71,73,72,70;,
 4;64,75,74,62;,
 4;66,77,76,64;,
 4;68,79,78,66;,
 4;70,81,80,68;,
 4;83,70,72,82;,
 4;85,56,57,84;,
 4;87,57,60,86;,
 4;89,88,60,62;,
 4;91,90,67,65;,
 4;63,93,92,65;,
 4;95,94,63,61;,
 4;61,58,97,96;,
 4;99,98,58,59;,
 4;73,71,101,100;,
 4;103,102,71,69;,
 4;105,104,69,67;,
 4;106,107,108,109;,
 4;107,110,111,108;,
 4;110,112,113,111;,
 4;112,114,115,113;,
 4;114,116,117,115;,
 4;116,118,119,117;,
 4;118,120,121,119;,
 4;120,122,123,121;,
 4;112,124,125,114;,
 4;114,126,127,116;,
 4;116,128,129,118;,
 4;118,130,131,120;,
 4;132,122,120,133;,
 4;134,107,106,135;,
 4;136,110,107,137;,
 4;112,110,138,139;,
 4;115,117,140,141;,
 4;115,142,143,113;,
 4;111,113,144,145;,
 4;146,147,108,111;,
 4;109,108,148,149;,
 4;150,151,121,123;,
 4;119,121,152,153;,
 4;117,119,154,155;,
 4;109,108,107,106;,
 4;108,111,110,107;,
 4;111,113,112,110;,
 4;113,115,114,112;,
 4;115,117,116,114;,
 4;117,119,118,116;,
 4;119,121,120,118;,
 4;121,123,122,120;,
 4;114,125,124,112;,
 4;116,127,126,114;,
 4;118,129,128,116;,
 4;120,131,130,118;,
 4;133,120,122,132;,
 4;135,106,107,134;,
 4;137,107,110,136;,
 4;139,138,110,112;,
 4;141,140,117,115;,
 4;113,143,142,115;,
 4;145,144,113,111;,
 4;111,108,147,146;,
 4;149,148,108,109;,
 4;123,121,151,150;,
 4;153,152,121,119;,
 4;155,154,119,117;,
 4;156,157,158,159;,
 4;157,160,161,158;,
 4;160,162,163,161;,
 4;162,164,165,163;,
 4;164,166,167,165;,
 4;166,168,169,167;,
 4;168,170,171,169;,
 4;170,172,173,171;,
 4;162,174,175,164;,
 4;164,176,177,166;,
 4;166,178,179,168;,
 4;168,180,181,170;,
 4;182,172,170,183;,
 4;184,157,156,185;,
 4;186,160,157,187;,
 4;162,160,188,189;,
 4;165,167,190,191;,
 4;165,192,193,163;,
 4;161,163,194,195;,
 4;196,197,158,161;,
 4;159,158,198,199;,
 4;200,201,171,173;,
 4;169,171,202,203;,
 4;167,169,204,205;,
 4;159,158,157,156;,
 4;158,161,160,157;,
 4;161,163,162,160;,
 4;163,165,164,162;,
 4;165,167,166,164;,
 4;167,169,168,166;,
 4;169,171,170,168;,
 4;171,173,172,170;,
 4;164,175,174,162;,
 4;166,177,176,164;,
 4;168,179,178,166;,
 4;170,181,180,168;,
 4;183,170,172,182;,
 4;185,156,157,184;,
 4;187,157,160,186;,
 4;189,188,160,162;,
 4;191,190,167,165;,
 4;163,193,192,165;,
 4;195,194,163,161;,
 4;161,158,197,196;,
 4;199,198,158,159;,
 4;173,171,201,200;,
 4;203,202,171,169;,
 4;205,204,169,167;,
 4;206,207,208,209;,
 4;210,211,212,213;,
 4;214,207,215,216;,
 4;214,216,217,210;,
 4;218,219,220,221;,
 4;218,221,222,223;,
 4;224,225,226,227;,
 4;224,227,228,229;,
 4;230,213,231,232;,
 4;230,232,233,208;,
 4;234,235,236,237;,
 4;238,239,240,241;,
 4;242,243,244,245;,
 4;246,247,248,249;,
 4;246,239,250,251;,
 4;252,253,240,249;,
 4;254,255,256,257;,
 4;258,259,260,261;,
 4;262,263,264,265;,
 4;266,267,268,269;,
 4;266,259,270,271;,
 4;272,273,260,269;;
 
 MeshMaterialList {
  3;
  246;
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
  1,
  1,
  1,
  1,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
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
  2,
  1,
  1;;
  Material {
   0.649600;0.100000;0.060000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.243600;0.037500;0.022500;;
  }
  Material {
   0.125600;0.006400;0.019200;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
  Material {
   1.000000;1.000000;1.000000;1.000000;;
   0.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
 }
 MeshNormals {
  126;
  0.144707;0.971035;-0.190133;,
  0.237398;0.970865;-0.032615;,
  -0.144707;0.971035;0.190133;,
  -0.032787;0.971131;-0.236282;,
  0.191055;0.970961;0.143990;,
  0.032787;0.971131;0.236282;,
  -0.237398;0.970865;0.032615;,
  -0.191055;0.970961;-0.143989;,
  0.191055;0.970961;-0.143989;,
  0.237398;0.970865;0.032615;,
  0.144707;0.971035;0.190133;,
  -0.191055;0.970961;0.143989;,
  0.032787;0.971131;-0.236282;,
  -0.032787;0.971131;0.236282;,
  -0.237398;0.970865;-0.032614;,
  -0.144706;0.971035;-0.190133;,
  -0.001667;0.118313;-0.992975;,
  0.702251;0.117958;-0.702089;,
  0.993043;0.117742;-0.001639;,
  0.704574;0.118094;0.699736;,
  0.001667;0.118313;0.992975;,
  -0.702251;0.117958;0.702089;,
  -0.993043;0.117741;0.001640;,
  -0.704574;0.118092;-0.699736;,
  0.137445;0.000000;-0.990509;,
  0.798238;0.000000;-0.602343;,
  0.990694;0.000000;0.136106;,
  0.605154;0.000000;0.796108;,
  -0.137445;0.000000;0.990509;,
  -0.798238;0.000000;0.602343;,
  -0.990694;0.000000;-0.136106;,
  -0.605154;0.000000;-0.796108;,
  0.143389;-0.971568;-0.188402;,
  0.235237;-0.971401;-0.032318;,
  -0.143389;-0.971568;0.188402;,
  -0.032488;-0.971662;-0.234130;,
  0.189315;-0.971495;0.142679;,
  0.032488;-0.971662;0.234130;,
  -0.235237;-0.971401;0.032318;,
  -0.189315;-0.971495;-0.142679;,
  0.189315;-0.971495;-0.142679;,
  0.235237;-0.971401;0.032318;,
  0.143389;-0.971568;0.188402;,
  -0.189315;-0.971495;0.142679;,
  0.032488;-0.971662;-0.234130;,
  -0.032488;-0.971662;0.234130;,
  -0.235237;-0.971401;-0.032318;,
  -0.143389;-0.971568;-0.188402;,
  0.133682;-0.232388;-0.963392;,
  0.776528;-0.231726;-0.585924;,
  0.963821;-0.231335;0.132414;,
  0.588667;-0.231991;0.774371;,
  -0.133682;-0.232388;0.963392;,
  -0.776528;-0.231726;0.585924;,
  -0.963821;-0.231333;-0.132414;,
  -0.588668;-0.231987;-0.774372;,
  0.588668;0.231987;-0.774372;,
  -0.133682;0.232388;-0.963392;,
  0.963821;0.231332;-0.132414;,
  0.776527;0.231730;0.585924;,
  0.133682;0.232389;0.963392;,
  -0.588668;0.231987;0.774372;,
  -0.963821;0.231332;0.132414;,
  -0.776528;0.231726;-0.585924;,
  0.588668;-0.231987;-0.774372;,
  -0.133682;-0.232388;-0.963392;,
  0.963821;-0.231332;-0.132414;,
  0.776527;-0.231730;0.585924;,
  0.133682;-0.232389;0.963392;,
  -0.588668;-0.231987;0.774372;,
  -0.963821;-0.231332;0.132414;,
  -0.776528;-0.231727;-0.585924;,
  0.000002;0.000000;-1.000000;,
  0.714549;0.000000;-0.699586;,
  1.000000;0.000000;0.000000;,
  0.714549;0.000000;0.699586;,
  0.000002;0.000000;1.000000;,
  -0.714548;0.000000;0.699586;,
  -1.000000;0.000000;0.000000;,
  -0.714548;0.000000;-0.699586;,
  0.000000;1.000000;0.000000;,
  0.000000;-1.000000;-0.000000;,
  -0.000002;0.000000;1.000000;,
  -0.714549;0.000000;0.699586;,
  -0.714549;0.000000;-0.699586;,
  -0.000002;0.000000;-1.000000;,
  0.714548;0.000000;-0.699586;,
  0.714548;0.000000;0.699586;,
  0.000002;0.000000;-1.000000;,
  0.714549;0.000000;-0.699586;,
  1.000000;0.000000;0.000000;,
  0.714549;0.000000;0.699586;,
  0.000002;0.000000;1.000000;,
  -0.714548;0.000000;0.699586;,
  -1.000000;0.000000;0.000000;,
  -0.714548;0.000000;-0.699586;,
  0.000000;1.000000;0.000000;,
  0.000000;-1.000000;-0.000000;,
  -0.000002;0.000000;1.000000;,
  -0.714549;0.000000;0.699586;,
  -0.714549;0.000000;-0.699586;,
  -0.000002;0.000000;-1.000000;,
  0.714548;0.000000;-0.699586;,
  0.714548;0.000000;0.699586;,
  -0.913021;0.407912;0.000000;,
  -1.000000;0.000000;0.000000;,
  0.910386;0.413759;0.000000;,
  1.000000;0.000000;0.000000;,
  0.657606;0.753362;0.000000;,
  0.000000;0.000000;1.000000;,
  0.000000;0.000000;-1.000000;,
  -0.667216;0.744864;0.000000;,
  0.667216;-0.744864;-0.000000;,
  -0.657606;-0.753362;0.000000;,
  0.000000;0.000000;-1.000000;,
  1.000000;0.000000;0.000000;,
  0.000000;0.000000;1.000000;,
  -1.000000;0.000000;0.000000;,
  0.000000;1.000000;0.000000;,
  0.000000;-1.000000;-0.000000;,
  0.866026;0.000000;-0.500000;,
  0.534375;0.000000;0.845248;,
  -0.866025;0.000000;0.500000;,
  -0.534370;0.000000;-0.845251;,
  -0.022481;0.999115;-0.035560;,
  0.022482;-0.999115;0.035561;;
  246;
  3;0,8,12;,
  3;0,12,3;,
  3;1,9,8;,
  3;1,8,0;,
  3;4,10,9;,
  3;4,9,1;,
  3;5,13,10;,
  3;5,10,4;,
  3;2,11,13;,
  3;2,13,5;,
  3;6,14,11;,
  3;6,11,2;,
  3;7,15,14;,
  3;7,14,6;,
  3;3,12,15;,
  3;3,15,7;,
  3;56,17,16;,
  3;56,16,57;,
  3;58,18,17;,
  3;58,17,56;,
  3;59,19,18;,
  3;59,18,58;,
  3;60,20,19;,
  3;60,19,59;,
  3;61,21,20;,
  3;61,20,60;,
  3;62,22,21;,
  3;62,21,61;,
  3;63,23,22;,
  3;63,22,62;,
  3;57,16,23;,
  3;57,23,63;,
  3;17,25,24;,
  3;17,24,16;,
  3;18,26,25;,
  3;18,25,17;,
  3;19,27,26;,
  3;19,26,18;,
  3;20,28,27;,
  3;20,27,19;,
  3;21,29,28;,
  3;21,28,20;,
  3;22,30,29;,
  3;22,29,21;,
  3;23,31,30;,
  3;23,30,22;,
  3;16,24,31;,
  3;16,31,23;,
  3;32,44,40;,
  3;32,35,44;,
  3;33,40,41;,
  3;33,32,40;,
  3;36,41,42;,
  3;36,33,41;,
  3;37,42,45;,
  3;37,36,42;,
  3;34,45,43;,
  3;34,37,45;,
  3;38,43,46;,
  3;38,34,43;,
  3;39,46,47;,
  3;39,38,46;,
  3;35,47,44;,
  3;35,39,47;,
  3;64,48,49;,
  3;64,65,48;,
  3;66,49,50;,
  3;66,64,49;,
  3;67,50,51;,
  3;67,66,50;,
  3;68,51,52;,
  3;68,67,51;,
  3;69,52,53;,
  3;69,68,52;,
  3;70,53,54;,
  3;70,69,53;,
  3;71,54,55;,
  3;71,70,54;,
  3;65,55,48;,
  3;65,71,55;,
  4;72,73,73,72;,
  4;73,74,74,73;,
  4;74,75,75,74;,
  4;75,76,76,75;,
  4;76,77,77,76;,
  4;77,78,78,77;,
  4;78,79,79,78;,
  4;79,72,72,79;,
  4;80,80,80,80;,
  4;80,80,80,80;,
  4;80,80,80,80;,
  4;80,80,80,80;,
  4;80,80,80,80;,
  4;80,80,80,80;,
  4;80,80,80,80;,
  4;80,80,80,80;,
  4;81,81,81,81;,
  4;81,81,81,81;,
  4;81,81,81,81;,
  4;81,81,81,81;,
  4;81,81,81,81;,
  4;81,81,81,81;,
  4;81,81,81,81;,
  4;81,81,81,81;,
  4;82,83,83,82;,
  4;83,78,78,83;,
  4;78,84,84,78;,
  4;84,85,85,84;,
  4;85,86,86,85;,
  4;86,74,74,86;,
  4;74,87,87,74;,
  4;87,82,82,87;,
  4;81,81,81,81;,
  4;81,81,81,81;,
  4;81,81,81,81;,
  4;81,81,81,81;,
  4;81,81,81,81;,
  4;81,81,81,81;,
  4;81,81,81,81;,
  4;81,81,81,81;,
  4;80,80,80,80;,
  4;80,80,80,80;,
  4;80,80,80,80;,
  4;80,80,80,80;,
  4;80,80,80,80;,
  4;80,80,80,80;,
  4;80,80,80,80;,
  4;80,80,80,80;,
  4;88,89,89,88;,
  4;89,90,90,89;,
  4;90,91,91,90;,
  4;91,92,92,91;,
  4;92,93,93,92;,
  4;93,94,94,93;,
  4;94,95,95,94;,
  4;95,88,88,95;,
  4;96,96,96,96;,
  4;96,96,96,96;,
  4;96,96,96,96;,
  4;96,96,96,96;,
  4;96,96,96,96;,
  4;96,96,96,96;,
  4;96,96,96,96;,
  4;96,96,96,96;,
  4;97,97,97,97;,
  4;97,97,97,97;,
  4;97,97,97,97;,
  4;97,97,97,97;,
  4;97,97,97,97;,
  4;97,97,97,97;,
  4;97,97,97,97;,
  4;97,97,97,97;,
  4;98,99,99,98;,
  4;99,94,94,99;,
  4;94,100,100,94;,
  4;100,101,101,100;,
  4;101,102,102,101;,
  4;102,90,90,102;,
  4;90,103,103,90;,
  4;103,98,98,103;,
  4;97,97,97,97;,
  4;97,97,97,97;,
  4;97,97,97,97;,
  4;97,97,97,97;,
  4;97,97,97,97;,
  4;97,97,97,97;,
  4;97,97,97,97;,
  4;97,97,97,97;,
  4;96,96,96,96;,
  4;96,96,96,96;,
  4;96,96,96,96;,
  4;96,96,96,96;,
  4;96,96,96,96;,
  4;96,96,96,96;,
  4;96,96,96,96;,
  4;96,96,96,96;,
  4;88,89,89,88;,
  4;89,90,90,89;,
  4;90,91,91,90;,
  4;91,92,92,91;,
  4;92,93,93,92;,
  4;93,94,94,93;,
  4;94,95,95,94;,
  4;95,88,88,95;,
  4;96,96,96,96;,
  4;96,96,96,96;,
  4;96,96,96,96;,
  4;96,96,96,96;,
  4;96,96,96,96;,
  4;96,96,96,96;,
  4;96,96,96,96;,
  4;96,96,96,96;,
  4;97,97,97,97;,
  4;97,97,97,97;,
  4;97,97,97,97;,
  4;97,97,97,97;,
  4;97,97,97,97;,
  4;97,97,97,97;,
  4;97,97,97,97;,
  4;97,97,97,97;,
  4;98,99,99,98;,
  4;99,94,94,99;,
  4;94,100,100,94;,
  4;100,101,101,100;,
  4;101,102,102,101;,
  4;102,90,90,102;,
  4;90,103,103,90;,
  4;103,98,98,103;,
  4;97,97,97,97;,
  4;97,97,97,97;,
  4;97,97,97,97;,
  4;97,97,97,97;,
  4;97,97,97,97;,
  4;97,97,97,97;,
  4;97,97,97,97;,
  4;97,97,97,97;,
  4;96,96,96,96;,
  4;96,96,96,96;,
  4;96,96,96,96;,
  4;96,96,96,96;,
  4;96,96,96,96;,
  4;96,96,96,96;,
  4;96,96,96,96;,
  4;96,96,96,96;,
  4;106,106,107,107;,
  4;104,104,105,105;,
  4;108,106,106,108;,
  4;111,111,104,104;,
  4;109,109,109,109;,
  4;109,109,109,109;,
  4;110,110,110,110;,
  4;110,110,110,110;,
  4;112,112,112,112;,
  4;113,113,113,113;,
  4;114,114,114,114;,
  4;115,115,115,115;,
  4;116,116,116,116;,
  4;117,117,117,117;,
  4;118,118,118,118;,
  4;119,119,119,119;,
  4;120,120,120,120;,
  4;121,121,121,121;,
  4;122,122,122,122;,
  4;123,123,123,123;,
  4;124,124,124,124;,
  4;125,125,125,125;;
 }
 MeshTextureCoords {
  274;
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.125000;0.000000;,
  0.125000;1.000000;,
  0.000000;1.000000;,
  0.250000;0.000000;,
  0.250000;1.000000;,
  0.375000;0.000000;,
  0.375000;1.000000;,
  0.500000;0.000000;,
  0.500000;1.000000;,
  0.625000;0.000000;,
  0.625000;1.000000;,
  0.750000;0.000000;,
  0.750000;1.000000;,
  0.875000;0.000000;,
  0.875000;1.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.406250;0.000000;,
  0.468750;0.000000;,
  0.531250;0.000000;,
  0.593750;0.000000;,
  0.656250;0.000000;,
  0.718750;0.000000;,
  0.781250;0.000000;,
  0.843750;0.000000;,
  0.968750;0.000000;,
  0.906250;0.000000;,
  0.093750;0.000000;,
  0.031250;0.000000;,
  0.218750;0.000000;,
  0.156250;0.000000;,
  0.281250;0.000000;,
  0.343750;0.000000;,
  0.593750;1.000000;,
  0.531250;1.000000;,
  0.468750;1.000000;,
  0.406250;1.000000;,
  0.343750;1.000000;,
  0.281250;1.000000;,
  0.218750;1.000000;,
  0.156250;1.000000;,
  0.093750;1.000000;,
  0.031250;1.000000;,
  0.968750;1.000000;,
  0.906250;1.000000;,
  0.843750;1.000000;,
  0.781250;1.000000;,
  0.718750;1.000000;,
  0.656250;1.000000;,
  0.000000;0.000000;,
  0.125000;0.000000;,
  0.125000;1.000000;,
  0.000000;1.000000;,
  0.250000;0.000000;,
  0.250000;1.000000;,
  0.375000;0.000000;,
  0.375000;1.000000;,
  0.500000;0.000000;,
  0.500000;1.000000;,
  0.625000;0.000000;,
  0.625000;1.000000;,
  0.750000;0.000000;,
  0.750000;1.000000;,
  0.875000;0.000000;,
  0.875000;1.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.406250;0.000000;,
  0.468750;0.000000;,
  0.531250;0.000000;,
  0.593750;0.000000;,
  0.656250;0.000000;,
  0.718750;0.000000;,
  0.781250;0.000000;,
  0.843750;0.000000;,
  0.968750;0.000000;,
  0.906250;0.000000;,
  0.093750;0.000000;,
  0.031250;0.000000;,
  0.218750;0.000000;,
  0.156250;0.000000;,
  0.281250;0.000000;,
  0.343750;0.000000;,
  0.593750;1.000000;,
  0.531250;1.000000;,
  0.468750;1.000000;,
  0.406250;1.000000;,
  0.343750;1.000000;,
  0.281250;1.000000;,
  0.218750;1.000000;,
  0.156250;1.000000;,
  0.093750;1.000000;,
  0.031250;1.000000;,
  0.968750;1.000000;,
  0.906250;1.000000;,
  0.843750;1.000000;,
  0.781250;1.000000;,
  0.718750;1.000000;,
  0.656250;1.000000;,
  0.000000;0.000000;,
  0.125000;0.000000;,
  0.125000;1.000000;,
  0.000000;1.000000;,
  0.250000;0.000000;,
  0.250000;1.000000;,
  0.375000;0.000000;,
  0.375000;1.000000;,
  0.500000;0.000000;,
  0.500000;1.000000;,
  0.625000;0.000000;,
  0.625000;1.000000;,
  0.750000;0.000000;,
  0.750000;1.000000;,
  0.875000;0.000000;,
  0.875000;1.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.406250;0.000000;,
  0.468750;0.000000;,
  0.531250;0.000000;,
  0.593750;0.000000;,
  0.656250;0.000000;,
  0.718750;0.000000;,
  0.781250;0.000000;,
  0.843750;0.000000;,
  0.968750;0.000000;,
  0.906250;0.000000;,
  0.093750;0.000000;,
  0.031250;0.000000;,
  0.218750;0.000000;,
  0.156250;0.000000;,
  0.281250;0.000000;,
  0.343750;0.000000;,
  0.593750;1.000000;,
  0.531250;1.000000;,
  0.468750;1.000000;,
  0.406250;1.000000;,
  0.343750;1.000000;,
  0.281250;1.000000;,
  0.218750;1.000000;,
  0.156250;1.000000;,
  0.093750;1.000000;,
  0.031250;1.000000;,
  0.968750;1.000000;,
  0.906250;1.000000;,
  0.843750;1.000000;,
  0.781250;1.000000;,
  0.718750;1.000000;,
  0.656250;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.493540;0.000000;,
  1.000000;1.000000;,
  0.493540;1.000000;,
  0.000000;1.000000;,
  0.506460;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.506460;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  0.493540;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.493540;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  0.493540;1.000000;,
  0.000000;0.000000;,
  0.493540;0.000000;,
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
