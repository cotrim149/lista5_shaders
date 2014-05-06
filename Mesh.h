/*
 *mesh.h
 */

#ifndef MESH_H_
#define MESH_H_
#include <stdio.h>
#include <stdlib.h>
#include <vector>
#include "vec.h"

using namespace std;

typedef struct _face{
    int ponto1,ponto2,ponto3;
    ponto3D verticeX,verticeY,verticeZ;
}face;

typedef struct _color{
	int R,G,B;
	int alpha;
}color;

typedef struct _mesh{
    vector<ponto3D> list_vertex;
    vector<face> list_faces;
    vector<color> list_color;
    int nvertex;
    int nface;
    int ncolor;
    float XMax, XMin, YMax, YMin, ZMax, ZMin;
    float deltaX, deltaY,deltaZ;
}mesh;

mesh *New_Mesh();
int Del_Mesh(mesh *pmesh);
mesh Load_Mesh(mesh *pmesh, char *File_Name);
int Render_Mesh(mesh *pmesh, int geometric);
int Resize_Mesh(mesh *pmesh, float ampliacao);

void repassaPontosListFaces(mesh *pmesh);
void calculaDeltas(mesh *malha);
void centralizaMesh(mesh *malha);

#endif
