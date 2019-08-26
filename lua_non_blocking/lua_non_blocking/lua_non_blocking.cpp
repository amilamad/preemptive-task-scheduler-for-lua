#include <exception>

#include "lua.h"
#include "lualib.h"
#include "lauxlib.h"
#include "lua_non_blocking.h"

struct ScriptRunner_impl
{
	lua_State* pLuaState = nullptr;
};

void LUAHook(lua_State* L, lua_Debug *ar)
{
	lua_yield(L, 0);
}

int call_function_non_blocking(lua_State* pLuaState, const char* functionName, float dt)
{
	lua_getglobal(pLuaState, functionName);

	// lua function is resumed from the last interrupted position.
	int ret = lua_resume(pLuaState, NULL, 0);
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

ScriptRunner::ScriptRunner(const std::string& script, const std::string& scriptFunctionToRun, std::function<void(float)> mainLoopFunction) : m_script(script),
																																		m_scriptFunctionToRun(m_scriptFunctionToRun),
																																		m_mainLoopFunction(mainLoopFunction),
																																		m_pScriptRunner_impl(std::make_unique<ScriptRunner_impl>())
{
	m_pScriptRunner_impl->pLuaState = luaL_newstate();
	luaL_openlibs(m_pScriptRunner_impl->pLuaState);

	int ret = luaL_dofile(m_pScriptRunner_impl->pLuaState, script.c_str());
	if (ret != 0)
	{
		// Error loading script. Return.
		throw std::exception("luaL_dofile error \n");
	}

	// Add a count hook that will trigger after "count" number instructions
	int count = 100;
	lua_sethook(m_pScriptRunner_impl->pLuaState, LUAHook, LUA_MASKCOUNT, count);
}

void ScriptRunner::Update(float dt)
{
	// Update a lua function with preemptive scheduling.
	int functionState = call_function_non_blocking(m_pScriptRunner_impl->pLuaState, m_scriptFunctionToRun.c_str(), 0.0);
	if (functionState == 0)
	{
		// lua function executed successfully.
		return;
	}
	else if (functionState == -1)
	{
		throw std::exception("CallFunctionNonBlocking error \n");
	}

	// Run the non script loop
	m_mainLoopFunction(dt);
}
