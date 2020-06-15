import moderngl_window
import numpy as np


class rectangle(moderngl_window.WindowConfig):
    gl_version = (4, 3)
    title = 'Rectangle'
    window_size = (1920, 1080)
    resizable = True

    def __init__(self, **kwargs):
        super().__init__(**kwargs)

        self.program = self.ctx.program(
            vertex_shader=open('../vert_frag_shaders/sample.vert.glsl').read(),
            fragment_shader=open('../vert_frag_shaders/sample.frag.glsl').read()
        )
        vertices = np.array(
            [
                -.5, .5,
                -.5, -.5,
                .5, -.5,
                .5, .5
            ]
        )

        indices = np.array(
            [
                0, 3, 2,
                0, 2, 1
            ]
        )

        self.vbo = self.ctx.buffer(vertices.astype('float32').tobytes())
        self.ebo = self.ctx.buffer(indices.astype('int32').tobytes())

        vao_content = [
            (self.vbo, '2f', 'in_vert')
        ]
        self.vao = self.ctx.vertex_array(self.program, vao_content, self.ebo)
        # self.ctx.wireframe = True

    def render(self, time: float, frame_time: float):
        self.ctx.clear(.3, .3, .4)
        self.vao.render()

    @classmethod
    def run(cls):
        moderngl_window.run_window_config(cls)


rectangle.run()
