#include "graphics-opengl.h"

void triangle_window_render_logic(GLFWwindow* window)
{
	return;
}

void triangle_window_resize_callback(GLFWwindow* window, int w, int h)
{
	glViewport(0, 0, w, h);
}

int triangle()
{
	if (!glfwInit())
	{
		cout << "Failed to initialize GLFW" << endl;
		return -1;
	}
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

	GLFWwindow* window = glfwCreateWindow(width, height, "traingle-window", nullptr, nullptr);

	if (!window)
	{
		cout << "Window not created" << endl;
		return -1;
	}

	glfwMakeContextCurrent(window);
	glfwSetFramebufferSizeCallback(window, triangle_window_resize_callback);

	if (glewInit() != GLEW_OK)
	{
		cout << "error linking GLEW" << endl;
		return -1;
	}

	while (!glfwWindowShouldClose(window))
	{
		//Render Logic
		triangle_window_render_logic(window);
		glfwPollEvents();
		glfwSwapBuffers(window);
	}

	glfwTerminate();

	return 0;
}