#include "glfw_window_setup.h"

glfw_window_setup::glfw_window_setup()
{

	if (glfwInit() != GL_TRUE)
		cout << GLFW_INIT_ERROR << endl;
	
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, major);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, minor);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	
	this->window = glfwCreateWindow(this->width, this->height, this->title.c_str(), nullptr, nullptr);

	glfwMakeContextCurrent(this->window);
	glfwSetFramebufferSizeCallback(this->window, resize_callback);
	
}

glfw_window_setup::~glfw_window_setup()
{
	glfwTerminate();
}