#version 430

in vec2 in_vert;
out vec4 vertcolor;
void main()
{
    gl_Position = vec4(in_vert, .0, 1.0);
    if(in_vert.x >= 0 && in_vert.y >= 0)
        vertcolor = vec4(.5, .5, .5, 1.0);
    else
        vertcolor = vec4(.0, .5, .2, 1.0);
}