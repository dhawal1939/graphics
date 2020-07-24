#version 430

in vec3 in_vert;
in vec2 in_tex;

out vec2 out_tex;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

void main()
{
	gl_Position = projection * view * model * vec4(in_vert, 1.0);
	out_tex = vec2(in_tex.x, in_tex.y);
}