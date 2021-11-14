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

	return 0;
}
