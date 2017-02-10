//
// Core.cpp for toto in /home/descam_d/workspace/C++/cpp_arcade
//
// Made by Corentin Descamps
// Login   <descam_d@epitech.net>
//
// Started on  Wed Mar  9 17:48:15 2016 Corentin Descamps
// Last update Sun Apr  3 21:05:38 2016 Corentin Descamps
//

#include  <dirent.h>
#include	"Core.hpp"

Core::Core()
{
  this->running = true;
  this->changeGame = true;
  this->changeGfx = true;
  this->runMenu = true;
  this->runGame = false;
  this->m_gfxIndex = 0;
  this->m_gameIndex = 0;
  this->m_changeLib[EVENT_NEXT_DISP] = &Core::loadNextGfx;
  this->m_changeLib[EVENT_PREV_DISP] = &Core::loadPrevGfx;
  this->m_changeLib[EVENT_NEXT_GAME] = &Core::loadNextGame;
  this->m_changeLib[EVENT_PREV_GAME] = &Core::loadPrevGame;
  this->m_changeLib[EVENT_RESTART] = &Core::restartGame;
  this->m_changeLib[EVENT_MENU] = &Core::getToMenu;
  this->playerName = "player";
}

Core::~Core()
{

}

void    Core::setPlayer(std::string const& name)
{
  this->playerName = name;
}


void    Core::loadFromPath(std::string const& path)
{
  std::vector<std::string>::iterator it;
  int index = 0;

  for (it = this->libraryPath.begin(); it != this->libraryPath.end(); it++)
  {
    if ((*it) == path)
    {
      this->m_gfxIndex = index;
      // this->loadGfxLibrary();
    return;
    }
    index++;
  }
  throw CoreError("Can't find library : " + path);
}

void    Core::loadGfxLibrary()
{
  try {
    this->m_gfxdll.close();
    this->m_gfxdll.open(this->libraryPath[this->m_gfxIndex]);
    this->changeGfx = false;
  } catch (CoreError& e) {
    std::cerr << e.what() << std::endl;
  }
}

void    Core::loadGameLibrary()
{
  try {
    this->m_gamedll.close();
    this->m_gamedll.open(this->gamesPath[this->m_gameIndex]);
    this->changeGame = false;
  } catch (CoreError& e) {
    std::cerr << e.what() << std::endl;
  }
}

void    Core::init(std::string const& path)
{
  this->loadFromPath(path);
}

void	Core::run()
{
  Map	*map;

  this->running = true;
  this->runMenu = true;
  this->runGame = false;
  while (this->running)
    {
      if (this->runMenu)
      {
        this->m_gfxdll.close();
        this->m_gfxdll.open(this->libraryPath[this->m_gfxIndex]);
        this->m_gfxdll.getInstance()->init(NULL, this, NULL, NULL);
        while (this->runMenu)
          this->m_gfxdll.getInstance()->drawMenu(this->getPathMap());
        if (this->running && this->gamesPath.size() > 0)
          this->runGame = true;
      }
      if (this->runGame)
      {
        this->loadGfxLibrary();
        this->loadGameLibrary();
        this->m_gamedll.getInstance()->init(this->playerName);
        map = this->m_gamedll.getInstance()->getMap();
        this->m_gfxdll.getInstance()->init(map, this, this->m_gamedll.getInstance()->getScore(), this->m_gamedll.getInstance()->getSprites());
        while (this->runGame)
        {
          if (this->changeGfx)
          {
            this->loadGfxLibrary();
            map = this->m_gamedll.getInstance()->getMap();
            this->m_gfxdll.getInstance()->init(map, this, this->m_gamedll.getInstance()->getScore(), this->m_gamedll.getInstance()->getSprites());
          }
          if (this->changeGame)
          {
	          this->loadGameLibrary();
	          this->m_gamedll.getInstance()->init(this->playerName);
	           map = this->m_gamedll.getInstance()->getMap();
	          this->m_gfxdll.getInstance()->init(map, this, this->m_gamedll.getInstance()->getScore(), this->m_gamedll.getInstance()->getSprites());
	        }
        this->m_gfxdll.getInstance()->update(this->m_gamedll.getInstance()->update());
      }
    }
  }
}

void    Core::loadNextGfx()
{
  this->changeGfx = true;
  this->m_gfxIndex = (this->m_gfxIndex + 1) % this->libraryPath.size();
}

void    Core::loadPrevGfx()
{
  this->changeGfx = true;
  if (this->m_gfxIndex == 0)
    this->m_gfxIndex = this->libraryPath.size() - 1;
  else
    this->m_gfxIndex -= 1;
}

void    Core::loadNextGame()
{
  this->changeGame = true;
  this->m_gameIndex = (this->m_gameIndex + 1) % this->gamesPath.size();
}

void    Core::loadPrevGame()
{
  this->changeGame = true;
  if (this->m_gameIndex == 0)
    this->m_gameIndex = this->gamesPath.size() - 1;
  else
    this->m_gameIndex -= 1;
}

void    Core::restartGame()
{
  Map*  map;

  this->m_gamedll.getInstance()->restart();
  map = this->m_gamedll.getInstance()->getMap();
  this->m_gfxdll.getInstance()->init(map, this, this->m_gamedll.getInstance()->getScore(), this->m_gamedll.getInstance()->getSprites());
}

void    Core::getToMenu()
{
  this->runGame = false;
  this->runMenu = true;
}

void    Core::notify(e_action event)
{
  this->m_gamedll.getInstance()->applyCommand(event);
  if (this->m_changeLib.find(event) != this->m_changeLib.end())
   (this->*m_changeLib[event])();
  if (event == EVENT_EXIT)
  {
   this->running = false;
   this->runMenu = false;
   this->runGame = false;
  }
}

void    Core::notify(e_menu event, std::string const& str)
{
  if (event == EVENT_CHANGE_GAME)
  {
    int pos = std::find(this->gamesPath.begin(), this->gamesPath.end(), str) - this->gamesPath.begin();
    this->m_gameIndex = pos;
    this->runMenu = false;
  }
  else if (event == EVENT_CHANGE_DISP)
  {
    int pos = std::find(this->libraryPath.begin(), this->libraryPath.end(), str) - this->libraryPath.begin();
    this->m_gfxIndex = pos;
  }
  else if (event == EVENT_EXIT_MENU)
  {
    this->running = false;
    this->runMenu = false;
    this->runGame = false;
  }
}

std::map<std::string, std::string> Core::getPathMap()
{
  std::map<std::string, std::string> ret;
  std::string name;

  for (auto it = this->libraryPath.begin(); it != this->libraryPath.end(); it++)
  {
    name = (*it).substr((*it).find("lib_arcade_") + 11);
    name = name.substr(0, name.find(".so"));
    ret[name] = (*it);
  }
  for (auto it = this->gamesPath.begin(); it != this->gamesPath.end(); it++)
  {
    name = (*it).substr((*it).find("lib_arcade_") + 11);
    name = name.substr(0, name.find(".so"));
    ret[name] = (*it);
  }
  return (ret);
}

void    Core::getPath()
{
  DIR *dir;
  struct dirent *ent;
  if ((dir = opendir ("./lib")) != NULL)
  {
    /* print all the files and directories within directory */
    while ((ent = readdir (dir)) != NULL)
    {
      std::string filename = std::string(ent->d_name);

      if (filename.find(".so") != std::string::npos)
        this->libraryPath.push_back("./lib/" + filename);
    }
    closedir (dir);
  }
  else
    throw CoreError("Couldn't open directory : ./lib");

  if ((dir = opendir ("./games")) != NULL)
  {
    /* print all the files and directories within directory */
    while ((ent = readdir (dir)) != NULL)
    {
      std::string filename = std::string(ent->d_name);
      if (filename.find(".so") != std::string::npos)
        this->gamesPath.push_back("./games/" + filename);
    }
    closedir (dir);
  }
  else
    throw CoreError("Couldn't open directory : ./games");
}
