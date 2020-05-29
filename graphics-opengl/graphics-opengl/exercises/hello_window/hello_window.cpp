#include "graphics-opengl.h"


void hello_window_resize_callback(GLFWwindow * window, int w, int h)
{
	glViewport(0, 0, w, h);																		
																								/* 
																								updating of size shall be reflected
																								*/
}

void hello_window_render_logic(GLFWwindow* window)
{
	/*
	Basically waits till the ESC key or q key is pressed
	and then closes the window
	*/
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS || glfwGetKey(window, GLFW_KEY_Q) == GLFW_PRESS)
	{
		cout << "Key pressed" << endl;
		glfwSetWindowShouldClose(window, true);
	}

}

int hello_window()
{

	/* Window Initialization */
	if (GL_FALSE == glfwInit())																	
																								/* If created it returns GL_TRUE */
	{
		cout << "Error initializing GL window" << endl;
		return -1;
	}

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);												
																								/*
																								glfwWindowHint sets the first argument with the 
																								values provided as second argument
																								first argument is an option while second argument is a value
																								based on which context is configured.
																								*/

	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);												
																								/*
																								MAJOR MINOR together states the OPENGL version to be at 4.6 
																								*/

	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);								
																								/*
																								The option OPENGL PROFILE can take 3 values
																								1 Core
																								2 Compact
																								3 Any
																								While using a opengl version <3.2 use only Any
																								While using ES version embedded system omit this option in total
																								*/

	GLFWwindow *window = glfwCreateWindow(width, height, "hello_window", nullptr, nullptr);		
																								/*
																								The window shall be created but if wont be rendered on to the
																								screen for that we need to Make it as ContextCurrent
																								Last to nullptrs are for monitor and 
																								for Context needs to be shared or not
																								*/
	if (!window)
	{
		cout << "Error creating window" << endl;
		return -1;
	}

	glfwMakeContextCurrent(window);


	glfwSetFramebufferSizeCallback(window, hello_window_resize_callback);									
																								/*
																								Shall be used if the window is resized like we do often
																								the callback expects new height and width along with the window object
																								*/

	/*
	GLAD shall manage the function pointers which is OS specific
	We pass Glad a function to load pointers to OpenGL pointers as they are OS specific
	
	So for this we need to pass glfwGetProcAddress which shall be initialized and will gives the addresses of the
	function pointers
	*/

	if (glewInit() != GLEW_OK)
	{
		cout << "Error initialzing the glad" << endl;
		return -1;
	}

	/* Rendering Loop */
	while (!glfwWindowShouldClose(window))
	{
		/* Logic goes here */
		hello_window_render_logic(window);

		glfwSwapBuffers(window);																
																								/*
																								The swap buffers is for the content to be double buffered if 
																								we dont use this render shall take time as generally with single buffer it either
																								fills from left or right
																								*/

		glfwPollEvents();																		
																								/*
																								Poll or catch the events of window like key presses mouse movements
																								*/

	}

	glfwTerminate();																			
																								/*
																								We terminate the window once finished
																								After doing this we need a glfwinit to use any glfw 
																								function
																								*/
	
	return 0;
}