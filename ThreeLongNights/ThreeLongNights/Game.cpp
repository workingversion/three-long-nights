#include <iostream>
#include <vector>
#include <limits>
#include <cstdlib>
#include <ctime>
#include "Tile.h"
#include "Player.h"
#include "Animals.h"


// establish width and height of grid
const int WIDTH{ 10 };
const int HEIGHT{ 10 };

bool isActionValid(const std::vector<char>& actions, char input)
{
	bool found{ false };

	for (char action : actions)
	{
		if (input == action)
		{
			found = true;
			break;
		}
	}

	return found;
}

// char input validation
char getValidatedPlayerAction(const std::string& prompt, const std::vector<char>& actions)
{
	char input{};

	while (true)
	{
		std::cout << prompt;
		std::cin >> input;

		if (std::cin.fail())
		{
			std::cin.clear();
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			std::cout << "Invalid input.\n";
			continue;
		}

		bool found{ isActionValid(actions, input) };

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

		if (rng <= 5)
			world.push_back(Tile{ Tile::Water});
		else if (rng <= 90)
			world.push_back(Tile{ Tile::Grass});
		else
			world.push_back(Tile{ Tile::Bush});
	}

	return world;
}


bool isDay(int tick)
{
	return (( tick - 1) % 100 < 50);
}

// prints the grid as passed to it with divisions between layers and labels the tick
void printWorld(const std::vector<Tile>& world, int tick, const Player& player, std::vector<Animal*>&animals)
{
	std::string timeOfDay { isDay(tick) ? "Day" : "Night"};

	std::cout << "Tick " << tick << " - " << timeOfDay << '\n';
	// nested for loop to print rows (which come first, y) and columns (second, x)
	for (int y{ 0 }; y < HEIGHT; y++)
	{
		for (int x{ 0 }; x < WIDTH; x++)
		{
			bool animalFound{ false };
			for (Animal* animal : animals)
			{
				if (x == animal->getX() && y == animal->getY())
				{
					std::cout << ' ' << animal->getSymbol() << ' ';
					animalFound = true;
				}
			}

			if (!animalFound)
			{
				if (x == player.getX() && y == player.getY())
					std::cout << ' ' << player.getSymbol() << ' ';
				else
					std::cout << ' ' << world[cellIndex(x, y)].getSymbol() << ' ';
			}
		}

		std::cout << '\n';
	}
}

// check if tile even exists
bool isInBounds(int x, int y)
{
	return x >= 0 && x < WIDTH && y >= 0 && y < HEIGHT;
}

// check if the grid tile it's trying to reach is accessible (not water)
bool canEnter(int x, int y, const std::vector<Tile>& world)
{
	return isInBounds(x, y)
		&& world[cellIndex(x, y)].getTileType() != Tile::Water;
}

// logic moved from main
// takes input and applies properly
void applyOffsets(char input, int& x, int& y)
{
	if (input == 'W' || input == 'w')
		y -= 1;
	else if (input == 'A' || input == 'a')
		x -= 1;
	else if (input == 'S' || input == 's')
		y += 1;
	else if (input == 'D' || input == 'd')
		x += 1;
}

std::vector<int> getValidStartingCoordinates(const std::vector<Tile>& world, const Player& player)
{
	int randomX{ rand() % WIDTH };
	int randomY{ rand() % HEIGHT };

	int distance{ abs(randomX - player.getX()) + abs(randomY - player.getY()) };
	while (!canEnter(randomX, randomY, world) || distance <= 3)
	{
		randomX = rand() % WIDTH;
		randomY = rand() % HEIGHT;
		distance = abs(randomX - player.getX()) + abs(randomY - player.getY());
	}

	return std::vector<int>{randomX, randomY};
}

// main game loop
int main()
{
	srand(static_cast<unsigned>(time(nullptr)));
	Player player{ 2, 3 };


	int tick{ 1 };
	std::vector<char> validActionChars{ 'w', 'a', 's', 'd', 'x'};
	std::vector <Tile> world {createWorld()};

	std::vector<int> bearStartingCoords{ getValidStartingCoordinates(world, player) };
	Bear bear{ bearStartingCoords[0], bearStartingCoords[1]};

	std::vector<Animal*> animals{&bear};

	// game ends after 300 ticks (3 days)
	while (tick <= 300)
	{
		int newX{ player.getX()};
		int newY{ player.getY()};
		printWorld(world, tick, player, animals);

		char playerInput{ getValidatedPlayerAction("Type w/a/s/d for movement, or x to open the interact options.", validActionChars)};
		bool playerTriedToMove{ playerInput != 'x' && playerInput != 'X'};

		if (playerTriedToMove)
		{
			applyOffsets(playerInput, newX, newY);

			if (canEnter(newX, newY, world))
			{
				player.setPos(newX, newY);
			}
			else
			{
				std::cout << "You can't go that way.\n";
			}
		}
		else
		{
			playerInput = getValidatedPlayerAction("Type w/a/s/d respectively to interact with the tile in that direction, or type 'x' to interact with the tile you're in.\n", validActionChars);

			applyOffsets(playerInput, newX, newY);

			if (isInBounds(newX, newY))
			{
				player.interactTile(world[cellIndex(newX, newY)], tick);
			}
			else
			{
				std::cout << "There is no valid tile to interact with!\n";
			}
		}

		for (Animal* animal : animals)
		{
			animal->takeTurn(world, player);
		}

		tick++;
		std::cout << '\n';
	}

	// TODO: add game completion celebration
	// maybe with stats? original tiles explored, berries picked, etc?
}