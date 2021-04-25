#pragma once

#include "Camera.h"
#include <vector>
#include <glm/glm.hpp>
#include "Shader.h"

//坐标轴
class CoordinateGrid{
public:
    void init();

    void render(Camera &camera);

private:
    float size = 100;
    
    glm::vec3 xCoordColor = glm::vec3(1.0f , 0.0f, 0.0f);
    glm::vec3 yCoordColor = glm::vec3(0.0f , 1.0f, 0.0f);
    glm::vec3 zCoordColor = glm::vec3(0.0f , 0.0f, 1.0f);

    std::vector<float> vertices;

    //构建顶点
    void prepareVertices();

    Shader shader;

    unsigned int vao;
    unsigned int vbo;
};