#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

//观察相机
class Camera{
public:
    Camera(const Camera& cam);

    Camera(glm::vec3 _pos , glm::vec3 _dest , float _aspect);

    //更新相机向量
    void updateCameraData();

    //获取摄像机矩阵
    glm::mat4 getCameraMatrix();

    //看向指定位置
    void lookAt(glm::vec3 _dest);

    //获取视角宽度 角度值
    inline float getFov(){
        return fov;
    }

    //获取相机位置
    inline glm::vec3 getPostion(){
        return position;
    }

    //获取右侧向量
    inline glm::vec3 getRight(){
        return right;
    }

    //获取up向量
    inline glm::vec3 getUp(){
        return up;
    }

    glm::vec3 getForward();

    //移动摄像头
    void movePosition(glm::vec3 _pos);

    //获取透视矩阵
    glm::mat4 getPerspectiveMatrix();
    
    ~Camera();

private:
    glm::vec3 position; //相机位置
    glm::vec3 dest; //朝向目标
    glm::vec3 right; //右侧向量
    glm::vec3 up; //相机向上向量
    glm::vec3 worldUp;

    float yaw = 0.0f;
    float pitch = -90.0f;

    float aspect = 1.0f;
    float fov = 45.0f;//视角宽度
    float zNear = 0.1f;//近裁剪面
    float zFar = 100.0f;//远裁剪面
};