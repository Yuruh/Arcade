//
// Core.hpp for azer in /home/yuruh/rendu/cpp_arcade/include/
//
// Made by Antoine Lempereur
// Login   <lemper_a@epitech.eu>
//
// Started on  Tue Mar  8 16:30:01 2016 Antoine Lempereur
// Last update Sun Apr  3 17:45:25 2016 Corentin Descamps
//

#ifndef  CORE_HPP_
# define CORE_HPP_

# include	<vector>
# include	<iostream>
# include	<string>
# include	<map>
# include	"IDisplay.hpp"
# include	"DLLoader.hpp"
# include	"Event.hpp"

class   Core
{
public:
  Core();
  ~Core();
  void  loadGfxLibrary();
  void  loadGameLibrary();
  void  loadFromPath(std::string const& path);
  void  loadNextGfx();
  void  loadPrevGfx();
  void  loadNextGame();
  void  loadPrevGame();
  void  restartGame();
  void  getToMenu();
  void  init(std::string const& path);
  void  run();
  void  notify(e_action event);
  void  notify(e_menu event, std::string const& str);
  void  getPath();
  void  setPlayer(std::string const&);
  std::map<std::string, std::string> getPathMap();

private:
  std::string   playerName;
  DLLoader<IDisplay>  m_gfxdll;
  DLLoader<IGames>  m_gamedll;
  int               m_gameIndex;
  int               m_gfxIndex;
  std::vector<std::string> libraryPath;
  std::vector<std::string> gamesPath;
  std::map<e_action, void (Core::*)(void)> m_changeLib;
  bool          running;
  bool          runMenu;
  bool          runGame;
  bool          changeGame;
  bool          changeGfx;
};

#endif  /* !CORE_HPP_ */
