//
// ADisplay.cpp for  in /home/yuruh/rendu/cpp_arcade/lib/
//
// Made by Antoine Lempereur
// Login   <lemper_a@epitech.eu>
//
// Started on  Fri Mar 11 13:36:24 2016 Antoine Lempereur
// Last update Sun Apr  3 16:13:28 2016 Antoine Lempereur
//

#include "ADisplay.hpp"
#include "Core.hpp"

ADisplay::ADisplay() : map(NULL), menu(), score(NULL)
{
}

ADisplay::~ADisplay()
{
}

void  ADisplay::init(Map *map, Core *core, Score *score, std::map<Tile::Type, std::string> *text_sprite)
{
  this->map = map;
  this->core = core;
  this->score = score;
  (void)text_sprite;
}

void  ADisplay::update(t_game_status *status)
{
  this->status = status;
  this->drawMap();
}

void  ADisplay::notifyKeyPressed()
{

}
