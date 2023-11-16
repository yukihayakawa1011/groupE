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
 115;
 0.00000;3.86499;-4.94977;,
 3.50001;3.86499;-3.50001;,
 3.67901;5.45999;-3.67901;,
 0.00000;5.45999;-5.20290;,
 4.94977;3.86499;0.00000;,
 5.20290;5.45999;0.00000;,
 3.50001;3.86499;3.50001;,
 3.67901;5.45999;3.67901;,
 -0.00000;3.86499;4.94977;,
 -0.00000;5.45999;5.20290;,
 -3.50001;3.86499;3.50001;,
 -3.67901;5.45999;3.67900;,
 -4.94977;3.86499;-0.00000;,
 -5.20290;5.45999;-0.00000;,
 -3.50001;3.86499;-3.50001;,
 -3.67901;5.45999;-3.67900;,
 0.00000;3.86499;-4.94977;,
 0.00000;5.45999;-5.20290;,
 0.00000;5.71195;-6.35167;,
 4.49131;5.71195;-4.49131;,
 3.92544;3.68508;-3.92544;,
 0.00000;3.68508;-5.55142;,
 6.35167;5.71195;0.00000;,
 5.55142;3.68508;0.00000;,
 4.49131;5.71195;4.49131;,
 3.92544;3.68508;3.92544;,
 -0.00000;5.71195;6.35167;,
 -0.00000;3.68508;5.55142;,
 -4.49131;5.71195;4.49131;,
 -3.92545;3.68508;3.92544;,
 -6.35167;5.71195;-0.00000;,
 -5.55142;3.68508;-0.00000;,
 -4.49131;5.71195;-4.49131;,
 -3.92544;3.68508;-3.92544;,
 0.00000;5.71195;-6.35167;,
 0.00000;3.68508;-5.55142;,
 2.36021;1.32049;-2.36021;,
 0.00000;1.32049;-3.33783;,
 3.33783;1.32049;0.00000;,
 2.36021;1.32049;2.36021;,
 -0.00000;1.32049;3.33783;,
 -2.36021;1.32049;2.36020;,
 -3.33783;1.32049;-0.00000;,
 -2.36021;1.32049;-2.36021;,
 0.00000;1.32049;-3.33783;,
 0.73101;0.88490;-0.73101;,
 0.00000;0.88490;-1.03381;,
 1.03381;0.88490;0.00000;,
 0.73101;0.88490;0.73101;,
 -0.00000;0.88490;1.03381;,
 -0.73101;0.88490;0.73101;,
 -1.03381;0.88490;-0.00000;,
 -0.73101;0.88490;-0.73101;,
 0.00000;0.88490;-1.03381;,
 0.73101;-3.72157;-0.73101;,
 0.00000;-3.72157;-1.03381;,
 1.03381;-3.72157;0.00000;,
 0.73101;-3.72157;0.73101;,
 -0.00000;-3.72157;1.03381;,
 -0.73101;-3.72157;0.73101;,
 -1.03381;-3.72157;-0.00000;,
 -0.73101;-3.72157;-0.73101;,
 0.00000;-3.72157;-1.03381;,
 2.38387;-4.73525;-2.38387;,
 0.00000;-4.73525;-3.37130;,
 3.37130;-4.73525;0.00000;,
 2.38387;-4.73525;2.38387;,
 -0.00000;-4.73525;3.37130;,
 -2.38387;-4.73525;2.38387;,
 -3.37130;-4.73525;-0.00000;,
 -2.38387;-4.73525;-2.38387;,
 0.00000;-4.73525;-3.37130;,
 2.51831;-5.62561;-2.51831;,
 0.00000;-5.62561;-3.56143;,
 3.56143;-5.62561;0.00000;,
 2.51831;-5.62561;2.51831;,
 -0.00000;-5.62561;3.56143;,
 -2.51831;-5.62561;2.51831;,
 -3.56143;-5.62561;-0.00000;,
 -2.51831;-5.62561;-2.51831;,
 0.00000;-5.62561;-3.56143;,
 0.00000;1.47216;0.00000;,
 0.00000;1.47216;0.00000;,
 0.00000;1.47216;0.00000;,
 0.00000;1.47216;0.00000;,
 0.00000;1.47216;0.00000;,
 0.00000;1.47216;0.00000;,
 0.00000;1.47216;0.00000;,
 0.00000;1.47216;0.00000;,
 0.00000;-5.80220;-0.00000;,
 0.00000;-5.80220;-0.00000;,
 0.00000;-5.80220;-0.00000;,
 0.00000;-5.80220;-0.00000;,
 0.00000;-5.80220;-0.00000;,
 0.00000;-5.80220;-0.00000;,
 0.00000;-5.80220;-0.00000;,
 0.00000;-5.80220;-0.00000;,
 0.00000;7.22801;-6.35782;,
 4.49566;7.22801;-4.49566;,
 0.00000;7.22801;-6.35782;,
 -4.49566;7.22801;-4.49565;,
 6.35782;7.22801;0.00000;,
 -6.35782;7.22801;-0.00000;,
 4.49566;7.22801;4.49566;,
 -4.49566;7.22801;4.49565;,
 -0.00000;7.22801;6.35782;,
 0.00000;7.28904;-5.95115;,
 4.20810;7.28904;-4.20810;,
 0.00000;7.28904;-5.95115;,
 -4.20810;7.28904;-4.20810;,
 5.95115;7.28904;0.00000;,
 -5.95115;7.28904;-0.00000;,
 4.20810;7.28904;4.20810;,
 -4.20810;7.28904;4.20810;,
 -0.00000;7.28904;5.95115;;
 
 96;
 4;0,1,2,3;,
 4;1,4,5,2;,
 4;4,6,7,5;,
 4;6,8,9,7;,
 4;8,10,11,9;,
 4;10,12,13,11;,
 4;12,14,15,13;,
 4;14,16,17,15;,
 4;18,19,20,21;,
 4;19,22,23,20;,
 4;22,24,25,23;,
 4;24,26,27,25;,
 4;26,28,29,27;,
 4;28,30,31,29;,
 4;30,32,33,31;,
 4;32,34,35,33;,
 4;21,20,36,37;,
 4;20,23,38,36;,
 4;23,25,39,38;,
 4;25,27,40,39;,
 4;27,29,41,40;,
 4;29,31,42,41;,
 4;31,33,43,42;,
 4;33,35,44,43;,
 4;37,36,45,46;,
 4;36,38,47,45;,
 4;38,39,48,47;,
 4;39,40,49,48;,
 4;40,41,50,49;,
 4;41,42,51,50;,
 4;42,43,52,51;,
 4;43,44,53,52;,
 4;46,45,54,55;,
 4;45,47,56,54;,
 4;47,48,57,56;,
 4;48,49,58,57;,
 4;49,50,59,58;,
 4;50,51,60,59;,
 4;51,52,61,60;,
 4;52,53,62,61;,
 4;55,54,63,64;,
 4;54,56,65,63;,
 4;56,57,66,65;,
 4;57,58,67,66;,
 4;58,59,68,67;,
 4;59,60,69,68;,
 4;60,61,70,69;,
 4;61,62,71,70;,
 4;64,63,72,73;,
 4;63,65,74,72;,
 4;65,66,75,74;,
 4;66,67,76,75;,
 4;67,68,77,76;,
 4;68,69,78,77;,
 4;69,70,79,78;,
 4;70,71,80,79;,
 3;81,1,0;,
 3;82,4,1;,
 3;83,6,4;,
 3;84,8,6;,
 3;85,10,8;,
 3;86,12,10;,
 3;87,14,12;,
 3;88,16,14;,
 3;89,73,72;,
 3;90,72,74;,
 3;91,74,75;,
 3;92,75,76;,
 3;93,76,77;,
 3;94,77,78;,
 3;95,78,79;,
 3;96,79,80;,
 4;97,98,19,18;,
 4;99,34,32,100;,
 4;98,101,22,19;,
 4;100,32,30,102;,
 4;101,103,24,22;,
 4;102,30,28,104;,
 4;103,105,26,24;,
 4;104,28,26,105;,
 4;106,3,2,107;,
 4;106,107,98,97;,
 4;108,99,100,109;,
 4;108,109,15,17;,
 4;107,2,5,110;,
 4;107,110,101,98;,
 4;109,100,102,111;,
 4;109,111,13,15;,
 4;110,5,7,112;,
 4;110,112,103,101;,
 4;111,102,104,113;,
 4;111,113,11,13;,
 4;112,7,9,114;,
 4;112,114,105,103;,
 4;113,104,105,114;,
 4;113,114,9,11;;
 
 MeshMaterialList {
  1;
  96;
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
   0.800000;0.630588;0.188235;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.730000;0.575412;0.171765;;
  }
 }
 MeshNormals {
  114;
  -0.000000;1.000000;0.000000;,
  0.000000;0.609141;0.793062;,
  -0.560780;0.609141;0.560780;,
  -0.793062;0.609141;-0.000000;,
  -0.560780;0.609141;-0.560780;,
  0.000000;0.609141;-0.793062;,
  0.560780;0.609141;-0.560780;,
  0.793062;0.609141;0.000000;,
  0.560780;0.609141;0.560780;,
  0.000000;0.269975;0.962867;,
  -0.680850;0.269975;0.680850;,
  -0.962867;0.269975;-0.000000;,
  -0.680850;0.269975;-0.680850;,
  0.000000;0.269975;-0.962867;,
  0.680850;0.269974;-0.680850;,
  0.962867;0.269975;0.000000;,
  0.680850;0.269975;0.680850;,
  -0.000000;-0.189823;-0.981818;,
  0.694250;-0.189823;-0.694250;,
  0.981818;-0.189823;0.000000;,
  0.694250;-0.189823;0.694250;,
  -0.000000;-0.189823;0.981818;,
  -0.694251;-0.189823;0.694250;,
  -0.981818;-0.189823;-0.000000;,
  -0.694250;-0.189823;-0.694250;,
  -0.000000;-0.536812;-0.843702;,
  0.596588;-0.536812;-0.596588;,
  0.843702;-0.536812;0.000000;,
  0.596588;-0.536812;0.596588;,
  -0.000000;-0.536812;0.843702;,
  -0.596588;-0.536811;0.596587;,
  -0.843702;-0.536812;-0.000000;,
  -0.596588;-0.536812;-0.596588;,
  0.000000;-0.879519;-0.475864;,
  0.336487;-0.879519;-0.336487;,
  0.475864;-0.879519;0.000000;,
  0.336487;-0.879519;0.336487;,
  -0.000000;-0.879519;0.475864;,
  -0.336487;-0.879519;0.336487;,
  -0.475864;-0.879519;-0.000000;,
  -0.336487;-0.879519;-0.336487;,
  0.000000;-0.982595;-0.185763;,
  0.131355;-0.982594;-0.131355;,
  0.185763;-0.982595;0.000000;,
  0.131355;-0.982594;0.131355;,
  -0.000000;-0.982595;0.185763;,
  -0.131355;-0.982595;0.131355;,
  -0.185763;-0.982595;-0.000000;,
  -0.131355;-0.982594;-0.131355;,
  0.000000;0.000000;-1.000000;,
  0.707107;0.000000;-0.707107;,
  1.000000;0.000000;0.000000;,
  0.707107;0.000000;0.707107;,
  -0.000000;0.000000;1.000000;,
  -0.707107;0.000000;0.707107;,
  -1.000000;0.000000;-0.000000;,
  -0.707107;0.000000;-0.707107;,
  0.000000;0.645827;-0.763483;,
  0.539864;0.645827;-0.539864;,
  0.763483;0.645827;0.000000;,
  0.539864;0.645827;0.539864;,
  -0.000000;0.645827;0.763483;,
  -0.539864;0.645827;0.539864;,
  -0.763483;0.645827;0.000000;,
  -0.539864;0.645827;-0.539864;,
  0.000000;0.208837;-0.977950;,
  0.691515;0.208837;-0.691515;,
  0.977950;0.208837;0.000000;,
  0.691515;0.208837;0.691515;,
  -0.000000;0.208837;0.977950;,
  -0.691516;0.208837;0.691515;,
  -0.977951;0.208837;0.000000;,
  -0.691516;0.208837;-0.691515;,
  -0.000000;-1.000000;-0.000000;,
  -0.000000;-0.004053;-0.999992;,
  0.707101;-0.004054;-0.707101;,
  -0.707101;-0.004053;-0.707101;,
  0.999992;-0.004054;0.000000;,
  -0.999992;-0.004053;-0.000000;,
  0.707101;-0.004054;0.707101;,
  -0.707101;-0.004053;0.707101;,
  -0.000000;-0.004053;0.999992;,
  0.000000;0.378635;0.925546;,
  -0.654460;0.378635;0.654460;,
  -0.104953;0.988923;-0.104953;,
  -0.925546;0.378635;-0.000000;,
  -0.148426;0.988923;-0.000000;,
  -0.654460;0.378635;-0.654460;,
  -0.104953;0.988923;0.104953;,
  0.000000;0.378635;-0.925546;,
  0.000000;0.917446;-0.397860;,
  0.281330;0.917446;-0.281329;,
  0.397860;0.917446;0.000000;,
  0.281329;0.917446;0.281330;,
  -0.000000;0.917446;0.397860;,
  -0.281330;0.917446;0.281329;,
  -0.397860;0.917446;-0.000000;,
  -0.281329;0.917446;-0.281329;,
  0.000000;-0.998773;-0.049524;,
  0.035019;-0.998773;-0.035019;,
  0.049524;-0.998773;0.000000;,
  0.035019;-0.998773;0.035019;,
  -0.000000;-0.998773;0.049524;,
  -0.035019;-0.998773;0.035019;,
  -0.049524;-0.998773;0.000000;,
  -0.035019;-0.998773;-0.035019;,
  -0.000000;0.988923;-0.148426;,
  0.104953;0.988923;-0.104953;,
  0.654460;0.378635;0.654460;,
  0.148426;0.988923;0.000000;,
  0.925546;0.378635;0.000000;,
  0.104953;0.988923;0.104953;,
  0.654460;0.378635;-0.654460;,
  -0.000000;0.988923;0.148426;;
  96;
  4;1,2,10,9;,
  4;2,3,11,10;,
  4;3,4,12,11;,
  4;4,5,13,12;,
  4;5,6,14,13;,
  4;6,7,15,14;,
  4;7,8,16,15;,
  4;8,1,9,16;,
  4;17,18,26,25;,
  4;18,19,27,26;,
  4;19,20,28,27;,
  4;20,21,29,28;,
  4;21,22,30,29;,
  4;22,23,31,30;,
  4;23,24,32,31;,
  4;24,17,25,32;,
  4;25,26,34,33;,
  4;26,27,35,34;,
  4;27,28,36,35;,
  4;28,29,37,36;,
  4;29,30,38,37;,
  4;30,31,39,38;,
  4;31,32,40,39;,
  4;32,25,33,40;,
  4;33,34,42,41;,
  4;34,35,43,42;,
  4;35,36,44,43;,
  4;36,37,45,44;,
  4;37,38,46,45;,
  4;38,39,47,46;,
  4;39,40,48,47;,
  4;40,33,41,48;,
  4;49,50,50,49;,
  4;50,51,51,50;,
  4;51,52,52,51;,
  4;52,53,53,52;,
  4;53,54,54,53;,
  4;54,55,55,54;,
  4;55,56,56,55;,
  4;56,49,49,56;,
  4;90,91,58,57;,
  4;91,92,59,58;,
  4;92,93,60,59;,
  4;93,94,61,60;,
  4;94,95,62,61;,
  4;95,96,63,62;,
  4;96,97,64,63;,
  4;97,90,57,64;,
  4;57,58,66,65;,
  4;58,59,67,66;,
  4;59,60,68,67;,
  4;60,61,69,68;,
  4;61,62,70,69;,
  4;62,63,71,70;,
  4;63,64,72,71;,
  4;64,57,65,72;,
  3;0,2,1;,
  3;0,3,2;,
  3;0,4,3;,
  3;0,5,4;,
  3;0,6,5;,
  3;0,7,6;,
  3;0,8,7;,
  3;0,1,8;,
  3;73,98,99;,
  3;73,99,100;,
  3;73,100,101;,
  3;73,101,102;,
  3;73,102,103;,
  3;73,103,104;,
  3;73,104,105;,
  3;73,105,98;,
  4;74,75,18,17;,
  4;74,17,24,76;,
  4;75,77,19,18;,
  4;76,24,23,78;,
  4;77,79,20,19;,
  4;78,23,22,80;,
  4;79,81,21,20;,
  4;80,22,21,81;,
  4;82,9,10,83;,
  4;106,107,107,106;,
  4;106,106,84,84;,
  4;82,108,16,9;,
  4;83,10,11,85;,
  4;107,109,109,107;,
  4;84,84,86,86;,
  4;108,110,15,16;,
  4;85,11,12,87;,
  4;109,111,111,109;,
  4;86,86,88,88;,
  4;110,112,14,15;,
  4;87,12,13,89;,
  4;111,113,113,111;,
  4;88,88,113,113;,
  4;112,89,13,14;;
 }
 MeshTextureCoords {
  115;
  0.000000;0.000000;,
  0.125000;0.000000;,
  0.125000;0.125000;,
  0.000000;0.125000;,
  0.250000;0.000000;,
  0.250000;0.125000;,
  0.375000;0.000000;,
  0.375000;0.125000;,
  0.500000;0.000000;,
  0.500000;0.125000;,
  0.625000;0.000000;,
  0.625000;0.125000;,
  0.750000;0.000000;,
  0.750000;0.125000;,
  0.875000;0.000000;,
  0.875000;0.125000;,
  1.000000;0.000000;,
  1.000000;0.125000;,
  0.000000;0.250000;,
  0.125000;0.250000;,
  0.125000;0.375000;,
  0.000000;0.375000;,
  0.250000;0.250000;,
  0.250000;0.375000;,
  0.375000;0.250000;,
  0.375000;0.375000;,
  0.500000;0.250000;,
  0.500000;0.375000;,
  0.625000;0.250000;,
  0.625000;0.375000;,
  0.750000;0.250000;,
  0.750000;0.375000;,
  0.875000;0.250000;,
  0.875000;0.375000;,
  1.000000;0.250000;,
  1.000000;0.375000;,
  0.125000;0.500000;,
  0.000000;0.500000;,
  0.250000;0.500000;,
  0.375000;0.500000;,
  0.500000;0.500000;,
  0.625000;0.500000;,
  0.750000;0.500000;,
  0.875000;0.500000;,
  1.000000;0.500000;,
  0.125000;0.625000;,
  0.000000;0.625000;,
  0.250000;0.625000;,
  0.375000;0.625000;,
  0.500000;0.625000;,
  0.625000;0.625000;,
  0.750000;0.625000;,
  0.875000;0.625000;,
  1.000000;0.625000;,
  0.125000;0.750000;,
  0.000000;0.750000;,
  0.250000;0.750000;,
  0.375000;0.750000;,
  0.500000;0.750000;,
  0.625000;0.750000;,
  0.750000;0.750000;,
  0.875000;0.750000;,
  1.000000;0.750000;,
  0.125000;0.875000;,
  0.000000;0.875000;,
  0.250000;0.875000;,
  0.375000;0.875000;,
  0.500000;0.875000;,
  0.625000;0.875000;,
  0.750000;0.875000;,
  0.875000;0.875000;,
  1.000000;0.875000;,
  0.125000;1.000000;,
  0.000000;1.000000;,
  0.250000;1.000000;,
  0.375000;1.000000;,
  0.500000;1.000000;,
  0.625000;1.000000;,
  0.750000;1.000000;,
  0.875000;1.000000;,
  1.000000;1.000000;,
  0.062500;0.000000;,
  0.187500;0.000000;,
  0.312500;0.000000;,
  0.437500;0.000000;,
  0.562500;0.000000;,
  0.687500;0.000000;,
  0.812500;0.000000;,
  0.937500;0.000000;,
  0.062500;1.000000;,
  0.187500;1.000000;,
  0.312500;1.000000;,
  0.437500;1.000000;,
  0.562500;1.000000;,
  0.687500;1.000000;,
  0.812500;1.000000;,
  0.937500;1.000000;,
  0.000000;0.204464;,
  0.125000;0.204464;,
  1.000000;0.204464;,
  0.875000;0.204464;,
  0.250000;0.204464;,
  0.750000;0.204464;,
  0.375000;0.204464;,
  0.625000;0.204464;,
  0.500000;0.204464;,
  0.000000;0.176526;,
  0.125000;0.176526;,
  1.000000;0.176526;,
  0.875000;0.176526;,
  0.250000;0.176526;,
  0.750000;0.176526;,
  0.375000;0.176526;,
  0.625000;0.176526;,
  0.500000;0.176526;;
 }
}