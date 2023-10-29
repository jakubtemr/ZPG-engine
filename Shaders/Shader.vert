#version 400

layout(location=0) in vec3 vp;
layout(location=1) in vec3 normal;
layout(location=2) in vec2 _uv;

out vec2 uv;
out vec4 ex_WorldPos;
out vec3 ex_WorldNormal;

uniform mat4 modelMatrix;
uniform mat4 viewMatrix;
uniform mat4 projectionMatrix;

void main () {
 uv = _uv;
 gl_Position = (projectionMatrix * viewMatrix * modelMatrix) * vec4 (vp, 1.0);
 ex_WorldPos = modelMatrix * vec4(vp, 1.0);
 ex_WorldNormal = transpose(inverse(mat3(modelMatrix))) * normal; // Normal matrix
};