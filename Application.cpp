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
}

int main()
{

	std::string cmd = "a = 7 + 11 + math.sin(23.7)";

	lua_State* L = luaL_newstate();
	luaL_openlibs(L);

	int r = luaL_dostring(L, cmd.c_str());

	if (r == LUA_OK)
	{
		lua_getglobal(L, "a");
		if (lua_isnumber(L, -1))
		{
			float a_in_cpp = (float)lua_tonumber(L, -1);
			std::cout << "a_in_cpp = " << a_in_cpp << std::endl;

		}
	}
	else
	{
		std::string errormsg = lua_tostring(L, -1);
		std::cout << errormsg << std::endl;


	}
	system("pause");
	lua_close(L);
	return 0;
}