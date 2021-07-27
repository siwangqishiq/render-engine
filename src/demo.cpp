#include "demo.h"

void ShowModel::onInit(){
    objModel = new ObjModel();
    objModel->loadObjFile("E:\\assets\\model\\lapu\\obj\\lap.obj");
    //objModel->loadObjFile("D:\\assets\\untitled.obj");
    
    // std::cout << "mesh size " << objModel->meshes.size() << std::endl;

    // for(int i = 0 ; i < objModel->meshes.size();i++){
    //     std::shared_ptr<Mesh> mesh = objModel->meshes[i];
    //     std::cout << "mesh material " << mesh->material.name << std::endl;
    //     std::cout << "mesh verteices " << mesh->verteices.size() << std::endl;
    // }//end for i
    //std::cout << "mesh  " << objModel->meshes.size() << std::endl;

    objModel->setupModel(*this);
}

void ShowModel::update(long long deltaTime){
    objModel->render(*this);
}

void FontTest::onInit(){
    text = std::make_shared<Text>(screenWidth , screenHeight);
    text->init();
}

void FontTest::update(long long deltaTime){
    //std::cout << "font text update" << std::endl;
    text->renderText(100.0f , 300.0f , 
        L"你好 世界 魑魅魍魉 日语 さようなら。" , 
        glm::vec4(1.0f , 1.0f , 0.0f , 1.0f)
    );
}

void FontTest::onDestory(){
    text->free();
}


void FboTest::onInit(){
    mOffScreenTexture = std::make_shared<OffScreenTexture>(this);

    camera = new Camera(glm::vec3(0,3,-5) , glm::vec3(0,0,0) , (float)screenWidth / (float)screenHeight);
    shader = Shader::buildGPUProgramFromFile("cube_render_vertex.glsl","cube_render_frag.glsl");
    
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

    mOffScreenTexture->init();
}

void FboTest::update(long long deltaTime){
     if(glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS) {
        //std::cout << "press UP" << std::endl;
        this->angleX += 0.003f;
    } 

    if(glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS) {
        //std::cout << "press DOWN" << std::endl;
        this->angleX -= 0.003f;
    } 

	if(glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS) {
        this->angleY += 0.003f;
    } 
    
	if(glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS) {
        this->angleY -= 0.003f;
    } 

    mOffScreenTexture->render();

    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);

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
    
    shader.setUniformMat4("modelMat" , modelMat);

    glm::vec3 p = camera->getPostion();
    //std::cout << "pos = " << p[0] << " " << p[1] << " " << p[2] << std::endl;

    shader.setUniformMat4("viewMat", camera->getCameraMatrix());
    shader.setUniformMat4("projMat", camera->getPerspectiveMatrix());

    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D , mOffScreenTexture->getTextureId());
    shader.setUniformInt("imageTexture",0);

    glDrawArrays(GL_TRIANGLES , 0 , 36);

    glBindTexture(GL_TEXTURE_2D , 0);
    
    glBindVertexArray(0);
}

void FboTest::onDestory(){
    mOffScreenTexture->free();
}

glm::mat4 FboTest::getPerspectiveMatrix(){
	return glm::perspective((float)glm::radians(camera->getFov()) ,(float)screenWidth / (float)screenHeight, 0.1f, 100.0f);
}
