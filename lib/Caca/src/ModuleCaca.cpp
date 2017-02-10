//
// ModuleCaca.cpp for  in /home/yuruh/rendu/cpp/cpp_arcade/lib/Caca/src/
//
// Made by Antoine Lempereur
// Login   <lemper_a@epitech.eu>
//
// Started on  Mon Mar 14 14:32:44 2016 Antoine Lempereur
// Last update Fri Apr  1 17:13:54 2016 Antoine Lempereur
//

#include "ModuleCaca.hpp"

ModuleCaca::ModuleCaca(int x, int y, e_menu type, std::string const& path, std::string value, caca_canvas_t *canvas)
  : AModule(x, y, type, path), value(value), canvas(canvas)
{

}

ModuleCaca::~ModuleCaca()
{

}

void  ModuleCaca::display()
{
  if (this->selected)
    caca_draw_thin_box(this->canvas, this->x - 1, this->y - 1, this->value.size() + 2, 3);
  caca_put_str(this->canvas, this->x, this->y, this->value.c_str());
}
