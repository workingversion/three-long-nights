#ifndef ANIMALS08475718
#define ANIMALS08475718
#include "Tile.h"
#include "Player.h"
#include <vector>

class Animal
{
protected:
	char symbol;
	int x;
	int y;

public:
	char getSymbol() const;
	int getX() const;
	int getY() const;
	virtual void takeTurn(const std::vector<Tile>& world, Player& player) = 0;
	bool move(int x, int y, const std::vector<Tile>& world);
	Animal(int startingX, int startingY, char ascii);
};


class Bear : public Animal
{
public:
	void takeTurn(const std::vector<Tile>& world, Player& player) override;
	Bear(int startingX, int startingY);
};

#endif