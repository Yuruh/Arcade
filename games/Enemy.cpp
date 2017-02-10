//
// Enemy.cpp for  in /home/wasta-geek/rendu/CPP/cpp_arcade
// 
// Made by Wasta-Geek
// Login   <ducate_c@epitech.net>
// 
// Started on  Wed Mar 30 15:51:47 2016 Wasta-Geek
// Last update Sat Apr  2 22:28:04 2016 Wasta-Geek
//

#include	<iostream>
#include	<stdlib.h>
#include	<sys/time.h>
#include	"Enemy.hpp"

Enemy::Enemy(int posx, int posy, Tile::Direction key, Tile::Direction orientation,
	     std::list<t_shoot> *shoots)
{
  this->position.a = posx;
  this->position.b = posy;
  this->key = key;
  this->percent_shoot = 10;
  this->orientation = orientation;
  this->shoots = shoots;
}

Enemy::~Enemy()
{
}

static void	invertKey(Tile::Direction &key)
{
  if (key == Tile::DOWN)
    key = Tile::UP;
  else if (key == Tile::UP)
    key = Tile::DOWN;
  else if (key == Tile::LEFT)
    key = Tile::RIGHT;
  else if (key == Tile::RIGHT)
    key = Tile::LEFT;
}
void	Enemy::findMove(Map *map)
{
  int	height = map->getHeight();
  int	width = map->getWidth();

  if ((this->key == Tile::UP && this->position.b == 1)
      || (this->key == Tile::DOWN && this->position.b == height - 2)
      || (this->key == Tile::LEFT && this->position.a == 1)
      || (this->key == Tile::RIGHT && this->position.a == width - 2))
    invertKey(this->key);
  if (this->key == Tile::UP)
    this->position.b -= 1;
  else if (this->key == Tile::DOWN)
    this->position.b += 1;
  else if (this->key == Tile::RIGHT)
    this->position.a += 1;
  else
    this->position.a -= 1;
}

void	Enemy::update(Map *map)
{
  int			old_x;
  int			old_y;

  if (rand() % 100 <= this->percent_shoot)
    {
      if (this->orientation == Tile::LEFT)
	this->addShoot(this->position.a, this->position.b, Tile::LEFT);
      else if (this->orientation == Tile::RIGHT)
	this->addShoot(this->position.a, this->position.b, Tile::RIGHT);
      else if (this->orientation == Tile::UP)
	this->addShoot(this->position.a, this->position.b, Tile::UP);
      else if (this->orientation == Tile::DOWN)
	this->addShoot(this->position.a, this->position.b, Tile::DOWN);
    }
  old_x = this->position.a;
  old_y = this->position.b;
  findMove(map);
  map->fillTile(old_y, old_x, Tile::EMPTY, this->orientation);
  map->fillTile(this->position.b, this->position.a, Tile::EVIL_DUDE, this->orientation);
}


void	Enemy::addShoot(int x, int y, Tile::Direction orientation)
{
  t_shoot	to_add;

  if (shoots->size() <= 5)
    {
      to_add.x = x;
      to_add.y = y;
      to_add.orientation = orientation;
      shoots->push_back(to_add);
    }
}
