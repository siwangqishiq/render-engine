#pragma once

#include "App.h"
#include "Camera.h"
#include <memory>
#include "CoordinateGrid.h"

//场景 自动带有Camera
class Scene : public App{
protected:
    std::shared_ptr<Camera> camera;
public:
    Scene();

    ~Scene();

    //摄像机移动速度
    float moveSpeed =0.01f;

    //构建自定义Camera
    virtual std::shared_ptr<Camera> buildCamera();

    //重新设置Camera
    void setCamera(std::shared_ptr<Camera> newCamera);

    virtual void processInput(GLFWwindow *window);
};

class CubeScene :public Scene {
private:
    CoordinateGrid *grid;

public:
    virtual void onInit();
    virtual void update(long long deltaTime);
    virtual void onDestory();
};