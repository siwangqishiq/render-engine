#include "demo.h"

void ShowModel::onInit(){
    objModel = new ObjModel();
    objModel->loadObjFile("E:\\assets\\model\\lapu\\obj\\lap.obj");
    //objModel->loadObjFile("D:\\assets\\untitled.obj");
    
    // std::cout << "mesh size " << objModel->meshes.size() << std::endl;

    // for(int i = 0 ; i < objModel->meshes.size();i++){
    //     std::shared_ptr<Mesh> mesh = objModel->meshes[i];
    //     std::cout << "mesh material " << mesh->material.name << std::endl;
    //     std::cout << "mesh verteices " << mesh->verteices.size() << std::endl;
    // }//end for i
    //std::cout << "mesh  " << objModel->meshes.size() << std::endl;

    objModel->setupModel(*this);
}

void ShowModel::update(long long deltaTime){
    objModel->render(*this);
}

void FontTest::onInit(){
    text = std::make_shared<Text>(screenWidth , screenHeight);
    text->init();
}

void FontTest::update(long long deltaTime){
    //std::cout << "font text update" << std::endl;
    text->renderText(100.0f , 300.0f , L"你好 世界 魑魅魍魉 日语 さようなら。" , 
        glm::vec4(1.0f , 1.0f , 0.0f , 1.0f));
}

void FontTest::onDestory(){
    text->free();
}