#pragma once

#include "config.h"
#include "Scene.h"
#include "Model.h"

class CubeScene :public Scene {
private:
    CoordinateGrid *grid;

public:
    virtual void onInit(){
        grid= new CoordinateGrid();
        grid->init();
    }

    virtual void update(long long deltaTime){
        grid->render(*camera);
    }

    virtual void onDestory(){
        if(grid != nullptr){
            delete grid;
            grid = nullptr;
        }
    }
};

class ShowModel : public Scene{
private:
    ObjModel *objModel;
public:
    virtual void onInit(){
        objModel = new ObjModel();
        objModel->loadObjFile("E:\\gits\\render-engine\\assets\\house-hill-small.obj");
    }
};
