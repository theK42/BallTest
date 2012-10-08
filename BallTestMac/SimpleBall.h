#pragma once
#include "Boundaries2D.h"
#include "MechanicalTransform2D.h"
#include "HierarchicalTransform2D.h"
#include "Physics2D.h"
#include "ConsoleRenderer.h"

class SimpleBall
{
public:
	SimpleBall();
	~SimpleBall();
	void Init(KEngine2D::MechanicsUpdater * mechanicsSystem, KEngine2D::PhysicsSystem * physicsSystem, KEngine2D::HierarchyUpdater * hierarchySystem, KEngineMac::ConsoleRenderer * renderer, KEngine2D::Point position, KEngine2D::Point velocity, float radius, float mass);
	void Deinit();

	void ApplyImpulse(KEngine2D::Point impulse);

private:
	KEngine2D::UpdatingMechanicalTransform		mMechanics;
	KEngine2D::UpdatingHierarchicalTransform	mModelTransform;
	KEngine2D::BoundingCircle					mBoundary;
	KEngine2D::PhysicalObject					mPhysics;
	KEngineMac::ConsoleGraphic					mGraphic;
	bool										mInitialized;
};