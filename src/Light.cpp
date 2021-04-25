#include "Light.h"

DirectionalLight::DirectionalLight(glm::vec3 _directional , glm::vec3 _lightColor){
    this->directional = _directional;
    this->lightColor = _lightColor;
}

DirectionalLight::~DirectionalLight(){
    
}

