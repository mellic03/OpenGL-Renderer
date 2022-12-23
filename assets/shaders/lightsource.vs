#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aNormal;
layout (location = 2) in vec2 aTexCoords;
layout (location = 3) in vec3 aTangent;

uniform vec3 diffuseColor;
uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

out vec3 fragColor;

void main()
{
  gl_Position = projection * view * model * vec4(aPos, 1.0);
  fragColor = 2 * diffuseColor;
}
