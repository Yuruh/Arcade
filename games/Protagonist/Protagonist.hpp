//
// Protagonist.hpp for  in /home/wasta-geek/rendu/CPP/cpp_arcade
// 
// Made by ducatez
// Login   <ducate_c@epitech.net>
// 
// Started on  Fri Mar 11 14:09:54 2016 ducatez
// Last update Tue Mar 15 15:51:43 2016 Wasta-Geek
//

#ifndef		PROTAGONIST_HPP_
# define	PROTAGONIST_HPP_

#include	<vector>
#include	"Tile.hpp"
#include	"Tuple.hpp"

class		Protagonist
{
private:
  Tuple<int>		head_position;	
  int			length;
  double		speed;
public:
  Protagonist(int&, int&, int);
  ~Protagonist() {} ;
  Tuple<int>		getHeadPosition() const;
  void			setHeadPostion(int, int);
  int			getLength() const;
  void			setLength(int);
  double		getSpeed() const;
  void			setSpeed(double);
};
  
#endif		/* Protagonist.hpp */
