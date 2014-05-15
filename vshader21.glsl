#version 330

in vec3 vPosition;
uniform float gScale;

void
main()
{
    gl_Position = vec4(vPosition, 1.0);

}
