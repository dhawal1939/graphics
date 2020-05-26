#include "graphics-opengl.h"


string read_shader(char* filename)
{
	ifstream shader(filename);
	if (!shader.good())
	{
		return "File does not exist\n";
	}
	return string(
		istreambuf_iterator<char>(shader),
		istreambuf_iterator<char>());
}

