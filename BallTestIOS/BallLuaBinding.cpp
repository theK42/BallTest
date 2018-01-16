#include "BallLuaBinding.h"
#include "SimpleBall.h"
#include "SimpleBox.h"
#include "SpriteFactory.h"

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

	KEngine2D::Point position = { x, y };

	if (!lua_istable(luaState, 2)) {
		luaL_error(luaState, "Table required for velocity");
	}
	lua_getfield(luaState, 2, "vx");
	double vx = luaL_checknumber(luaState, -1);
	lua_pop(luaState, 1);

	lua_getfield(luaState, 2, "vy");
	double vy = luaL_checknumber(luaState, -1);
	lua_pop(luaState, 1);

	KEngine2D::Point velocity = { vx, vy };

	double angularVelocity = luaL_checknumber(luaState, 3);

	double radius = luaL_checknumber(luaState, 4);
	double mass = luaL_checknumber(luaState, 5);

	SimpleBall * ball = BallLuaBinding::GetInstance()->NewBall(position, velocity, angularVelocity, radius, mass);

	lua_pushlightuserdata(luaState, ball); //Probably want a full userdata

	return 1;
}

int newBox(lua_State * luaState) {
	if (!lua_istable(luaState, 1)) {
		luaL_error(luaState, "Table required for position");
	}
	lua_getfield(luaState, 1, "x");
	double x = luaL_checknumber(luaState, -1);
	lua_pop(luaState, 1);

	lua_getfield(luaState, 1, "y");
	double y = luaL_checknumber(luaState, -1);
	lua_pop(luaState, 1);

	KEngine2D::Point position = { x, y };

	if (!lua_istable(luaState, 2)) {
		luaL_error(luaState, "Table required for velocity");
	}
	lua_getfield(luaState, 2, "vx");
	double vx = luaL_checknumber(luaState, -1);
	lua_pop(luaState, 1);

	lua_getfield(luaState, 2, "vy");
	double vy = luaL_checknumber(luaState, -1);
	lua_pop(luaState, 1);

	KEngine2D::Point velocity = { vx, vy };

	double angularVelocity = luaL_checknumber(luaState, 3);

	double width = luaL_checknumber(luaState, 4);
	double height = luaL_checknumber(luaState, 5);
	double mass = luaL_checknumber(luaState, 6);

	SimpleBox * box = BallLuaBinding::GetInstance()->NewBox(position, velocity, angularVelocity, width, height, mass);

	lua_pushlightuserdata(luaState, box); //Probably want a full userdata

	return 1;
}

int hitBox(lua_State * luaState) {

	if (!lua_islightuserdata(luaState, 1)) {
		luaL_error(luaState, "Box required");
	}
	SimpleBox * box = (SimpleBox*)lua_touserdata(luaState, 1);
	if (!lua_istable(luaState, 2)) {
		luaL_error(luaState, "Table required for impulse");
	}
	lua_getfield(luaState, 2, "ix");
	double ix = luaL_checknumber(luaState, -1);
	lua_pop(luaState, 1);

	lua_getfield(luaState, 2, "iy");
	double iy = luaL_checknumber(luaState, -1);
	lua_pop(luaState, 1);

	lua_getfield(luaState, 2, "ox");
	double ox = luaL_checknumber(luaState, -1);
	lua_pop(luaState, 1);

	lua_getfield(luaState, 2, "oy");
	double oy = luaL_checknumber(luaState, -1);
	lua_pop(luaState, 1);

	KEngine2D::Point impulse = { ix, iy };
	KEngine2D::Point offset = { ox, oy };

	box->ApplyImpulse(impulse, offset);
	return 1;	
}


const struct luaL_Reg ballLibrary [] = {
	{ "newBall", newBall },
	{ "newBox", newBox },
	{ "hitBox", hitBox },
	{nullptr, nullptr}
};

int luaopen_ball (lua_State * luaState) {
	luaL_newlib(luaState, ballLibrary);	
	return 1;
};

void BallLuaBinding::Init(lua_State * luaState,
						  KEngineBox2D::Box2DWorld * boxWorld,
						  KEngine2D::HierarchyUpdater * hierarchySystem,
						  KEngineOpenGL::SpriteRenderer * renderer,
						  SpriteFactory * spriteFactory) {
	assert(mInstance == nullptr);
	mInstance = this;
	mLuaState = luaState;
	mBoxWorld = boxWorld;
	mHierarchySystem = hierarchySystem;
	mRenderer = renderer;
	mSpriteFactory = spriteFactory;

	lua_getglobal(luaState, "package");
	lua_getfield(luaState, -1, "preload");
	lua_pushcfunction(luaState, luaopen_ball);
	lua_setfield(luaState, -2, "ballTest");
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

SimpleBall * BallLuaBinding::NewBall(KEngine2D::Point & position, KEngine2D::Point & velocity, double angularVelocity, double radius, double mass) {
	SimpleBall * ball = new SimpleBall();
	ball->Init(mBoxWorld,mHierarchySystem, mRenderer, mSpriteFactory, position, velocity, angularVelocity, radius, mass);
	return ball;
}

SimpleBox * BallLuaBinding::NewBox(KEngine2D::Point & position, KEngine2D::Point & velocity, double angularVelocity, double width, double height, double mass) {
	SimpleBox * box = new SimpleBox();
	box->Init(mBoxWorld, mHierarchySystem, mRenderer, mSpriteFactory, position, velocity, angularVelocity, width, height, mass);
	return box;
}
