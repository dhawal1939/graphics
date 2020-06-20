import numpy as np
from pathlib import Path
import moderngl_window
from pyrr import Matrix44 as mat4

class transforms(moderngl_window.WindowConfig):
    gl_version = (4, 3)
    resizable = True
    window_size = (1920, 1080)
    resource_dir = Path('.').absolute()

    def __init__(self, **kwargs):
        super().__init__(**kwargs)

        self.program = self.ctx.program(vertex_shader=open('transforms.vert.glsl').read(),
                                        fragment_shader=open('transforms.frag.glsl').read())

        rgb_vals = np.array([
            1., .0, .0,
            .0, 1., .0,
            .0, .0, 1.,
            .5, .5, .0
        ])

        tex_corr = np.array(
            [
                1.0, 1.0,
                1.0, 0.0,
                0.0, 0.0,
                0.0, 1.0,
            ]
        )
        rect_indices = np.array(
            [
                0, 1, 2,
                2, 3, 0
            ]
        )

        rect_vertices = np.array(
            [
                0.5, 0.5, 0.0,
                0.5, -0.5, 0.0,
                -0.5, -0.5, 0.0,
                -0.5, 0.5, 0.0,
            ]
        )

        self.texture_bg = self.load_texture_2d('../imgs/wall.jpg')
        self.texture_fg = self.load_texture_2d('../imgs/awesomeface.png')

        self.program['out_tex_1'] = 0
        self.program['out_tex_2'] = 1

        self.rect_vbo = self.ctx.buffer(rect_vertices.astype('float32').tobytes())
        self.ibo = self.ctx.buffer(rect_indices.astype('int32').tobytes())

        self.rgb_vbo = self.ctx.buffer(rgb_vals.astype('float32').tobytes())
        self.tex_vbo = self.ctx.buffer(tex_corr.astype('float32').tobytes())

        vao_content = [
            (self.rect_vbo, '3f', 'in_vert'),
            (self.rgb_vbo, '3f', 'in_color'),
            (self.tex_vbo, '2f', 'in_tex_corr')
        ]


        self.vao = self.ctx.vertex_array(self.program, vao_content, self.ibo)

    def render(self, time: float, frame_time: float):
        self.ctx.clear(.0, .0, .0)

        import math
        self.program['uni_color'] = tuple([math.sin(time) / 2.0 + .5] * 3 + [1.0])
        translate = mat4.from_translation([.5, 0.5, .0], dtype='float32')
        rotation = mat4.from_eulers((time, time/2, time/3), dtype='float32')

        self.program['transform'].write(translate * rotation)


        self.texture_fg.use(1)
        self.texture_bg.use(0)
        self.vao.render()

    @classmethod
    def run(cls):
        moderngl_window.run_window_config(cls)


transforms.run()
