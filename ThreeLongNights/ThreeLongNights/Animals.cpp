#include <cstdlib>
#include <iostream>
#include "Animals.h"

Animal::Animal(int startingX, int startingY) :
	x(startingX), y(startingY) { }

char Animal::getSymbol() const
{
	return symbol;
}

int Animal::getX() const
{
	return x;
}

int Animal::getY() const
{
	return y;
}

Bear::Bear(int startingX, int startingY) :
	Animal(startingX, startingY) 
{
	symbol = 'B';
};

void Bear::takeTurn(const std::vector<Tile>& world, const Player& player)
{
	// if not at location, determine if x or y axis are aligned
	// move one at random if both not aligned, move non-aligned one if one is aligned
	if (player.getX() != x && player.getY() != y)
	{
		int moveXOrY{ rand() % 2 + 1 };

		// x
		if (moveXOrY == 1)
		{
			if (x > player.getX())
				move(x - 1, y, world);
			else
				move(x + 1, y, world);

		}
		// y 
		else if (moveXOrY == 2)
		{
			if (y > player.getY())
				move(x, y - 1, world);
			else
				move(x, y + 1, world);
		}
	}
	else if (player.getX() != x)
	{
		if (x > player.getX())
			move(x - 1, y, world);
		else
			move(x + 1, y, world);
	}
	else if (player.getY() != y)
	{
		if (y > player.getY())
			move(x, y - 1, world);
		else
			move(x, y + 1, world);
	}
	else
		std::cout << "You get mauled by the bear\n";
}

// so move() can use it
bool canEnter(int x, int y, const std::vector<Tile>& world);

void Bear::move(int newX, int newY, const std::vector<Tile>& world)
{
	if (canEnter(newX, newY, world))
	{
		x = newX;
		y = newY;
	}
}