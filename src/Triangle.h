#pragma once

#include "App.h"
#include "Shader.h"
#include <glad/glad.h>

class TriangleApp : public App {
private:
    GLuint vao;
    GLuint vbo;

    Shader shader;

    float vertices[3 * 2] = {
        -0.5f , -0.5f,
         0.5f , -0.5f,
         0.0f ,  0.5f 
    };
public:
    virtual void onInit();

	virtual void update(long long deltaTime);

	virtual void onDestory();
};