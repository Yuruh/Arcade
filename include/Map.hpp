//
// Map.hpp for  in /home/yuruh/rendu/cpp_arcade/games/
//
// Made by Antoine Lempereur
// Login   <lemper_a@epitech.eu>
//
// Started on  Thu Mar 10 14:09:06 2016 Antoine Lempereur
// Last update Sat Mar 19 21:48:57 2016 Wasta-Geek
//

#ifndef MAP_HPP_
#define MAP_HPP_

#include "Tuple.hpp"
#include "Tile.hpp"

class   Map
{
private:
  Tuple<int>  dim;
  Tuple<Tile::Type, Tile::Direction> **tiles;
public:
  Map(int width, int height);
  ~Map();
  int	getWidth() const;
  int	getHeight() const;
  Tuple<Tile::Type, Tile::Direction>  **getTiles() const;
  bool	isOver();
  void	print();
  void	fillTile(int, int, Tile::Type, int);
  Tuple<Tile::Type, Tile::Direction>	getTile(int, int) const;
  Tile::Type	getTileType(int, int) const;
  Tile::Direction	getTileDir(int, int) const;
  void	clear();
};

#endif
