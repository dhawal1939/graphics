#include "stdfx.h"


string file_path = string("C:/Users/brothereye/source/repos/Graphics/graphics-opengl/graphics-opengl/");

void resize_callback(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);
}

int init()
{
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to initialize GLAD" << std::endl;
		return 1;
	}
	return 0;
}