#include "fbo.h"
#include <glad/glad.h>
#include <iostream>

void OffScreenTexture::init(){
    mShader = Shader::buildGPUProgramFromFile("rect_render_vertex.glsl","rect_render_frag.glsl");
    TextureInfo info = mContext->loadTexture("a_test.png");
    this->textureId = info.textureId;
    TextureInfo otherInfo = mContext->loadTexture("songxia.jpg");
    this->textureId2 = otherInfo.textureId;

    //std::cout << "textureId = " << textureId << " textureId2 = " << textureId2 << std::endl;

    glGenVertexArrays(1 , &vao);
    glGenBuffers(1 , &vbo);
    glGenBuffers(1 , &ebo);

    glBindVertexArray(vao);
    glBindBuffer(GL_ARRAY_BUFFER , vbo);
    glBufferData(GL_ARRAY_BUFFER , sizeof(vertices) , vertices , GL_STATIC_DRAW);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER , sizeof(indices) , indices , GL_STATIC_DRAW);

    //set vertex attr
    glVertexAttribPointer(0 , 3 , GL_FLOAT , GL_FALSE , 
            8 * sizeof(float) , (void *)(0 * sizeof(float)));
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(1 , 3 , GL_FLOAT , GL_FALSE , 
            8 * sizeof(float) , (void *)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    glVertexAttribPointer(2 , 2 , GL_FLOAT , GL_FALSE , 
            8 * sizeof(float) , (void *)(6 * sizeof(float)));
    glEnableVertexAttribArray(2);
    glBindVertexArray(0);

    // frame buffer init
    glGenFramebuffers(1 , &mFrameBuffer);
    glBindFramebuffer(GL_FRAMEBUFFER , mFrameBuffer);

    glGenTextures(1 , &mTextureId);
    glBindTexture(GL_TEXTURE_2D , mTextureId);
    glTexImage2D(GL_TEXTURE_2D , 0 , GL_RGBA , 
        mContext->screenWidth , mContext->screenHeight , 0, GL_RGBA, 
        GL_UNSIGNED_BYTE , nullptr);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR );
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glFramebufferTexture2D(GL_FRAMEBUFFER , GL_COLOR_ATTACHMENT0 , 
            GL_TEXTURE_2D , mTextureId , 0);
    glBindTexture(GL_TEXTURE_2D , 0);

    glGenRenderbuffers(1 , &mRenderBufferId);
    glBindRenderbuffer(GL_RENDERBUFFER , mRenderBufferId);
    glRenderbufferStorage(GL_RENDERBUFFER , GL_DEPTH24_STENCIL8 , 
        mContext->screenWidth , mContext->screenHeight);
    glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, 
        GL_RENDERBUFFER , mRenderBufferId);

    glBindFramebuffer(GL_FRAMEBUFFER , 0);
}

void OffScreenTexture::render(){
    glBindFramebuffer(GL_FRAMEBUFFER , mFrameBuffer);
    if(glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE){
        glBindFramebuffer(GL_FRAMEBUFFER , 0);
        std::cout << "frame buffer status error !" << std::endl;
        return;
    }

    glEnable(GL_DEPTH_TEST);
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    mShader.useShader();

    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D , this->textureId);
    mShader.setUniformInt("imageTexture",0);

    glActiveTexture(GL_TEXTURE1);
    glBindTexture(GL_TEXTURE_2D , this->textureId2);
    mShader.setUniformInt("image2Texture",1);
    
    glBindVertexArray(vao);
    glDrawElements(GL_TRIANGLES , 6 , GL_UNSIGNED_INT , 0);
    glBindVertexArray(0);

    glBindTexture(GL_TEXTURE_2D , 0);
    glBindFramebuffer(GL_FRAMEBUFFER , 0);
}

void OffScreenTexture::free(){
    glDeleteFramebuffers(1 , &mFrameBuffer);
    glDeleteTextures(1 , &mTextureId);
    glDeleteRenderbuffers(1 , &mRenderBufferId);

    mTextureId = -1;
}

unsigned int OffScreenTexture::getTextureId(){
    return mTextureId;
}