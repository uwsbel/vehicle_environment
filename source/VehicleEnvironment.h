#pragma once

#include "BaseOgreApplication.h"


class VehicleEnvironmentApplication : public BaseOgreApplication {
public:
	VehicleEnvironmentApplication();
	~VehicleEnvironmentApplication();

protected:
	virtual void createScene();
	virtual void destroyScene();
	virtual void createCamera();
	virtual void createViewports();
private:
};

