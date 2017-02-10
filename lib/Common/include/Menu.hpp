//
// AMenu.hpp for  in /home/yuruh/rendu/cpp/cpp_arcade/include/
//
// Made by Antoine Lempereur
// Login   <lemper_a@epitech.eu>
//
// Started on  Mon Mar 14 13:58:50 2016 Antoine Lempereur
// Last update Fri Apr  1 17:06:42 2016 Antoine Lempereur
//

#ifndef MENU_HPP_
#define MENU_HPP_

#include <vector>
#include <cstddef>

#include "AModule.hpp"

class   Menu
{
private:
  size_t  idx;
  std::vector<AModule*> modules;
public:
  Menu();
  ~Menu();
  void  addModule(AModule*);
  void  display() const;
  void  selectNext();
  void  selectPrev();
  AModule   *getSelected();
};

#endif
