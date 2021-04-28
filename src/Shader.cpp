#include "Shader.h"
#include <iostream>
#include <fstream>
#include <glm/gtc/type_ptr.hpp>

Shader Shader::buildGPUProgramFromFile(std::string vertexFileName , std::string fragFileName){
    Shader shader;
    GLuint id = CreateGPUProgramFromFile(SHADER_FOLDER + vertexFileName , SHADER_FOLDER + fragFileName);
    shader.programId = id;
    return shader;
}

GLuint CreateGPUProgram(const char* vsShaderSource, const char* fsShaderSource) {
	GLuint vsShader = CompileShader(GL_VERTEX_SHADER, vsShaderSource);
	GLuint fsShader = CompileShader(GL_FRAGMENT_SHADER, fsShaderSource);

	//Attach
	GLuint program = glCreateProgram();
	glAttachShader(program, vsShader);
	glAttachShader(program, fsShader);

	//Link
	glLinkProgram(program);

	//Clear
	glDetachShader(program, vsShader);
	glDetachShader(program, fsShader);
	glDeleteShader(vsShader);
	glDeleteShader(fsShader);

	//check error
	GLint linkResult = GL_TRUE;
	glGetProgramiv(program, GL_LINK_STATUS, &linkResult);
	if (linkResult == GL_FALSE) {
		char szLog[1024] = { 0 };
		GLsizei logLen = 0;
		glGetProgramInfoLog(program, 1024, &logLen, szLog);
		printf("Link program fail error log: %s \nvs shader code:\n%s\nfs shader code:\n%s\n", 
				szLog, "vertexSource", "fragmentSource");
		glDeleteShader(program);
		program = 0;
	}

	std::cout << "program = " << program << std::endl;
	return program;
}

//读取文本文件
std::string ReadFileAsText(std::string path){
	std::string content;
	std::ifstream infile(path);
	if(infile.is_open()){
		std::string line;
		while(std::getline(infile , line)){
			line += "\n";
			content += line;
		}//end while
	}else{
		std::cout << "open file : " << path << " error "<<std::endl;
	}
	infile.close();
	return content;
}

//从文件中创建shader
GLuint CreateGPUProgramFromFile(std::string vertexShaderPath , std::string fragShaderPath){
	std::string vertexSrc = ReadFileAsText(vertexShaderPath);
	std::string fragSrc = ReadFileAsText(fragShaderPath);

	return CreateGPUProgram(vertexSrc.c_str() , fragSrc.c_str());
}

GLuint CompileShader(GLenum shaderType, const char* shaderSource) {
	GLuint shader = glCreateShader(shaderType);
	if (shader == 0) {
		std::cout << "create shader fail:" << shaderSource << std::endl;
		glDeleteShader(shader);
		return 0;
	}
	const char* shaderCode = shaderSource;
	if (shaderCode == nullptr) {
		printf("load shader code from %s fail\n", shaderSource);
		std::cout << "load shader code from " << shaderSource << " failed" << std::endl;
		glDeleteShader(shader);
		return 0;
	}

	glShaderSource(shader, 1, &shaderCode, nullptr);
	glCompileShader(shader);

	GLint compileResult = GL_TRUE;
	glGetShaderiv(shader, GL_COMPILE_STATUS, &compileResult);
	if (compileResult == GL_FALSE) {
		char szLog[1024] = { 0 };
		GLsizei logLen = 0;
		glGetShaderInfoLog(shader, 1024, &logLen, szLog);
		printf("Compile Shader fail error log: %s \nshader code:\n%s\n", szLog, shaderCode);
		glDeleteShader(shader);
		shader = 0;
	}
	return shader;
}

void Shader::useShader(){
    glUseProgram(this->programId);
}

void Shader::setUniformInt(std::string key , int value){
    GLint loc = findUniformLocation(key);
    glUniform1i(loc , value);
}

void Shader::setUniformFloat(std::string key , float value){
    GLint loc = findUniformLocation(key);
    glUniform1f(loc , value);
}

void Shader::setUniformMat4(std::string key , glm::mat4 mat){
    GLint loc = findUniformLocation(key);
	glUniformMatrix4fv(loc , 1 , GL_FALSE , glm::value_ptr(mat));
}

void Shader::setUniformVec3(std::string key , float x , float y , float z){
	GLint loc = findUniformLocation(key);
	glUniform3f(loc , x , y , z);
}

void Shader::setUniformVec3(std::string key ,glm::vec3 value){
	GLint loc = findUniformLocation(key);
	glUniform3fv(loc , 1 , (float *)(&value[0]));
}

void Shader::setUniformVec2(std::string key , float x , float y){
	GLint loc = findUniformLocation(key);
	glUniform2f(loc , x , y);
}

void Shader::setUniformBool(std::string key , bool value){
	GLint loc = findUniformLocation(key);
	glUniform1i(loc , value);
}

int Shader::findUniformLocation(std::string key){
	if(unifromLocs.find(key) != unifromLocs.end()){
		return unifromLocs[key];
	}

	const int loc = glGetUniformLocation(this->programId , key.c_str());
	if(loc >= 0){
		unifromLocs[key] = loc;
	}
	return loc;
}


//
PhongShader PhongShader::buildPhongShaderFromFile(std::string vertexFileName , std::string fragFileName){
	PhongShader shader;
    GLuint id = CreateGPUProgramFromFile(SHADER_FOLDER + vertexFileName , SHADER_FOLDER + fragFileName);
    shader.programId = id;
    return shader;
}

//设置材质数据组到shader
void PhongShader::setMaterialData(Material &material){
	setUniformVec3("material.diffuse" , material.diffuse);
	setUniformVec3("material.specular" , material.specular);
	setUniformFloat("material.shininess", material.shininess);
}

void PhongShader::enableDirectionalLight(bool enable){
	setUniformBool("uDirectionalLightEnable" , enable);
}

//设置平行光光源
void PhongShader::setDirectionalLightData(DirectionalLight *light){
	setUniformFloat("light.ambientWeight", light->ambientWeight);

	setUniformFloat("light.diffuseWeight", light->diffuseWeight);
	setUniformFloat("light.specularWeight", light->specularWeight);

	setUniformVec3("light.lightColor",light->lightColor);
	setUniformVec3("light.lightDir",light->directional);
}

//启用or关闭点光源
void PhongShader::enablePointLight(bool enable){
	setUniformBool("uPointLightEnable" , enable);
}

//设置点光源数据
void PhongShader::setPointLightData(PointLight *light){
	setUniformFloat("uPointLight.ambientWeight", light->ambientWeight);
	setUniformFloat("uPointLight.diffuseWeight", light->diffuseWeight);
	setUniformFloat("uPointLight.specularWeight", light->specularWeight);
	
	setUniformFloat("uPointLight.k0", light->k0);
	setUniformFloat("uPointLight.k1", light->k1);
	setUniformFloat("uPointLight.k2", light->k2);
	
	setUniformVec3("uPointLight.lightColor",light->lightColor);
	setUniformVec3("uPointLight.position",light->position);
}

