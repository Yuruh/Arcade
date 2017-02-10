//
// DispCaca.hpp for  in /home/yuruh/rendu/cpp_arcade/include/
//
// Made by Antoine Lempereur
// Login   <lemper_a@epitech.eu>
//
// Started on  Fri Mar 11 14:05:46 2016 Antoine Lempereur
// Last update Sun Apr  3 20:25:55 2016 Antoine Lempereur
//

#ifndef DISPCACA_HPP_
#define DISPCACA_HPP_

#include "ADisplay.hpp"
#include "Tile.hpp"
#include <map>
#include "caca.h"

#define   CACA_SPACE 32
#define   CACA_NUM2 50
#define   CACA_NUM3 51
#define   CACA_NUM4 52
#define   CACA_NUM5 53
#define   CACA_NUM8 56
#define   CACA_NUM9 57
#define   CACA_F    102

class   DispCaca : public ADisplay
{
private:
  std::map<Tile::Type, uint8_t> textures;
  caca_display_t                *display;
  caca_canvas_t                 *canvas;
  std::map<int, e_action>       keyMap;
  std::string                   playerName;
public:
  DispCaca();
  virtual ~DispCaca();
  virtual void  drawMenu(std::map<std::string, std::string>);
  virtual void  drawMap();
  void          drawEndScreen();
  void          setKeyMap();
  void          interpretKey(int);
};

#endif
