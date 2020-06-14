import moderngl_window
import numpy as np


class triangle(moderngl_window.WindowConfig):
    gl_version = (4, 3)
    title = 'Sample Triangle'
    resizable = True
    aspect_ratio = 16 / 9
    window_size = (1920, 1080)

    def __init__(self, **kwargs):
        super().__init__(**kwargs)

        self.program = self.ctx.program(
            vertex_shader=open('../shaders/sample.vert').read(),
            fragment_shader=open('../shaders/sample.frag').read()
        )
        vertices = np.array([
            -.5, .0,
            .0, .5,
            .5, .0,
        ])

        indices = np.array(
            [
                0, 1, 2,
            ]
        )

        self.vbo = self.ctx.buffer(vertices.astype('f4').tobytes())
        self.ebo = self.ctx.buffer(indices.astype('i4').tobytes())

        vao_content = [
            (self.vbo, '2f', 'in_vert')
        ]
        self.vao = self.ctx.vertex_array(self.program, vao_content, self.ebo)

    def render(self, time: float, frame_time: float):
        self.ctx.clear(.3, .3, .4)
        self.vao.render()

    @classmethod
    def run(cls):
        moderngl_window.run_window_config(cls)


triangle.run()
