import moderngl_window
import numpy as np
from pathlib import Path


class multi_texture(moderngl_window.WindowConfig):
    gl_version = (4, 3)
    resizable = True
    resource_dir = Path('.').absolute()
    window_size = (1920, 1080)

    def __init__(self, **kwargs):
        super().__init__(**kwargs)

        self.program = self.ctx.program(vertex_shader=open('multi_texture.vert.glsl').read(),
                                        fragment_shader=open('multi_texture.frag.glsl').read())

        vertices = np.array([
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

        self.texture_bg = self.load_texture_2d('../imgs/wall.jpg')
        self.texture_fg = self.load_texture_2d('../imgs/awesomeface.png')

        self.program['out_tex_1'] = 0
        self.program['out_tex_2'] = 1

        self.vbo = self.ctx.buffer(vertices.astype('float32').tobytes())
        vao_content = [
            (self.vbo, '3f 2f 3f', 'in_vert', 'in_tex_corr', 'in_color')
        ]
        self.ebo = self.ctx.buffer(indices.astype('int32').tobytes())

        self.vao = self.ctx.vertex_array(self.program, vao_content, self.ebo)

    def render(self, time: float, frame_time: float):
        self.ctx.clear(.0, .0, .0)

        import math
        self.program['uni_color'] = tuple([math.sin(time) / 2.0 + .2] * 3 + [1.0])

        self.texture_bg.use(0)
        self.texture_fg.use(1)
        # swapping these 0 1 and with bg fg shall decide the opacity of the textures as set
        # in frag-shader where mix(_0,_1,opacity) altering 0 1 here shall change them there
        self.vao.render()

    @classmethod
    def run(cls):
        moderngl_window.run_window_config(cls)


multi_texture.run()
