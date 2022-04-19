#version 330 core

layout(location = 0) in vec3 aPos;
layout(location = 1) in vec3 aColor;
layout(location = 2) in vec2 aTexCoord;

out vec2 UV;
out vec3 fragmentColor;

uniform mat4 MVP;
uniform bool isColorGrey;
uniform bool isCyl;

vec2 calcul_uv() {
    float u, v;
    u = aPos.x + aPos.z + aPos.x;
    v = aPos.y + aPos.y + aPos.z;
    return (vec2(u, v));
}

void main() {
	gl_Position =  MVP * vec4(aPos, 1);
    if (!isColorGrey)
        fragmentColor = aColor;
    else {
        float grey = dot(aColor.rgb, vec3(0.299, 0.310, 0.114));
	    fragmentColor = vec3(grey);
    }
    if (isCyl)
        UV = aTexCoord;
    else
        UV = calcul_uv();
}
