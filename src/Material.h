#pragma once

#include <glm/glm.hpp>
#include <string>

//材质
class Material{
public:
    enum MaterialEnum{
        Normal,
        Plastic,//塑料
        Gold,//金属
    };
    static Material buildMaterial(MaterialEnum materialType);

    Material();

    Material(glm::vec3 _diffuse , glm::vec3 _specular , float _shininess);

    glm::vec3 ambient; 
    glm::vec3 diffuse; //漫反射颜色
    glm::vec3 specular; //镜面反射颜色
    glm::vec3 emitter;

    float shininess = 1.0f; //材质表面粗糙程度

    std::string diffuseMapFile = "";//漫反射文件名称
    std::string bumpFile = "";//bumpfile
    std::string name = "";//材质名称

    float pticalDensity = 1.0f;//材质表面光密度
    
    int illum = 2;//光照类型
    float factor = 0.0f;//物体融入背景的数量


    //赋值运算符
    Material& operator=(const Material &m){
        this->ambient = m.ambient;
        this->diffuse = m.diffuse;
        this->specular = m.specular;
        this->emitter = m.emitter;
        
        this->shininess = m.shininess;

        this->diffuseMapFile = m.diffuseMapFile;
        this->bumpFile = m.bumpFile;
        this->name = m.name;

        this->pticalDensity = m.pticalDensity;
        this->illum = m.illum;
        this->factor = m.factor;

        return *this;
    }
};
