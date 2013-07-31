#version 140


uniform mat4 mvp;

in vec3 position;
in vec3 color;

out vec3 fColor;


void main()
{
  gl_Position = mvp * vec4(position, 1.0f);

  fColor = color;
}
