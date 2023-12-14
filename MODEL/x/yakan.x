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
 144;
 2.19649;46.62628;-0.12153;,
 11.18252;44.52444;-8.84265;,
 2.19649;44.52444;-12.45505;,
 2.19649;46.62628;-0.12153;,
 14.90466;44.52444;-0.12153;,
 2.19649;46.62628;-0.12153;,
 11.18252;44.52444;8.59958;,
 2.19649;46.62628;-0.12153;,
 2.19649;44.52444;12.21199;,
 2.19649;46.62628;-0.12153;,
 -6.78953;44.52444;8.59958;,
 2.19649;46.62628;-0.12153;,
 -10.51168;44.52444;-0.12153;,
 2.19649;46.62628;-0.12153;,
 -6.78953;44.52444;-8.84265;,
 2.19649;46.62628;-0.12153;,
 2.19649;44.52444;-12.45505;,
 18.80049;38.53894;-16.23602;,
 2.19649;38.53894;-22.91084;,
 25.67808;38.53894;-0.12153;,
 18.80049;38.53894;15.99296;,
 2.19649;38.53894;22.66778;,
 -14.40750;38.53894;15.99296;,
 -21.28511;38.53894;-0.12153;,
 -14.40750;38.53894;-16.23602;,
 2.19649;38.53894;-22.91084;,
 23.89068;29.58091;-21.17612;,
 2.19649;29.58091;-27.43652;,
 30.53270;29.58091;-0.12153;,
 23.89068;29.58091;20.93305;,
 2.19649;29.58091;27.90361;,
 -19.49770;29.58091;20.93305;,
 -26.74349;29.58091;-0.12153;,
 -19.49770;29.58091;-21.17612;,
 2.19649;29.58091;-27.43652;,
 25.67808;19.01424;-22.91084;,
 2.19649;19.01424;-29.88980;,
 33.06053;19.01424;-0.12153;,
 25.67808;19.01424;22.66778;,
 2.19649;19.01424;30.35690;,
 -21.28511;19.01424;22.66778;,
 -29.27130;19.01424;-0.12153;,
 -21.28511;19.01424;-22.91084;,
 2.19649;19.01424;-29.88980;,
 23.89068;8.44757;-21.17612;,
 2.19649;8.44757;-27.43652;,
 30.53270;8.44757;-0.12153;,
 23.89068;8.44757;20.93305;,
 2.19649;8.44757;27.90361;,
 -19.49770;8.44757;20.93305;,
 -26.74349;8.44757;-0.12153;,
 -19.49770;8.44757;-21.17612;,
 2.19649;8.44757;-27.43652;,
 18.80049;0.43292;-16.23602;,
 2.19649;0.43292;-22.91084;,
 25.67808;0.43292;-0.12153;,
 18.80049;0.43292;15.99296;,
 2.19649;2.25444;22.66778;,
 -14.40750;0.43292;15.99296;,
 -21.28511;0.43292;-0.12153;,
 -14.40750;0.43292;-16.23602;,
 2.19649;0.43292;-22.91084;,
 11.18252;0.35926;-8.84265;,
 2.19649;0.79297;-12.45505;,
 14.90466;0.35926;-0.12153;,
 11.18252;0.35926;8.59958;,
 2.19649;0.35926;12.21199;,
 -6.78953;0.35926;8.59958;,
 -10.51168;0.35926;-0.12153;,
 -6.78953;0.35926;-8.84265;,
 2.19649;0.79297;-12.45505;,
 2.19649;0.12513;-0.12153;,
 2.19649;0.12513;-0.12153;,
 2.19649;0.12513;-0.12153;,
 2.19649;0.12513;-0.12153;,
 2.19649;0.12513;-0.12153;,
 2.19649;0.12513;-0.12153;,
 2.19649;0.12513;-0.12153;,
 2.19649;0.12513;-0.12153;,
 -0.24576;50.96655;-2.72739;,
 4.63874;50.96655;-2.72739;,
 3.86823;46.01894;-1.70401;,
 0.52475;46.01894;-1.70401;,
 4.63874;50.96655;-2.72739;,
 4.63874;50.96655;2.48432;,
 3.67963;46.01894;1.46094;,
 3.86823;46.01894;-1.70401;,
 4.63874;50.96655;2.48432;,
 -0.24576;50.96655;2.48432;,
 0.71335;46.01894;1.46094;,
 3.67963;46.01894;1.46094;,
 -0.24576;50.96655;2.48432;,
 -0.24576;50.96655;-2.72739;,
 0.52475;46.01894;-1.70401;,
 0.71335;46.01894;1.46094;,
 4.63874;50.96655;-2.72739;,
 -0.24576;50.96655;-2.72739;,
 0.52475;46.01894;-1.70401;,
 3.86823;46.01894;-1.70401;,
 -17.13477;35.16241;2.22432;,
 -16.80453;56.46126;2.22432;,
 -16.80452;56.46124;-2.53772;,
 -17.13477;35.16241;-2.53772;,
 2.01553;66.36533;2.22432;,
 2.01553;66.36533;-2.53772;,
 20.83558;56.46126;2.22432;,
 20.83559;56.46124;-2.53772;,
 21.16583;35.16241;2.22432;,
 21.16583;35.16241;-2.53772;,
 -26.15719;20.40903;-0.12153;,
 -26.15719;20.40903;-3.48061;,
 -24.66334;22.99650;-2.49678;,
 -26.15719;20.40903;-0.12153;,
 -23.77565;24.33710;-0.12153;,
 -26.15719;20.40903;-0.12153;,
 -24.66334;22.99650;2.25371;,
 -26.15719;20.40903;-0.12153;,
 -26.15719;20.40903;3.23754;,
 -26.15719;20.40903;-0.12153;,
 -27.52739;17.40266;2.25371;,
 -26.15719;20.40903;-0.12153;,
 -28.14616;16.33094;-0.12153;,
 -26.15719;20.40903;-0.12153;,
 -27.52743;17.40266;-2.49678;,
 -26.15719;20.40903;-0.12153;,
 -26.15719;20.40903;-3.48061;,
 -34.63237;25.50214;-2.49678;,
 -33.96600;26.61670;-3.48061;,
 -40.81484;29.77463;-3.48061;,
 -41.30113;27.95967;-2.49678;,
 -40.81484;29.77463;-3.48061;,
 -40.32854;31.58945;-2.49678;,
 -33.33620;28.61515;-2.49678;,
 -33.96600;26.61670;-3.48061;,
 -32.88514;29.91807;-0.12153;,
 -40.12711;32.34122;-0.12153;,
 -34.89322;24.52867;-0.12153;,
 -41.50256;27.20800;-0.12153;,
 -34.44853;24.46394;2.25371;,
 -33.96600;26.26472;3.23754;,
 -40.81487;29.77463;3.23754;,
 -41.30113;27.95972;2.25371;,
 -33.33620;28.61515;2.25371;,
 -40.32857;31.58945;2.25371;;
 
 102;
 3;0,1,2;,
 3;3,4,1;,
 3;5,6,4;,
 3;7,8,6;,
 3;9,10,8;,
 3;11,12,10;,
 3;13,14,12;,
 3;15,16,14;,
 4;2,1,17,18;,
 4;1,4,19,17;,
 4;4,6,20,19;,
 4;6,8,21,20;,
 4;8,10,22,21;,
 4;10,12,23,22;,
 4;12,14,24,23;,
 4;14,16,25,24;,
 4;18,17,26,27;,
 4;17,19,28,26;,
 4;19,20,29,28;,
 4;20,21,30,29;,
 4;21,22,31,30;,
 4;22,23,32,31;,
 4;23,24,33,32;,
 4;24,25,34,33;,
 4;27,26,35,36;,
 4;26,28,37,35;,
 4;28,29,38,37;,
 4;29,30,39,38;,
 4;30,31,40,39;,
 4;31,32,41,40;,
 4;32,33,42,41;,
 4;33,34,43,42;,
 4;36,35,44,45;,
 4;35,37,46,44;,
 4;37,38,47,46;,
 4;38,39,48,47;,
 4;39,40,49,48;,
 4;40,41,50,49;,
 4;41,42,51,50;,
 4;42,43,52,51;,
 4;45,44,53,54;,
 4;44,46,55,53;,
 4;46,47,56,55;,
 4;47,48,57,56;,
 4;48,49,58,57;,
 4;49,50,59,58;,
 4;50,51,60,59;,
 4;51,52,61,60;,
 4;54,53,62,63;,
 4;53,55,64,62;,
 4;55,56,65,64;,
 4;56,57,66,65;,
 4;57,58,67,66;,
 4;58,59,68,67;,
 4;59,60,69,68;,
 4;60,61,70,69;,
 3;63,62,71;,
 3;62,64,72;,
 3;64,65,73;,
 3;65,66,74;,
 3;66,67,75;,
 3;67,68,76;,
 3;68,69,77;,
 3;69,70,78;,
 4;79,80,81,82;,
 4;83,84,85,86;,
 4;87,88,89,90;,
 4;91,92,93,94;,
 4;91,84,95,96;,
 4;97,98,85,94;,
 4;99,100,101,102;,
 4;100,103,104,101;,
 4;103,105,106,104;,
 4;105,107,108,106;,
 4;102,101,100,99;,
 4;101,104,103,100;,
 4;104,106,105,103;,
 4;106,108,107,105;,
 3;109,110,111;,
 3;112,111,113;,
 3;114,113,115;,
 3;116,115,117;,
 3;118,117,119;,
 3;120,119,121;,
 3;122,121,123;,
 3;124,123,125;,
 4;126,127,125,123;,
 4;128,127,126,129;,
 4;130,131,132,133;,
 4;110,133,132,111;,
 4;134,113,111,132;,
 4;134,132,131,135;,
 4;129,126,136,137;,
 4;123,121,136,126;,
 4;121,119,138,136;,
 4;119,117,139,138;,
 4;139,140,141,138;,
 4;137,136,138,141;,
 4;117,115,142,139;,
 4;142,143,140,139;,
 4;113,134,142,115;,
 4;135,143,142,134;;
 
 MeshMaterialList {
  3;
  102;
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
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
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
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
   0.461176;0.461176;0.461176;1.000000;;
   5.000000;
   0.300000;0.300000;0.300000;;
   0.000000;0.000000;0.000000;;
  }
  Material {
   0.517647;0.517647;0.517647;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
  Material {
   0.000000;0.000000;0.000000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
 }
 MeshNormals {
  108;
  -0.000000;1.000000;-0.000000;,
  -0.000000;0.941809;-0.336150;,
  0.231425;0.943287;-0.238016;,
  0.327730;0.944771;-0.000000;,
  0.231425;0.943287;0.238016;,
  -0.000000;0.941809;0.336149;,
  -0.231425;0.943287;0.238016;,
  -0.327730;0.944771;-0.000000;,
  -0.231425;0.943287;-0.238017;,
  -0.000000;0.718196;-0.695840;,
  0.474361;0.732865;-0.487740;,
  0.682573;0.730817;-0.000000;,
  0.474098;0.737735;0.480602;,
  -0.000000;0.730600;0.682805;,
  -0.468169;0.741665;0.480365;,
  -0.671630;0.740886;-0.000000;,
  -0.468420;0.736841;-0.487491;,
  -0.000000;0.373209;-0.927747;,
  0.639358;0.400262;-0.656514;,
  0.921939;0.387334;-0.000000;,
  0.645863;0.406690;0.646115;,
  -0.000000;0.391508;0.920175;,
  -0.637001;0.411798;0.651653;,
  -0.915414;0.402513;0.000000;,
  -0.630431;0.405378;-0.661986;,
  -0.000000;-0.000000;-1.000000;,
  0.698170;-0.000000;-0.715932;,
  1.000000;-0.000000;-0.000000;,
  0.708416;-0.000000;0.705795;,
  0.000000;-0.000000;1.000000;,
  -0.699599;-0.000000;0.714536;,
  -1.000000;-0.000000;0.000000;,
  -0.689229;-0.000000;-0.724544;,
  0.000000;-0.396418;-0.918070;,
  0.631581;-0.424484;-0.648782;,
  0.911644;-0.410981;-0.000000;,
  0.629528;-0.448414;0.634523;,
  -0.000000;-0.443702;0.896175;,
  -0.620257;-0.453642;0.639915;,
  -0.904357;-0.426777;-0.000000;,
  -0.622368;-0.429803;-0.654162;,
  0.000000;-0.891493;-0.453034;,
  0.300601;-0.900895;-0.313093;,
  0.450789;-0.892630;-0.000000;,
  0.289389;-0.897569;0.332601;,
  -0.000000;-0.877642;0.479316;,
  -0.282781;-0.899911;0.331957;,
  -0.436945;-0.899488;-0.000000;,
  -0.293775;-0.903334;-0.312543;,
  0.000000;-0.999796;-0.020214;,
  -0.007698;-0.999888;-0.012799;,
  0.012629;-0.999920;-0.000000;,
  0.007889;-0.999142;0.040660;,
  -0.000000;-0.997113;0.075937;,
  -0.007889;-0.999142;0.040660;,
  -0.012629;-0.999920;-0.000000;,
  0.007698;-0.999888;-0.012799;,
  -0.000000;-0.999961;-0.008773;,
  0.000000;-0.202555;-0.979271;,
  0.983624;-0.177862;0.029153;,
  0.000000;-0.202555;0.979271;,
  -0.983624;-0.177862;0.029153;,
  0.000000;1.000000;0.000000;,
  0.000000;-1.000000;-0.000000;,
  -0.999880;0.015504;-0.000001;,
  -0.000000;1.000000;-0.000002;,
  0.465702;0.884942;-0.000001;,
  0.999880;0.015504;0.000001;,
  -0.465702;0.884942;-0.000002;,
  0.999880;-0.015504;0.000001;,
  0.465702;-0.884942;0.000002;,
  0.000000;-1.000000;0.000002;,
  -0.465702;-0.884942;0.000001;,
  -0.999880;-0.015504;-0.000001;,
  -0.015522;-0.049373;-0.998660;,
  0.267217;0.670918;-0.691711;,
  0.352906;0.935659;0.000001;,
  0.267275;0.661360;0.700833;,
  -0.020538;-0.020128;0.999586;,
  -0.346050;-0.728393;0.591349;,
  -0.387919;-0.917805;-0.084577;,
  -0.287897;-0.722093;-0.629045;,
  0.889009;-0.457890;-0.000000;,
  0.860542;-0.509200;-0.013479;,
  0.855112;-0.518444;-0.000000;,
  0.860542;-0.509200;0.013479;,
  0.889011;-0.457885;-0.000000;,
  0.904303;-0.426504;-0.018168;,
  0.898799;-0.438362;-0.000008;,
  0.904301;-0.426509;0.018161;,
  0.883501;-0.468428;-0.000002;,
  -0.033607;-0.034605;-0.998836;,
  0.311274;0.607430;-0.730847;,
  0.404020;0.893896;-0.194211;,
  -0.418855;-0.621229;-0.662296;,
  -0.583034;-0.809481;-0.069373;,
  -0.445624;-0.630612;0.635411;,
  -0.025855;-0.014169;0.999565;,
  0.307496;0.598920;0.739419;,
  -0.050930;-0.020428;-0.998493;,
  -0.538908;-0.501570;-0.676761;,
  0.352599;0.540071;-0.764197;,
  0.452739;0.719003;-0.527316;,
  -0.752524;-0.656648;-0.050216;,
  -0.535200;-0.519956;0.665738;,
  -0.030980;-0.008423;0.999484;,
  0.345185;0.532986;0.772511;,
  0.452739;0.719003;0.527316;;
  102;
  3;0,2,1;,
  3;0,3,2;,
  3;0,4,3;,
  3;0,5,4;,
  3;0,6,5;,
  3;0,7,6;,
  3;0,8,7;,
  3;0,1,8;,
  4;1,2,10,9;,
  4;2,3,11,10;,
  4;3,4,12,11;,
  4;4,5,13,12;,
  4;5,6,14,13;,
  4;6,7,15,14;,
  4;7,8,16,15;,
  4;8,1,9,16;,
  4;9,10,18,17;,
  4;10,11,19,18;,
  4;11,12,20,19;,
  4;12,13,21,20;,
  4;13,14,22,21;,
  4;14,15,23,22;,
  4;15,16,24,23;,
  4;16,9,17,24;,
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
  4;41,42,50,49;,
  4;42,43,51,50;,
  4;43,44,52,51;,
  4;44,45,53,52;,
  4;45,46,54,53;,
  4;46,47,55,54;,
  4;47,48,56,55;,
  4;48,41,49,56;,
  3;49,50,57;,
  3;50,51,57;,
  3;51,52,57;,
  3;52,53,57;,
  3;53,54,57;,
  3;54,55,57;,
  3;55,56,57;,
  3;56,49,57;,
  4;58,58,58,58;,
  4;59,59,59,59;,
  4;60,60,60,60;,
  4;61,61,61,61;,
  4;62,62,62,62;,
  4;63,63,63,63;,
  4;64,64,64,64;,
  4;68,65,65,68;,
  4;65,66,66,65;,
  4;67,67,67,67;,
  4;69,69,69,69;,
  4;70,71,71,70;,
  4;71,72,72,71;,
  4;73,73,73,73;,
  3;90,82,83;,
  3;90,83,84;,
  3;90,84,85;,
  3;90,85,86;,
  3;90,86,87;,
  3;90,87,88;,
  3;90,88,89;,
  3;90,89,82;,
  4;94,91,99,100;,
  4;74,91,94,81;,
  4;74,75,92,91;,
  4;99,91,92,101;,
  4;93,102,101,92;,
  4;93,92,75,76;,
  4;81,94,95,80;,
  4;100,103,95,94;,
  4;103,104,96,95;,
  4;104,105,97,96;,
  4;97,78,79,96;,
  4;80,95,96,79;,
  4;105,106,98,97;,
  4;98,77,78,97;,
  4;107,107,98,106;,
  4;76,77,98,93;;
 }
 MeshTextureCoords {
  144;
  0.062500;0.000000;,
  0.125000;0.125000;,
  0.000000;0.125000;,
  0.187500;0.000000;,
  0.250000;0.125000;,
  0.312500;0.000000;,
  0.375000;0.125000;,
  0.437500;0.000000;,
  0.500000;0.125000;,
  0.562500;0.000000;,
  0.625000;0.125000;,
  0.687500;0.000000;,
  0.750000;0.125000;,
  0.812500;0.000000;,
  0.875000;0.125000;,
  0.937500;0.000000;,
  1.000000;0.125000;,
  0.125000;0.250000;,
  0.000000;0.250000;,
  0.250000;0.250000;,
  0.375000;0.250000;,
  0.500000;0.250000;,
  0.625000;0.250000;,
  0.750000;0.250000;,
  0.875000;0.250000;,
  1.000000;0.250000;,
  0.125000;0.375000;,
  0.000000;0.375000;,
  0.250000;0.375000;,
  0.375000;0.375000;,
  0.500000;0.375000;,
  0.625000;0.375000;,
  0.750000;0.375000;,
  0.875000;0.375000;,
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
  0.062500;1.000000;,
  0.187500;1.000000;,
  0.312500;1.000000;,
  0.437500;1.000000;,
  0.562500;1.000000;,
  0.687500;1.000000;,
  0.812500;1.000000;,
  0.937500;1.000000;,
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
  0.125000;0.000000;,
  0.125000;1.000000;,
  0.000000;1.000000;,
  0.250000;0.000000;,
  0.250000;1.000000;,
  0.375000;0.000000;,
  0.375000;1.000000;,
  0.500000;0.000000;,
  0.500000;1.000000;,
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
  0.875000;0.500000;,
  1.000000;0.500000;,
  1.000000;0.000000;,
  0.875000;0.000000;,
  0.000000;0.000000;,
  0.125000;0.000000;,
  0.125000;0.500000;,
  0.000000;0.500000;,
  0.250000;0.500000;,
  0.250000;0.000000;,
  0.750000;0.500000;,
  0.750000;0.000000;,
  0.625000;0.500000;,
  0.500000;0.500000;,
  0.500000;0.000000;,
  0.625000;0.000000;,
  0.375000;0.500000;,
  0.375000;0.000000;;
 }
}