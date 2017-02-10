//
// ModuleSfml.hpp for  in /home/yuruh/rendu/cpp/cpp_arcade/lib/Sfml/include/
//
// Made by Antoine Lempereur
// Login   <lemper_a@epitech.eu>
//
// Started on  Sat Mar 19 19:58:33 2016 Antoine Lempereur
// Last update Sat Apr  2 17:33:31 2016 Antoine Lempereur
//

#ifndef MODULESFML_HPP_
#define MODULESFML_HPP_

#include "AModule.hpp"
#include "Graphics.hpp"
#include "Tuple.hpp"
#include <iostream>
#include <sys/time.h>
#include "Core.hpp"

class   ModuleSfml : public AModule
{
private:
  sf::Text          text;
  sf::RenderWindow  *window;
  int               lastTick;
  double            characterSize;
  bool              isIncrementing;
  // sf::Clock         *my_clock;
  sf::Font          *font;
public:
  ModuleSfml(int, int, e_menu, std::string const&, std::string const&, sf::RenderWindow*);
  ~ModuleSfml();
  virtual void display();
};

#endif
