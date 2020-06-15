'''
    Renders a rotating and scaling triangle
'''

import numpy as np
import moderngl_window
import math


class uniforms(moderngl_window.WindowConfig):
    gl_version = (4, 3)
    title = 'Uniform'
    resizable = True
    aspect_ratio = 16 / 9
    window_size = (1920, 1080)

    def __init__(self, **kwargs):
        super().__init__(**kwargs)

        self.program = self.ctx.program(vertex_shader=open("../shaders/uniforms.vert.glsl").read(),
                                        fragment_shader=open("../shaders/uniforms.frag.glsl").read(),
                                        )

        vertices = np.array(
            [
                -.5, 0,
                .0, .5,
                .5, .0,
            ]
        )

        indices = np.array([
            0, 1, 2
        ])
        self.vbo = self.ctx.buffer(vertices.astype('float32').tobytes())
        self.ibo = self.ctx.buffer(indices.astype('int32').tobytes())

        self.vao_content = [
            (self.vbo, '2f', 'in_vert')
        ]
        self.vao = self.ctx.vertex_array(self.program, self.vao_content, self.ibo)

    def render(self, time: float, frame_time: float):
        self.ctx.clear(.3, .3, .3)

        self.program['outcolor'] = (.0, math.sin(time) / 2.0 + 0.5, .0, 1.0)

        self.vao.render()

    @classmethod
    def run(cls):
        moderngl_window.run_window_config(cls)


uniforms.run()
