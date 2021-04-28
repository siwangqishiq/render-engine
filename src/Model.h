#pragma once

#include "Material.h"
#include <vector>
#include <fstream>
#include <iostream>

//模型加载H

class Model{
public:
    Model();
    ~Model();
};

//加载并解析mtl 材质文件
std::vector<Material> LoadAndParseMtlFile(std::string mtlFilePath);

