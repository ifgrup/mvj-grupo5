#pragma once
#include "cwalkabilityfunctor.h"
class cWalkabilityFunctorFlalling :	public cWalkabilityFunctor
{
public:
	cWalkabilityFunctorFlalling(void);
	virtual ~cWalkabilityFunctorFlalling(void);
	bool IsThisTileWalkableForMe(CTile2D*);
};

