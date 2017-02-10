//
// Menu.cpp for  in /home/yuruh/rendu/cpp/cpp_arcade/lib/
//
// Made by Antoine Lempereur
// Login   <lemper_a@epitech.eu>
//
// Started on  Mon Mar 14 14:22:48 2016 Antoine Lempereur
// Last update Fri Apr  1 17:07:37 2016 Antoine Lempereur
//

#include "Menu.hpp"

Menu::Menu() : idx(0)
{

}

Menu::~Menu()
{

}

void    Menu::addModule(AModule *module)
{
  this->modules.push_back(module);
  if (this->modules.size() == 1)
    this->modules[0]->setSelected(true);
}

void    Menu::display() const
{
  for (std::vector<AModule*>::const_iterator it = this->modules.begin(); it != this->modules.end(); it++)
    (*it)->display();
}

void    Menu::selectNext()
{
  if (this->idx != this->modules.size() - 1)
  {
    this->modules[this->idx]->setSelected(false);
    this->idx++;
    this->modules[this->idx]->setSelected(true);
  }
  else
  {
    this->modules[this->idx]->setSelected(false);
    this->idx = 0;
    this->modules[this->idx]->setSelected(true);
  }
}

void    Menu::selectPrev()
{
  if (this->idx != 0)
  {
    this->modules[this->idx]->setSelected(false);
    this->idx--;
    this->modules[this->idx]->setSelected(true);
  }
  else
  {
    this->modules[this->idx]->setSelected(false);
    this->idx = this->modules.size() - 1;
    this->modules[this->idx]->setSelected(true);
  }
}

AModule*    Menu::getSelected()
{
  return (this->modules[this->idx]);
}
