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
    result += specular;

    return result;
}

vec3 computePointLight(LightPoint lightPoint){
    vec3 result;
    
    float distance = length(lightPoint.position - vWorldPos);
    float strength = 1.0/(lightPoint.k0 + lightPoint.k1 * distance + lightPoint.k2 * distance * distance);

    vec3 ambient = lightPoint.lightColor * lightPoint.ambientWeight;
    result += strength * ambient;

    vec3 normal = normalize(vNormal);
    // diffuse 

    vec3 lightDir = -normalize(vWorldPos - lightPoint.position);
    float diff = max(dot(normal, lightDir), 0.0);
    vec3 diffuse = lightPoint.diffuseWeight * (diff * material.diffuse);
    result += (strength * diffuse);
    
    //specular
    vec3 cameraDir = normalize(cameraPos - vWorldPos);
    vec3 reflectDir = reflect(-lightDir, normal);  
    float spec = pow(max(dot(cameraDir, reflectDir), 0.0), material.shininess);
    vec3 specular = lightPoint.specularWeight * (spec * material.specular);
    result += (strength * specular);
    //result = vec3(strength * specular);
    return result;
}

void main(){
    vec3 result = vec3(0 , 0, 0);

    if(uDirectionalLightEnable){
        result += computeDiretionalLight(light);
    }
    
    if(uPointLightEnable){
        result += computePointLight(uPointLight);
    }
    
    fragColor = vec4(result, 1.0);
}
