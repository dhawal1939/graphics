This is python variant to the C++ version presented in [`learnopengl`](https://learnopengl.com/Getting-started/Shaders)

Most of the content is presented in the above site, important points to poinder here are

unlike tedious task of accessing uniforms in `c++` we just can get them just by the dictionary kind of access in 
morderngl from `self.program['uniform_variable']`

`vao_content` sending/interpreting data is crucial. 

`vao_content =[(self.vbo, '2f 3f', 'in_vert', 'in_color')]` here after we load the data in `self.vbo` the data has 
`x y r g b` values in order to interpret that `2f 3f` is specified where `2f` takes care of 2 `x y` coordinates and sends
them to `in_vert`, while `3f` sends the `r g b` information to `in_color`.