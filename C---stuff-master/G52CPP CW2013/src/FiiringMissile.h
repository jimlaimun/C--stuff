#pragma once
#include "DisplayableObject.h"
#include "MyProjectMain.h"
#include "MovementPosition.h"

class BaseEngine;
class FiiringMissile :
	public DisplayableObject
{
public:
	FiiringMissile(MyProjectMain* pEngine, int iID,int xstart,int ystart,int xend,int yend);
	~FiiringMissile(void);
	
	void DoUpdate(int CurrentTime);
	void Draw();
	void SetMovement(int Start, int End, int Current, int startX, int startY, int endX, int endY);
	// Handle pressing of a mouse button
	void MouseDown( int iButton, int iX, int iY );
	// gets id of current this class
	int GetID();

private:
	//coordinate placement for setting movment
	int xcoord;
	int ycoord;
	int xtar;
	int ytar;
	MyProjectMain* Engine;


	// Unique id for object, passed to engine to identify it
	int ID;

protected:
	/** Movement position calculator - give it start and end position and times 
	and it works out current position for the current time. 
	Notice also the MyMovementPosition class. */
	MovementPosition m_oMovement;

	
};

