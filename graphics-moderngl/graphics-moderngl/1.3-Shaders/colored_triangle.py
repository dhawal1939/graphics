import moderngl_window
import numpy as np


class colored_triangle(moderngl_window.WindowConfig):
    gl_version = (4, 3)
    window_size = (1920, 1080)
    resizable = True

    def __init__(self, **kwargs):
        super().__init__(**kwargs)

        self.program = self.ctx.program(vertex_shader=open("../vert_frag_shaders/triangle.vert.glsl").read(),
                                        fragment_shader=open("../vert_frag_shaders/triangle.frag.glsl").read(),
                                        )

        vertices = np.array([
            # x,  y,   r,    g,   b
            -.5, +.0, 0.0, 1.0, 0.0,
            +.0, +.5, 1.0, 0.0, 0.0,
            +.5, +.0, 0.0, 0.0, 1.0
        ])

        self.vbo = self.ctx.buffer(vertices.astype('float32').tobytes())

        vao_content = [(self.vbo, '2f 3f', 'in_vert', 'in_color')]

        self.vao = self.ctx.vertex_array(self.program, vao_content)

    def render(self, time: float, frame_time: float):
        self.ctx.clear(.0, .0, .0)
        self.vao.render()

    @classmethod
    def run(cls):
        moderngl_window.run_window_config(cls)


colored_triangle.run()
