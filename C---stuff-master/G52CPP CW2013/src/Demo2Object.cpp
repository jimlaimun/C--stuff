#include "header.h"
#include "Demo2Object.h"
#include "Demo2Main.h"

Demo2Object::Demo2Object(Demo2Main* pEngine)
: DisplayableObject(pEngine)
, m_pMainEngine( pEngine )
{
	// The ball coordinate will be the centre of the ball
	// Because we start drawing half the size to the top-left.
	m_iStartDrawPosX = -50;
	m_iStartDrawPosY = -50;

	// Record the ball size as both height and width
	m_iDrawWidth = 100;
	m_iDrawHeight = 100;
	
	// Just put it somewhere initially
	m_iPreviousScreenX = m_iCurrentScreenX = 10;
	m_iPreviousScreenY = m_iCurrentScreenY = 10;

	// And make it visible
	SetVisible(true);
}

Demo2Object::~Demo2Object(void)
{
}

void Demo2Object::Draw()
{
	// Do not draw if it should not be visible
	if ( !IsVisible() )
		return;

	m_pMainEngine->DrawScreenOval(
			m_iCurrentScreenX - 10,
			m_iCurrentScreenY - 10,
			m_iCurrentScreenX +5,
			m_iCurrentScreenY + 5,
			rand() % 0xffffff );

	// Store the position at which the object was last drawn
	// You MUST do this to ensure that the screen is updated when only drawing movable objects
	// This tells the system where to 'undraw' the object from
	StoreLastScreenPositionAndUpdateRect();
}


void Demo2Object::DoUpdate( int iCurrentTime )
{

	int testX = 565;
	int testY = 580;
	int time =0;

	m_iPreviousScreenX = m_iCurrentScreenX;
	m_iPreviousScreenY = m_iCurrentScreenY;

	int targetx =0;
	int targety = 0;

	targetx =  testX-m_iPreviousScreenX ;
	targety =  testY-m_iPreviousScreenY;

	if(m_iCurrentScreenX >GetEngine()->GetScreenWidth()-10 )
	m_iCurrentScreenX = m_iPreviousScreenX - 5;
	m_iCurrentScreenY = m_iPreviousScreenY - 5;
	if(m_iCurrentScreenX < 300 && m_iCurrentScreenY >=550)
	m_iCurrentScreenX = m_iPreviousScreenX + 5;
	m_iCurrentScreenY = m_iPreviousScreenY + 5;

	
	//m_iCurrentScreenX = m_iCurrentScreenX; + targetx * 100*time;
	//m_iCurrentScreenY = m_iCurrentScreenY; + targety * 100*time;


	//m_iCurrentScreenX = m_iPreviousScreenX + (rand()%121 - 60)/30;
	//m_iCurrentScreenY = m_iPreviousScreenY + (rand()%121 - 60)/30;

	// Ensure not off the screen
	if ( m_iCurrentScreenX < 50 )
		m_iCurrentScreenX = 100;
	if ( m_iCurrentScreenX >= 750 )
		m_iCurrentScreenX = 400;
	if ( m_iCurrentScreenY >= 550 )
		m_iCurrentScreenY = 10;
	/*if ( m_iCurrentScreenY < 50 )
		m_iCurrentScreenY = 10;*/

	// Ensure that the object gets redrawn on the display, if something changed
	time +=1;
	RedrawObjects();
}