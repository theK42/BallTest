#pragma once
#include "Boundaries2D.h"
#include "HierarchicalTransform2D.h"
#include "SpriteRenderer.h"
#include "Box2DTransform.h"

class SpriteFactory;

class SimpleBall
{
public:
	SimpleBall();
	~SimpleBall();
	void Init(KEngineBox2D::Box2DWorld * boxWorld, KEngine2D::HierarchyUpdater * hierarchySystem, KEngineOpenGL::SpriteRenderer * renderer, SpriteFactory * spriteFactory, KEngine2D::Point position, KEngine2D::Point velocity, double angularVelocity, double radius, double mass);
	void Deinit();

	void ApplyImpulse(KEngine2D::Point impulse);

private:
	KEngineBox2D::Box2DTransform				mBoxMechanics;
	KEngine2D::UpdatingHierarchicalTransform	mModelTransform;
	KEngine2D::BoundingArea						mBoundingArea;
	KEngine2D::BoundingCircle					mBoundary;
	KEngineOpenGL::SpriteGraphic				mGraphic;
	bool										mInitialized;
};