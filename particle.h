#pragma once
#include <glm/glm.hpp>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <random>

struct position{
	position():x(0),y(0),z(0){};
	position(float X,float Y,float Z):x(X),y(Y),z(Z){}
	float x, y, z;
};

struct color{
	color(){

	};

	color(GLubyte red, GLubyte green, GLubyte blue, GLubyte alpha)
	:r(red),g(green),b(blue),a(alpha)
	{

	}


	GLubyte r,g,b,a;
};


class particle{

public:
	particle();
	~particle();

	
	//setters
	void setPosition(position pos);

	void setSpeed(glm::vec2 spd);
	//getters
	position getPosition();

	inline glm::vec2 getSpeed();

	//inline float getMass();

	//inline float getRadius();

	void generate_random_particle();

	void calculate_position();
private:

	position _position;
	//color _color;
	glm::vec2 _speed;
	//float _mass;
	//float _radius;

};