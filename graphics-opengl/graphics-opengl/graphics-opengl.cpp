#include "graphics-opengl.h"


string read_shader(string filename)
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

int print_error(string err_string)
{
	cout << err_string << endl;
	return -1;
}