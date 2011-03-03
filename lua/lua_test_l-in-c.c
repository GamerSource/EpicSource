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
		fprintf(stderr, "Fehler beim Ausführen des Skripts !\n");
	}
	fprintf (stdout, "Ausgabe von C\n");
	lua_close(L);
	return 0;
}
