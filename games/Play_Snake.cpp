//
// Play_Snake.cpp for  in /home/wasta-geek/rendu/CPP/cpp_arcade
// 
// Made by Wasta-Geek
// Login   <ducate_c@epitech.net>
// 
// Started on  Tue Mar 29 14:53:58 2016 Wasta-Geek
// Last update Sun Apr  3 17:25:59 2016 Wasta-Geek
//

#include	<iostream>
#include	<istream>
#include	<unistd.h>
#include	"Protocol.hpp"
#include	"Snake.hpp"
#include	"Tile.hpp"

static void	translate_where(Snake& snake, struct arcade::WhereAmI **where)
{
  std::vector<Tuple<int, int>>	positions = snake.getVector();
  int		counter = 0;
  int		vector_length = positions.size();

  if (where == NULL || *where == NULL || (*where)->lenght != vector_length)
    {
      if (where != NULL && *where != NULL)
	delete[] ((*where));
      *where = new arcade::WhereAmI [vector_length + 1];
      (*where)->lenght = vector_length;
    }
  while (counter < vector_length)
    {
      (*where)->position[counter].x = positions[counter].b;
      (*where)->position[counter].y = positions[counter].a;
      counter++;
    }
}

static void	getmap(Snake &snake, struct arcade::GetMap **map)
{
  Map		*my_map;
  int		counter = 0;
  int		line = -1;
  int		col;
  int		width;
  int		height;
  Tile::Type	case_type;

  my_map = snake.getMap();
  if (map == NULL || *map == NULL)
    {
      width = my_map->getWidth();
      height = my_map->getHeight();
      *map = new arcade::GetMap [height * width];
      (*map)->width = width;
      (*map)->height = height;
    }
  width = (*map)->width;
  height = (*map)->height;
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
    Snake			snake;

    snake.init("J'adore cette musique");
    where = NULL;
    map = NULL;
    while (read(0, &command, sizeof(uint16_t)))
      {
	getmap(snake, &map);
	if (command != arcade::CommandType::PLAY)
	  map->type = command;
	if (command == arcade::CommandType::WHERE_AM_I)
	  {
	    translate_where(snake, &where);
	    where->type = command;
	    write(1, where, sizeof(*where) + (sizeof(arcade::Position) * where->lenght));
	  }
	else if (command == arcade::CommandType::GET_MAP)
	  write(1, map, sizeof(*map) + (sizeof(arcade::TileType) * map->width * map->height));
	else if (command == arcade::CommandType::PLAY && map->type != arcade::CommandType::PLAY)
	  {
	    if (map->type == arcade::CommandType::GO_UP)
	      snake.applyCommand(EVENT_PRESS_UP);
	    else if (map->type == arcade::CommandType::GO_DOWN)
	      snake.applyCommand(EVENT_PRESS_DOWN);
	    else if (map->type == arcade::CommandType::GO_LEFT)
	      snake.applyCommand(EVENT_PRESS_LEFT);
	    else if (map->type == arcade::CommandType::GO_RIGHT)
	      snake.applyCommand(EVENT_PRESS_RIGHT);
	    else if (map->type == arcade::CommandType::GO_FORWARD)
	      snake.applyCommand(EVENT_FORWARD);
	    snake.interpretCommand();
	    map->type = command;
	  }
      }
  }
}
