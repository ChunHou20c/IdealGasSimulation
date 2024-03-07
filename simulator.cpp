#include "simulator.h"
#include "shader.h"
#include <iostream>
#include <vector>
#include <string>

Simulator::Simulator(int screenwidth,int screenheight,const char* title, std::string& executable_path)
:_window(nullptr),_screenWidth(screenwidth),_screenHeight(screenheight),_title(title),_vao(0),_vbo(0), _executable_path(executable_path)
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

		for(int i=0;i<particles.size();i++){
			particles[i].calculate_position();
		}
		for(int i=0;i<particles.size();i++){

			for(int j=i+1;j<particles.size();j++){

				if(collided(particles[i],particles[j])){
					particles[i].setPosition(
						(position(particles[i].getPosition().x-particles[i].getSpeed().x,
						particles[i].getPosition().y-particles[i].getSpeed().y,1.0f)));
					particles[j].setPosition(
						(position(particles[j].getPosition().x-particles[j].getSpeed().x,
						particles[j].getPosition().y-particles[j].getSpeed().y,1.0f)));
					
					elastic_collision(particles[i],particles[j]);
				}
			}
		}

		glBufferSubData(GL_ARRAY_BUFFER,0,sizeof(particle)*particles.size(),particles.data());

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

bool Simulator::collided(particle &particle1,particle &particle2){

	float x_dis=particle1.getPosition().x-particle2.getPosition().x;
	float y_dis=particle1.getPosition().y-particle2.getPosition().y;

	if(sqrt(x_dis*x_dis+y_dis*y_dis)<=(particle1.getRadius()+particle2.getRadius())){
		return true;
	}
	return false;
}

void Simulator::elastic_collision(particle &particle1,particle &particle2){

	float pi2=2*acos(-1.0e0);
	float r12=particle1.getRadius()+particle2.getRadius();//calculate collision distance
	float m21=particle2.getMass()/particle1.getMass();
	float x21=particle2.getPosition().x-particle1.getPosition().x;
	float y21=particle2.getPosition().y-particle1.getPosition().y;

	glm::vec2 initial_speed1=particle1.getSpeed();
	glm::vec2 initial_speed2=particle2.getSpeed();


	float Vx21=particle2.getSpeed().x-particle1.getSpeed().x;
	float Vy21=particle2.getSpeed().y-particle1.getSpeed().y;

	float gammav=atan2(-Vy21,-Vx21);
	float d=sqrt(x21*x21 +y21*y21);
	float gammaxy=atan2(y21,x21);
    float dgamma=gammaxy-gammav;

        if (dgamma>pi2) {dgamma=dgamma-pi2;}
        else if (dgamma<-pi2) {dgamma=dgamma+pi2;}

    float dr=d*sin(dgamma)/r12;

	float alpha=asin(dr);
	float dc=d*cos(dgamma);
	float sqs;
    if (dc>0) {sqs=1.0;} else {sqs=-1.0;}
    float t=(dc-sqs*r12*sqrt(1-dr*dr))/sqrt(Vx21*Vx21+ Vy21*Vy21);

	float a=tan( gammav +alpha);

    float dvx2=-2*(Vx21 +a*Vy21) /((1+a*a)*(1+m21));
       
    particle2.setSpeed(initial_speed2+glm::vec2(dvx2,a*dvx2));
    particle1.setSpeed(initial_speed1+glm::vec2(-m21*dvx2,-a*m21*dvx2));
       
  
	particle1.setPosition(position(
		particle1.getPosition().x+initial_speed1.x*t+particle1.getSpeed().x*(1-t),
		particle1.getPosition().y+initial_speed1.y*t+particle1.getSpeed().y*(1-t),
		0.0f));

	particle2.setPosition(position(
		particle2.getPosition().x+initial_speed2.x*t+particle2.getSpeed().x*(1-t),
		particle2.getPosition().y+initial_speed2.y*t+particle2.getSpeed().y*(1-t),
		0.0f));

}
