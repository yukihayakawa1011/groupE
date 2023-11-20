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
 68;
 23.33714;-0.13766;4.49260;,
 23.32710;-3.31438;3.17676;,
 26.54458;-1.72602;1.58838;,
 26.54960;-0.13766;2.24630;,
 23.34718;3.03908;3.17676;,
 26.55462;1.45070;1.58838;,
 23.35132;4.35494;0.00000;,
 26.55670;2.10864;0.00000;,
 23.34718;3.03908;-3.17676;,
 26.55462;1.45070;-1.58838;,
 23.33714;-0.13766;-4.49260;,
 26.54960;-0.13766;-2.24630;,
 23.32710;-3.31438;-3.17676;,
 26.54458;-1.72602;-1.58838;,
 23.32296;-4.63024;-0.00000;,
 26.54066;-2.36264;-0.00000;,
 7.68394;-0.07560;4.49260;,
 7.67390;-3.25234;3.17676;,
 7.69396;3.10114;3.17676;,
 7.69812;4.41698;0.00000;,
 7.69396;3.10114;-3.17676;,
 7.68394;-0.07560;-4.49260;,
 7.67390;-3.25234;-3.17676;,
 7.66976;-4.56818;-0.00000;,
 7.68394;-0.07560;-0.00000;,
 27.08136;-0.13766;-0.00000;,
 -4.41350;2.22498;2.12748;,
 -4.42672;0.09760;3.00870;,
 0.18224;0.08350;6.01740;,
 0.20866;4.33836;4.25494;,
 -4.43990;-2.02986;2.12748;,
 0.15584;-4.17136;4.25494;,
 -4.44538;-2.91106;0.00000;,
 0.14490;-5.93380;-0.00000;,
 -4.43990;-2.02986;-2.12748;,
 0.15584;-4.17136;-4.25494;,
 -4.42672;0.09760;-3.00870;,
 0.18224;0.08350;-6.01740;,
 -4.41350;2.22498;-2.12748;,
 0.20866;4.33836;-4.25494;,
 -4.40802;3.10618;0.00000;,
 0.21960;6.10076;0.00000;,
 7.66264;-0.00094;6.21996;,
 7.68996;4.39712;4.39818;,
 7.63534;-4.39904;4.39818;,
 7.62404;-6.22082;-0.00000;,
 7.63534;-4.39904;-4.39818;,
 7.66264;-0.00094;-6.21996;,
 7.68996;4.39712;-4.39818;,
 7.70128;6.21884;0.00000;,
 15.06320;-0.08544;5.58372;,
 15.08770;3.86278;3.94828;,
 15.03870;-4.03364;3.94828;,
 15.02854;-5.66904;-0.00000;,
 15.03870;-4.03364;-3.94828;,
 15.06320;-0.08544;-5.58372;,
 15.08770;3.86278;-3.94828;,
 15.09786;5.49818;0.00000;,
 19.37578;-0.09848;2.97128;,
 19.38880;2.00250;2.10102;,
 19.36272;-2.19946;2.10102;,
 19.35732;-3.06970;-0.00000;,
 19.36272;-2.19946;-2.10102;,
 19.37578;-0.09848;-2.97128;,
 19.38880;2.00250;-2.10102;,
 19.39420;2.87276;0.00000;,
 -5.23834;0.10004;0.00000;,
 19.92054;-0.10014;-0.00000;;
 
 80;
 4;0,1,2,3;,
 4;4,0,3,5;,
 4;6,4,5,7;,
 4;8,6,7,9;,
 4;10,8,9,11;,
 4;12,10,11,13;,
 4;14,12,13,15;,
 4;1,14,15,2;,
 4;0,16,17,1;,
 4;4,18,16,0;,
 4;6,19,18,4;,
 4;8,20,19,6;,
 4;10,21,20,8;,
 4;12,22,21,10;,
 4;14,23,22,12;,
 4;1,17,23,14;,
 3;16,24,17;,
 3;18,24,16;,
 3;19,24,18;,
 3;20,24,19;,
 3;21,24,20;,
 3;22,24,21;,
 3;23,24,22;,
 3;17,24,23;,
 3;9,7,25;,
 3;11,9,25;,
 3;13,11,25;,
 3;15,13,25;,
 3;2,15,25;,
 3;3,2,25;,
 3;5,3,25;,
 3;7,5,25;,
 4;26,27,28,29;,
 4;27,30,31,28;,
 4;30,32,33,31;,
 4;32,34,35,33;,
 4;34,36,37,35;,
 4;36,38,39,37;,
 4;38,40,41,39;,
 4;40,26,29,41;,
 4;29,28,42,43;,
 4;28,31,44,42;,
 4;31,33,45,44;,
 4;33,35,46,45;,
 4;35,37,47,46;,
 4;37,39,48,47;,
 4;39,41,49,48;,
 4;41,29,43,49;,
 4;43,42,50,51;,
 4;42,44,52,50;,
 4;44,45,53,52;,
 4;45,46,54,53;,
 4;46,47,55,54;,
 4;47,48,56,55;,
 4;48,49,57,56;,
 4;49,43,51,57;,
 4;51,50,58,59;,
 4;50,52,60,58;,
 4;52,53,61,60;,
 4;53,54,62,61;,
 4;54,55,63,62;,
 4;55,56,64,63;,
 4;56,57,65,64;,
 4;57,51,59,65;,
 3;27,26,66;,
 3;30,27,66;,
 3;32,30,66;,
 3;34,32,66;,
 3;36,34,66;,
 3;38,36,66;,
 3;40,38,66;,
 3;26,40,66;,
 3;59,58,67;,
 3;58,60,67;,
 3;60,61,67;,
 3;61,62,67;,
 3;62,63,67;,
 3;63,64,67;,
 3;64,65,67;,
 3;65,59,67;;
 
 MeshMaterialList {
  1;
  80;
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
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
    "data\\TEXTURE\\UV\\ninja_red.jpg";
   }
  }
 }
 MeshNormals {
  74;
  0.303474;-0.674981;0.672536;,
  0.304097;-0.000862;0.952641;,
  0.305752;0.672811;0.673678;,
  0.306437;0.951891;0.000000;,
  0.305752;0.672811;-0.673678;,
  0.304097;-0.000862;-0.952641;,
  0.303474;-0.674981;-0.672536;,
  0.303187;-0.952931;-0.000000;,
  -0.002803;-0.707100;0.707108;,
  0.000000;-0.000001;1.000000;,
  0.002803;0.707100;0.707108;,
  0.003964;0.999992;0.000000;,
  0.002803;0.707100;-0.707108;,
  0.000000;-0.000001;-1.000000;,
  -0.002803;-0.707100;-0.707108;,
  -0.003964;-0.999992;0.000000;,
  0.999993;-0.003819;-0.000000;,
  -0.999995;0.003157;0.000000;,
  0.833759;0.552129;0.000000;,
  0.833422;0.389511;-0.392033;,
  0.832610;-0.002519;-0.553854;,
  0.832485;-0.394623;-0.388898;,
  0.831086;-0.556145;-0.000000;,
  0.832485;-0.394623;0.388898;,
  0.832610;-0.002519;0.553854;,
  0.833422;0.389511;0.392033;,
  -0.812813;0.414373;0.409426;,
  -0.814883;0.004943;0.579604;,
  -0.816953;-0.405311;0.410256;,
  -0.817813;-0.575484;0.000000;,
  -0.816953;-0.405311;-0.410256;,
  -0.814883;0.004943;-0.579604;,
  -0.812813;0.414373;-0.409426;,
  -0.811956;0.583718;0.000000;,
  -0.296000;0.676303;0.674535;,
  -0.301108;0.001784;0.953588;,
  -0.306212;-0.672237;0.674041;,
  -0.308326;-0.951281;0.000000;,
  -0.306212;-0.672237;-0.674041;,
  -0.301108;0.001784;-0.953588;,
  -0.296000;0.676303;-0.674535;,
  -0.293882;0.955842;0.000000;,
  0.037361;0.706493;0.706733;,
  0.029352;-0.000204;0.999569;,
  0.021340;-0.707027;0.706864;,
  0.018022;-0.999838;-0.000000;,
  0.021340;-0.707027;-0.706864;,
  0.029352;-0.000204;-0.999569;,
  0.037361;0.706493;-0.706733;,
  0.040677;0.999172;0.000000;,
  0.317249;0.669632;0.671526;,
  0.312171;-0.001875;0.950024;,
  0.307088;-0.673867;0.672012;,
  0.304982;-0.952358;-0.000000;,
  0.307088;-0.673867;-0.672012;,
  0.312171;-0.001875;-0.950024;,
  0.317249;0.669632;-0.671526;,
  0.319349;0.947637;0.000000;,
  0.832320;0.389414;0.394462;,
  0.830325;-0.005046;0.557257;,
  0.828330;-0.398665;0.393619;,
  0.827505;-0.561459;-0.000000;,
  0.828330;-0.398665;-0.393619;,
  0.830325;-0.005046;-0.557257;,
  0.832320;0.389414;-0.394462;,
  0.833149;0.553049;0.000000;,
  -0.999982;0.006084;-0.000000;,
  0.999981;-0.006147;0.000000;,
  -0.999995;0.003157;0.000000;,
  -0.999995;0.003158;-0.000002;,
  -0.999995;0.003155;-0.000001;,
  -0.999995;0.003156;0.000000;,
  -0.999995;0.003155;0.000001;,
  -0.999995;0.003158;0.000002;;
  80;
  4;1,0,23,24;,
  4;2,1,24,25;,
  4;3,2,25,18;,
  4;4,3,18,19;,
  4;5,4,19,20;,
  4;6,5,20,21;,
  4;7,6,21,22;,
  4;0,7,22,23;,
  4;1,9,8,0;,
  4;2,10,9,1;,
  4;3,11,10,2;,
  4;4,12,11,3;,
  4;5,13,12,4;,
  4;6,14,13,5;,
  4;7,15,14,6;,
  4;0,8,15,7;,
  3;68,17,69;,
  3;70,17,68;,
  3;71,17,70;,
  3;72,17,71;,
  3;68,17,72;,
  3;73,17,68;,
  3;71,17,73;,
  3;69,17,71;,
  3;19,18,16;,
  3;20,19,16;,
  3;21,20,16;,
  3;22,21,16;,
  3;23,22,16;,
  3;24,23,16;,
  3;25,24,16;,
  3;18,25,16;,
  4;26,27,35,34;,
  4;27,28,36,35;,
  4;28,29,37,36;,
  4;29,30,38,37;,
  4;30,31,39,38;,
  4;31,32,40,39;,
  4;32,33,41,40;,
  4;33,26,34,41;,
  4;34,35,43,42;,
  4;35,36,44,43;,
  4;36,37,45,44;,
  4;37,38,46,45;,
  4;38,39,47,46;,
  4;39,40,48,47;,
  4;40,41,49,48;,
  4;41,34,42,49;,
  4;42,43,51,50;,
  4;43,44,52,51;,
  4;44,45,53,52;,
  4;45,46,54,53;,
  4;46,47,55,54;,
  4;47,48,56,55;,
  4;48,49,57,56;,
  4;49,42,50,57;,
  4;50,51,59,58;,
  4;51,52,60,59;,
  4;52,53,61,60;,
  4;53,54,62,61;,
  4;54,55,63,62;,
  4;55,56,64,63;,
  4;56,57,65,64;,
  4;57,50,58,65;,
  3;27,26,66;,
  3;28,27,66;,
  3;29,28,66;,
  3;30,29,66;,
  3;31,30,66;,
  3;32,31,66;,
  3;33,32,66;,
  3;26,33,66;,
  3;58,59,67;,
  3;59,60,67;,
  3;60,61,67;,
  3;61,62,67;,
  3;62,63,67;,
  3;63,64,67;,
  3;64,65,67;,
  3;65,58,67;;
 }
 MeshTextureCoords {
  68;
  0.276792;0.071144;,
  0.276851;0.090102;,
  0.257774;0.080623;,
  0.257744;0.071144;,
  0.276732;0.052185;,
  0.257714;0.061665;,
  0.276707;0.044332;,
  0.257702;0.057738;,
  0.276732;0.052185;,
  0.257714;0.061665;,
  0.276792;0.071144;,
  0.257744;0.071144;,
  0.276851;0.090102;,
  0.257774;0.080623;,
  0.276876;0.097955;,
  0.257797;0.084422;,
  0.393346;0.070773;,
  0.393405;0.089732;,
  0.393286;0.051815;,
  0.393262;0.043962;,
  0.393286;0.051815;,
  0.393346;0.070773;,
  0.393405;0.089732;,
  0.393430;0.097585;,
  0.393346;0.070773;,
  0.254591;0.071144;,
  0.186906;0.312211;,
  0.186984;0.324907;,
  0.159657;0.324991;,
  0.159500;0.299598;,
  0.187063;0.337603;,
  0.159813;0.350383;,
  0.187095;0.342862;,
  0.159878;0.360901;,
  0.187063;0.337603;,
  0.159813;0.350383;,
  0.186984;0.324907;,
  0.159657;0.324991;,
  0.186906;0.312211;,
  0.159500;0.299598;,
  0.186874;0.306952;,
  0.159435;0.289080;,
  0.115304;0.325495;,
  0.115142;0.299247;,
  0.115465;0.351742;,
  0.115532;0.362614;,
  0.115465;0.351742;,
  0.115304;0.325495;,
  0.115142;0.299247;,
  0.115075;0.288375;,
  0.071424;0.325999;,
  0.071279;0.302436;,
  0.071569;0.349561;,
  0.071629;0.359321;,
  0.071569;0.349561;,
  0.071424;0.325999;,
  0.071279;0.302436;,
  0.071218;0.292676;,
  0.045853;0.326077;,
  0.045776;0.313538;,
  0.045931;0.338615;,
  0.045963;0.343809;,
  0.045931;0.338615;,
  0.045853;0.326077;,
  0.045776;0.313538;,
  0.045744;0.308345;,
  0.191797;0.324892;,
  0.042623;0.326087;;
 }
}
