#include "script_system.h"

#include <lua.h>
#include <luacode.h>
#include <lualib.h>

#include <utils/file.h>

#include <stdlib.h>
#include <core/log.h>
#include <core/asset.h>

#include <core/input.h>

#define GEN_BINDING(FUNC) \
int LUA#FUNC(lua_State* L) \
{\
	FUNC();\
}\




int input_key_down_wrapper(lua_State* L)
{


	//Input::key_down();
	return 0;
}

void ScriptSystem::init()
{
	L = luaL_newstate();
	luaL_openlibs(L);


	


	//bind_function("fntest", test);
	run_script("script/test.lua");
}

void ScriptSystem::update(float dt)
{
	lua_resume(L, NULL, 0);
}

void ScriptSystem::destroy()
{

}

void ScriptSystem::bind_function(const char* name, lua_CFunction function)
{
	// bind function to lua state
	lua_pushcfunction(L, function, name);
	lua_setglobal(L, name);
}

void ScriptSystem::bind_variable(const char* name, void* variable)
{

}

void ScriptSystem::run_script(const char* file_path)
{
	size_t bytecodeSize = 0;
    char* bytecode = luau_compile(utils::file::ReadAllBytes(Asset::get_asset_path(file_path)).data(), utils::file::ReadAllBytes(Asset::get_asset_path(file_path)).size(), NULL, &bytecodeSize);

	int result = luau_load(L, "test.lua", bytecode, bytecodeSize, 0);
	free(bytecode);

}
