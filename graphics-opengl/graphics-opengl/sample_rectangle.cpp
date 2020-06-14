#include "sample_rectangle.h"

int sample_rectangle(string vert_file, string frag_file)
{
    GLfloat vertices[] = {
       .5f,.5f,.0f,
       .5f,-.5f,.0f,
       -.5f,-.5f,.0f,
       -.5f,.5f,.0f,
    };

    GLuint indicies[] = {
        0,1,3,
        1,2,3
    };

    Window* window = new Window();

    if (init())
        return -1;
    Program* program = new Program();

    Shader* vert_shader = new Shader(GL_VERTEX_SHADER, vert_file);
    Shader* frag_shader = new Shader(GL_FRAGMENT_SHADER, frag_file);

    program->attach_shader(vert_shader->shader);
    program->attach_shader(frag_shader->shader);

    if (program->program_link())
        return -1;
    if (program->program_validate())
        return -1;

    GLuint vao, vbo, ebo;

    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);
    {

        glGenBuffers(1, &vbo);
        glBindBuffer(GL_ARRAY_BUFFER, vbo);
        {
            glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

            glGenBuffers(1, &ebo);
            glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
            glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indicies), indicies, GL_STATIC_DRAW);

            glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GL_FLOAT), nullptr);
            glEnableVertexAttribArray(0);
        }
        glBindBuffer(GL_ARRAY_BUFFER, 0); // Can be unbinded as glvertexattribpointer has registered vbo as vertex attrib 
        // Donot unbind GLARRAY_ELEMENT BUFFER
    }
    glBindVertexArray(0);

    //glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    while (!glfwWindowShouldClose(window->window))
    {
        glClearColor(.2f, .3f, .3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        glUseProgram(program->program);

        glBindVertexArray(vao);
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

        glfwSwapBuffers(window->window);
        glfwPollEvents();
    }

    delete window;
    delete program;
    delete vert_shader;
    delete frag_shader;
    return 0;
}
