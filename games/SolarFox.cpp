//
// SolarFox.cpp for  in /home/wasta-geek/rendu/CPP/cpp_arcade
//
// Made by Wasta-Geek
// Login   <ducate_c@epitech.net>
//
// Started on  Wed Mar 30 13:27:29 2016 Wasta-Geek
// Last update Sun Apr  3 18:28:31 2016 Wasta-Geek
//

#define FPS 60
#define SEC_AS_MICROSEC 1000000

#include	<unistd.h>
#include	<sys/time.h>
#include	"Solarfox.hpp"

Solarfox::Solarfox()
{
}

Solarfox::~Solarfox()
{
  if (this->enemies)
    {
      delete this->enemies[0];
      delete this->enemies[1];
      delete this->enemies[2];
      delete this->enemies[3];
    }
  if (this->scoreClass)
    delete (this->scoreClass);
  if (this->my_map)
    delete (this->my_map);
  if (this->status)
    delete (this->status);
}

void	Solarfox::setBorder()
{
  int	col = 1;
  int	line = 1;
  int	height = this->my_map->getHeight();
  int	width = this->my_map->getWidth();

  while (col < width - 1)
    {
      this->my_map->fillTile(line, col, Tile::BLOCK, Tile::NONE);
      this->my_map->fillTile(line + height - 3, col, Tile::BLOCK, Tile::NONE);
      col++;
    }
  col = 1;
  while (line < height - 1)
    {
      this->my_map->fillTile(line, col, Tile::BLOCK, Tile::NONE);
      this->my_map->fillTile(line, col + width - 3, Tile::BLOCK, Tile::NONE);
      line++;
    }
}

void	Solarfox::fillLineRessources(Map *map, int line, int nbr_case)
{
  int	col = 2;
  int	limit = map->getWidth() - 2;
  Tuple<int, int>	to_add;

  while (col < limit)
    {
      if (!(line >= 9 && line <= 11 && col >= 18 && col <= 22))
	if (col > (nbr_case / 2) && col < limit - nbr_case / 2)
	  {
	    to_add.a = col;
	    to_add.b = line;
	    this->ressources.push_back(to_add);
	    map->fillTile(line, col, Tile::RESSOURCE, Tile::NONE);
	  }
      col++;
    }
}

void	Solarfox::makeJesusSpawnRessources(int nbr_case)
{
  int	line = 2 + nbr_case / 2;
  int	height = this->my_map->getHeight();

  while (line < height - nbr_case / 2 - 2)
    {
      fillLineRessources(this->my_map, line, nbr_case);
      line++;
    }
  if (nbr_case % 2 == 1)
    fillLineRessources(this->my_map, line, nbr_case);
}

void	Solarfox::restart()
{
  this->position.a = this->my_map->getWidth() / 2;
  this->position.b = this->my_map->getHeight() / 2;
  this->ressources.clear();
  this->my_map->clear();
  this->evilshoots.clear();
  this->shoots.clear();
  this->makeJesusSpawnRessources(difficulty = 20);
  this->status->score = 0;
  this->status->is_over = false;
  this->status->coeff = 0;
  this->status->who_won = 0;
  this->lastTick = 0;
  this->key = EVENT_FORWARD;
  this->my_map->fillTile(this->my_map->getHeight() / 2, this->my_map->getWidth() / 2,
			 Tile::HEAD, Tile::RIGHT);
}

void	Solarfox::init(std::string pseudo)
{
  int	height;
  int	width;

  height = 20;
  width = 40;
  this->my_map = new Map(width, height);
  this->status = new t_game_status();
  this->scoreClass = new Score();
  this->enemies[0] = new Enemy(0, 0, Tile::RIGHT, Tile::DOWN, &this->evilshoots);
  this->enemies[1] = new Enemy(0, 0, Tile::DOWN, Tile::RIGHT, &this->evilshoots);
  this->enemies[2] = new Enemy(width - 1, height - 2, Tile::UP, Tile::LEFT, &this->evilshoots);
  this->enemies[3] = new Enemy(width - 2, height - 1, Tile::LEFT, Tile::UP, &this->evilshoots);
  this->my_map->fillTile(0, 1, Tile::EVIL_DUDE, Tile::DOWN);
  this->my_map->fillTile(1, 0, Tile::EVIL_DUDE, Tile::RIGHT);
  this->my_map->fillTile(height - 1, width - 2, Tile::EVIL_DUDE, Tile::UP);
  this->my_map->fillTile(height - 2, width - 1, Tile::EVIL_DUDE, Tile::LEFT);
  this->makeJesusSpawnRessources(difficulty = 20);
  this->scoreClass->loadScoreFile("./scores/solarfox.score");
  this->status->pseudo = pseudo;
  this->status->score = 0;
  this->status->is_over = false;
  this->status->coeff = 0;
  this->status->camera_coeff = 0;
  this->status->who_won = 0;
  this->lastTick = 0;
  this->key = EVENT_FORWARD;
  this->speed = 80000;
  this->position.a = width / 2;
  this->position.b = height / 2;
  this->my_map->fillTile(height / 2, width / 2, Tile::HEAD, Tile::RIGHT);
}

Score	*Solarfox::getScore() const
{
  return (this->scoreClass);
}

extern "C"
{
  IGames	*create_instance()
  {
    return (new Solarfox());
  }
}

Map	*Solarfox::getMap() const
{
  return (this->my_map);
}

void	Solarfox::update_enemies()
{
  this->enemies[0]->update(this->my_map);
  this->enemies[1]->update(this->my_map);
  this->enemies[2]->update(this->my_map);
  this->enemies[3]->update(this->my_map);
}

void			Solarfox::update_evilshoots()
{
  std::list<t_shoot>::iterator	counter = this->evilshoots.begin();
  std::list<t_shoot>::iterator	last = this->evilshoots.end();

  while (counter != last)
    {
      this->my_map->fillTile(counter->y, counter->x, Tile::EMPTY, counter->orientation);
      if ((counter->orientation == Tile::UP && counter->y == 1)
	  || (counter->orientation == Tile::DOWN && counter->y == this->my_map->getHeight() - 2)
	  || (counter->orientation == Tile::LEFT && counter->x == 1)
	  || (counter->orientation == Tile::RIGHT && counter->x == this->my_map->getWidth() - 2))
	counter = this->evilshoots.erase(counter);
      else
	{
	  if (counter->orientation == Tile::LEFT
	      && (this->my_map->getTileType(counter->y, counter->x - 1) != Tile::HEAD))
	    counter->x -= 1;
	  else if (counter->orientation == Tile::RIGHT
		   && (this->my_map->getTileType(counter->y, counter->x + 1) != Tile::HEAD))
	    counter->x += 1;
	  else if (counter->orientation == Tile::UP
		   && (this->my_map->getTileType(counter->y - 1, counter->x) != Tile::HEAD))
	    counter->y -= 1;
	  else if (counter->orientation == Tile::DOWN
		   && (this->my_map->getTileType(counter->y + 1, counter->x) != Tile::HEAD))
	    counter->y += 1;
	  else
	    this->setDeath();
	  this->my_map->fillTile(counter->y, counter->x, Tile::EVIL_SHOOT, counter->orientation);
	  counter++;
	}
    }
}

void		Solarfox::addShoot()
{
  t_shoot	to_add;
  Tile::Direction	dir = this->my_map->getTileDir(this->position.b, this->position.a);
  int		add_x = 0;
  int		add_y = 0;

  if (dir == Tile::UP)
    add_y -= 1;
  else if (dir == Tile::DOWN)
    add_y += 1;
  else if (dir == Tile::LEFT)
    add_x -= 1;
  else
    add_x += 1;
  to_add.x = this->position.a + add_x;
  to_add.y = this->position.b + add_y;
  to_add.nbr_max = 4;
  to_add.orientation = dir;
  this->shoots.push_back(to_add);
  this->key = EVENT_FORWARD;
}

void	Solarfox::killEvilShoot(int col, int line)
{
  std::list<t_shoot>::iterator	counter = this->evilshoots.begin();
  std::list<t_shoot>::iterator	last = this->evilshoots.end();

  while (counter != last)
    {
      if (counter->x == col && counter->y == line)
	{
	  this->evilshoots.erase(counter);
	  return;
	}
      counter++;
    }
}

void	Solarfox::manage_destructive_shoots(int pos_x, int pos_y, Tile::Type type)
{
  if (type == Tile::RESSOURCE)
    {
      this->status->score += 10;
      killRessources(pos_x, pos_y);
    }
  else if (type == Tile::EVIL_SHOOT)
    {
      this->status->score += 20;
      killEvilShoot(pos_x, pos_y);
    }
}

void	Solarfox::controlShoots()
{
  std::list<t_shoot>::iterator	counter = this->shoots.begin();
  std::list<t_shoot>::iterator	last = this->shoots.end();

  while (counter != last)
    {
      if (counter->nbr_max <= 0 || counter-> x <= 1 || counter->y <= 1
	  || counter->x >= this->my_map->getWidth() - 2 || counter->y >= this->my_map->getHeight() - 2)
	{
	  this->my_map->fillTile(counter->y, counter->x, Tile::EMPTY, Tile::NONE);
	  this->shoots.erase(counter);
	  this->controlShoots();
	  return ;
	}
      counter++;
    }
}

void		Solarfox::update_my_shoots()
{
  std::list<t_shoot>::iterator	counter = this->shoots.begin();
  std::list<t_shoot>::iterator	last = this->shoots.end();
  int				add_x = 0;
  int				add_y = 0;

  if (this->key == EVENT_SHOOT)
    addShoot();
  this->controlShoots();
  counter = this->shoots.begin();
  last = this->shoots.end();
  while (counter != last)
    {
      if (counter->nbr_max <= 3)
	{
	  if (counter->orientation == Tile::UP)
	    add_y -= 1;
	  else if (counter->orientation == Tile::DOWN)
	    add_y += 1;
	  else if (counter->orientation == Tile::LEFT)
	    add_x -= 1;
	  else
	    add_x += 1;
	  this->my_map->fillTile(counter->y, counter->x, Tile::EMPTY, Tile::NONE);
	}
      this->manage_destructive_shoots(counter->x + add_x, counter->y + add_y,
				      this->my_map->getTileType(counter->y + add_y, counter->x + add_x));
      this->my_map->fillTile(counter->y + add_y, counter->x + add_x,
			     Tile::MY_SHOOT, counter->orientation);
      counter->x += add_x;
      counter->y += add_y;
      counter->nbr_max--;
      counter++;
    }
}

std::map<Tile::Type, std::string>	*Solarfox::getSprites() const
{
  std::map<Tile::Type, std::string>	*sprites = new std::map<Tile::Type, std::string>;

  (*sprites)[Tile::Type::HEAD] = "media/my_space.png";
  (*sprites)[Tile::Type::RESSOURCE] = "media/boule.png";
  (*sprites)[Tile::Type::BLOCK] = "media/glass_texture.jpg";
  (*sprites)[Tile::Type::EVIL_DUDE] = "media/cannon_sprite.png";
  (*sprites)[Tile::Type::EVIL_SHOOT] = "media/friendly_fire.png";
  (*sprites)[Tile::Type::MY_SHOOT] = "media/test_shoot.png";
  return (sprites);
}

void		Solarfox::update_player()
{
  if (this->key <= EVENT_FORWARD && this->status->is_over == false)
    movePlayer();
}

void	Solarfox::setDeath()
{
  this->status->who_won = 0;
  this->scoreClass->saveScore(this->status->pseudo, this->status->score);
  this->status->is_over = true;
}

void	Solarfox::movePlayer()
{
  int	add_col = 0;
  int	add_line = 0;

  findMovement(this->getDirection(), add_line, add_col);
  if (add_line == 0 && add_col == 0)
    setDeath();
  else
    {
      this->my_map->fillTile(this->position.b + add_line, this->position.a + add_col,
			     Tile::HEAD, this->getDirection());
      this->my_map->fillTile(this->position.b, this->position.a, Tile::EMPTY, Tile::NONE);
      this->position.a += add_col;
      this->position.b += add_line;
    }
}

Tile::Direction Solarfox::getDirection() const
{
  Tile::Direction       press_dir;

  if (this->key == EVENT_PRESS_RIGHT)
    press_dir = Tile::RIGHT;
  else if (this->key == EVENT_PRESS_LEFT)
    press_dir = Tile::LEFT;
  else if (this->key == EVENT_PRESS_UP)
    press_dir = Tile::UP;
  else if (this->key == EVENT_PRESS_DOWN)
    press_dir = Tile::DOWN;
  else if (this->key == EVENT_FORWARD)
    press_dir = this->my_map->getTileDir(this->position.b, this->position.a);
  return (press_dir);
}

void	Solarfox::killRessources(int col, int line)
{
  std::list<Tuple<int, int>>::iterator	counter = this->ressources.begin();
  std::list<Tuple<int, int>>::iterator	last = this->ressources.end();

  while (counter != last)
    {
      if (counter->a == col && counter->b == line)
	{
	  ressources.erase(counter);
	  return;
	}
      counter++;
    }
}

void	Solarfox::findMovement(Tile::Direction key, int &add_line, int &add_col)
{
  add_line = 0;
  add_col = 0;
  if (key == Tile::UP)
    add_line = -1;
  else if (key == Tile::DOWN)
    add_line = 1;
  else if (key == Tile::RIGHT)
    add_col = 1;
  else if (key == Tile::LEFT)
    add_col = -1;
  if (add_line == 0 && add_col == 0)
    return;
  if (this->position.b + add_line < this->my_map->getHeight() - 2
      && this->position.a + add_col < this->my_map->getWidth() - 2
      && this->position.b + add_line >= 2 && this->position.a + add_col >= 2)
    if (this->my_map->getTileType(this->position.b + add_line, this->position.a + add_col) == Tile::EMPTY
	|| this->my_map->getTileType(this->position.b + add_line, this->position.a + add_col) == Tile::RESSOURCE)
      return;
  this->setDeath();
}

void	Solarfox::update_ressources()
{
  std::list<Tuple<int, int>>::iterator	counter = this->ressources.begin();
  std::list<Tuple<int, int>>::iterator	last = this->ressources.end();

  while (counter != last)
    {
      if (this->my_map->getTileType(counter->b, counter->a) == Tile::EMPTY)
	this->my_map->fillTile(counter->b, counter->a, Tile::RESSOURCE, Tile::NONE);
      counter++;
    }
}

t_game_status	*Solarfox::update()
{
  struct timeval	tmp;
  int			new_tick;
  int     nb_frame = FPS * ((double)this->speed / SEC_AS_MICROSEC);

  if (this->ressources.size() == 0)
    {
      if (difficulty == 0)
	{
	  this->status->is_over = true;
	  return (this->status);
	}
      makeJesusSpawnRessources(difficulty /= 2);
      this->position.a = this->my_map->getWidth() / 2;
      this->position.b = this->my_map->getHeight() / 2;
    }
  gettimeofday(&tmp, NULL);
  new_tick = tmp.tv_usec;
  if (new_tick < this->lastTick)
    new_tick += 1000000;
  this->update_my_shoots();
  if (new_tick > this->lastTick + this->speed / nb_frame
      && this->key != EVENT_PAUSE && this->status->is_over == false)
    {
      this->status->coeff += 1 / (double)nb_frame;
      this->status->camera_coeff += 1 / (double)nb_frame;
      this->lastTick = tmp.tv_usec;
      if (this->status->coeff > 0.99)
	{
	  this->update_ressources();
	  this->update_my_shoots();
	  this->status->coeff = 0;
	  this->status->camera_coeff = 0;
	  this->update_player();
	  if (this->status->is_over == true)
	    return (this->status);
	  this->update_enemies();
	  this->update_evilshoots();
	  if (this->status->is_over == true)
	    return (this->status);
	  this->setBorder();
	}
    }
  return (this->status);
}

void			Solarfox::applyCommand(e_action key)
{
  Tile::Direction	head_dir;

  if (this->status->is_over == true)
    return;
  if (key == EVENT_PAUSE)
    this->key = (this->key == EVENT_PAUSE) ? EVENT_FORWARD : EVENT_PAUSE;
  if (key == EVENT_PAUSE
      || (key != EVENT_SHOOT && key >= 14))
    return;
  head_dir = this->my_map->getTileDir(this->position.b, this->position.a);
  if ((head_dir != Tile::LEFT && key == EVENT_PRESS_RIGHT) || head_dir != Tile::RIGHT
      || head_dir != Tile::UP || head_dir != Tile::DOWN || key == EVENT_SHOOT)
    this->key = key;
}

const Tuple<int, int>	&Solarfox::getPosition() const
{
  return (this->position);
}
