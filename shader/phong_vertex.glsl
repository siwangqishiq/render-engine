#version 330 core

layout(location = 0) in vec3 aPos;
layout(location = 1) in vec3 aNormal;
layout(location = 2) in vec2 aTexCoord;

uniform mat4 modelMat;
uniform mat4 viewMat;
uniform mat4 projMat;

out vec3 vWorldPos;
out vec3 vNormal;
out vec2 vTexCoord;

void main() {
    gl_Position = projMat * viewMat * modelMat * vec4(aPos, 1.0);
    vWorldPos = (modelMat * vec4(aPos, 1.0)).xyz;
    vNormal = (transpose(inverse(modelMat)) * vec4(aNormal , 1.0)).xyz;
    vTexCoord = aTexCoord;
}
