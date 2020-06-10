#include "sample_triangle.h"

int sample_triangle(string vert_file, string frag_file)
{
	glfw_window_setup *window = new glfw_window_setup();

	if (init())
		return -1;

	Program *program = new Program();

	Shader* vert_shader = new Shader(GL_VERTEX_SHADER, vert_file);
	Shader* frag_shader = new Shader(GL_FRAGMENT_SHADER, frag_file);

	program->attach_shader(vert_shader->shader);
	program->attach_shader(frag_shader->shader);

	if (program->program_link())
		return -1;
	if (program->program_validate())
		return -1;

	GLfloat vertices[] = {
		-.5, .0,.0,
		.0,.5,.0,
		.5,.0,.0
	};

	GLuint vao, vbo;

	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);
	{
		glGenBuffers(1, &vbo);
		glBindBuffer(GL_ARRAY_BUFFER, vbo);
		{
			glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
			glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3*sizeof(GLfloat), nullptr);
			glEnableVertexAttribArray(0);
		}
		glBindBuffer(GL_ARRAY_BUFFER, 0);
	}
	glBindVertexArray(0);


	while (!glfwWindowShouldClose(window->window))
	{
		glClearColor(.2, .3, .3, 1.0);
		glClear(GL_COLOR_BUFFER_BIT);

		glUseProgram(program->program);
		glBindVertexArray(vao);
		{
			glDrawArrays(GL_TRIANGLES, 0, 3);
		}

		glfwSwapBuffers(window->window);
		glfwPollEvents();
	}

	delete window;
	delete program;
	delete vert_shader;
	delete frag_shader;

	return 0;
}