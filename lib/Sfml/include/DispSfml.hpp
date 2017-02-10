//
// Sfml.hpp for  in /home/yuruh/rendu/cpp_arcade/include/
//
// Made by Antoine Lempereur
// Login   <lemper_a@epitech.eu>
//
// Started on  Tue Mar  8 17:33:47 2016 Antoine Lempereur
// Last update Sun Apr  3 20:27:40 2016 Antoine Lempereur
//

#ifndef DISPSFML_HPP_
#define DISPSFML_HPP_

#include <unistd.h>

#include "Graphics.hpp" // dependencies ?
#include "Window.hpp" // dependencies ?
#include "Audio.hpp" // dependencies ?
#include "ADisplay.hpp"
#include "Core.hpp"
#include "MediaHandler.hpp"

class   DispSfml : public ADisplay
{
private:
  MediaHandler        media;
  sf::RenderWindow    *window;
  std::map<int, e_action> keyMap;
  int                 lastTick;
public:
  DispSfml();
  virtual ~DispSfml();
  void    setKeyMap();
  virtual void  drawMenu(std::map<std::string, std::string>);
  void          interpretKey(int);
  void          drawMap();
  void          drawBackground();
  void          drawEndScreen();
  void          handleEvents();
  void          init(Map*, Core*, Score*, std::map<Tile::Type, std::string>*);
  void          setWindow(sf::RenderWindow *w) { this->window = w; }
  sf::RenderWindow *getWindow() const { return (this->window); }
  MediaHandler      getMedia() const { return (this->media); }
};

#endif
