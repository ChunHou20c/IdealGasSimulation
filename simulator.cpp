#include "simulator.h"
#include "shader.h"
#include <iostream>
#include <vector>

Simulator::Simulator(int screenwidth,int screenheight,const char* title)
:_window(nullptr),_screenWidth(screenwidth),_screenHeight(screenheight),_title(title),_vao(0),_vbo(0)
{

}


Simulator::~Simulator(){
	glfwTerminate();
}

//main loop of the simulation
void Simulator::Run(){


	MainLoop();

}

void Simulator::MainLoop(){
	particles.resize(100);

	for(int i=0;i<particles.size();i++){
		particles[i].generate_random_particle();
	}

	InitSimulator();
	glfwSetKeyCallback(_window,Simulator::keyCallback);
	shader _shader("res/shader");
	_shader.Bind();
	
	glClearColor(0.8f,0.8f,0.8f,1.0f);
	while(!glfwWindowShouldClose(_window)){
		glClearDepth(1.0);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		glBindVertexArray(_vao);
		glBufferSubData(GL_ARRAY_BUFFER,0,sizeof(particle)*particles.size(),particles.data());

		for(int i=0;i<particles.size();i++){
			particles[i].calculate_position();
		}

		glDrawArrays(GL_POINTS,0,100);

		glfwSwapBuffers(_window);
		glBindVertexArray(0);

		ProcessInput();
	}
	_shader.Unbind();
}
void Simulator::ProcessInput(){
	glfwPollEvents();
	
}


void Simulator::InitSimulator(){
	//initiallize glfw
	glfwInit();

	//configure opengl
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR,3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR,3);
	//use core profile
	glfwWindowHint(GLFW_OPENGL_PROFILE,GLFW_OPENGL_CORE_PROFILE);

	//window creation
	_window = glfwCreateWindow(_screenWidth,_screenHeight,_title,NULL,NULL);

	//error checking: if window returned NULL, the window is not created
	if(_window==NULL){
		std::cout<<"Falied to create window!\n";
		glfwTerminate();
		exit(-1);
	}

	//make openGL context before glewinit
	glfwMakeContextCurrent(_window);
	glfwSwapInterval(1);

	//error checking for glew initialization
	if(glewInit()!=GLEW_OK){
		std::cout<<"failed to initialize glew!\n";
		glfwTerminate();
		exit(-1);
	}

	glGenVertexArrays(1,&_vao);
	glBindVertexArray(_vao);

	glGenBuffers(1,&_vbo);
	glBindBuffer(GL_ARRAY_BUFFER,_vbo);
	glBufferData(GL_ARRAY_BUFFER,sizeof(particle)*100,nullptr,GL_DYNAMIC_DRAW); //orphan the data
	
	//vao

	//gl attribpointer send data to shader
	glVertexAttribPointer(0,3,GL_FLOAT,GL_TRUE,3*sizeof(float)+sizeof(glm::vec2),(void*)0);
	//argument 1, location of attribute: position layout=0
	//argument 2, data size: 3 data per vertex
	//argument 3, type of data: float
	//argument 4, normalized: not to normalized
	//argument 5, stride: distance between first data in byte
	//argument 6, starting position 

	glEnableVertexAttribArray(0);//enable for location 0: position attribute

    glEnable(GL_PROGRAM_POINT_SIZE);
	glBindVertexArray(0);
}

void Simulator::keyCallback(GLFWwindow* window,int key, int scancode,int action, int mods){
	if (key == GLFW_KEY_SPACE && action == GLFW_PRESS){
		std::cout<<"Space is pressed"<<std::endl;
	}
}
