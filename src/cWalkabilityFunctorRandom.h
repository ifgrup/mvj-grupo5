#pragma once
#include "cwalkabilityfunctor.h"
class cWalkabilityFunctorRandom :	public cWalkabilityFunctor
{
public:
	cWalkabilityFunctorRandom(void);
	virtual ~cWalkabilityFunctorRandom(void);
	bool IsThisTileWalkableForMe(CTile2D*);
};

