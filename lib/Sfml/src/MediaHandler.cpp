//
// MediaHandler.cpp for  in /home/yuruh/rendu/cpp_arcade/lib/
//
// Made by Antoine Lempereur
// Login   <lemper_a@epitech.eu>
//
// Started on  Wed Mar  9 15:36:20 2016 Antoine Lempereur
// Last update Sun Apr  3 20:21:02 2016 Antoine Lempereur
//

#include "MediaHandler.hpp"
#include <X11/Xlib.h>

MediaHandler::MediaHandler(int width, int height)
{
  Display       *m_disp;

  if (!(m_disp = XOpenDisplay(NULL)))
  {
    std::cout << "The DISPLAY environment variable is not set correctly" << std::endl;
    throw std::exception();
  }
  XCloseDisplay(m_disp);

  this->dim_window.a = width;
  this->dim_window.b = height;
  this->player = "player";
  this->font = new sf::Font();
  this->font->loadFromFile("media/Blox2.ttf");
}

void    MediaHandler::interpretTextInput(char c)
{
  if (((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') || c == ' ') && this->player.size() <= 10)
  {
    if (this->player == "player")
      this->player = "";
    this->player += c;
  }
  else if (c == 8)
    this->player = this->player.substr(0, this->player.size() - 1);
}

void    MediaHandler::setMapDim(int width, int height)
{
  this->dim_map.a = width;
  this->dim_map.b = height;

  int small_win = this->dim_window.a > this->dim_window.b ? this->dim_window.b : this->dim_window.a;
  int big_map = this->dim_map.a < this->dim_map.b ? this->dim_map.b : this->dim_map.a;

  this->square = small_win * 1.2 / big_map;
  this->pos_map.a = this->dim_window.a / 2 - this->square * width / 2;
  this->pos_map.b = this->dim_window.b / 2 - this->square * height / 2;

}

void    MediaHandler::addBdTexture(std::string const& path, std::string const& key)
{
  sf::Texture text;
  sf::Sprite  sprite;

  if (text.loadFromFile(path))
  {
    this->bdText[key] = text;
    sprite.setTexture(this->bdText[key]);
    this->bdSprites[key] = sprite;
  }
}

void    MediaHandler::addTileTexture(std::string const& path, Tile::Type type)
{
  sf::Texture text;
  sf::Sprite  sprite;
  Tuple<double>      scale;
  sf::Vector2u  rect;

  if (text.loadFromFile(path))
  {
    this->tileText[type] = text;
    sprite.setTexture(this->tileText[type]);
    sprite.setOrigin(sf::Vector2f(this->square / 2, this->square / 2));
    rect = this->tileText[type].getSize();
    scale.a = this->square / (double)(rect.x);
    scale.b = this->square / (double)(rect.y);
    sprite.scale(scale.a, scale.b);
    sprite.setOrigin(sf::Vector2f(sprite.getLocalBounds().width / 2, sprite.getLocalBounds().height / 2));
    this->sprites[type] = sprite;
  }
}

sf::Sprite  MediaHandler::getSprite(std::string const& key, int x, int y)
{
  this->bdSprites[key].setPosition(x, y);
  return (this->bdSprites[key]);
}

bool      MediaHandler::hasSprite(Tile::Type type)
{
  return (this->sprites.find(type) != this->sprites.end());
}

sf::Text   MediaHandler::getTitle(std::string const& title)
{
  sf::Text  text;

  text.setString(title);
  text.setColor(sf::Color(237, 162, 0));
  text.setFont(*(this->font));
  text.setCharacterSize(this->dim_window.a / 15);
  text.setPosition(this->dim_window.a / 2 - text.getLocalBounds().width / 2, 20);

  return (text);
}

sf::Text  MediaHandler::getWinner(int winner)
{
  sf::Text  text;

  if (winner != 3)
    text.setString("p" + std::to_string(winner) + " won");
  else
    text.setString("tie");
  text.setColor(sf::Color(200, 0, 0));
  text.setFont(*(this->font));
  text.setCharacterSize(this->dim_window.a / 10);
  text.setPosition(this->pos_map.a - 10 + this->dim_map.a / 3 * this->square, this->pos_map.b + 1 * (this->dim_map.b * this->square / 5) + 10);
  return (text);
}

sf::Text   MediaHandler::getScore(std::string const& score)
{
  sf::Text  text;

  text.setString(score);
  text.setColor(sf::Color(255, 50, 0));
  text.setFont(*(this->font));
  text.setCharacterSize(this->dim_window.a / 15);
  text.setPosition(this->dim_window.a / 2 - text.getLocalBounds().width / 2, this->dim_window.b - 50 - text.getCharacterSize());
  return (text);
}

sf::Text  MediaHandler::getPlayer()
{
  sf::Text  text;

  text.setString(this->player);
  text.setColor(sf::Color(255, 50, 0));
  text.setFont(*(this->font));
  text.setCharacterSize(this->dim_window.a / 15);
  text.setPosition(this->dim_window.a / 2 - text.getLocalBounds().width / 2, this->dim_window.b - 50 - text.getCharacterSize());
  return (text);
}

sf::RectangleShape MediaHandler::getHighScoreRectangle()
{
  sf::RectangleShape rekt;

  rekt.setSize(sf::Vector2f(this->square / 2, this->dim_map.b * this->square + this->square));
  rekt.setPosition(this->pos_map.a + this->dim_map.a * this->square / 2 - this->square, this->pos_map.b - this->square);
  rekt.setFillColor(sf::Color(122, 69, 0));
  return (rekt);
}

sf::Text  MediaHandler::getHighScore(Tuple<std::string, int> hs, int i)
{
  sf::Text  text;
  int       nb_space;
  std::string s;

  s = hs.a.substr(0, 10);
  if (hs.a.size() <= 10)
    nb_space = 13 - hs.a.size();
  else
    nb_space = 3;
  for (int i = 0; i < nb_space; i++) {
    s += " ";
  }
  s[0] = toupper(s[0]);
  text.setString(s + std::to_string(hs.b));
  text.setColor(sf::Color(0, 0, 0));
  text.setFont(*(this->font));
  text.setCharacterSize(this->dim_window.a / 30);
  if (i < 5)
    text.setPosition(this->pos_map.a + 10,
      this->pos_map.b + i * (this->dim_map.b * this->square / 5) + 10);
  else
    text.setPosition(this->pos_map.a + 10 + this->dim_map.a * this->square / 2,
      this->pos_map.b + (i - 5) * (this->dim_map.b * this->square / 5) + 10);
  return (text);
}

sf::Sprite MediaHandler::getMapSprite(std::string const& key)
{
  Tuple<double>      scale;
  auto               rekt = this->bdSprites[key].getLocalBounds();

  scale.a = this->square * this->dim_map.a / rekt.width;
  scale.b = this->square * this->dim_map.b / rekt.height;
  this->bdSprites[key].setScale(scale.a, scale.b);
  this->bdSprites[key].setPosition(sf::Vector2f(this->pos_map.a - this->square / 2, this->pos_map.b - this->square / 2));
  return (this->bdSprites[key]);
}

sf::RectangleShape   MediaHandler::getMapRectangle()
{
  sf::RectangleShape rekt;

  rekt.setSize(sf::Vector2f(this->dim_map.a * this->square + this->square, this->dim_map.b * this->square + this->square));
  rekt.setPosition(this->pos_map.a - this->square, this->pos_map.b - this->square);
  rekt.setFillColor(sf::Color(122, 69, 0));
  return (rekt);
}

sf::Sprite  MediaHandler::getSprite(Tuple<Tile::Type, Tile::Direction> tile, int x, int y, double coeff)
{
  sf::Vector2f test;

  this->sprites[tile.a].setRotation((float)tile.b);

  if (tile.a == Tile::EVIL_DUDE)
    {
      this->sprites[tile.a].setPosition(x * this->square + this->pos_map.a, y * this->square + this->pos_map.b);
      return (this->sprites[tile.a]);
    }

  if (tile.b == Tile::Direction::RIGHT)
    this->sprites[tile.a].setPosition(x * this->square + this->pos_map.a - this->square * (1 - coeff), y * this->square + this->pos_map.b);
  else if (tile.b == Tile::Direction::LEFT)
    this->sprites[tile.a].setPosition(x * this->square + this->pos_map.a + this->square * (1 - coeff), y * this->square + this->pos_map.b);
  else if (tile.b == Tile::Direction::UP)
    this->sprites[tile.a].setPosition(x * this->square + this->pos_map.a, y * this->square + this->pos_map.b + this->square * (1 - coeff));
  else if (tile.b == Tile::Direction::DOWN)
    this->sprites[tile.a].setPosition(x * this->square + this->pos_map.a, y * this->square + this->pos_map.b - this->square * (1 - coeff));
  else
    this->sprites[tile.a].setPosition(x * this->square + this->pos_map.a, y * this->square + this->pos_map.b);
  return (this->sprites[tile.a]);
}
