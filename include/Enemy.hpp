//
// Enemy.hpp for  in /home/wasta-geek/rendu/CPP/cpp_arcade
// 
// Made by Wasta-Geek
// Login   <ducate_c@epitech.net>
// 
// Started on  Wed Mar 30 15:22:03 2016 Wasta-Geek
// Last update Sat Apr  2 22:33:41 2016 Wasta-Geek
//

#ifndef		ENEMY_HPP_
# define	ENEMY_HPP_

#include	<list>
#include	"Map.hpp"
#include	"Tuple.hpp"
#include	"Tile.hpp"

typedef struct          s_shoot
{
  int                   x;
  int                   y;
  Tile::Direction       orientation;
  int			nbr_max;
}                       t_shoot;

class			Enemy
{
  int			percent_shoot;
  Tuple<int, int>	position;
  Tile::Direction	key;
  Tile::Direction	orientation;
  std::list<t_shoot>	*shoots;
public:
  Enemy(int, int, Tile::Direction, Tile::Direction, std::list<t_shoot>*);
  ~Enemy();
  void	update(Map*);
  void	findMove(Map*);
  void	addShoot(int, int, Tile::Direction);
};

#endif		/* Enemy.hpp */
