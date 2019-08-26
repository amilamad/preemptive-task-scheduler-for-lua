# Preemptive-task-scheduler-for-lua

Problem we are trying to solve is that when running a long lua scrpt function it will block the execution thread. This often a problem in realtime systems like game engines. 

# Build informationd
Open the soultion with Visual studio and run and see the TestApplication. 
lua_non_blocking.lib can be linked to your own project for running lua code without blocking.
Added the static build of lua to the \lua folder. If you want to use a different version download the static binaries from lua offical site.
http://luabinaries.sourceforge.net/download.html

# Running 
Place non_blocking_test.lua in the workspace.
Then run the .exe that was built from previous step.

Only Tested with Visual Studio 2017(toolset v141) with x64.

#### Key Words
Lua script, Non-blocking, preemptive, C, C++, GameDev, GameEngine, Script Engine 

