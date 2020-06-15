#version 430

uniform vec4 outcolor;
out vec4 gl_FragColor;
void main() {
    gl_FragColor = outcolor;
}
