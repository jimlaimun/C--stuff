#include "FiiringMissile.h"


FiiringMissile::FiiringMissile(MyProjectMain* pEngine, int iID,int xstart,int ystart,int xend,int yend)
	:DisplayableObject(pEngine)
	,ID(iID)
	, Engine(pEngine)
{
	// The ball coordinate will be the centre of the ball
	// Because we start drawing half the size to the top-left.
	int Size = 18;
	m_iStartDrawPosX = Size/2;
	m_iStartDrawPosY = Size/2;

	// Record the ball size as both height and width
	m_iDrawWidth = Size;
	m_iDrawHeight = Size;


	xcoord = xstart;
	ycoord = ystart;
	xtar = xend;
	ytar = yend;

	//movement initialization
	SetMovement(Engine->GetTime(),Engine->GetTime()+300,Engine->GetTime(),xcoord,ycoord,xtar,ytar);


	// Just put it somewhere initially
	m_iPreviousScreenX = m_iCurrentScreenX = xcoord;
	m_iPreviousScreenY = m_iCurrentScreenY = ycoord;

	// And make it visible
	SetVisible(true);

}


FiiringMissile::~FiiringMissile(void)
{

}


void FiiringMissile::Draw(void)
{
	// Do not draw if it should not be visible
	if ( !IsVisible() )
		return;

	unsigned int uiColourMult = 0x010001;

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








void FiiringMissile::SetMovement(int Start, int End, int Current, int startX, int startY, int endX, int endY)
{
	m_oMovement.Setup( startX, startY, endX, endY, Start, End );
	m_oMovement.Calculate( Current );
	m_iCurrentScreenX = m_oMovement.GetX();
	m_iCurrentScreenY = m_oMovement.GetY();
}

void FiiringMissile::DoUpdate(int CurrentTime)
{
	// Work out current position
	m_oMovement.Calculate(CurrentTime);
	if(m_iCurrentScreenY>10)
	{
		SetVisible(true);
	}
	m_iCurrentScreenX = m_oMovement.GetX();
	m_iCurrentScreenY = m_oMovement.GetY();

	
	// If movement has finished then request instructions
	if ( m_oMovement.HasMovementFinished( CurrentTime ) )
	{	
		int i =19;
		SetVisible(false);
		this->RedrawWholeScreen();
		Engine->setObjecttoNULL(i);
		

	}else if (Engine->GetMouseXClickedDown() != xtar || Engine->GetMouseYClickedDown() !=ytar)
	{
		//int i =19;
		SetVisible(false);
		//this->RedrawWholeScreen();
		//Engine->setObjecttoNULL(i);

		xtar = Engine->GetMouseXClickedDown();
		ytar= Engine->GetMouseYClickedDown();
		//new FiiringMissile(Engine,GetID(),xcoord,ycoord,xtar,ytar);
		m_oMovement.Setup(xcoord,ycoord,xtar,ytar,CurrentTime,CurrentTime+300);

	}


	// Ensure that the object gets redrawn on the display, if something changedo
	RedrawObjects();
}



int FiiringMissile::GetID()
{
	return ID;
}



