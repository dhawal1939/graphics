This is python variant to the C++ version presented in [`learnopengl`](https://learnopengl.com/Getting-started/Hello-Triangle)

In this example we follow same template for window creation as the previous Window Creation
specifying `gl_version, window_size, resizable flags etc`

`program` using, linking and compiling is a piece of cake now. Just pass in the `self.program` to the
`self.vao` which shall be rendered in `render` function.

`vbo` holds the vertex data which is required for rendering the concept is similar to ones explained the
link provided above.

`ibo or ebo` acts as a index object which is same as Element Buffer object as explained in the above
mentioned site. 

`vao_content` basically specifies how to interpret the data being sent to shader,
we also specify data is being sent to which variable.

say `vao_content = [((self.vbo, '2f', 'in_vert'))]` 
which means the data in `self.vbo` has `2 floats` as the data is of `x, y` coordinates.

If we are sending `x, y, z` coordinates then we need to use
`vao_content = [((self.vbo, '2f', 'in_vert'))]` and also change the `in_vert` in vertex shader
from vec2 to vec3.

Uncommenting the lines where `self.points = False` and `self.ctx.wireframe = True` shall plot only
point and wireframes respectively.

