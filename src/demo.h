#pragma once

#include "config.h"
#include "Scene.h"
#include "Model.h"
#include "Text.h"
#include "fbo.h"

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
    virtual void onInit();

    virtual void update(long long deltaTime);
};

class FontTest : public Scene{

public:
    std::shared_ptr<Text> text;

    virtual void onInit();

    virtual void update(long long deltaTime); 

    virtual void onDestory();
};

class FboTest : public Scene {
public :
    std::shared_ptr<OffScreenTexture> mOffScreenTexture;

    virtual void onInit();

    virtual void update(long long deltaTime); 

    virtual void onDestory();
};
