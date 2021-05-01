#include "Model.h"
#include <fstream>
#include <iostream>
#include <sstream>
#include "StringUtils.h"

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
        std::string content = StringUtils::trim(lineContent);

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
            //std::cout <<"newmtl : " << parts[1] << std::endl;
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
    
    //close file
    infile.close();
    
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


ObjModel::ObjModel(){

}

/**
 * 导入 并读取obj文件
 * 
 * */
int ObjModel::loadObjFile(std::string path){
    std::ifstream infile;
    infile.open(path.data()); 
    if(!infile.is_open()){
        std::cout << path << " open failed !" << std::endl;
        infile.close();
        return -1;
    }

    std::string lineContent;

    materialList.clear();//材质列表清空
    

    //postion
    std::vector<glm::vec3> positionVec;
    positionVec.push_back(glm::vec3(0.0f));

    //texCoord
    std::vector<glm::vec2> texCoordVec;
    texCoordVec.push_back(glm::vec2(0.0f));

    //normal
    std::vector<glm::vec3> normalVec;
    normalVec.push_back(glm::vec3(0.0f));

    while(std::getline(infile , lineContent)){
        std::string content = StringUtils::trim(lineContent);
        if(content.empty() || content[0] == '#'){ //
			continue;
		}

        std::vector<std::string> parts = StringUtils::split(content , " ");
        if(parts.empty()){
            continue;
        }

        const std::string type = parts[0];
    
        //std::cout << parts[0] << std::endl;
        if(type == "mtllib"){//
            std::string foldPath = StringUtils::findDirectoryPath(path);
            mtlFilePath = foldPath +"\\" +parts[1];
            //std::cout << "mtl path " << mtlFilePath << std::endl;
            
            std::vector<Material> mLists = LoadAndParseMtlFile(mtlFilePath);
            materialList.insert(materialList.begin() , mLists.begin() , mLists.end());
            materialList.shrink_to_fit();

            // for(Material &m : materialList){
            //     std::cout << "->" << m.name << std::endl;
            // }
        }else if(type == "o"){
            objectName = parts[1];
            std::cout << "objectName ->" << objectName << std::endl;
        }else if(type == "v"){//顶点坐标
            glm::vec3 position;
            position[0] = std::stof(parts[1]);
            position[1] = std::stof(parts[2]);
            position[2] = std::stof(parts[3]);
            positionVec.push_back(position);
        }else if(type == "vt"){//纹理坐标
            glm::vec2 texCoord;
            texCoord[0] = std::stof(parts[1]);
            texCoord[1] = std::stof(parts[2]);
            texCoordVec.push_back(texCoord);
        }else if(type == "vn"){//法线坐标
            glm::vec3 normal;
            normal[0] = std::stof(parts[1]);
            normal[1] = std::stof(parts[2]);
            normal[2] = std::stof(parts[3]);
            normalVec.push_back(normal);
        }else if(type == "g"){
            ensureMesh();
            curMesh->group = parts[1];
        }else if(type == "usemtl"){
            curMesh = std::make_shared<Mesh>(); 
            meshes.push_back(curMesh);
            
            //std::cout << " meshes.push_back "<< std::endl;

            Material material = findMaterialByName(parts[1]);
            curMesh->material = material;
            std::cout << "material " << curMesh->material.name << std::endl;
        }else if(type == "s"){
            ensureMesh();
            if(parts[1] == "off" || parts[1] == "1"){
                curMesh->smooth = false;
            }else if(parts[1] == "on" || parts[1] == "0"){
                curMesh->smooth = true;
            }else{
                curMesh->smooth = false;
            }
        }else if(type == "f"){
            ensureMesh();
            readObjFileFaceData(parts , positionVec , texCoordVec , normalVec);
        }
    }//end while

    // std::cout << "vertex count = " << positionVec.size() << std::endl;
    // std::cout << "normal count = " << normalVec.size() << std::endl;
    // std::cout << "texCoord count = " << texCoordVec.size() << std::endl;
    // std::cout << "mat name : " << curMesh->material.name << std::endl;

    // if(curMesh != nullptr){
    //     meshes.push_back(curMesh); 
    //     curMesh = nullptr;        
    // }
    
    infile.close();
    return 0;
}

std::shared_ptr<Mesh> ObjModel::ensureMesh(){
    if(curMesh == nullptr){
        curMesh = std::make_shared<Mesh>();
    }
    
    return curMesh;
}

//查找材质列表
Material ObjModel::findMaterialByName(std::string &materialName){
    Material result;
    for(Material &m : materialList){
        if(m.name == materialName){
            result = m;
            break;
        }
    }//end for each
    //std::cout << "Not found material : " << materialName << std::endl;
    return result;
}

//
void ObjModel::readObjFileFaceData(std::vector<std::string> &parts, 
    std::vector<glm::vec3> &positionVec, 
    std::vector<glm::vec2> &texCoordVec, 
    std::vector<glm::vec3> &normalVec)
{
    //std::cout << "parts[1] = " << parts[1] << std::endl;
    for(int i = 1 ;i <= 3;i++){
        Vertex vertex = readObjFileVertexAttributeData(parts[i] , positionVec , texCoordVec , normalVec);
        curMesh->verteices.push_back(vertex);
    }//end for i
}

//顶点数据读取
Vertex ObjModel::readObjFileVertexAttributeData(std::string &vertexStr, 
                        std::vector<glm::vec3> &positionVec, 
                        std::vector<glm::vec2> &texCoordVec,
                        std::vector<glm::vec3> &normalVec)
{
    Vertex vertex;
    std::string subStr = "";
    const char *cStr = vertexStr.c_str();
    int index = 0;
    int step = 0;
    while(index < vertexStr.length()){
        if(cStr[index] == '/'){  
            if(step == 0){//读取顶点位置
                // std::cout << subStr << std::endl;
                if(subStr.empty()){
                    vertex.position = glm::vec3(0);
                }else{
                    int indexValue = std::stoi(subStr);
                    //vertex.position = positionVec.at(indexValue);
                    vertex.position = positionVec[indexValue];
                }

                step++;
            }else if(step == 1){//读取纹理坐标
                // std::cout << subStr << std::endl;
                if(subStr.empty()){
                    vertex.texCoord = glm::vec2(0);
                }else{
                    int indexValue = std::stoi(subStr);
                    vertex.texCoord = texCoordVec[indexValue];
                }
                step++;
            }else if(step == 2){//读取法线坐标
                //std::cout << subStr << std::endl;
                step++;
            }
            subStr = "";
        }else{
            subStr += cStr[index];
        }
        index++;
    }//end while
    if(step == 2){
        if(subStr.empty()){
            vertex.normal = glm::vec3(0);
        }else{
            int indexValue = std::stoi(subStr);
            vertex.normal = normalVec[indexValue];
        }
    }
    
    //std::cout << std::endl;

    return vertex;
}

void ObjModel::setupModel(){
    for(std::shared_ptr<Mesh> &pMesh : meshes){
        pMesh->init();
    }//end for each
}

void ObjModel::render(Scene &scene){
    for(std::shared_ptr<Mesh> &pMesh : meshes){
        pMesh->render(scene);
    }//end for each
}

void Mesh::init(){
    //std::cout << "mesh name = " << this->group << " init " << std::endl;

    
}

void Mesh::render(Scene &scene){
    std::cout << "mesh render = " << this->group << " render " << std::endl;
}



