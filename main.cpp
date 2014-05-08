#include <iostream>

#include "InitShader.h"
#include "CG.h"
#include "Mesh.h"
#include "sdl.cpp"

GLuint VBO;

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


static void RenderSceneCB(mesh *malha)
{

    glClear(GL_COLOR_BUFFER_BIT);

    gScale = 0.50f;
    glUniform1f(gScaleLocation, gScale);
 
    int i;
    glEnableVertexAttribArray(0);

	    for(i=0;i< malha->nface;i+=3){

		    glBindBuffer(GL_ARRAY_BUFFER, VBO);
	    	glVertexAttribPointer(i, i+3, GL_FLOAT, GL_FALSE, 0, NULL);

	    	glDrawArrays(GL_TRIANGLES, i, i+3);	    
	    }

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

 	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(Faces), Faces, GL_STATIC_DRAW);
	
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
	
	CreateVertexBuffer(malha);
	calculaNormal(malha);
	
	while(1){
	
		processEvents();
			RenderSceneCB(malha);
		SDL_Delay(1);
	}

	Del_Mesh(malha);	

	return 0;
}

