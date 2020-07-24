import moderngl_window
from pathlib import Path
import glm
import numpy as np


class coordinate_systems(moderngl_window.WindowConfig):
    gl_version = (4, 3)
    window_size = (1920, 1080)
    resource_dir = Path('.').absolute()

    def __init__(self, **kwargs):
        super().__init__(**kwargs)

        self.program = self.ctx.program(vertex_shader=open('./coordinate_systems.vert.glsl').read(),
                                        fragment_shader=open('./coordinate_system.frag.glsl').read())

        self.box_vertices = np.array(
            [
                0.5, 0.5, 0.0,
                0.5, -0.5, 0.0,
                - 0.5, -0.5, 0.0,
                - 0.5, 0.5, 0.0,
            ]
        )

        self.texture_coor = np.array(
            [
                1.0, 1.0,
                1.0, 0.0,
                0.0, 0.0,
                0.0, 1.0
            ]
        )

        self.indices = np.array([
            0, 1, 3,
            1, 2, 3
        ])

        self.box_vbo = self.ctx.buffer(self.box_vertices.astype('float32').tobytes())
        self.box_ibo = self.ctx.buffer(self.indices.astype('int32').tobytes())

        self.texture_vbo = self.ctx.buffer((self.texture_coor.astype('float32')).tobytes())

        self.texture_bg = self.load_texture_2d('../imgs/wall.jpg')
        self.texture_fg = self.load_texture_2d('../imgs/awesomeface.png')

        self.program['out_tex_bg'] = 0
        self.program['out_tex_fg'] = 1

        self.vao_content = [
            (self.box_vbo, '3f', 'in_vert'),
            (self.texture_vbo, '2f', 'in_tex'),
        ]

        self.vao = self.ctx.vertex_array(self.program, self.vao_content, self.box_ibo)

    def render(self, time: float, frame_time: float):
        self.ctx.clear(.0, .0, .0)
        model = glm.mat4(1.0)
        view = glm.mat4(1.0)
        projection = glm.mat4(1.0)

        model = glm.rotate(model, glm.radians(-55.0), glm.vec3(1., .0, .0))
        view = glm.translate(view, glm.vec3(.0, .0, -3.0))

        projection = glm.perspective(glm.radians(45.0), 1920/1080, .1, 100.0)

        self.program['model'].write(model)
        self.program['view'].write(view)
        self.program['projection'].write(projection)

        self.texture_bg.use(0)
        self.texture_fg.use(1)

        self.vao.render()


    @classmethod
    def run(cls):
        moderngl_window.run_window_config(cls)


coordinate_systems.run()