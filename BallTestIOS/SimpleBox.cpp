#include "SimpleBox.h"
#include "SpriteFactory.h"
#include <assert.h>

SimpleBox::SimpleBox()
{
	mInitialized = false;
}

SimpleBox::~SimpleBox()
{
	Deinit();
}

void SimpleBox::Init(KEngineBox2D::Box2DWorld * boxWorld, KEngine2D::HierarchyUpdater * hierarchySystem, KEngineOpenGL::SpriteRenderer * renderer, SpriteFactory * spriteFactory, KEngine2D::Point position, KEngine2D::Point velocity, double angularVelocity, double width, double height, double mass)
{
	KEngine2D::StaticTransform initialTransform(position);
	mBoundary.Init(&initialTransform, width, height);
	mBoundingArea.Init(&initialTransform);
	mBoundingArea.AddBoundingBox(&mBoundary);

	mBoxMechanics.Init(boxWorld, &mBoundingArea, mass, initialTransform, velocity, angularVelocity);


	KEngine2D::Point modelUpperLeft = { -width / 2.0f, -height / 2.0f };
	KEngine2D::StaticTransform modelTransform(modelUpperLeft);

	mModelTransform.Init(hierarchySystem, &mBoxMechanics, modelTransform);

	mGraphic.Init(renderer, spriteFactory->BoxSpriteForDimensions(width, height), &mModelTransform);
	mInitialized = true;
}

void SimpleBox::Deinit()
{
	mGraphic.Deinit();
	mBoxMechanics.Deinit();
	mBoundary.Deinit();
	mInitialized = false;
}

void SimpleBox::ApplyImpulse(KEngine2D::Point impulse, KEngine2D::Point offset)
{
	assert(mInitialized);
	//TODO
}
