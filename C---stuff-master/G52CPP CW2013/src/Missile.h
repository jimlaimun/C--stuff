#pragma once
#include "DisplayableObject.h"
#include "MovementPosition.h"
#include "MyProjectMain.h"
#include "JPGImage.h"

class BaseEngine;
class TileManager;

class Missile :
	public DisplayableObject
{
public:
	Missile(MyProjectMain* pEngine, int iID, 
		int iDrawType, int iSize, int iColour);

	~Missile(void);
	void startup();
	void Draw(void);
	void DoUpdate(int CurrentTime);
	void SetMovement(int Start, int End, int Current, int startX, int startY, int endX, int endY);
	void reset();
	
private:

	MyProjectMain* Engine;

	// Unique id for object, passed to engine to identify it
	int ID;

	// Type of thing to draw
	int DrawType;

	// Size of thing to draw
	int Size;

	// Colour index to draw with
	int Colour;

	// Label to apply
	char* score;

	//initial x Position
	int initX;
	//random delay
	int randStart;
	//result of random function
	int result ;
	//x target
	int tarX ;
	//y target
	int tarY ;
	int timepassed;
	int diff;
	
protected:
	/** Movement position calculator - give it start and end position and times 
	and it works out current position for the current time. 
	Notice also the MyMovementPosition class. */
	MovementPosition m_oMovement;

	// Pointer to the tile manager - we are going to use this!
	TileManager* m_pTileManager;

	MyProjectMain** getMain();
};

