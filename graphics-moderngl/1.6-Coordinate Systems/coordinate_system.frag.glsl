#version 430
out vec4 out_color;

in vec2 out_tex;

// texture samplers
uniform sampler2D out_tex_bg;
uniform sampler2D out_tex_fg;

void main()
{
	// linearly interpolate between both textures (80% container, 20% awesomeface)
	out_color = mix(texture(out_tex_bg, out_tex), texture(out_tex_fg, out_tex), 0.2);
}