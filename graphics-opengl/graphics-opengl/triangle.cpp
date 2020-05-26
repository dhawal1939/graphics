#include "graphics-opengl.h"

int triangle_render_logic(GLFWwindow* window)
{
	return 0;
}

void triangle_resize_callback(GLFWwindow* window, int w, int h)
{
	glViewport(0, 0, w, h);
}

int triangle()
{
	if (glfwInit() == GL_FALSE)
	{
		cout << "Error Initializing GLFW" << endl;
		return -1;
	}

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	GLFWwindow* window = glfwCreateWindow(width, height, "Triangle", nullptr, nullptr);

	if (!window)
	{
		cout << "Error creating window" << endl;
		return -1;
	}

	glfwMakeContextCurrent(window);
	glfwSetFramebufferSizeCallback(window, triangle_resize_callback);

	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		cout << "Opengl function pointers loading failed" << endl;
		return -1;
	}

	/* Rendering Logic */
	while (glfwWindowShouldClose(window))
	{
		triangle_render_logic(window);
		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	glfwTerminate();

	return 0;
}