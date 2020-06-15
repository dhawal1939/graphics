import moderngl_window
import math
import random


class window(moderngl_window.WindowConfig):
    gl_version = (3, 3)
    title = "Empty Window"
    window_size = (1280, 720)
    aspect_ratio = 16 / 9
    resizable = True

    def __init__(self, **kwargs):
        super().__init__(**kwargs)

    def render(self, time: float, frame_time: float):
        # Uncomment to see changing colors with time
        # self.ctx.clear(
        #     (math.sin(time) + 1.0) / 2,
        #     (math.sin(time + 2) + 1.0) / 2,
        #     (math.sin(time + 3) + 1.0) / 2,
        # )
        pass

    @classmethod
    def run(cls):
        moderngl_window.run_window_config(cls)


window.run()
