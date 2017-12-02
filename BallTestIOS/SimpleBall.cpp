#include "SimpleBall.h"
#include "BallSprite.h"
#include <cmath>
#include <assert.h>


SimpleBall::SimpleBall()
{
	mInitialized = false;
}

SimpleBall::~SimpleBall()
{
	Deinit();
}

void SimpleBall::Init(KEngine2D::MechanicsUpdater * mechanicsSystem, KEngine2D::PhysicsSystem * physicsSystem, KEngine2D::HierarchyUpdater * hierarchySystem, KEngineOpenGL::SpriteRenderer * renderer, BallSpriteFactory * spriteFactory, KEngine2D::Point position, KEngine2D::Point velocity, float radius, float mass)
{
	KEngine2D::StaticTransform initialTransform(position);
	mMechanics.Init(mechanicsSystem, position, velocity);

	mBoundary.Init(&mMechanics, radius);
	
	std::vector<KEngine2D::BoundingCircle *> bounds(1, &mBoundary);

	mPhysics.Init(physicsSystem, &mMechanics, bounds, mass);
    
    KEngine2D::Point modelUpperLeft = {-radius, -radius};
	KEngine2D::StaticTransform modelTransform(modelUpperLeft);

	mModelTransform.Init(hierarchySystem, &mMechanics, modelTransform);

	mGraphic.Init(renderer, spriteFactory->BallSpriteForRadius(radius), &mModelTransform);
    
	mInitialized = true;
}

void SimpleBall::Deinit()
{
	mGraphic.Deinit();
	mPhysics.Deinit();
	mBoundary.Deinit();
	mMechanics.Deinit();
	mInitialized = false;
}

void SimpleBall::ApplyImpulse( KEngine2D::Point impulse )
{
	assert(mInitialized);
	mPhysics.ApplyImpulse(impulse);
}
