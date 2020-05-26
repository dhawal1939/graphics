#pragma once

#include <iostream>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <fstream>

#define width 1920
#define height 1080

using namespace std;

string read_shader(char* filename);

int hello_window();

int colored_window();

int lab_1_triangle();