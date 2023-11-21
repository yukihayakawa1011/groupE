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
 42;
 -5.85897;2.45202;-2.38222;,
 -1.54082;4.82654;-4.77259;,
 -1.56549;0.04590;-6.75282;,
 -5.87128;0.06170;-3.37235;,
 -1.59018;-4.73472;-4.77258;,
 -5.88364;-2.32860;-2.38223;,
 -1.60038;-6.71494;0.00814;,
 -5.88873;-3.31870;0.00813;,
 -1.59017;-4.73472;4.78889;,
 -5.88361;-2.32860;2.39851;,
 -1.56549;0.04590;6.76911;,
 -5.87126;0.06170;3.38861;,
 -1.54082;4.82654;4.78889;,
 -5.85894;2.45202;2.39851;,
 -1.53060;6.80674;0.00814;,
 -5.85384;3.44212;0.00814;,
 3.39842;4.73472;-4.77259;,
 3.37374;-0.04590;-6.75283;,
 3.34906;-4.82654;-4.77258;,
 3.33885;-6.80674;0.00814;,
 3.34906;-4.82654;4.78889;,
 3.37373;-0.04590;6.76912;,
 3.39842;4.73472;4.78888;,
 3.40862;6.71494;0.00815;,
 15.69515;4.26936;-4.39901;,
 15.67242;-0.13772;-6.22450;,
 15.64967;-4.54478;-4.39900;,
 15.64025;-6.37026;0.00814;,
 15.64968;-4.54478;4.41531;,
 15.67242;-0.13772;6.24081;,
 15.69515;4.26936;4.41530;,
 15.70458;6.09482;0.00814;,
 20.26628;3.99958;-4.14200;,
 20.24484;-0.15048;-5.86105;,
 20.22342;-4.30056;-4.14200;,
 20.21458;-6.01956;0.00814;,
 20.22342;-4.30056;4.15830;,
 20.24481;-0.15048;5.87733;,
 20.26627;3.99958;4.15831;,
 20.27514;5.71858;0.00814;,
 -6.62956;0.06448;0.00813;,
 23.28967;-0.15248;0.00813;;
 
 48;
 4;0,1,2,3;,
 4;3,2,4,5;,
 4;5,4,6,7;,
 4;7,6,8,9;,
 4;9,8,10,11;,
 4;11,10,12,13;,
 4;13,12,14,15;,
 4;15,14,1,0;,
 4;1,16,17,2;,
 4;2,17,18,4;,
 4;4,18,19,6;,
 4;6,19,20,8;,
 4;8,20,21,10;,
 4;10,21,22,12;,
 4;12,22,23,14;,
 4;14,23,16,1;,
 4;16,24,25,17;,
 4;17,25,26,18;,
 4;18,26,27,19;,
 4;19,27,28,20;,
 4;20,28,29,21;,
 4;21,29,30,22;,
 4;22,30,31,23;,
 4;23,31,24,16;,
 4;24,32,33,25;,
 4;25,33,34,26;,
 4;26,34,35,27;,
 4;27,35,36,28;,
 4;28,36,37,29;,
 4;29,37,38,30;,
 4;30,38,39,31;,
 4;31,39,32,24;,
 3;3,40,0;,
 3;5,40,3;,
 3;7,40,5;,
 3;9,40,7;,
 3;11,40,9;,
 3;13,40,11;,
 3;15,40,13;,
 3;0,40,15;,
 3;32,41,33;,
 3;33,41,34;,
 3;34,41,35;,
 3;35,41,36;,
 3;36,41,37;,
 3;37,41,38;,
 3;38,41,39;,
 3;39,41,32;;
 
 MeshMaterialList {
  1;
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
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
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
  42;
  -0.848315;0.376567;-0.372235;,
  -0.850058;0.004334;-0.526671;,
  -0.851806;-0.368248;-0.372586;,
  -0.852528;-0.522681;0.000003;,
  -0.851805;-0.368247;0.372589;,
  -0.850058;0.004333;0.526672;,
  -0.848315;0.376565;0.372238;,
  -0.847591;0.530650;0.000002;,
  -0.323832;0.669816;-0.668191;,
  -0.331371;0.001662;-0.943499;,
  -0.338889;-0.664414;-0.666114;,
  -0.341997;-0.939701;-0.000000;,
  -0.338891;-0.664413;0.666114;,
  -0.331374;0.001662;0.943498;,
  -0.323834;0.669815;0.668191;,
  -0.320702;0.947180;-0.000000;,
  0.030670;0.706692;-0.706856;,
  0.021465;-0.000119;-0.999770;,
  0.012257;-0.707090;-0.707017;,
  0.008442;-0.999964;-0.000001;,
  0.012257;-0.707090;0.707017;,
  0.021464;-0.000118;0.999770;,
  0.030670;0.706693;0.706856;,
  0.034482;0.999405;-0.000000;,
  0.064713;0.705467;-0.705783;,
  0.061090;-0.000309;-0.998132;,
  0.057466;-0.706089;-0.705788;,
  0.055966;-0.998433;-0.000001;,
  0.057467;-0.706089;0.705787;,
  0.061091;-0.000309;0.998132;,
  0.064714;0.705467;0.705782;,
  0.066214;0.997805;-0.000000;,
  0.568876;0.580125;-0.582954;,
  0.566820;-0.002829;-0.823837;,
  0.564769;-0.584950;-0.582126;,
  0.563921;-0.825829;-0.000000;,
  0.564770;-0.584948;0.582126;,
  0.566820;-0.002828;0.823837;,
  0.568876;0.580124;0.582955;,
  0.569727;0.821834;-0.000000;,
  -0.999987;0.005119;0.000004;,
  0.999989;-0.004621;0.000001;;
  48;
  4;0,8,9,1;,
  4;1,9,10,2;,
  4;2,10,11,3;,
  4;3,11,12,4;,
  4;4,12,13,5;,
  4;5,13,14,6;,
  4;6,14,15,7;,
  4;7,15,8,0;,
  4;8,16,17,9;,
  4;9,17,18,10;,
  4;10,18,19,11;,
  4;11,19,20,12;,
  4;12,20,21,13;,
  4;13,21,22,14;,
  4;14,22,23,15;,
  4;15,23,16,8;,
  4;16,24,25,17;,
  4;17,25,26,18;,
  4;18,26,27,19;,
  4;19,27,28,20;,
  4;20,28,29,21;,
  4;21,29,30,22;,
  4;22,30,31,23;,
  4;23,31,24,16;,
  4;24,32,33,25;,
  4;25,33,34,26;,
  4;26,34,35,27;,
  4;27,35,36,28;,
  4;28,36,37,29;,
  4;29,37,38,30;,
  4;30,38,39,31;,
  4;31,39,32,24;,
  3;1,40,0;,
  3;2,40,1;,
  3;3,40,2;,
  3;4,40,3;,
  3;5,40,4;,
  3;6,40,5;,
  3;7,40,6;,
  3;0,40,7;,
  3;32,41,33;,
  3;33,41,34;,
  3;34,41,35;,
  3;35,41,36;,
  3;36,41,37;,
  3;37,41,38;,
  3;38,41,39;,
  3;39,41,32;;
 }
 MeshTextureCoords {
  42;
  0.020537;0.312617;,
  0.051329;0.298446;,
  0.051153;0.326977;,
  0.020449;0.326882;,
  0.050977;0.355507;,
  0.020361;0.341148;,
  0.050905;0.367325;,
  0.020325;0.347056;,
  0.050977;0.355507;,
  0.020361;0.341148;,
  0.051153;0.326977;,
  0.020449;0.326882;,
  0.051329;0.298446;,
  0.020537;0.312617;,
  0.051402;0.286629;,
  0.020573;0.306708;,
  0.086551;0.298994;,
  0.086375;0.327525;,
  0.086199;0.356055;,
  0.086126;0.367873;,
  0.086199;0.356055;,
  0.086375;0.327525;,
  0.086551;0.298994;,
  0.086623;0.287177;,
  0.174237;0.301772;,
  0.174075;0.328073;,
  0.173913;0.354374;,
  0.173846;0.365268;,
  0.173913;0.354374;,
  0.174075;0.328073;,
  0.174237;0.301772;,
  0.174305;0.290877;,
  0.206834;0.303382;,
  0.206681;0.328149;,
  0.206528;0.352916;,
  0.206465;0.363175;,
  0.206528;0.352916;,
  0.206681;0.328149;,
  0.206834;0.303382;,
  0.206897;0.293123;,
  0.015042;0.326866;,
  0.228393;0.328161;;
 }
}
