#version 430
in vec2 in_vert;
in vec3 in_color;

out vec3 out_color;
void main() {
    gl_Position = vec4(in_vert, .0, 1.0);
    out_color = in_color;
}
