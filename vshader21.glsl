attribute vec4 vPosition;
uniform float gScale;

void
main()
{
    gl_Position = vec4(gScale * vPosition.x, gScale * vPosition.y, gScale * vPosition.z, 1.0);
}
