#version 330 core

in vec3 vColor;
in vec2 vTexCoord;

uniform sampler2D imageTexture;
uniform sampler2D image2Texture;

out vec4 fragColor;

void main(){
    // fragColor = vec4(vColor, 1.0f);
    //fragColor = vec4(1.0 , 1.0 , 0.0 , 1.0);
    vec4 color1 = texture(imageTexture , vTexCoord);
    vec4 color2 = texture(image2Texture , vTexCoord);
    
    fragColor = mix(color1 , color2 , 0.8);
    // fragColor = vec4(0.0 , 0.0 , 1.0 , 1.0);

    // fragColor = vec4(color2);
}
