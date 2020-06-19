import moderngl_window
import moderngl
import numpy as np


class triangle(moderngl_window.WindowConfig):
    gl_version = (4, 3)
    title = 'Sample 1.2-Triangle'
    resizable = True
    aspect_ratio = 16 / 9
    window_size = (1920, 1080)

    def __init__(self, **kwargs):
        super().__init__(**kwargs)

        self.program = self.ctx.program(
            vertex_shader=open('sample_triangle.vert.glsl').read(),
            fragment_shader=open('sample_triangle.frag.glsl').read()
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

        self.vbo = self.ctx.buffer(vertices.astype('float32').tobytes())
        self.ebo = self.ctx.buffer(indices.astype('int32').tobytes())

        vao_content = [
            (self.vbo, '2f', 'in_vert')
        ]
        self.vao = self.ctx.vertex_array(self.program, vao_content, self.ebo)
        # uncomment the next line to plot only points
        self.points = False  # if False else True

    def render(self, time: float, frame_time: float):
        self.ctx.clear(.0, .0, .0)
        if self.points:
            '''plot only points'''
            mode = moderngl.POINTS
        else:
            mode = moderngl.TRIANGLES
        self.vao.render(mode=mode)

    @classmethod
    def run(cls):
        moderngl_window.run_window_config(cls)


triangle.run()
