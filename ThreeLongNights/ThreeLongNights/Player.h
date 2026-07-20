#ifndef PLAYER5837191
#define PLAYER5837191

#include "Tile.h"
class Player {
	int x;
	int y;
	char symbol;

public:
	int getX() const;
	int getY() const;
	char getSymbol() const;
	void setPos(int newX, int newY);
	void interactTile(Tile& tile, int tick);
	Player(int startingX, int startingY);
};

#endif