#include <iostream>
#include "lua_non_blocking.h"

void MainLoop(float);

int main()
{
	ScriptRunner scriptRunner(std::string("test.lua"), std::string("lua_main"), &MainLoop);
	while (true)
	{
		constexpr float simpleDeltaTime = 1 / 60.0;
		scriptRunner.Update(simpleDeltaTime);
	}	
}

void MainLoop(float dt) 
{

}