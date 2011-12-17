#pragma once
#include "CTile2D.h"

class cWalkabilityFunctor
{
public:
	cWalkabilityFunctor(void);
	virtual ~cWalkabilityFunctor(void);
	virtual bool IsThisTileWalkableForMe(CTile2D*);
};

