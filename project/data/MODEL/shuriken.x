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
 168;
 5.47243;-0.07100;-7.83069;,
 25.49923;-0.07100;0.00001;,
 5.47243;-2.32733;-7.85074;,
 25.49923;-0.07100;0.00001;,
 7.08571;-2.95901;0.00001;,
 25.49923;-0.07100;0.00001;,
 5.28151;-2.27177;7.65764;,
 25.49923;-0.07100;0.00001;,
 5.28151;-0.07100;7.63811;,
 25.49923;-0.07100;0.00001;,
 5.28151;2.12977;7.65764;,
 25.49923;-0.07100;0.00001;,
 7.08571;2.81699;0.00001;,
 25.49923;-0.07100;0.00001;,
 5.47243;2.18534;-7.85074;,
 25.49923;-0.07100;0.00001;,
 5.47243;-0.07100;-7.83069;,
 6.17921;-0.07100;0.10989;,
 5.47243;-0.07100;-7.83069;,
 5.47243;-2.32733;-7.85074;,
 7.08571;-2.95901;0.00001;,
 5.28151;-2.27177;7.65764;,
 5.28151;-0.07100;7.63811;,
 5.28151;2.12977;7.65764;,
 7.08571;2.81699;0.00001;,
 5.47243;2.18534;-7.85074;,
 -6.45271;-0.07100;-5.38121;,
 0.17295;-0.07100;-24.49927;,
 -6.46971;-2.27177;-5.38121;,
 0.17295;-0.07100;-24.49927;,
 0.20007;-2.95901;-7.32657;,
 0.17295;-0.07100;-24.49927;,
 7.01734;-2.32733;-5.60076;,
 0.17295;-0.07100;-24.49927;,
 6.99993;-0.07100;-5.60076;,
 0.17295;-0.07100;-24.49927;,
 7.01734;2.18534;-5.60076;,
 0.17295;-0.07100;-24.49927;,
 0.20007;2.81698;-7.32657;,
 0.17295;-0.07100;-24.49927;,
 -6.46971;2.12977;-5.38121;,
 0.17295;-0.07100;-24.49927;,
 -6.45271;-0.07100;-5.38121;,
 -0.60691;-0.07096;-5.78526;,
 -6.45271;-0.07100;-5.38121;,
 -6.46971;-2.27177;-5.38121;,
 0.20007;-2.95901;-7.32657;,
 7.01734;-2.32733;-5.60076;,
 6.99993;-0.07100;-5.60076;,
 7.01734;2.18534;-5.60076;,
 0.20007;2.81698;-7.32657;,
 -6.46971;2.12977;-5.38121;,
 -5.19191;-0.07100;7.83174;,
 -25.87488;-0.13888;0.23691;,
 -5.19191;-2.32733;7.85177;,
 -25.87488;-0.13888;0.23691;,
 -6.89803;-2.95901;0.00117;,
 -25.87488;-0.13888;0.23691;,
 -5.00097;-2.27177;-7.65661;,
 -25.87488;-0.13888;0.23691;,
 -5.00097;-0.07100;-7.63707;,
 -25.87488;-0.13888;0.23691;,
 -4.37651;2.19763;-7.89278;,
 -25.87488;-0.13888;0.23691;,
 -6.89803;2.81699;0.00117;,
 -25.87488;-0.13888;0.23691;,
 -5.19191;2.18536;7.85177;,
 -25.87488;-0.13888;0.23691;,
 -5.19191;-0.07100;7.83174;,
 -5.71835;0.47228;0.14375;,
 -5.19191;-0.07100;7.83174;,
 -5.19191;-2.32733;7.85177;,
 -6.89803;-2.95901;0.00117;,
 -5.00097;-2.27177;-7.65661;,
 -5.00097;-0.07100;-7.63707;,
 -4.37651;2.19763;-7.89278;,
 -6.89803;2.81699;0.00117;,
 -5.19191;2.18536;7.85177;,
 6.83157;-0.07100;5.38145;,
 0.17225;-0.07100;24.49930;,
 6.84857;-2.27177;5.38145;,
 0.17225;-0.07100;24.49930;,
 0.19899;-2.95901;7.32655;,
 0.17225;-0.07100;24.49930;,
 -6.63851;-2.32733;5.60099;,
 0.17225;-0.07100;24.49930;,
 -6.62110;-0.07100;5.60099;,
 0.17225;-0.07100;24.49930;,
 -6.63851;2.18534;5.60099;,
 0.17225;-0.07100;24.49930;,
 0.19899;2.81699;7.32655;,
 0.17225;-0.07100;24.49930;,
 6.84857;2.12977;5.38145;,
 0.17225;-0.07100;24.49930;,
 6.83157;-0.07100;5.38145;,
 0.20089;-0.07096;5.96981;,
 6.83157;-0.07100;5.38145;,
 6.84857;-2.27177;5.38145;,
 0.19899;-2.95901;7.32655;,
 -6.63851;-2.32733;5.60099;,
 -6.62110;-0.07100;5.60099;,
 -6.63851;2.18534;5.60099;,
 0.19899;2.81699;7.32655;,
 6.84857;2.12977;5.38145;,
 5.78513;-3.32481;-0.34805;,
 5.78513;3.46683;-0.34805;,
 4.39181;3.46683;-3.71180;,
 4.39181;-3.32481;-3.71180;,
 5.78513;-3.32481;0.34803;,
 5.78513;3.46683;0.34803;,
 3.89961;3.46683;-4.20399;,
 3.89961;-3.32481;-4.20399;,
 7.32689;2.81134;-6.64688;,
 9.93593;2.81134;-0.34805;,
 9.93593;2.81134;0.34803;,
 6.83468;2.81134;-7.13907;,
 7.32689;-2.66932;-6.64688;,
 9.93593;-2.66932;-0.34805;,
 9.93593;-2.66932;0.34803;,
 6.83468;-2.66932;-7.13907;,
 0.53587;3.46683;-5.59731;,
 0.53587;-3.32481;-5.59731;,
 -0.16021;3.46683;-5.59731;,
 -0.16021;-3.32481;-5.59731;,
 0.53587;2.81134;-9.74812;,
 -0.16021;2.81134;-9.74812;,
 0.53587;-2.66932;-9.74812;,
 -0.16021;-2.66932;-9.74812;,
 -3.52395;3.46683;-4.20399;,
 -3.42471;-3.32482;-4.31414;,
 -4.01615;3.46683;-3.71180;,
 -4.01615;-3.32481;-3.71180;,
 -6.45903;2.81134;-7.13907;,
 -6.95123;2.81134;-6.64688;,
 -6.45903;-2.66932;-7.13907;,
 -6.95123;-2.66932;-6.64688;,
 -5.40947;3.46683;-0.34805;,
 -5.40947;-3.32481;-0.34805;,
 -5.40947;3.46683;0.34803;,
 -5.40947;-3.32481;0.34803;,
 -9.56028;2.81134;-0.34805;,
 -9.56028;2.81134;0.34803;,
 -9.56028;-2.66932;-0.34805;,
 -9.56028;-2.66932;0.34803;,
 -4.01615;3.46683;3.71177;,
 -4.01615;-3.32481;3.71177;,
 -3.52395;3.46683;4.20397;,
 -3.52395;-3.32481;4.20397;,
 -6.95123;2.81134;6.64684;,
 -6.45903;2.81134;7.13905;,
 -6.95123;-2.66932;6.64684;,
 -6.45903;-2.66932;7.13905;,
 -0.16021;3.46683;5.59729;,
 -0.16021;-3.32481;5.59729;,
 0.53587;3.46683;5.59729;,
 0.53587;-3.32481;5.59729;,
 -0.16021;2.81134;9.74809;,
 0.53587;2.81134;9.74809;,
 -0.16021;-2.66932;9.74809;,
 0.53587;-2.66932;9.74809;,
 3.89961;3.46683;4.20397;,
 3.89961;-3.32481;4.20397;,
 4.39181;3.46683;3.71177;,
 4.39181;-3.32481;3.71177;,
 6.83468;2.81134;7.13905;,
 7.32689;2.81134;6.64684;,
 6.83468;-2.66932;7.13905;,
 7.32689;-2.66932;6.64684;;
 
 128;
 3;0,1,2;,
 3;2,3,4;,
 3;4,5,6;,
 3;6,7,8;,
 3;8,9,10;,
 3;10,11,12;,
 3;12,13,14;,
 3;14,15,16;,
 3;17,18,19;,
 3;17,19,20;,
 3;17,20,21;,
 3;17,21,22;,
 3;17,22,23;,
 3;17,23,24;,
 3;17,24,25;,
 3;17,25,18;,
 3;26,27,28;,
 3;28,29,30;,
 3;30,31,32;,
 3;32,33,34;,
 3;34,35,36;,
 3;36,37,38;,
 3;38,39,40;,
 3;40,41,42;,
 3;43,44,45;,
 3;43,45,46;,
 3;43,46,47;,
 3;43,47,48;,
 3;43,48,49;,
 3;43,49,50;,
 3;43,50,51;,
 3;43,51,44;,
 3;52,53,54;,
 3;54,55,56;,
 3;56,57,58;,
 3;58,59,60;,
 3;60,61,62;,
 3;62,63,64;,
 3;64,65,66;,
 3;66,67,68;,
 3;69,70,71;,
 3;69,71,72;,
 3;69,72,73;,
 3;69,73,74;,
 3;69,74,75;,
 3;69,75,76;,
 3;69,76,77;,
 3;69,77,70;,
 3;78,79,80;,
 3;80,81,82;,
 3;82,83,84;,
 3;84,85,86;,
 3;86,87,88;,
 3;88,89,90;,
 3;90,91,92;,
 3;92,93,94;,
 3;95,96,97;,
 3;95,97,98;,
 3;95,98,99;,
 3;95,99,100;,
 3;95,100,101;,
 3;95,101,102;,
 3;95,102,103;,
 3;95,103,96;,
 4;104,105,106,107;,
 4;104,108,109,105;,
 4;110,111,107,106;,
 4;112,106,105,113;,
 4;109,114,113,105;,
 4;112,115,110,106;,
 4;116,112,113,117;,
 4;114,118,117,113;,
 4;116,119,115,112;,
 4;107,116,117,104;,
 4;118,108,104,117;,
 4;107,111,119,116;,
 4;111,110,120,121;,
 4;122,123,121,120;,
 4;124,120,110,115;,
 4;124,125,122,120;,
 4;126,124,115,119;,
 4;126,127,125,124;,
 4;121,126,119,111;,
 4;121,123,127,126;,
 4;123,122,128,129;,
 4;130,131,129,128;,
 4;132,128,122,125;,
 4;132,133,130,128;,
 4;134,132,125,127;,
 4;134,135,133,132;,
 4;129,134,127,123;,
 4;129,131,135,134;,
 4;131,130,136,137;,
 4;138,139,137,136;,
 4;140,136,130,133;,
 4;140,141,138,136;,
 4;142,140,133,135;,
 4;142,143,141,140;,
 4;137,142,135,131;,
 4;137,139,143,142;,
 4;139,138,144,145;,
 4;146,147,145,144;,
 4;148,144,138,141;,
 4;148,149,146,144;,
 4;150,148,141,143;,
 4;150,151,149,148;,
 4;145,150,143,139;,
 4;145,147,151,150;,
 4;147,146,152,153;,
 4;154,155,153,152;,
 4;156,152,146,149;,
 4;156,157,154,152;,
 4;158,156,149,151;,
 4;158,159,157,156;,
 4;153,158,151,147;,
 4;153,155,159,158;,
 4;155,154,160,161;,
 4;162,163,161,160;,
 4;164,160,154,157;,
 4;164,165,162,160;,
 4;166,164,157,159;,
 4;166,167,165,164;,
 4;161,166,159,155;,
 4;161,163,167,166;,
 4;163,162,109,108;,
 4;114,109,162,165;,
 4;118,114,165,167;,
 4;108,118,167,163;;
 
 MeshMaterialList {
  1;
  128;
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
   0.072000;0.103200;0.288800;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.044100;0.063210;0.176890;;
  }
 }
 MeshNormals {
  148;
  0.364162;0.000000;-0.931336;,
  0.364150;0.008272;-0.931304;,
  0.154943;-0.987900;0.006824;,
  0.153747;-0.980274;0.124199;,
  0.353413;0.000000;0.935468;,
  0.353400;-0.008305;0.935435;,
  0.154943;0.987900;0.006824;,
  0.153996;0.981857;-0.110644;,
  -0.999894;-0.000000;-0.014565;,
  -0.944866;0.000000;-0.327458;,
  -0.944841;0.007298;-0.327449;,
  -0.008093;-0.986122;-0.165827;,
  0.132237;-0.977457;-0.164592;,
  0.940514;0.000000;-0.339755;,
  0.940489;-0.007261;-0.339746;,
  -0.008093;0.986122;-0.165826;,
  -0.148257;0.975292;-0.163783;,
  0.024591;0.000003;0.999698;,
  -0.344698;-0.000000;0.938714;,
  -0.344710;0.008329;0.938672;,
  -0.147076;-0.989100;-0.007044;,
  -0.147363;-0.981207;-0.124564;,
  -0.352941;-0.000004;-0.935646;,
  -0.352905;-0.008315;-0.935622;,
  -0.153989;0.988047;-0.007144;,
  -0.151581;0.982084;0.111958;,
  0.999758;-0.001163;0.021987;,
  0.944349;0.000000;0.328945;,
  0.944324;0.007294;0.328936;,
  0.008618;-0.986113;0.165851;,
  -0.131753;-0.977589;0.164199;,
  -0.941047;0.000000;0.338276;,
  -0.941022;-0.007265;0.338267;,
  0.008618;0.986113;0.165851;,
  0.148816;0.975133;0.164223;,
  -0.017043;0.000003;-0.999855;,
  -0.980785;0.000000;0.195092;,
  -0.831469;0.000000;0.555572;,
  0.155907;0.987245;-0.032256;,
  0.133051;0.987245;-0.087434;,
  0.980786;0.000000;-0.195089;,
  0.831470;0.000000;-0.555570;,
  -0.555572;0.000000;0.831469;,
  -0.195092;0.000000;0.980785;,
  0.087434;0.987245;-0.133051;,
  0.032256;0.987245;-0.155907;,
  0.555569;0.000000;-0.831471;,
  0.195089;0.000000;-0.980785;,
  0.190630;-0.002392;0.981659;,
  0.553687;-0.002636;0.832720;,
  -0.032256;0.987245;-0.155907;,
  -0.087434;0.987245;-0.133050;,
  -0.195089;0.000000;-0.980785;,
  -0.555569;0.000000;-0.831470;,
  0.832735;-0.000238;0.553672;,
  0.980785;0.000000;0.195092;,
  -0.133050;0.987245;-0.087434;,
  -0.155907;0.987245;-0.032256;,
  -0.831470;0.000000;-0.555569;,
  -0.980785;0.000000;-0.195089;,
  0.980785;0.000000;-0.195092;,
  0.831469;0.000000;-0.555572;,
  -0.155907;0.987245;0.032256;,
  -0.133051;0.987245;0.087434;,
  -0.980785;0.000000;0.195089;,
  -0.831471;0.000000;0.555569;,
  0.555572;0.000000;-0.831469;,
  0.195092;0.000000;-0.980785;,
  -0.087434;0.987245;0.133051;,
  -0.032256;0.987245;0.155907;,
  -0.555570;0.000000;0.831470;,
  -0.195089;0.000000;0.980786;,
  -0.195092;0.000000;-0.980785;,
  -0.555572;0.000000;-0.831469;,
  0.032256;0.987245;0.155907;,
  0.087434;0.987245;0.133051;,
  0.195089;0.000000;0.980785;,
  0.555569;0.000000;0.831470;,
  -0.831469;0.000000;-0.555572;,
  -0.980785;0.000000;-0.195092;,
  0.133051;0.987245;0.087434;,
  0.155907;0.987245;0.032256;,
  0.831470;0.000000;0.555569;,
  0.980785;0.000000;0.195089;,
  0.153996;-0.981857;-0.110647;,
  0.353400;0.008305;0.935435;,
  0.153747;0.980274;0.124197;,
  0.364150;-0.008272;-0.931304;,
  -0.996062;-0.000000;0.088658;,
  -0.979627;-0.152825;0.130292;,
  -0.954163;-0.298984;-0.013505;,
  -0.976537;-0.145660;-0.158617;,
  -0.992965;-0.000000;-0.118406;,
  -0.976537;0.145660;-0.158617;,
  -0.954163;0.298984;-0.013505;,
  -0.979627;0.152825;0.130292;,
  -0.148263;-0.975291;-0.163784;,
  0.940489;0.007261;-0.339746;,
  0.132231;0.977458;-0.164591;,
  -0.944841;-0.007298;-0.327449;,
  0.068952;-0.000000;0.997620;,
  0.146103;-0.211803;0.966330;,
  0.024022;-0.465465;0.884740;,
  -0.100185;-0.259994;0.960399;,
  -0.024247;-0.000000;0.999706;,
  -0.100185;0.260002;0.960397;,
  0.024022;0.465478;0.884734;,
  0.146103;0.211809;0.966329;,
  -0.144749;-0.983271;0.110574;,
  -0.352952;0.008307;-0.935604;,
  -0.154207;0.979953;-0.126145;,
  -0.344662;-0.008329;0.938690;,
  0.997664;-0.000000;-0.068316;,
  0.979325;-0.159265;-0.124732;,
  0.945467;-0.325522;0.011269;,
  0.974956;-0.165962;0.148047;,
  0.986754;-0.127811;0.099901;,
  0.977042;0.104615;0.185594;,
  0.891486;0.451087;0.042102;,
  0.967582;0.224367;-0.115948;,
  0.148818;-0.975133;0.164223;,
  -0.941022;0.007265;0.338267;,
  -0.131750;0.977589;0.164199;,
  0.944324;-0.007294;0.328936;,
  -0.088386;-0.000000;-0.996086;,
  -0.155974;-0.213295;-0.964457;,
  -0.015221;-0.425140;-0.905000;,
  0.123076;-0.214690;-0.968897;,
  0.053985;-0.000000;-0.998542;,
  0.123076;0.214695;-0.968895;,
  -0.015221;0.425150;-0.904995;,
  -0.155974;0.213300;-0.964456;,
  0.133047;-0.987246;-0.087432;,
  0.155902;-0.987246;-0.032255;,
  0.155902;-0.987246;0.032255;,
  0.087432;-0.987246;-0.133047;,
  0.032255;-0.987246;-0.155902;,
  -0.031698;-0.987161;-0.156548;,
  -0.087177;-0.987209;-0.133486;,
  -0.133343;-0.987225;-0.087216;,
  -0.155902;-0.987246;-0.032255;,
  -0.155902;-0.987246;0.032255;,
  -0.133047;-0.987246;0.087432;,
  -0.087432;-0.987246;0.133047;,
  -0.032255;-0.987246;0.155902;,
  0.032255;-0.987246;0.155902;,
  0.087432;-0.987246;0.133047;,
  0.133047;-0.987246;0.087432;;
  128;
  3;0,0,1;,
  3;84,2,2;,
  3;2,2,3;,
  3;85,4,4;,
  3;4,4,5;,
  3;86,6,6;,
  3;6,6,7;,
  3;87,0,0;,
  3;8,88,89;,
  3;8,89,90;,
  3;8,90,91;,
  3;8,91,92;,
  3;8,92,93;,
  3;8,93,94;,
  3;8,94,95;,
  3;8,95,88;,
  3;9,9,10;,
  3;96,11,11;,
  3;11,11,12;,
  3;97,13,13;,
  3;13,13,14;,
  3;98,15,15;,
  3;15,15,16;,
  3;99,9,9;,
  3;17,100,101;,
  3;17,101,102;,
  3;17,102,103;,
  3;17,103,104;,
  3;17,104,105;,
  3;17,105,106;,
  3;17,106,107;,
  3;17,107,100;,
  3;18,18,19;,
  3;108,20,20;,
  3;20,20,21;,
  3;109,22,22;,
  3;22,22,23;,
  3;110,24,24;,
  3;24,24,25;,
  3;111,18,18;,
  3;26,112,113;,
  3;26,113,114;,
  3;26,114,115;,
  3;26,115,116;,
  3;26,116,117;,
  3;26,117,118;,
  3;26,118,119;,
  3;26,119,112;,
  3;27,27,28;,
  3;120,29,29;,
  3;29,29,30;,
  3;121,31,31;,
  3;31,31,32;,
  3;122,33,33;,
  3;33,33,34;,
  3;123,27,27;,
  3;35,124,125;,
  3;35,125,126;,
  3;35,126,127;,
  3;35,127,128;,
  3;35,128,129;,
  3;35,129,130;,
  3;35,130,131;,
  3;35,131,124;,
  4;36,36,37,37;,
  4;36,79,79,36;,
  4;42,42,37,37;,
  4;39,39,38,38;,
  4;81,81,38,38;,
  4;39,44,44,39;,
  4;41,41,40,40;,
  4;83,83,40,40;,
  4;41,46,46,41;,
  4;132,132,133,133;,
  4;134,134,133,133;,
  4;132,135,135,132;,
  4;42,42,43,43;,
  4;48,48,43,43;,
  4;45,45,44,44;,
  4;45,50,50,45;,
  4;47,47,46,46;,
  4;47,52,52,47;,
  4;136,136,135,135;,
  4;136,137,137,136;,
  4;48,48,49,49;,
  4;54,54,49,49;,
  4;51,51,50,50;,
  4;51,56,56,51;,
  4;53,53,52,52;,
  4;53,58,58,53;,
  4;138,138,137,137;,
  4;138,139,139,138;,
  4;54,54,55,55;,
  4;60,60,55,55;,
  4;57,57,56,56;,
  4;57,62,62,57;,
  4;59,59,58,58;,
  4;59,64,64,59;,
  4;140,140,139,139;,
  4;140,141,141,140;,
  4;60,60,61,61;,
  4;66,66,61,61;,
  4;63,63,62,62;,
  4;63,68,68,63;,
  4;65,65,64,64;,
  4;65,70,70,65;,
  4;142,142,141,141;,
  4;142,143,143,142;,
  4;66,66,67,67;,
  4;72,72,67,67;,
  4;69,69,68,68;,
  4;69,74,74,69;,
  4;71,71,70,70;,
  4;71,76,76,71;,
  4;144,144,143,143;,
  4;144,145,145,144;,
  4;72,72,73,73;,
  4;78,78,73,73;,
  4;75,75,74,74;,
  4;75,80,80,75;,
  4;77,77,76,76;,
  4;77,82,82,77;,
  4;146,146,145,145;,
  4;146,147,147,146;,
  4;78,78,79,79;,
  4;81,81,80,80;,
  4;83,83,82,82;,
  4;134,134,147,147;;
 }
 MeshTextureCoords {
  168;
  0.000000;1.000000;,
  0.062500;0.000000;,
  0.125000;1.000000;,
  0.125000;0.000000;,
  0.250000;1.000000;,
  0.187500;0.000000;,
  0.375000;1.000000;,
  0.250000;0.000000;,
  0.500000;1.000000;,
  0.312500;0.000000;,
  0.625000;1.000000;,
  0.375000;0.000000;,
  0.750000;1.000000;,
  0.437500;0.000000;,
  0.875000;1.000000;,
  0.500000;0.000000;,
  1.000000;1.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;1.000000;,
  0.062500;0.000000;,
  0.125000;1.000000;,
  0.125000;0.000000;,
  0.250000;1.000000;,
  0.187500;0.000000;,
  0.375000;1.000000;,
  0.250000;0.000000;,
  0.500000;1.000000;,
  0.312500;0.000000;,
  0.625000;1.000000;,
  0.375000;0.000000;,
  0.750000;1.000000;,
  0.437500;0.000000;,
  0.875000;1.000000;,
  0.500000;0.000000;,
  1.000000;1.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;1.000000;,
  0.062500;0.000000;,
  0.125000;1.000000;,
  0.125000;0.000000;,
  0.250000;1.000000;,
  0.187500;0.000000;,
  0.375000;1.000000;,
  0.250000;0.000000;,
  0.500000;1.000000;,
  0.312500;0.000000;,
  0.625000;1.000000;,
  0.375000;0.000000;,
  0.750000;1.000000;,
  0.437500;0.000000;,
  0.875000;1.000000;,
  0.500000;0.000000;,
  1.000000;1.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;1.000000;,
  0.062500;0.000000;,
  0.125000;1.000000;,
  0.125000;0.000000;,
  0.250000;1.000000;,
  0.187500;0.000000;,
  0.375000;1.000000;,
  0.250000;0.000000;,
  0.500000;1.000000;,
  0.312500;0.000000;,
  0.625000;1.000000;,
  0.375000;0.000000;,
  0.750000;1.000000;,
  0.437500;0.000000;,
  0.875000;1.000000;,
  0.500000;0.000000;,
  1.000000;1.000000;,
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
  0.000000;0.000000;;
 }
}
