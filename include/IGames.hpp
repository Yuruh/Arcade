//
// IGames.hpp for azer in /home/yuruh/rendu/cpp_arcade/include/
//
// Made by Antoine Lempereur
// Login   <lemper_a@epitech.eu>
//
// Started on  Tue Mar  8 16:16:13 2016 Antoine Lempereur
// Last update Sun Apr  3 17:21:41 2016 Wasta-Geek
//

#ifndef IGAMES_HPP_
#define IGAMES_HPP_

#include <map>
#include "Tile.hpp"
#include "Map.hpp"
#include "Score.hpp"
#include "Event.hpp"
#include "Protocol.hpp"

typedef struct	s_game_status
{
  bool		is_over;
  int		score;
  double	coeff;
  double camera_coeff;
  int	  	who_won;
  std::string	pseudo;
}		t_game_status;

class   IGames
{
public:
  virtual ~IGames() {};
  virtual Map			*getMap() const = 0;
  virtual void			applyCommand(e_action) = 0;
  virtual void			init(std::string) = 0;
  virtual t_game_status		*update() = 0;
  virtual Score			*getScore() const = 0;
  virtual void			restart() = 0;
  virtual std::map<Tile::Type, std::string>	*getSprites() const = 0;
};

#endif
