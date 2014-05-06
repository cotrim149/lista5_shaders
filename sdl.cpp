#include <SDL/SDL.h>


static void handle_key_down( SDL_keysym* keysym )
{
	
    switch( keysym->sym ) {
		case SDLK_ESCAPE:
			SDL_Quit( );
			exit( 0 );
			break;
		case SDLK_SPACE:
			break;
		default:
			break;
    }
	
}

static void processEvents( void )
{
    SDL_Event event;

    while( SDL_PollEvent( &event ) ) {
		
		switch( event.type ) {
			case SDL_KEYDOWN:
				handle_key_down( &event.key.keysym );
				break;
			case SDL_QUIT:
				SDL_Quit( );
				exit( 0 );
				break;
        }
		
    }	
}

void initialize_color_and_doble_buffer(){
    SDL_GL_SetAttribute(SDL_GL_RED_SIZE, 5);
    SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE, 5);
    SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE, 5);
    SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 16);
    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);

}

int initializeScreen(int width, int height){
	
	int bpp = 16;
	int flags = SDL_DOUBLEBUF | SDL_OPENGL;

    if (SDL_Init(SDL_INIT_VIDEO) < 0){
        fprintf(stderr, "Erro na inicializacao da SDL: %s\n", SDL_GetError());
		return -1;
    }
    else{
    printf("INICIALIZACAO DE SDL ... OK");
    }
    initialize_color_and_doble_buffer();
    
    atexit(SDL_Quit);

    if (SDL_SetVideoMode(width, height, bpp, flags) == 0){
        fprintf(stderr, "Erro na inicializacao do video: %s\n", SDL_GetError());
		exit(-2);
    }

	return 0;
}

void swapBuffer(){
	SDL_GL_SwapBuffers();
}	

