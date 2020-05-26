#include "graphics-opengl.h"

const char vert[] = "#version 430\nlayout(location = 0) in vec3 pos;\nvoid main()\n{	gl_Position = vec4(pos.x, pos.y, pos.z, 1.0);}";
const char frag[] = "#version 430\nout vec4 color;void main()\n{	color = vec4(1.0, 1.0, .0, 1.0);}";

GLuint lab_1_triangle_window_render_logic(GLFWwindow* window)
{
	/*Triangle data*/
	GLint verticies[] = {
		-1.0f, -1.0f, .0f,
		1.0f, -1.0f, .0f,
		.0f, 1.0f, .0f
	};

	GLuint vao, vbo;

	glGenVertexArrays(1, &vao);
								/*
								Creates a vertex array in gpu and initializing
								it to the vao variable
								-------------->This tell what type of data is
								*/
	glBindVertexArray(vao);


	glGenBuffers(1, &vbo);	
								/*
								Create Buffer the data is stored here
								------------------>This is data itself
								*/
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(verticies), verticies, GL_STATIC_DRAW);
								/*
								Static draw is we dont change the vertices
								*/
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);

	glEnableVertexAttribArray(0);

	glBindVertexArray(0); /* Unbind the vertex buffer */

	return vao;
}

void lab_1_compile_shader(GLuint program, const char* filename, GLenum shader_type)
{
	string shader_string = read_shader((char*)filename);
	GLchar* shader_code = (char*)shader_string.c_str();
	cout << shader_code << endl;
	GLint shader_code_length = strlen(shader_code);

	GLuint shader = glCreateShader(shader_type);
	
	glShaderSource(shader, 1, &shader_code, &shader_code_length);

	glCompileShader(shader);

	GLint result = 0;
	GLchar gl_log[1024] = { 0 };

	glGetShaderiv(shader, GL_LINK_STATUS, &result);

	if (!result)
	{
		glGetShaderInfoLog(shader, sizeof(gl_log), nullptr, gl_log);
		cout << "Error in " << filename << " :" << gl_log << endl;
		return;
	}

	glAttachShader(program, shader);

	return;
}

GLuint lab_1_shaders()
{
	GLuint program = glCreateProgram();
	if (!program)
	{
		cout << "Error creating shader" << endl;
		return 1;
	}

	lab_1_compile_shader(program, "lab_1.vert", GL_VERTEX_SHADER);
	lab_1_compile_shader(program, "lab_1.frag", GL_FRAGMENT_SHADER);

	GLint result = 0;
	GLchar gl_log[1024] = { 0 };

	glLinkProgram(program);
	glGetProgramiv(program, GL_LINK_STATUS, &result);

	if (!result)
	{
		glGetProgramInfoLog(program, sizeof(gl_log), nullptr, gl_log);
		cout << "Error Link: " << gl_log << endl;
		return 1;
	}

	glValidateProgram(program);
	glGetProgramiv(program, GL_VALIDATE_STATUS, &result);

	if (!result)
	{
		glGetProgramInfoLog(program, sizeof(gl_log), nullptr, gl_log);
		cout << "Error Validate:" << gl_log << endl;
		return 1;
	}

	return program;
}

void lab_1_triangle_window_resize_callback(GLFWwindow* window, int w, int h)
{
	glViewport(0, 0, w, h);
}

int lab_1_triangle()
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
	glfwSetFramebufferSizeCallback(window, lab_1_triangle_window_resize_callback);

	if (glewInit() != GLEW_OK)
	{
		cout << "error linking GLEW" << endl;
		return -1;
	}




	GLuint vao = lab_1_triangle_window_render_logic(window);
	GLuint shader = lab_1_shaders();

	while (!glfwWindowShouldClose(window))
	{
		//Render Logic
		glUseProgram(shader);

		glBindVertexArray(vao);

		glDrawArrays(GL_TRIANGLES, 0, 3);

		glBindVertexArray(0);

		glUseProgram(0);
		glfwPollEvents();
		glfwSwapBuffers(window);
	}

	glfwTerminate();

	return 0;
}