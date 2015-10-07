#version 430

layout (location = 0) in vec3 position;
layout (location = 1) in vec2 vecTexUV;
layout (location = 2) in vec3 vecNorm;

uniform mat4 worldMatrix;
out vec2 fragTexUV;
out vec3 fragPos;
out vec3 fragNorm;

void main()
{
	gl_Position = worldMatrix * vec4(position, 1);
	fragTexUV = vecTexUV;
	fragPos = gl_Position.xyz;
	fragNorm = normalize(vecNorm);
}