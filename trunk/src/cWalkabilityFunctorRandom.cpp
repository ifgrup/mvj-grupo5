#include "cWalkabilityFunctorRandom.h"


cWalkabilityFunctorRandom::cWalkabilityFunctorRandom(void)
{
}


cWalkabilityFunctorRandom::~cWalkabilityFunctorRandom(void)
{
}

bool cWalkabilityFunctorRandom::IsThisTileWalkableForMe(CTile2D* pTile)
{
	if (!pTile->IsWalkeable())
		return false;

	
	return true;
}