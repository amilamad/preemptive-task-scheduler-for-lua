#include <iostream>
#include "lua_non_blocking.h"

void MainLoop(float);

int main()
{
	try {
		ScriptRunner scriptRunner(std::string("non_blocking_test.lua"), std::string("heavy_function"), 100, &MainLoop);
		while (true)
		{
			constexpr float simpleDeltaTime = 1 / 60.0;
			scriptRunner.Update(simpleDeltaTime);
		}
	}
	catch (std::exception e) 
	{
		std::cout << "Error on runing lua script : error = " << e.what() << std::endl;
	}		
}

void MainLoop(float dt) 
{
	std::cout << "Main loop is in control" << std::endl;
}