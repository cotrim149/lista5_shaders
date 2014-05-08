#include "Mesh.h"
#include <string.h>

float verificaMaior(float valorMalha, float valor){
	if(valor > valorMalha){
		return valor;
	}
	
	return valorMalha;
}

float verificaMenor(float valorMalha, float valor){
	if(valor < valorMalha){
		return valor;
	}
	
	return valorMalha;
}

mesh lerArquivo(char *nomeArquivo){
	
	FILE *arq = fopen(nomeArquivo,"r+");
	
	if(arq == NULL){
		printf("\nERRO AO ABRIR ARQUIVO! \n");
		//return NULL;
	}
	
	int i;
	char cabecalho[5];
	fscanf(arq,"%s\n",&cabecalho);
	int qtdPontos, qtdFaces, textura;
	
	
	fscanf(arq,"%d %d %d\n",&qtdPontos,&qtdFaces,&textura);
	
	if(strcmp(cabecalho,"OFF") == 0 ){

		mesh malha;
		malha.nvertex = qtdPontos;
		malha.nface = qtdFaces;
		malha.XMax = 0;
		malha.XMin = 1;
		malha.YMax = 0;
		malha.YMin = 1;
		malha.ZMax = 0;
		malha.ZMin = 1;

		int conta;
		float x,y,z;

		for(i=0;i<qtdPontos;i++){
	
			ponto3D pontos;
			fscanf(arq,"%f %f %f\n",&x,&y,&z);
	
			malha.XMax=verificaMaior(malha.XMax,x);
			malha.XMin=verificaMenor(malha.XMin,x);		

			malha.YMax=verificaMaior(malha.YMax,y);
			malha.YMin=verificaMenor(malha.YMin,y);		

			malha.ZMax=verificaMaior(malha.ZMax,z);
			malha.ZMin=verificaMenor(malha.ZMin,z);		
	
			pontos.x=x;
			pontos.y=y;
			pontos.z=z;
	
			malha.list_vertex.push_back(pontos);
		}	

		printf("\n Escaneamento dos pontos feita com sucesso!\n");
		int tri;
		for(i=0;i<qtdFaces;i++){
			face Face;
	
			fscanf(arq,"%d %d %d %d\n",&tri,&Face.ponto1,&Face.ponto2,&Face.ponto3);
	
			Face.verticeX= malha.list_vertex[Face.ponto1];
			Face.verticeY= malha.list_vertex[Face.ponto2];
			Face.verticeZ= malha.list_vertex[Face.ponto3];
	
			malha.list_faces.push_back(Face);
		}
		printf("\n Escaneamento das faces feita com sucesso!\n");
	
		fclose(arq);
	
		return malha;

		
	}else{
	
		printf("cacalho: %s\n",cabecalho);
	
		mesh malha;
		malha.nvertex = qtdPontos;
		malha.nface = qtdFaces;
		malha.ncolor = qtdPontos;
		malha.XMax = 0;
		malha.XMin = 1;
		malha.YMax = 0;
		malha.YMin = 1;
		malha.ZMax = 0;
		malha.ZMin = 1;

		
		int conta;
		int red,green,blue,alpha;
		float x,y,z;

		for(i=0;i<qtdPontos;i++){
	
			color cores;
			ponto3D pontos;
	
			fscanf(arq,"%f %f %f %d %d %d %d\n",&x,&y,&z,&red,&green,&blue,&alpha);
	
			malha.XMax=verificaMaior(malha.XMax,x);
			malha.XMin=verificaMenor(malha.XMin,x);		

			malha.YMax=verificaMaior(malha.YMax,y);
			malha.YMin=verificaMenor(malha.YMin,y);		

			malha.ZMax=verificaMaior(malha.ZMax,z);
			malha.ZMin=verificaMenor(malha.ZMin,z);		
	
			cores.R = red;
			cores.G = green;
			cores.B = blue;
			cores.alpha = alpha;
	
			pontos.x=x;
			pontos.y=y;
			pontos.z=z;
	
			malha.list_color.push_back(cores);
			malha.list_vertex.push_back(pontos);
		}	

		printf("\n scan dos pontos feita com sucesso!\n");
		int tri;
		for(i=0;i<qtdFaces;i++){
			face Face;
	
			fscanf(arq,"%d %d %d %d\n",&tri,&Face.ponto1,&Face.ponto2,&Face.ponto3);
	
			Face.verticeX= malha.list_vertex[Face.ponto1];
			Face.verticeY= malha.list_vertex[Face.ponto2];
			Face.verticeZ= malha.list_vertex[Face.ponto3];
	
			malha.list_faces.push_back(Face);
		}
		printf("\n scan das faces feita com sucesso!\n");
	
		fclose(arq);
	
		return malha;
	
	}
	mesh m;
	return m;
	
}
