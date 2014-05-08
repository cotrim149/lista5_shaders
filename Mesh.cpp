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
	face Face = malha->list_faces[0];
	
	ponto3D ponto1 = Face.verticeX; 
	ponto3D ponto2 = Face.verticeY;
	ponto3D ponto3 = Face.verticeZ;
	
	printf("ponto1 X: %f\n",ponto1.x);
	printf("ponto1 Y: %f\n",ponto1.y);
	printf("ponto1 Z: %f\n\n",ponto1.z);

	printf("ponto2 X: %f\n",ponto2.x);
	printf("ponto2 Y: %f\n",ponto2.y);
	printf("ponto2 Z: %f\n\n",ponto2.z);

	printf("ponto3 X: %f\n",ponto3.x);
	printf("ponto3 Y: %f\n",ponto3.y);
	printf("ponto3 Z: %f\n\n",ponto3.z);


	// vetores u e v	
	ponto3D u; 
	u.x = ponto1.x - ponto2.x;
	u.y = ponto1.y - ponto2.y;
	u.z = ponto1.z - ponto2.z;

	printf("vetor u X: %f\n",u.x);
	printf("vetor u Y: %f\n",u.y);
	printf("vetor u Z: %f\n\n",u.z);
	

	ponto3D v;
	v.x = ponto1.x- ponto3.x;
	v.y = ponto1.y- ponto3.y;
	v.z = ponto1.z- ponto3.z;

	printf("vetor v X: %f\n",v.x);
	printf("vetor v Y: %f\n",v.y);
	printf("vetor v Z: %f\n\n",v.z);
	
	// produto Vetorial u x v
	ponto3D normal;
	normal.x = (u.y * v.z) - (u.z * v.y);
    normal.y = (u.z * v.x) - (u.x * v.z);
    normal.z = (u.x * v.y) - (u.y * v.x);
	
	printf("u x v X: %f\n",normal.x);
	printf("u x v Y: %f\n",normal.y);
	printf("u x v Z: %f\n\n",normal.z);

	// Normalizacao
	float norma = sqrt(pow(normal.x,2) + pow(normal.y,2) +pow(normal.z,2));
	printf("Norma: %f\n\n",norma);
	
	normal.x = normal.x/norma;
	normal.y = normal.y/norma;
	normal.z = normal.z/norma;

	printf("Normal X: %f\n",normal.x);
	printf("Normal Y: %f\n",normal.y);
	printf("Normal Z: %f\n\n",normal.z);
	
	
	
}

