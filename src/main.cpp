// std::cout, std::cin
#include <iostream>

#include "Core/CoreSimulation.h"

int main() {
	kt::Core::CoreSimulation Game;
	bool gameInitialized = Game.initialize();
	if (gameInitialized) {
		Game.run();
	}
	Game.exitSimulation();
	return 0;
}
