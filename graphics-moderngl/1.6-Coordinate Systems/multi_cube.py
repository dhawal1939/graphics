import moderngl
import moderngl_window
from pathlib import Path
import numpy as np
import glm


class multi_cube(moderngl_window.WindowConfig):
    gl_version = (4, 3)
    resource_dir = Path('.').absolute()
    resizable = True
    window_size = (1920, 1080)
    aspect_ratio = 16 / 9
    title = "Multi Cube"

    def __init__(self, **kwargs):
        super().__init__(**kwargs)

        self.program = self.ctx.program(vertex_shader=open("./coordinate_systems.vert.glsl").read(),
                                        fragment_shader=open("./coordinate_system.frag.glsl").read())

        self.texture_bg = self.load_texture_2d('../imgs/wall.jpg')
        self.texture_fg = self.load_texture_2d('../imgs/awesomeface.png')

        self.program['out_tex_bg'] = 0
        self.program['out_tex_fg'] = 1

        self.box_vertices = np.array(
            [
                -0.5, -0.5, -0.5,
                0.5, -0.5, -0.5,
                0.5, 0.5, -0.5,
                0.5, 0.5, -0.5,
                -0.5, 0.5, -0.5,
                -0.5, -0.5, -0.5,

                -0.5, -0.5, 0.5,
                0.5, -0.5, 0.5,
                0.5, 0.5, 0.5,
                0.5, 0.5, 0.5,
                -0.5, 0.5, 0.5,
                -0.5, -0.5, 0.5,

                -0.5, 0.5, 0.5,
                -0.5, 0.5, -0.5,
                -0.5, -0.5, -0.5,
                -0.5, -0.5, -0.5,
                -0.5, -0.5, 0.5,
                -0.5, 0.5, 0.5,

                0.5, 0.5, 0.5,
                0.5, 0.5, -0.5,
                0.5, -0.5, -0.5,
                0.5, -0.5, -0.5,
                0.5, -0.5, 0.5,
                0.5, 0.5, 0.5,

                -0.5, -0.5, -0.5,
                0.5, -0.5, -0.5,
                0.5, -0.5, 0.5,
                0.5, -0.5, 0.5,
                -0.5, -0.5, 0.5,
                -0.5, -0.5, -0.5,

                -0.5, 0.5, -0.5,
                0.5, 0.5, -0.5,
                0.5, 0.5, 0.5,
                0.5, 0.5, 0.5,
                -0.5, 0.5, 0.5,
                -0.5, 0.5, -0.5,
            ]
        )

        self.texture_coor = np.array(
            [
                0.0, 0.0,
                1.0, 0.0,
                1.0, 1.0,
                1.0, 1.0,
                0.0, 1.0,
                0.0, 0.0,

                0.0, 0.0,
                1.0, 0.0,
                1.0, 1.0,
                1.0, 1.0,
                0.0, 1.0,
                0.0, 0.0,

                1.0, 0.0,
                1.0, 1.0,
                0.0, 1.0,
                0.0, 1.0,
                0.0, 0.0,
                1.0, 0.0,

                1.0, 0.0,
                1.0, 1.0,
                0.0, 1.0,
                0.0, 1.0,
                0.0, 0.0,
                1.0, 0.0,

                0.0, 1.0,
                1.0, 1.0,
                1.0, 0.0,
                1.0, 0.0,
                0.0, 0.0,
                0.0, 1.0,

                0.0, 1.0,
                1.0, 1.0,
                1.0, 0.0,
                1.0, 0.0,
                0.0, 0.0,
                0.0, 1.0
            ]
        )

        self.box_vbo = self.ctx.buffer(self.box_vertices.astype('f4').tobytes())
        self.tex_vbo = self.ctx.buffer(self.texture_coor.astype('f4').tobytes())

        self.vao_content = [
            (self.box_vbo, '3f', 'in_vert'),
            (self.tex_vbo, '2f', 'in_tex')
        ]

        # multi cube positions
        self.cube_positions = [
            glm.vec3(0.0, 0.0, 0.0),
            glm.vec3(2.0, 5.0, -15.0),
            glm.vec3(-1.5, -2.2, -2.5),
            glm.vec3(-3.8, -2.0, -12.3),
            glm.vec3(2.4, -0.4, -3.5),
            glm.vec3(-1.7, 3.0, -7.5),
            glm.vec3(1.3, -2.0, -2.5),
            glm.vec3(1.5, 2.0, -2.5),
            glm.vec3(1.5, 0.2, -1.5),
            glm.vec3(-1.3, 1.0, -1.5)
        ]

        self.vao = self.ctx.vertex_array(self.program, self.vao_content)

    def render(self, time: float, frame_time: float):
        self.ctx.clear(.0, .0, .0)
        self.ctx.enable(moderngl.DEPTH_TEST)

        view = glm.mat4(1.0)

        self.program['view'].write(glm.translate(view, glm.vec3(0.0, 0.0, -3.0)))

        self.program['projection'].write(glm.perspective(glm.radians(45.0), self.aspect_ratio, .1, 100.))

        self.texture_bg.use(0)
        self.texture_fg.use(1)

        for i in range(len(self.cube_positions)):
            model = glm.mat4(1.0)
            model = glm.translate(model, self.cube_positions[i])
            model = glm.rotate(model, glm.radians(20.0 * time), glm.vec3(i, .3, .5))

            self.program['model'].write(model)

            self.vao.render()


    @classmethod
    def run(cls):
        moderngl_window.run_window_config(cls)


multi_cube.run()
