#include "Light.h"

DirectionalLight::DirectionalLight(glm::vec3 _directional , glm::vec3 _lightColor = glm::vec3(1 , 1, 1)){
    this->directional = _directional;
    this->lightColor = _lightColor;
}

DirectionalLight::~DirectionalLight(){
    
}

