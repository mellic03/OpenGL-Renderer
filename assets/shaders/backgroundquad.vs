#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 2) in vec2 aTexCoords;

void main()
{
  gl_Position = vec4(aPos.x/2, aPos.y/2, 0.9, 1.0); 
}