#version 330 core

in vec2 vTexCoord;

uniform sampler2D imageTexture;

out vec4 fragColor;

void main(){
    // fragColor = vec4(1.0 ,0.0 , 1.0, 1.0);
    fragColor = texture(imageTexture , vTexCoord);
    // fragColor = vec4(vTexCoord.x , vTexCoord.y , 0.0 , 1.0);
}
