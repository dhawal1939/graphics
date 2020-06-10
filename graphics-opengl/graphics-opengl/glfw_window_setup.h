#pragma once
#include "stdfx.h"

class glfw_window_setup
{
private:
	unsigned int major = 4;
	unsigned int minor = 3;

	string title = "sample";

	unsigned int width = 1920;
	unsigned int height = 1080;


public:
	GLFWwindow* window = nullptr;
	glfw_window_setup();
	~glfw_window_setup();
};