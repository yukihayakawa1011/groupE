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
 138;
 103.10665;57.86081;-81.50734;,
 103.10665;57.86081;-103.10665;,
 103.10665;71.95293;-103.10665;,
 103.10665;71.95293;-81.50734;,
 -103.10665;71.95293;-103.10665;,
 -103.10665;57.86081;-103.10665;,
 -103.10665;57.86081;-81.50734;,
 -103.10665;71.95293;-81.50734;,
 -103.10665;71.95293;103.10665;,
 -103.10665;71.95293;79.98756;,
 -103.10665;57.86081;79.98756;,
 -103.10665;57.86081;103.10665;,
 103.10665;71.95293;103.10665;,
 103.10665;57.86081;103.10665;,
 103.10665;57.86081;79.98756;,
 103.10665;71.95293;79.98756;,
 103.10665;71.95293;-103.10665;,
 103.10665;57.86081;-103.10665;,
 77.90449;57.86081;-103.10665;,
 77.90449;71.95293;-103.10665;,
 103.10665;71.95293;-103.10665;,
 77.90449;71.95293;-103.10665;,
 77.90449;71.95293;-81.50734;,
 103.10665;71.95293;-81.50734;,
 77.90449;71.95293;79.98756;,
 103.10665;71.95293;79.98756;,
 77.90449;71.95293;103.10665;,
 103.10665;71.95293;103.10665;,
 77.90449;57.86081;103.10665;,
 103.10665;57.86081;103.10665;,
 103.10665;57.86081;79.98756;,
 77.90449;57.86081;79.98756;,
 77.90449;57.86081;-81.50734;,
 103.10665;57.86081;-81.50734;,
 77.90449;57.86081;-103.10665;,
 103.10665;57.86081;-103.10665;,
 -81.74148;57.86081;-103.10665;,
 -103.10665;57.86081;-103.10665;,
 -103.10665;71.95293;-103.10665;,
 -81.74148;71.95293;-103.10665;,
 -81.74148;71.95293;-81.50734;,
 -81.74148;71.95293;-103.10665;,
 -103.10665;71.95293;-103.10665;,
 -103.10665;71.95293;-81.50734;,
 -103.10665;71.95293;79.98756;,
 -81.74148;71.95293;79.98756;,
 -81.74148;71.95293;103.10665;,
 -81.74148;71.95293;103.10665;,
 -81.74148;57.86081;103.10665;,
 -103.10665;71.95293;103.10665;,
 -103.10665;57.86081;103.10665;,
 -81.74148;57.86081;103.10665;,
 -81.74148;57.86081;79.98756;,
 -103.10665;57.86081;79.98756;,
 -81.74148;57.86081;-81.50734;,
 -103.10665;57.86081;-81.50734;,
 -81.74148;57.86081;-103.10665;,
 -103.10665;57.86081;-103.10665;,
 -92.14116;59.97844;-87.80388;,
 -70.06508;59.97844;-87.80388;,
 -70.06508;0.01143;-87.80388;,
 -92.14116;0.01143;-87.80388;,
 -70.06508;59.97844;-87.80388;,
 -70.06508;59.97844;-65.94699;,
 -70.06508;0.01143;-65.94699;,
 -70.06508;0.01143;-87.80388;,
 -70.06508;59.97844;-65.94699;,
 -92.14116;59.97844;-65.94699;,
 -92.14116;0.01143;-65.94699;,
 -70.06508;0.01143;-65.94699;,
 -92.14116;59.97844;-65.94699;,
 -92.14116;59.97844;-87.80388;,
 -92.14116;0.01143;-87.80388;,
 -92.14116;0.01143;-65.94699;,
 -70.06508;59.97844;-87.80388;,
 -92.14116;59.97844;-87.80388;,
 -92.14116;0.01143;-87.80388;,
 -70.06508;0.01143;-87.80388;,
 69.99174;59.97844;-87.80388;,
 92.06782;59.97844;-87.80388;,
 92.06782;0.01143;-87.80388;,
 69.99174;0.01143;-87.80388;,
 92.06782;59.97844;-87.80388;,
 92.06782;59.97844;-65.94699;,
 92.06782;0.01143;-65.94699;,
 92.06782;0.01143;-87.80388;,
 92.06782;59.97844;-65.94699;,
 69.99174;59.97844;-65.94699;,
 69.99174;0.01143;-65.94699;,
 92.06782;0.01143;-65.94699;,
 69.99174;59.97844;-65.94699;,
 69.99174;59.97844;-87.80388;,
 69.99174;0.01143;-87.80388;,
 69.99174;0.01143;-65.94699;,
 92.06782;59.97844;-87.80388;,
 69.99174;59.97844;-87.80388;,
 69.99174;0.01143;-87.80388;,
 92.06782;0.01143;-87.80388;,
 69.99174;59.97844;68.48310;,
 92.06782;59.97844;68.48310;,
 92.06782;0.01143;68.48310;,
 69.99174;0.01143;68.48310;,
 92.06782;59.97844;68.48310;,
 92.06782;59.97844;90.34008;,
 92.06782;0.01143;90.34008;,
 92.06782;0.01143;68.48310;,
 92.06782;59.97844;90.34008;,
 69.99174;59.97844;90.34008;,
 69.99174;0.01143;90.34008;,
 92.06782;0.01143;90.34008;,
 69.99174;59.97844;90.34008;,
 69.99174;59.97844;68.48310;,
 69.99174;0.01143;68.48310;,
 69.99174;0.01143;90.34008;,
 92.06782;59.97844;68.48310;,
 69.99174;59.97844;68.48310;,
 69.99174;0.01143;68.48310;,
 92.06782;0.01143;68.48310;,
 -92.83506;59.97844;68.48310;,
 -70.75898;59.97844;68.48310;,
 -70.75898;0.01143;68.48310;,
 -92.83506;0.01143;68.48310;,
 -70.75898;59.97844;68.48310;,
 -70.75898;59.97844;90.34008;,
 -70.75898;0.01143;90.34008;,
 -70.75898;0.01143;68.48310;,
 -70.75898;59.97844;90.34008;,
 -92.83506;59.97844;90.34008;,
 -92.83506;0.01143;90.34008;,
 -70.75898;0.01143;90.34008;,
 -92.83506;59.97844;90.34008;,
 -92.83506;59.97844;68.48310;,
 -92.83506;0.01143;68.48310;,
 -92.83506;0.01143;90.34008;,
 -70.75898;59.97844;68.48310;,
 -92.83506;59.97844;68.48310;,
 -92.83506;0.01143;68.48310;,
 -70.75898;0.01143;68.48310;;
 
 54;
 4;0,1,2,3;,
 4;4,5,6,7;,
 4;8,9,10,11;,
 4;7,6,10,9;,
 4;12,13,14,15;,
 4;3,15,14,0;,
 4;16,17,18,19;,
 4;20,21,22,23;,
 4;24,25,23,22;,
 4;26,12,25,24;,
 4;27,26,28,29;,
 4;30,31,32,33;,
 4;31,30,13,28;,
 4;33,32,34,35;,
 4;36,37,38,39;,
 4;40,41,42,43;,
 4;40,22,21,41;,
 4;36,39,19,18;,
 4;43,44,45,40;,
 4;22,40,45,24;,
 4;46,45,44,8;,
 4;24,45,46,26;,
 4;26,47,48,28;,
 4;48,47,49,50;,
 4;28,51,52,31;,
 4;11,53,52,51;,
 4;54,32,31,52;,
 4;54,52,53,55;,
 4;32,54,56,34;,
 4;56,54,55,57;,
 4;58,59,60,61;,
 4;62,63,64,65;,
 4;66,67,68,69;,
 4;70,71,72,73;,
 4;70,63,74,75;,
 4;76,77,64,73;,
 4;78,79,80,81;,
 4;82,83,84,85;,
 4;86,87,88,89;,
 4;90,91,92,93;,
 4;90,83,94,95;,
 4;96,97,84,93;,
 4;98,99,100,101;,
 4;102,103,104,105;,
 4;106,107,108,109;,
 4;110,111,112,113;,
 4;110,103,114,115;,
 4;116,117,104,113;,
 4;118,119,120,121;,
 4;122,123,124,125;,
 4;126,127,128,129;,
 4;130,131,132,133;,
 4;130,123,134,135;,
 4;136,137,124,133;;
 
 MeshMaterialList {
  2;
  54;
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
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
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
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
   0.432800;0.235200;0.056800;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
  Material {
   0.586400;0.398400;0.241600;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
 }
 MeshNormals {
  30;
  -1.000000;0.000000;0.000000;,
  1.000000;0.000000;0.000000;,
  0.000000;0.000000;-1.000000;,
  0.000000;1.000000;0.000000;,
  0.000000;0.000000;1.000000;,
  0.000000;-1.000000;-0.000000;,
  0.000000;0.000000;-1.000000;,
  1.000000;0.000000;0.000000;,
  0.000000;0.000000;1.000000;,
  -1.000000;0.000000;0.000000;,
  0.000000;1.000000;0.000000;,
  0.000000;-1.000000;-0.000000;,
  0.000000;0.000000;-1.000000;,
  1.000000;0.000000;0.000000;,
  0.000000;0.000000;1.000000;,
  -1.000000;0.000000;0.000000;,
  0.000000;1.000000;0.000000;,
  0.000000;-1.000000;-0.000000;,
  0.000000;0.000000;-1.000000;,
  1.000000;0.000000;0.000000;,
  0.000000;0.000000;1.000000;,
  -1.000000;0.000000;0.000000;,
  0.000000;1.000000;0.000000;,
  0.000000;-1.000000;-0.000000;,
  0.000000;0.000000;-1.000000;,
  1.000000;0.000000;0.000000;,
  0.000000;0.000000;1.000000;,
  -1.000000;0.000000;0.000000;,
  0.000000;1.000000;0.000000;,
  0.000000;-1.000000;-0.000000;;
  54;
  4;1,1,1,1;,
  4;0,0,0,0;,
  4;0,0,0,0;,
  4;0,0,0,0;,
  4;1,1,1,1;,
  4;1,1,1,1;,
  4;2,2,2,2;,
  4;3,3,3,3;,
  4;3,3,3,3;,
  4;3,3,3,3;,
  4;4,4,4,4;,
  4;5,5,5,5;,
  4;5,5,5,5;,
  4;5,5,5,5;,
  4;2,2,2,2;,
  4;3,3,3,3;,
  4;3,3,3,3;,
  4;2,2,2,2;,
  4;3,3,3,3;,
  4;3,3,3,3;,
  4;3,3,3,3;,
  4;3,3,3,3;,
  4;4,4,4,4;,
  4;4,4,4,4;,
  4;5,5,5,5;,
  4;5,5,5,5;,
  4;5,5,5,5;,
  4;5,5,5,5;,
  4;5,5,5,5;,
  4;5,5,5,5;,
  4;6,6,6,6;,
  4;7,7,7,7;,
  4;8,8,8,8;,
  4;9,9,9,9;,
  4;10,10,10,10;,
  4;11,11,11,11;,
  4;12,12,12,12;,
  4;13,13,13,13;,
  4;14,14,14,14;,
  4;15,15,15,15;,
  4;16,16,16,16;,
  4;17,17,17,17;,
  4;18,18,18,18;,
  4;19,19,19,19;,
  4;20,20,20,20;,
  4;21,21,21,21;,
  4;22,22,22,22;,
  4;23,23,23,23;,
  4;24,24,24,24;,
  4;25,25,25,25;,
  4;26,26,26,26;,
  4;27,27,27,27;,
  4;28,28,28,28;,
  4;29,29,29,29;;
 }
 MeshTextureCoords {
  138;
  0.500000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  0.500000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.500000;1.000000;,
  0.500000;0.000000;,
  0.000000;0.000000;,
  0.250000;0.000000;,
  0.250000;1.000000;,
  0.000000;1.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.750000;1.000000;,
  0.750000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.500000;1.000000;,
  0.500000;0.000000;,
  1.000000;1.000000;,
  0.500000;1.000000;,
  0.500000;0.500000;,
  1.000000;0.500000;,
  0.500000;0.250000;,
  1.000000;0.250000;,
  0.500000;0.000000;,
  0.000000;0.000000;,
  0.500000;1.000000;,
  0.000000;1.000000;,
  1.000000;0.750000;,
  0.500000;0.750000;,
  0.500000;0.500000;,
  1.000000;0.500000;,
  0.500000;0.000000;,
  1.000000;0.000000;,
  0.250000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  0.250000;0.000000;,
  0.250000;0.500000;,
  0.250000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.500000;,
  0.000000;0.250000;,
  0.250000;0.250000;,
  0.250000;0.000000;,
  0.750000;0.000000;,
  0.750000;1.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.250000;1.000000;,
  0.250000;0.750000;,
  0.000000;0.750000;,
  0.250000;0.500000;,
  0.000000;0.500000;,
  0.250000;0.000000;,
  0.000000;0.000000;,
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
  1.000000;0.000000;;
 }
}
