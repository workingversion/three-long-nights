#ifndef TILES0192949101
#define TILES0192949101

class Tile
{
	char symbol;
public:
	enum TileType
	{
		Grass, Bush, Water
	};
private:
	TileType tileType;

public:
	char getSymbol() const;
	TileType getTileType() const;
	Tile(TileType type);
};

#endif