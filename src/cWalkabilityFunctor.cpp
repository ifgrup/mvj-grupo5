#include "cWalkabilityFunctor.h"


cWalkabilityFunctor::cWalkabilityFunctor(void)
{
}


cWalkabilityFunctor::~cWalkabilityFunctor(void)
{
}

bool cWalkabilityFunctor::IsThisTileWalkableForMe(CTile2D* pTile)
{
	return pTile->IsWalkeable() && !pTile->IsFired();
}
