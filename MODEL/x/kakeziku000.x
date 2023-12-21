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
 205;
 29.70225;180.22081;-1.59918;,
 -29.70225;180.22081;-1.59918;,
 -29.70225;0.08469;0.00000;,
 29.70225;0.08469;0.00000;,
 -32.33019;180.20946;-0.25026;,
 -32.33019;180.87192;-1.13943;,
 -32.33019;180.20946;-1.50774;,
 -32.33019;180.20946;-0.25026;,
 -32.33019;181.14639;-0.25026;,
 -32.33019;180.20946;-0.25026;,
 -32.33019;180.87192;0.63894;,
 -32.33019;180.20946;-0.25026;,
 -32.33019;180.20946;1.00725;,
 -32.33019;180.20946;-0.25026;,
 -32.33019;179.54699;0.63894;,
 -32.33019;180.20946;-0.25026;,
 -32.33019;179.27251;-0.25026;,
 -32.33019;180.20946;-0.25026;,
 -32.33019;179.54699;-1.13943;,
 -32.33019;180.20946;-0.25026;,
 -32.33019;180.20946;-1.50774;,
 31.88928;180.20946;-0.25026;,
 31.88928;180.20946;-1.50774;,
 31.88928;180.87192;-1.13943;,
 31.88928;180.20946;-0.25026;,
 31.88928;181.14639;-0.25026;,
 31.88928;180.20946;-0.25026;,
 31.88928;180.87192;0.63894;,
 31.88928;180.20946;-0.25026;,
 31.88928;180.20946;1.00725;,
 31.88928;180.20946;-0.25026;,
 31.88928;179.54699;0.63894;,
 31.88928;180.20946;-0.25026;,
 31.88928;179.27251;-0.25026;,
 31.88928;180.20946;-0.25026;,
 31.88928;179.54699;-1.13943;,
 31.88928;180.20946;-0.25026;,
 31.88928;180.20946;-1.50774;,
 -29.70384;180.87192;0.63894;,
 -29.70384;180.20946;1.00725;,
 -29.70384;181.14639;-0.25026;,
 -29.70384;179.54699;0.63894;,
 -29.70384;180.87192;-1.13943;,
 -29.70384;179.27251;-0.25026;,
 -29.70384;180.20946;-1.50774;,
 -29.70384;179.54699;-1.13943;,
 -29.70384;180.20946;-1.50774;,
 29.78811;180.87192;0.63894;,
 29.78811;180.20946;1.00725;,
 29.78811;181.14639;-0.25026;,
 29.78811;179.54699;0.63894;,
 29.78811;180.87192;-1.13943;,
 29.78811;179.27251;-0.25026;,
 29.78811;180.20946;-1.50774;,
 29.78811;179.54699;-1.13943;,
 29.78811;180.20946;-1.50774;,
 -32.33019;0.20484;1.29336;,
 -32.33019;0.86730;0.40419;,
 -32.33019;0.20484;0.03588;,
 -32.33019;0.20484;1.29336;,
 -32.33019;1.14177;1.29336;,
 -32.33019;0.20484;1.29336;,
 -32.33019;0.86730;2.18256;,
 -32.33019;0.20484;1.29336;,
 -32.33019;0.20484;2.55087;,
 -32.33019;0.20484;1.29336;,
 -32.33019;-0.45765;2.18256;,
 -32.33019;0.20484;1.29336;,
 -32.33019;-0.73212;1.29336;,
 -32.33019;0.20484;1.29336;,
 -32.33019;-0.45765;0.40419;,
 -32.33019;0.20484;1.29336;,
 -32.33019;0.20484;0.03588;,
 31.88928;0.20484;1.29336;,
 31.88928;0.20484;0.03588;,
 31.88928;0.86730;0.40419;,
 31.88928;0.20484;1.29336;,
 31.88928;1.14177;1.29336;,
 31.88928;0.20484;1.29336;,
 31.88928;0.86730;2.18256;,
 31.88928;0.20484;1.29336;,
 31.88928;0.20484;2.55087;,
 31.88928;0.20484;1.29336;,
 31.88928;-0.45765;2.18256;,
 31.88928;0.20484;1.29336;,
 31.88928;-0.73212;1.29336;,
 31.88928;0.20484;1.29336;,
 31.88928;-0.45765;0.40419;,
 31.88928;0.20484;1.29336;,
 31.88928;0.20484;0.03588;,
 -29.70384;0.86730;2.18256;,
 -29.70384;0.20484;2.55087;,
 -29.70384;1.14177;1.29336;,
 -29.70384;-0.45765;2.18256;,
 -29.70384;0.86730;0.40419;,
 -29.70384;-0.73212;1.29336;,
 -29.70384;0.20484;0.03588;,
 -29.70384;-0.45765;0.40419;,
 -29.70384;0.20484;0.03588;,
 29.78811;0.86730;2.18256;,
 29.78811;0.20484;2.55087;,
 29.78811;1.14177;1.29336;,
 29.78811;-0.45765;2.18256;,
 29.78811;0.86730;0.40419;,
 29.78811;-0.73212;1.29336;,
 29.78811;0.20484;0.03588;,
 29.78811;-0.45765;0.40419;,
 29.78811;0.20484;0.03588;,
 -25.06933;176.70506;-1.85514;,
 25.06933;176.70506;-1.85514;,
 25.06933;4.68963;-1.85514;,
 -25.06933;4.68963;-1.85514;,
 25.06933;176.70506;-1.85514;,
 25.06933;176.70506;-1.56091;,
 25.06933;4.68963;-1.56091;,
 25.06933;4.68963;-1.85514;,
 25.06933;176.70506;-1.56091;,
 -25.06933;176.70506;-1.56091;,
 -25.06933;4.68963;-1.56091;,
 25.06933;4.68963;-1.56091;,
 -25.06933;176.70506;-1.56091;,
 -25.06933;176.70506;-1.85514;,
 -25.06933;4.68963;-1.85514;,
 -25.06933;4.68963;-1.56091;,
 25.06933;176.70506;-1.85514;,
 -25.06933;176.70506;-1.85514;,
 -25.06933;4.68963;-1.85514;,
 25.06933;4.68963;-1.85514;,
 -28.39140;181.08214;-0.25026;,
 -29.37837;181.07572;-1.13943;,
 -28.39140;181.08214;-1.50774;,
 -28.39140;181.08214;-0.25026;,
 -29.78733;181.07312;-0.25026;,
 -28.39140;181.08214;-0.25026;,
 -29.37837;181.07572;0.63894;,
 -28.39140;181.08214;-0.25026;,
 -28.39140;181.08214;1.00725;,
 -28.39140;181.08214;-0.25026;,
 -27.40446;181.08850;0.63894;,
 -28.39140;181.08214;-0.25026;,
 -26.99547;181.09111;-0.25026;,
 -28.39140;181.08214;-0.25026;,
 -27.40446;181.08850;-1.13943;,
 -28.39140;181.08214;-0.25026;,
 -28.39140;181.08214;-1.50774;,
 28.37034;181.17256;-0.25026;,
 28.37034;181.17256;-1.50774;,
 29.35347;181.15018;-1.13943;,
 28.37034;181.17256;-0.25026;,
 29.76084;181.14108;-0.25026;,
 28.37034;181.17256;-0.25026;,
 29.35347;181.15018;0.63894;,
 28.37034;181.17256;-0.25026;,
 28.37034;181.17256;1.00725;,
 28.37034;181.17256;-0.25026;,
 27.38718;181.19490;0.63894;,
 28.37034;181.17256;-0.25026;,
 26.97984;181.20405;-0.25026;,
 28.37034;181.17256;-0.25026;,
 27.38718;181.19490;-1.13943;,
 28.37034;181.17256;-0.25026;,
 28.37034;181.17256;-1.50774;,
 1.33899;208.54714;-1.13943;,
 1.33899;207.88468;-1.50774;,
 1.33899;208.82161;-0.25026;,
 1.33899;207.88468;-1.50774;,
 1.33899;207.22223;-1.13943;,
 1.33899;208.54714;0.63894;,
 1.33899;206.94771;-0.25026;,
 1.33899;207.88468;1.00725;,
 1.33899;207.22223;0.63894;,
 1.20941;206.03865;-3.30735;,
 1.55581;206.19726;-3.30735;,
 1.55581;206.19726;3.16089;,
 1.20941;206.03865;3.16089;,
 1.69931;206.57998;-3.30735;,
 1.69931;206.57998;3.16089;,
 1.55581;206.96271;-3.30735;,
 1.55581;206.96271;3.16089;,
 1.20941;207.12132;-3.30735;,
 1.20941;207.12132;3.16089;,
 0.86299;206.96271;-3.30735;,
 0.86299;206.96271;3.16089;,
 0.71949;206.57998;-3.30735;,
 0.71949;206.57998;3.16089;,
 0.86299;206.19726;-3.30735;,
 0.86299;206.19726;3.16089;,
 1.20941;206.03865;-3.30735;,
 1.20941;206.03865;3.16089;,
 1.20941;206.57998;-3.30735;,
 1.20941;206.57998;-3.30735;,
 1.20941;206.57998;-3.30735;,
 1.20941;206.57998;-3.30735;,
 1.20941;206.57998;-3.30735;,
 1.20941;206.57998;-3.30735;,
 1.20941;206.57998;-3.30735;,
 1.20941;206.57998;-3.30735;,
 1.20941;206.57998;3.16089;,
 1.20941;206.57998;3.16089;,
 1.20941;206.57998;3.16089;,
 1.20941;206.57998;3.16089;,
 1.20941;206.57998;3.16089;,
 1.20941;206.57998;3.16089;,
 1.20941;206.57998;3.16089;,
 1.20941;206.57998;3.16089;;
 
 144;
 4;0,1,2,3;,
 4;3,2,1,0;,
 3;4,5,6;,
 3;7,8,5;,
 3;9,10,8;,
 3;11,12,10;,
 3;13,14,12;,
 3;15,16,14;,
 3;17,18,16;,
 3;19,20,18;,
 3;21,22,23;,
 3;24,23,25;,
 3;26,25,27;,
 3;28,27,29;,
 3;30,29,31;,
 3;32,31,33;,
 3;34,33,35;,
 3;36,35,37;,
 4;38,10,12,39;,
 4;38,40,8,10;,
 4;39,12,14,41;,
 4;40,42,5,8;,
 4;41,14,16,43;,
 4;42,44,6,5;,
 4;43,16,18,45;,
 4;46,45,18,20;,
 4;47,38,39,48;,
 4;47,48,29,27;,
 4;47,27,25,49;,
 4;47,49,40,38;,
 4;48,39,41,50;,
 4;48,50,31,29;,
 4;49,25,23,51;,
 4;49,51,42,40;,
 4;50,41,43,52;,
 4;50,52,33,31;,
 4;51,23,22,53;,
 4;51,53,44,42;,
 4;52,43,45,54;,
 4;52,54,35,33;,
 4;55,37,35,54;,
 4;55,54,45,46;,
 3;56,57,58;,
 3;59,60,57;,
 3;61,62,60;,
 3;63,64,62;,
 3;65,66,64;,
 3;67,68,66;,
 3;69,70,68;,
 3;71,72,70;,
 3;73,74,75;,
 3;76,75,77;,
 3;78,77,79;,
 3;80,79,81;,
 3;82,81,83;,
 3;84,83,85;,
 3;86,85,87;,
 3;88,87,89;,
 4;90,62,64,91;,
 4;90,92,60,62;,
 4;91,64,66,93;,
 4;92,94,57,60;,
 4;93,66,68,95;,
 4;94,96,58,57;,
 4;95,68,70,97;,
 4;98,97,70,72;,
 4;99,90,91,100;,
 4;99,100,81,79;,
 4;99,79,77,101;,
 4;99,101,92,90;,
 4;100,91,93,102;,
 4;100,102,83,81;,
 4;101,77,75,103;,
 4;101,103,94,92;,
 4;102,93,95,104;,
 4;102,104,85,83;,
 4;103,75,74,105;,
 4;103,105,96,94;,
 4;104,95,97,106;,
 4;104,106,87,85;,
 4;107,89,87,106;,
 4;107,106,97,98;,
 4;108,109,110,111;,
 4;112,113,114,115;,
 4;116,117,118,119;,
 4;120,121,122,123;,
 4;120,113,124,125;,
 4;126,127,114,123;,
 3;128,129,130;,
 3;131,132,129;,
 3;133,134,132;,
 3;135,136,134;,
 3;137,138,136;,
 3;139,140,138;,
 3;141,142,140;,
 3;143,144,142;,
 3;145,146,147;,
 3;148,147,149;,
 3;150,149,151;,
 3;152,151,153;,
 3;154,153,155;,
 3;156,155,157;,
 3;158,157,159;,
 3;160,159,161;,
 4;162,147,146,163;,
 4;162,163,130,129;,
 4;162,129,132,164;,
 4;162,164,149,147;,
 4;165,161,159,166;,
 4;165,166,142,144;,
 4;164,132,134,167;,
 4;164,167,151,149;,
 4;166,159,157,168;,
 4;166,168,140,142;,
 4;167,134,136,169;,
 4;167,169,153,151;,
 4;168,157,155,170;,
 4;168,170,138,140;,
 4;169,136,138,170;,
 4;169,170,155,153;,
 4;171,172,173,174;,
 4;172,175,176,173;,
 4;175,177,178,176;,
 4;177,179,180,178;,
 4;179,181,182,180;,
 4;181,183,184,182;,
 4;183,185,186,184;,
 4;185,187,188,186;,
 3;189,172,171;,
 3;190,175,172;,
 3;191,177,175;,
 3;192,179,177;,
 3;193,181,179;,
 3;194,183,181;,
 3;195,185,183;,
 3;196,187,185;,
 3;197,174,173;,
 3;198,173,176;,
 3;199,176,178;,
 3;200,178,180;,
 3;201,180,182;,
 3;202,182,184;,
 3;203,184,186;,
 3;204,186,188;;
 
 MeshMaterialList {
  4;
  144;
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
  1,
  2,
  2,
  1,
  1,
  2,
  2,
  1,
  1,
  2,
  2,
  1,
  1,
  2,
  2,
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
  1,
  2,
  2,
  1,
  1,
  2,
  2,
  1,
  1,
  2,
  2,
  1,
  1,
  2,
  2,
  1,
  0,
  0,
  0,
  0,
  0,
  0,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3;;
  Material {
   0.800000;0.800000;0.800000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.300000;0.300000;0.300000;;
   TextureFilename {
    "data\\TEXTURE\\gold00.jpg";
   }
  }
  Material {
   0.140800;0.524000;0.016000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
  Material {
   0.571200;0.269600;0.156800;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
  Material {
   0.627200;0.627200;0.627200;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
 }
 MeshNormals {
  117;
  0.000000;0.008877;0.999961;,
  0.000000;-0.008877;-0.999961;,
  -1.000000;0.000000;0.000000;,
  1.000000;0.000000;0.000000;,
  0.000000;0.776700;0.629871;,
  0.000000;0.000006;1.000000;,
  0.000000;1.000000;-0.000005;,
  0.000000;-0.776696;0.629876;,
  0.000000;0.776697;-0.629875;,
  0.000000;-1.000000;-0.000005;,
  0.000000;0.000006;-1.000000;,
  0.000000;-0.776693;-0.629879;,
  0.000000;0.776700;0.629871;,
  0.000000;0.000006;1.000000;,
  0.000000;1.000000;-0.000005;,
  0.000000;-1.000000;-0.000005;,
  0.000000;0.000006;-1.000000;,
  0.000000;0.776697;-0.629875;,
  0.000000;-0.776693;-0.629879;,
  0.000000;1.000000;-0.000005;,
  0.000000;-1.000000;-0.000005;,
  -1.000000;0.000000;0.000000;,
  1.000000;0.000000;0.000000;,
  0.000000;0.776701;0.629870;,
  0.000000;0.000010;1.000000;,
  0.000000;1.000000;-0.000005;,
  0.000000;-0.776695;0.629877;,
  0.000000;0.776698;-0.629874;,
  0.000000;-1.000000;-0.000005;,
  0.000000;0.000010;-1.000000;,
  0.000000;-0.776692;-0.629881;,
  0.000000;0.000010;1.000000;,
  0.000000;1.000000;-0.000005;,
  0.000000;-0.776695;0.629877;,
  0.000000;0.000010;-1.000000;,
  0.000000;0.000010;1.000000;,
  0.000000;-1.000000;-0.000005;,
  0.000000;0.000010;-1.000000;,
  0.000000;-0.776692;-0.629881;,
  0.000000;1.000000;-0.000005;,
  0.000000;-0.776695;0.629877;,
  0.000000;0.776698;-0.629874;,
  0.000000;-1.000000;-0.000005;,
  0.000000;0.000000;-1.000000;,
  1.000000;0.000000;0.000000;,
  0.000000;0.000000;1.000000;,
  -1.000000;0.000000;0.000000;,
  0.000000;1.000000;0.000000;,
  0.000000;-1.000000;-0.000000;,
  0.006461;-0.999979;-0.000000;,
  0.006475;-0.999979;-0.000000;,
  0.006489;-0.999979;0.000025;,
  0.006467;-0.999979;-0.000000;,
  0.006489;-0.999979;-0.000025;,
  0.006475;-0.999979;-0.000000;,
  0.297504;-0.900751;0.316447;,
  0.357884;-0.933766;-0.000002;,
  0.236436;-0.967280;-0.092020;,
  -0.022735;-0.999742;-0.000000;,
  -0.022692;-0.999743;0.000068;,
  -0.022631;-0.999744;0.000000;,
  -0.022692;-0.999743;-0.000068;,
  -0.022735;-0.999742;0.000000;,
  -0.323710;-0.891294;0.317500;,
  -0.387151;-0.922017;-0.000002;,
  -0.261213;-0.960857;-0.092308;,
  -0.022686;-0.999743;-0.000000;,
  -0.246353;0.598923;-0.761972;,
  -0.000132;0.001075;-0.999999;,
  -0.666040;0.745916;-0.000004;,
  -0.277881;-0.583410;-0.763161;,
  -0.246354;0.598925;0.761971;,
  -0.707683;-0.706530;-0.000005;,
  -0.000132;0.001075;0.999999;,
  -0.572771;-0.573637;0.585555;,
  0.566995;0.579574;-0.585329;,
  0.384173;0.391044;-0.836358;,
  -0.365108;0.406455;-0.837550;,
  -0.540126;0.603595;-0.586462;,
  0.674983;0.691611;-0.257047;,
  0.698452;0.715657;-0.000004;,
  -0.386256;-0.388987;-0.836358;,
  0.366750;-0.404914;-0.837579;,
  -0.540127;0.603596;0.586459;,
  0.674984;0.691612;0.257039;,
  0.566997;0.579576;0.585326;,
  0.650569;-0.714210;-0.258196;,
  0.673402;-0.739277;-0.000004;,
  -0.365108;0.406455;0.837550;,
  0.384173;0.391044;0.836358;,
  0.544708;-0.599218;0.586711;,
  0.366750;-0.404914;0.837579;,
  -0.386256;-0.388987;0.836359;,
  0.000000;-0.000002;-1.000000;,
  0.000004;-1.000000;-0.000000;,
  0.731640;-0.681691;-0.000000;,
  1.000000;0.000000;0.000000;,
  0.731640;0.681691;0.000000;,
  0.000004;1.000000;0.000000;,
  -0.731637;0.681694;0.000000;,
  -1.000000;0.000000;0.000000;,
  -0.731637;-0.681694;0.000000;,
  0.000000;-0.000001;1.000000;,
  0.000003;-0.000007;-1.000000;,
  0.000000;-0.000004;-1.000000;,
  0.000000;-0.000004;-1.000000;,
  -0.000002;0.000002;-1.000000;,
  -0.000000;0.000004;-1.000000;,
  0.000002;0.000002;-1.000000;,
  -0.000003;-0.000007;-1.000000;,
  0.000002;0.000000;1.000000;,
  0.000002;-0.000001;1.000000;,
  0.000000;0.000000;1.000000;,
  0.000005;-0.000002;1.000000;,
  0.000000;-0.000006;1.000000;,
  -0.000005;-0.000002;1.000000;,
  0.000000;0.000001;1.000000;;
  144;
  4;0,0,0,0;,
  4;1,1,1,1;,
  3;2,2,2;,
  3;2,2,2;,
  3;2,2,2;,
  3;2,2,2;,
  3;2,2,2;,
  3;2,2,2;,
  3;2,2,2;,
  3;2,2,2;,
  3;3,3,3;,
  3;3,3,3;,
  3;3,3,3;,
  3;3,3,3;,
  3;3,3,3;,
  3;3,3,3;,
  3;3,3,3;,
  3;3,3,3;,
  4;4,4,5,5;,
  4;4,6,6,4;,
  4;5,5,7,7;,
  4;6,8,17,6;,
  4;7,7,9,9;,
  4;8,10,16,17;,
  4;9,9,18,11;,
  4;10,11,18,16;,
  4;12,4,5,13;,
  4;12,13,5,12;,
  4;12,12,19,14;,
  4;12,14,6,4;,
  4;13,5,7,7;,
  4;13,7,7,5;,
  4;14,19,8,8;,
  4;14,8,8,6;,
  4;7,7,9,15;,
  4;7,15,20,7;,
  4;8,8,16,16;,
  4;8,16,10,8;,
  4;15,9,11,11;,
  4;15,11,11,20;,
  4;16,16,11,11;,
  4;16,11,11,10;,
  3;21,21,21;,
  3;21,21,21;,
  3;21,21,21;,
  3;21,21,21;,
  3;21,21,21;,
  3;21,21,21;,
  3;21,21,21;,
  3;21,21,21;,
  3;22,22,22;,
  3;22,22,22;,
  3;22,22,22;,
  3;22,22,22;,
  3;22,22,22;,
  3;22,22,22;,
  3;22,22,22;,
  3;22,22,22;,
  4;23,23,35,24;,
  4;23,25,25,23;,
  4;24,35,26,26;,
  4;25,27,27,25;,
  4;26,26,36,28;,
  4;27,29,37,27;,
  4;28,36,38,30;,
  4;29,30,38,37;,
  4;23,23,24,31;,
  4;23,31,31,23;,
  4;23,23,39,32;,
  4;23,32,25,23;,
  4;31,24,26,33;,
  4;31,33,40,31;,
  4;32,39,41,27;,
  4;32,27,27,25;,
  4;33,26,28,28;,
  4;33,28,42,40;,
  4;27,41,34,34;,
  4;27,34,29,27;,
  4;28,28,30,30;,
  4;28,30,30,42;,
  4;34,34,30,30;,
  4;34,30,30,29;,
  4;43,43,43,43;,
  4;44,44,44,44;,
  4;45,45,45,45;,
  4;46,46,46,46;,
  4;47,47,47,47;,
  4;48,48,48,48;,
  3;49,51,50;,
  3;49,52,51;,
  3;49,53,52;,
  3;49,54,53;,
  3;49,55,54;,
  3;49,56,55;,
  3;49,57,56;,
  3;49,50,57;,
  3;66,58,59;,
  3;66,59,60;,
  3;66,60,61;,
  3;66,61,62;,
  3;66,62,63;,
  3;66,63,64;,
  3;66,64,65;,
  3;66,65,58;,
  4;67,75,76,68;,
  4;67,68,77,78;,
  4;67,78,69,69;,
  4;79,80,80,75;,
  4;68,81,81,70;,
  4;68,70,82,82;,
  4;69,69,83,71;,
  4;80,84,85,80;,
  4;70,65,64,72;,
  4;86,87,56,57;,
  4;71,83,88,73;,
  4;71,73,89,85;,
  4;72,64,63,74;,
  4;87,90,55,56;,
  4;73,91,55,90;,
  4;73,74,63,92;,
  4;94,95,95,94;,
  4;95,96,96,95;,
  4;96,97,97,96;,
  4;97,98,98,97;,
  4;98,99,99,98;,
  4;99,100,100,99;,
  4;100,101,101,100;,
  4;101,94,94,101;,
  3;93,103,104;,
  3;93,105,103;,
  3;93,106,105;,
  3;93,107,106;,
  3;93,108,107;,
  3;93,105,108;,
  3;93,109,105;,
  3;93,104,109;,
  3;102,110,111;,
  3;102,111,112;,
  3;102,112,113;,
  3;102,113,114;,
  3;102,114,115;,
  3;102,115,116;,
  3;102,116,112;,
  3;102,112,110;;
 }
 MeshTextureCoords {
  205;
  1.000000;0.500000;,
  0.000000;0.500000;,
  0.000000;1.000000;,
  1.000000;1.000000;,
  0.062500;0.000000;,
  0.125000;0.000000;,
  0.000000;0.000000;,
  0.187500;0.000000;,
  0.250000;0.000000;,
  0.312500;0.000000;,
  0.375000;0.000000;,
  0.437500;0.000000;,
  0.500000;0.000000;,
  0.562500;0.000000;,
  0.625000;0.000000;,
  0.687500;0.000000;,
  0.750000;0.000000;,
  0.812500;0.000000;,
  0.875000;0.000000;,
  0.937500;0.000000;,
  1.000000;0.000000;,
  0.062500;1.000000;,
  0.000000;1.000000;,
  0.125000;1.000000;,
  0.187500;1.000000;,
  0.250000;1.000000;,
  0.312500;1.000000;,
  0.375000;1.000000;,
  0.437500;1.000000;,
  0.500000;1.000000;,
  0.562500;1.000000;,
  0.625000;1.000000;,
  0.687500;1.000000;,
  0.750000;1.000000;,
  0.812500;1.000000;,
  0.875000;1.000000;,
  0.937500;1.000000;,
  1.000000;1.000000;,
  0.375000;0.301550;,
  0.500000;0.301550;,
  0.250000;0.301550;,
  0.625000;0.301550;,
  0.125000;0.301550;,
  0.750000;0.301550;,
  0.000000;0.301550;,
  0.875000;0.301550;,
  1.000000;0.301550;,
  0.375000;0.702080;,
  0.500000;0.702080;,
  0.250000;0.702080;,
  0.625000;0.702080;,
  0.125000;0.702080;,
  0.750000;0.702080;,
  0.000000;0.702080;,
  0.875000;0.702080;,
  1.000000;0.702080;,
  0.062500;0.000000;,
  0.125000;0.000000;,
  0.000000;0.000000;,
  0.187500;0.000000;,
  0.250000;0.000000;,
  0.312500;0.000000;,
  0.375000;0.000000;,
  0.437500;0.000000;,
  0.500000;0.000000;,
  0.562500;0.000000;,
  0.625000;0.000000;,
  0.687500;0.000000;,
  0.750000;0.000000;,
  0.812500;0.000000;,
  0.875000;0.000000;,
  0.937500;0.000000;,
  1.000000;0.000000;,
  0.062500;1.000000;,
  0.000000;1.000000;,
  0.125000;1.000000;,
  0.187500;1.000000;,
  0.250000;1.000000;,
  0.312500;1.000000;,
  0.375000;1.000000;,
  0.437500;1.000000;,
  0.500000;1.000000;,
  0.562500;1.000000;,
  0.625000;1.000000;,
  0.687500;1.000000;,
  0.750000;1.000000;,
  0.812500;1.000000;,
  0.875000;1.000000;,
  0.937500;1.000000;,
  1.000000;1.000000;,
  0.375000;0.301550;,
  0.500000;0.301550;,
  0.250000;0.301550;,
  0.625000;0.301550;,
  0.125000;0.301550;,
  0.750000;0.301550;,
  0.000000;0.301550;,
  0.875000;0.301550;,
  1.000000;0.301550;,
  0.375000;0.702080;,
  0.500000;0.702080;,
  0.250000;0.702080;,
  0.625000;0.702080;,
  0.125000;0.702080;,
  0.750000;0.702080;,
  0.000000;0.702080;,
  0.875000;0.702080;,
  1.000000;0.702080;,
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
  0.062500;0.000000;,
  0.125000;0.000000;,
  0.000000;0.000000;,
  0.187500;0.000000;,
  0.250000;0.000000;,
  0.312500;0.000000;,
  0.375000;0.000000;,
  0.437500;0.000000;,
  0.500000;0.000000;,
  0.562500;0.000000;,
  0.625000;0.000000;,
  0.687500;0.000000;,
  0.750000;0.000000;,
  0.812500;0.000000;,
  0.875000;0.000000;,
  0.937500;0.000000;,
  1.000000;0.000000;,
  0.062500;1.000000;,
  0.000000;1.000000;,
  0.125000;1.000000;,
  0.187500;1.000000;,
  0.250000;1.000000;,
  0.312500;1.000000;,
  0.375000;1.000000;,
  0.437500;1.000000;,
  0.500000;1.000000;,
  0.562500;1.000000;,
  0.625000;1.000000;,
  0.687500;1.000000;,
  0.750000;1.000000;,
  0.812500;1.000000;,
  0.875000;1.000000;,
  0.937500;1.000000;,
  1.000000;1.000000;,
  0.125000;0.609840;,
  0.000000;0.609840;,
  0.250000;0.609840;,
  1.000000;0.609840;,
  0.875000;0.609840;,
  0.375000;0.609840;,
  0.750000;0.609840;,
  0.500000;0.609840;,
  0.625000;0.609840;,
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
  0.937500;1.000000;;
 }
}
