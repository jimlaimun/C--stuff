#pragma once
#include "baseengine.h"
class DemoAMain :
	public BaseEngine
{
public:
	DemoAMain(void);
	~DemoAMain(void);
	void SetupBackgroundBuffer(void);
	void MouseDown(int iButton, int iX, int iY);
};

