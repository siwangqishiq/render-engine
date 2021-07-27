#pragma once

#include "Shader.h"
#include "App.h"

class OffScreenTexture{
public:
    OffScreenTexture(App *context) : mContext(context){
    }

    virtual void init();

    virtual void render();

    virtual void free();

    virtual unsigned int getTextureId();

private:
    unsigned int mFrameBuffer;

    Shader mShader;

    App *mContext;

    unsigned int mTextureId = -1;
    unsigned int mRenderBufferId = -1;

    unsigned int vao;
    unsigned int vbo;
    unsigned int ebo;

    unsigned int textureId;
    unsigned int textureId2;
    
    float vertices[4 *(3 + 3 + 2)] = {
        //     ---- 位置 ----       ---- 颜色 ----     - 纹理坐标 -
        0.5f,  0.5f, 0.0f,   1.0f, 0.0f, 0.0f,   1.0f, 1.0f,   // 右上
        0.5f, -0.5f, 0.0f,   0.0f, 1.0f, 0.0f,   1.0f, 0.0f,   // 右下
        -0.5f, -0.5f, 0.0f,   0.0f, 0.0f, 1.0f,   0.0f, 0.0f,   // 左下
        -0.5f,  0.5f, 0.0f,   1.0f, 1.0f, 0.0f,   0.0f, 1.0f    // 左上
    };

    unsigned int indices[3 * 2] = { // 
        0, 1, 3, // 第一个三角形
        1, 2, 3  // 第二个三角形
    };
};

