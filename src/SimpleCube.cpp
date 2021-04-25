#include "SimpleCube.h"

void SimpleCubeScene::onInit(){
    phongShader = PhongShader::buildPhongShaderFromFile("phong_vertex.glsl","phong_fragment.glsl");
    
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

    //
    createMaterial();
    createDirectionalLight();
}

void SimpleCubeScene::update(long long deltaTime){
    glBindVertexArray(vao);

    glm::mat4 modelMat = glm::mat4(1.0f);
   
    modelMat = glm::translate(modelMat, this->pos);
    modelMat = glm::rotate(modelMat , angleY , glm::vec3(0 , 1, 0));

    glm::vec3 cameraPosition = camera->getPostion();
    camera->lookAt(glm::vec3(0,0,0));
    
    phongShader.useShader();
    phongShader.setUniformMat4("modelMat" , modelMat);
    phongShader.setUniformMat4("viewMat", camera->getCameraMatrix());
    phongShader.setUniformMat4("projMat", camera->getPerspectiveMatrix());

    phongShader.setUniformVec3("cameraPos" , camera->getPostion());
    phongShader.setMaterialData(material);
    phongShader.setDirectionalLightData(*light);

    glDrawArrays(GL_TRIANGLES , 0 , 36);
    
    glBindVertexArray(0);
}

//创建材质
Material SimpleCubeScene::createMaterial(){
    material = Material::buildMaterial(Material::MaterialEnum::Normal);
    // material = Material::buildMaterial(Material::MaterialEnum::Plastic);
    return material;
}

std::shared_ptr<DirectionalLight> SimpleCubeScene::createDirectionalLight(){
    glm::vec3 dir = glm::vec3(0 , 0, 0) - glm::vec3(1 , 1, 1);

    this->light = std::make_shared<DirectionalLight>(dir);

    return light;
}

void SimpleCubeScene::onDestory(){
    glDeleteBuffers(1 , &vbo);
    glDeleteVertexArrays(1 , &vao);
} 

void SimpleCubeScene::processInput(GLFWwindow *window){
    Scene::processInput(window);

    if(glfwGetKey(window, GLFW_KEY_0) == GLFW_PRESS) {
       light->lightColor = glm::vec3(1.0 , 1.0 , 1.0);
        angleY = 0.0f;
    } 

    if(glfwGetKey(window, GLFW_KEY_1) == GLFW_PRESS) {
       light->lightColor = glm::vec3(1.0 , 0 , 0);
    } 

    if(glfwGetKey(window, GLFW_KEY_2) == GLFW_PRESS) {
       light->lightColor = glm::vec3(1.0 , 1.0 , 0);
    } 

    if(glfwGetKey(window, GLFW_KEY_3) == GLFW_PRESS) {
       light->lightColor = glm::vec3(0.0 , 1.0 , 0);
    } 

    if(glfwGetKey(window, GLFW_KEY_4) == GLFW_PRESS) {
       light->lightColor = glm::vec3(0.0 , 0.0 , 1.0);
    } 

    if(glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS) {
       angleY += glm::radians(0.1f);
    }

    if(glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS) {
       angleY -= glm::radians(0.1f);
    }  

    if(glfwGetKey(window, GLFW_KEY_I) == GLFW_PRESS) {
        glm::vec3 lg = light->directional;
        lg[0] += 0.1f;
        light->directional = glm::normalize(lg);
    }

    if(glfwGetKey(window, GLFW_KEY_K) == GLFW_PRESS) {
        glm::vec3 lg = light->directional;
        lg[0] -= 0.1f;
        light->directional = glm::normalize(lg);
    }

    if(glfwGetKey(window, GLFW_KEY_J) == GLFW_PRESS) {
       glm::vec3 lg = light->directional;
       lg[2] += 0.1f;
       light->directional = glm::normalize(lg);
    }

    if(glfwGetKey(window, GLFW_KEY_L) == GLFW_PRESS) {
       glm::vec3 lg = light->directional;
       lg[2] -= 0.1f;
       light->directional = glm::normalize(lg);
    } 
}
