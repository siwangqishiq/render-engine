#include "CubeRender.h"

CubeRender::CubeRender(){
    camera = new Camera(glm::vec3(0,3,-5) , glm::vec3(0,0,0) , (float)screenWidth / (float)screenHeight);
}

void CubeRender::onInit(){
    shader = Shader::buildGPUProgramFromFile("cube_render_vertex.glsl","cube_render_frag.glsl");
    buildTexture();

    glGenVertexArrays(1 , &vao);
    glGenBuffers(1 , &vbo);
    
    glBindVertexArray(vao);

    glBindBuffer(GL_ARRAY_BUFFER , vbo);
    glBufferData(GL_ARRAY_BUFFER , sizeof(vertices) , vertices , GL_STATIC_DRAW);

    //set vertex attr
    glVertexAttribPointer(0 , 3 , GL_FLOAT , GL_FALSE , 5 * sizeof(float) , (void *)(0 * sizeof(float)));
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(1 , 2 , GL_FLOAT , GL_FALSE , 5 * sizeof(float) , (void *)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    glBindVertexArray(0);

    //坐标系显示
    grid= new CoordinateGrid();
    grid->init();
}

void CubeRender::buildTexture(){
    TextureInfo info = loadTexture("box2.png");
    this->textureId = info.textureId;
}

void CubeRender::update(long long deltaTime){  
    grid->render(*camera);

    shader.useShader();
    glBindVertexArray(vao);

    glm::mat4 modelMat = glm::mat4(1.0f);
    modelMat = glm::translate(modelMat, glm::vec3(0 , 0 , 0));
    modelMat = glm::rotate(modelMat , this->angleX , glm::vec3(1 ,  0, 0));
    modelMat = glm::rotate(modelMat , this->angleY , glm::vec3(0 ,  1, 0));
    modelMat = glm::rotate(modelMat , this->angleZ , glm::vec3(0 ,  0, 1));
    //modelMat = glm::scale(modelMat , glm::vec3(3 , 3 , 3));
    glm::vec3 cameraPosition = camera->getPostion();
    cameraPosition[2] += 1.0;
    camera->lookAt(glm::vec3(0,0,0));
    
    shader.setUnifromMat4("modelMat" , modelMat);

    glm::vec3 p = camera->getPostion();
    //std::cout << "pos = " << p[0] << " " << p[1] << " " << p[2] << std::endl;

    shader.setUnifromMat4("viewMat", camera->getCameraMatrix());
    shader.setUnifromMat4("projMat", camera->getPerspectiveMatrix());

    glBindTexture(GL_TEXTURE_2D , this->textureId);

    glDrawArrays(GL_TRIANGLES , 0 , 36);
    
    glBindVertexArray(0);
}

glm::mat4 CubeRender::getPerspectiveMatrix(){
	return glm::perspective((float)glm::radians(camera->getFov()) ,(float)screenWidth / (float)screenHeight, 0.1f, 100.0f);
}

void CubeRender::onDestory(){
    // glDeleteTextures(1 , &textureId);
    // glDeleteBuffers(1 , &ebo);
    glDeleteVertexArrays(1 , &vao);

    if(camera != nullptr){
        delete camera;
        camera = nullptr;
    }

    if(grid != nullptr){
        delete grid;
        grid = nullptr;
    }
}

void CubeRender::processInput(GLFWwindow *window){
    App::processInput(window);

    if(glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS) {
        //std::cout << "press UP" << std::endl;
        this->angleX += 0.01f;
    } 

    if(glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS) {
        //std::cout << "press DOWN" << std::endl;
        this->angleX -= 0.01f;
    } 

	if(glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS) {
        this->angleY += 0.01f;
    } 

	if(glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS) {
        this->angleY -= 0.01f;
    } 

    if(glfwGetKey(window, GLFW_KEY_Z) == GLFW_PRESS) {
        this->angleZ += 0.01f;
    } 

	if(glfwGetKey(window, GLFW_KEY_X) == GLFW_PRESS) {
        this->angleZ -= 0.01f;
    } 

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
        cameraPos[1] += moveSpeed;
        camera->movePosition(cameraPos);
    } 

    if(glfwGetKey(window, GLFW_KEY_E) == GLFW_PRESS) {
        cameraPos[1] -= moveSpeed;
        camera->movePosition(cameraPos);
    } 

    
    if(glfwGetKey(window, GLFW_KEY_R) == GLFW_PRESS) {
        camera->movePosition(glm::vec3(0 ,  3 , -10));
    } 
}