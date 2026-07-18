#ifndef PLAYER5837191
#define PLAYER5837191

class Player {
	int x;
	int y;
	char symbol;

public:
	int getX() const;
	int getY() const;
	char getSymbol() const;
	void setPos(int newX, int newY);
	Player(int startingX, int startingY);
};

#endif