#pragma once

// system is a global thing that 

struct lua_State;
typedef int (*lua_CFunction)(lua_State* L);

class ScriptSystem
{
public:
	ScriptSystem() {};
	~ScriptSystem() {};

	void init();
	void update(float dt);
	void destroy();

	void bind_function(const char* name, lua_CFunction function);
	void bind_variable(const char* name, void* variable);

	void run_script(const char* file_path);
private:
	lua_State* L;
};