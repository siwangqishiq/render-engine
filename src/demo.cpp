#include "demo.h"

void ShowModel::onInit(){
    objModel = new ObjModel();
    objModel->loadObjFile("assets\\house-hill-small.obj");
    //objModel->loadObjFile("D:\\assets\\untitled.obj");

    // std::cout << "mesh size " << objModel->meshes.size() << std::endl;

    // for(int i = 0 ; i < objModel->meshes.size();i++){
    //     std::shared_ptr<Mesh> mesh = objModel->meshes[i];
    //     std::cout << "mesh material " << mesh->material.name << std::endl;
    //     std::cout << "mesh verteices " << mesh->verteices.size() << std::endl;
    // }//end for i
    //std::cout << "mesh  " << objModel->meshes.size() << std::endl;

    objModel->setupModel();
}

void ShowModel::update(long long deltaTime){
    objModel->render(*this);
}