#pragma once

struct lua_State;
namespace KEngine2D {
	class MechanicsUpdater;
	class PhysicsSystem;
	class HierarchyUpdater;
	struct Point;
}

namespace KEngineOpenGL {
	class SpriteRenderer;
}
class SimpleBall;
class BallSpriteFactory;

class BallLuaBinding
{
public:
	BallLuaBinding(void);
	~BallLuaBinding(void);
	void Init(lua_State * luaState, KEngine2D::MechanicsUpdater * mechanicsSystem, KEngine2D::PhysicsSystem * physicsSystem, KEngine2D::HierarchyUpdater * hierarchySystem, KEngineOpenGL::SpriteRenderer * renderer, BallSpriteFactory * spriteFactory);
	void Deinit();
	static BallLuaBinding * GetInstance();

	SimpleBall * NewBall( KEngine2D::Point & position, KEngine2D::Point & velocity, double radius, double mass );
private:
	lua_State *							mLuaState;
	KEngine2D::MechanicsUpdater *		mMechanicsSystem;
	KEngine2D::PhysicsSystem *			mPhysicsSystem;
	KEngine2D::HierarchyUpdater *		mHierarchySystem;
	KEngineOpenGL::SpriteRenderer *		mRenderer;
	BallSpriteFactory *                 mSpriteFactory;

	static BallLuaBinding *				mInstance;

};
