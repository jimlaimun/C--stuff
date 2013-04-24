#include "Base.h"


Base::Base(MyProjectMain* mEngine,int id,int size,int xcoord, int ycoord)
	:DisplayableObject(mEngine)
	,BEngine(mEngine)
{
	xCoord = xcoord;
	yCoord = ycoord;
	ID = id;
	Size = size;
	
	

	// The ball coordinate will be the centre of the ball
	// Because we start drawing half the size to the top-left.
	m_iStartDrawPosX = xCoord;
	m_iStartDrawPosY = yCoord;

	// Record the ball size as both height and width
	m_iDrawWidth = 100;
	m_iDrawHeight = 100;
	
	// Just put it somewhere initially
	m_iPreviousScreenX = m_iCurrentScreenX = xCoord;
	m_iPreviousScreenY = m_iCurrentScreenY = yCoord;

	SetVisible(true);
	
}


Base::~Base(void)
{
}



int Base::getId()
{
	return ID;
}

int Base::getX()
{
	return xCoord;
}

int Base::getY()
{
	return yCoord;
}



void Base::Draw(void)
{

	if ( !IsVisible() )
		return;

	
	BEngine->DrawRectangle( m_iCurrentScreenX-10, m_iCurrentScreenY-10, m_iCurrentScreenX+40, m_iCurrentScreenY+5, 0x00ffff ); 
	
	StoreLastScreenPositionAndUpdateRect();
}

void Base::DoUpdate(int iCurrentTime) 
{ 
	
	//m_iPreviousScreenX = m_iCurrentScreenX;
	//m_iPreviousScreenY = m_iCurrentScreenY;
	//	// Ensure that the object gets redrawn on the display, if something changed
	RedrawObjects(); 
}



