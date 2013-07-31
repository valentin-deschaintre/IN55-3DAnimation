#version 140


in vec2 ftexC;
uniform sampler2D texId;
out vec4 fragColor;


void main()
{
  fragColor =  texture(texId, ftexC);
  //fragColor = vec4(0.5f,0.5f,0.5f,1.0f);
  }
