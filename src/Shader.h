#pragma once

#include <string>
#include <glad/glad.h>

#include <glm/glm.hpp>
#include <unordered_map>
#include "Material.h"

static std::string SHADER_FOLDER = "shader/";

//编译shader源码
static GLuint CompileShader(GLenum shaderType, const char* shaderSource);

//创建完整Shader
static GLuint CreateGPUProgram(const char* vsShaderSource, const char* fsShaderSource);

//读取文本文件
static std::string ReadFileAsText(std::string path);

//从文件中创建shader
static GLuint CreateGPUProgramFromFile(std::string vertexShaderPath , std::string fragShaderPath);

class Shader{
public:
    static Shader buildGPUProgramFromFile(std::string vertexShaderPath , std::string fragShaderPath);

    //使用shader
    void useShader();

    //
    void setUniformInt(std::string key , int value);

    //
    void setUnifromMat4(std::string key , glm::mat4 mat);

    //设置三维向量
    void setUnifromVec3(std::string key , float x , float y , float z);

    //设置二维向量
    void setUnifromVec2(std::string key , float x , float y);

    //设置材质数据组到shader
    void setMaterialData(Material &material);
    
    int findUniformLocation(std::string key);
private:
    unsigned int programId;
    std::unordered_map<std::string , int> unifromLocs; //unifrom变量loccation
};
