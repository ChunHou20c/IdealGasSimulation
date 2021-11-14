#include <iostream>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <ctime>
#include <random>
#include <glm/glm.hpp>
#include "shader.h"
#include "simulator.h"



int main(){



	Simulator ideal_gas(600,600,"Ideal Gas Simulation");
	ideal_gas.Run();


#ifdef false
	float vertices[9]={-0.5f,-0.5f,0.0f,
	0.5f,-0.5f,0.0f,0.0f,0.5f,0.0f};
	//vbo

	vertices[2],vertices[5],vertices[8]=0.0f;
	//draw here
		for(int i=0;i<9;i++){
			if((i+1)%3==0) continue;
			vertices[i]=randomNumber(randomEngine);
			std::cout<<i<<std::endl;
			}
	float speed[6];
	for(int i=0;i<6;i++){
	speed[i]=randomNumber(randomEngine)/10;
	std::cout<<speed[i]<<std::endl;
	}
#endif
	return 0;
}