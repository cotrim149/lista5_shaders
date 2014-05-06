#ifndef CG_H
#define CG_h
#include <stdio.h>
#include <GL/gl.h>
#include <GL/glu.h>

enum ViewPortMode
{
    VIEWPORT_MODE_HALF,
    VIEWPORT_MODE_FULL
};

enum geometricForm{
	LINES,
	TRIANGLES,
	SQUARE
};

void initializeOpenGl(int SCREEN_WIDTH, int SCREEN_HEIGHT);
void Open_Viewport(int geometric);
#endif
