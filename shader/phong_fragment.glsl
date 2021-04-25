#version 330 core

in vec3 vWorldPos;
in vec3 vNormal;
in vec2 vTexCoord;

struct Material{
    vec3 diffuse;//漫反射系数
    vec3 specular;//镜面反射系数
    
    float shininess; //材质粗糙度
};

struct LightDir{ //平行光光源
    float ambientWeight;//环境光权值
    float diffuseWeight;//
    float specularWeight;

    vec3 lightColor;//光颜色
    vec3 lightDirectional; //平行光方向
};

uniform Material material;
uniform LightDir light;
uniform vec3 cameraPos;//观察者位置

out vec4 fragColor;

void main(){
    vec3 ambient = light.lightColor * light.ambientWeight;
  	
    // diffuse 
    // vec3 normal = normalize(vNormal);
    // vec3 lightDir = -normalize(light.lightDirectional);
    // float diff = max(dot(normal, lightDir), 0.0);
    // vec3 diffuse = light.diffuse * (diff * material.diffuse);
    vec3 diffuse = vec3(1 ,0 ,0);
    
    // // specular
    // vec3 cameraDir = normalize(cameraPos - vWorldPos);
    // vec3 reflectDir = reflect(-lightDir, normal);  
    // float spec = pow(max(dot(cameraDir, reflectDir), 0.0), material.shininess);
    // vec3 specular = light.specular * (spec * material.specular);
    vec3 specular = vec3(0 ,0 ,0);  
    
    vec3 result = ambient + diffuse + specular;
    fragColor = vec4(result, 1.0);
}
