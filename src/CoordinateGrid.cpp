#include "CoordinateGrid.h"

void CoordinateGrid::init(){
    prepareVertices();
    shader = Shader::buildGPUProgramFromFile("coord_grid_vertex.glsl","coord_grid_frag.glsl");

    glGenVertexArrays(1 , &vao);
    glGenBuffers(1 , &vbo);
    
    glBindVertexArray(vao);

    glBindBuffer(GL_ARRAY_BUFFER , vbo);
    glBufferData(GL_ARRAY_BUFFER , sizeof(float) * vertices.size() , &vertices[0] , GL_STATIC_DRAW);

    //set vertex attr
    glVertexAttribPointer(0 , 3 , GL_FLOAT , GL_FALSE , 6 * sizeof(float) , (void *)(0 * sizeof(float)));
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1 , 3 , GL_FLOAT , GL_FALSE , 6 * sizeof(float) , (void *)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    glBindVertexArray(0);
}

void CoordinateGrid::prepareVertices(){
    this->vertices = {
        -size , 0 , 0 , xCoordColor[0] , xCoordColor[1] , xCoordColor[2],
         size , 0 , 0 , xCoordColor[0] , xCoordColor[1] , xCoordColor[2],
         0, -size , 0 , yCoordColor[0] , yCoordColor[1] , yCoordColor[2],
         0,  size , 0 , yCoordColor[0] , yCoordColor[1] , yCoordColor[2],
         0, 0 , -size , zCoordColor[0] , zCoordColor[1] , zCoordColor[2],
         0, 0 ,  size , zCoordColor[0] , zCoordColor[1] , zCoordColor[2],
    };
}

void CoordinateGrid::render(Camera &camera){
    glBindVertexArray(vao);

    shader.useShader();
    glm::mat4 modelMat = glm::mat4(1.0f);
    shader.setUniformMat4("modelMat" , modelMat);
    shader.setUniformMat4("viewMat", camera.getCameraMatrix());
    shader.setUniformMat4("projMat", camera.getPerspectiveMatrix());


    glDrawArrays(GL_LINES , 0 , vertices.size() / 6);
    
    glBindVertexArray(0);
}
