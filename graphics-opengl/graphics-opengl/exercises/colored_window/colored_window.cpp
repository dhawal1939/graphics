#include "graphics-opengl.h"
#include <random>
void colored_window_render_logic(GLFWwindow* window)
{
	/* S for change the color at random */
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
	{
		GLfloat r = (rand() + 255) % 255 / 255.0f, g = (rand() + 255) % 255 / 255.0f, b = (rand() + 255) % 255 / 255.0f;
		glClearColor(r, g, b, 1.0);
		glClear(GL_COLOR_BUFFER_BIT);
		/*
		if this glclear function is not used it does
		not render the new color
		*/
	}
	if (glfwGetKey(window, GLFW_KEY_Q) == GLFW_PRESS || glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
	{
		glfwSetWindowShouldClose(window, true);
	}
}

void colored_window_resize_callback(GLFWwindow* window, int w, int h)
{
	glViewport(0, 0, w, h);
}

int colored_window()
{
	if (glfwInit() == GL_FALSE)
	{
		cout << "Error initializing GLFW" << endl;
		return -1;
	}
	
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	GLFWwindow* window = glfwCreateWindow(width, height, "colored_window", nullptr, nullptr);

	if (!window)
	{
		cout << "Error creating Window" << endl;
		return -1;
	}

	glfwMakeContextCurrent(window);
	glfwSetFramebufferSizeCallback(window, colored_window_resize_callback);

	if (glewInit() != GLEW_OK)
	{
		cout << "Error fetching function pointers of GL Library" << endl;
	}

	/* Render Logic */
	cout << "press S to start color change" << endl;
	while (!glfwWindowShouldClose(window))
	{
		colored_window_render_logic(window);
		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	glfwTerminate();
	return 0;
}