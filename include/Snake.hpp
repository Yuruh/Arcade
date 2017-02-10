//
// Snake.hpp for  in /home/wasta-geek/rendu/CPP/cpp_arcade/games
//
// Made by Wasta-Geek
// Login   <ducate_c@epitech.net>
//
// Started on  Tue Mar 15 14:49:12 2016 Wasta-Geek
// Last update Sun Apr  3 18:46:05 2016 Antoine Lempereur
//

#ifndef		SNAKE_HPP_
# define	SNAKE_HPP_

#include	<vector>
#include	"Tile.hpp"
#include	"IGames.hpp"
#include	<sys/time.h>

#define   FPS     60
#define   SEC_AS_MICROSEC 1000000
#define   SIZE_SNAKE_2P   40
#define   SNAKE_SPEED_1P   50000

class	Snake	: public IGames
{
private:
  bool		have_apple;
  Map		*my_map;
  std::vector<std::vector<Tuple<int, int>>>	positions;
  int		   lastTick;
  std::vector<e_action> key;
  int		speed;
  t_game_status	*status;
  Score		*scoreClass;

  void	moveHead(Tile::Direction, int&, int&, unsigned int&);
  void	randomApple();
  void	findMovement(int&, int&, Tile::Direction&, int&, int&);
  void	growUp(unsigned int&);
  void	setTwisted(Tile::Direction&, int&, int&, Tile::Direction&, unsigned int&);
  void	setTailDir(int&, int&, int&, unsigned int&);
  void	eventEatApple(unsigned int&);
  void	setMultiplayer();
  void	createSnake(int, int);
  Tile::Direction	getDirection(e_action, int, int) const;
public:
  Snake();
  virtual ~Snake();
  virtual Map	*getMap() const;
  virtual void	applyCommand(e_action);
  virtual void	init(std::string);
  virtual t_game_status  *update();
  virtual Score *getScore() const;
  virtual void	restart();
  virtual std::map<Tile::Type, std::string>	*getSprites() const;
  std::vector<Tuple<int, int>>	getVector() const;
  void  interpretCommand();
};

#endif		/* Snake.hpp */
