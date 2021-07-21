#version 330 core

in vec2 vTexUv;

uniform sampler2D fontTexture;
uniform vec4 fontColor;

out vec4 fragColor;

void main(){
    vec4 sampled = vec4(1.0, 1.0, 1.0, texture(fontTexture, vTexUv).r);
    fragColor = fontColor * sampled;

    //fragColor = vec4(1.0,0.0,0.0,1.0);
}
