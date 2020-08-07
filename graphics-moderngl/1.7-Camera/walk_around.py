import moderngl
import moderngl_window
from pathlib import Path
import numpy as np
import glm


class walk_around(moderngl_window.WindowConfig):
    gl_version = (4, 3)
    resizable = True
    resource_dir = Path('.').absolute()
    aspect_ratio = 16 / 9
    title = 'Walk Around'
    window_size = (1920, 1080)

    def __init__(self, **kwargs):
        super().__init__(**kwargs)

        self.cam_up = glm.vec3(.0, 1., .0)
        self.cam_pos = glm.vec3(.0, .0, 3.)
        self.cam_front = glm.vec3(.0, .0, -1.)

        # uncomment for moment speed
        # self.last_frame, self.delta_time = .0, .0
        self.program = self.ctx.program(vertex_shader=open('./camera_demo.vert.glsl').read(),
                                        fragment_shader=open('./camera_demo.frag.glsl').read())

        self.texture_bg = self.load_texture_2d('../imgs/wall.jpg')
        self.texture_fg = self.load_texture_2d('../imgs/awesomeface.png')

        self.program['out_tex_bg'] = 0
        self.program['out_tex_fg'] = 1

        self.box_vertices = np.array(
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

        self.texture_coor = np.array(
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

        self.box_vbo = self.ctx.buffer(self.box_vertices.astype('f4').tobytes())
        self.tex_vbo = self.ctx.buffer(self.texture_coor.astype('f4').tobytes())

        self.vao_content = [
            (self.box_vbo, '3f', 'in_vert'),
            (self.tex_vbo, '2f', 'in_tex')
        ]

        # multi cube positions
        self.cube_positions = [
            glm.vec3(0.0, 0.0, 0.0),
            glm.vec3(2.0, 5.0, -15.0),
            glm.vec3(-1.5, -2.2, -2.5),
            glm.vec3(-3.8, -2.0, -12.3),
            glm.vec3(2.4, -0.4, -3.5),
            glm.vec3(-1.7, 3.0, -7.5),
            glm.vec3(1.3, -2.0, -2.5),
            glm.vec3(1.5, 2.0, -2.5),
            glm.vec3(1.5, 0.2, -1.5),
            glm.vec3(-1.3, 1.0, -1.5)
        ]

        self.vao = self.ctx.vertex_array(self.program, self.vao_content)

    def render(self, time: float, frame_time: float):

        self.ctx.clear(.0, .0, .0)
        self.ctx.enable(moderngl.DEPTH_TEST)

        # uncomment for moment speed
        # self.delta_time = time - self.last_frame
        # self.last_frame = time

        model = glm.mat4(1.)
        self.texture_bg.use(0)
        self.texture_fg.use(1)

        view = glm.lookAt(self.cam_pos, self.cam_pos + self.cam_front, self.cam_up)

        projection = glm.perspective(glm.radians(45.0), self.aspect_ratio, 0.1, 100.)

        self.program["projection"].write(projection)

        self.program['view'].write(view)

        for i in range(len(self.cube_positions)):
            model = glm.translate(model, self.cube_positions[i])
            angle = 20. * i
            model = glm.rotate(model, glm.radians(angle), glm.vec3(1., .3, .5))

            self.program['model'].write(model)
            self.vao.render()

    def key_event(self, key, action, modifiers):
        keys = self.wnd.keys
        # uncomment for moment speed
        cam_speed = 2.5  # * self.delta_time
        if action == keys.ACTION_PRESS:
            if key == keys.W:
                self.cam_pos += cam_speed * self.cam_front
            if key == keys.S:
                self.cam_pos -= cam_speed * self.cam_front
            if key == keys.A:
                self.cam_pos -= glm.normalize(glm.cross(self.cam_front, self.cam_up))
            if key == keys.D:
                self.cam_pos += glm.normalize(glm.cross(self.cam_front, self.cam_up))

    @classmethod
    def run(cls):
        moderngl_window.run_window_config(cls)


walk_around.run()
