//
// Map.hpp for  in /home/yuruh/rendu/cpp_arcade/games/
//
// Made by Antoine Lempereur
// Login   <lemper_a@epitech.eu>
//
// Started on  Thu Mar 10 14:25:26 2016 Antoine Lempereur
// Last update Tue Mar 29 19:18:46 2016 Wasta-Geek
//

#include "Map.hpp"
#include	<iostream>

Map::Map(int width, int height)
{
  this->dim.a = width;
  this->dim.b = height;
  this->tiles = new Tuple<Tile::Type, Tile::Direction>*[height]();
  for (int i = 0; i < height; i++)
    this->tiles[i] = new Tuple<Tile::Type, Tile::Direction>[width]();
}

Map::~Map()
{

}

Tuple<Tile::Type, Tile::Direction>	Map::getTile(int line, int col) const
{
  return (this->tiles[line][col]);
}

Tile::Type	Map::getTileType(int line, int col) const
{
  return (this->tiles[line][col].a);
}

Tile::Direction	Map::getTileDir(int line, int col) const
{
  return (this->tiles[line][col].b);
}

int     Map::getWidth() const
{
  return (this->dim.a);
}

int     Map::getHeight() const
{
  return (this->dim.b);
}

Tuple<Tile::Type, Tile::Direction>  **Map::getTiles() const
{
  return (this->tiles);
}

bool	Map::isOver()
{
  int	counter_l = 0;
  int	counter_c;

  while (counter_l < this->dim.b)
    {
      counter_c = 0;
      while (counter_c < this->dim.a)
	if (this->tiles[counter_l][counter_c++].a == Tile::EMPTY)
	    return true;
      counter_l++;
    }
  return false;
}

//JE FAIS UN CAST PAS BEAU
void	Map::fillTile(int line, int col, Tile::Type a, int b)
{
  this->tiles[line][col].a = a;
  this->tiles[line][col].b = (Tile::Direction)b;
}

void	Map::clear()
{
  int	line = 0;
  int	col;

  while (line < this->dim.b)
    {
      col = 0;
      while (col < this->dim.a)
	{
	  this->tiles[line][col].a = Tile::EMPTY;
	  this->tiles[line][col].b = Tile::NONE;
	  col++;
	}
      line++;
    }
}

void	Map::print()
{
  int	counter_l = 0;
  int	counter;

  while (counter_l < this->dim.b)
    {
      counter = 0;
      while (counter < this->dim.a)
	{
	  if (this->tiles[counter_l][counter].a == Tile::RESSOURCE)
	    std::cout << "A";
	  else if (this->tiles[counter_l][counter].a == Tile::EMPTY)
	    std::cout << "-";
	  else
	    std::cout << "S";
	  counter++;
	}
      std::cout << std::endl;
      counter_l++;
    }
  std::cout << std::endl;
}
