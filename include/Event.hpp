//
// Event.hpp for arcade in /home/archie/workspace/C++/cpp_arcade/include/
//
// Made by Corentin Descamps
// Login   <descam_d@epitech.eu>
//
// Started on  Mon Mar 14 13:34:09 2016 Corentin Descamps
// Last update Sun Apr  3 17:33:06 2016 Corentin Descamps
//

#ifndef   EVENT_HPP_
# define  EVENT_HPP_

enum e_display
{
  EVENT_LOAD_SFML,
  EVENT_LOAD_CACA,
  EVENT_LOAD_OGRE
};

enum e_games
{
  EVENT_LOAD_SNAKE,
  EVENT_LOAD_QIX
};

enum e_menu
{
  EVENT_CHANGE_GAME,
  EVENT_CHANGE_DISP,
  EVENT_EXIT_MENU
};

enum e_action
{
  EVENT_PRESS_UP = 0,
  EVENT_PRESS_DOWN = 1,
  EVENT_PRESS_LEFT = 2,
  EVENT_PRESS_RIGHT = 3,
  EVENT_FORWARD = 4,
  EVENT_PRESS_SPACE = 5,
  EVENT_PREV_DISP = 6,
  EVENT_NEXT_DISP = 7,
  EVENT_PREV_GAME = 8,
  EVENT_NEXT_GAME = 9,
  EVENT_RESTART = 10,
  EVENT_MENU = 11,
  EVENT_PAUSE = 12,
  EVENT_EXIT = 13,
  EVENT_ADD_PLAYER = 14,
  EVENT_P2_UP = 15,
  EVENT_P2_DOWN = 16,
  EVENT_P2_LEFT = 17,
  EVENT_P2_RIGHT = 18,
  EVENT_SHOOT = 19
};

#endif    /* !EVENT_HPP_ */
