//
// Protagonist.cpp for  in /home/wasta-geek/rendu/CPP/cpp_arcade
// 
// Made by ducatez
// Login   <ducate_c@epitech.net>
// 
// Started on  Fri Mar 11 14:38:18 2016 ducatez
// Last update Tue Mar 15 15:52:11 2016 Wasta-Geek
//

#include	<iostream>
#include	"Protagonist.hpp"

Protagonist::Protagonist(int &height, int &width, int length)
{
  Tuple<int, int>	to_fill;

  width = (width % 2 == 0) ? width : width + 1;
  height = (height % 2 == 0) ? height : height + 1;
  this->head_position.a = height / 2;
  this->head_position.b = width / 2;
  this->length = length;
  // SET SPEED A QQCH this->speed = smth;
  // to_fill.a = height / 2;
  // to_fill.b = width / 2;
  // this->positions->push_back(to_fill);
  // to_fill.b = width / 2 - 1;
  // this->positions->push_back(to_fill);
  // to_fill.b = width / 2 - 2;
  // this->positions->push_back(to_fill);
  // to_fill.b = width / 2 - 3;
  // this->positions->push_back(to_fill);
}

Tuple<int>	Protagonist::getHeadPosition() const
{
  return (this->head_position);
}

void	Protagonist::setHeadPostion(int new_pos_line, int new_pos_col)
{
  this->head_position.a = new_pos_line;
  this->head_position.b = new_pos_col;
}

int	Protagonist::getLength() const
{
  return (this->length);
}

void	Protagonist::setLength(int new_length)
{
  this->length = new_length;
}

double	Protagonist::getSpeed() const
{
  return (this->speed);
}

void	Protagonist::setSpeed(double new_speed)
{
  this->speed = new_speed;
}
