#pragma once

#include "Material.h"
#include <vector>
#include <fstream>
#include <iostream>
#include <memory>

struct Vertex{
    float x;
    float y;
    float z;
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

//obj模型  负责模型的导入与解析
class ObjModel:public Model{

};

