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
 338;
 -0.00977;40.42869;0.00000;,
 0.67334;39.96455;-0.68311;,
 -0.00977;39.96455;-0.96607;,
 -0.00977;40.42869;0.00000;,
 0.95630;39.96455;0.00000;,
 -0.00977;40.42869;0.00000;,
 0.67334;39.96455;0.68311;,
 -0.00977;40.42869;0.00000;,
 -0.00977;39.96455;0.96607;,
 -0.00977;40.42869;0.00000;,
 -0.69288;39.96455;0.68311;,
 -0.00977;40.42869;0.00000;,
 -0.97583;39.96455;0.00000;,
 -0.00977;40.42869;0.00000;,
 -0.69288;39.96455;-0.68311;,
 -0.00977;40.42869;0.00000;,
 -0.00977;39.96455;-0.96607;,
 1.25246;39.41731;-1.26222;,
 -0.00977;39.41731;-1.78506;,
 1.77529;39.41731;0.00000;,
 1.25246;39.41731;1.26222;,
 -0.00977;39.41731;1.78506;,
 -1.27199;39.41731;1.26222;,
 -1.79482;39.41731;0.00000;,
 -1.27199;39.41731;-1.26222;,
 -0.00977;39.41731;-1.78506;,
 1.63941;38.59834;-1.64918;,
 -0.00977;38.59834;-2.33229;,
 2.32252;38.59834;0.00000;,
 1.63941;38.59834;1.64918;,
 -0.00977;38.59834;2.33229;,
 -1.65894;38.59834;1.64918;,
 -2.34205;38.59834;0.00000;,
 -1.65894;38.59834;-1.64918;,
 -0.00977;38.59834;-2.33229;,
 1.77529;37.63228;-1.78506;,
 -0.00977;37.63228;-2.52445;,
 2.51468;37.63228;0.00000;,
 1.77529;37.63228;1.78506;,
 -0.00977;37.63228;2.52445;,
 -1.79482;37.63228;1.78506;,
 -2.53422;37.63228;0.00000;,
 -1.79482;37.63228;-1.78506;,
 -0.00977;37.63228;-2.52445;,
 1.63941;36.66620;-1.64918;,
 -0.00977;36.66620;-2.33229;,
 2.32252;36.66620;0.00000;,
 1.63941;36.66620;1.64918;,
 -0.00977;36.66620;2.33229;,
 -1.65894;36.66620;1.64918;,
 -2.34205;36.66620;0.00000;,
 -1.65894;36.66620;-1.64918;,
 -0.00977;36.66620;-2.33229;,
 1.25246;35.84721;-1.26222;,
 -0.00977;35.84721;-1.78506;,
 1.77529;35.84721;0.00000;,
 1.25246;35.84721;1.26222;,
 -0.00977;35.84721;1.78506;,
 -1.27199;35.84721;1.26222;,
 -1.79482;35.84721;0.00000;,
 -1.27199;35.84721;-1.26222;,
 -0.00977;35.84721;-1.78506;,
 -1.83219;35.90148;-1.82865;,
 1.81419;35.90148;-1.82865;,
 1.64840;33.42956;-1.54154;,
 -1.49516;33.42956;-1.54154;,
 1.81419;35.90148;-1.82865;,
 1.81419;35.90148;1.82637;,
 1.64840;33.42956;1.60201;,
 1.64840;33.42956;-1.54154;,
 1.81419;35.90148;1.82637;,
 -1.83219;35.90148;1.82637;,
 -1.49516;33.42956;1.60201;,
 1.64840;33.42956;1.60201;,
 -1.83219;35.90148;1.82637;,
 -1.83219;35.90148;-1.82865;,
 -1.49516;33.42956;-1.54154;,
 -1.49516;33.42956;1.60201;,
 1.81419;35.90148;-1.82865;,
 -1.83219;35.90148;-1.82865;,
 -1.49516;33.42956;-1.54154;,
 1.64840;33.42956;-1.54154;,
 -3.62489;33.53877;3.61512;,
 3.60536;33.53877;3.61512;,
 3.60536;33.53877;-3.61512;,
 -3.62489;33.53877;-3.61512;,
 -5.72983;30.00609;-5.72006;,
 5.71030;30.00609;-5.72006;,
 5.71030;30.00609;5.72006;,
 -5.72983;30.00609;5.72006;,
 -5.72983;30.00609;-5.72006;,
 -5.75851;31.21295;5.74874;,
 -5.75851;31.21295;-5.74874;,
 5.71030;30.00609;5.72006;,
 5.73897;31.21295;5.74874;,
 -5.75851;31.21295;5.74874;,
 -5.72983;30.00609;5.72006;,
 5.71030;30.00609;-5.72006;,
 5.73897;31.21295;-5.74874;,
 5.73897;31.21295;5.74874;,
 5.73897;31.21295;-5.74874;,
 5.71030;30.00609;-5.72006;,
 -5.72983;30.00609;-5.72006;,
 -5.75851;31.21295;-5.74874;,
 4.65954;31.82645;-4.73147;,
 -4.76755;31.82645;-4.73147;,
 -3.62489;33.53877;-3.61512;,
 3.60536;33.53877;-3.61512;,
 -4.76755;31.82645;-4.73147;,
 -4.76755;31.82645;4.75712;,
 -3.62489;33.53877;-3.61512;,
 4.65954;31.82645;4.75712;,
 -4.76755;31.82645;4.75712;,
 3.60536;33.53877;3.61512;,
 -3.62489;33.53877;3.61512;,
 4.65954;31.82645;-4.73147;,
 4.65954;31.82645;4.75712;,
 3.60536;33.53877;-3.61512;,
 -4.99172;23.30968;5.02439;,
 -4.99172;28.90891;5.02439;,
 -4.99172;28.90891;3.39723;,
 -4.99172;23.30968;3.39723;,
 -4.99172;29.97931;5.02439;,
 -4.99172;29.97931;3.39723;,
 -4.99172;22.20438;5.02439;,
 -4.99172;22.20438;3.39723;,
 -3.22324;22.20438;-5.02439;,
 -4.99172;22.20438;-5.02439;,
 -4.99172;23.30968;-5.02439;,
 -3.22324;23.30968;-5.02439;,
 -4.99172;28.90891;-5.02439;,
 -3.22324;28.90891;-5.02439;,
 -4.99172;29.97931;-5.02439;,
 -3.22324;29.97931;-5.02439;,
 -3.22324;29.97931;3.39723;,
 -4.99172;29.97931;3.39723;,
 -3.22324;29.97931;5.02439;,
 5.05705;28.90891;5.02439;,
 5.05705;23.30968;5.02439;,
 5.05705;23.30968;3.39723;,
 5.05705;28.90891;3.39723;,
 5.05705;22.20438;5.02439;,
 5.05705;22.20438;3.39723;,
 5.05705;29.97931;5.02439;,
 5.05705;29.97931;3.39723;,
 -4.99172;29.97931;5.02439;,
 -4.99172;28.90891;5.02439;,
 -3.22324;28.90891;5.02439;,
 -4.99172;23.30968;5.02439;,
 -3.22324;23.30968;5.02439;,
 -4.99172;22.20438;5.02439;,
 -3.22324;22.20438;5.02439;,
 -4.99172;22.20438;3.39723;,
 -3.22324;22.20438;3.39723;,
 5.05705;22.20438;5.02439;,
 5.05705;23.30968;5.02439;,
 3.39821;23.30968;5.02439;,
 3.39821;22.20438;5.02439;,
 5.05705;28.90891;5.02439;,
 3.39821;28.90891;5.02439;,
 5.05705;29.97931;5.02439;,
 3.39821;29.97931;5.02439;,
 3.39821;29.97931;5.02439;,
 3.39821;29.97931;3.39723;,
 5.05705;29.97931;3.39723;,
 5.05705;29.97931;-5.02439;,
 5.05705;28.90891;-5.02439;,
 3.39821;28.90891;-5.02439;,
 3.39821;29.97931;-5.02439;,
 3.39821;23.30968;-5.02439;,
 5.05705;23.30968;-5.02439;,
 5.05705;22.20438;-5.02439;,
 3.39821;22.20438;-5.02439;,
 3.39821;22.20438;3.39723;,
 3.39821;22.20438;5.02439;,
 5.05705;22.20438;3.39723;,
 5.05705;22.20438;-5.02439;,
 5.05705;22.20438;-3.13127;,
 3.39821;22.20438;-3.13127;,
 3.39821;22.20438;-5.02439;,
 -3.22324;22.20438;-3.13127;,
 -3.22324;22.20438;-5.02439;,
 -4.99172;22.20438;-5.02439;,
 -4.99172;22.20438;-3.13127;,
 -4.99172;22.20438;-3.13127;,
 -4.99172;23.30968;-3.13127;,
 -4.99172;23.30968;-5.02439;,
 -4.99172;22.20438;-5.02439;,
 -4.99172;28.90891;-5.02439;,
 -4.99172;28.90891;-3.13127;,
 -4.99172;29.97931;-3.13127;,
 -4.99172;29.97931;-5.02439;,
 -3.22324;29.97931;-3.13127;,
 -4.99172;29.97931;-3.13127;,
 -3.22324;29.97931;-5.02439;,
 -4.99172;29.97931;-5.02439;,
 3.39821;29.97931;-3.13127;,
 3.39821;29.97931;-5.02439;,
 5.05705;29.97931;-3.13127;,
 5.05705;29.97931;-5.02439;,
 5.05705;28.90891;-3.13127;,
 5.05705;28.90891;-5.02439;,
 5.05705;29.97931;-5.02439;,
 5.05705;29.97931;-3.13127;,
 5.05705;23.30968;-3.13127;,
 5.05705;23.30968;-5.02439;,
 5.05705;22.20438;-3.13127;,
 5.05705;22.20438;-5.02439;,
 -3.22324;28.90891;4.44198;,
 3.39821;28.90891;4.44198;,
 -3.22324;23.30968;4.44198;,
 3.39821;23.30968;4.44198;,
 3.39821;28.90891;4.44198;,
 -3.22324;28.90891;4.44198;,
 -3.22324;23.30968;4.44198;,
 3.39821;23.30968;4.44198;,
 3.39821;28.90891;-4.44198;,
 -3.22324;28.90891;-4.44198;,
 3.39821;23.30968;-4.44198;,
 -3.22324;23.30968;-4.44198;,
 -3.22324;28.90891;-4.44198;,
 3.39821;28.90891;-4.44198;,
 3.39821;23.30968;-4.44198;,
 -3.22324;23.30968;-4.44198;,
 -4.40931;28.90891;-3.13127;,
 -4.40931;28.90891;3.39723;,
 -4.40931;23.30968;-3.13127;,
 -4.40931;23.30968;3.39723;,
 4.47466;28.90891;-3.13127;,
 4.47466;23.30968;-3.13127;,
 4.47466;28.90891;3.39723;,
 4.47466;23.30968;3.39723;,
 -5.04402;22.27211;5.02439;,
 5.00476;22.27211;5.02439;,
 5.00476;22.27211;-5.02439;,
 -5.04402;22.27211;-5.02439;,
 -3.56335;17.61045;-3.54372;,
 3.52409;17.61045;-3.54372;,
 3.52409;17.61045;3.54372;,
 -3.56335;17.61045;3.54372;,
 3.52409;17.61045;3.54372;,
 6.11412;19.94127;6.13375;,
 -6.15338;19.94127;6.13375;,
 -3.56335;17.61045;3.54372;,
 5.00476;22.27211;5.02439;,
 -5.04402;22.27211;5.02439;,
 6.11412;19.94127;6.13375;,
 6.11412;19.94127;-6.13375;,
 5.00476;22.27211;-5.02439;,
 3.52409;17.61045;-3.54372;,
 6.11412;19.94127;-6.13375;,
 -6.15338;19.94127;-6.13375;,
 -5.04402;22.27211;-5.02439;,
 5.00476;22.27211;-5.02439;,
 3.52409;17.61045;-3.54372;,
 -3.56335;17.61045;-3.54372;,
 -5.04402;22.27211;-5.02439;,
 -6.15338;19.94127;-6.13375;,
 -6.15338;19.94127;6.13375;,
 -3.56335;17.61045;-3.54372;,
 -0.00977;17.73915;-3.52609;,
 2.41004;17.73915;-2.49332;,
 2.41004;3.40710;-2.49332;,
 -0.00977;3.40710;-3.52609;,
 3.41236;17.73915;0.00000;,
 3.41236;3.40710;0.00000;,
 2.41004;17.73915;2.49332;,
 2.41004;3.40710;2.49332;,
 -0.00977;17.73915;3.52609;,
 -0.00977;3.40710;3.52609;,
 -2.42958;17.73915;2.49332;,
 -2.42958;3.40710;2.49332;,
 -3.43190;17.73915;0.00000;,
 -3.43190;3.40710;0.00000;,
 -2.42958;17.73915;-2.49332;,
 -2.42958;3.40710;-2.49332;,
 -0.00977;17.73915;-3.52609;,
 -0.00977;3.40710;-3.52609;,
 -0.00977;17.73915;0.00000;,
 -0.00977;17.73915;0.00000;,
 -0.00977;17.73915;0.00000;,
 -0.00977;17.73915;0.00000;,
 -0.00977;17.73915;0.00000;,
 -0.00977;17.73915;0.00000;,
 -0.00977;17.73915;0.00000;,
 -0.00977;17.73915;0.00000;,
 -0.00977;3.40710;0.00000;,
 -0.00977;3.40710;0.00000;,
 -0.00977;3.40710;0.00000;,
 -0.00977;3.40710;0.00000;,
 -0.00977;3.40710;0.00000;,
 -0.00977;3.40710;0.00000;,
 -0.00977;3.40710;0.00000;,
 -0.00977;3.40710;0.00000;,
 -3.62489;3.42060;3.61512;,
 3.60536;3.42060;3.61512;,
 3.60536;3.42060;-3.61512;,
 -3.62489;3.42060;-3.61512;,
 -5.72983;-0.11209;-5.72006;,
 5.71030;-0.11209;-5.72006;,
 5.71030;-0.11209;5.72006;,
 -5.72983;-0.11209;5.72006;,
 -5.72983;-0.11209;-5.72006;,
 -5.75851;1.09478;5.74874;,
 -5.75851;1.09478;-5.74874;,
 5.71030;-0.11209;5.72006;,
 5.73897;1.09478;5.74874;,
 -5.75851;1.09478;5.74874;,
 -5.72983;-0.11209;5.72006;,
 5.71030;-0.11209;-5.72006;,
 5.73897;1.09478;-5.74874;,
 5.73897;1.09478;5.74874;,
 5.73897;1.09478;-5.74874;,
 5.71030;-0.11209;-5.72006;,
 -5.72983;-0.11209;-5.72006;,
 -5.75851;1.09478;-5.74874;,
 4.65954;1.70826;-4.73147;,
 -4.76755;1.70826;-4.73147;,
 -3.62489;3.42060;-3.61512;,
 3.60536;3.42060;-3.61512;,
 -4.76755;1.70826;-4.73147;,
 -4.76755;1.70826;4.75712;,
 -3.62489;3.42060;-3.61512;,
 4.65954;1.70826;4.75712;,
 -4.76755;1.70826;4.75712;,
 3.60536;3.42060;3.61512;,
 -3.62489;3.42060;3.61512;,
 4.65954;1.70826;-4.73147;,
 4.65954;1.70826;4.75712;,
 3.60536;3.42060;-3.61512;,
 -4.42240;21.10970;4.05455;,
 -4.42240;29.21881;4.05455;,
 -4.42240;29.21881;-4.05455;,
 -4.42240;21.10970;-4.05455;,
 4.27842;21.10970;-4.05455;,
 4.27842;29.21881;-4.05455;,
 4.27843;29.21881;4.05455;,
 4.27843;21.10970;4.05455;;
 
 259;
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
 4;54,53,55,56;,
 4;57,58,59,60;,
 4;56,57,60,54;,
 4;62,63,64,65;,
 4;66,67,68,69;,
 4;70,71,72,73;,
 4;74,75,76,77;,
 4;74,67,78,79;,
 4;80,81,68,77;,
 4;82,83,84,85;,
 4;86,87,88,89;,
 4;90,89,91,92;,
 4;93,94,95,96;,
 4;97,98,99,88;,
 4;100,101,102,103;,
 4;104,100,103,105;,
 4;106,107,104,105;,
 4;108,92,91,109;,
 4;82,110,108,109;,
 4;94,111,112,95;,
 4;112,111,113,114;,
 4;99,98,115,116;,
 4;83,116,115,117;,
 4;118,119,120,121;,
 4;120,119,122,123;,
 4;124,118,121,125;,
 4;126,127,128,129;,
 4;130,131,129,128;,
 4;132,133,131,130;,
 4;134,135,122,136;,
 4;137,138,139,140;,
 4;138,141,142,139;,
 4;143,137,140,144;,
 4;145,146,147,136;,
 4;148,149,147,146;,
 4;150,151,149,148;,
 4;151,124,152,153;,
 4;154,155,156,157;,
 4;151,157,156,149;,
 4;155,158,159,156;,
 4;158,160,161,159;,
 4;147,159,161,136;,
 4;136,162,163,134;,
 4;143,164,163,162;,
 4;165,166,167,168;,
 4;133,168,167,131;,
 4;169,167,166,170;,
 4;171,172,169,170;,
 4;169,172,126,129;,
 4;151,153,173,174;,
 4;173,175,141,174;,
 4;176,177,178,179;,
 4;178,177,175,173;,
 4;178,173,153,180;,
 4;181,179,178,180;,
 4;182,181,180,183;,
 4;152,183,180,153;,
 4;184,125,121,185;,
 4;186,187,184,185;,
 4;188,186,185,189;,
 4;189,190,191,188;,
 4;189,120,123,190;,
 4;134,192,193,135;,
 4;194,195,193,192;,
 4;163,196,192,134;,
 4;192,196,197,194;,
 4;196,198,199,197;,
 4;196,163,164,198;,
 4;200,201,202,203;,
 4;200,203,144,140;,
 4;201,200,204,205;,
 4;205,204,206,207;,
 4;139,142,206,204;,
 4;208,209,159,147;,
 4;210,208,147,149;,
 4;211,210,149,156;,
 4;209,211,156,159;,
 4;212,213,214,215;,
 4;216,217,131,167;,
 4;218,216,167,169;,
 4;219,218,169,129;,
 4;217,219,129,131;,
 4;220,221,222,223;,
 4;224,225,120,189;,
 4;226,224,189,185;,
 4;227,226,185,121;,
 4;225,227,121,120;,
 4;228,229,204,200;,
 4;230,228,200,140;,
 4;231,230,140,139;,
 4;229,231,139,204;,
 4;121,120,119,118;,
 4;123,122,119,120;,
 4;125,121,118,124;,
 4;129,128,127,126;,
 4;128,129,131,130;,
 4;130,131,133,132;,
 4;136,122,135,134;,
 4;140,139,138,137;,
 4;139,142,141,138;,
 4;144,140,137,143;,
 4;136,147,146,145;,
 4;146,147,149,148;,
 4;148,149,151,150;,
 4;153,152,124,151;,
 4;157,156,155,154;,
 4;149,156,157,151;,
 4;156,159,158,155;,
 4;159,161,160,158;,
 4;136,161,159,147;,
 4;134,163,162,136;,
 4;162,163,164,143;,
 4;168,167,166,165;,
 4;131,167,168,133;,
 4;170,166,167,169;,
 4;170,169,172,171;,
 4;129,126,172,169;,
 4;174,173,153,151;,
 4;174,141,175,173;,
 4;179,178,177,176;,
 4;173,175,177,178;,
 4;180,153,173,178;,
 4;180,178,179,181;,
 4;183,180,181,182;,
 4;153,180,183,152;,
 4;185,121,125,184;,
 4;185,184,187,186;,
 4;189,185,186,188;,
 4;188,191,190,189;,
 4;190,123,120,189;,
 4;135,193,192,134;,
 4;192,193,195,194;,
 4;134,192,196,163;,
 4;194,197,196,192;,
 4;197,199,198,196;,
 4;198,164,163,196;,
 4;203,202,201,200;,
 4;140,144,203,200;,
 4;205,204,200,201;,
 4;207,206,204,205;,
 4;204,206,142,139;,
 4;147,159,209,208;,
 4;149,147,208,210;,
 4;156,149,210,211;,
 4;159,156,211,209;,
 4;215,214,213,212;,
 4;167,131,217,216;,
 4;169,167,216,218;,
 4;129,169,218,219;,
 4;131,129,219,217;,
 4;223,222,221,220;,
 4;189,120,225,224;,
 4;185,189,224,226;,
 4;121,185,226,227;,
 4;120,121,227,225;,
 4;200,204,229,228;,
 4;140,200,228,230;,
 4;139,140,230,231;,
 4;204,139,231,229;,
 4;232,233,234,235;,
 4;236,237,238,239;,
 4;240,241,242,243;,
 4;244,245,242,241;,
 4;233,246,247,248;,
 4;247,246,238,249;,
 4;250,251,252,253;,
 4;250,254,255,251;,
 4;232,256,257,258;,
 4;239,258,257,259;,
 4;260,261,262,263;,
 4;261,264,265,262;,
 4;264,266,267,265;,
 4;266,268,269,267;,
 4;268,270,271,269;,
 4;270,272,273,271;,
 4;272,274,275,273;,
 4;274,276,277,275;,
 3;278,261,260;,
 3;279,264,261;,
 3;280,266,264;,
 3;281,268,266;,
 3;282,270,268;,
 3;283,272,270;,
 3;284,274,272;,
 3;285,276,274;,
 3;286,263,262;,
 3;287,262,265;,
 3;288,265,267;,
 3;289,267,269;,
 3;290,269,271;,
 3;291,271,273;,
 3;292,273,275;,
 3;293,275,277;,
 4;294,295,296,297;,
 4;298,299,300,301;,
 4;302,301,303,304;,
 4;305,306,307,308;,
 4;309,310,311,300;,
 4;312,313,314,315;,
 4;316,312,315,317;,
 4;318,319,316,317;,
 4;320,304,303,321;,
 4;294,322,320,321;,
 4;306,323,324,307;,
 4;324,323,325,326;,
 4;311,310,327,328;,
 4;295,328,327,329;,
 4;330,331,332,333;,
 4;333,332,331,330;,
 4;334,335,336,337;,
 4;337,336,335,334;;
 
 MeshMaterialList {
  4;
  259;
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  3,
  0,
  0,
  0,
  0,
  0,
  0,
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
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
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
  0,
  0,
  0,
  0,
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
  3,
  0,
  0,
  0,
  0,
  0,
  0,
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
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
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
  0,
  0,
  0,
  0,
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
  2;;
  Material {
   0.561600;0.564800;0.536800;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
   TextureFilename {
    "stone-white00.png";
   }
  }
  Material {
   0.800000;0.800000;0.800000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
   TextureFilename {
    "cicle00 (1).png";
   }
  }
  Material {
   0.800000;0.800000;0.800000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
   TextureFilename {
    "cicle00 (1).png";
   }
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
  -0.000001;1.000000;0.000000;,
  -0.000000;0.868754;-0.495243;,
  0.350191;0.868753;-0.350191;,
  0.495243;0.868755;0.000000;,
  0.350191;0.868753;0.350191;,
  -0.000000;0.868754;0.495243;,
  -0.350193;0.868753;0.350189;,
  -0.495246;0.868753;0.000000;,
  -0.350193;0.868753;-0.350189;,
  -0.000001;0.709233;-0.704974;,
  0.498493;0.709232;-0.498492;,
  0.704975;0.709232;0.000000;,
  0.498493;0.709232;0.498492;,
  -0.000001;0.709233;0.704974;,
  -0.498495;0.709231;0.498492;,
  -0.704976;0.709231;0.000000;,
  -0.498495;0.709231;-0.498492;,
  -0.000001;0.384558;-0.923101;,
  0.652731;0.384558;-0.652731;,
  0.923101;0.384557;0.000000;,
  0.652731;0.384558;0.652731;,
  -0.000001;0.384558;0.923101;,
  -0.652731;0.384559;0.652730;,
  -0.923100;0.384559;0.000000;,
  -0.652731;0.384559;-0.652730;,
  -0.000001;0.000002;-1.000000;,
  0.707107;0.000002;-0.707107;,
  1.000000;0.000002;0.000000;,
  0.707107;0.000002;0.707107;,
  -0.000001;0.000002;1.000000;,
  -0.707107;0.000002;0.707107;,
  -1.000000;0.000003;0.000000;,
  -0.707107;0.000002;-0.707107;,
  -0.000001;-0.384551;-0.923104;,
  0.652733;-0.384550;-0.652733;,
  0.923104;-0.384549;-0.000000;,
  0.652734;-0.384550;0.652733;,
  -0.000001;-0.384551;0.923104;,
  -0.652734;-0.384551;0.652732;,
  -0.923104;-0.384552;0.000000;,
  -0.652734;-0.384551;-0.652732;,
  -0.000001;-0.888882;-0.458137;,
  0.430259;-0.793572;-0.430258;,
  0.608478;-0.793571;-0.000000;,
  0.323953;-0.888881;0.323952;,
  -0.000001;-0.888882;0.458137;,
  -0.430260;-0.793571;0.430257;,
  -0.608478;-0.793571;0.000000;,
  -0.323953;-0.888881;-0.323952;,
  0.000000;-0.115373;-0.993322;,
  0.997758;-0.066919;-0.000000;,
  0.000000;-0.090392;0.995906;,
  -0.990833;-0.135093;0.000000;,
  0.000000;1.000000;0.000000;,
  0.000000;-1.000000;-0.000000;,
  0.000000;0.879243;-0.476373;,
  0.000000;-1.000000;-0.000000;,
  0.000000;0.881718;0.471777;,
  -0.471660;0.881781;0.000000;,
  -0.999718;-0.023757;0.000000;,
  0.999718;-0.023749;-0.000000;,
  0.000000;-0.023758;0.999718;,
  0.397008;0.825743;0.400666;,
  -0.398977;0.825627;0.398946;,
  -0.399432;0.825747;-0.398240;,
  0.397464;0.825866;-0.399960;,
  0.000000;-0.023758;-0.999718;,
  0.264538;0.923892;-0.276484;,
  -0.283143;0.917966;-0.277792;,
  -0.283557;0.916116;0.283420;,
  -0.831801;0.555074;0.000000;,
  0.264929;0.922083;0.282090;,
  0.000000;0.554853;0.831949;,
  0.851560;0.524258;0.000000;,
  0.000000;0.000000;-1.000000;,
  1.000000;0.000000;0.000000;,
  -1.000000;0.000000;0.000000;,
  0.000000;1.000000;0.000000;,
  0.000000;-1.000000;-0.000000;,
  0.000000;0.000000;1.000000;,
  0.000000;1.000000;0.000000;,
  -0.251429;-0.934648;-0.251429;,
  0.251429;-0.934648;-0.251429;,
  0.251429;-0.934648;0.251429;,
  -0.251429;-0.934648;0.251429;,
  0.379618;-0.843671;0.379618;,
  -0.379618;-0.843671;0.379618;,
  0.000000;0.429756;-0.902945;,
  0.902945;0.429756;0.000000;,
  0.000000;0.429756;0.902945;,
  0.379618;-0.843671;-0.379618;,
  -0.379618;-0.843671;-0.379618;,
  -0.902945;0.429756;0.000000;,
  0.000000;1.000000;0.000000;,
  -0.000000;0.000000;-1.000000;,
  0.714549;0.000000;-0.699586;,
  1.000000;0.000000;0.000000;,
  0.714549;0.000000;0.699586;,
  -0.000000;0.000000;1.000000;,
  -0.714549;0.000000;0.699586;,
  -1.000000;0.000000;0.000000;,
  -0.714549;0.000000;-0.699586;,
  0.000000;-1.000000;-0.000000;,
  0.000000;0.879242;-0.476376;,
  0.000000;-1.000000;-0.000000;,
  0.000000;0.881717;0.471780;,
  -0.471662;0.881779;0.000000;,
  -0.999718;-0.023757;0.000000;,
  0.999718;-0.023749;-0.000000;,
  0.000000;-0.023757;0.999718;,
  0.397006;0.825745;0.400663;,
  -0.398974;0.825629;0.398943;,
  -0.399429;0.825750;-0.398237;,
  0.397462;0.825868;-0.399957;,
  0.000000;-0.023757;-0.999718;,
  0.264530;0.923897;-0.276476;,
  -0.283135;0.917971;-0.277784;,
  -0.283548;0.916121;0.283412;,
  -0.831804;0.555070;0.000000;,
  0.264921;0.922088;0.282082;,
  0.000000;0.554848;0.831952;,
  0.851562;0.524253;0.000000;,
  -1.000000;0.000000;0.000000;,
  1.000000;0.000000;0.000000;,
  1.000000;0.000000;-0.000001;,
  -1.000000;0.000000;0.000001;;
  259;
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
  4;41,42,43,44;,
  4;45,46,47,48;,
  4;44,45,48,41;,
  4;49,49,49,49;,
  4;50,50,50,50;,
  4;51,51,51,51;,
  4;52,52,52,52;,
  4;53,53,53,53;,
  4;54,54,54,54;,
  4;58,57,55,55;,
  4;56,56,56,56;,
  4;59,59,59,59;,
  4;61,61,61,61;,
  4;60,60,60,60;,
  4;66,66,66,66;,
  4;65,67,68,64;,
  4;55,55,65,64;,
  4;64,68,69,63;,
  4;58,70,64,63;,
  4;71,62,63,69;,
  4;63,62,57,72;,
  4;71,67,65,62;,
  4;73,62,65,73;,
  4;76,76,76,76;,
  4;76,76,76,76;,
  4;76,76,76,76;,
  4;74,74,74,74;,
  4;74,74,74,74;,
  4;74,74,74,74;,
  4;77,77,77,77;,
  4;75,75,75,75;,
  4;75,75,75,75;,
  4;75,75,75,75;,
  4;79,79,79,79;,
  4;79,79,79,79;,
  4;79,79,79,79;,
  4;78,78,78,78;,
  4;79,79,79,79;,
  4;79,79,79,79;,
  4;79,79,79,79;,
  4;79,79,79,79;,
  4;79,79,79,79;,
  4;77,77,77,77;,
  4;77,77,77,77;,
  4;74,74,74,74;,
  4;74,74,74,74;,
  4;74,74,74,74;,
  4;74,74,74,74;,
  4;74,74,74,74;,
  4;78,78,78,78;,
  4;78,78,78,78;,
  4;78,78,78,78;,
  4;78,78,78,78;,
  4;78,78,78,78;,
  4;78,78,78,78;,
  4;78,78,78,78;,
  4;78,78,78,78;,
  4;76,76,76,76;,
  4;76,76,76,76;,
  4;76,76,76,76;,
  4;76,76,76,76;,
  4;76,76,76,76;,
  4;77,77,77,77;,
  4;77,77,77,77;,
  4;77,77,77,77;,
  4;77,77,77,77;,
  4;77,77,77,77;,
  4;77,77,77,77;,
  4;75,75,75,75;,
  4;75,75,75,75;,
  4;75,75,75,75;,
  4;75,75,75,75;,
  4;75,75,75,75;,
  4;78,78,78,78;,
  4;75,75,75,75;,
  4;77,77,77,77;,
  4;76,76,76,76;,
  4;79,79,79,79;,
  4;78,78,78,78;,
  4;76,76,76,76;,
  4;77,77,77,77;,
  4;75,75,75,75;,
  4;74,74,74,74;,
  4;78,78,78,78;,
  4;79,79,79,79;,
  4;77,77,77,77;,
  4;74,74,74,74;,
  4;79,79,79,79;,
  4;78,78,78,78;,
  4;74,74,74,74;,
  4;77,77,77,77;,
  4;75,75,75,75;,
  4;75,75,75,75;,
  4;75,75,75,75;,
  4;79,79,79,79;,
  4;79,79,79,79;,
  4;79,79,79,79;,
  4;78,78,78,78;,
  4;76,76,76,76;,
  4;76,76,76,76;,
  4;76,76,76,76;,
  4;74,74,74,74;,
  4;74,74,74,74;,
  4;74,74,74,74;,
  4;77,77,77,77;,
  4;74,74,74,74;,
  4;74,74,74,74;,
  4;74,74,74,74;,
  4;74,74,74,74;,
  4;74,74,74,74;,
  4;78,78,78,78;,
  4;78,78,78,78;,
  4;79,79,79,79;,
  4;79,79,79,79;,
  4;79,79,79,79;,
  4;79,79,79,79;,
  4;79,79,79,79;,
  4;77,77,77,77;,
  4;77,77,77,77;,
  4;77,77,77,77;,
  4;77,77,77,77;,
  4;77,77,77,77;,
  4;77,77,77,77;,
  4;77,77,77,77;,
  4;77,77,77,77;,
  4;75,75,75,75;,
  4;75,75,75,75;,
  4;75,75,75,75;,
  4;75,75,75,75;,
  4;75,75,75,75;,
  4;78,78,78,78;,
  4;78,78,78,78;,
  4;78,78,78,78;,
  4;78,78,78,78;,
  4;78,78,78,78;,
  4;78,78,78,78;,
  4;76,76,76,76;,
  4;76,76,76,76;,
  4;76,76,76,76;,
  4;76,76,76,76;,
  4;76,76,76,76;,
  4;77,77,77,77;,
  4;76,76,76,76;,
  4;78,78,78,78;,
  4;75,75,75,75;,
  4;74,74,74,74;,
  4;77,77,77,77;,
  4;75,75,75,75;,
  4;78,78,78,78;,
  4;76,76,76,76;,
  4;79,79,79,79;,
  4;77,77,77,77;,
  4;74,74,74,74;,
  4;78,78,78,78;,
  4;79,79,79,79;,
  4;74,74,74,74;,
  4;77,77,77,77;,
  4;79,79,79,79;,
  4;78,78,78,78;,
  4;80,80,80,80;,
  4;81,82,83,84;,
  4;83,85,86,84;,
  4;89,89,89,89;,
  4;88,88,88,88;,
  4;90,85,83,82;,
  4;87,87,87,87;,
  4;90,82,81,91;,
  4;92,92,92,92;,
  4;84,86,91,81;,
  4;94,95,95,94;,
  4;95,96,96,95;,
  4;96,97,97,96;,
  4;97,98,98,97;,
  4;98,99,99,98;,
  4;99,100,100,99;,
  4;100,101,101,100;,
  4;101,94,94,101;,
  3;93,93,93;,
  3;93,93,93;,
  3;93,93,93;,
  3;93,93,93;,
  3;93,93,93;,
  3;93,93,93;,
  3;93,93,93;,
  3;93,93,93;,
  3;102,102,102;,
  3;102,102,102;,
  3;102,102,102;,
  3;102,102,102;,
  3;102,102,102;,
  3;102,102,102;,
  3;102,102,102;,
  3;102,102,102;,
  4;106,105,103,103;,
  4;104,104,104,104;,
  4;107,107,107,107;,
  4;109,109,109,109;,
  4;108,108,108,108;,
  4;114,114,114,114;,
  4;113,115,116,112;,
  4;103,103,113,112;,
  4;112,116,117,111;,
  4;106,118,112,111;,
  4;119,110,111,117;,
  4;111,110,105,120;,
  4;119,115,113,110;,
  4;121,110,113,121;,
  4;122,122,122,122;,
  4;123,123,123,123;,
  4;124,124,124,124;,
  4;125,125,125,125;;
 }
 MeshTextureCoords {
  338;
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
  1.000000;1.000000;,
  0.000000;0.500000;,
  1.000000;0.500000;,
  0.000000;1.000000;,
  0.000000;0.500000;,
  1.000000;0.500000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.500000;,
  1.000000;0.500000;,
  1.000000;0.500000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.500000;,
  1.000000;0.250000;,
  0.000000;0.250000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;0.250000;,
  0.000000;0.250000;,
  1.000000;0.000000;,
  0.000000;0.250000;,
  1.000000;0.250000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  0.000000;0.250000;,
  1.000000;0.250000;,
  0.000000;0.000000;,
  0.000000;0.500000;,
  0.000000;0.250000;,
  0.500000;0.250000;,
  0.500000;0.500000;,
  0.000000;0.000000;,
  0.500000;0.000000;,
  0.000000;1.000000;,
  0.500000;1.000000;,
  0.500000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.500000;,
  0.500000;0.500000;,
  0.000000;0.250000;,
  0.500000;0.250000;,
  0.000000;0.000000;,
  0.500000;0.000000;,
  0.500000;0.500000;,
  0.000000;0.500000;,
  0.500000;0.000000;,
  1.000000;0.250000;,
  1.000000;0.500000;,
  0.500000;0.500000;,
  0.500000;0.250000;,
  1.000000;1.000000;,
  0.500000;1.000000;,
  1.000000;0.000000;,
  0.500000;0.000000;,
  1.000000;0.000000;,
  1.000000;0.250000;,
  0.500000;0.250000;,
  1.000000;0.500000;,
  0.500000;0.500000;,
  1.000000;1.000000;,
  0.500000;1.000000;,
  0.000000;0.500000;,
  0.500000;0.500000;,
  0.000000;1.000000;,
  0.000000;0.500000;,
  0.250000;0.500000;,
  0.250000;1.000000;,
  0.000000;0.250000;,
  0.250000;0.250000;,
  0.000000;0.000000;,
  0.250000;0.000000;,
  0.750000;0.000000;,
  0.750000;0.500000;,
  1.000000;0.500000;,
  1.000000;0.000000;,
  1.000000;0.250000;,
  0.750000;0.250000;,
  0.750000;0.000000;,
  0.750000;0.500000;,
  1.000000;0.500000;,
  1.000000;1.000000;,
  0.750000;1.000000;,
  0.750000;0.500000;,
  0.750000;1.000000;,
  1.000000;0.500000;,
  1.000000;0.000000;,
  1.000000;0.250000;,
  0.750000;0.250000;,
  0.750000;0.000000;,
  0.500000;0.250000;,
  0.500000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.250000;,
  0.750000;1.000000;,
  0.750000;0.500000;,
  1.000000;0.500000;,
  1.000000;1.000000;,
  1.000000;0.250000;,
  0.750000;0.250000;,
  0.750000;0.000000;,
  1.000000;0.000000;,
  0.500000;0.750000;,
  0.000000;0.750000;,
  0.500000;1.000000;,
  0.000000;1.000000;,
  0.750000;0.750000;,
  0.750000;1.000000;,
  1.000000;0.750000;,
  1.000000;1.000000;,
  0.250000;0.250000;,
  0.000000;0.250000;,
  0.000000;0.000000;,
  0.250000;0.000000;,
  0.250000;0.500000;,
  0.000000;0.500000;,
  0.250000;1.000000;,
  0.000000;1.000000;,
  0.500000;0.250000;,
  0.250000;0.250000;,
  0.500000;0.500000;,
  0.250000;0.500000;,
  0.118330;0.832722;,
  0.938173;0.832722;,
  0.938173;0.112563;,
  0.118330;0.112563;,
  0.750000;0.250000;,
  0.500000;0.250000;,
  0.750000;0.500000;,
  0.500000;0.500000;,
  0.986199;0.832722;,
  0.166356;0.832722;,
  0.166356;0.112563;,
  0.986199;0.112563;,
  0.750000;0.250000;,
  0.500000;0.250000;,
  0.750000;0.500000;,
  0.500000;0.500000;,
  0.250000;0.250000;,
  0.250000;0.500000;,
  0.500000;0.250000;,
  0.500000;0.500000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.500000;,
  1.000000;0.500000;,
  1.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;0.500000;,
  0.000000;0.500000;,
  0.000000;0.000000;,
  0.000000;1.000000;,
  1.000000;0.500000;,
  0.000000;0.500000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  1.000000;0.000000;,
  1.000000;0.500000;,
  0.000000;0.500000;,
  1.000000;1.000000;,
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
  0.937500;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  1.000000;1.000000;,
  0.000000;0.500000;,
  1.000000;0.500000;,
  0.000000;1.000000;,
  0.000000;0.500000;,
  1.000000;0.500000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.500000;,
  1.000000;0.500000;,
  1.000000;0.500000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.500000;,
  1.000000;0.250000;,
  0.000000;0.250000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;0.250000;,
  0.000000;0.250000;,
  1.000000;0.000000;,
  0.000000;0.250000;,
  1.000000;0.250000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  0.000000;0.250000;,
  1.000000;0.250000;,
  0.000000;0.000000;,
  1.013970;0.078826;,
  1.013970;-0.916206;,
  0.018940;-0.916206;,
  0.018940;0.078826;,
  0.018940;0.078826;,
  0.018940;-0.916206;,
  1.013970;-0.916206;,
  1.013970;0.078826;;
 }
}