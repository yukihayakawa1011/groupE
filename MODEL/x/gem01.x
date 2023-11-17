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
 32;
 0.00000;0.00000;7.67620;,
 4.43414;11.38430;5.42790;,
 0.00000;11.58436;5.40088;,
 7.17458;7.56422;5.42790;,
 7.17458;-7.56422;5.42790;,
 4.43414;-11.38430;5.42790;,
 0.00000;-11.58436;5.40088;,
 -4.43414;-11.38430;5.42790;,
 -7.17458;-7.56422;5.42790;,
 -7.17458;7.56422;5.42790;,
 -4.43414;11.38430;5.42790;,
 6.27082;16.09984;0.00000;,
 0.00000;16.38276;0.00000;,
 10.14640;10.69742;0.00000;,
 10.14640;-10.69742;-0.00000;,
 6.27082;-16.09984;-0.00000;,
 0.00000;-16.38276;-0.00000;,
 -6.27082;-16.09984;0.00000;,
 -10.14640;-10.69742;0.00000;,
 -10.14640;10.69742;0.00000;,
 -6.27082;16.09984;0.00000;,
 4.43414;11.38430;-5.42790;,
 0.00000;11.64228;-5.42790;,
 7.17458;7.56422;-5.42790;,
 7.17458;-7.56422;-5.42790;,
 4.43414;-11.38430;-5.42790;,
 0.00000;-11.58436;-5.40088;,
 -4.43414;-11.38430;-5.42790;,
 -7.17458;-7.56422;-5.42790;,
 -7.17458;7.56422;-5.42790;,
 -4.43414;11.38432;-5.42790;,
 0.00000;0.00000;-7.67620;;
 
 40;
 3;0,1,2;,
 3;0,3,1;,
 3;0,4,3;,
 3;0,5,4;,
 3;0,6,5;,
 3;0,7,6;,
 3;0,8,7;,
 3;0,9,8;,
 3;0,10,9;,
 3;0,2,10;,
 4;2,1,11,12;,
 4;1,3,13,11;,
 4;3,4,14,13;,
 4;4,5,15,14;,
 4;5,6,16,15;,
 4;6,7,17,16;,
 4;7,8,18,17;,
 4;8,9,19,18;,
 4;9,10,20,19;,
 4;10,2,12,20;,
 4;12,11,21,22;,
 4;11,13,23,21;,
 4;13,14,24,23;,
 4;14,15,25,24;,
 4;15,16,26,25;,
 4;16,17,27,26;,
 4;17,18,28,27;,
 4;18,19,29,28;,
 4;19,20,30,29;,
 4;20,12,22,30;,
 3;22,21,31;,
 3;21,23,31;,
 3;23,24,31;,
 3;24,25,31;,
 3;25,26,31;,
 3;26,27,31;,
 3;27,28,31;,
 3;28,29,31;,
 3;29,30,31;,
 3;30,22,31;;
 
 MeshMaterialList {
  1;
  40;
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
   0.000000;0.850000;0.147050;1.000000;;
   14.000000;
   0.600000;0.600000;0.600000;;
   0.000000;1.000000;0.173000;;
   TextureFilename {
    "data\\TEXTURE\\Marbl24l.jpg";
   }
  }
 }
 MeshNormals {
  42;
  0.000000;-0.000000;1.000000;,
  0.000000;0.496626;0.867965;,
  0.230875;0.414735;0.880166;,
  0.542476;0.159234;0.824842;,
  0.542476;-0.159234;0.824842;,
  0.230875;-0.414735;0.880166;,
  0.000000;-0.496626;0.867965;,
  -0.230875;-0.414735;0.880166;,
  -0.542476;-0.159234;0.824842;,
  -0.542476;0.159234;0.824842;,
  -0.230875;0.414735;0.880166;,
  0.000000;0.748395;0.663254;,
  0.356958;0.641321;0.679182;,
  0.787315;0.238319;0.568629;,
  0.787315;-0.238319;0.568629;,
  0.356958;-0.641321;0.679182;,
  0.000000;-0.748395;0.663254;,
  -0.356958;-0.641321;0.679182;,
  -0.787315;-0.238319;0.568629;,
  -0.787315;0.238319;0.568629;,
  -0.356958;0.641321;0.679182;,
  0.000001;0.497062;-0.867715;,
  0.234997;0.414495;-0.879187;,
  0.542476;0.159234;-0.824842;,
  0.542476;-0.159234;-0.824842;,
  0.230875;-0.414735;-0.880166;,
  0.000000;-0.496626;-0.867965;,
  -0.230875;-0.414735;-0.880166;,
  -0.542476;-0.159234;-0.824842;,
  -0.542477;0.159233;-0.824842;,
  -0.234997;0.414495;-0.879187;,
  0.000000;-0.000643;-1.000000;,
  0.000001;0.751207;-0.660067;,
  0.360333;0.642052;-0.676705;,
  0.787315;0.238319;-0.568629;,
  0.787315;-0.238319;-0.568629;,
  0.356958;-0.641321;-0.679182;,
  0.000000;-0.748395;-0.663254;,
  -0.356958;-0.641321;-0.679182;,
  -0.787315;-0.238319;-0.568629;,
  -0.787316;0.238319;-0.568628;,
  -0.360333;0.642052;-0.676704;;
  40;
  3;0,2,1;,
  3;0,3,2;,
  3;0,4,3;,
  3;0,5,4;,
  3;0,6,5;,
  3;0,7,6;,
  3;0,8,7;,
  3;0,9,8;,
  3;0,10,9;,
  3;0,1,10;,
  4;1,2,12,11;,
  4;2,3,13,12;,
  4;3,4,14,13;,
  4;4,5,15,14;,
  4;5,6,16,15;,
  4;6,7,17,16;,
  4;7,8,18,17;,
  4;8,9,19,18;,
  4;9,10,20,19;,
  4;10,1,11,20;,
  4;32,33,22,21;,
  4;33,34,23,22;,
  4;34,35,24,23;,
  4;35,36,25,24;,
  4;36,37,26,25;,
  4;37,38,27,26;,
  4;38,39,28,27;,
  4;39,40,29,28;,
  4;40,41,30,29;,
  4;41,32,21,30;,
  3;21,22,31;,
  3;22,23,31;,
  3;23,24,31;,
  3;24,25,31;,
  3;25,26,31;,
  3;26,27,31;,
  3;27,28,31;,
  3;28,29,31;,
  3;29,30,31;,
  3;30,21,31;;
 }
 MeshTextureCoords {
  32;
  0.500000;0.500000;,
  0.937016;-0.194893;,
  0.500000;-0.207105;,
  1.207106;0.038283;,
  1.207106;0.961717;,
  0.937016;1.194893;,
  0.500000;1.207105;,
  0.062984;1.194893;,
  -0.207106;0.961717;,
  -0.207106;0.038283;,
  0.062984;-0.194893;,
  1.118034;-0.482728;,
  0.500000;-0.499998;,
  1.500000;-0.152966;,
  1.500000;1.152966;,
  1.118034;1.482728;,
  0.500000;1.499998;,
  -0.118034;1.482728;,
  -0.500000;1.152966;,
  -0.500000;-0.152966;,
  -0.118034;-0.482728;,
  0.937016;-0.194893;,
  0.500000;-0.210640;,
  1.207106;0.038283;,
  1.207106;0.961717;,
  0.937016;1.194893;,
  0.500000;1.207105;,
  0.062984;1.194893;,
  -0.207106;0.961717;,
  -0.207106;0.038283;,
  0.062984;-0.194895;,
  0.500000;0.500000;;
 }
}
