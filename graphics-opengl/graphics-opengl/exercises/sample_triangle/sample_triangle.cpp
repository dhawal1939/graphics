#include "graphics-opengl.h"

void sample_triangle_resize_callback(GLFWwindow *window, int w, int h)
{
	glViewport(0, 0, w, h);
}

GLuint sample_triangle_create_triangle_vbo()
{
	GLfloat vertices[] = {
		0.5f,  0.5f, 0.0f,  // top right
	 0.5f, -0.5f, 0.0f,  // bottom right
	-0.5f,  0.5f, 0.0f,  // top left 
	// second triangle
	 0.5f, -0.5f, 0.0f,  // bottom right
	-0.5f, -0.5f, 0.0f,  // bottom left
	-0.5f,  0.5f, 0.0f   // top left
	};
	GLuint* vao = new GLuint[1], * vbo = new GLuint[1];
	
	glGenVertexArrays(1, vao);
	glBindVertexArray(*vao);

	glGenBuffers(1, vbo);
	glBindBuffer(GL_ARRAY_BUFFER, *vbo);

	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GL_FLOAT), 0);
	glEnableVertexAttribArray(0);

	return *vao;
}
GLuint sample_triangle_compile_shader(GLenum shader_type, const char *shader_filename)
{
	GLuint shader;

	shader = glCreateShader(shader_type);

	string temp = read_shader((char*)shader_filename);
	GLchar* shader_code = (char*)temp.c_str();

	GLint result = 0;
	char elog[512];

	glShaderSource(shader, 1, &shader_code, nullptr);

	glCompileShader(shader);

	glGetShaderiv(shader, GL_COMPILE_STATUS, &result);
	if (!result)
	{
		glGetShaderInfoLog(shader, sizeof(elog), nullptr, elog);
		cout << elog << endl;
		return -1;
	}

	return shader;
}
GLuint sample_triangle_create_program(const char *vertex_shader_file, const char* frag_shader_file)
{
	GLuint program = glCreateProgram();

	if (!program)
	{
		cout << "Error creating Program" << endl;
		return -1;
	}

	GLuint vertex_shader = sample_triangle_compile_shader(GL_VERTEX_SHADER, vertex_shader_file);
	GLuint frag_shader = sample_triangle_compile_shader(GL_FRAGMENT_SHADER, frag_shader_file);

	glAttachShader(program, vertex_shader);
	glAttachShader(program, frag_shader);

	glLinkProgram(program);

	GLint result = 0;
	char elog[512] = {'\0'};

	glGetProgramiv(program, GL_LINK_STATUS, &result);
	if (!result)
	{
		glGetProgramInfoLog(program, sizeof(elog), nullptr, elog);
		cout << elog << endl;
		return -1;
	}

	glValidateProgram(program);

	glGetProgramiv(program, GL_VALIDATE_STATUS, &result);

	if (!result)
	{
		glGetProgramInfoLog(program, sizeof(elog), nullptr, elog);
		cout << elog << endl;
	}

	glDeleteShader(vertex_shader);
	glDeleteShader(frag_shader);

	return program;
}

int sample_triangle()
{
	if (glfwInit() != GL_TRUE)
	{
		cout << "GLFW INIT Failed" << endl;
		return - 1;
	}

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

	GLFWwindow* window = glfwCreateWindow(width, height, "lab_1", nullptr, nullptr);

	if (!window)
	{
		cout << "Error Creating Window" << endl;
		return -1;
	}

	glfwMakeContextCurrent(window);

	glfwSetFramebufferSizeCallback(window, sample_triangle_resize_callback);

	if (glewInit() != GLEW_OK)
	{
		cout << "GLEW INIT Failed" << endl;
		return -1;
	}
	GLuint vao = sample_triangle_create_triangle_vbo();

	const char* vertex_shader_file = "C:/Users/brothereye/source/repos/Graphics/graphics-opengl/graphics-opengl/exercises/sample_triangle/sample_triangle.vert";
	const char* frag_shader_file = "C:/Users/brothereye/source/repos/Graphics/graphics-opengl/graphics-opengl/exercises/sample_triangle/sample_triangle.frag";

	GLuint program = sample_triangle_create_program(vertex_shader_file, frag_shader_file);

	while (!glfwWindowShouldClose(window))
	{
		//Render logic
		glClearColor(.2f, .2f, .2f, 1.0);
		glClear(GL_COLOR_BUFFER_BIT);

		glUseProgram(program);

			glBindVertexArray(vao);
			
			glDrawArrays(GL_FRONT_AND_BACK, 0, 6);

			glBindVertexArray(0);

		glfwPollEvents();
		glfwSwapBuffers(window);
	}

	glDeleteProgram(program);
	glfwTerminate();
	return 0;
}