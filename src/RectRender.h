#pragma once

#include "App.h"
#include "Shader.h"

class RectRender : public App{
public:
    virtual void onInit();

    virtual void update(long long deltaTime);

    virtual void onDestory();

private:
    unsigned int vao;
    unsigned int vbo;
    unsigned int ebo;

    unsigned int textureId;
    unsigned int textureId2;

    int locTexture1;
    int locTexture2;

    Shader shader;

    float vertices[4 *(3 + 3 + 2)] = {
        //     ---- 位置 ----       ---- 颜色 ----     - 纹理坐标 -
        0.5f,  0.5f, 0.0f,   1.0f, 0.0f, 0.0f,   1.0f, 1.0f,   // 右上
        0.5f, -0.5f, 0.0f,   0.0f, 1.0f, 0.0f,   1.0f, 0.0f,   // 右下
        -0.5f, -0.5f, 0.0f,   0.0f, 0.0f, 1.0f,   0.0f, 0.0f,   // 左下
        -0.5f,  0.5f, 0.0f,   1.0f, 1.0f, 0.0f,   0.0f, 1.0f    // 左上
    };

    // float vertices[4 *(3 + 3 + 2)] = {
    //     //     ---- 位置 ----       ---- 颜色 ----     - 纹理坐标 -
    //     1.0f,  1.0f, 0.0f,   1.0f, 0.0f, 0.0f,   1.0f, 1.0f,   // 右上
    //     1.0f, -1.0f, 0.0f,   0.0f, 1.0f, 0.0f,   1.0f, 0.0f,   // 右下
    //     -1.0f, -1.0f, 0.0f,   0.0f, 0.0f, 1.0f,   0.0f, 0.0f,   // 左下
    //     -1.0f,  1.0f, 0.0f,   1.0f, 1.0f, 0.0f,   0.0f, 1.0f    // 左上
    // };

    // float vertices[4 * 3] = {
    //     0.5f, 0.5f, 0.0f,   // 右上角
    //     0.5f, -0.5f, 0.0f,  // 右下角
    //     -0.5f, -0.5f, 0.0f, // 左下角
    //     -0.5f, 0.5f, 0.0f   // 左上角
    // };

    unsigned int indices[3 * 2] = { // 
        0, 1, 3, // 第一个三角形
        1, 2, 3  // 第二个三角形
    };

    void buildTexture();
};
