// Game.h : Maintain the game elements of the program
//

#ifndef	GAME_H
#define	GAME_H

#define MAX_HEIGHT	25
#define MAX_WIDTH	80

#define ESC			27
#define SPACE		32
#define ENTER		13

#define W			119
#define S			115
#define A			97
#define D			100

#define UP			72
#define DOWN		80
#define LEFT		75
#define	RIGHT		77

/* Maintain the system of the game */
class	gamesys
{
};

/* The ship controlled by the user */
class	usrship
{
private:
	int xpos, ypos;
	int life;

public:
	usrship( );

	void getPosition(int *xPos, int *yPos);
	int  getLife( );
	void setMovement(int xMov, int yMov);

	void killShip( );
};

/* The enemy ships */
class	enyship
{
private:
	int xpos, ypos;
	int life;
	int speed;
	int cnttrpt;

	//int heading;

public:
	bool isActive;

	enyship( );
	enyship(int yPos, int spd);

	void loadParam(int yPos, int spd, int maxLife);

	void getPosition(int *xPos, int *yPos);
	int  getLife( );
	void updtPos( );

	void killLife( );
	void killShip( );
};

/* Laser shot by the user ship */
class	lasers
{
private:
	int xpos, ypos;

public:
	bool isActive;

	lasers( );
	lasers(int xPos, int yPos);

	void getPosition(int *xPos, int *yPos);
	void updtPos( );
};

bool cmpUsrship_Enyship(usrship , enyship);
bool cmpLasers_Enyship(lasers, enyship);
int  cmpWall_Enyship(enyship);

#endif//GAME_H