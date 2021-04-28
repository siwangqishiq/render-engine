#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <iostream>
#include <string>
#include "config.h"


static void framebuffer_size_callback(GLFWwindow* window, int width, int height);


//纹理文件原始信息  
struct TextureInfo{
	int srcWidth;
	int srcHeight;
	int channel;
	GLuint textureId;
	unsigned char *data;
};

class App{
public:
	GLFWwindow* window;

	bool isFullScreen = false;

	int init();

	int mainLoop();

	long long currentTime();

	//纹理数据送至GPU
	TextureInfo loadTexture(std::string filename);

	//纹理数据送至GPU
	TextureInfo loadTexture(std::string filename , bool releaseData);

	virtual void onInit();

	virtual void update(long long deltaTime);

	virtual void onDestory();

	//对键盘输入事件处理
	virtual void processInput(GLFWwindow *window);

	~App();

protected:
	std::string title = "Fuck Alibaba suck my dick!!!";

	const int screenWidth = 1280;
	const int screenHeight = 800;

	long long startRenderTime = -1;
	long long lastRenderTime = -1;
};


