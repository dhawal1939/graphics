#version 430

in vec2 out_tex_corr;
in vec3 out_color;

uniform vec4 uni_color;

uniform sampler2D out_tex_1;
uniform sampler2D out_tex_2;

out vec4 frag_color;

void main() {
    frag_color = mix(texture(out_tex_1, out_tex_corr), texture(out_tex_2, out_tex_corr), .3) * vec4(out_color, 1.0) *uni_color;
}
