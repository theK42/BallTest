#pragma once

struct lua_State;
namespace KEngine2D {
	class MechanicsUpdater;
	class PhysicsSystem;
	class HierarchyUpdater;
	struct Point;
}

namespace KEngineBox2D {
	class Box2DWorld;
}

namespace KEngineOpenGL {
	class SpriteRenderer;
}
class SimpleBall;
class SimpleBox;
class SpriteFactory;

class BallLuaBinding
{
public:
	BallLuaBinding(void);
	~BallLuaBinding(void);
	void Init(lua_State * luaState, KEngineBox2D::Box2DWorld * boxWorld, KEngine2D::HierarchyUpdater * hierarchySystem, KEngineOpenGL::SpriteRenderer * renderer, SpriteFactory * spriteFactory);
	void Deinit();
	static BallLuaBinding * GetInstance();

	SimpleBall * NewBall( KEngine2D::Point & position, KEngine2D::Point & velocity, double angularVelocity, double radius, double mass );
	SimpleBox * NewBox( KEngine2D::Point & position, KEngine2D::Point & velocity, double angularVelocity, double width, double height, double mass);
private:
	lua_State *							mLuaState;
	KEngineBox2D::Box2DWorld *			mBoxWorld;
	KEngine2D::HierarchyUpdater *		mHierarchySystem;
	KEngineOpenGL::SpriteRenderer *		mRenderer;
	SpriteFactory *						mSpriteFactory;

	static BallLuaBinding *				mInstance;

};
