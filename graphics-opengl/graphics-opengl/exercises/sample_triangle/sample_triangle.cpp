#include "graphics-opengl.h"

void sample_triangle_resize_callback(GLFWwindow* window, int w, int h)
{
	glViewport(0, 0, w, h);
}

GLuint sample_triangle_vao()
{
	GLuint vao, vbo;

	GLfloat vertices[] = {
		-1.0, 0.0, 0.0,
		0.0, 1.0, 0.0,
		1.0, 0.0, 0.0,
	};

	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);

	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	{
		glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);

		glEnableVertexAttribArray(0);

	}
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);

	return vao;
}

GLuint sample_triangle_load_shader(string filename, GLenum shader_type)
{
	GLuint shader = glCreateShader(shader_type);

	string temp = read_shader(filename);
	GLchar* shader_code = (char*)temp.c_str();
	
	glShaderSource(shader, 1, &shader_code, 0);

	glCompileShader(shader);

	GLint result;
	char info_log[512];
	glGetShaderiv(shader, GL_COMPILE_STATUS, &result);
	if (!result)
	{
		glGetShaderInfoLog(shader, sizeof(info_log), nullptr, info_log);
		return print_error(info_log);
	}

	return shader;
}

GLuint sample_triangle_shadder_program(string vert_file, string frag_file)
{
	GLuint program = glCreateProgram();
	if (!program)
		return print_error("ERROR CREATING PROGRAM");

	GLuint vert_shader, frag_shader;
	vert_shader = sample_triangle_load_shader(vert_file, GL_VERTEX_SHADER);
	frag_shader = sample_triangle_load_shader(frag_file, GL_FRAGMENT_SHADER);

	glAttachShader(program, vert_shader);
	glAttachShader(program, frag_shader);

	GLint result;
	char info_log[512];

	glLinkProgram(program);
		
	glGetProgramiv(program, GL_LINK_STATUS, &result);
	if (!result)
	{
		glGetProgramInfoLog(program, sizeof(info_log), nullptr, info_log);
		return print_error(info_log);
	}

	glValidateProgram(program);

	glGetProgramiv(program, GL_VALIDATE_STATUS, &result);
	if (!result)
	{
		glGetProgramInfoLog(program, sizeof(info_log), nullptr, info_log);
		return print_error(info_log);
	}

	return program;
}

int sample_triangle()
{
	if (!glfwInit())
	{
		
	}

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);

	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	GLFWwindow* window = glfwCreateWindow(WIDTH, HEIGHT, "Sample Triangle", nullptr, nullptr);

	if (!window)
		return print_error("ERROR CREATING WINDOW");

	glfwMakeContextCurrent(window);

	glfwSetFramebufferSizeCallback(window, sample_triangle_resize_callback);

	if (glewInit() != GLEW_OK)
		return print_error("GLEW INIT FAILED");

	
	string vert_file = "C:/Users/brothereye/source/repos/Graphics/graphics-opengl/graphics-opengl/exercises/sample_triangle/sample_triangle.vert";
	string frag_file = "C:/Users/brothereye/source/repos/Graphics/graphics-opengl/graphics-opengl/exercises/sample_triangle/sample_triangle.frag";
	
	GLuint program = sample_triangle_shadder_program(vert_file, frag_file);
	GLuint vao = sample_triangle_vao();

	while (!glfwWindowShouldClose(window))
	{
		//Render Logic
		glUseProgram(program);
		
		glBindVertexArray(vao);
		{
			glDrawArrays(GL_TRIANGLES, 0, 3);
		}
		glBindVertexArray(0);

		glfwPollEvents();
		glfwSwapBuffers(window);
	}

	return 0;
}