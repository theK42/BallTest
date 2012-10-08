#pragma once

struct lua_State;
namespace KEngine2D {
	class MechanicsUpdater;
	class PhysicsSystem;
	class HierarchyUpdater;
	struct Point;
}

namespace KEngineMac {
	class ConsoleRenderer;
}

class SimpleBall;

class BallLuaBinding
{
public:
	BallLuaBinding(void);
	~BallLuaBinding(void);
	void Init(lua_State * luaState, KEngine2D::MechanicsUpdater * mechanicsSystem, KEngine2D::PhysicsSystem * physicsSystem, KEngine2D::HierarchyUpdater * hierarchySystem, KEngineMac::ConsoleRenderer * renderer);
	void Deinit();
	static BallLuaBinding * GetInstance();

	SimpleBall * NewBall( KEngine2D::Point & position, KEngine2D::Point & velocity, double radius, double mass );
private:
	lua_State *							mLuaState;
	KEngine2D::MechanicsUpdater *		mMechanicsSystem;
	KEngine2D::PhysicsSystem *			mPhysicsSystem;
	KEngine2D::HierarchyUpdater *		mHierarchySystem;
	KEngineMac::ConsoleRenderer *		mRenderer;
	static BallLuaBinding *				mInstance;

};

