//
// DispSfml.cpp for  in /home/yuruh/rendu/cpp_arcade/lib/
//
// Made by Antoine Lempereur
// Login   <lemper_a@epitech.eu>
//
// Started on  Tue Mar  8 18:23:41 2016 Antoine Lempereur
// Last update Sun Apr  3 20:54:56 2016 Antoine Lempereur
//

#include "DispSfml.hpp"
#include "Event.hpp"
#include "ModuleSfml.hpp"

DispSfml::DispSfml() : ADisplay(), media(1920, 1080), window(NULL)
{
  this->lastTick = 0;
  this->setKeyMap();
}

DispSfml::~DispSfml()
{
  if (this->window)
  {
    this->window->close();
    delete this->window;
  }
}

void  DispSfml::init(Map *map, Core *core, Score *score, std::map<Tile::Type, std::string> *text_path)
{
  this->map = map;
  this->core = core;
  this->score = score;
  if (map != NULL)
    this->media.setMapDim(map->getWidth(), map->getHeight());
  else
    this->media.setMapDim(40, 20);

  if (text_path != NULL)
  {
    std::map<Tile::Type, std::string>::iterator it = text_path->begin();

    while (it != text_path->end())
    {
      this->media.addTileTexture(it->second, it->first);
      it++;
    }
  }
  this->media.addBdTexture("media/arcade_panorama_flou.png", "background");
  this->media.addBdTexture("media/wood_texture.png", "wood");
}

extern "C"
{
  IDisplay  *create_instance()
  {
    return (new DispSfml());
  }
}

void  DispSfml::setKeyMap()
{
  this->keyMap[sf::Keyboard::Up] = EVENT_PRESS_UP;
  this->keyMap[sf::Keyboard::Down] = EVENT_PRESS_DOWN;
  this->keyMap[sf::Keyboard::Left] = EVENT_PRESS_LEFT;
  this->keyMap[sf::Keyboard::Right] = EVENT_PRESS_RIGHT;
  this->keyMap[sf::Keyboard::Escape] = EVENT_EXIT;
  this->keyMap[sf::Keyboard::Space] = EVENT_PAUSE;
  this->keyMap[sf::Keyboard::Num2] = EVENT_PREV_DISP;
  this->keyMap[sf::Keyboard::Num3] = EVENT_NEXT_DISP;
  this->keyMap[sf::Keyboard::Num4] = EVENT_PREV_GAME;
  this->keyMap[sf::Keyboard::Num5] = EVENT_NEXT_GAME;
  this->keyMap[sf::Keyboard::Num8] = EVENT_RESTART;
  this->keyMap[sf::Keyboard::Num9] = EVENT_MENU;
  this->keyMap[sf::Keyboard::P] = EVENT_ADD_PLAYER;
  this->keyMap[sf::Keyboard::F] = EVENT_SHOOT;
}

void  DispSfml::interpretKey(int keycode)
{
  if (this->keyMap.find(keycode) != this->keyMap.end())
    this->core->notify(this->keyMap[keycode]);
}

void  DispSfml::drawBackground()
{
  this->window->draw(this->media.getSprite("background", 0, 0));
  this->window->draw(this->media.getMapRectangle());
  this->window->draw(this->media.getMapSprite("wood"));
  this->window->draw(this->media.getTitle("arcade         SFML"));
}

void  DispSfml::drawMenu(std::map<std::string, std::string> modules)
{
  sf::Event event;
  int ylib = 250;
  int ygames = 350;

  if (!this->window)
  {
    this->window = new sf::RenderWindow(sf::VideoMode(1920, 1080), "Arcade Launcher");

    for (auto it = modules.begin(); it != modules.end(); it++) {
      if (it->second.substr(0, 7) == "./games")
      {
        this->menu.addModule(new ModuleSfml(1100, ygames, EVENT_CHANGE_GAME, it->second, it->first, this->window));
        ygames += 200;
      }
      else if (it->second.substr(0, 5) == "./lib")
      {
        this->menu.addModule(new ModuleSfml(600, ylib, EVENT_CHANGE_DISP, it->second, it->first, this->window));
        ylib += 200;
      }
    }
  }
  if (this->window->isOpen())
    {
      while (this->window->pollEvent(event))
      {
        if (event.type == sf::Event::Closed || (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape))
          this->core->notify(EVENT_EXIT_MENU, "");
        if (event.type == sf::Event::KeyPressed)
        {
          if (event.key.code == sf::Keyboard::Down)
            this->menu.selectNext();
          if (event.key.code == sf::Keyboard::Up)
            this->menu.selectPrev();
          if (event.key.code == sf::Keyboard::Return)
            this->core->notify(this->menu.getSelected()->getType(), this->menu.getSelected()->getPath());
        }
        if (event.type == sf::Event::TextEntered)
        {
          this->media.interpretTextInput(static_cast<char>(event.text.unicode));
          this->core->setPlayer(this->media.getPlayerName());
        }
      }
      this->window->clear();
      this->drawBackground();
      this->window->draw(this->media.getPlayer());
      this->menu.display();
      this->window->display();
    }
}


void  DispSfml::handleEvents()
{
  sf::Event event;
  while (this->window->pollEvent(event))
  {
    if (event.type == sf::Event::KeyPressed)
      this->interpretKey(event.key.code);
    if (event.type == sf::Event::JoystickButtonPressed)
      {
        if (sf::Joystick::isButtonPressed(1, 0))
          this->core->notify(EVENT_PRESS_DOWN);
        if (sf::Joystick::isButtonPressed(1, 1))
          this->core->notify(EVENT_PRESS_RIGHT);
        if (sf::Joystick::isButtonPressed(1, 2))
          this->core->notify(EVENT_PRESS_LEFT);
        if (sf::Joystick::isButtonPressed(1, 3))
          this->core->notify(EVENT_PRESS_UP);
        if (sf::Joystick::isButtonPressed(2, 0))
          this->core->notify(EVENT_P2_DOWN);
        if (sf::Joystick::isButtonPressed(2, 1))
          this->core->notify(EVENT_P2_RIGHT);
        if (sf::Joystick::isButtonPressed(2, 2))
          this->core->notify(EVENT_P2_LEFT);
        if (sf::Joystick::isButtonPressed(2, 3))
          this->core->notify(EVENT_P2_UP);
        if (sf::Joystick::isButtonPressed(1, 6))
          this->core->notify(EVENT_PAUSE);
        if (sf::Joystick::isButtonPressed(1, 7))
          this->core->notify(EVENT_RESTART);
        if (sf::Joystick::isButtonPressed(1, 4) || sf::Joystick::isButtonPressed(1, 5))
          this->core->notify(EVENT_SHOOT);
      }
  }
}

void  DispSfml::drawEndScreen()
{
  if (this->status->who_won == 0)
  {
    this->window->draw(this->media.getHighScoreRectangle());
    for (size_t i = 0; i < this->score->getScores().size() && i < 10; i++) {
     this->window->draw(this->media.getHighScore(this->score->getScores()[i], i));
   }
  }
  else
   this->window->draw(this->media.getWinner(this->status->who_won));
}

void   DispSfml::drawMap()
{
  if (!this->window)
    this->window = new sf::RenderWindow(sf::VideoMode(1920, 1080), "Arcade");
  if (this->window && this->window->isOpen())
    {
      this->window->clear();
      this->drawBackground();
      if (this->status->is_over)
        this->drawEndScreen();
      else
      {
        this->window->draw(this->media.getScore(std::to_string(this->status->score)));
        for (int x = 0; x < this->map->getWidth(); x++)
          for (int y = 0; y < this->map->getHeight(); y++)
            if (this->media.hasSprite(this->map->getTiles()[y][x].a))
              this->window->draw(this->media.getSprite(this->map->getTiles()[y][x], x, y, this->status->coeff));
      }
      this->window->display();
      this->handleEvents();
    }
}
