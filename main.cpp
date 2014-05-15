#include <iostream>

#include "InitShader.h"
#include "CG.h"
#include "Mesh.h"
#include "sdl.cpp"

GLuint idVertices;
GLuint idCores;

static float gScale = 0.0f;
int gScaleLocation;

struct Vector3f
{
    float x;
    float y;
    float z;

    Vector3f()
    {
    }

    Vector3f(float _x, float _y, float _z)
    {
        x = _x;
        y = _y;
        z = _z;
    }
};

struct Vector4f
{
    float r;
    float g;
    float b;
	float alpha;
	
    Vector4f()
    {
    }

    Vector4f(float _r, float _g, float _b, float _alpha)
    {
        r = _r;
        g = _g;
        b = _b;
        alpha = _alpha;
    }
};


static void RenderSceneCB(mesh *malha)
{

    glClear(GL_COLOR_BUFFER_BIT);

    gScale = 0.90f;
    glUniform1f(gScaleLocation, gScale);
 
    int numTriangulos = malha->nface;
    glEnableVertexAttribArray(0);
 

	    glBindBuffer(GL_ARRAY_BUFFER, idVertices);
    	
    	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, NULL);
//	    	glVertexAttribPointer(id do atributteArray(index de quem eu trabalho), tamanho da lista, tipo, normalizado ou não, tamanho estrutura de dados(tamanho do pacote), ponteiro);
		
    	glDrawArrays(GL_TRIANGLES, 0,numTriangulos);	    
		
    glDisableVertexAttribArray(0);
	
    SDL_GL_SwapBuffers();
}

static void CreateVertexBuffer(mesh *malha)
{
	printf("iniciou criacao de vertex \n");
   	Vector3f Faces[malha->nface];
   	int i;
   	
   	for(i=0;i< malha->nface;i+=3){
	  	face Face = malha->list_faces[i];
	    Faces[i] = Vector3f(Face.verticeX.x, Face.verticeX.y, Face.verticeX.z);
	    Faces[i+1] = Vector3f(Face.verticeY.x, Face.verticeY.y, Face.verticeY.z);
	    Faces[i+2] = Vector3f(Face.verticeZ.x, Face.verticeZ.y, Face.verticeZ.z);
   	}

	

 	glGenBuffers(1, &idVertices);
	glBindBuffer(GL_ARRAY_BUFFER, idVertices);
	glBufferData(GL_ARRAY_BUFFER, sizeof(Vector3f)*malha->nface, Faces, GL_STATIC_DRAW);


	
	printf("Terminou criacao de vertex \n");
}

//----------------------------------------------------------------------------
void Display_InitGL()
{
    GLuint program = InitShader( "vshader21.glsl", "fshader21.glsl" );
    glUseProgram( program );					   
    glClearColor( 0.0, 0, 0, 0.0 ); // black background
    gScaleLocation = glGetUniformLocation(program,"gScale");// map
 }

int main(){
	
	initializeScreen(SCREEN_WIDTH,SCREEN_HEIGHT);
	initializeOpenGl(SCREEN_WIDTH,SCREEN_HEIGHT);
   
	glewInit();
	if (glewIsSupported("GL_VERSION_3_0"))
		printf("Ready for OpenGL 3.3\n");
	else {
		printf("OpenGL 3.3 not supported\n");
		exit(1);
	}
	printf("Versao OpenGL: %s\n\n", glGetString(GL_SHADING_LANGUAGE_VERSION));

	Display_InitGL();


	mesh *malha = NULL;
	malha = New_Mesh();
	
	mesh malha2;
	malha2 = Load_Mesh(malha,"bun_zipper.off");
	malha = &malha2;

	calculaDeltas(malha);
	Resize_Mesh(malha,1.6);
	centralizaMesh(malha);
	calculaNormal(malha);
	CreateVertexBuffer(malha);

	
	
	
	while(1){
	
		processEvents();
		RenderSceneCB(malha);

		SDL_Delay(1000);
	}

	Del_Mesh(malha);	

	return 0;
}

