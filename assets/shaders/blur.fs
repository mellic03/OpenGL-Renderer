#version 330 core

in vec2 TexCoords;

out vec4 FragColor;

uniform sampler2D image;
uniform float texel_size;
uniform float x_strength;
uniform float y_strength;

uniform bool horizontal;
float weight[5] = float[] (0.227027, 0.1945946, 0.1216216, 0.054054, 0.016216);

void main()
{             
  vec2 tex_offset = texel_size / textureSize(image, 0); // gets size of single texel
  vec3 result = texture(image, TexCoords).rgb * weight[0]; // current fragment's contribution
  if(horizontal)
  {
    for(int i = 1; i < 5; ++i)
    {
      result += texture(image, TexCoords + vec2(tex_offset.x * i * x_strength, 0.0)).rgb * weight[i];
      result += texture(image, TexCoords - vec2(tex_offset.x * i * x_strength, 0.0)).rgb * weight[i];
    }
  }
  else
  {
    for(int i = 1; i < 5; ++i)
    {
      result += texture(image, TexCoords + vec2(0.0, tex_offset.y * i * y_strength)).rgb * weight[i];
      result += texture(image, TexCoords - vec2(0.0, tex_offset.y * i * y_strength)).rgb * weight[i];
    }
  }
  FragColor = vec4(result, 1.0);
}