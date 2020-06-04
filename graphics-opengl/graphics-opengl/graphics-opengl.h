#include <iostream>
#include <fstream>

//#include <GL/glew.h>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <stb_image.h>

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>

#include <shader_s.h>


#define width 1920
#define height 1080


using namespace std;

string read_shader(char* filename);

int hello_window();

int colored_window();

int sample_triangle();

int textures();