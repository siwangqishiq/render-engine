#include "RectRender.h"

void RectRender::onInit(){
    // this->shaderProgram = CreateGPUProgramFromFile("shader/rect_render_vertex.glsl" , "shader/rect_render_frag.glsl");
    shader = Shader::buildGPUProgramFromFile("rect_render_vertex.glsl","rect_render_frag.glsl");

    // this->locTexture1 = glGetUniformLocation(shaderProgram , "imageTexture");
    // this->locTexture2 = glGetUniformLocation(shaderProgram , "image2Texture");


    buildTexture();

    glGenVertexArrays(1 , &vao);
    glGenBuffers(1 , &vbo);
    glGenBuffers(1 , &ebo);

    glBindVertexArray(vao);

    
    glBindBuffer(GL_ARRAY_BUFFER , vbo);
    glBufferData(GL_ARRAY_BUFFER , sizeof(vertices) , vertices , GL_STATIC_DRAW);
   
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER , sizeof(indices) , indices , GL_STATIC_DRAW);

    //set vertex attr
    glVertexAttribPointer(0 , 3 , GL_FLOAT , GL_FALSE , 8 * sizeof(float) , (void *)(0 * sizeof(float)));
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(1 , 3 , GL_FLOAT , GL_FALSE , 8 * sizeof(float) , (void *)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    glVertexAttribPointer(2 , 2 , GL_FLOAT , GL_FALSE , 8 * sizeof(float) , (void *)(6 * sizeof(float)));
    glEnableVertexAttribArray(2);

    glBindVertexArray(0);
}

void RectRender::buildTexture(){
    TextureInfo info = loadTexture("a_test.png");
    this->textureId = info.textureId;
    // std::cout << "width = " << info.srcWidth << std::endl;
    // std::cout << "height = " << info.srcHeight << std::endl;
    // std::cout << "channel = " << info.channel << std::endl;
    // std::cout << "TextureId = " << info.textureId << std::endl;

    TextureInfo otherInfo = loadTexture("songxia.jpg");
    // std::cout << "width = " << otherInfo.srcWidth << std::endl;
    // std::cout << "height = " << otherInfo.srcHeight << std::endl;
    // std::cout << "channel = " << otherInfo.channel << std::endl;
    // std::cout << "TextureId = " << otherInfo.textureId << std::endl;
    this->textureId2 = otherInfo.textureId;
}

void RectRender::update(long long deltaTime){
    
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D , this->textureId);

    glActiveTexture(GL_TEXTURE1);
    glBindTexture(GL_TEXTURE_2D , this->textureId2);

    // glUniform1i(this->locTexture1 , 0);
    // glUniform1i(this->locTexture2 , 1);

    // glUseProgram(this->shaderProgram);

    shader.useShader();
    shader.setUniformInt("imageTexture",0);
    shader.setUniformInt("image2Texture",1);

    glBindVertexArray(vao);
    glDrawElements(GL_TRIANGLES , 6 , GL_UNSIGNED_INT , 0);

    glBindVertexArray(0);
}

void RectRender::onDestory(){
    glDeleteTextures(1 , &textureId);

    glDeleteBuffers(1 , &ebo);
}