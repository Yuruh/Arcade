//
// AModule.cpp for  in /home/yuruh/rendu/cpp/cpp_arcade/lib/
//
// Made by Antoine Lempereur
// Login   <lemper_a@epitech.eu>
//
// Started on  Mon Mar 14 14:51:47 2016 Antoine Lempereur
// Last update Fri Apr  1 17:04:00 2016 Antoine Lempereur
//

#include "AModule.hpp"

AModule::AModule(int x, int y, e_menu type, std::string const& path) : x(x), y(y), selected(false), type(type), path(path)
{

}

AModule::~AModule()
{

}

void  AModule::setSelected(bool selection)
{
  this->selected = selection;
}

bool  AModule::isSelected() const
{
  return (this->selected);
}
