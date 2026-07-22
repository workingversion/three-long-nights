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
	virtual void takeTurn(const std::vector<Tile>& world, const Player& player) = 0;
	virtual void move(int x, int y, const std::vector<Tile>& world) = 0;
	Animal(int startingX, int startingY);
};


class Bear : public Animal
{
public:
	void takeTurn(const std::vector<Tile>& world, const Player& player) override;
	void move(int x, int y, const std::vector<Tile>& world) override;
	Bear(int startingX, int startingY);
};

#endif