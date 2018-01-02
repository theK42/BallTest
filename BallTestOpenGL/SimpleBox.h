#pragma once

#include "Boundaries2D.h"
#include "MechanicalTransform2D.h"
#include "HierarchicalTransform2D.h"
#include "Physics2D.h"
#include "SpriteRenderer.h"

class SpriteFactory;

class SimpleBox
{
public:
	SimpleBox();
	~SimpleBox();
	void Init(KEngine2D::MechanicsUpdater * mechanicsSystem, KEngine2D::PhysicsSystem * physicsSystem, KEngine2D::HierarchyUpdater * hierarchySystem, KEngineOpenGL::SpriteRenderer * renderer, SpriteFactory * spriteFactory, KEngine2D::Point position, KEngine2D::Point velocity, double angularVelocity, double width, double height, double mass);
	void Deinit();

	void ApplyImpulse(KEngine2D::Point impulse, KEngine2D::Point offset);

private:
	KEngine2D::UpdatingMechanicalTransform		mMechanics;
	KEngine2D::UpdatingHierarchicalTransform	mModelTransform;
	KEngine2D::BoundingArea						mBoundingArea;
	KEngine2D::BoundingBox						mBoundary;
	KEngine2D::PhysicalObject					mPhysics;
	KEngineOpenGL::SpriteGraphic				mGraphic;
	bool										mInitialized;
};

