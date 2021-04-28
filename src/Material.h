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

    float shininess; //材质表面粗糙程度

    std::string diffuseMapFile;//漫反射文件名称
    std::string bumpFile;//bumpfile
    std::string name;//材质名称

    float pticalDensity;//材质表面光密度
    
    int illum;//光照类型
    float factor;//物体融入背景的数量
};
