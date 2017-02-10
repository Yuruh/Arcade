//
// ADisplay.hpp for  in /home/yuruh/rendu/cpp_arcade/include/
//
// Made by Antoine Lempereur
// Login   <lemper_a@epitech.eu>
//
// Started on  Fri Mar 11 12:47:43 2016 Antoine Lempereur
// Last update Sun Apr  3 20:24:49 2016 Antoine Lempereur
//

#ifndef ADISPLAY_HPP_
#define ADISPLAY_HPP_

#include "IDisplay.hpp"
#include "Menu.hpp"
#include <thread>
#include <sys/time.h>
#include "Core.hpp"

#define   FPS   60
#define   SEC_AS_MICROSEC   1000000

class   ADisplay : public IDisplay
{
protected:
  Map     *map;
  Core    *core;
  Menu    menu;
  Score   *score;
  t_game_status *status;
public:
  ADisplay();
  virtual ~ADisplay();
  virtual void drawMenu(std::map<std::string, std::string>) = 0;
  virtual void drawMap() = 0;
  virtual void init(Map *map, Core *core, Score *score, std::map<Tile::Type, std::string>*);
  void update(t_game_status *);
  virtual void notifyKeyPressed();
};

#endif
