#version 330 core

in vec2 vTexCoord;

uniform sampler2D imageTexture;

out vec4 fragColor;

void main(){
    //fragColor = vec4(vColor, 1.0f);
    //fragColor = vec4(1.0 , 1.0 , 0.0 , 1.0);
    //fragColor = vec4(1.0 , 0.0 , 0.0 , 1.0);
    vec4 color1 = texture(imageTexture , vTexCoord);
    fragColor = color1;
}
