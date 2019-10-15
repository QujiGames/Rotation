#include "Random/Random.h"
#include "Console/Console.h"
#include <Windows.h>
#include <stdio.h>
#include <math.h>



#define PI 3.14159265

static float angle = 0;
static int bGameIsRunning = 1;
static char aScreen[40][40];
static char aLevel[40][40];
static int intSleep = 100;
static int xTrans = 1;
static int yTrans = 1;
static float xMod = 0;
static float yMod = 0;


void GameInit()
{
	//Game Initialization
	Console_Init();
	Random_Init();

	//Set a title on my window

	Console_SetTitle("Rotate Test");

	// Setup a square font and the window size and remove cursor visibility
	Console_SetSquareFont();
	Console_SetWindowedMode(40, 40, false);
	Console_SetCursorVisibility(0);
	Console_CreateRenderBuffer();

}

void GameShutdown()
{
	Console_CleanUp();


}


void ReadInput()
{
	float anglerad = ((angle / 180) * PI);
	// move the player
	if (GetAsyncKeyState(VK_RIGHT))
	{
		
		angle = angle + 10;
	}


	if (GetAsyncKeyState(VK_LEFT))
	{
		
		angle = angle - 10;
	}
	//A
	if (GetAsyncKeyState(0x41))
	{
		yMod = yMod - (1 * sin(anglerad));
		xMod = xMod + (1 * cos(anglerad));
		xTrans = xMod;
		yTrans = yMod;
	}
	//W
	if (GetAsyncKeyState(0x57))
	{
		
		yMod = yMod + (1 * cos(anglerad));
		xMod = xMod + (1 * sin(anglerad));
		xTrans = xMod;
		yTrans = yMod;

	}
	//S
	if (GetAsyncKeyState(0x53))
	{

		yMod = yMod - (1 * cos(anglerad));
		xMod = xMod - (1 * sin(anglerad));
		xTrans = xMod;
		yTrans = yMod;
	}
	//D
	if (GetAsyncKeyState(0x44))
	{

		yMod = yMod + (1 * sin(anglerad));
		xMod = xMod - (1 * cos(anglerad));
		xTrans = xMod;
		yTrans = yMod;
	}
	

}

void ClearScreen()
{
	int i, j;

	for (i = 0; i < 40; ++i)
	{
		for (j = 0; j < 40; ++j)
		{
			aScreen[i][j] = '\0';
		}
	}
}


void DrawLevel2()
{
	
	ClearScreen();
	
	
	//float anglerad = ((angle / 180) * 3.14);
	
	//int a = (5 * cos(anglerad)) - (5 * sin(anglerad)) + 20;
	//int b = (5 * sin(anglerad)) + (5 * cos(anglerad)) + 20;

	//aScreen[a][b] = '#';

	int i, j;

	for (i = 0; i < 40; ++i)
	{
		for (j = 0; j < 40; ++j)
		{
			aScreen[i][j] = aLevel[i][j];
		}
	}


	//int i, j;
	//float anglerad = ((angle / 180) * 3.14);



}



void DrawLevel()
{

	ClearScreen();


	int i, j, a, b;
	
	float anglerad = ((angle / 180) * 3.14);


	for (i = 0; i < 40; ++i)
	{
		for (j = 0; j < 40; ++j)
		{
			if (aLevel[i][j] == '#')
			{
				
				
				a = ((i +xTrans- 20)* cos(anglerad)) - ((j + yTrans- 20)* sin(anglerad)) + 20  ;
				b = ((i +xTrans- 20 )* sin(anglerad)) + ((j +yTrans -20) * cos(anglerad)) + 20 ;

				if (a>0 && b>0 && a<40 && b<40)
				{
				
				aScreen[a][b] = '#';
				}	
			}

		}
	}
	aScreen[20][20] = "^";
	
	

}

void FirstDraw()
{
	int i, j;

	for (i = 0; i < 40; ++i)
	{
		for (j = 0; j < 40; ++j)
		{
			aLevel[i][j] = '\0';
		}
	}
	

	for (i = 10; i < 29; ++i)
	{
		
		
		aLevel[i][10] = '#';
		aLevel[i][29] = '#';
	}

	for (i = 10; i < 30; ++i)
	{
		

		aLevel[10][i] = '#';
		aLevel[29][i] = '#';
	}
}






void RenderScene()
{
	
		Console_ClearRenderBuffer();

		

	
	


		

		// Collision_Detection();

		// Redraw the array
		// Populate_Screen();

		// copy the array to the buffer
		int i;
		int j;

		for (i = 0; i < 40; ++i)
		{
			for (j = 0; j < 40; ++j)
			{
				Console_SetRenderBuffer_Char(i, j, aScreen[i][j]);
			}
		}
	


		Console_SwapRenderBuffer();
	
}

void GameLoop()
{

	ReadInput();
	DrawLevel();
	RenderScene();


}



int main()
{

	GameInit();
	FirstDraw();



	//Game Loop
	while (bGameIsRunning)
	{





		GameLoop();



		Sleep(intSleep);
	}

	GameShutdown();



}