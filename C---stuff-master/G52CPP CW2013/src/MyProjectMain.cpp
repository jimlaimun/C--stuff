#include "header.h"

// This is a basic implementation, without fancy stuff

#include "BaseEngine.h"

#include "MyProjectMain.h"

#include "JPGImage.h"

#include "TileManager.h"

#include "DisplayableObject.h"

#include "Missile.h"
#include "FiiringMissile.h"
#include "Base.h"

#include <ctime>


void MyProjectMain::SetupBackgroundBuffer()
{

	for ( int iX = 0 ; iX < GetScreenWidth() ; iX++ )
	{
		for ( int iY = 0 ; iY < this->GetScreenHeight()-50; iY++ )
			switch( rand()%100 )
		{
			case 0: SetBackgroundPixel( iX, iY, 0xFF0000 ); break;
				//case 1: SetBackgroundPixel( iX, iY, 0x00FF00 ); break;
			case 2: SetBackgroundPixel( iX, iY, 0x0000FF ); break;
				//case 3: SetBackgroundPixel( iX, iY, 0xFFFF00 ); break;
			case 4: SetBackgroundPixel( iX, iY, 0x00FFFF ); break;
				//case 5: SetBackgroundPixel( iX, iY, 0xFF00FF ); break;
		}
	}


	switch(CurState)
	{
	case stateinit:
		FillBackground( 0x000000 );
		return;
	case statemain:
		break;
	case statepause:
		FillBackground( 0x000000 );
		return;
	case stateoption:
		FillBackground( 0x000000 );
		return;
	case stateHscore:
		FillBackground( 0x000000 );
		return;
	}


}


/*
In here you need to create any movable objects that you wish to use.
Sub-classes need to implement this function.
*/
int MyProjectMain::InitialiseObjects()
{
	// Record the fact that we are about to change the array - so it doesn't get used elsewhere without reloading it
	DrawableObjectsChanged();

	// Destroy any existing objects
	DestroyOldObjects();

	//initiliase objects properties
	int max = (GetScreenWidth()-100)/100;
	BaseY = GetScreenHeight() - 50;


	// Create an array one element larger than the number of objects that you want.

	m_ppDisplayableObjects = new DisplayableObject*[20];

	// You MUST set the array entry after the last one that you create to NULL, so that the system knows when to stop.

	//11-18 = bases
	for(int i=11;i<19;i++)
	{
		m_ppDisplayableObjects[i] = new Base(this,i,3,(20+(max*((i-10)*10))),BaseY);

	}
	//0-10 = missiles
	for(int i=0;i<11;i++)
	{
		m_ppDisplayableObjects[i] = new Missile(this, 
			i/*Id*/, 1/*Type*/, 
			18/*Size*/, 
			3/*Colour*/);
	}

	//19 = friendly missiles (look at mouseDown function

	m_ppDisplayableObjects[19] = new FiiringMissile(this,0,0,0,0,0);

	// i.e. The LAST entry has to be NULL. The fact that it is NULL is used in order to work out where the end of the array is.

	m_ppDisplayableObjects[20] = NULL;



	// NOTE: We also need to destroy the objects, but the method at the 
	// top of this function will destroy all objects pointed at by the 
	// array elements so we can ignore that here.



	return 0;
}








/* Draw text labels */
void MyProjectMain::DrawStrings()
{
	switch(CurState)
	{
	case stateinit:
		CopyBackgroundPixels( 0/*X*/, 280/*Y*/, GetScreenWidth(), 40/*Height*/ );
		DrawScreenString( 100, 200, "(S)tart Game", 0xffffff, NULL );
		DrawScreenString( 100, 300, "(O)ptions", 0xffffff, NULL );
		DrawScreenString( 100, 400, "(H)ighscore", 0xffffff, NULL );
		SetNextUpdateRect( 0/*X*/, 280/*Y*/, GetScreenWidth(), 40/*Height*/ );
		break;
	case statemain:
		// Build the string to print
		sprintf(tempc,"%s",Name.c_str());

		sprintf( buf, "%s : %6d",tempc,score );
		highscore = string(buf);
		// Clear the top of the screen, since we about to draw text on it.
		CopyBackgroundPixels( 0, 0, GetScreenWidth(), 35 );
		// Then draw the strings
		DrawScreenString( 150, 10, buf, 0xffffff, NULL );
		// And mark that area of the screen as having been changed, so it gets redrawn
		SetNextUpdateRect( 0/*X*/, 0/*Y*/, GetScreenWidth(), 35/*Height*/ );
		break;
	case statepause:
		CopyBackgroundPixels( 0/*X*/, 280/*Y*/, GetScreenWidth(), 40/*Height*/ );
		DrawScreenString( 100, 200, "(P)aused. Press (P) to continue, or (E)xit to exit", 0xffffff, NULL );
		SetNextUpdateRect( 0/*X*/, 280/*Y*/, GetScreenWidth(), 40/*Height*/ );
		break;
	case stateoption:
		CopyBackgroundPixels( 0/*X*/, 280/*Y*/, GetScreenWidth(), 40/*Height*/ );
		sprintf(tempc,"Current Name is %s",Name.c_str());
		DrawScreenString( 10, 200,tempc , 0xffffff, NULL );
		DrawScreenString( 10, 250,"press (Y) to enter new name else (E) to exit" , 0xffffff, NULL );
		SetNextUpdateRect( 0/*X*/, 280/*Y*/, GetScreenWidth(), 40/*Height*/ );

		break;
	case stateHscore:

		CopyBackgroundPixels( 0/*X*/, 280/*Y*/, GetScreenWidth(), 40/*Height*/ );
		string prevHighsore = "";
		ifstream infile;
		int ycoord = 100;

		infile.open("Highscore.txt");

		while (!infile.eof())
		{

			getline(infile, prevHighsore);
			DrawScreenString( 100, ycoord, prevHighsore.c_str(), 0xffffff, NULL );
			ycoord+=50;
		}

		infile.close();
		DrawScreenString( 100, ycoord, "(E)xit", 0xffffff, NULL );
		SetNextUpdateRect( 0/*X*/, 280/*Y*/, GetScreenWidth(), 40/*Height*/ );
		break;
	}
}


/* Overridden GameAction which can be modified */
void MyProjectMain::GameAction()
{

	// If too early to act then do nothing
	if ( !TimeToAct() )
		return;

	// Don't act for another 10 ticks
	SetTimeToAct( 1 );

	switch(CurState )
	{
	case stateinit:
	case stateHscore:
	case statepause:
	case stateoption:
		break;
	case statemain:
		// Only tell objects to move when not paused etc

		UpdateAllObjects( GetTime() );
		break;
	}
}

// Override to handle a mouse press
void MyProjectMain::MouseDown( int iButton, int iX, int iY )
{
	int xstart= 0;
	int ystart = GetScreenHeight() -50;

	if(iButton == SDL_BUTTON_LEFT)
	{


		if(mode ==1)
		{
			xstart =(GetScreenWidth()-10);
			setObjecttoNULL(19);
			m_ppDisplayableObjects[19] = new FiiringMissile(this,0,xstart,ystart,iX,iY);
			mode--;

		}else if(mode==0)
		{
			xstart =10;
			setObjecttoNULL(19);
			m_ppDisplayableObjects[19] = new FiiringMissile(this,0,xstart,ystart,iX,iY);
			mode++;

		}
	}

}

/*
Handle any key presses here.
Note that the objects themselves (e.g. player) may also check whether a key is currently pressed
*/
void MyProjectMain::KeyDown(int iKeyCode)
{
	switch ( iKeyCode )
	{
	case SDLK_s:
		if(CurState == stateinit)
			score =0;
		GameInit();
		CurState = statemain;
		// Force redraw of background
		SetupBackgroundBuffer();
		// Redraw the whole screen now
		Redraw(true);
		break;

	case SDLK_p:
		switch( CurState )
		{
		case statemain:
			// Go to state paused
			CurState = statepause;
			// Force redraw of background
			SetupBackgroundBuffer();
			//// Redraw the whole screen now
			Redraw(true);

			break;

		case statepause:
			// Go to state main
			CurState = statemain;
			// Force redraw of background
			SetupBackgroundBuffer();
			// Redraw the whole screen now
			Redraw(true);

			break;
		}
		break;

	case SDLK_h:
		if(CurState == stateinit)
			CurState = stateHscore;
		// Force redraw of background
		SetupBackgroundBuffer();
		// Redraw the whole screen now
		Redraw(true);
		break;

	case SDLK_e:
		switch(CurState)
		{
		case statepause:
			CurState = stateinit;
			//m_ppDisplayableObjects[19] = new FiiringMissile(this,0,0,0,0,0);
			//DrawableObjectsChanged();
			//DestroyOldObjects();
			saveFile();
			// Force redraw of background
			SetupBackgroundBuffer();
			// Redraw the whole screen now
			Redraw(true);

			break;

		case stateHscore:
			CurState = stateinit;
			// Force redraw of background
			SetupBackgroundBuffer();
			// Redraw the whole screen now
			Redraw(true);

			break;

		case stateinit:
			SetExitWithCode(0);
			break;

		case stateoption:
			CurState = stateinit;
			// Force redraw of background
			SetupBackgroundBuffer();
			// Redraw the whole screen now
			Redraw(true);

			break;
		}
		break;

	case SDLK_o:
		if(CurState == stateinit)
			CurState = stateoption;
		// Force redraw of background
		SetupBackgroundBuffer();
		// Redraw the whole screen now
		Redraw(true);
		break;

	case SDLK_y:
		if (CurState ==stateoption);
		cout <<"Enter New Name :";
		getline(cin,Name);
		// And mark that area of the screen as having been changed, so it gets redrawn
		SetNextUpdateRect( 0/*X*/, 0/*Y*/, GetScreenWidth(), 35/*Height*/ );
		SetupBackgroundBuffer();
		Redraw(true);
		break;
	}
}


void MyProjectMain::DrawChanges()
{
	// NEW IF
	if ( CurState == stateinit || CurState == stateHscore ||CurState == stateoption )
		return; // Do not draw objects if initialising

	// Remove objects from their old positions
	UndrawChangingObjects();
	// Draw the text for the user
	DrawStrings();
	// Draw objects at their new positions
	DrawChangingObjects();
}

/* Draw the screen - copy the background buffer, then draw the text and objects. */
void MyProjectMain::DrawScreen()
{
	// First draw the background
	//this->CopyBackgroundPixels( 100, 100, 100, 100 );
	CopyAllBackgroundBuffer();
	// And finally, draw the text
	DrawStrings();

	// NEW IF
	if ( CurState == stateinit || CurState == stateHscore||CurState == stateoption)
		return; // Do not draw objects if initialising

	// Then draw the changing objects
	DrawChangingObjects();
}

double MyProjectMain::randFunc(int min, int max)
{
	int output =0;
	//srand(time(NULL));
	output = min + (rand() % (int)(max - min + 1));

	return output;

}

void MyProjectMain::saveFile()
{
	fstream filestr;

	filestr.open ("Highscore.txt", fstream::in | fstream::out | fstream::app);

	filestr<<highscore+"\n"<<endl;
	filestr.close();


}



void MyProjectMain::setObjecttoNULL(int id)
{
	m_ppDisplayableObjects[id]=NULL;
	delete m_ppDisplayableObjects[id];
}

void MyProjectMain::setstate(State newstate)
{
	CurState = newstate;

	SetupBackgroundBuffer();
	// Redraw the whole screen now
	Redraw(true);
}



bool MyProjectMain::checkWin()
{


	DisplayableObject* pobject;

	for (int i = 11; i <19; i++)      
	{         
		pobject = GetDisplayableObject(i);

		if(pobject->IsVisible())
		{
			return false;
		}
	}

	return true;


}
