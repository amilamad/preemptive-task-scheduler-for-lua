#include <iostream>
#include "lua_non_blocking.h"

void MainLoop(float);

int main()
{
	ScriptRunner scriptRunner(std::string("non_blocking_test.lua"), std::string("heavy_function"), 100, &MainLoop);
	while (true)
	{
		constexpr float simpleDeltaTime = 1 / 60.0;
		scriptRunner.Update(simpleDeltaTime);
	}	
}

void MainLoop(float dt) 
{
	std::cout << "Main loop is in control" << std::endl;
}