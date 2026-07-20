#ifndef TILES0192949101
#define TILES0192949101

class Tile
{
	char symbol;
	bool hasResource;
	int lastTickThatHadResource;
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
	int getLastTickThatHadResource() const;
	bool getHasResource() const;
	void takeResource(int tick);
	void respawnResource();
	Tile(TileType type);
};

#endif