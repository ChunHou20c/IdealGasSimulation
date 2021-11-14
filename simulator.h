#pragma once
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <string>
#include "particle.h"
#include <vector>



class Simulator{

public:
	Simulator(int screenwidth,int screenheight,const char* title);
	~Simulator();

	void Run();
private:

	void MainLoop();
	void ProcessInput();
	void InitSimulator();
	static void keyCallback(GLFWwindow* window,int key, int scancode,int action, int mods);

private:
	GLFWwindow* _window;
	int _screenWidth;
	int _screenHeight;
	const char* _title;
	std::vector <particle> particles;
	unsigned int _vao;
	unsigned int _vbo;
};
