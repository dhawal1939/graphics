#include "shader.h"

Shader::Shader(GLenum shader_type, string shader_file)
{
	this->shader_type = shader_type;
	this->shader = glCreateShader(this->shader_type);

	string shader_source_code = read_shader(shader_file);
	const char* shader_source = shader_source_code.c_str();


	glShaderSource(this->shader, 1, &shader_source, nullptr);

	glCompileShader(this->shader);

	GLint result;
	char info_log[512];
	glGetShaderiv(this->shader, GL_COMPILE_STATUS, &result);

	if (result != GL_TRUE)
	{
		glGetShaderInfoLog(this->shader, sizeof(info_log), nullptr, info_log);
		cout << SHADER_COMPILE_ERROR << info_log << endl;
	}
}

Shader::~Shader()
{
	glDeleteShader(this->shader);
}

string Shader::read_shader(string shader_file)
{
	fstream shader_source(shader_file);
	if (!shader_source.good())
	{
		cout << SHADER_FILE_ERROR << shader_file << endl;
		return "";
	}

	return string(istreambuf_iterator<char>(shader_source), istreambuf_iterator<char>());
}