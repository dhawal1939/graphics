#version 330                                                                  
                                                                              
layout (location = 0) in vec3 pos;											  
                                                                              
void main()                                                                   
{                                                                             
    gl_Position = vec4(.4 *pos.x, .4*pos.y, .4*pos.z, 1.0);				  
}