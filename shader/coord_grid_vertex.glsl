#version 330 core

layout(location = 0) in vec3 aPos;
layout(location = 1) in vec3 aColor;

uniform mat4 modelMat;
uniform mat4 viewMat;
uniform mat4 projMat;

out vec3 vColor;

void main() {
    gl_Position = projMat * viewMat * modelMat * vec4(aPos, 1.0);
    vColor = aColor;
}
