import moderngl
import moderngl_window

class window(moderngl_window.WindowConfig):
    def __init__(self, ctx=None, wnd=None, timer=None, **kwargs):
        self.gl_version = kwargs['version']
        self.window_size =
        super().__init__(ctx=ctx, wnd=wnd, timer=timer, **kwargs)

    @classmethod
    def run(cls):
        moderngl_window.run_window_config(cls)