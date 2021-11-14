#include "shader.h"
#include "simulator.h"



int main(){



	Simulator ideal_gas(600,600,"Ideal Gas Simulation");
	ideal_gas.Run();

	return 0;
}
