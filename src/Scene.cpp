#include "Scene.h"

Scene::Scene(){
    camera = buildCamera();
}

Scene::~Scene(){

}

//构建自定义Camera
std::shared_ptr<Camera> Scene::buildCamera(){
    return std::make_shared<Camera>(glm::vec3(0,3,-5) , glm::vec3(0,0,0) , (float)screenWidth / (float)screenHeight);
}

//
void Scene::setCamera(std::shared_ptr<Camera> newCamera){
    this->camera = newCamera;
}

void Scene::processInput(GLFWwindow *window){
    App::processInput(window);

    glm::vec3 cameraPos = camera->getPostion();
    if(glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) {
        glm::vec3 forward = camera->getForward();
        float scalar = moveSpeed;
        glm::vec3 moveVec = glm::vec3(scalar* forward[0] , scalar* forward[1] ,scalar* forward[2]);
        cameraPos += (moveVec);
        camera->movePosition(cameraPos);
    } 

    if(glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) {
        glm::vec3 forward = camera->getForward();
        float scalar = moveSpeed;
        glm::vec3 moveVec = glm::vec3(scalar* forward[0] , scalar* forward[1] ,scalar* forward[2]);
        cameraPos -= (moveVec);
        camera->movePosition(cameraPos);
    } 

	if(glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) {
        
        glm::vec3 right = camera->getRight();
        float scalar = moveSpeed;
        glm::vec3 moveVec = glm::vec3(scalar* right[0] , scalar* right[1] ,scalar* right[2]);
        cameraPos -= (moveVec);
        camera->movePosition(cameraPos);
    } 

	if(glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) {
        glm::vec3 right = camera->getRight();
        float scalar = moveSpeed;
        glm::vec3 moveVec = glm::vec3(scalar* right[0] , scalar* right[1] ,scalar* right[2]);
        cameraPos += (moveVec);
        camera->movePosition(cameraPos);
    } 

    if(glfwGetKey(window, GLFW_KEY_Q) == GLFW_PRESS) {
        glm::vec3 up = camera->getUp();
        float scalar = moveSpeed;
        glm::vec3 moveVec = glm::vec3(scalar* up[0] , scalar* up[1] ,scalar* up[2]);
        cameraPos += (moveVec);
        camera->movePosition(cameraPos);
    } 

    if(glfwGetKey(window, GLFW_KEY_E) == GLFW_PRESS) {
        glm::vec3 up = camera->getUp();
        float scalar = moveSpeed;
        glm::vec3 moveVec = glm::vec3(scalar* up[0] , scalar* up[1] ,scalar* up[2]);
        cameraPos -= (moveVec);
        camera->movePosition(cameraPos);
    } 

    
    if(glfwGetKey(window, GLFW_KEY_R) == GLFW_PRESS) {
        camera->movePosition(glm::vec3(0 ,  3 , -5));
    } 
}


void CubeScene::onInit(){
    grid= new CoordinateGrid();
    grid->init();
}

void CubeScene::update(long long deltaTime){
    grid->render(*camera);
}

void CubeScene::onDestory(){
    if(grid != nullptr){
        delete grid;
        grid = nullptr;
    }
}

