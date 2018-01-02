#include "stdafx.h"
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

void SimpleBox::Init(KEngine2D::MechanicsUpdater * mechanicsSystem, KEngine2D::PhysicsSystem * physicsSystem, KEngine2D::HierarchyUpdater * hierarchySystem, KEngineOpenGL::SpriteRenderer * renderer, SpriteFactory * spriteFactory, KEngine2D::Point position, KEngine2D::Point velocity, double angularVelocity, double width, double height, double mass)
{
	KEngine2D::StaticTransform initialTransform(position);
	mMechanics.Init(mechanicsSystem, position, velocity, angularVelocity);

	mBoundary.Init(&mMechanics, width, height);
	mBoundingArea.Init(&mMechanics);
	mBoundingArea.AddBoundingBox(&mBoundary);
	mPhysics.Init(physicsSystem, &mMechanics, &mBoundingArea, mass);

	KEngine2D::Point modelUpperLeft = { -width / 2.0f, -height / 2.0f };
	KEngine2D::StaticTransform modelTransform(modelUpperLeft);

	mModelTransform.Init(hierarchySystem, &mMechanics, modelTransform);

	mGraphic.Init(renderer, spriteFactory->BoxSpriteForDimensions(width, height), &mModelTransform);
	mInitialized = true;
}

void SimpleBox::Deinit()
{
	mGraphic.Deinit();
	mPhysics.Deinit();
	mBoundary.Deinit();
	mMechanics.Deinit();
	mInitialized = false;
}

void SimpleBox::ApplyImpulse(KEngine2D::Point impulse, KEngine2D::Point offset)
{
	assert(mInitialized);
	mPhysics.ApplyImpulse(impulse, offset);
}