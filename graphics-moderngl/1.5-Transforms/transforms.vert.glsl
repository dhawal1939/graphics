#version 430

in vec3 in_vert;
in vec3 in_color;
in vec2 in_tex_corr;

uniform mat4 transform;

out vec3 out_color;
out vec2 out_tex_corr;

void main() {
    gl_Position = transform * vec4(in_vert, 1.0);
    out_tex_corr = vec2(in_tex_corr.x, in_tex_corr.y);
    out_color = in_color;
}
