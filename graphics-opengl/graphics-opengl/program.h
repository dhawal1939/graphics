#pragma once
#include"stdfx.h"

class Program
{
public:
	GLuint program;
	Program();
	~Program();
	int attach_shader(GLuint shader);
	int program_link();
	int program_validate();
};

