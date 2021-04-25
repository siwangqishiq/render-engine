#include "SimpleCube.h"

void SimpleCubeScene::onInit(){
    phongShader = Shader::buildGPUProgramFromFile("phong_vertex.glsl","phong_fragment.glsl");
    
    glGenVertexArrays(1 , &vao);
    glGenBuffers(1 , &vbo);
    
    glBindVertexArray(vao);

    glBindBuffer(GL_ARRAY_BUFFER , vbo);
    glBufferData(GL_ARRAY_BUFFER , sizeof(vertices) , vertices , GL_STATIC_DRAW);

    //set vertex attr
    glVertexAttribPointer(0 , 3 , GL_FLOAT , GL_FALSE , 8 * sizeof(float) , (void *)(0 * sizeof(float)));
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(1 , 3 , GL_FLOAT , GL_FALSE , 8 * sizeof(float) , (void *)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    glVertexAttribPointer(2 , 2 , GL_FLOAT , GL_FALSE , 8 * sizeof(float) , (void *)(6 * sizeof(float)));
    glEnableVertexAttribArray(2);

    glBindVertexArray(0);

    
}

void SimpleCubeScene::update(long long deltaTime){
    glBindVertexArray(vao);

    glm::mat4 modelMat = glm::mat4(1.0f);
    modelMat = glm::translate(modelMat, this->pos);
    
    glm::vec3 cameraPosition = camera->getPostion();
    camera->lookAt(glm::vec3(0,0,0));
    
    phongShader.useShader();
    phongShader.setUnifromMat4("modelMat" , modelMat);
    phongShader.setUnifromMat4("viewMat", camera->getCameraMatrix());
    phongShader.setUnifromMat4("projMat", camera->getPerspectiveMatrix());


    glDrawArrays(GL_TRIANGLES , 0 , 36);
    
    glBindVertexArray(0);
}

void SimpleCubeScene::onDestory(){
    glDeleteBuffers(1 , &vbo);
    glDeleteVertexArrays(1 , &vao);
}   