//
// Snake.cpp for  in /home/wasta-geek/rendu/CPP/cpp_arcade/games
//
// Made by Wasta-Geek
// Login   <ducate_c@epitech.net>
//
// Started on  Tue Mar 15 14:46:13 2016 Wasta-Geek
// Last update Sun Apr  3 20:42:16 2016 Wasta-Geek
//

#include	<stdlib.h>
#include	<iostream>
#include	"Snake.hpp"

Snake::Snake()
{
}

Snake::~Snake()
{
  if (this->status)
    delete (this->status);
  if (this->scoreClass)
    delete (this->scoreClass);
  if (this->my_map)
    delete this->my_map;
}

std::map<Tile::Type, std::string>	*Snake::getSprites() const
{
  std::map<Tile::Type, std::string>	*sprites = new std::map<Tile::Type, std::string>;

  (*sprites)[Tile::Type::HEAD] = "media/snake_head.png";
  (*sprites)[Tile::Type::BODY] = "media/snake_body.png";
  (*sprites)[Tile::Type::TAIL] = "media/snake_tail.png";
  (*sprites)[Tile::Type::TWISTED_BODY_LEFT] = "media/snake_twisted_left.png";
  (*sprites)[Tile::Type::TWISTED_BODY_RIGHT] = "media/snake_twisted_right.png";
  (*sprites)[Tile::Type::HEAD_P2] = "media/snake_head_blue.png";
  (*sprites)[Tile::Type::BODY_P2] = "media/snake_body_blue.png";
  (*sprites)[Tile::Type::TAIL_P2] = "media/snake_tail_blue.png";
  (*sprites)[Tile::Type::TWISTED_BODY_LEFT_P2] = "media/snake_twisted_left_blue.png";
  (*sprites)[Tile::Type::TWISTED_BODY_RIGHT_P2] = "media/snake_twisted_right_blue.png";
  (*sprites)[Tile::Type::RESSOURCE] = "media/HEY_APPLE.png";
  return (sprites);
}

void			Snake::createSnake(int width, int height)
{
  Tuple<int, int>	my_fill;

  width = (width % 2 == 0) ? width : width - 1;
  height = (height % 2 == 0) ? height : height - 1;
  this->randomApple();
  this->positions.resize(1);
  my_fill.a = height / 2;
  my_fill.b = width / 2;
  this->positions[0].push_back(my_fill);
  my_fill.b--;
  this->positions[0].push_back(my_fill);
  my_fill.b--;
  this->positions[0].push_back(my_fill);
  my_fill.b--;
  this->positions[0].push_back(my_fill);
  this->my_map->fillTile(height / 2, width / 2 - 3, Tile::TAIL, Tile::RIGHT);
  this->my_map->fillTile(height / 2, width / 2 - 2, Tile::BODY, Tile::RIGHT);
  this->my_map->fillTile(height / 2, width / 2 - 1, Tile::BODY, Tile::RIGHT);
  this->my_map->fillTile(height / 2, width / 2, Tile::HEAD, Tile::RIGHT);
}

void			Snake::setMultiplayer()
{
  Tuple<int, int>	my_fill;
  int			width;
  int			height;

  width = this->my_map->getWidth();
  height = this->my_map->getHeight();
  this->status->coeff = 1;
  this->key[0] = EVENT_PAUSE;
  this->key[1] = EVENT_PAUSE;
  this->my_map->clear();
  this->have_apple = false;
  this->positions.resize(2);
  this->positions[0].clear();
  this->positions[1].clear();
  my_fill.a = 0;
  my_fill.b = SIZE_SNAKE_2P - 1;
  for (my_fill.b = SIZE_SNAKE_2P - 1; my_fill.b >= 0; my_fill.b--) {
    this->positions[0].push_back(my_fill);
    this->my_map->fillTile(0, SIZE_SNAKE_2P - my_fill.b - 1, Tile::BODY, Tile::RIGHT);
  }
  this->my_map->fillTile(0, 0, Tile::TAIL, Tile::RIGHT);
  this->my_map->fillTile(0, SIZE_SNAKE_2P - 1, Tile::HEAD, Tile::RIGHT);

  my_fill.a = height - 1;
  my_fill.b = width - SIZE_SNAKE_2P;
  for (my_fill.b = width - SIZE_SNAKE_2P; my_fill.b < width; my_fill.b++) {
    this->positions[1].push_back(my_fill);
    this->my_map->fillTile(height - 1, my_fill.b, Tile::BODY_P2, Tile::LEFT);
  }
  this->my_map->fillTile(height - 1, width  - 1, Tile::TAIL_P2, Tile::LEFT);
  this->my_map->fillTile(height - 1, width  - SIZE_SNAKE_2P, Tile::HEAD_P2, Tile::LEFT);
  this->speed = 75000;
  this->randomApple();
}


void	Snake::restart()
{
  this->my_map->clear();
  this->key.clear();
  this->status->is_over = false;
  this->status->score = 0;
  this->status->who_won = 0;
  this->status->coeff = 1;
  this->lastTick = 0;
  this->key.push_back(EVENT_FORWARD);
  this->speed = 80000;
  this->have_apple = false;
  if (this->positions.size() == 2)
    {
      this->positions.clear();
      this->setMultiplayer();
      return;
    }
  this->positions.clear();
  this->createSnake(this->my_map->getWidth(), this->my_map->getHeight());
}

void	Snake::init(std::string pseudo)
{
  int	height;
  int	width;

  height = 20;
  width = 40;
  this->my_map = new Map(width, height);
  this->status = new t_game_status();
  this->scoreClass = new Score();
  this->scoreClass->loadScoreFile("./scores/snake.score");
  this->status->pseudo = pseudo;
  this->status->score = 0;
  this->status->is_over = false;
  this->status->coeff = 1;
  this->status->camera_coeff = 0;
  this->status->who_won = 0;
  this->lastTick = 0;
  this->key.push_back(EVENT_FORWARD);
  this->speed = 80000;
  this->have_apple = false;
  this->createSnake(width, height);
}

Score	*Snake::getScore() const
{
  return (this->scoreClass);
}

extern "C"
{
  IGames	*create_instance()
  {
    return (new Snake());
  }
}

Map	*Snake::getMap() const
{
  return (this->my_map);
}

t_game_status  *Snake::update()
{
   struct timeval tmp;
   int            new_tick;
   double            nb_frame = FPS * ((double)this->speed / SEC_AS_MICROSEC);

   gettimeofday(&tmp, NULL);
   new_tick = tmp.tv_usec;
   if (new_tick < this->lastTick)
     new_tick += SEC_AS_MICROSEC;
   if (new_tick > this->lastTick + this->speed / nb_frame && this->key[0] != EVENT_PAUSE && this->status->is_over == false)
     {
       this->status->camera_coeff += 1 / (double)nb_frame;
       this->lastTick = tmp.tv_usec;
       if (this->status->camera_coeff > 0.99)
       {
         this->status->camera_coeff = 0;
         this->interpretCommand();
       }
     }
   return (this->status);
}

void	Snake::growUp(unsigned int& player)
{
  int   max_size = this->positions[player].size();
  int	line = this->positions[player][max_size - 1].a;
  int	col = this->positions[player][max_size - 1].b;
  Tuple<int, int>	to_fill;

  to_fill.a = line;
  to_fill.b = col;
  this->status->score++;
  if (line - 1 >= 0 && (this->my_map->getTileType(line - 1, col) == Tile::RESSOURCE
  			|| this->my_map->getTileType(line - 1, col) == Tile::EMPTY))
    to_fill.a = line - 1;
  else if (line + 1 < this->my_map->getHeight()
  	   && (this->my_map->getTileType(line + 1, col) == Tile::RESSOURCE
  	       || this->my_map->getTileType(line + 1, col) == Tile::EMPTY))
    to_fill.a = line + 1;
  else if (col - 1 >= 0
  	   && (this->my_map->getTileType(line, col - 1) == Tile::RESSOURCE
  	       || this->my_map->getTileType(line, col - 1) == Tile::EMPTY))
    to_fill.b = col - 1;
  else if (col + 1 < this->my_map->getWidth()
  	   && (this->my_map->getTileType(line, col + 1) == Tile::RESSOURCE
  	       || this->my_map->getTileType(line, col + 1) == Tile::EMPTY))
    to_fill.b = col + 1;
  else
    {
      this->status->is_over = true;
      this->status->who_won = (this->positions.size() == 1) ? 0 : 1 + (player + 1) % 2;
      this->status->coeff = 1;
      this->scoreClass->saveScore(this->status->pseudo, this->status->score);
      return;
    }
  this->positions[player].push_back(to_fill);
  this->my_map->fillTile(to_fill.a, to_fill.b, (player == 0) ? Tile::TAIL : Tile::TAIL_P2, this->my_map->getTileDir(line, col));
  this->my_map->fillTile(line, col,
  			 this->my_map->getTileType(this->positions[player][max_size - 2].a,
						   this->positions[player][max_size - 2].b),
  			 this->my_map->getTileDir(this->positions[player][max_size - 2].a,
						  this->positions[player][max_size - 2].b));
}

void	Snake::setTwisted(Tile::Direction& key, int &line, int &col, Tile::Direction &save_dir,
			  unsigned int &player)
{
  if (key == Tile::UP && save_dir == Tile::RIGHT)
    this->my_map->fillTile(line, col, (player == 0) ? Tile::TWISTED_BODY_RIGHT : Tile::TWISTED_BODY_RIGHT_P2, Tile::UP);
  else if (key == Tile::UP && save_dir == Tile::LEFT)
    this->my_map->fillTile(line, col, (player == 0) ? Tile::TWISTED_BODY_LEFT : Tile::TWISTED_BODY_LEFT_P2, Tile::UP);
  else if (key == Tile::DOWN && save_dir == Tile::LEFT)
    this->my_map->fillTile(line, col, (player == 0) ? Tile::TWISTED_BODY_RIGHT : Tile::TWISTED_BODY_RIGHT_P2, Tile::DOWN);
  else if (key == Tile::DOWN && save_dir == Tile::RIGHT)
    this->my_map->fillTile(line, col, (player == 0) ? Tile::TWISTED_BODY_RIGHT : Tile::TWISTED_BODY_RIGHT_P2, Tile::LEFT);
  else if (key == Tile::RIGHT && save_dir == Tile::UP)
    this->my_map->fillTile(line, col, (player == 0) ? Tile::TWISTED_BODY_LEFT : Tile::TWISTED_BODY_LEFT_P2, Tile::RIGHT);
  else if (key == Tile::RIGHT && save_dir == Tile::DOWN)
    this->my_map->fillTile(line, col, (player == 0) ? Tile::TWISTED_BODY_RIGHT : Tile::TWISTED_BODY_RIGHT_P2, Tile::RIGHT);
  else if (key == Tile::LEFT && save_dir == Tile::UP)
    this->my_map->fillTile(line, col, (player == 0) ? Tile::TWISTED_BODY_LEFT : Tile::TWISTED_BODY_LEFT_P2, Tile::DOWN);
  else if (key == Tile::LEFT && save_dir == Tile::DOWN)
    this->my_map->fillTile(line, col, (player == 0) ? Tile::TWISTED_BODY_LEFT : Tile::TWISTED_BODY_LEFT_P2, Tile::LEFT);
  else
    this->my_map->fillTile(line, col, (player == 0) ? Tile::BODY : Tile::BODY_P2,
  			   this->my_map->getTileDir(this->positions[player][0].a, this->positions[player][0].b));
}

void	Snake::eventEatApple(unsigned int &player)
{
  this->have_apple = false;
  this->growUp(player);
  if (this->speed >= 10000)
    this->speed -= 1000;
  this->randomApple();
}

void	Snake::moveHead(Tile::Direction key, int &line, int &col, unsigned int &player)
{
  int	add_col;
  int	add_line;
  Tile::Direction	save_dir;
  bool			eaten_apple = false;
 
  findMovement(line, col, key, add_line, add_col);
  if (this->status->is_over == false && (add_col != 0 || add_line != 0))
    {
      if (this->my_map->getTileType(line + add_line, col + add_col) == Tile::RESSOURCE)
	eaten_apple = true;
      if (this->status->is_over == true)
      	return;
      this->my_map->fillTile(line + add_line, col + add_col,
			     (player == 0) ? Tile::HEAD : Tile::HEAD_P2, key);
      add_line += line;
      add_col += col;
      save_dir = this->my_map->getTileDir(line, col);
      this->positions[player][0].a = add_line;
      this->positions[player][0].b = add_col;
      add_line = line;
      add_col = col;
      setTwisted(key, add_line, add_col, save_dir, player);
      line = this->positions[player][1].a;
      col = this->positions[player][1].b;
      this->positions[player][1].a = add_line;
      this->positions[player][1].b = add_col;
      if (eaten_apple == true)
	this->eventEatApple(player);
    }
  else
    {
      if (this->status->who_won != 3)
	this->status->who_won = (this->positions.size() == 1) ? 0 : 1 + (player + 1) % 2;
      this->scoreClass->saveScore(this->status->pseudo, this->status->score);
    }
}

void	Snake::setTailDir(int &counter, int &line, int &col, unsigned int &player)
{
  int			prev_line = this->positions[player][counter - 1].a;
  int			prev_col = this->positions[player][counter - 1].b;

  if (prev_line == line  && col > prev_col)
    this->my_map->fillTile(line, col, (player == 0) ? Tile::TAIL : Tile::TAIL_P2, Tile::LEFT);
  else if (prev_line == line  && col < prev_col)
    this->my_map->fillTile(line, col, (player == 0) ? Tile::TAIL : Tile::TAIL_P2, Tile::RIGHT);
  else if (prev_line > line  && col == prev_col)
    this->my_map->fillTile(line, col, (player == 0) ? Tile::TAIL : Tile::TAIL_P2, Tile::DOWN);
  else if (prev_line < line  && col == prev_col)
    this->my_map->fillTile(line, col, (player == 0) ? Tile::TAIL : Tile::TAIL_P2, Tile::UP);
}

Tile::Direction	Snake::getDirection(e_action key, int line, int col) const
{
  Tile::Direction	press_dir;

  if (key == EVENT_PRESS_RIGHT || key == EVENT_P2_RIGHT)
    press_dir = Tile::RIGHT;
  else if (key == EVENT_PRESS_LEFT || key == EVENT_P2_LEFT)
    press_dir = Tile::LEFT;
  else if (key == EVENT_PRESS_UP || key == EVENT_P2_UP)
    press_dir = Tile::UP;
  else if (key == EVENT_PRESS_DOWN || key == EVENT_P2_DOWN)
    press_dir = Tile::DOWN;
  else if (key == EVENT_FORWARD)
    press_dir = this->my_map->getTileDir(line, col);
  return (press_dir);
}

void			Snake::interpretCommand()
{
  int			counter;
  int			max_size;
  int			line;
  int			col;
  int			tmp_line;
  int			tmp_col;
  Tile::Direction	press_dir;
  unsigned int		counter_vect = 0;

  if (this->status->is_over == true || this->key[0] == EVENT_PAUSE)
    return;
  while (counter_vect < this->positions.size())
    {
      counter = 2;
      line = this->positions[counter_vect][0].a;
      col = this->positions[counter_vect][0].b;
      press_dir = getDirection(this->key[counter_vect], line, col);
      this->moveHead(press_dir, line, col, counter_vect);
      if (this->status->is_over == true)
      	return;
      max_size = this->positions[counter_vect].size();
      while (counter < max_size)
      	{
      	  tmp_line = this->positions[counter_vect][counter].a;
      	  tmp_col = this->positions[counter_vect][counter].b;
      	  if (counter == max_size - 1)
      	    this->my_map->fillTile(this->positions[counter_vect][counter].a,
      				   this->positions[counter_vect][counter].b, Tile::EMPTY, Tile::UP);
      	  this->positions[counter_vect][counter].a = line;
      	  this->positions[counter_vect][counter].b = col;
      	  if (counter == max_size - 1)
      	    setTailDir(counter, line, col, counter_vect);
      	  line = tmp_line;
      	  col = tmp_col;
      	  counter++;
      }
      counter_vect++;
    }
}

void			Snake::applyCommand(e_action key)
{
  Tile::Direction	head_dir;
  unsigned int		counter;

  if (key == EVENT_PAUSE)
    {
      counter = 0;
      while (counter < this->positions.size())
  	{
  	  this->key[counter] = (this->key[counter] == EVENT_PAUSE) ? EVENT_FORWARD : EVENT_PAUSE;
  	  counter++;
  	}
    }
  else if (key == EVENT_ADD_PLAYER && this->positions.size() == 1)
    setMultiplayer();
  if (key == EVENT_PAUSE || key == EVENT_ADD_PLAYER || key == EVENT_SHOOT)
    return;
  if (key >= 14 && this->positions.size() == 1)
    return ;
  counter = (key >= 14) ? 1 : 0;
  head_dir = this->my_map->getTileDir(this->positions[counter][0].a, this->positions[counter][0].b);
  if ((head_dir != Tile::LEFT && (key == EVENT_PRESS_RIGHT || key == EVENT_P2_RIGHT))
      || (head_dir != Tile::RIGHT && (key == EVENT_PRESS_LEFT || key == EVENT_P2_LEFT))
      || (head_dir != Tile::UP && (key == EVENT_PRESS_DOWN || key == EVENT_P2_DOWN))
      || (head_dir != Tile::DOWN && (key == EVENT_PRESS_UP || key == EVENT_P2_UP)))
    this->key[counter] = key;
  else if (key == EVENT_PRESS_RIGHT || key == EVENT_PRESS_LEFT
	   || key == EVENT_PRESS_DOWN || key == EVENT_PRESS_UP
	   || key == EVENT_P2_RIGHT || key == EVENT_P2_LEFT || key == EVENT_P2_DOWN || key == EVENT_P2_UP)
    this->key[counter] = EVENT_FORWARD;
}

void	Snake::findMovement(int &line, int &col, Tile::Direction &key, int &add_line, int &add_col)
{
  Tile::Direction	head_dir = this->my_map->getTileDir(line, col);

  add_line = 0;
  add_col = 0;
  if (key == Tile::UP)
    add_line = (head_dir == Tile::DOWN) ? 0 : -1;
  else if (key == Tile::DOWN)
    add_line = (head_dir == Tile::UP) ? 0 : 1;
  else if (key == Tile::RIGHT)
    add_col = (head_dir == Tile::LEFT) ? 0 : 1;
  else if (key == Tile::LEFT)
    add_col = (head_dir == Tile::RIGHT) ? 0 : -1;
  if (add_line == 0 && add_col == 0)
    return;
  if ((line + add_line < this->my_map->getHeight() && col + add_col < this->my_map->getWidth()
       && line + add_line >= 0 && col + add_col >= 0)
      && (this->my_map->getTileType(line + add_line, col + add_col) == Tile::EMPTY
	  || this->my_map->getTileType(line + add_line, col + add_col) == Tile::RESSOURCE))
    return;
  if ((line + add_line < this->my_map->getHeight() && col + add_col < this->my_map->getWidth()
       && line + add_line >= 0 && col + add_col >= 0)
      && (this->my_map->getTileType(line + add_line, col + add_col) == Tile::HEAD
	  || this->my_map->getTileType(line + add_line, col + add_col) == Tile::HEAD_P2))
    this->status->who_won = 3;
  this->status->is_over = true;
}

void    Snake::randomApple()
{
  int   counter_l = 0;
  int   counter_c;

  if (this->have_apple == false)
    {
      while (this->my_map->getTileType(counter_l = rand() % this->my_map->getHeight(),
				       counter_c = rand() % this->my_map->getWidth()) != Tile::EMPTY);
      this->have_apple = true;
      this->my_map->fillTile(counter_l, counter_c, Tile::RESSOURCE, Tile::NONE);
    }
}

std::vector<Tuple<int, int>>	Snake::getVector() const
{
  return (this->positions[0]);
}
