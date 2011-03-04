#include <stdio.h>
#include "lua.h"       /* Kernfunktionen */
#include "lauxlib.h"   /* Hilfsfunktionen */
#include "lualib.h"    /* die Bibliotheken */

int main (int argc, char *argv[])
{
	int result;
	lua_State *L = luaL_newstate();
	luaL_openlibs(L);
	result = (luaL_loadfile(L, "script.lua") || lua_pcall(L, 0, 0, 0));
	if (result){
		fprintf(stderr, "EP!C ERROR: Failed to load lua skript: %s!\n", lua_tostring(L, -1));
	}
	lua_getglobal(L, "rand_vel_x");
	if(lua_tointeger(L, 1))
	{
		lua_getglobal(L, "vel_x_max");
		lua_getglobal(L, "vel_x_min");
		lua_getglobal(L, "vel_x_div");
		printf("Max: %f; Min: %f; Div: %f;\n",lua_tonumber(L, 2),lua_tonumber(L, 3),lua_tonumber(L, 4));
	}
	else 
		printf("norandom!!1 :D\n");
	lua_close(L);
	return 0;
}
