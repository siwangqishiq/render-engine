#include "Triangle.h"

void TriangleApp::onInit(){
    shader = Shader::buildGPUProgramFromFile("triangle_vertex.glsl" , "triangle_fragment.glsl");

    glGenVertexArrays(1 , &vao);
    glGenBuffers(1 , &vbo);

    glBindVertexArray(vao);
    glBindBuffer(GL_ARRAY_BUFFER , vbo);
    glBufferData(GL_ARRAY_BUFFER , sizeof(vertices) , vertices , GL_STATIC_DRAW);

    glVertexAttribPointer(0 , 2 , GL_FLOAT , GL_FALSE , 2 * sizeof(float) , (void *)0);
    glEnableVertexAttribArray(0);
}

void TriangleApp::update(long long deltaTime){
    //glBindVertexArray(vao);
    shader.useShader();
    
    glBindVertexArray(vao);
    glDrawArrays(GL_TRIANGLE_FAN , 0 , 3);
}

void TriangleApp::onDestory(){

}

