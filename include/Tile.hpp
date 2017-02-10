//
// Tile.hpp for  in /home/yuruh/rendu/cpp_arcade/include/
//
// Made by Antoine Lempereur
// Login   <lemper_a@epitech.eu>
//
// Started on  Thu Mar 10 14:02:40 2016 Antoine Lempereur
// Last update Sat Apr  2 18:25:20 2016 Wasta-Geek
//

#ifndef TILE_HPP_
#define TILE_HPP_

namespace   Tile
{
  enum Type { EMPTY, BLOCK, EVIL_DUDE, EVIL_SHOOT, MY_SHOOT, POWERUP, RESSOURCE,
              HEAD, BODY, TWISTED_BODY_LEFT, TWISTED_BODY_RIGHT, TAIL,
	      HEAD_P2, BODY_P2, TWISTED_BODY_LEFT_P2, TWISTED_BODY_RIGHT_P2, TAIL_P2};
  enum Direction {UP = 0, NONE, RIGHT = 90, DOWN = 180, LEFT = 270};
};

#endif
