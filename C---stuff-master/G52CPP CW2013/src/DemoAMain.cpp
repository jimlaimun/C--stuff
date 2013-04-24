#include "DemoAMain.h"
#include "header.h"
#include "templates.h"

DemoAMain::DemoAMain(void)
	: BaseEngine(6)
{
}


DemoAMain::~DemoAMain(void)
{
}


void DemoAMain::SetupBackgroundBuffer(void)
{
	FillBackground(0x000000);
	for(int iX =0; iX<GetScreenWidth();iX++){
		for(int iY =0; iY<GetScreenHeight()-100;iY++){
			switch (rand()%100){
				case 0: SetBackgroundPixel( iX, iY, 0xFF0000 ); break; 
				case 1: SetBackgroundPixel( iX, iY, 0x00FF00 ); break; 
				case 2: SetBackgroundPixel( iX, iY, 0x0000FF ); break; 
				case 3: SetBackgroundPixel( iX, iY, 0xFFFF00 ); break; 
				case 4: SetBackgroundPixel( iX, iY, 0x00FFFF ); break; 
				case 5: SetBackgroundPixel( iX, iY, 0xFF00FF ); break; 
				}
		}
	}
}

void DemoAMain::MouseDown(int iButton, int iX, int iY)
{
	printf( "%d %d\n", iX, iY ); 
	if ( iButton == SDL_BUTTON_LEFT ) 
	{	
		DrawRectangle( iX-10, iY-10, iX+10, iY+10, 0xffff00 ); 
		SetSDLUpdateRectImmediately( iX-10, iY-10, 21, 21 ); 
	} 
	else if ( iButton == SDL_BUTTON_RIGHT ) 
	{ 
		DrawOval( iX-10, iY-10, iX+10, iY+10, 0xff0000 ); 
		//SetSDLUpdateRectImmediately( iX-10, iY-10, 21, 21 ); 
		Redraw(true);
	} 
}
