#include <iostream>
#include <fstream>

#include <GL/glew.h>
#include <GLFW/glfw3.h>


#define WIDTH 1920
#define HEIGHT 1080


using namespace std;

string read_shader(string filename);

int print_error(string);

int hello_window();

int colored_window();

int sample_triangle();