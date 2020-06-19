import moderngl_window
import moderngl
import numpy as np
from pathlib import Path
import sys

class texture(moderngl_window.WindowConfig):
    gl_version = (4, 3)
    resizable = True
    window_size = (1920, 1080)
    resource_dir = Path('./').absolute()

    def __init__(self, **kwargs):
        super().__init__(**kwargs)
        self.program = self.ctx.program(vertex_shader=open('texture.vert.glsl').read(),
                                        fragment_shader=open('texture.frag.glsl').read())
        vertices = np.array([
            # positions(0,1,2)     texture(3,4)     rgb(5,6,7)
            0.5, 0.5, 0.0, 1.0, 1.0, 1., .0, .0,
            0.5, -0.5, 0.0, 1.0, 0.0, .0, 1., .0,
            -0.5, -0.5, 0.0, 0.0, 0.0, .0, .0, 1.,
            -0.5, 0.5, 0.0, 0.0, 1.0, .5, .5, .0
        ])
        indices = np.array(
            [
                0, 1, 2,
                2, 3, 0
            ]
        )

        self.vbo = self.ctx.buffer(vertices.astype('float32').tobytes())
        self.ebo = self.ctx.buffer(indices.astype('int32').tobytes())

        self.vao_content = [
            (self.vbo, '3f 2f 3f', 'in_vert', 'in_tex', 'in_color')
        ]

        self.texture = self.load_texture_2d(r"../imgs/wall.jpg")

        self.texture.repeat_x = True
        self.texture.repeat_y = True
        self.texture.filter = (moderngl.NEAREST, moderngl.NEAREST)  # minification and magnification filter
        # self.program['in_tex'] = 0

        self.vao = self.ctx.vertex_array(self.program, self.vao_content, self.ebo)

    def render(self, time: float, frame_time: float):
        self.ctx.clear(.0, .0, .0)
        self.texture.use(0)
        self.vao.render()

    @classmethod
    def run(cls):
        moderngl_window.run_window_config(cls)


texture.run()
