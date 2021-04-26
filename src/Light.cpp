#include "Light.h"

DirectionalLight::DirectionalLight(glm::vec3 _directional , glm::vec3 _lightColor){
    this->directional = _directional;
    this->lightColor = _lightColor;
}

DirectionalLight::~DirectionalLight(){
    
}

PointLight::PointLight(glm::vec3 _position , glm::vec3 _lightColor){
    this->position = _position;
    this->lightColor = _lightColor;
}

PointLight::~PointLight(){

}

