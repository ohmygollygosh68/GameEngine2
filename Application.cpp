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

	if(CheckLua(L, luaL_dofile(L, "VideoExample.lua")))
	{
		// Read Table Object
		lua_getglobal(L, "player");
		if (lua_istable(L, -1))
		{
			lua_pushstring(L, "Name");
			lua_gettable(L, -2);
			player.name = lua_tostring(L, -1);
			lua_pop(L, 1);

			lua_pushstring(L, "Family");
			lua_gettable(L, -2);
			player.family = lua_tostring(L, -1);
			lua_pop(L, 1);

			lua_pushstring(L, "Title");
			lua_gettable(L, -2);
			player.title = lua_tostring(L, -1);
			lua_pop(L, 1);

			// Note for Level the key is a string but we are expecting an integer
			lua_pushstring(L, "Level");
			lua_gettable(L, -2);
			player.level = lua_tointeger(L, -1);
			lua_pop(L, 1);

		}

		std::cout << player.title << " " << player.name << " of " <<
			player.family << "[Lvl: " << player.level << "]" << std::endl;

	}


	system("pause");
	lua_close(L);
	return 0;
}