#pragma once

#include <iostream>
#include <fstream>


#include "GLFW/glfw3.h"
#include "glad/glad.h"

#define GLFW_INIT_ERROR "Error INIT GLFW "
#define SHADER_FILE_ERROR "Shader File Not Found "
#define SHADER_COMPILE_ERROR "Shader Compile Error "
#define PROGRAM_LINK_ERROR "Program Link Error"
#define PROGRAM_VALIDATION_ERROR "Program Validation Error"

using namespace std;

extern string file_path;

void resize_callback(GLFWwindow* window, int width, int height);

int init();