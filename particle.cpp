#include "particle.h"
#include <random>
#include <ctime>
#include <iostream>

particle::particle(){

	}

particle::~particle(){

	}


void particle::setPosition(position pos){
		_position=pos;
	}

void particle::setSpeed(glm::vec2 spd){
		_speed=spd;
	}
	//getters
position particle::getPosition(){
		return _position;
	}

glm::vec2 particle::getSpeed(){
		return _speed;
	}

//float particle::getMass(){
//		return _mass;
//	}

//float particle::getRadius(){
//		return _radius;
//	}

void particle::generate_random_particle(){
	static std::mt19937 randomEngine(time(0));
	static std::uniform_real_distribution<float> randomNumber(-1.0,1.0);

	setPosition(position(randomNumber(randomEngine),randomNumber(randomEngine),1.0));
	setSpeed(glm::vec2(randomNumber(randomEngine)*0.02,randomNumber(randomEngine)*0.02));
}

void particle::calculate_position(){
	_position.x= _position.x+_speed.x;

	static const double BORDER=0.96667;
	if(_position.x<-BORDER)
		{_position.x= -BORDER+(-BORDER-_position.x);
		_speed.x=-_speed.x;}
	
	if(_position.x>BORDER){
		_position.x= BORDER-(_position.x-BORDER);
		_speed.x=-_speed.x;
	}

	_position.y= _position.y+_speed.y;

	if(_position.y<-BORDER)
		{_position.y= -BORDER+(-BORDER-_position.y);
		_speed.y=-_speed.y;}
	
	if(_position.y>BORDER){
		_position.y= BORDER-(_position.y-BORDER);
		_speed.y=-_speed.y;
	}

}
