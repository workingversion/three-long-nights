#include <iostream>
#include <vector>
#include <limits>

// establish width and height of the grid
const int WIDTH{ 5 };
const int HEIGHT{ 5 };

// char input validation
char getValidatedMovementOption(std::vector<char> chars)
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

		return input;
	}
}

// prints the grid as passed to it with divisions between layers and labels the tick
void printGrid(int tick, int playerX, int playerY)
{
	std::cout << "Tick " << tick << '\n';
	// nested for loop to print rows (which come first, y) and columns (second, x)
	for (int y{ 0 }; y < HEIGHT; y++)
	{
		for (int x{ 0 }; x < WIDTH; x++)
		{
			if (x == playerX && y == playerY)
				std::cout << " @ ";
			else
				std::cout << " . ";
		}

		std::cout << '\n';
	}
}

// main game loop
int main()
{
	int playerY{ 2 };
	int playerX{ 3 };
	int newX{};
	int newY{};
	int tick = 1;

	std::vector<char> movementOptions{ 'w', 'a', 's', 'd' };

	while (true)
	{
		newX = playerX;
		newY = playerY;
		printGrid(tick, playerX, playerY);
		char movementKey{ getValidatedMovementOption(movementOptions) };

		if (movementKey == 'w')
			newY = playerY - 1;
		else if (movementKey == 'a')
			newX = playerX - 1;
		else if (movementKey == 's')
			newY = playerY + 1;
		else
			newX = playerX + 1;

		if (newX >= 0 && newX < WIDTH && newY >= 0 && newY < HEIGHT)
		{
			playerX = newX;
			playerY = newY;
		}
		else
		{
			std::cout << "You can't go that way.\n";
		}

		tick++;
	}
}