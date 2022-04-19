#version 330 core

in vec3 fragmentColor;
in vec2 UV;

out vec3 color;

uniform int isTex;
uniform float transition;
uniform sampler2D myTextureSampler;

void main() {
  if (isTex == 1)
    color = mix(fragmentColor, texture(myTextureSampler, UV).rgb, transition);
  if (isTex == 2)
    color = mix(texture(myTextureSampler, UV).rgb, fragmentColor, transition);
  if (isTex == 0)
    color = fragmentColor;
}
