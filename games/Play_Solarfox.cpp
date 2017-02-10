//
// Play_Solarfox.cpp for  in /home/wasta-geek/rendu/CPP/cpp_arcade
// 
// Made by Wasta-Geek
// Login   <ducate_c@epitech.net>
// 
// Started on  Tue Mar 29 14:53:58 2016 Wasta-Geek
// Last update Sun Apr  3 17:25:47 2016 Wasta-Geek
//

#include	<iostream>
#include	<istream>
#include	<unistd.h>
#include	"Protocol.hpp"
#include	"Solarfox.hpp"
#include	"Tile.hpp"

static void	translate_where(Solarfox& solarfox, struct arcade::WhereAmI **where)
{
  Tuple<int, int>	position = solarfox.getPosition();

  (*where)->position[0].x = position.a;
  (*where)->position[0].y = position.b;
  (*where)->lenght = 1;
}

static void	getmap(Solarfox &solarfox, struct arcade::GetMap **map)
{
  Map		*my_map;
  int		counter = 0;
  int		line = -1;
  int		col;
  int		width;
  int		height;
  Tile::Type	case_type;

  my_map = solarfox.getMap();
  width = my_map->getWidth();
  height = my_map->getHeight();
  if (map == NULL || *map == NULL)
    {
      *map = new arcade::GetMap [height * width];
      (*map)->width = width;
      (*map)->height = height;
    }
  while (++line < height)
    {
      col = -1;
      while (++col < width)
	{
	  case_type = my_map->getTileType(line, col);
	  if (case_type == Tile::EMPTY)
	    (*map)->tile[counter] = arcade::TileType::EMPTY;
	  else if (case_type == Tile::RESSOURCE)
	    (*map)->tile[counter] = arcade::TileType::POWERUP;
	  else if (case_type == Tile::MY_SHOOT)
	    {
	      (*map)->tile[counter] = arcade::TileType::MY_SHOOT;
	    }
	  else if (case_type == Tile::EVIL_SHOOT)
	    (*map)->tile[counter] = arcade::TileType::EVIL_SHOOT;
	  else
	    (*map)->tile[counter] = arcade::TileType::BLOCK;
	  counter++;
	}
    }
}

extern "C"
{
  void				Play()
  {
    arcade::CommandType		command;
    struct arcade::GetMap	*map;
    struct arcade::WhereAmI	*where;
    Solarfox			solarfox;

    where = new arcade::WhereAmI + 3;
    solarfox.init("MICHEL DRUCKER");
    map = NULL;
    while (read(0, &command, sizeof(uint16_t)) >= 0)
      {
	getmap(solarfox, &map);
	if (command != arcade::CommandType::PLAY)
	  map->type = command;
	if (command == arcade::CommandType::WHERE_AM_I)
	  {
	    translate_where(solarfox, &where);
	    where->type = command;
	    write(1, where, sizeof(*where) + (sizeof(arcade::Position) * where->lenght));
	  }
	else if (command == arcade::CommandType::GET_MAP)
	  write(1, map, sizeof(*map) + (sizeof(arcade::TileType) * map->width * map->height));
	else if (map->type == arcade::CommandType::SHOOT)
	  {
	    solarfox.applyCommand(EVENT_SHOOT);
	    solarfox.update_my_shoots();
	  }
	else if (command == arcade::CommandType::PLAY && map->type != arcade::CommandType::PLAY)
	  {
	    if (map->type == arcade::CommandType::GO_UP)
	      solarfox.applyCommand(EVENT_PRESS_UP);
	    else if (map->type == arcade::CommandType::GO_DOWN)
	      solarfox.applyCommand(EVENT_PRESS_DOWN);
	    else if (map->type == arcade::CommandType::GO_LEFT)
	      solarfox.applyCommand(EVENT_PRESS_LEFT);
	    else if (map->type == arcade::CommandType::GO_RIGHT)
	      solarfox.applyCommand(EVENT_PRESS_RIGHT);
	    else if (map->type == arcade::CommandType::GO_FORWARD)
	      solarfox.applyCommand(EVENT_FORWARD);
	    solarfox.update_player();
	    map->type = command;
	  }
      }
  }
}
