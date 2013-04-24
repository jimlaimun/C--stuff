#pragma once
#include "DisplayableObject.h"
#include "MyProjectMain.h"

class BaseEngine;

class Base :
	public DisplayableObject
{
public:
	Base(MyProjectMain* mEngine,int id,int size,int x, int y);
	~Base(void);
	int getX();
	int getY();
	int getId();

	void Draw(void);
	void DoUpdate(int CurrentTime);

	
	

	

	enum State { stateinit,statemain,statepause,stateHscore };
private:
	int xCoord;
	int yCoord;
	int ID;
	int Size;
	MyProjectMain* BEngine;

};

