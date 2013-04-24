#ifndef MYPROJECTMAIN_H
#define MYPROJECTMAIN_H

#include "BaseEngine.h"
#include <iostream>
#include <fstream>
#include <string>

using namespace std;


class FiiringMissile;
class Base;

class MyProjectMain : public BaseEngine
{
public:

	/**
	Constructor
	*/
	MyProjectMain()
		: BaseEngine( 6 )
		,CurState(stateinit) // NEW
	{mode=0;
	score =0;
	Name = "Player 1";
	strcpy(tempc,Name.c_str());
	}
	// Do any setup of back buffer prior to locking the screen buffer
	// Basically do the drawing of the background in here and it'll be copied to the screen for you as needed
	virtual void SetupBackgroundBuffer();

	// Create any moving objects
	int InitialiseObjects();

	/** Draw any strings */
	void DrawStrings();

	/**
	The game logic - move things and change the state if necessary.
	Must call Redraw(true/false) if anything changes that shows on the screen.
	*/
	virtual void GameAction();

	// Handle pressing of a mouse button
	void MouseDown( int iButton, int iX, int iY );

	// Handle pressing of a key
	virtual void KeyDown(int iKeyCode);

	//public variables
	ofstream highscorefile;
	char buf[128];
	char tempc[256];
	string highscore;
	string temp;

	//save highscore to file	
	void saveFile();
	//random function
	double randFunc(int min, int max);

	
	
	//set object to null
	void setObjecttoNULL(int id);
	bool checkWin();
	


	//game states
	enum State { stateinit,statemain,statepause,stateHscore,stateoption };
	void DrawScreen();
	void DrawChanges();

	//score changing
	void setScore(int Nscore)
	{score = score +Nscore;
	}
	void setstate(State newstate);

private:
	State CurState;
	int BaseY;
	int mode;
	int score;
	string Name;
	unsigned long time();

protected:
	FiiringMissile* missile;
	Base** Bases;
};

#endif
