#include "Player.h"
#include <iostream>

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

void Player::interactTile(Tile& tile, int tick)
{
	//TODO: check if there's an entity at the tile BEFORE checking the tile type, entity interaction comes first


	// only check if the tile should replenish resources by now when the player is checking it
	if (!tile.getHasResource() && tick >= tile.getLastTickThatHadResource() + 50)
	{
		tile.respawnResource();
	}

	if (tile.getTileType() == Tile::Water)
	{
		if (tile.getHasResource())
		{
			std::cout << "You caught a fish!\n";
			tile.takeResource(tick);
		}
		else
		{
			std::cout << "There is no fish to catch.\n";
		}
	}
	else if (tile.getTileType() == Tile::Bush)
	{
		if (tile.getHasResource())
		{
			std::cout << "You take some berries from the bush.\n";
			tile.takeResource(tick);
		}
		else
		{
			std::cout << "The bush is bare.\n";
		}
	}
	else
	{
		std::cout << "You feel the grass. The grass almost seems like it's feeling back.\n";
	}
}