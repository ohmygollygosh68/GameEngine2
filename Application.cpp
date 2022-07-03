#include <iostream>
#include <string>

extern "C"
{
#include "lua536/include/lua.h"
#include "lua536/include/lauxlib.h"
#include "lua536/include/lualib.h"
}

#ifdef _WIN64
#pragma comment(lib, "lua536/liblua53.a")
#endif

bool CheckLua(lua_State* L, int r)
{
	if (r != LUA_OK)
	{
		std::string errormsg = lua_tostring(L, -1);
		std::cout << errormsg << std::endl;
		return false;
	}
	return true;
}

int lua_HostFunction(lua_State *L)
{
	// int n = lua_gettop(L) returns the number of arguments. Not used here.
	float a = (float)lua_tonumber(L, 1); // Fresh stack so not necessary to use -1 although this does work
	float b = (float)lua_tonumber(L, 2);
	std::cout << "[C++] HostFunction(" << a << ", " << b << ") called" << std::endl;
	float c = a * b;
	lua_pushnumber(L, c);
	return 1; // This is just the number of arguments passed back to Lua. In this case the value used for variable c. It does not have to be just 1.

}

int main()
{

	struct Player
	{
		std::string title;
		std::string name;
		std::string family;
		int level;
	} player;

	// Create Lua State
	lua_State* L = luaL_newstate();

	// Add standard libraries to Lua Virtual Machine
	luaL_openlibs(L);
	// Link the C++ function to the virtual machine
	lua_register(L, "HostFunction", lua_HostFunction);

	if(CheckLua(L, luaL_dofile(L, "VideoExample.lua")))
	{
		lua_getglobal(L, "DoAThing");
		if (lua_isfunction(L, -1))
		{
			lua_pushnumber(L, 5.0f);
			lua_pushnumber(L, 6.0f);
			if (CheckLua(L, lua_pcall(L, 2, 1, 0)))
			{
				std::cout << "[C++] Called in Lua 'DoAThing(5.0f, 6.0f)', got "
					<< (float)lua_tonumber(L, -1) << std::endl;
			}
		}
	}


	system("pause");
	lua_close(L);
	return 0;
}