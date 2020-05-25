//// graphics-opengl.cpp : This file contains the 'main' function. Program execution begins and ends there.
////
//#include "graphics-opengl.h"
//int main()
//{
//    int return_status = -1;
//    return_status = triangle();
//    cout << "\n\nReturn Status --> " << return_status << endl;
//}
//
//// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
//// Debug program: F5 or Debug > Start Debugging menu
//
//// Tips for Getting Started: 
////   1. Use the Solution Explorer window to add/manage files
////   2. Use the Team Explorer window to connect to source control
////   3. Use the Output window to see build output and other messages
////   4. Use the Error List window to view errors
////   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
////   6. In the future, to open this project again, go to File > Open > Project and select the .sln file


#include <GL/glew.h>
#include <GLFW/glfw3.h>

int main()
{
	if (!glfwInit())
	{
		glfwTerminate();
		return -1;
	}
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE); // Core implies no backward compatibility
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

	GLFWwindow* window = glfwCreateWindow(800, 900, "main window", nullptr, nullptr);
	if (!window)
	{
		return -1;
	}

	int buff_width, buff_height;
	glfwGetFramebufferSize(window, &buff_width, &buff_height);

	glfwMakeContextCurrent(window);

	glewExperimental = GL_TRUE;

	if (glewInit()!=GLEW_OK)
	{
		glfwDestroyWindow(window);
		return -1;
	}

	//viewport
	glViewport(0, 0, buff_width, buff_height);


	while (!glfwWindowShouldClose(window))
	{
		glClearColor(.5, .7, .8, 1);

		glClear(GL_COLOR_BUFFER_BIT);

		glfwPollEvents();
		glfwSwapBuffers(window);
	}
	glfwTerminate();
	return 0;
}