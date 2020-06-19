#version 430

in vec3 in_vert;
in vec2 in_tex_corr;
in vec3 in_color;

out vec3 out_color;
out vec2 out_tex_corr;

void main() {
    gl_Position = vec4(in_vert, 1.0);
    out_tex_corr = vec2(in_tex_corr.x, in_tex_corr.y);
    out_color = in_color;
}
