//
// ModuleCaca.hpp for  in /home/yuruh/rendu/cpp/cpp_arcade/lib/Caca/include/
//
// Made by Antoine Lempereur
// Login   <lemper_a@epitech.eu>
//
// Started on  Mon Mar 14 13:45:42 2016 Antoine Lempereur
// Last update Fri Apr  1 17:14:10 2016 Antoine Lempereur
//

#ifndef MODULECACA_HPP_
#define MODULECACA_HPP_

#include <string>

#include "AModule.hpp"
#include "caca.h"

class   ModuleCaca : public AModule
{
private:
  std::string value;
  caca_canvas_t *canvas;
public:
  ModuleCaca(int, int, e_menu, std::string const&, std::string, caca_canvas_t *);
  ~ModuleCaca();
  virtual void display();
};

#endif
