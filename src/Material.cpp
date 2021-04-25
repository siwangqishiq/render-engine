#include "Material.h"

Material Material::buildMaterial(MaterialEnum type){
    switch(type){
        case Normal://普通
            return Material(glm::vec3(1.0f, 0.5f, 0.31f) , glm::vec3(0.5f, 0.5f, 0.5f) , 32.0f);
        case Plastic://塑料材质
            return Material(glm::vec3(0.0f, 1.0f, 0.0f) , glm::vec3(0.5f, 0.5f, 0.5f) , 32.0f);
        default:
           return Material(glm::vec3(1.0f, 0.5f, 0.31f) , glm::vec3(0.5f, 0.5f, 0.5f) , 32.0f);
    }//end switch
}

Material::Material(){
    this->diffuse = glm::vec3(0);
    this->specular = glm::vec3(0);
    this->shininess = 1.0f;
}

Material::Material(glm::vec3 _diffuse , glm::vec3 _specular , float _shininess) {
    this->diffuse = _diffuse;
    this->specular = _specular;
    this->shininess = _shininess;
}