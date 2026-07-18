#include <iostream>
#include <vector>
#include <limits>
#include <cstdlib>
#include <ctime>
#include "Tile.h"
#include "Player.h"


// establish width and height of the grid
const int WIDTH{ 10 };
const int HEIGHT{ 5 };

// char input validation
char getValidatedMovementOption(const std::vector<char>& chars)
{
	char input{};

	while (true)
	{
		std::cout << "Type w/a/s/d to move up, left, down or right respectively: ";
		std::cin >> input;

		if (std::cin.fail())
		{
			std::cin.clear();
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			std::cout << "Invalid input.\n";
			continue;
		}

		bool found{ false };

		for (char ch : chars)
		{
			if (input == ch)
			{
				found = true; 
				break;
			}	
		}

		if (!found)
		{
			std::cout << "Invalid character. Please choose from the ones selected.\n";
			continue;
		}

		return input;
	}
}

// translation between x, y coords and grid index
int cellIndex(int xCoord, int yCoord)
{
	return yCoord * WIDTH + xCoord;
}

// main world generation
std::vector<Tile> createWorld()
{
	std::vector<Tile> world{};

	for (int i{ 0 }; i < WIDTH * HEIGHT; i++)
	{
		int rng = rand() % 100 + 1;

		if (rng <= 10)
			world.push_back(Tile{ Tile::Water});
		else if (rng <= 85)
			world.push_back(Tile{ Tile::Grass});
		else
			world.push_back(Tile{ Tile::Bush});
	}

	return world;
}

// prints the grid as passed to it with divisions between layers and labels the tick
void printWorld(const std::vector<Tile>& world, int tick, Player& player)
{
	std::cout << "Tick " << tick << '\n';
	// nested for loop to print rows (which come first, y) and columns (second, x)
	for (int y{ 0 }; y < HEIGHT; y++)
	{
		for (int x{ 0 }; x < WIDTH; x++)
		{
			if (x == player.getX() && y == player.getY())
				std::cout << ' ' << player.getSymbol() << ' ';
			else
				std::cout << ' ' << world[cellIndex(x, y)].getSymbol() << ' ';
		}

		std::cout << '\n';
	}
}

// main game loop
int main()
{
	srand(static_cast<unsigned>(time(nullptr)));
	Player player{ 2, 3 };


	int tick{ 1 };
	std::vector<char> validMovementChars{ 'w', 'a', 's', 'd' };
	std::vector <Tile> world {createWorld()};

	while (true)
	{
		int newX{ player.getX()};
		int newY{ player.getY()};
		printWorld(world, tick, player);

		char playerInput{ getValidatedMovementOption(validMovementChars) };

		if (playerInput == 'w')
			newY -= 1;
		else if (playerInput == 'a')
			newX -= 1;
		else if (playerInput == 's')
			newY += 1;
		else if (playerInput == 'd')
			newX += 1;

		if (newX >= 0 && newX < WIDTH && newY >= 0 && newY < HEIGHT)
		{
			player.setPos(newX, newY);
			tick++;
		}
		else
		{
			std::cout << "You can't go that way.\n";
		}
	}
}