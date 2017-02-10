//
// IDisplay.hpp for  in /home/yuruh/rendu/cpp_arcade/include/
//
// Made by Antoine Lempereur
// Login   <lemper_a@epitech.eu>
//
// Started on  Tue Mar  8 16:16:26 2016 Antoine Lempereur
// Last update Sun Apr  3 20:26:07 2016 Antoine Lempereur
//

#ifndef IDISPLAY_HPP_
#define IDISPLAY_HPP_

#include "Protocol.hpp"
#include "Map.hpp"
#include "Score.hpp"
#include "IGames.hpp"

class Core;

class   IDisplay
{
public:
  virtual     ~IDisplay() {}
  virtual void  drawMenu(std::map<std::string, std::string>) = 0;
  virtual void  init(Map *, Core *, Score *, std::map<Tile::Type, std::string>*) = 0;
  virtual void  update(t_game_status *) = 0;
};

#endif
