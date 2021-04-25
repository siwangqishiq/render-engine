#include "Camera.h"

#include <iostream>

Camera::Camera(glm::vec3 _pos , glm::vec3 _dest , float _aspect){
    this->position = _pos;
    this->dest = _dest;
    this->aspect = _aspect;

    worldUp = glm::vec3(0.0f , 1.0f , 0.0f);

    updateCameraData();
}

Camera::Camera(const Camera& cam){
    this->position = cam.position;
    this->dest = cam.dest;
    this->aspect = cam.aspect;

    worldUp = glm::vec3(0.0f , 1.0f , 0.0f);
    updateCameraData();
}

//计算View矩阵
glm::mat4 Camera::getCameraMatrix(){
    return glm::lookAt(position , dest , up);
}

//看向指定位置
void Camera::lookAt(glm::vec3 _dest){
    this->dest = _dest;

    updateCameraData();
}

//更新相机相关向量 
void Camera::updateCameraData(){
    glm::vec3 arrow = glm::normalize(dest - position);
    right = glm::normalize(glm::cross(arrow , worldUp));
    up = glm::normalize(glm::cross(right , arrow));
}

void Camera::movePosition(glm::vec3 _pos){
    position = _pos;
    updateCameraData();

    glm::vec3 p = this->getPostion();
    std::cout << "pos22 = " << p[0] << " " << p[1] << " " << p[2] << std::endl;
}

//透视矩阵
glm::mat4 Camera::getPerspectiveMatrix(){
    return glm::perspective(glm::radians(this->fov) , aspect , zNear , zFar);
}

//获得向前 单位向量
glm::vec3 Camera::getForward(){
    return glm::normalize(dest - position);
}

Camera::~Camera(){
    std::cout << "release camera !" << std::endl; 
}