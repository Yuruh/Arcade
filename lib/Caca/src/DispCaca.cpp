//
// DispCaca.cpp for  in /home/yuruh/rendu/cpp_arcade/lib/Caca/
//
// Made by Antoine Lempereur
// Login   <lemper_a@epitech.eu>
//
// Started on  Fri Mar 11 14:14:30 2016 Antoine Lempereur
// Last update Sun Apr  3 20:48:40 2016 Antoine Lempereur
//

#include "DispCaca.hpp"
#include "ModuleCaca.hpp"

DispCaca::DispCaca() : ADisplay(), display(NULL)
{
  this->textures[Tile::Type::EMPTY] = CACA_BLACK;
  this->textures[Tile::Type::HEAD] = CACA_LIGHTGREEN;
  this->textures[Tile::Type::BODY] = CACA_GREEN;
  this->textures[Tile::Type::TAIL] = CACA_GREEN;
  this->textures[Tile::Type::TWISTED_BODY_LEFT] = CACA_GREEN;
  this->textures[Tile::Type::TWISTED_BODY_RIGHT] = CACA_GREEN;
  this->textures[Tile::Type::RESSOURCE] = CACA_RED;
  this->textures[Tile::Type::MY_SHOOT] = CACA_LIGHTBLUE;
  this->textures[Tile::Type::EVIL_SHOOT] = CACA_BLUE;
  this->textures[Tile::Type::BLOCK] = CACA_CYAN;
  this->textures[Tile::Type::EVIL_DUDE] = CACA_WHITE;

  this->playerName = "player";
  this->setKeyMap();
  this->canvas = caca_create_canvas(500, 62);
}

DispCaca::~DispCaca()
{
  if (this->display)
    caca_free_display(this->display);
  if (this->canvas)
    caca_free_canvas(this->canvas);
  this->display = NULL;
  this->canvas = NULL;
}

void  DispCaca::drawMenu(std::map<std::string, std::string> modules)
{
  caca_event_t    event;
  int             keycode;
  int             y = 14;

  if (!this->display)
  {
    for (auto it = modules.begin(); it != modules.end(); it++) {
      if (it->second.substr(0, 7) == "./games")
        this->menu.addModule(new ModuleCaca(20, y, EVENT_CHANGE_GAME, it->second, it->first, canvas));
      else if (it->second.substr(0, 5) == "./lib")
        this->menu.addModule(new ModuleCaca(20, y, EVENT_CHANGE_DISP, it->second, it->first, canvas));
      y += 2;
    }
    this->display = caca_create_display(this->canvas);
    caca_set_display_title(this->display, "Arcade");
  }
  caca_refresh_display(this->display);
  caca_clear_canvas(this->canvas);
  this->menu.display();
  caca_put_str(this->canvas, 34, 12, this->playerName.c_str());
  caca_get_event(this->display, CACA_EVENT_ANY, &event, -1);
  if (caca_get_event_type(&event) & CACA_EVENT_KEY_PRESS)
  {
    keycode = caca_get_event_key_ch(&event);
    if (keycode == CACA_KEY_ESCAPE)
      this->core->notify(EVENT_EXIT_MENU, "");
    if (keycode == CACA_KEY_DOWN)
      this->menu.selectNext();
    else if (keycode == CACA_KEY_UP)
      this->menu.selectPrev();
    else if (keycode == CACA_KEY_RETURN)
      this->core->notify(this->menu.getSelected()->getType(), this->menu.getSelected()->getPath());
    else if (keycode == 8)
      this->playerName = this->playerName.substr(0, this->playerName.size() - 1);
    else if (this->playerName.size() <= 10 && ((keycode >= 'a' && keycode <= 'z') || (keycode >= 'A' && keycode <= 'Z') || keycode == ' '))
    {
      if (this->playerName == "player")
        this->playerName = "";
      this->playerName += keycode;
    }
  }
}


extern "C"
{
  IDisplay  *create_instance()
  {
    return (new DispCaca());
  }
}

void  DispCaca::setKeyMap()
{
  this->keyMap[CACA_KEY_UP] = EVENT_PRESS_UP;
  this->keyMap[CACA_KEY_DOWN] = EVENT_PRESS_DOWN;
  this->keyMap[CACA_KEY_LEFT] = EVENT_PRESS_LEFT;
  this->keyMap[CACA_KEY_RIGHT] = EVENT_PRESS_RIGHT;
  this->keyMap[CACA_KEY_ESCAPE] = EVENT_EXIT;
  this->keyMap[CACA_SPACE] = EVENT_PAUSE;
  this->keyMap[CACA_NUM2] = EVENT_PREV_DISP;
  this->keyMap[CACA_NUM3] = EVENT_NEXT_DISP;
  this->keyMap[CACA_NUM4] = EVENT_PREV_GAME;
  this->keyMap[CACA_NUM5] = EVENT_NEXT_GAME;
  this->keyMap[CACA_NUM8] = EVENT_RESTART;
  this->keyMap[CACA_NUM9] = EVENT_MENU;
  this->keyMap[CACA_F] = EVENT_SHOOT;
}

void  DispCaca::interpretKey(int keycode)
{
  if (this->keyMap.find(keycode) != this->keyMap.end())
    this->core->notify(this->keyMap[keycode]);
}

void  DispCaca::drawEndScreen()
{
   for (size_t i = 0; i < this->score->getScores().size() && i < 10; i++) {
     caca_set_color_ansi(this->canvas, CACA_WHITE, CACA_BLACK);
     caca_put_str(this->canvas, 40, 10 + i * 4, (this->score->getScores()[i].a + "   " + std::to_string(this->score->getScores()[i].b)).c_str());
   }
 }

void  DispCaca::drawMap()
{
  caca_event_t    event;

  if (!this->canvas)
    this->canvas = caca_create_canvas(500, 62);
  if (!this->display)
  {
    this->display = caca_create_display(this->canvas);
    caca_set_display_title(this->display, "Arcade");
  }
  if (!this->status->is_over)
  {
    caca_set_color_ansi(this->canvas, CACA_RED, CACA_LIGHTBLUE);
    caca_draw_box(this->canvas, 9, 9, this->map->getWidth() * 2 * 2, this->map->getHeight() * 2 + 1, ' ');
    for (int x = 0; x < this->map->getWidth(); x++)
      for (int y = 0; y < this->map->getHeight(); y++)
      {
        caca_set_color_ansi(this->canvas, CACA_BLACK, this->textures[this->map->getTiles()[y][x].a]);
        caca_draw_box(this->canvas, x * 2 * 2 + 10, (y * 2) + 10, 1 * 2, 1, ' ');
      }
      caca_set_color_ansi(this->canvas, CACA_WHITE, CACA_BLACK);
      caca_put_str(this->canvas, 100, 5, std::to_string(this->status->score).c_str());
  }
  else
    this->drawEndScreen();
  caca_refresh_display(this->display);
  caca_clear_canvas(this->canvas);
  caca_get_event(this->display, CACA_EVENT_KEY_PRESS, &event, 10);
  if (caca_get_event_type(&event) & CACA_EVENT_KEY_PRESS)
    this->interpretKey(caca_get_event_key_ch(&event));
}
