#define AMULET_LUA_MODULE_NAME "amulet"

void am_set_globals_metatable(lua_State *L);
void am_requiref(lua_State *L, const char *modname, lua_CFunction openf);
void am_open_module(lua_State *L, const char *name, luaL_Reg *funcs);

struct am_enum_value {
    const char *str;
    int val;
};

void am_register_enum(lua_State *L, int enum_id, am_enum_value *values);
int am_get_enum_raw(lua_State *L, int enum_id, int idx);
#define am_get_enum(L, e, idx) ((e)am_get_enum_raw((L), ENUM_##e, (idx)))

int am_check_nargs(lua_State *L, int n);

void am_init_traceback_func(lua_State *L);
bool am_call(lua_State *L, int nargs, int nresults);
bool am_call_amulet(lua_State *L, const char *func, int nargs, int nresults);
bool am_run_script(lua_State *L, const char *script, const char *name);

// The caller must ensure v is live and was created
// with lua_newuserdata.
void lua_unsafe_pushuserdata(lua_State *L, void *v);

int am_load_module(lua_State *L);
int am_package_searcher(lua_State *L);

#ifdef AM_LUAJIT
void lua_setuservalue(lua_State *L, int idx);
void lua_getuservalue(lua_State *L, int idx);
int lua_rawlen(lua_State *L, int idx);
lua_Integer lua_tointegerx(lua_State *L, int idx, int *isnum);
lua_Number lua_tonumberx(lua_State *L, int idx, int *isnum);
#endif

#define am_absindex(L, idx) ((idx) > 0 ? (idx) : lua_gettop(L) + (idx) + 1)
