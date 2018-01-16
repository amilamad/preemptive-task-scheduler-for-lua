#include "lua.h"

int call_function_non_blocking(lua_State* pLuaState, const char* functionName, float dt)
{
	lua_getglobal(pLuaState, functionName);

	// lua function is resumed from the last interrupted position.
	int ret = lua_resume(pLuaState, 0);
	if (ret == LUA_YIELD)
	{
		// lua function execution is interrupted.
		return 1;
	}
	else if (ret == 0)
	{
		// lua function is returned successfully.
		return 0;
	}
	else
	{
		// Handle lua error.
		return -1;
	}
}

int main()
{
	lua_State* pLuaState = luaL_newstate();
	luaL_openlibs(pLuaState);

	int ret = luaL_dofile(pLuaState, "non_blocking_test.lua");
	if (ret != 0)
	{
		// Error loading script. Return.
		printf("luaL_dofile error \n");
		return -1;
	}

	// Add a count hook that will trigger after "count" number instructions
	int count = 100;
	lua_sethook(pLuaState, LUAHook, LUA_MASKCOUNT, count);

	while (true)
	{
		printf("lua script resumed \n");
		// Update a lua function with preemptive scheduling.
		int functionState = call_function_non_blocking(pLuaState, "heavy_function", 0.0);
		if (functionState == 0)
		{
			// lua function executed successfully.
			break;
		}
		else if (functionState == -1)
		{
			printf("CallFunctionNonBlocking error \n");
		}

		printf("lua script interrupted \n");
		
		//Do other work
		//...........
	}

	return 0;
}