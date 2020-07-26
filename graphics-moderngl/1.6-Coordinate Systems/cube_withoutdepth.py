import moderngl_window
import numpy as np
from pathlib import Path
import glm
import moderngl


class cube_withoutdepth(moderngl_window.WindowConfig):
    gl_version = (4, 3)
    window_size = (1920, 1080)
    resizable = True
    resource_dir = Path('.').absolute()
    title = "Depth Less Cube"

    def __init__(self, **kwargs):
        super().__init__(**kwargs)

        self.program = self.ctx.program(vertex_shader=open('./coordinate_systems.vert.glsl').read(),
                                        fragment_shader=open('./coordinate_system.frag.glsl').read())

        self.texture_vertices = np.array(
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
        self.vertices = np.array(
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

        self.texture_bg = self.load_texture_2d("../imgs/wall.jpg")
        self.texture_fg = self.load_texture_2d("../imgs/awesomeface.png")

        self.program['out_tex_bg'] = 0
        self.program['out_tex_fg'] = 1

        self.cube_vbo = self.ctx.buffer(self.vertices.astype("float32").tobytes())
        self.text_vbo = self.ctx.buffer(self.texture_vertices.astype('float32').tobytes())

        self.vao_content = [
            (self.cube_vbo, '3f', 'in_vert'),
            (self.text_vbo, '2f', 'in_tex')
        ]

        self.vao = self.ctx.vertex_array(self.program, self.vao_content)

    def render(self, time: float, frame_time: float):
        self.ctx.clear(.0, .0, .0)

        # Uncomment this line to get the Depth based Box
        # self.ctx.enable(moderngl.DEPTH_TEST)

        model, view = glm.mat4(1.0), glm.mat4(1.0)

        model = glm.rotate(model, time * glm.radians(45), glm.vec3(.5, 1., .0))
        view = glm.translate(view, glm.vec3(.0, .0, -3.0))

        projection = glm.perspective(glm.radians(45.0), 800 / 600, .1, 100.0)

        self.program['model'].write(model)
        self.program['view'].write(view)
        self.program['projection'].write(projection)

        self.texture_bg.use(0)
        self.texture_fg.use(1)

        self.vao.render()

    @classmethod
    def run(cls):
        moderngl_window.run_window_config(cls)


cube_withoutdepth.run()
