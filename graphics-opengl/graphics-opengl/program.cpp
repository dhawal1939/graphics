#include "program.h"

Program::Program()
{
	this->program = glCreateProgram();

}

Program::~Program()
{
	glDeleteProgram(this->program);
}

int Program::attach_shader(GLuint shader)
{
	glAttachShader(this->program, shader);
	return 0;
}

int Program::program_link()
{
	GLint result;
	GLchar info_log[512];

	glLinkProgram(this->program);
	
	glGetProgramiv(this->program, GL_LINK_STATUS, &result);
	if (result != GL_TRUE)
	{
		glGetProgramInfoLog(this->program, sizeof(info_log), nullptr, info_log);
		cout << PROGRAM_LINK_ERROR << endl;
		return 1;
	}
	return 0;
}

int Program::program_validate()
{
	GLint result;
	GLchar info_log[512];

	glValidateProgram(this->program);

	glGetProgramiv(this->program, GL_VALIDATE_STATUS, &result);
	if (result != GL_TRUE)
	{
		glGetProgramInfoLog(this->program, sizeof(info_log), nullptr, info_log);
		cout << PROGRAM_VALIDATION_ERROR << endl;
		return 1;
	}
	return 0;
}
