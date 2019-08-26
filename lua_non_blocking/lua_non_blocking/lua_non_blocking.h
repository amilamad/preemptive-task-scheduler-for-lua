#pragma once

#include <string>
#include <functional>
#include <memory>

class ScriptRunner_impl;

class ScriptRunner 
{
public:
	ScriptRunner(const std::string& script, const std::string& scriptFunctionToRun, std::function<void(float)> mainLoopFunction);
	void Update(float dt);

private:
	std::string m_script;
	std::string m_scriptFunctionToRun;
	std::function<void(float)> m_mainLoopFunction;

	std::unique_ptr<ScriptRunner_impl> m_pScriptRunner_impl = nullptr;
};