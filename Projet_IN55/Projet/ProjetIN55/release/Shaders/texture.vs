#version 140


uniform mat4 mvp;
in vec2 texC;
in vec3 position;
out vec2 ftexC;
void main()
{
  gl_Position = mvp * vec4( position, 1.0f );
  ftexC = texC;
}
