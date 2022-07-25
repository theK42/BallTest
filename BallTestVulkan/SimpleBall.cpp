#include "SimpleBall.h"
#include "SpriteFactory.h"
#include <assert.h>

SimpleBall::SimpleBall()
{
	mInitialized = false;
}

SimpleBall::~SimpleBall()
{
	Deinit();
}

void SimpleBall::Init(KEngineBox2D::Box2DWorld * boxWorld, KEngine2D::HierarchyUpdater * hierarchySystem, KEngineVulkan::SpriteRenderer * renderer, SpriteFactory * spriteFactory, KEngine2D::Point position, KEngine2D::Point velocity, double angularVelocity, double radius, double mass)
{
	KEngine2D::StaticTransform initialTransform(position);
	mBoundary.Init(&initialTransform, radius);
	mBoundingArea.Init(&initialTransform);
	mBoundingArea.AddBoundingCircle(&mBoundary);

	mBoxMechanics.Init(boxWorld, &mBoundingArea, mass, initialTransform, velocity, angularVelocity);


	KEngine2D::Point modelUpperLeft = {-radius, -radius};
	KEngine2D::StaticTransform modelTransform(modelUpperLeft);

	mModelTransform.Init(hierarchySystem, &mBoxMechanics, modelTransform); 
	
	mGraphic.Init(renderer, spriteFactory->BallSpriteForRadius(radius), &mModelTransform);
	mInitialized = true;
}

void SimpleBall::Deinit()
{
	mGraphic.Deinit();
	mBoxMechanics.Deinit();
	mBoundary.Deinit();
	mInitialized = false;
}

void SimpleBall::ApplyImpulse( KEngine2D::Point impulse )
{
	assert(mInitialized);
	//TODO
}