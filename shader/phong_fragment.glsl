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

struct LightPoint{//点光源
    vec3 lightColor;//光颜色
    vec3 position;//点光源位置

    float ambientWeight;//环境光权值
    float diffuseWeight;//
    float specularWeight;

    //衰减方程参数
    float k0;
    float k1;
    float k2;
};


uniform bool uDirectionalLightEnable;
uniform bool uPointLightEnable;

uniform Material material;
uniform LightDirectional light;
uniform LightPoint uPointLight;
uniform vec3 cameraPos;//观察者位置

out vec4 fragColor;

vec3 computeDiretionalLight(LightDirectional light){
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

    return result;
}

void main(){
    vec3 result;

    if(uDirectionalLightEnable){
        result += computeDiretionalLight(light);
    }
    
    if(uPointLightEnable){
        
    }
    
    fragColor = vec4(result, 1.0);
}
