#include <iostream>

#include "CG.h"
#include "Mesh.h"
#include "sdl.cpp"

int main(){
	
	initializeScreen(SCREEN_WIDTH,SCREEN_HEIGHT);
	initializeOpenGl(SCREEN_WIDTH,SCREEN_HEIGHT);

	mesh *malha = NULL;
	malha = New_Mesh();
	
	mesh malha2;
	malha2 = Load_Mesh(malha,"bun_zipper.off");
	malha = &malha2;

	calculaDeltas(malha);
	Resize_Mesh(malha,3);
	centralizaMesh(malha);
	while(1){
	
		processEvents();
		Render_Mesh(malha,TRIANGLES);
		SDL_Delay(500);
	}

	Del_Mesh(malha);	

	return 0;
}

