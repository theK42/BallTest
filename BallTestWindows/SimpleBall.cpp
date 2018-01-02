#include "SimpleBall.h"
#include <assert.h>

static KEngineWindows::CharMap circleMaps[] = {
	{1,1,	"O"}, //Radius .5 and below

	{2,2,	"OO"
			"OO"}, //Radius 1

	{3,3,	" O "
			"O O"
			" O "}, //Radius 1.5

	{4,4,	" OO "
			"O  O"
			"O  O"
			" OO "}, //Radius 2
			
	{5,5,	" OOO "
			"O   O"
			"O   O"
			"O   O"
			" OOO "}, //Radius 2.5

	{6,6,	"  OO  "
			" O  O "
			"O    O"
			"O    O"
			" O  O "			
			"  OO  "}, //Radius 3
			
	{7,7,	"  OOO  "
			" O   O "
			"O     O"
			"O     O"
			"O     O"
			" O   O "
			"  OOO  "}, //Radius 3.5

	{8,8,	"  OOOO  "
			" O    O "
			"O      O"
			"O      O"
			"O      O"
			"O      O"
			" O    O "
			"  OOOO  "}, //Radius 4
			
	{9,9,	"   OOO   "
			"  O   O  "
			" O     O "
			"O       O"
			"O       O"
			"O       O"
			" O     O "
			"  O   O  "
			"   OOO   "} //Radius 4.5
};

SimpleBall::SimpleBall()
{
	mInitialized = false;
}

SimpleBall::~SimpleBall()
{
	Deinit();
}

void SimpleBall::Init(KEngine2D::MechanicsUpdater * mechanicsSystem, KEngine2D::PhysicsSystem * physicsSystem, KEngine2D::HierarchyUpdater * hierarchySystem, KEngineWindows::ConsoleRenderer * renderer, KEngine2D::Point position, KEngine2D::Point velocity, double radius, double mass)
{
	KEngine2D::StaticTransform initialTransform(position);
	mMechanics.Init(mechanicsSystem, position, velocity);

	mBoundary.Init(&mMechanics, radius);
	
	std::vector<KEngine2D::BoundingCircle *> bounds(1, &mBoundary);
	mBoundingArea.Init(&mMechanics);
	mBoundingArea.AddBoundingCircle(&mBoundary);

	mPhysics.Init(physicsSystem, &mMechanics, &mBoundingArea, mass);

	KEngine2D::Point modelUpperLeft = {-radius, -radius};
	KEngine2D::StaticTransform modelTransform(modelUpperLeft);

	mModelTransform.Init(hierarchySystem, &mMechanics, modelTransform); 

	assert(radius <= 4.5); // Current highest supported radius
	int index = int(abs(radius - .0001) * 2);

	mGraphic.Init(renderer, &circleMaps[index], &mModelTransform);
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