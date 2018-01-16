#pragma once

#include "Boundaries2D.h"
#include "HierarchicalTransform2D.h"
#include "SpriteRenderer.h"
#include "Box2DTransform.h"

class SpriteFactory;

class SimpleBox
{
public:
	SimpleBox();
	~SimpleBox();
	void Init(KEngineBox2D::Box2DWorld * boxWorld, KEngine2D::HierarchyUpdater * hierarchySystem, KEngineOpenGL::SpriteRenderer * renderer, SpriteFactory * spriteFactory, KEngine2D::Point position, KEngine2D::Point velocity, double angularVelocity, double width, double height, double mass);
	void Deinit();

	void ApplyImpulse(KEngine2D::Point impulse, KEngine2D::Point offset);

private:
	KEngineBox2D::Box2DTransform				mBoxMechanics;
	KEngine2D::UpdatingHierarchicalTransform	mModelTransform;
	KEngine2D::BoundingArea						mBoundingArea;
	KEngine2D::BoundingBox						mBoundary;
	KEngineOpenGL::SpriteGraphic				mGraphic;
	bool										mInitialized;
};

