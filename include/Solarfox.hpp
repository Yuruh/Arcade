//
// Solarfox.hpp for  in /home/wasta-geek/rendu/CPP/cpp_arcade
// 
// Made by Wasta-Geek
// Login   <ducate_c@epitech.net>
// 
// Started on  Wed Mar 30 13:27:57 2016 Wasta-Geek
// Last update Sun Apr  3 17:30:51 2016 Wasta-Geek
//

#ifndef		SOLARFOX_HPP_
# define	SOLARFOX_HPP_

#include	<list>
#include	"Enemy.hpp"
#include	"IGames.hpp"
#include	"Tile.hpp"

class	Solarfox : public IGames
{
  Map			*my_map;
  Tuple<int, int>	position;
  int			lastTick;
  e_action		key;
  int			speed;
  t_game_status		*status;
  Score			*scoreClass;
  Enemy			*enemies[4];
  std::list<t_shoot>	evilshoots;
  std::list<t_shoot>	shoots;
  std::list<Tuple<int, int>>	ressources;
  int			difficulty;
  
private:
  void	controlShoots();
  void	killEvilShoot(int, int);
  void	manage_destructive_shoots(int, int, Tile::Type);
  void	findMovement(Tile::Direction, int&, int&);
  void	movePlayer();
  Tile::Direction	getDirection() const;
  void	setBorder();
  void	makeJesusSpawnRessources(int);
  void	fillLineRessources(Map*, int, int);
  void	setDeath();
  void	killRessources(int, int);
public:
  void	addShoot();
  void	update_enemies();
  void	update_evilshoots();
  void	update_player();
  void	update_ressources();
  void	update_my_shoots();
  Solarfox();
  const Tuple<int, int>	&getPosition() const;
  virtual ~Solarfox();
  virtual Map   *getMap() const;
  virtual void  applyCommand(e_action);
  virtual void  init(std::string);
  virtual t_game_status  *update();
  virtual Score *getScore() const;
  virtual void	restart();
  virtual std::map<Tile::Type, std::string>	*getSprites() const;
};

#endif		/* Solarfox.hpp */
