#include "Tile.h"

Tile::Tile(TileType type) :
	tileType(type) 
{ 
	if (type == Tile::Water)
		symbol = '~';
	else if (type == Tile::Bush)
		symbol = 'x';
	else
		symbol = '.';
};

char Tile::getSymbol() const
{
	return symbol;
}

Tile::TileType Tile::getTileType() const
{
	return tileType;
}