// Game.cpp : Maintain the game elements of the program
//

#include "Game.h"

/*	usrship : implement functions	*/
usrship::usrship( )
{
	xpos = 2;
	ypos = 12;
	life = 3;
}

void usrship::getPosition(int *xPos, int *yPos)
{
	*xPos = xpos;
	*yPos = ypos;
}

int  usrship::getLife( )
{
	return life;
}

void usrship::setMovement(int xMov, int yMov)
{
	xpos = xpos + xMov;
	ypos = ypos + yMov;

	if(xpos == 0)
		xpos = 1;
	if(xpos == MAX_WIDTH)
		xpos = MAX_WIDTH - 1;

	if(ypos == 0)
		ypos = 1;
	if(ypos == MAX_HEIGHT )
		ypos = MAX_HEIGHT - 1;

}

void usrship::killShip()
{
	life --;

	xpos = 2;
	ypos = 12;
}

/*	enyship : implement functions	*/
enyship::enyship( )
{
	xpos = 25;
	ypos = 12;
	life = 3;
	speed = 5;
	cnttrpt = 0;
	isActive = false;
}

enyship::enyship(int yPos, int spd)
{
	xpos = 25;
	ypos = yPos;
	life = 3;
	speed = spd;
}

void enyship::loadParam(int yPos, int spd, int maxLife)
{	
	xpos = MAX_WIDTH - 1;
	ypos = yPos;
	life = maxLife;
	speed = spd;
	isActive = true;
}

void enyship::getPosition(int *xPos, int *yPos)
{
	*xPos = xpos;
	*yPos = ypos;
}

int  enyship::getLife( )
{
	return life;
}

void enyship::updtPos( )
{
	cnttrpt ++;

	if(cnttrpt == speed)
	{
		cnttrpt = 0;
		xpos --;
	}
}

void enyship::killLife()
{
	life --;

	if(life == 0)
		isActive = false;
}

void enyship::killShip()
{
	isActive = false;
}

/*	lasers : implement functions	*/
lasers::lasers( )
{
}

lasers::lasers(int xPos, int yPos)
{
	xpos = xPos;
	ypos = yPos;
}

void lasers::getPosition(int *xPos, int *yPos)
{
	*xPos = xpos;
	*yPos = ypos;
}

void lasers::updtPos( )
{
	xpos ++;
}

bool cmpUsrship_Enyship(usrship user, enyship enemy)
{
	int xuser, yuser, xenemy, yenemy;

	user.getPosition(&xuser, &yuser);
	enemy.getPosition(&xenemy, &yenemy);

	if(yuser == yenemy)
	{
		if(xuser == xenemy)
			return 1;
	}
	return 0;
}

bool cmpLasers_Enyship(lasers laser, enyship enemy)
{
	int xlas, ylas, xenemy, yenemy;

	laser.getPosition(&xlas, &ylas);
	enemy.getPosition(&xenemy, &yenemy);

	if(ylas == yenemy)
	{
		if(xlas == xenemy)
			return 1;
	}
	return 0;
}

int  cmpWall_Enyship(enyship enemy)
{
	int xenemy, yenemy;

	enemy.getPosition(&xenemy, &yenemy);

	if(xenemy == 0)
		return yenemy;

	return -1;
}

