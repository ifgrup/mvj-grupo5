#include "cWalkabilityFunctorFlalling.h"


cWalkabilityFunctorFlalling::cWalkabilityFunctorFlalling(void)
{
}


cWalkabilityFunctorFlalling::~cWalkabilityFunctorFlalling(void)
{
}

bool cWalkabilityFunctorFlalling::IsThisTileWalkableForMe(CTile2D* pTile)
{
	return !pTile->IsFired();
}