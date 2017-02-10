//
// ModuleSfml.cpp for  in /home/yuruh/rendu/cpp/cpp_arcade/lib/Sfml/src/
//
// Made by Antoine Lempereur
// Login   <lemper_a@epitech.eu>
//
// Started on  Sat Mar 19 20:22:16 2016 Antoine Lempereur
// Last update Sat Apr  2 17:37:12 2016 Antoine Lempereur
//

#include "ModuleSfml.hpp"

ModuleSfml::ModuleSfml(int x, int y, e_menu type, std::string const& path, std::string const& name, sf::RenderWindow *w)
  : AModule(x, y, type, path)
{
  this->window = w;
  this->font = new sf::Font();
  this->font->loadFromFile("media/Blox2.ttf");
  this->text.setString(name);
  this->text.setColor(sf::Color(0, 103, 180));
  this->text.setFont(*(this->font));
  this->text.setCharacterSize(60);
  this->text.setPosition(x, y);
  this->lastTick = 0;
  this->characterSize = 60;
  this->isIncrementing = true;
  // this->my_clock = new sf::Clock();
}

ModuleSfml::~ModuleSfml()
{
  if (this->font)
    delete this->font;
}

void    ModuleSfml::display()
{
  this->text.setCharacterSize(this->characterSize);
   if (this->selected)
   {
    //  if (this->my_clock->getElapsedTime().asMicroseconds() > this->lastTick)
    //  {
    //   this->lastTick = this->my_clock->getElapsedTime().asMicroseconds();
      if (this->isIncrementing)
        this->characterSize += 1.5;
      else
        this->characterSize -= 1.5;
      if (this->characterSize >= 90)
        this->isIncrementing = false;
      if (this->characterSize <= 60)
        this->isIncrementing = true;
      }
    // }
   else
    this->characterSize = 60;
  this->window->draw(this->text);
}
