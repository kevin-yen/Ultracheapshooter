// Main.cpp : Defines the entry point for the console application.
//

#include <windows.h>
#include <stdlib.h>
#include <stdio.h>
#include <conio.h>
#include <time.h>

#include "Game.h"

void clearScreen( );
void clearBuffer(char *);
void loadBuffer(char *);
void setPixel(char *, int, int, char);

void wait(int milliseconds);

int main(int argc, char* argv[])
{
	/* Game and screen system variable */
	char scrBuffer[MAX_HEIGHT*MAX_WIDTH];
	bool isQuit = false;
	char kbInput;
	int  horzDsplc = 0;
	int  vertDsplc = 0;

	/* Game element variable */
	usrship user;
	enyship enemies[10];
	lasers  Lasers[20];

	int  curEnemies;
	int  cntEnemies;
	int  cntLasers;
	int  xPos, yPos;
	int  life;

	/* All purpose variable */
	int  iIndex;
	int  jIndex;
	int  result;
	bool bresult;

	clearBuffer(&scrBuffer[0]);

	for(iIndex = 1; iIndex < 24; iIndex ++)
		scrBuffer[iIndex * MAX_WIDTH] = 1;

	loadBuffer(&scrBuffer[0]);

	wait(4);

	/* Initial Routines */
//	clearScreen( );
	printf("Hello, this is Ultracheapshooter \n press any key to play");

	while(!kbhit( )){}
	getch( );

	clearBuffer(&scrBuffer[0]);

	curEnemies = 3;
	cntEnemies = 3;

	for(iIndex = 0; iIndex < curEnemies; iIndex ++)
		enemies[iIndex].loadParam(rand( ) % 23 + 1, 3, 3);

	while(!isQuit)
	{
		/* The user press a key */
		if(kbhit( ))
		{
			/*	Keyboard Input Routines		*/

			kbInput = getch( );

			switch(kbInput)
			{
			/* Get movement of ship from directional pad */
			case W:
				vertDsplc --;
				break;

			case S:
				vertDsplc ++;
				break;

			case D:
				horzDsplc ++;
				break;

			case A:
				horzDsplc --;
				break;				

			/* Quit */
			case ESC:
				isQuit = true;
				break;

			/* Shoot */
			case SPACE:
				/* Create new laser object */
				break;

			default:
				break;
			}
		}

		/*	Object State Update Routines	*/
		for(iIndex = 0; iIndex < 10; iIndex ++)
		{
			if(enemies[iIndex].isActive)
				enemies[iIndex].updtPos( );
		
		}

		user.setMovement(horzDsplc, vertDsplc);

		/*	Object Draw to Buffer Routine	*/
		if(curEnemies > cntEnemies)
		{
			for(iIndex = 0; (iIndex < 10) && (!enemies[iIndex].isActive); iIndex ++){ }

			enemies[iIndex].loadParam(rand( ) % 23 + 1, 3, 1);

			curEnemies ++;
		}

		for(iIndex = 0; iIndex < 10; iIndex ++)
		{
			if(enemies[iIndex].isActive)
			{
				enemies[iIndex].getPosition(&xPos, &yPos);
				result = cmpWall_Enyship(enemies[iIndex]);
				if(result != -1)
				{
					enemies[iIndex].killShip( );
					cntEnemies --;
				}
				else
				{
					life = enemies[iIndex].getLife( );
					setPixel(&scrBuffer[0], xPos, yPos, (char) life + 48);
				}
				
				bresult = cmpUsrship_Enyship(user, enemies[iIndex]);
				if(bresult)
				{
					user.killShip( );
					enemies[iIndex].killShip( );
				}
			}
		}
		
		user.getPosition(&xPos, &yPos);
		setPixel(&scrBuffer[0], xPos, yPos, '>');

		setPixel(&scrBuffer[0], 1, 1, (char) cntEnemies + 48);
		setPixel(&scrBuffer[0], 1, 2, (char) curEnemies + 48);

		/*	Load Buffer to Screen and Wait	*/
		loadBuffer(&scrBuffer[0]);
		wait(750);
		clearBuffer(&scrBuffer[0]);
		clearScreen( );

		vertDsplc = 0;
		horzDsplc = 0;
	}

	system("cls");

	printf("Game Over\n");

	return 0;
}

void clearScreen( )
{
	DWORD n;
	DWORD size;
	COORD coord = {0};
	CONSOLE_SCREEN_BUFFER_INFO csbi;

	HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);

	GetConsoleScreenBufferInfo(h, &csbi);

	size = csbi.dwSize.X * csbi.dwSize.Y;

	FillConsoleOutputCharacter( h, TEXT (' '), size, coord, &n);
	GetConsoleScreenBufferInfo( h, &csbi);
	FillConsoleOutputAttribute( h, csbi.wAttributes, size, coord, &n);

	SetConsoleCursorPosition( h, coord);
}

void clearBuffer(char *scrBuf)
{
	int iIndex, jIndex;

	for(iIndex = 0; iIndex < MAX_HEIGHT; iIndex ++)
	{
		for(jIndex = 0; jIndex < MAX_WIDTH; jIndex ++)
			*(scrBuf + (iIndex * MAX_WIDTH) + jIndex) = 32;
	}
}

void loadBuffer(char *scrBuf)
{
	int iIndex, jIndex;
	char curChar;
	char dsNxtLn = false;

	for(iIndex = 0; iIndex < MAX_HEIGHT; iIndex ++)
	{
		for(jIndex = 0; jIndex < MAX_WIDTH; jIndex ++)
		{
			curChar = *(scrBuf + (iIndex * MAX_WIDTH) + jIndex);
			if(curChar != 32)
				dsNxtLn = true;
		}
		if(dsNxtLn == true)
		{
			for(jIndex = 0; jIndex < MAX_WIDTH; jIndex ++)
				printf("%c", *(scrBuf + (iIndex * MAX_WIDTH) + jIndex ));
		}
		else
			printf("\n");
	}
}

void setPixel(char *scrBuf, int xPos, int yPos, char value)
{
	*(scrBuf + (yPos * MAX_WIDTH) + xPos) = value;
}

void wait(int milliseconds)
{
	clock_t endwait;
	endwait = clock() + milliseconds * CLOCKS_PER_SEC / 1000;
	while(clock() < endwait) { };
}