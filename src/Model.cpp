#include "Model.h"
#include <fstream>
#include <iostream>
#include <sstream>

Model::Model(){

}

Model::~Model(){

}

std::vector<Material> Model::LoadAndParseMtlFile(std::string mtlFilePath){
    std::vector<Material> materialVec;
    std::ifstream infile;
    infile.open(mtlFilePath.data()); 
    if(!infile.is_open()){
        std::cout << mtlFilePath << "open failed !" << std::endl;
        infile.close();
        return materialVec;
    }

    std::string lineContent;
    std::shared_ptr<Material> curMaterial = nullptr;
    while(std::getline(infile , lineContent)){
        //std::cout << lineContent << std::endl;
        std::string content = trim(lineContent);

        if(content.empty() || content[0] == '#'){ //
			continue;
		}

        std::vector<std::string> parts;
        std::istringstream in(content);
		std::string tmp;
		while(in >> tmp){
			parts.push_back(tmp);
		}//end while

        std::string type = parts[0];
        //std::cout << type << std::endl;

        if(type == "newmtl"){ //新材质 newmtl
            std::cout << parts[1] << std::endl;
            if(curMaterial != nullptr){
                materialVec.push_back(*curMaterial);
            }
            curMaterial = std::make_shared<Material>();
            curMaterial->name = parts[1];
        }else{
            if(curMaterial == nullptr){
                std::cout << "error obj file! exit" << std::endl;
                break;
            } 

            //std::cout << "type =" << type << std::endl;
            if(type == "Ns"){//shininess参数
                curMaterial->shininess = std::stof(parts[1]);
            }else if(type == "Ka"){//环境光系数Ka
                curMaterial->ambient[0] = std::stof(parts[1]);
                curMaterial->ambient[1] = std::stof(parts[2]);
                curMaterial->ambient[2] = std::stof(parts[3]);
            }else if(type == "Kd"){//漫反射系数 Kd
                curMaterial->diffuse[0] = std::stof(parts[1]);
                curMaterial->diffuse[1] = std::stof(parts[2]);
                curMaterial->diffuse[2] = std::stof(parts[3]);
            }else if(type == "Ks"){//镜面反射系数 Ks
                curMaterial->specular[0] = std::stof(parts[1]);
                curMaterial->specular[1] = std::stof(parts[2]);
                curMaterial->specular[2] = std::stof(parts[3]);
            }else if(type == "Ke"){//发光系数 Ke
                curMaterial->emitter[0] = std::stof(parts[1]);
                curMaterial->emitter[1] = std::stof(parts[2]);
                curMaterial->emitter[2] = std::stof(parts[3]);
            }else if(type == "map_Kd"){ //漫反射贴图文件路径
                parseObjFileMapCommand(curMaterial , parts , type);
            }else if(type == "map_Bump"){//法线贴图路径
                parseObjFileMapCommand(curMaterial , parts , type);
            }else if(type == "Ni"){ //NI
                curMaterial->pticalDensity = std::stof(parts[1]);
            }else if(type == "illum"){//illum
                curMaterial->illum = std::stoi(parts[1]);
            }else if(type == "d"){//d
                curMaterial->factor = std::stof(parts[1]);
            }
        } 
    }//end while

    if(curMaterial != nullptr){
        materialVec.push_back(*curMaterial);
    }
    
    return materialVec;
}

//解析Map命令行
void Model::parseObjFileMapCommand(std::shared_ptr<Material> material , std::vector<std::string> &params , 
            std::string &key){
    int index = 1;
    while(params[index][0] == '-'){
        index += 4;
    }//end while
    //std::cout << "index " << index <<std::endl;
    std::string filepath = params[index];
    //std::cout << "file = " << filepath << std::endl;
    if(key == "map_Kd"){
        material->diffuseMapFile = filepath;
    }else if(key == "map_Bump"){
        material->bumpFile = filepath;
    }
}