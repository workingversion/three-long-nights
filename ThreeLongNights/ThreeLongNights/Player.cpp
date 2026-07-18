#include "Player.h"

Player::Player(int startingX, int startingY) :
	x(startingX), y(startingY), symbol('@')
{ };

int Player::getX() const
{
	return x;
}

int Player::getY() const
{
	return y;
}

char Player::getSymbol() const
{
	return symbol;
}

void Player::setPos(int newX, int newY)
{
	x = newX;
	y = newY;
}