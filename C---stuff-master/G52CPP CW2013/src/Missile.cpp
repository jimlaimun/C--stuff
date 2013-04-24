#include "Missile.h"
#include "header.h"
#include "MyProjectMain.h"




//class BaseEngine;
Missile::Missile(MyProjectMain* pEngine, int iID, 
				 int iDrawType, int iSize, int iColour)
				 :DisplayableObject(pEngine)
				 ,Engine(pEngine)
				 // Unique id for object, passed to engine to identify it
				 , ID(iID)
				 // Size of thing to draw
				 , Size(iSize)
				 ,DrawType(iDrawType)
				 ,Colour(iColour)

{

	// The ball coordinate will be the centre of the ball
	// Because we start drawing half the size to the top-left.
	m_iStartDrawPosX = Size/2;
	m_iStartDrawPosY = Size/2;

	// Record the ball size as both height and width
	m_iDrawWidth = Size;
	m_iDrawHeight = Size;
	diff = 100;

	reset();


	// Just put it somewhere initially
	m_iPreviousScreenX = m_iCurrentScreenX = initX;
	m_iPreviousScreenY = m_iCurrentScreenY = 10;

	timepassed = Engine->GetTime();
	SetMovement(Engine->GetTime()+randStart,Engine->GetTime()+randStart + (1000*diff),Engine->GetTime()+randStart,initX,0,tarX,tarY);

	// And make it visible
	SetVisible(false);

}




void Missile::startup()
{

}


Missile::~Missile(void)
{
}


void Missile::Draw(void)
{
	// Do not draw if it should not be visible
	if ( !IsVisible() )
		return;

	unsigned int uiColourMult = 0xA59692;
	unsigned int uiColourText = 0xffffff;


	// Concentric circles for pseudo-sphere
	int iRadiusSquared = (m_iDrawWidth/2) * (m_iDrawWidth/2);
	int iCentreX = m_iCurrentScreenX + m_iStartDrawPosX + m_iDrawWidth/2;
	int iCentreY = m_iCurrentScreenY + m_iStartDrawPosY + m_iDrawHeight/2;
	for ( int iX = m_iCurrentScreenX + m_iStartDrawPosX ; iX < (m_iCurrentScreenX + m_iStartDrawPosX + m_iDrawWidth) ; iX++ )
		for ( int iY = m_iCurrentScreenY + m_iStartDrawPosY ; iY < (m_iCurrentScreenY + m_iStartDrawPosY + m_iDrawHeight) ; iY++ )
			if ( ( (iX-iCentreX)*(iX-iCentreX) + (iY-iCentreY)*(iY-iCentreY) ) <= iRadiusSquared )
			{
				// 0xB0 is the range of values, 0xff is the brightest value.
				unsigned int uiColour = (0xB0 * ((iX-iCentreX)*(iX-iCentreX) + (iY-iCentreY)*(iY-iCentreY))) / iRadiusSquared;
				uiColour = 0xff - uiColour;
				GetEngine()->SafeSetScreenPixel( iX, iY, uiColourMult * uiColour );
			}

			// Store the position at which the object was last drawn
			// You MUST do this to ensure that the screen is updated when only drawing movable objects
			// This tells the system where to 'undraw' the object from
			StoreLastScreenPositionAndUpdateRect();
}








void Missile::SetMovement(int Start, int End, int Current, int startX, int startY, int endX, int endY)
{
	m_oMovement.Setup( startX, startY, endX, endY, Start, End );
	m_oMovement.Calculate( Current );
	m_iCurrentScreenX = m_oMovement.GetX();
	m_iCurrentScreenY = m_oMovement.GetY();
}

void Missile::DoUpdate(int CurrentTime)
{

	// Work out current position
	m_oMovement.Calculate(CurrentTime);
	if(m_iCurrentScreenY>10)
	{
		SetVisible(true);
	}
	m_iCurrentScreenX = m_oMovement.GetX();
	m_iCurrentScreenY = m_oMovement.GetY();

	//progressive difficulty
	int timedone = 0;
	timedone = (CurrentTime-timepassed);
	if(timedone<10000 && timedone >5000)
		diff = 90;
	if(timedone<15000 && timedone >10000)
		diff = 80;
	if(timedone<25000 && timedone >20000)
		diff = 70;
	if(timedone<30000 && timedone >27000)
		diff = 60;
	if(timedone<35000 && timedone >33000)
		diff = 50;
	if(timedone<45000 && timedone >40000)
		diff = 40;
	if(timedone<52000 && timedone >48000)
		diff = 30;
	if(timedone<55000 && timedone >53000)
		diff = 20;
	if(timedone<60000 && timedone >58000)
	{
		diff = 10;
	}else if(timedone >60000)
		diff = 9;

	int sec = 60000;
	if(timedone >(10*sec))
		diff = 5;
	printf("%d\n",timedone);





	//collision between missiles

	DisplayableObject* pObject;

	// If you need to cast to the sub-class type, you must use dynamic_cast, see lecture 19
	// We are just using base class parts
	for ( int iObjectId =  19; 
		(pObject = Engine->GetDisplayableObject( iObjectId )
		) != NULL ;
	iObjectId++ )
	{
		if ( pObject == this ) // This is us, skip it
			continue;
		int iXDiff = pObject->GetCurrentScreenX()+10 - m_iCurrentScreenX;
		int iYDiff = pObject->GetCurrentScreenY()- m_iCurrentScreenY;

		// Estimate the size - by re-calculating it
		int iTick = CurrentTime/20; // 1 per 20ms
		int iFrame = iTick % 30;
		int iSize = 10 + iFrame;
		if ( iFrame > 15 )
			iSize = 10 + (30-iFrame);
		int iSizeOther = iSize+5; // Assume both the same size

		// Pythagorus' theorum:
		if ( ((iXDiff*iXDiff)+(iYDiff*iYDiff)) 
			< ((iSizeOther+iSize)*(iSizeOther+iSize)) )
		{

			pObject->SetVisible(false);
			pObject=NULL;
			Engine->setScore(100);
			this->RedrawWholeScreen();

			reset();



			SetMovement(Engine->GetTime()+randStart,Engine->GetTime()+randStart +(100*diff),Engine->GetTime()+randStart,initX,0,tarX,tarY);
			SetVisible(false);

			// Ensure that the object gets redrawn on the display, if something changed
			RedrawObjects();
			return;
		}
	}


	pObject = NULL;
	delete pObject;
	//end

	// If movement has finished then request instructions
	if ( m_oMovement.HasMovementFinished( CurrentTime ) )
	{	




		//base detection

		for ( int iObjectId =  11;iObjectId<19;iObjectId++ )
		{
			SetVisible(false);
			pObject = Engine->GetDisplayableObject(iObjectId);


			if(Engine->checkWin())
			{
				Engine->setstate(Engine->stateinit);
			}

			int Xcoord = pObject->GetXCentre();
			int Ycoord = pObject->GetYCentre();
			if ((Xcoord-10)<m_iCurrentScreenX && m_iCurrentScreenX<(Xcoord+40)&& m_iCurrentScreenY<Ycoord+5 )
			{

				if(pObject->IsVisible())
				{
					pObject->SetVisible(false);
				}




				this->RedrawWholeScreen();



				reset();
				m_oMovement.Setup(initX,0,tarX,tarY,Engine->GetTime()+randStart,Engine->GetTime()+randStart+ (100*diff));

				m_oMovement.Calculate(CurrentTime);
				m_iCurrentScreenX = m_oMovement.GetX();
				m_iCurrentScreenY = m_oMovement.GetY();
				RedrawObjects();
				return;
				pObject = NULL;
				delete pObject;
			}
		}





		reset();
		m_oMovement.Setup(initX,0,tarX,tarY,Engine->GetTime(),Engine ->GetTime()+randStart + (100*diff));

		// Ask the mover where the object should be
		m_oMovement.Calculate( CurrentTime );
		m_iCurrentScreenX =m_oMovement.GetX();
		m_iCurrentScreenY = m_oMovement.GetY();
		// Ensure that the object gets redrawn on the display, if something changed
	}


	// Ensure that the object gets redrawn on the display, if something changed

	RedrawObjects();
}

void Missile::reset()
{

	bool done = false;


	for(int i =0;i<9;i++)
	{
		result = Engine->randFunc(11,18);
		if(Engine->GetDisplayableObject(result)->IsVisible() ==false)
		{
			result = Engine->randFunc(11,18);
		}else{
			break;
		}
	}

	tarX = Engine->GetDisplayableObject(result)->GetXCentre();/*-( m_iStartDrawPosX + m_iDrawHeight/2);*/
	tarY = Engine->GetDisplayableObject(result)->GetYCentre();/*-( m_iStartDrawPosY + m_iDrawHeight/2);*/
	initX = Engine->randFunc(10,Engine->GetScreenWidth()-100);
	randStart = Engine ->randFunc(1000,6000);

}

