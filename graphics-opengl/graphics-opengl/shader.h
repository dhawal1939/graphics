#pragma once
#include "stdfx.h"

class Shader
{
public:
	GLuint shader;
	GLenum shader_type;
	Shader(GLenum shader_type, string shader_file);
	~Shader();
private:
	string read_shader(string shader_file);
};
