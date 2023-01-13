#pragma once
#include	 "Mof.h"
#include     "GameDefine.h"

class CPublicFunction
{
public:
	float Animation(float startTime, float endTime, float startKey, float endKey, float time)
	{
		float animationTime = endTime - startTime;
		float animationValue = endKey - startKey;

		float t = (time - startTime) / animationTime;
		t = MOF_CLIPING(t, 0, 1);
		return startKey + animationValue * t;
	}
};
