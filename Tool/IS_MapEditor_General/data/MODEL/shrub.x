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
 334;
 56.31182;84.91016;-7.54066;,
 31.75569;84.91016;-43.94670;,
 -4.65044;84.91016;-19.39053;,
 19.90582;84.91016;17.01560;,
 -0.30865;112.08520;0.07815;,
 -0.18567;112.08520;0.12706;,
 2.44201;-0.07009;-2.98134;,
 -0.30865;-0.07009;-4.31784;,
 -0.13464;112.08520;0.24529;,
 3.58137;-0.07009;0.24529;,
 -0.18567;112.08520;0.36351;,
 2.44201;-0.07009;3.47191;,
 -0.30865;112.08520;0.41243;,
 -0.30865;-0.07009;4.80842;,
 -0.43163;112.08520;0.36351;,
 -3.05931;-0.07009;3.47191;,
 -0.48266;112.08520;0.24529;,
 -4.19867;-0.07009;0.24529;,
 -0.43163;112.08520;0.12706;,
 -3.05931;-0.07009;-2.98134;,
 -0.30865;112.08520;0.07815;,
 -0.30865;-0.07009;-4.31784;,
 -0.30865;112.08520;0.24529;,
 -0.30865;112.08520;0.24529;,
 -0.30865;112.08520;0.24529;,
 -0.30865;112.08520;0.24529;,
 -0.30865;112.08520;0.24529;,
 -0.30865;112.08520;0.24529;,
 -0.30865;112.08520;0.24529;,
 -0.30865;112.08520;0.24529;,
 -0.30865;-0.07009;0.24529;,
 -0.30865;-0.07009;0.24529;,
 -0.30865;-0.07009;0.24529;,
 -0.30865;-0.07009;0.24529;,
 -0.30865;-0.07009;0.24529;,
 -0.30865;-0.07009;0.24529;,
 -0.30865;-0.07009;0.24529;,
 -0.30865;-0.07009;0.24529;,
 17.08849;101.56460;-4.24896;,
 17.13287;101.53572;-4.23342;,
 0.65765;68.64106;-1.06945;,
 -0.00036;69.47277;-1.61409;,
 17.15125;101.52377;-4.19613;,
 1.18813;68.29663;0.24529;,
 17.13287;101.53572;-4.15873;,
 0.65765;68.64106;1.56003;,
 17.08849;101.56460;-4.14330;,
 -0.62297;69.47277;2.10466;,
 17.04402;101.59342;-4.15873;,
 -1.28108;70.30444;1.56003;,
 17.02563;101.60532;-4.19613;,
 -1.81156;70.64886;0.24529;,
 17.04402;101.59342;-4.23342;,
 -1.28108;70.30444;-1.06945;,
 17.08849;101.56460;-4.24896;,
 -0.00036;69.47277;-1.61409;,
 17.08849;101.56460;-4.19613;,
 17.08849;101.56460;-4.19613;,
 17.08849;101.56460;-4.19613;,
 17.08849;101.56460;-4.19613;,
 17.08849;101.56460;-4.19613;,
 17.08849;101.56460;-4.19613;,
 17.08849;101.56460;-4.19613;,
 17.08849;101.56460;-4.19613;,
 -0.00036;69.47277;0.24529;,
 -0.00036;69.47277;0.24529;,
 -0.00036;69.47277;0.24529;,
 -0.00036;69.47277;0.24529;,
 -0.00036;69.47277;0.24529;,
 -0.00036;69.47277;0.24529;,
 -0.00036;69.47277;0.24529;,
 -0.00036;69.47277;0.24529;,
 24.06536;27.79965;0.35231;,
 24.06536;27.76713;0.36541;,
 -0.29460;27.07340;-0.29671;,
 -0.29460;27.79965;-0.52080;,
 24.06536;27.75370;0.39690;,
 -0.29460;26.77250;0.24444;,
 24.06536;27.76713;0.42849;,
 -0.29460;27.07340;0.78559;,
 24.06536;27.79965;0.44148;,
 -0.29460;27.79965;1.00968;,
 24.06536;27.83209;0.42849;,
 -0.29460;28.52591;0.78559;,
 24.06536;27.84561;0.39690;,
 -0.29460;28.82670;0.24444;,
 24.06536;27.83209;0.36541;,
 -0.29460;28.52591;-0.29671;,
 24.06536;27.79965;0.35231;,
 -0.29460;27.79965;-0.52080;,
 24.06536;27.79965;0.39690;,
 24.06536;27.79965;0.39690;,
 24.06536;27.79965;0.39690;,
 24.06536;27.79965;0.39690;,
 24.06536;27.79965;0.39690;,
 24.06536;27.79965;0.39690;,
 24.06536;27.79965;0.39690;,
 24.06536;27.79965;0.39690;,
 -0.29460;27.79965;0.24444;,
 -0.29460;27.79965;0.24444;,
 -0.29460;27.79965;0.24444;,
 -0.29460;27.79965;0.24444;,
 -0.29460;27.79965;0.24444;,
 -0.29460;27.79965;0.24444;,
 -0.29460;27.79965;0.24444;,
 -0.29460;27.79965;0.24444;,
 -25.39634;27.79965;0.44148;,
 -25.39634;27.76713;0.42849;,
 -1.03638;27.07340;0.78559;,
 -1.03638;27.79965;1.00968;,
 -25.39634;27.75370;0.39690;,
 -1.03638;26.77250;0.24444;,
 -25.39634;27.76713;0.36541;,
 -1.03638;27.07340;-0.29671;,
 -25.39634;27.79965;0.35231;,
 -1.03638;27.79965;-0.52080;,
 -25.39634;27.83209;0.36541;,
 -1.03638;28.52591;-0.29671;,
 -25.39634;27.84561;0.39690;,
 -1.03638;28.82670;0.24444;,
 -25.39634;27.83209;0.42849;,
 -1.03638;28.52591;0.78559;,
 -25.39634;27.79965;0.44148;,
 -1.03638;27.79965;1.00968;,
 -25.39634;27.79965;0.39690;,
 -25.39634;27.79965;0.39690;,
 -25.39634;27.79965;0.39690;,
 -25.39634;27.79965;0.39690;,
 -25.39634;27.79965;0.39690;,
 -25.39634;27.79965;0.39690;,
 -25.39634;27.79965;0.39690;,
 -25.39634;27.79965;0.39690;,
 -1.03638;27.79965;0.24444;,
 -1.03638;27.79965;0.24444;,
 -1.03638;27.79965;0.24444;,
 -1.03638;27.79965;0.24444;,
 -1.03638;27.79965;0.24444;,
 -1.03638;27.79965;0.24444;,
 -1.03638;27.79965;0.24444;,
 -1.03638;27.79965;0.24444;,
 -23.60258;32.33510;6.13858;,
 -23.60553;32.32337;6.13351;,
 -13.69037;27.53837;0.59278;,
 -13.64040;27.79965;0.67931;,
 -23.61261;32.31851;6.12136;,
 -13.81092;27.43018;0.38390;,
 -23.61958;32.32337;6.10921;,
 -13.93158;27.53837;0.17503;,
 -23.62254;32.33510;6.10414;,
 -13.98155;27.79965;0.08850;,
 -23.61958;32.34672;6.10921;,
 -13.93158;28.06083;0.17503;,
 -23.61261;32.35159;6.12136;,
 -13.81092;28.16911;0.38390;,
 -23.60553;32.34672;6.13351;,
 -13.69037;28.06083;0.59278;,
 -23.60258;32.33510;6.13858;,
 -13.64040;27.79965;0.67931;,
 -23.61261;32.33510;6.12136;,
 -23.61261;32.33510;6.12136;,
 -23.61261;32.33510;6.12136;,
 -23.61261;32.33510;6.12136;,
 -23.61261;32.33510;6.12136;,
 -23.61261;32.33510;6.12136;,
 -23.61261;32.33510;6.12136;,
 -23.61261;32.33510;6.12136;,
 -13.81092;27.79965;0.38390;,
 -13.81092;27.79965;0.38390;,
 -13.81092;27.79965;0.38390;,
 -13.81092;27.79965;0.38390;,
 -13.81092;27.79965;0.38390;,
 -13.81092;27.79965;0.38390;,
 -13.81092;27.79965;0.38390;,
 -13.81092;27.79965;0.38390;,
 -23.73675;25.86199;-5.20257;,
 -23.73390;25.85036;-5.20764;,
 -13.97786;27.53837;0.60884;,
 -14.02782;27.79965;0.69537;,
 -23.72681;25.84550;-5.21979;,
 -13.85730;27.43018;0.39996;,
 -23.71984;25.85036;-5.23194;,
 -13.73665;27.53837;0.19109;,
 -23.71689;25.86199;-5.23701;,
 -13.68678;27.79965;0.10456;,
 -23.71984;25.87372;-5.23194;,
 -13.73665;28.06083;0.19109;,
 -23.72681;25.87857;-5.21979;,
 -13.85730;28.16911;0.39996;,
 -23.73390;25.87372;-5.20764;,
 -13.97786;28.06083;0.60884;,
 -23.73675;25.86199;-5.20257;,
 -14.02782;27.79965;0.69537;,
 -23.72681;25.86199;-5.21979;,
 -23.72681;25.86199;-5.21979;,
 -23.72681;25.86199;-5.21979;,
 -23.72681;25.86199;-5.21979;,
 -23.72681;25.86199;-5.21979;,
 -23.72681;25.86199;-5.21979;,
 -23.72681;25.86199;-5.21979;,
 -23.72681;25.86199;-5.21979;,
 -13.85730;27.79965;0.39996;,
 -13.85730;27.79965;0.39996;,
 -13.85730;27.79965;0.39996;,
 -13.85730;27.79965;0.39996;,
 -13.85730;27.79965;0.39996;,
 -13.85730;27.79965;0.39996;,
 -13.85730;27.79965;0.39996;,
 -13.85730;27.79965;0.39996;,
 -11.49322;69.05775;-4.24896;,
 -11.44145;69.06875;-4.23342;,
 0.16879;34.15908;-1.06945;,
 -0.88456;34.28185;-1.61409;,
 -11.42000;69.07339;-4.19613;,
 0.78749;34.29051;0.24529;,
 -11.44145;69.06875;-4.15873;,
 0.16879;34.15908;1.56003;,
 -11.49322;69.05775;-4.14330;,
 -1.32481;33.84160;2.10466;,
 -11.54510;69.04676;-4.15873;,
 -2.37817;33.96437;1.56003;,
 -11.56654;69.04222;-4.19613;,
 -2.99687;33.83282;0.24529;,
 -11.54510;69.04676;-4.23342;,
 -2.37817;33.96437;-1.06945;,
 -11.49322;69.05775;-4.24896;,
 -0.88456;34.28185;-1.61409;,
 -11.49322;69.05775;-4.19613;,
 -11.49322;69.05775;-4.19613;,
 -11.49322;69.05775;-4.19613;,
 -11.49322;69.05775;-4.19613;,
 -11.49322;69.05775;-4.19613;,
 -11.49322;69.05775;-4.19613;,
 -11.49322;69.05775;-4.19613;,
 -11.49322;69.05775;-4.19613;,
 -0.88456;34.28185;0.24529;,
 -0.88456;34.28185;0.24529;,
 -0.88456;34.28185;0.24529;,
 -0.88456;34.28185;0.24529;,
 -0.88456;34.28185;0.24529;,
 -0.88456;34.28185;0.24529;,
 -0.88456;34.28185;0.24529;,
 -0.88456;34.28185;0.24529;,
 61.95293;90.80242;-9.51139;,
 37.39679;90.80242;-45.91741;,
 0.99066;94.76286;-21.36125;,
 25.54682;94.76286;15.04486;,
 65.25037;111.40629;-10.34499;,
 40.69431;111.40629;-46.75098;,
 7.18707;101.40957;-22.19485;,
 25.94545;101.40957;14.21126;,
 50.95031;74.70869;-6.29153;,
 26.39425;74.70869;-42.69756;,
 -10.01187;74.70869;-18.14140;,
 14.54428;74.70869;18.26461;,
 47.93573;57.63251;-6.29153;,
 23.37957;57.63251;-42.69756;,
 -13.02655;57.63251;-18.14140;,
 11.52970;57.63251;18.26461;,
 47.93573;51.41519;-6.29153;,
 23.37957;51.41519;-42.69756;,
 -13.02655;51.41519;-18.14140;,
 11.52970;51.41519;18.26461;,
 51.32802;28.27086;-5.88519;,
 26.77196;28.27086;-42.29121;,
 -9.63416;28.27086;-17.73506;,
 14.92210;28.27086;18.67096;,
 30.95642;28.27086;39.14967;,
 50.20682;28.27086;-0.31953;,
 10.73762;28.27086;-19.57002;,
 -8.51287;28.27086;19.89927;,
 -54.07652;28.27086;6.53667;,
 -29.52048;28.27086;42.94270;,
 6.88564;28.27086;18.38655;,
 -17.67050;28.27086;-18.01948;,
 -33.09851;27.77768;-44.93696;,
 -61.90844;27.77768;-11.79507;,
 -28.76643;27.77768;17.01496;,
 0.04349;27.77768;-16.12713;,
 -56.22329;23.26569;-26.87717;,
 -64.60256;23.26569;16.22944;,
 -21.49564;29.42183;24.60862;,
 -13.11658;29.42183;-18.49819;,
 -35.88582;21.62427;-46.53812;,
 -64.69576;20.84201;-13.39623;,
 -31.55366;26.99818;15.41370;,
 -2.74373;26.99818;-17.72829;,
 -43.18272;47.50109;-31.41386;,
 -51.56199;47.50109;11.69283;,
 -8.45508;47.50109;20.07203;,
 -0.07600;47.50109;-23.03479;,
 -45.90274;55.46759;-31.41386;,
 -54.28203;55.46759;11.69283;,
 -11.17511;55.46759;20.07203;,
 -2.79592;55.46759;-23.03479;,
 -48.50335;77.38192;-33.24863;,
 -56.88255;77.38192;9.85797;,
 -13.77563;64.19353;18.23716;,
 -5.39655;64.19353;-24.86966;,
 -38.50421;109.15294;-29.27336;,
 -46.88350;109.15294;13.83335;,
 -3.77658;85.90572;22.21253;,
 4.60249;85.90572;-20.89428;,
 -6.41885;92.55677;-48.77954;,
 -42.82484;92.55677;-24.22359;,
 -18.26872;79.36836;12.18253;,
 18.13742;79.36836;-12.37362;,
 -6.71636;115.73151;-48.20131;,
 -43.12238;115.73151;-23.64536;,
 -18.56624;102.54310;12.76087;,
 17.83979;102.54310;-11.79539;,
 -6.41885;62.25353;-48.77954;,
 -42.82484;62.25353;-24.22359;,
 -18.26872;69.32698;12.18253;,
 18.13742;69.32698;-12.37362;,
 14.17819;77.50073;47.11373;,
 50.58431;77.50073;22.55770;,
 26.02807;84.91016;-13.84842;,
 -10.37795;84.91016;10.70772;,
 10.06145;63.29917;48.33879;,
 46.46748;63.29917;23.78253;,
 21.91132;77.95506;-12.62349;,
 -14.49481;77.95506;11.93266;,
 5.38506;41.01476;48.33879;,
 41.79120;41.01476;23.78253;,
 17.23493;49.54217;-12.62349;,
 -19.17109;49.54217;11.93266;,
 -29.86872;44.32137;38.96087;,
 13.23810;44.32137;47.34005;,
 21.61729;52.84889;4.23324;,
 -21.48952;52.84889;-4.14594;,
 38.00113;38.18022;-28.62740;,
 -1.46829;38.18022;-47.87792;,
 -20.71869;46.70763;-8.40859;,
 18.75062;46.70763;10.84191;;
 
 216;
 4;0,1,2,3;,
 4;3,2,1,0;,
 4;4,5,6,7;,
 4;5,8,9,6;,
 4;8,10,11,9;,
 4;10,12,13,11;,
 4;12,14,15,13;,
 4;14,16,17,15;,
 4;16,18,19,17;,
 4;18,20,21,19;,
 3;22,5,4;,
 3;23,8,5;,
 3;24,10,8;,
 3;25,12,10;,
 3;26,14,12;,
 3;27,16,14;,
 3;28,18,16;,
 3;29,20,18;,
 3;30,7,6;,
 3;31,6,9;,
 3;32,9,11;,
 3;33,11,13;,
 3;34,13,15;,
 3;35,15,17;,
 3;36,17,19;,
 3;37,19,21;,
 4;38,39,40,41;,
 4;39,42,43,40;,
 4;42,44,45,43;,
 4;44,46,47,45;,
 4;46,48,49,47;,
 4;48,50,51,49;,
 4;50,52,53,51;,
 4;52,54,55,53;,
 3;56,39,38;,
 3;57,42,39;,
 3;58,44,42;,
 3;59,46,44;,
 3;60,48,46;,
 3;61,50,48;,
 3;62,52,50;,
 3;63,54,52;,
 3;64,41,40;,
 3;65,40,43;,
 3;66,43,45;,
 3;67,45,47;,
 3;68,47,49;,
 3;69,49,51;,
 3;70,51,53;,
 3;71,53,55;,
 4;72,73,74,75;,
 4;73,76,77,74;,
 4;76,78,79,77;,
 4;78,80,81,79;,
 4;80,82,83,81;,
 4;82,84,85,83;,
 4;84,86,87,85;,
 4;86,88,89,87;,
 3;90,73,72;,
 3;91,76,73;,
 3;92,78,76;,
 3;93,80,78;,
 3;94,82,80;,
 3;95,84,82;,
 3;96,86,84;,
 3;97,88,86;,
 3;98,75,74;,
 3;99,74,77;,
 3;100,77,79;,
 3;101,79,81;,
 3;102,81,83;,
 3;103,83,85;,
 3;104,85,87;,
 3;105,87,89;,
 4;106,107,108,109;,
 4;107,110,111,108;,
 4;110,112,113,111;,
 4;112,114,115,113;,
 4;114,116,117,115;,
 4;116,118,119,117;,
 4;118,120,121,119;,
 4;120,122,123,121;,
 3;124,107,106;,
 3;125,110,107;,
 3;126,112,110;,
 3;127,114,112;,
 3;128,116,114;,
 3;129,118,116;,
 3;130,120,118;,
 3;131,122,120;,
 3;132,109,108;,
 3;133,108,111;,
 3;134,111,113;,
 3;135,113,115;,
 3;136,115,117;,
 3;137,117,119;,
 3;138,119,121;,
 3;139,121,123;,
 4;140,141,142,143;,
 4;141,144,145,142;,
 4;144,146,147,145;,
 4;146,148,149,147;,
 4;148,150,151,149;,
 4;150,152,153,151;,
 4;152,154,155,153;,
 4;154,156,157,155;,
 3;158,141,140;,
 3;159,144,141;,
 3;160,146,144;,
 3;161,148,146;,
 3;162,150,148;,
 3;163,152,150;,
 3;164,154,152;,
 3;165,156,154;,
 3;166,143,142;,
 3;167,142,145;,
 3;168,145,147;,
 3;169,147,149;,
 3;170,149,151;,
 3;171,151,153;,
 3;172,153,155;,
 3;173,155,157;,
 4;174,175,176,177;,
 4;175,178,179,176;,
 4;178,180,181,179;,
 4;180,182,183,181;,
 4;182,184,185,183;,
 4;184,186,187,185;,
 4;186,188,189,187;,
 4;188,190,191,189;,
 3;192,175,174;,
 3;193,178,175;,
 3;194,180,178;,
 3;195,182,180;,
 3;196,184,182;,
 3;197,186,184;,
 3;198,188,186;,
 3;199,190,188;,
 3;200,177,176;,
 3;201,176,179;,
 3;202,179,181;,
 3;203,181,183;,
 3;204,183,185;,
 3;205,185,187;,
 3;206,187,189;,
 3;207,189,191;,
 4;208,209,210,211;,
 4;209,212,213,210;,
 4;212,214,215,213;,
 4;214,216,217,215;,
 4;216,218,219,217;,
 4;218,220,221,219;,
 4;220,222,223,221;,
 4;222,224,225,223;,
 3;226,209,208;,
 3;227,212,209;,
 3;228,214,212;,
 3;229,216,214;,
 3;230,218,216;,
 3;231,220,218;,
 3;232,222,220;,
 3;233,224,222;,
 3;234,211,210;,
 3;235,210,213;,
 3;236,213,215;,
 3;237,215,217;,
 3;238,217,219;,
 3;239,219,221;,
 3;240,221,223;,
 3;241,223,225;,
 4;242,243,244,245;,
 4;245,244,243,242;,
 4;246,247,248,249;,
 4;249,248,247,246;,
 4;250,251,252,253;,
 4;253,252,251,250;,
 4;254,255,256,257;,
 4;257,256,255,254;,
 4;258,259,260,261;,
 4;261,260,259,258;,
 4;262,263,264,265;,
 4;265,264,263,262;,
 4;266,267,268,269;,
 4;269,268,267,266;,
 4;270,271,272,273;,
 4;273,272,271,270;,
 4;274,275,276,277;,
 4;277,276,275,274;,
 4;278,279,280,281;,
 4;281,280,279,278;,
 4;282,283,284,285;,
 4;285,284,283,282;,
 4;286,287,288,289;,
 4;289,288,287,286;,
 4;290,291,292,293;,
 4;293,292,291,290;,
 4;294,295,296,297;,
 4;297,296,295,294;,
 4;298,299,300,301;,
 4;301,300,299,298;,
 4;302,303,304,305;,
 4;305,304,303,302;,
 4;306,307,308,309;,
 4;309,308,307,306;,
 4;310,311,312,313;,
 4;313,312,311,310;,
 4;314,315,316,317;,
 4;317,316,315,314;,
 4;318,319,320,321;,
 4;321,320,319,318;,
 4;322,323,324,325;,
 4;325,324,323,322;,
 4;326,327,328,329;,
 4;329,328,327,326;,
 4;330,331,332,333;,
 4;333,332,331,330;;
 
 MeshMaterialList {
  2;
  216;
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
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
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
    "C:\\Users\\student\\Desktop\\groupE\\project\\data\\TEXTURE\\reaf02.png";
   }
  }
  Material {
   0.800000;0.800000;0.800000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
   TextureFilename {
    "af18.jpg";
   }
  }
 }
 MeshNormals {
  180;
  0.000000;1.000000;0.000000;,
  0.000000;-1.000000;-0.000000;,
  0.000000;1.000000;0.000000;,
  -0.000000;0.038070;-0.999275;,
  0.721353;0.035533;-0.691656;,
  0.999450;0.033156;0.000000;,
  0.721353;0.035532;0.691656;,
  -0.000000;0.038070;0.999275;,
  -0.721353;0.035532;0.691656;,
  -0.999450;0.033156;0.000000;,
  -0.721353;0.035533;-0.691656;,
  0.000000;-1.000000;-0.000000;,
  0.544583;0.838707;0.000000;,
  -0.006666;-0.079159;-0.996840;,
  0.568506;-0.354354;-0.742452;,
  0.901590;-0.432577;-0.003690;,
  0.631772;-0.185782;0.752561;,
  0.064158;0.154897;0.985845;,
  -0.509399;0.433300;0.743481;,
  -0.853740;0.520699;0.000415;,
  -0.588689;0.267644;-0.762766;,
  -0.644762;-0.762467;-0.054090;,
  0.545382;0.838188;-0.000067;,
  0.544639;0.838670;0.000000;,
  0.545342;0.838214;-0.000000;,
  0.545382;0.838188;0.000067;,
  0.544639;0.838670;0.000000;,
  0.543784;0.839225;-0.000124;,
  0.543711;0.839273;0.000000;,
  0.543784;0.839225;0.000124;,
  -0.673332;-0.739340;0.000000;,
  -0.744407;-0.665947;0.048719;,
  -0.703406;-0.710788;-0.000000;,
  -0.648140;-0.746970;-0.148155;,
  -0.639604;-0.738267;-0.214170;,
  -0.621948;-0.774422;-0.115978;,
  -0.544600;-0.838696;0.000000;,
  -0.544609;-0.838690;-0.000013;,
  1.000000;0.000000;0.000000;,
  0.035883;0.000207;-0.999356;,
  0.039221;-0.665058;-0.745761;,
  0.039463;-0.999221;-0.000243;,
  0.029237;-0.664974;0.746294;,
  0.023381;0.000206;0.999727;,
  0.029227;0.664719;0.746522;,
  0.039477;0.999220;-0.000244;,
  0.039198;0.664803;-0.745990;,
  -1.000000;0.000000;0.000000;,
  -1.000000;0.000000;0.000000;,
  -0.023381;0.000206;0.999727;,
  -0.029237;-0.664974;0.746294;,
  -0.039463;-0.999221;-0.000242;,
  -0.039221;-0.665058;-0.745761;,
  -0.035883;0.000207;-0.999356;,
  -0.039198;0.664803;-0.745990;,
  -0.039477;0.999220;-0.000244;,
  -0.029227;0.664719;0.746522;,
  1.000000;0.000000;0.000000;,
  -0.865488;0.000003;0.500930;,
  0.480827;0.002542;0.876812;,
  0.079884;-0.679944;0.728900;,
  -0.341609;-0.918892;0.197332;,
  -0.596799;-0.678416;-0.428465;,
  -0.528970;0.002973;-0.848636;,
  -0.128974;0.692517;-0.709778;,
  0.299001;0.938373;-0.173366;,
  0.556041;0.691446;0.461216;,
  0.866004;0.000000;-0.500038;,
  -0.863964;-0.000062;0.503554;,
  -0.863990;0.000001;0.503510;,
  -0.865760;0.000000;0.500459;,
  -0.867004;-0.001361;0.498300;,
  -0.866436;0.000013;0.499288;,
  -0.867004;0.001373;0.498300;,
  -0.865760;0.000000;0.500459;,
  -0.863964;0.000063;0.503554;,
  0.866066;0.000000;-0.499930;,
  0.866088;-0.000041;-0.499891;,
  0.866010;0.000000;-0.500027;,
  0.865919;-0.000019;-0.500185;,
  0.865929;0.000000;-0.500167;,
  0.865919;0.000019;-0.500185;,
  0.866088;0.000042;-0.499891;,
  -0.865918;0.000010;-0.500185;,
  -0.519523;-0.001760;0.854455;,
  -0.262569;-0.715754;0.647112;,
  0.119904;-0.990397;0.068821;,
  0.422145;-0.716688;-0.555114;,
  0.469708;-0.001940;-0.882820;,
  0.210435;0.709717;-0.672323;,
  -0.170176;0.980475;-0.098529;,
  -0.470662;0.710186;0.523558;,
  0.866037;-0.000000;0.499980;,
  -0.864958;0.002991;-0.501836;,
  -0.866199;0.000029;-0.499699;,
  -0.865504;0.000000;-0.500902;,
  -0.866872;0.000981;-0.498530;,
  -0.866466;0.000009;-0.499236;,
  -0.866872;-0.000972;-0.498530;,
  -0.864958;-0.002962;-0.501836;,
  0.866060;-0.000000;0.499940;,
  0.866077;0.000031;0.499911;,
  0.866010;0.000000;0.500027;,
  0.865997;0.000131;0.500049;,
  0.866068;-0.000000;0.499926;,
  0.865997;-0.000132;0.500049;,
  0.866010;0.000000;0.500027;,
  0.866077;-0.000031;0.499911;,
  -0.207804;0.978171;-0.000001;,
  0.051285;-0.060679;-0.996839;,
  0.652516;0.151408;-0.742495;,
  0.943394;0.331653;-0.003627;,
  0.577971;0.315331;0.752672;,
  -0.064099;0.154912;0.985847;,
  -0.666458;-0.053762;0.743601;,
  -0.971877;-0.235489;0.000452;,
  -0.605470;-0.227006;-0.762807;,
  0.083218;-0.995062;-0.054089;,
  -0.208310;0.978063;-0.000854;,
  -0.207529;0.978229;0.000000;,
  -0.208898;0.977937;-0.000002;,
  -0.208310;0.978063;0.000852;,
  -0.207529;0.978229;0.000000;,
  -0.207298;0.978278;0.000056;,
  -0.207260;0.978286;-0.000000;,
  -0.207298;0.978278;-0.000057;,
  0.046690;-0.998909;-0.000000;,
  -0.055469;-0.997273;0.048680;,
  0.005183;-0.999987;-0.000000;,
  0.069888;-0.986499;-0.148108;,
  0.069766;-0.974303;-0.214166;,
  0.107780;-0.987386;-0.115981;,
  0.207931;-0.978144;0.000000;,
  0.207919;-0.978146;-0.000013;,
  0.074466;0.995958;-0.050228;,
  -0.074466;-0.995958;0.050228;,
  -0.191105;0.974936;0.113925;,
  0.191105;-0.974936;-0.113925;,
  0.000000;1.000000;0.000000;,
  0.000000;-1.000000;-0.000000;,
  0.000000;1.000000;0.000000;,
  0.000000;-1.000000;-0.000000;,
  0.000000;1.000000;0.000000;,
  0.000000;-1.000000;-0.000000;,
  0.000000;1.000000;0.000000;,
  0.000000;-1.000000;-0.000000;,
  0.000000;1.000000;0.000000;,
  0.000000;-1.000000;-0.000000;,
  0.000000;1.000000;0.000000;,
  0.000000;-1.000000;-0.000000;,
  0.000000;1.000000;0.000000;,
  0.000000;-1.000000;0.000000;,
  -0.136279;0.990316;-0.026490;,
  0.136279;-0.990316;0.026490;,
  -0.104011;0.991455;-0.078729;,
  0.104011;-0.991455;0.078729;,
  0.000000;1.000000;0.000000;,
  0.000000;-1.000000;-0.000000;,
  0.000000;1.000000;0.000000;,
  0.000000;-1.000000;0.000000;,
  0.282349;0.957740;0.054883;,
  -0.282349;-0.957740;-0.054883;,
  0.459273;0.883798;0.089274;,
  -0.459273;-0.883798;-0.089274;,
  0.160842;0.957740;0.238460;,
  -0.160842;-0.957740;-0.238460;,
  0.160843;0.957740;0.238460;,
  -0.160843;-0.957740;-0.238460;,
  -0.088926;0.987274;-0.131839;,
  0.088926;-0.987274;0.131839;,
  0.093036;0.986062;0.137932;,
  -0.093036;-0.986062;-0.137932;,
  0.177028;0.948567;0.262455;,
  -0.177028;-0.948567;-0.262455;,
  0.106596;0.981663;0.158035;,
  -0.106596;-0.981663;-0.158035;,
  -0.036374;0.981662;0.187125;,
  0.036374;-0.981662;-0.187125;,
  0.083565;0.981663;-0.171333;,
  -0.083565;-0.981663;0.171333;;
  216;
  4;0,0,0,0;,
  4;1,1,1,1;,
  4;3,4,4,3;,
  4;4,5,5,4;,
  4;5,6,6,5;,
  4;6,7,7,6;,
  4;7,8,8,7;,
  4;8,9,9,8;,
  4;9,10,10,9;,
  4;10,3,3,10;,
  3;2,2,2;,
  3;2,2,2;,
  3;2,2,2;,
  3;2,2,2;,
  3;2,2,2;,
  3;2,2,2;,
  3;2,2,2;,
  3;2,2,2;,
  3;11,11,11;,
  3;11,11,11;,
  3;11,11,11;,
  3;11,11,11;,
  3;11,11,11;,
  3;11,11,11;,
  3;11,11,11;,
  3;11,11,11;,
  4;13,14,14,13;,
  4;14,15,15,14;,
  4;15,16,16,15;,
  4;16,17,17,16;,
  4;17,18,18,17;,
  4;18,19,19,18;,
  4;19,20,20,19;,
  4;20,13,13,20;,
  3;12,22,23;,
  3;12,24,22;,
  3;12,25,24;,
  3;12,26,25;,
  3;12,27,26;,
  3;12,28,27;,
  3;12,29,28;,
  3;12,23,29;,
  3;21,30,31;,
  3;21,31,32;,
  3;21,32,33;,
  3;21,33,34;,
  3;21,34,35;,
  3;21,35,36;,
  3;21,36,37;,
  3;21,37,30;,
  4;39,40,40,39;,
  4;40,41,41,40;,
  4;41,42,42,41;,
  4;42,43,43,42;,
  4;43,44,44,43;,
  4;44,45,45,44;,
  4;45,46,46,45;,
  4;46,39,39,46;,
  3;38,38,38;,
  3;38,38,38;,
  3;38,38,38;,
  3;38,38,38;,
  3;38,38,38;,
  3;38,38,38;,
  3;38,38,38;,
  3;38,38,38;,
  3;47,47,47;,
  3;47,47,47;,
  3;47,47,47;,
  3;47,47,47;,
  3;47,47,47;,
  3;47,47,47;,
  3;47,47,47;,
  3;47,47,47;,
  4;49,50,50,49;,
  4;50,51,51,50;,
  4;51,52,52,51;,
  4;52,53,53,52;,
  4;53,54,54,53;,
  4;54,55,55,54;,
  4;55,56,56,55;,
  4;56,49,49,56;,
  3;48,48,48;,
  3;48,48,48;,
  3;48,48,48;,
  3;48,48,48;,
  3;48,48,48;,
  3;48,48,48;,
  3;48,48,48;,
  3;48,48,48;,
  3;57,57,57;,
  3;57,57,57;,
  3;57,57,57;,
  3;57,57,57;,
  3;57,57,57;,
  3;57,57,57;,
  3;57,57,57;,
  3;57,57,57;,
  4;59,60,60,59;,
  4;60,61,61,60;,
  4;61,62,62,61;,
  4;62,63,63,62;,
  4;63,64,64,63;,
  4;64,65,65,64;,
  4;65,66,66,65;,
  4;66,59,59,66;,
  3;58,68,69;,
  3;58,70,68;,
  3;58,71,70;,
  3;58,72,71;,
  3;58,73,72;,
  3;58,74,73;,
  3;58,75,74;,
  3;58,69,75;,
  3;67,76,77;,
  3;67,77,78;,
  3;67,78,79;,
  3;67,79,80;,
  3;67,80,81;,
  3;67,81,78;,
  3;67,78,82;,
  3;67,82,76;,
  4;84,85,85,84;,
  4;85,86,86,85;,
  4;86,87,87,86;,
  4;87,88,88,87;,
  4;88,89,89,88;,
  4;89,90,90,89;,
  4;90,91,91,90;,
  4;91,84,84,91;,
  3;83,93,94;,
  3;83,95,93;,
  3;83,96,95;,
  3;83,97,96;,
  3;83,98,97;,
  3;83,95,98;,
  3;83,99,95;,
  3;83,94,99;,
  3;92,100,101;,
  3;92,101,102;,
  3;92,102,103;,
  3;92,103,104;,
  3;92,104,105;,
  3;92,105,106;,
  3;92,106,107;,
  3;92,107,100;,
  4;109,110,110,109;,
  4;110,111,111,110;,
  4;111,112,112,111;,
  4;112,113,113,112;,
  4;113,114,114,113;,
  4;114,115,115,114;,
  4;115,116,116,115;,
  4;116,109,109,116;,
  3;108,118,119;,
  3;108,120,118;,
  3;108,121,120;,
  3;108,122,121;,
  3;108,123,122;,
  3;108,124,123;,
  3;108,125,124;,
  3;108,119,125;,
  3;117,126,127;,
  3;117,127,128;,
  3;117,128,129;,
  3;117,129,130;,
  3;117,130,131;,
  3;117,131,132;,
  3;117,132,133;,
  3;117,133,126;,
  4;134,134,134,134;,
  4;135,135,135,135;,
  4;136,136,136,136;,
  4;137,137,137,137;,
  4;138,138,138,138;,
  4;139,139,139,139;,
  4;140,140,140,140;,
  4;141,141,141,141;,
  4;142,142,142,142;,
  4;143,143,143,143;,
  4;144,144,144,144;,
  4;145,145,145,145;,
  4;146,146,146,146;,
  4;147,147,147,147;,
  4;148,148,148,148;,
  4;149,149,149,149;,
  4;150,150,150,150;,
  4;151,151,151,151;,
  4;152,152,152,152;,
  4;153,153,153,153;,
  4;154,154,154,154;,
  4;155,155,155,155;,
  4;156,156,156,156;,
  4;157,157,157,157;,
  4;158,158,158,158;,
  4;159,159,159,159;,
  4;160,160,160,160;,
  4;161,161,161,161;,
  4;162,162,162,162;,
  4;163,163,163,163;,
  4;164,164,164,164;,
  4;165,165,165,165;,
  4;166,166,166,166;,
  4;167,167,167,167;,
  4;168,168,168,168;,
  4;169,169,169,169;,
  4;170,170,170,170;,
  4;171,171,171,171;,
  4;172,172,172,172;,
  4;173,173,173,173;,
  4;174,174,174,174;,
  4;175,175,175,175;,
  4;176,176,176,176;,
  4;177,177,177,177;,
  4;178,178,178,178;,
  4;179,179,179,179;;
 }
 MeshTextureCoords {
  334;
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
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
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;;
 }
}
