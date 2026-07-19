#include <iostream>
#include <vector>
#include <limits>
#include <cstdlib>
#include <ctime>
#include "Tile.h"
#include "Player.h"


// establish width and height of grid
const int WIDTH{ 10 };
const int HEIGHT{ 5 };

// char input validation
char getValidatedPlayerAction(const std::vector<char>& actions)
{
	char input{};

	while (true)
	{
		std::cout << "Type w/a/s/d for movement, or x to interact with the tile you're standing on or nearby.";
		std::cin >> input;

		if (std::cin.fail())
		{
			std::cin.clear();
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			std::cout << "Invalid input.\n";
			continue;
		}

		bool found{ false };

		for (char action : actions)
		{
			if (input == action)
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
void printWorld(const std::vector<Tile>& world, int tick, const Player& player)
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

bool isDay(int tick)
{
	return (tick % 100 < 50);
}

// main game loop
int main()
{
	srand(static_cast<unsigned>(time(nullptr)));
	Player player{ 2, 3 };


	int tick{ 1 };
	std::vector<char> validActionChars{ 'w', 'a', 's', 'd', 'x'};
	std::vector <Tile> world {createWorld()};

	// game ends after 300 ticks (3 days)
	while (tick <= 300)
	{
		int newX{ player.getX()};
		int newY{ player.getY()};
		printWorld(world, tick, player);

		char playerInput{ getValidatedPlayerAction(validActionChars) };

		if (playerInput == 'w')
			newY -= 1;
		else if (playerInput == 'a')
			newX -= 1;
		else if (playerInput == 's')
			newY += 1;
		else if (playerInput == 'd')
			newX += 1;

		//TODO: add interact action in else if chain here

		if (newX >= 0 && newX < WIDTH && newY >= 0 && newY < HEIGHT
			&& world[cellIndex(newX, newY)].getTileType() != Tile::Water)
		{
			player.setPos(newX, newY);
		}
		else
		{
			std::cout << "You can't go that way.\n";
		}

		tick++;
	}
}