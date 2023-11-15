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
 192;
 2.03571;8.15118;-11.73339;,
 1.67553;7.66055;-11.37321;,
 2.00000;7.66055;-10.58986;,
 2.50937;8.15118;-10.58986;,
 1.98675;6.95345;-10.58986;,
 1.66615;6.95345;-11.36384;,
 2.00000;6.92145;-9.85075;,
 2.00000;7.66055;-9.85075;,
 2.50937;8.15118;-9.85075;,
 1.51308;8.15118;-12.25601;,
 1.15290;7.66055;-11.89583;,
 1.14353;6.95345;-11.88646;,
 2.53571;8.13793;-12.23339;,
 3.21648;8.13793;-10.58986;,
 3.18448;8.15118;-9.85075;,
 2.01308;8.13793;-12.75601;,
 2.88263;7.62856;-12.58031;,
 3.70711;7.62856;-10.58986;,
 3.69385;7.66055;-9.85075;,
 2.36001;7.62856;-13.10294;,
 2.88263;6.95345;-12.58031;,
 3.70711;6.95345;-10.58986;,
 3.70711;6.95345;-9.85075;,
 2.36001;6.95345;-13.10294;,
 2.53571;6.44407;-12.23339;,
 3.21648;6.44407;-10.58986;,
 3.21648;6.44407;-9.85075;,
 2.01308;6.44407;-12.75601;,
 2.01308;6.44407;-11.71076;,
 2.50937;6.43082;-10.58986;,
 2.50937;6.43082;-9.85075;,
 1.49046;6.44407;-12.23339;,
 0.36955;8.15118;-12.72968;,
 0.36955;7.66055;-12.22031;,
 0.36955;6.95344;-12.20705;,
 -0.36955;8.15118;-12.72968;,
 -0.36955;7.66055;-12.22031;,
 -0.36955;6.95344;-12.20705;,
 0.36955;8.13793;-13.43678;,
 -0.36955;8.13793;-13.43678;,
 0.36955;7.62856;-13.92741;,
 -0.36955;7.62856;-13.92741;,
 0.36955;6.95345;-13.92741;,
 -0.36955;6.95345;-13.92741;,
 0.36955;6.44407;-13.43678;,
 -0.36955;6.43082;-13.40479;,
 0.36955;6.44407;-12.69768;,
 -0.36955;6.44407;-12.69768;,
 -1.51308;8.15118;-12.25601;,
 -1.15290;7.66055;-11.89583;,
 -1.14353;6.95345;-11.88646;,
 -2.03571;8.15118;-11.73339;,
 -1.67553;7.66055;-11.37321;,
 -1.66615;6.95345;-11.36384;,
 -2.01308;8.13793;-12.75601;,
 -2.53571;8.13793;-12.23339;,
 -2.36001;7.62856;-13.10294;,
 -2.88263;7.62856;-12.58031;,
 -2.36001;6.95345;-13.10294;,
 -2.88263;6.95345;-12.58031;,
 -2.01308;6.44407;-12.75601;,
 -2.53571;6.44407;-12.23339;,
 -1.49046;6.44407;-12.23339;,
 -2.01308;6.44407;-11.71076;,
 -2.47738;8.13793;-10.58986;,
 -2.00000;7.66055;-10.58986;,
 -1.98675;6.95345;-10.58986;,
 -2.50937;8.15118;-9.85075;,
 -1.98675;7.62856;-9.85075;,
 -1.98675;6.95345;-9.85075;,
 -3.21648;8.13793;-10.58986;,
 -3.21648;8.13793;-9.85075;,
 -3.70711;7.62856;-10.58986;,
 -3.70711;7.62856;-9.85075;,
 -3.70711;6.95345;-10.58986;,
 -3.69385;6.92145;-9.85075;,
 -3.18448;6.43082;-10.58986;,
 -3.18448;6.43082;-9.85075;,
 -2.47738;6.44407;-10.58986;,
 -2.47737;6.44407;-9.85075;,
 -2.01308;8.13793;-8.72985;,
 -1.67553;7.66055;-9.06740;,
 -1.67553;6.92145;-9.06740;,
 -1.51308;8.15118;-8.18460;,
 -1.14353;7.62856;-8.55415;,
 -1.14353;6.95345;-8.55415;,
 -2.53571;8.13793;-8.20722;,
 -2.01308;8.13793;-7.68460;,
 -2.88263;7.62856;-7.86030;,
 -2.36001;7.62856;-7.33767;,
 -2.88263;6.95345;-7.86030;,
 -2.36001;6.95345;-7.33767;,
 -2.51308;6.43082;-8.22985;,
 -1.99046;6.43082;-7.70722;,
 -2.01308;6.44407;-8.72985;,
 -1.49046;6.44407;-8.20722;,
 -0.36955;8.15118;-7.71093;,
 -0.36955;7.62856;-8.23356;,
 -0.36955;6.95345;-8.23356;,
 0.36955;8.15118;-7.71093;,
 0.36955;7.66055;-8.22030;,
 0.36955;6.95345;-8.23356;,
 -0.36955;8.13793;-7.00383;,
 0.36955;8.15118;-7.03582;,
 -0.36955;7.66055;-6.52645;,
 0.36955;7.66055;-6.52645;,
 -0.36955;6.95345;-6.51320;,
 0.36955;6.95345;-6.51320;,
 -0.36955;6.43082;-7.03582;,
 0.36955;6.43082;-7.03582;,
 -0.36955;6.44407;-7.74293;,
 0.36955;6.44407;-7.74293;,
 1.51308;8.15118;-8.18460;,
 1.15290;7.66055;-8.54478;,
 1.15290;6.92145;-8.54478;,
 2.03571;8.15118;-8.70722;,
 1.67553;7.66055;-9.06740;,
 1.66615;6.95345;-9.07678;,
 2.01308;8.13793;-7.68460;,
 2.53571;8.13793;-8.20722;,
 2.35064;7.66055;-7.34704;,
 2.87326;7.66055;-7.86967;,
 2.36001;6.95345;-7.33767;,
 2.88263;6.95345;-7.86030;,
 1.99046;6.43082;-7.70722;,
 2.53571;6.44407;-8.20722;,
 1.49046;6.44407;-8.20722;,
 2.03571;6.43082;-8.70722;,
 0.00000;8.36332;-0.09205;,
 0.75824;8.04924;-0.09205;,
 0.75824;8.04924;-6.92894;,
 0.00000;8.36332;-6.92894;,
 1.07232;7.29100;-0.09205;,
 1.07232;7.29100;-6.92894;,
 0.75824;6.53276;-0.09205;,
 0.75824;6.53276;-6.92894;,
 0.00000;6.21868;-0.09205;,
 0.00000;6.21868;-6.92894;,
 -0.75824;6.53276;-0.09205;,
 -0.75824;6.53276;-6.92894;,
 -1.07232;7.29100;-0.09205;,
 -1.07232;7.29100;-6.92894;,
 -0.75824;8.04924;-0.09205;,
 -0.75824;8.04924;-6.92894;,
 0.00000;7.29100;0.19193;,
 0.75824;8.04924;-0.09205;,
 0.00000;8.36332;-0.09205;,
 0.00000;7.29100;0.19193;,
 1.07232;7.29100;-0.09205;,
 0.00000;7.29100;0.19193;,
 0.75824;6.53276;-0.09205;,
 0.00000;7.29100;0.19193;,
 0.00000;6.21868;-0.09205;,
 0.00000;7.29100;0.19193;,
 -0.75824;6.53276;-0.09205;,
 0.00000;7.29100;0.19193;,
 -1.07232;7.29100;-0.09205;,
 0.00000;7.29100;0.19193;,
 -0.75824;8.04924;-0.09205;,
 0.00000;7.29100;0.19193;,
 0.00000;8.36332;-0.09205;,
 0.00000;7.29100;-7.21292;,
 0.00000;8.36332;-6.92894;,
 0.75824;8.04924;-6.92894;,
 0.00000;7.29100;-7.21292;,
 1.07232;7.29100;-6.92894;,
 0.00000;7.29100;-7.21292;,
 0.75824;6.53276;-6.92894;,
 0.00000;7.29100;-7.21292;,
 0.00000;6.21868;-6.92894;,
 0.00000;7.29100;-7.21292;,
 -0.75824;6.53276;-6.92894;,
 0.00000;7.29100;-7.21292;,
 -1.07232;7.29100;-6.92894;,
 0.00000;7.29100;-7.21292;,
 -0.75824;8.04924;-6.92894;,
 0.00000;7.29100;-7.21292;,
 0.00000;8.36332;-6.92894;,
 0.00000;9.41970;3.47995;,
 0.00000;7.21303;16.97060;,
 4.03487;7.21303;3.47995;,
 0.00000;7.21303;16.97060;,
 0.00000;5.00637;3.47995;,
 0.00000;7.21303;16.97060;,
 -4.03487;7.21303;3.47995;,
 0.00000;7.21303;16.97060;,
 0.00000;9.41970;3.47995;,
 0.00000;7.21303;-1.24441;,
 0.00000;9.41970;3.47995;,
 4.03487;7.21303;3.47995;,
 0.00000;5.00637;3.47995;,
 -4.03487;7.21303;3.47995;;
 
 160;
 4;0,1,2,3;,
 4;4,2,1,5;,
 4;4,6,7,2;,
 4;7,8,3,2;,
 4;0,9,10,1;,
 4;10,11,5,1;,
 4;12,0,3,13;,
 4;8,14,13,3;,
 4;12,15,9,0;,
 4;16,12,13,17;,
 4;14,18,17,13;,
 4;16,19,15,12;,
 4;20,16,17,21;,
 4;18,22,21,17;,
 4;20,23,19,16;,
 4;24,20,21,25;,
 4;22,26,25,21;,
 4;24,27,23,20;,
 4;28,24,25,29;,
 4;26,30,29,25;,
 4;28,31,27,24;,
 4;5,28,29,4;,
 4;30,6,4,29;,
 4;5,11,31,28;,
 4;32,33,10,9;,
 4;11,10,33,34;,
 4;32,35,36,33;,
 4;36,37,34,33;,
 4;38,32,9,15;,
 4;38,39,35,32;,
 4;40,38,15,19;,
 4;40,41,39,38;,
 4;42,40,19,23;,
 4;42,43,41,40;,
 4;44,42,23,27;,
 4;44,45,43,42;,
 4;46,44,27,31;,
 4;46,47,45,44;,
 4;34,46,31,11;,
 4;34,37,47,46;,
 4;48,49,36,35;,
 4;37,36,49,50;,
 4;48,51,52,49;,
 4;52,53,50,49;,
 4;54,48,35,39;,
 4;54,55,51,48;,
 4;56,54,39,41;,
 4;56,57,55,54;,
 4;58,56,41,43;,
 4;58,59,57,56;,
 4;60,58,43,45;,
 4;60,61,59,58;,
 4;62,60,45,47;,
 4;62,63,61,60;,
 4;50,62,47,37;,
 4;50,53,63,62;,
 4;64,65,52,51;,
 4;53,52,65,66;,
 4;64,67,68,65;,
 4;68,69,66,65;,
 4;70,64,51,55;,
 4;70,71,67,64;,
 4;72,70,55,57;,
 4;72,73,71,70;,
 4;74,72,57,59;,
 4;74,75,73,72;,
 4;76,74,59,61;,
 4;76,77,75,74;,
 4;78,76,61,63;,
 4;78,79,77,76;,
 4;66,78,63,53;,
 4;66,69,79,78;,
 4;80,81,68,67;,
 4;69,68,81,82;,
 4;80,83,84,81;,
 4;84,85,82,81;,
 4;86,80,67,71;,
 4;86,87,83,80;,
 4;88,86,71,73;,
 4;88,89,87,86;,
 4;90,88,73,75;,
 4;90,91,89,88;,
 4;92,90,75,77;,
 4;92,93,91,90;,
 4;94,92,77,79;,
 4;94,95,93,92;,
 4;82,94,79,69;,
 4;82,85,95,94;,
 4;96,97,84,83;,
 4;85,84,97,98;,
 4;96,99,100,97;,
 4;100,101,98,97;,
 4;102,96,83,87;,
 4;102,103,99,96;,
 4;104,102,87,89;,
 4;104,105,103,102;,
 4;106,104,89,91;,
 4;106,107,105,104;,
 4;108,106,91,93;,
 4;108,109,107,106;,
 4;110,108,93,95;,
 4;110,111,109,108;,
 4;98,110,95,85;,
 4;98,101,111,110;,
 4;112,113,100,99;,
 4;101,100,113,114;,
 4;112,115,116,113;,
 4;116,117,114,113;,
 4;118,112,99,103;,
 4;118,119,115,112;,
 4;120,118,103,105;,
 4;120,121,119,118;,
 4;122,120,105,107;,
 4;122,123,121,120;,
 4;124,122,107,109;,
 4;124,125,123,122;,
 4;126,124,109,111;,
 4;126,127,125,124;,
 4;114,126,111,101;,
 4;114,117,127,126;,
 4;8,7,116,115;,
 4;117,116,7,6;,
 4;14,8,115,119;,
 4;18,14,119,121;,
 4;22,18,121,123;,
 4;26,22,123,125;,
 4;30,26,125,127;,
 4;6,30,127,117;,
 4;128,129,130,131;,
 4;129,132,133,130;,
 4;132,134,135,133;,
 4;134,136,137,135;,
 4;136,138,139,137;,
 4;138,140,141,139;,
 4;140,142,143,141;,
 4;142,128,131,143;,
 3;144,145,146;,
 3;147,148,145;,
 3;149,150,148;,
 3;151,152,150;,
 3;153,154,152;,
 3;155,156,154;,
 3;157,158,156;,
 3;159,160,158;,
 3;161,162,163;,
 3;164,163,165;,
 3;166,165,167;,
 3;168,167,169;,
 3;170,169,171;,
 3;172,171,173;,
 3;174,173,175;,
 3;176,175,177;,
 3;178,179,180;,
 3;180,181,182;,
 3;182,183,184;,
 3;184,185,186;,
 3;187,188,189;,
 3;187,189,190;,
 3;187,190,191;,
 3;187,191,188;;
 
 MeshMaterialList {
  2;
  160;
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
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
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
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
   0.800000;0.752800;0.298400;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
  Material {
   0.800000;0.800000;0.800000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
   TextureFilename {
    "C:\\Users\\student\\Desktop\\3DCG\\2023_チーム制作\\data\\TEXTURE\\bandage01.png";
   }
  }
 }
 MeshNormals {
  164;
  -0.900437;0.394578;0.183086;,
  -0.763991;0.396932;0.508687;,
  -0.362822;0.929168;0.070762;,
  -0.306672;0.929867;0.203224;,
  0.388074;0.917949;-0.082273;,
  0.335658;0.915337;-0.222467;,
  0.908164;0.377711;-0.180479;,
  0.772931;0.370977;-0.514737;,
  0.911767;-0.368927;-0.180484;,
  0.772932;-0.370972;-0.514738;,
  0.391535;-0.916660;-0.080211;,
  0.329410;-0.918294;-0.219603;,
  -0.371805;-0.925332;0.074309;,
  -0.324934;-0.920693;0.216198;,
  -0.909209;-0.373205;0.184547;,
  -0.774211;-0.364240;0.517616;,
  -0.508684;0.396931;0.763994;,
  -0.180531;0.396933;0.899918;,
  -0.203223;0.929866;0.306674;,
  -0.073151;0.929866;0.360552;,
  0.222466;0.915338;-0.335657;,
  0.080038;0.915338;-0.394652;,
  0.514739;0.370979;-0.772928;,
  0.182568;0.370980;-0.910518;,
  0.514740;-0.370975;-0.772930;,
  0.180372;-0.373323;-0.909998;,
  0.217625;-0.919170;-0.328276;,
  0.078241;-0.920988;-0.381655;,
  -0.217624;-0.919171;0.328274;,
  -0.075727;-0.918430;0.388267;,
  -0.516595;-0.362468;0.775723;,
  -0.183229;-0.362469;0.913807;,
  0.180531;0.396933;0.899918;,
  0.508684;0.396931;0.763994;,
  0.073151;0.929866;0.360552;,
  0.203223;0.929866;0.306674;,
  -0.080038;0.915338;-0.394652;,
  -0.222466;0.915338;-0.335657;,
  -0.182568;0.370980;-0.910518;,
  -0.514739;0.370979;-0.772928;,
  -0.183622;-0.375372;-0.908504;,
  -0.513686;-0.373488;-0.772421;,
  -0.076343;-0.923088;-0.376935;,
  -0.215733;-0.921286;-0.323560;,
  0.080763;-0.916858;0.390958;,
  0.217645;-0.918098;0.331249;,
  0.183229;-0.362469;0.913807;,
  0.516595;-0.362468;0.775723;,
  0.765826;0.394493;0.507824;,
  0.903657;0.387592;0.182142;,
  0.311605;0.927753;0.205371;,
  0.371974;0.924976;0.077809;,
  -0.333572;0.916662;-0.220138;,
  -0.390311;0.917201;-0.080002;,
  -0.772931;0.370977;-0.514737;,
  -0.911765;0.368932;-0.180484;,
  -0.772423;-0.373487;-0.513683;,
  -0.906119;-0.382092;-0.181535;,
  -0.323561;-0.921286;-0.215733;,
  -0.370296;-0.925574;-0.078701;,
  0.331251;-0.918097;0.217647;,
  0.393210;-0.916112;0.078257;,
  0.775722;-0.362466;0.516598;,
  0.913349;-0.364841;0.180790;,
  0.906729;0.381939;-0.178789;,
  0.770331;0.379646;-0.512307;,
  0.373278;0.924652;-0.075381;,
  0.318983;0.924040;-0.210711;,
  -0.389429;0.917760;0.077855;,
  -0.332562;0.917200;0.219423;,
  -0.911943;0.366520;0.184456;,
  -0.773995;0.368983;0.514571;,
  -0.903582;-0.388177;0.181270;,
  -0.768384;-0.383789;0.512144;,
  -0.364711;-0.928302;0.072394;,
  -0.311677;-0.927152;0.207960;,
  0.392404;-0.916196;-0.081263;,
  0.333349;-0.916689;-0.220361;,
  0.910801;-0.370233;-0.182672;,
  0.771265;-0.375237;-0.514147;,
  0.512715;0.379764;-0.770002;,
  0.181807;0.384148;-0.905194;,
  0.211370;0.925730;-0.313604;,
  0.069892;0.926760;-0.369096;,
  -0.222568;0.917212;0.330433;,
  -0.079961;0.919916;0.383875;,
  -0.514138;0.375030;0.771371;,
  -0.179917;0.386122;0.904732;,
  -0.512576;-0.377778;0.771070;,
  -0.181718;-0.373274;0.909750;,
  -0.208006;-0.926429;0.313786;,
  -0.074799;-0.926429;0.368964;,
  0.222679;-0.916443;-0.332486;,
  0.080038;-0.915336;-0.394656;,
  0.511895;-0.372997;-0.773846;,
  0.185005;-0.368614;-0.910987;,
  -0.178914;0.390422;-0.903084;,
  -0.509988;0.393056;-0.765127;,
  -0.078106;0.926679;-0.367648;,
  -0.203301;0.928869;-0.309631;,
  0.076517;0.922928;0.377292;,
  0.215853;0.921125;0.323938;,
  0.182193;0.392564;0.901498;,
  0.509747;0.390695;0.766495;,
  0.182587;-0.371289;0.910388;,
  0.513439;-0.368926;0.774773;,
  0.074799;-0.926429;0.368964;,
  0.210932;-0.923617;0.320062;,
  -0.081260;-0.916198;-0.392400;,
  -0.213837;-0.919255;-0.330521;,
  -0.180204;-0.368632;-0.911941;,
  -0.511943;-0.372673;-0.773970;,
  -0.765854;0.392429;-0.509378;,
  -0.901643;0.393055;-0.180410;,
  -0.309630;0.928869;-0.203302;,
  -0.365537;0.927721;-0.075606;,
  0.323939;0.921125;0.215853;,
  0.379537;0.922190;0.074281;,
  0.766498;0.390694;0.509744;,
  0.903376;0.388220;0.182203;,
  0.773818;-0.364817;0.517798;,
  0.912566;-0.364526;0.185321;,
  0.329447;-0.918286;0.219580;,
  0.394658;-0.915335;0.080040;,
  -0.312746;-0.925831;-0.212194;,
  -0.365865;-0.927667;-0.074683;,
  -0.769340;-0.377406;-0.515443;,
  -0.907149;-0.379425;-0.181984;,
  -0.000000;0.000000;1.000000;,
  0.000000;1.000000;0.000000;,
  0.707106;0.707107;0.000000;,
  1.000000;0.000000;0.000000;,
  0.707107;-0.707106;-0.000000;,
  0.000000;-1.000000;-0.000000;,
  -0.707107;-0.707106;0.000000;,
  -1.000000;0.000000;0.000000;,
  -0.707106;0.707107;0.000000;,
  -0.000000;0.000000;-1.000000;,
  0.181022;0.181022;0.966676;,
  0.000000;0.256003;0.966676;,
  0.256002;0.000000;0.966676;,
  0.181022;-0.181022;0.966676;,
  0.000000;-0.256002;0.966676;,
  -0.181022;-0.181022;0.966676;,
  -0.256002;0.000000;0.966676;,
  -0.181022;0.181022;0.966676;,
  0.000000;0.256002;-0.966676;,
  0.181021;0.181021;-0.966676;,
  0.256001;0.000000;-0.966676;,
  0.181021;-0.181021;-0.966676;,
  0.000000;-0.256001;-0.966676;,
  -0.181021;-0.181021;-0.966676;,
  -0.256001;0.000000;-0.966676;,
  -0.181021;0.181021;-0.966676;,
  0.000000;0.990188;-0.139745;,
  0.476192;0.870712;-0.122883;,
  0.000000;-0.990188;-0.139744;,
  -0.476191;-0.870713;-0.122883;,
  0.000000;0.986885;0.161425;,
  0.000000;0.906038;-0.423195;,
  0.476191;-0.870713;-0.122883;,
  0.000000;-0.986885;0.161424;,
  -0.476192;0.870712;-0.122883;,
  0.000000;-0.906039;-0.423194;;
  160;
  4;3,1,0,2;,
  4;14,0,1,15;,
  4;14,127,113,0;,
  4;113,115,2,0;,
  4;3,18,16,1;,
  4;16,30,15,1;,
  4;5,3,2,4;,
  4;115,117,4,2;,
  4;5,20,18,3;,
  4;7,5,4,6;,
  4;117,119,6,4;,
  4;7,22,20,5;,
  4;9,7,6,8;,
  4;119,121,8,6;,
  4;9,24,22,7;,
  4;11,9,8,10;,
  4;121,123,10,8;,
  4;11,26,24,9;,
  4;13,11,10,12;,
  4;123,125,12,10;,
  4;13,28,26,11;,
  4;15,13,12,14;,
  4;125,127,14,12;,
  4;15,30,28,13;,
  4;19,17,16,18;,
  4;30,16,17,31;,
  4;19,34,32,17;,
  4;32,46,31,17;,
  4;21,19,18,20;,
  4;21,36,34,19;,
  4;23,21,20,22;,
  4;23,38,36,21;,
  4;25,23,22,24;,
  4;25,40,38,23;,
  4;27,25,24,26;,
  4;27,42,40,25;,
  4;29,27,26,28;,
  4;29,44,42,27;,
  4;31,29,28,30;,
  4;31,46,44,29;,
  4;35,33,32,34;,
  4;46,32,33,47;,
  4;35,50,48,33;,
  4;48,62,47,33;,
  4;37,35,34,36;,
  4;37,52,50,35;,
  4;39,37,36,38;,
  4;39,54,52,37;,
  4;41,39,38,40;,
  4;41,56,54,39;,
  4;43,41,40,42;,
  4;43,58,56,41;,
  4;45,43,42,44;,
  4;45,60,58,43;,
  4;47,45,44,46;,
  4;47,62,60,45;,
  4;51,49,48,50;,
  4;62,48,49,63;,
  4;51,66,64,49;,
  4;64,78,63,49;,
  4;53,51,50,52;,
  4;53,68,66,51;,
  4;55,53,52,54;,
  4;55,70,68,53;,
  4;57,55,54,56;,
  4;57,72,70,55;,
  4;59,57,56,58;,
  4;59,74,72,57;,
  4;61,59,58,60;,
  4;61,76,74,59;,
  4;63,61,60,62;,
  4;63,78,76,61;,
  4;67,65,64,66;,
  4;78,64,65,79;,
  4;67,82,80,65;,
  4;80,94,79,65;,
  4;69,67,66,68;,
  4;69,84,82,67;,
  4;71,69,68,70;,
  4;71,86,84,69;,
  4;73,71,70,72;,
  4;73,88,86,71;,
  4;75,73,72,74;,
  4;75,90,88,73;,
  4;77,75,74,76;,
  4;77,92,90,75;,
  4;79,77,76,78;,
  4;79,94,92,77;,
  4;83,81,80,82;,
  4;94,80,81,95;,
  4;83,98,96,81;,
  4;96,110,95,81;,
  4;85,83,82,84;,
  4;85,100,98,83;,
  4;87,85,84,86;,
  4;87,102,100,85;,
  4;89,87,86,88;,
  4;89,104,102,87;,
  4;91,89,88,90;,
  4;91,106,104,89;,
  4;93,91,90,92;,
  4;93,108,106,91;,
  4;95,93,92,94;,
  4;95,110,108,93;,
  4;99,97,96,98;,
  4;110,96,97,111;,
  4;99,114,112,97;,
  4;112,126,111,97;,
  4;101,99,98,100;,
  4;101,116,114,99;,
  4;103,101,100,102;,
  4;103,118,116,101;,
  4;105,103,102,104;,
  4;105,120,118,103;,
  4;107,105,104,106;,
  4;107,122,120,105;,
  4;109,107,106,108;,
  4;109,124,122,107;,
  4;111,109,108,110;,
  4;111,126,124,109;,
  4;115,113,112,114;,
  4;126,112,113,127;,
  4;117,115,114,116;,
  4;119,117,116,118;,
  4;121,119,118,120;,
  4;123,121,120,122;,
  4;125,123,122,124;,
  4;127,125,124,126;,
  4;129,130,130,129;,
  4;130,131,131,130;,
  4;131,132,132,131;,
  4;132,133,133,132;,
  4;133,134,134,133;,
  4;134,135,135,134;,
  4;135,136,136,135;,
  4;136,129,129,136;,
  3;128,138,139;,
  3;128,140,138;,
  3;128,141,140;,
  3;128,142,141;,
  3;128,143,142;,
  3;128,144,143;,
  3;128,145,144;,
  3;128,139,145;,
  3;137,146,147;,
  3;137,147,148;,
  3;137,148,149;,
  3;137,149,150;,
  3;137,150,151;,
  3;137,151,152;,
  3;137,152,153;,
  3;137,153,146;,
  3;154,158,155;,
  3;160,161,156;,
  3;156,161,157;,
  3;162,158,154;,
  3;159,154,155;,
  3;163,160,156;,
  3;163,156,157;,
  3;159,162,154;;
 }
 MeshTextureCoords {
  192;
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
  0.499864;1.773513;,
  0.951294;1.773532;,
  0.951565;-0.773495;,
  0.500135;-0.773514;,
  1.138285;1.773540;,
  1.138556;-0.773487;,
  0.951294;1.773532;,
  0.951565;-0.773495;,
  0.499864;1.773513;,
  0.500135;-0.773514;,
  0.048435;1.773494;,
  0.048706;-0.773532;,
  -0.138556;1.773486;,
  -0.138285;-0.773540;,
  0.048435;1.773494;,
  0.048706;-0.773532;,
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
  0.000000;1.000000;,
  0.125000;0.000000;,
  0.250000;1.000000;,
  0.250000;0.000000;,
  0.500000;1.000000;,
  0.375000;0.000000;,
  0.750000;1.000000;,
  0.500000;0.000000;,
  1.000000;1.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;;
 }
}
