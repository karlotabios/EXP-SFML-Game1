// std::cout, std::cin
#include <iostream>

#include "Core/CoreSimulation.h"

int main() {
	kt::Core::CoreSimulation Game;
	Game.run();
	Game.exitSimulation();
	return 0;
}
