#pragma once
#include "CameraObserver.h"

class CameraObservable
{
public:
	virtual void addCameraObserver(CameraObserver* observer) = 0;
	virtual void removeCameraObserver(CameraObserver* observer) = 0;

	virtual void notifyCameraObservers() = 0;
};