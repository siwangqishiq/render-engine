#version 330 core

in vec3 vWorldPos;
in vec3 vNormal;
in vec2 vTexCoord;

struct Material{
    vec3 diffuse;//漫反射系数
    vec3 specular;//镜面反射系数
    
    float shininess; //材质粗糙度
};

struct LightDirectional{ //平行光光源
    float ambientWeight;//环境光权值
    float diffuseWeight;//
    float specularWeight;

    vec3 lightColor;//光颜色
    vec3 lightDir; //平行光方向
};

uniform Material material;
uniform LightDirectional light;
uniform vec3 cameraPos;//观察者位置

out vec4 fragColor;

void main(){
    vec3 result;

    vec3 ambient = light.lightColor * light.ambientWeight;
    result += ambient;

    vec3 normal = normalize(vNormal);
    // diffuse 
    vec3 lightDir = -normalize(light.lightDir);
    float diff = max(dot(normal, lightDir), 0.0);
    vec3 diffuse = light.diffuseWeight * (diff * material.diffuse);
    result += diffuse;
    
    //specular
    vec3 cameraDir = normalize(cameraPos - vWorldPos);
    vec3 reflectDir = reflect(-lightDir, normal);  
    float spec = pow(max(dot(cameraDir, reflectDir), 0.0), material.shininess);
    
    vec3 specular = light.specularWeight * (spec * material.specular);
    specular = vec3(spec , spec , spec);
    result += specular;
    
    fragColor = vec4(result, 1.0);
}
