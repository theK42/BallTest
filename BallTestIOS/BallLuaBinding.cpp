#include "BallLuaBinding.h"
#include "SimpleBall.h"

#include "Lua/lua.hpp"
#include "Lua/lauxlib.h"

#include <assert.h> 


BallLuaBinding * BallLuaBinding::mInstance = nullptr;

BallLuaBinding * BallLuaBinding::GetInstance() {
	return mInstance;
}

BallLuaBinding::BallLuaBinding(void)
{
	mLuaState = nullptr;
}

BallLuaBinding::~BallLuaBinding(void)
{
	Deinit();
}

int newBall(lua_State * luaState) {
	if (!lua_istable(luaState, 1)) {
		luaL_error(luaState, "Table required for position");
	}
	lua_getfield(luaState, 1, "x");
	double x = luaL_checknumber(luaState, -1);
	lua_pop(luaState, 1);

	lua_getfield(luaState, 1, "y");
	double y = luaL_checknumber(luaState, -1);
	lua_pop(luaState, 1);

	KEngine2D::Point position = {x, y};

	if (!lua_istable(luaState, 2)) {
		luaL_error(luaState, "Table required for velocity");
	}
	lua_getfield(luaState, 2, "vx");
	double vx = luaL_checknumber(luaState, -1);
	lua_pop(luaState, 1);

	lua_getfield(luaState, 2, "vy");
	double vy = luaL_checknumber(luaState, -1);
	lua_pop(luaState, 1);
	
	KEngine2D::Point velocity = {vx, vy};

	double radius = luaL_checknumber(luaState, 3);
	double mass = luaL_checknumber(luaState, 4);

	SimpleBall * ball = BallLuaBinding::GetInstance()->NewBall(position, velocity, radius, mass);

	lua_pushlightuserdata(luaState, ball); //Probably want a full userdata

	return 1;
}

const struct luaL_Reg ballLibrary [] = {
	{"new", newBall},
	{nullptr, nullptr}
};

int luaopen_ball (lua_State * luaState) {
	luaL_newlib(luaState, ballLibrary);
	return 1;
};

void BallLuaBinding::Init(lua_State * luaState, KEngine2D::MechanicsUpdater * mechanicsSystem, KEngine2D::PhysicsSystem * physicsSystem, KEngine2D::HierarchyUpdater * hierarchySystem, KEngineOpenGL::SpriteRenderer * renderer, BallSpriteFactory * spriteFactory) {
	assert(mInstance == nullptr);
	mInstance = this;
	mLuaState = luaState;
	mMechanicsSystem = mechanicsSystem;
	mPhysicsSystem = physicsSystem;
	mHierarchySystem = hierarchySystem;
	mRenderer = renderer;
    mSpriteFactory = spriteFactory;

	lua_getglobal(luaState, "package");
	lua_getfield(luaState, -1, "preload");
	lua_pushcfunction(luaState, luaopen_ball);
	lua_setfield(luaState, -2, "ball");
	lua_pop(luaState, 2);
}

void BallLuaBinding::Deinit() {
	if (mInstance == this) {
		mInstance = nullptr;
	}

	lua_getglobal(mLuaState, "package");
	lua_getfield(mLuaState, -1, "preload");
	lua_pushnil(mLuaState);
	lua_setfield(mLuaState, -2, "ball");
	lua_pop(mLuaState, 2);
}

SimpleBall * BallLuaBinding::NewBall(KEngine2D::Point & position, KEngine2D::Point & velocity, double radius, double mass) {
	SimpleBall * ball = new SimpleBall();
	ball->Init(mMechanicsSystem, mPhysicsSystem, mHierarchySystem, mRenderer, mSpriteFactory, position, velocity, radius, mass);
	return ball;
}
