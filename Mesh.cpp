#include "Mesh.h"
#include "arquivo.cpp"
#include "CG.h"
#include <SDL/SDL.h>

mesh *New_Mesh(){
	mesh *malha = (mesh *)malloc(sizeof(mesh));
	return malha;
}

int Del_Mesh(mesh *pmesh){
	free(pmesh);
	
	if(pmesh == NULL){
		printf("\n ERRO ao desalocar mesh! ... NOT NULL ");
		return -1;
	}
	return 0;
}

mesh Load_Mesh(mesh *pMesh, char *File_Name){
	
	mesh malha = lerArquivo(File_Name);
	pMesh = &malha;	
	if(pMesh == NULL){
		printf("\n ERRO com mesh! ... NULL");
		//return NULL;
	}
		
	return malha;
}

int Render_Mesh(mesh *pmesh,int geometric){

	if(pmesh == NULL){
		printf("malha nula!\n");
	}

			
	int i;
	
	if(pmesh->list_color.size() == 0){

		Open_Viewport(TRIANGLES);

		for(i=0;i<pmesh->list_faces.size();i++){
			face Face = pmesh->list_faces[i];
			glBegin(GL_TRIANGLES);
				glColor4f(1,1,1,0);
				glVertex3f(Face.verticeX.x,Face.verticeX.y,Face.verticeX.z);
			
				glColor4f(1,1,1,0);
				glVertex3f(Face.verticeX.x,Face.verticeX.y,Face.verticeX.z);
			
				glColor4f(1,1,1,0);
				glVertex3f(Face.verticeX.x,Face.verticeX.y,Face.verticeX.z);
			glEnd();
		}	
		
		Open_Viewport(LINES);

		for(i=0;i<pmesh->list_faces.size();i++){
			face Face = pmesh->list_faces[i];
			glBegin(GL_LINES);
				glColor4f(1,1,1,0.5);
				glVertex3f(Face.verticeX.x,Face.verticeX.y,Face.verticeX.z);			
				glColor4f(1,1,1,0.5);
				glVertex3f(Face.verticeY.x,Face.verticeY.y,Face.verticeY.z);

				glColor4f(1,1,1,0.5);
				glVertex3f(Face.verticeY.x,Face.verticeY.y,Face.verticeY.z);
				glColor4f(1,1,1,0.5);
				glVertex3f(Face.verticeZ.x,Face.verticeZ.y,Face.verticeZ.z);			

				glColor4f(1,1,1,0.5);
				glVertex3f(Face.verticeX.x,Face.verticeX.y,Face.verticeX.z);
				glColor4f(1,1,1,0.5);
				glVertex3f(Face.verticeZ.x,Face.verticeZ.y,Face.verticeZ.z);			

			glEnd();
		
		}
	} else {
		
		Open_Viewport(TRIANGLES);

		for(i=0;i<pmesh->list_faces.size();i++){
			face Face = pmesh->list_faces[i];
			color corPonto1 = pmesh->list_color[Face.ponto1];
			color corPonto2 = pmesh->list_color[Face.ponto2];
			color corPonto3 = pmesh->list_color[Face.ponto3];
			glBegin(GL_TRIANGLES);
				glColor4f(corPonto1.R,corPonto1.G,corPonto1.B,corPonto1.alpha);
				glVertex3f(Face.verticeX.x,Face.verticeX.y,Face.verticeX.z);

				glColor4f(corPonto2.R,corPonto2.G,corPonto2.B,corPonto2.alpha);
				glVertex3f(Face.verticeY.x,Face.verticeY.y,Face.verticeY.z);
			
				glColor4f(corPonto3.R,corPonto3.G,corPonto3.B,corPonto3.alpha);		
				glVertex3f(Face.verticeZ.x,Face.verticeZ.y,Face.verticeZ.z);
			glEnd();
		}	
		
		Open_Viewport(LINES);
	
		for(i=0;i<pmesh->list_faces.size();i++){
			face Face = pmesh->list_faces[i];
			color corPonto1 = pmesh->list_color[Face.ponto1];
			color corPonto2 = pmesh->list_color[Face.ponto2];
			color corPonto3 = pmesh->list_color[Face.ponto3];

			glBegin(GL_LINES);
				glColor4f(corPonto1.R,corPonto1.G,corPonto1.B,corPonto1.alpha);
				glVertex3f(Face.verticeX.x,Face.verticeX.y,Face.verticeX.z);			
				glColor4f(corPonto2.R,corPonto2.G,corPonto2.B,corPonto2.alpha);
				glVertex3f(Face.verticeY.x,Face.verticeY.y,Face.verticeY.z);

				glColor4f(corPonto2.R,corPonto2.G,corPonto2.B,corPonto2.alpha);
				glVertex3f(Face.verticeY.x,Face.verticeY.y,Face.verticeY.z);
				glColor4f(corPonto3.R,corPonto3.G,corPonto3.B,corPonto3.alpha);		
				glVertex3f(Face.verticeZ.x,Face.verticeZ.y,Face.verticeZ.z);			

				glColor4f(corPonto1.R,corPonto1.G,corPonto1.B,corPonto1.alpha);
				glVertex3f(Face.verticeX.x,Face.verticeX.y,Face.verticeX.z);
				glColor4f(corPonto3.R,corPonto3.G,corPonto3.B,corPonto3.alpha);		
				glVertex3f(Face.verticeZ.x,Face.verticeZ.y,Face.verticeZ.z);			

			glEnd();
		
		}	
		
		
	}	
	
		
	SDL_GL_SwapBuffers();
	
	
	return 0;
}

int Resize_Mesh(mesh *pmesh, float ampliacao){
	int i;

	for(i=0;i < pmesh->list_vertex.size();i++){
	
		pmesh->list_vertex[i].x = (pmesh->list_vertex[i].x/pmesh->deltaX) * ampliacao; 
		pmesh->list_vertex[i].y = (pmesh->list_vertex[i].y/pmesh->deltaY) * ampliacao; 
		pmesh->list_vertex[i].z = (pmesh->list_vertex[i].z/pmesh->deltaZ) * ampliacao;	
				
	}
	
	repassaPontosListFaces(pmesh);
	return 0;
}

void repassaPontosListFaces(mesh *pmesh){
	int i;
	for(i=0;i < pmesh->list_faces.size();i++){
		pmesh->list_faces[i].verticeX = pmesh->list_vertex[pmesh->list_faces[i].ponto1];
		pmesh->list_faces[i].verticeY = pmesh->list_vertex[pmesh->list_faces[i].ponto2];
		pmesh->list_faces[i].verticeZ = pmesh->list_vertex[pmesh->list_faces[i].ponto3];
	}	

}

void calculaDeltas(mesh *malha){
	malha->deltaX = malha->XMax - malha->XMin;
	malha->deltaY = malha->YMax - malha->YMin;
	malha->deltaZ = malha->ZMax - malha->ZMin;
	
}

void centralizaMesh(mesh *malha){
	float xCentral = malha->XMin + (malha->deltaX);
	float yCentral = malha->YMin + (malha->deltaY);
	float zCentral = malha->ZMin + (malha->deltaZ);
	

	int i;
	for(i=0;i<malha->list_vertex.size();i++){
		malha->list_vertex[i].x -= xCentral; 
		malha->list_vertex[i].y -= yCentral; 
		malha->list_vertex[i].z -= zCentral; 
	}
	
	repassaPontosListFaces(malha);
}

void calculaNormal(mesh *malha){
	
	
	int i;
	for(i =0; i< malha->nface;i++){
		face Face = malha->list_faces[i];
	
		ponto3D ponto1 = Face.verticeX; 
		ponto3D ponto2 = Face.verticeY;
		ponto3D ponto3 = Face.verticeZ;

		// vetores u e v	
		ponto3D u; 
		u.x = ponto1.x - ponto2.x;
		u.y = ponto1.y - ponto2.y;
		u.z = ponto1.z - ponto2.z;
	
		ponto3D v;
		v.x = ponto1.x- ponto3.x;
		v.y = ponto1.y- ponto3.y;
		v.z = ponto1.z- ponto3.z;

		// produto Vetorial u x v
		ponto3D normal;
		normal.x = (u.y * v.z) - (u.z * v.y);
		normal.y = (u.z * v.x) - (u.x * v.z);
		normal.z = (u.x * v.y) - (u.y * v.x);
	
		// Normalizacao
		float norma = sqrt(pow(normal.x,2) + pow(normal.y,2) +pow(normal.z,2));
	
		Face.normal.x = normal.x/norma;
		Face.normal.y = normal.y/norma;
		Face.normal.z = normal.z/norma;

		printf("Normal X: %f\n",normal.x);
		printf("Normal Y: %f\n",normal.y);
		printf("Normal Z: %f\n\n",normal.z);
	
	}
	
	
	
	
}

