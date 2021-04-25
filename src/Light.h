#pragma once

#include <string>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

//光照类型 基类
class BaseLight{
public:
    glm::vec3 lightColor; //光线颜色
    std::string name;
};

//平行光光源
class DirectionalLight : public BaseLight{
public:
    DirectionalLight(glm::vec3 _directional , glm::vec3 _lightColor = glm::vec3(1 , 1, 1));
    ~DirectionalLight();

    glm::vec3 directional; //平行光方向
    
    float ambientWeight = 0.2f;//环境光占比
    float diffuseWeight = 0.5f;//漫反射占比
    float specularWeight = 1.0f;//镜面反射
};