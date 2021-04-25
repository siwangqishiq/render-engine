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

static GLuint CreateGPUProgram(const char* vsShaderSource, const char* fsShaderSource) {
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
static std::string ReadFileAsText(std::string path){
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
	return content;
}

//从文件中创建shader
static GLuint CreateGPUProgramFromFile(std::string vertexShaderPath , std::string fragShaderPath){
	std::string vertexSrc = ReadFileAsText(vertexShaderPath);
	std::string fragSrc = ReadFileAsText(fragShaderPath);

	return CreateGPUProgram(vertexSrc.c_str() , fragSrc.c_str());
}

static GLuint CompileShader(GLenum shaderType, const char* shaderSource) {
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

void Shader::setUnifromMat4(std::string key , glm::mat4 mat){
    GLint loc = findUniformLocation(key);
	glUniformMatrix4fv(loc , 1 , GL_FALSE , glm::value_ptr(mat));
}

void Shader::setUnifromVec3(std::string key , float x , float y , float z){
	GLint loc = findUniformLocation(key);
	glUniform3f(loc , x , y , z);
}

void Shader::setUnifromVec2(std::string key , float x , float y){
	GLint loc = findUniformLocation(key);
	glUniform2f(loc , x , y);
}

//设置材质数据组到shader
void Shader::setMaterialData(Material &material){
	
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

