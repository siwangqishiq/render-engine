#version 330 core

layout(location = 0) in vec2 aPos;
layout(location = 1) in vec2 aTextureUv;

uniform mat4 orthMat;

out vec2 vTexUv;

void main() {
    //vec4 pos = orthMat * vec4(aPos , 0.0 , 1.0) - vec4(1.0 , 1.0 , 0.0 ,0.0);
    gl_Position = orthMat * vec4(aPos , 0.0 , 1.0);
    vTexUv = aTextureUv;
}
