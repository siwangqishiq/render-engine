#include "Model.h"
#include <fstream>
#include <iostream>

Model::Model(){

}

Model::~Model(){

}

//加载并解析mtl文件 返回解析出的材质列表
std::vector<Material> LoadAndParseMtlFile(std::string mtlFilePath) {
    std::vector<Material> materialVec;
    std::ifstream infile;
    infile.open(mtlFilePath.data()); 
    if(!infile.is_open()){
        std::cout << mtlFilePath << "open failed !" << std::endl;
        infile.close();
        return materialVec;
    }

    std::string lineContent;
    while(std::getline(infile , lineContent)){
        std::cout << lineContent << std::endl;
    }//end while
    
    return materialVec;
}