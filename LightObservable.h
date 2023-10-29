#pragma once
#include "LightObserver.h"

class LightObservable
{
public:
	virtual void addLightObserver(LightObserver* obs) = 0;
	virtual void removeLightObserver(LightObserver* obs) = 0;

	virtual void notifyLightObservers() = 0;
};
