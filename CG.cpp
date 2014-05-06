#include "CG.h"
#include "vec.h"

int gViewportMode = VIEWPORT_MODE_HALF;

void initializeOpenGl(int SCREEN_WIDTH, int SCREEN_HEIGHT){
	glClearColor(0, 0, 0, 0);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glViewport( 0.f, 0.f, SCREEN_WIDTH, SCREEN_HEIGHT );

    GLenum error = glGetError();
    if( error != GL_NO_ERROR )
    {
        printf( "Error initializing OpenGL! %s\n", gluErrorString( error ) );
        return;
    }
    else
	    printf("\nINICIALIZAÇÃO DO OPENGL ... OK\n");
}

void Open_Viewport(int geometric){

	
 
    if( gViewportMode == VIEWPORT_MODE_FULL )
    {

         //Fill the screen
        glViewport( 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT );

        //ViewPort da esquerda
        glBegin( GL_QUADS );
            glColor3f( 0.f, 0.f, 0.f );
            glVertex2f( -SCREEN_WIDTH / 4.f, -SCREEN_HEIGHT / 4.f );
            glVertex2f(  SCREEN_WIDTH / 4.f, -SCREEN_HEIGHT / 4.f );
            glVertex2f(  SCREEN_WIDTH / 4.f,  SCREEN_HEIGHT / 4.f );
            glVertex2f( -SCREEN_WIDTH / 4.f,  SCREEN_HEIGHT / 4.f );
        glEnd();
 
    } else if(gViewportMode == VIEWPORT_MODE_HALF){

		if(geometric == LINES){
		    //Fill the screen
		    glViewport( 0, 0, SCREEN_WIDTH/2, SCREEN_HEIGHT );

		    //ViewPort da esquerda
		    glBegin( GL_QUADS );
		        glColor3f( 0.f, 0.f, 0.f );
		        glVertex2f( -SCREEN_WIDTH / 4.f, -SCREEN_HEIGHT / 4.f );
		        glVertex2f(  SCREEN_WIDTH / 4.f, -SCREEN_HEIGHT / 4.f );
		        glVertex2f(  SCREEN_WIDTH / 4.f,  SCREEN_HEIGHT / 4.f );
		        glVertex2f( -SCREEN_WIDTH / 4.f,  SCREEN_HEIGHT / 4.f );
		    glEnd();
		
		}

		if(geometric == TRIANGLES){
		    //Fill the screen
		    glViewport( SCREEN_WIDTH/2, 0, SCREEN_WIDTH/2, SCREEN_HEIGHT );

		    //ViewPort da direita
		    glBegin( GL_QUADS );
		        glColor3f( 0.f, 0.f, 0.f );
		        glVertex2f( -SCREEN_WIDTH / 4.f, -SCREEN_HEIGHT / 4.f );
		        glVertex2f(  SCREEN_WIDTH / 4.f, -SCREEN_HEIGHT / 4.f );
		        glVertex2f(  SCREEN_WIDTH / 4.f,  SCREEN_HEIGHT / 4.f );
		        glVertex2f( -SCREEN_WIDTH / 4.f,  SCREEN_HEIGHT / 4.f );
		    glEnd();
		
		}       
    
    }	

}

