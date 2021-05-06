#pragma once

#include "Material.h"
#include <vector>
#include <fstream>
#include <iostream>
#include <memory>
#include "Scene.h"

//顶点
struct Vertex{
    glm::vec3 position;//位置
    glm::vec2 texCoord;//纹理坐标
    glm::vec3 normal;//法线
};


//模型加载H
class Model{
public:
    Model();
    ~Model();

    //加载并解析mtl 材质文件
    static std::vector<Material> LoadAndParseMtlFile(std::string mtlFilePath);

    //解析map格式参数
    static void parseObjFileMapCommand(std::shared_ptr<Material> material , std::vector<std::string> &parts ,std::string &key);
};

//网格
class Mesh{
public: 
    std::vector<Vertex> verteices;//顶点数据
    
    std::string group;//顶点集合名称
    Material material;//网格材质
    bool smooth = false;//是否光滑处理

    //初始化网格资源
    void init();

    //渲染网格
    void render(Scene &scene);
private:
    Shader shader;

    unsigned int vao;
    unsigned int vbo;
};

//obj模型  负责模型的导入与解析
class ObjModel:public Model{
public:
    ObjModel();

    //从文件中导入模型数据
    int loadObjFile(std::string filepath);

    //网格
    std::vector<std::shared_ptr<Mesh>> meshes;

    //装载模型  完成初始化 纹理载入等
    void setupModel();

    //渲染模型
    void render(Scene &scene);

private:
    unsigned int vao;
    unsigned int vbo;

    std::shared_ptr<Mesh> curMesh = nullptr;//当前操作网格

    std::string objectName;//物体名称

    std::string mtlFilePath;//材质描述文件路径

    std::vector<Material> materialList; //与模型关联的材质列表

    //根据材质名称找到材质类
    Material findMaterialByName(std::string &materialName);

    std::shared_ptr<Mesh> ensureMesh();

    //读取面数据
    void readObjFileFaceData(std::vector<std::string> &parts, 
                        std::vector<glm::vec3> &positionVec, 
                        std::vector<glm::vec2> &texCoordVec,
                        std::vector<glm::vec3> &normalVec);


    //顶点数据读取
    Vertex readObjFileVertexAttributeData(std::string &vertexStr, 
                        std::vector<glm::vec3> &positionVec, 
                        std::vector<glm::vec2> &texCoordVec,
                        std::vector<glm::vec3> &normalVec);
};

