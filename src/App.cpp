#include "App.h"
#include <GLFW/glfw3.h>
#include <chrono>


#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

int App::init(){
	glfwInit();

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    // --------------------
    window = glfwCreateWindow(screenWidth, screenHeight, title.c_str(), isFullScreen ?glfwGetPrimaryMonitor():nullptr, nullptr);
	
    if (window == nullptr) {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }

	glfwMakeContextCurrent(window);
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

	// glad: load all OpenGL function pointers
    // ---------------------------------------
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }

	startRenderTime = currentTime();

	glEnable(GL_DEPTH_TEST);//开启深度测试

	this->onInit();

	return 0;
}

int App::mainLoop(){

	while (!glfwWindowShouldClose(window)) {
        processInput(window);

        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClearColor(0, 0, 0, 1.0);
        glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
		
		long long deltaTime = 0;
		long long currentTimeM = currentTime();

		if(this->lastRenderTime > 0){
			deltaTime = currentTimeM - lastRenderTime;
		}
		lastRenderTime = currentTimeM;
		
		this->update(deltaTime);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

	this->onDestory();
	glfwTerminate();
	
	return 0;
}

long long App::currentTime(){
	std::chrono::milliseconds ms = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch());
	//std::cout << ms.count() << std::endl;
	return ms.count();
}

void App::onInit(){
	//std::cout << "onInit" << std::endl;
}

void App::update(long long deltaTime){
	//std::cout << "update " << deltaTime << std::endl;
	
}

void App::onDestory(){
	//std::cout << "onDestory" << std::endl;
}

TextureInfo App::loadTexture(std::string filename){
	return loadTexture(filename , true);
}

TextureInfo App::loadTexture(std::string filename , bool releaseData){
	if(hasLoadedTextures.find(filename) != hasLoadedTextures.end()){//此filename之前已被载入过
		return hasLoadedTextures[filename];
	}

	TextureInfo info;
	
	stbi_set_flip_vertically_on_load(true);

	unsigned char *imageData = nullptr;

	if(filename.rfind("D:" , 0) == 0 || filename.rfind("E:" , 0) == 0){
		imageData = stbi_load(filename.c_str() , &info.srcWidth , &info.srcHeight , &info.channel , 0);
	}else{
		imageData = stbi_load((ASSETS_FOLDER + filename).c_str() , &info.srcWidth , &info.srcHeight , &info.channel , 0);
	}
	
	//stbi_set_flip_vertically_on_load(false);

	if(imageData){
		info.data = imageData;
	}else{
		std::cout << "load texture " << filename << " failed!" << std::endl;
		return info;
	}

	GLint format;
	if(info.channel == 3){//3通道
		format = GL_RGB;
	}else if(info.channel == 4){ //4通道 
		format = GL_RGBA;
	}

	glGenTextures(1 , &info.textureId);

	glBindTexture(GL_TEXTURE_2D , info.textureId);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_MIRROR_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_MIRROR_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	
	glTexImage2D(GL_TEXTURE_2D , 0 , format , info.srcWidth , info.srcHeight ,0 , format, GL_UNSIGNED_BYTE , info.data);
	glGenerateMipmap(GL_TEXTURE_2D);

	glBindTexture(GL_TEXTURE_2D , 0);

	if(releaseData){
		stbi_image_free(imageData);
	}

	//加入map 防止后面重复加载
	hasLoadedTextures[filename] = info;
	return info;
}

App::~App(){
}

void App::processInput(GLFWwindow *window) {
    if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS){
        glfwSetWindowShouldClose(window, true);
		return;
    }
}

static void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
    glViewport(0, 0, width, height);
}



