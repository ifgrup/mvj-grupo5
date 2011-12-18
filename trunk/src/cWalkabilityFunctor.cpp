#include "cWalkabilityFunctor.h"


cWalkabilityFunctor::cWalkabilityFunctor(void)
{
}


cWalkabilityFunctor::~cWalkabilityFunctor(void)
{
}

bool cWalkabilityFunctor::IsThisTileWalkableForMe(CTile2D* pTile)
{
	//La de por defecto, la del prota. Debe ser walkeable por mapa, y no tener fuego.
	return pTile->IsWalkeable() && !pTile->IsFired();
}
