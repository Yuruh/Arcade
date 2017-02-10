//
// MediaHandler.hpp for  in /home/yuruh/rendu/cpp_arcade/include/
//
// Made by Antoine Lempereur
// Login   <lemper_a@epitech.eu>
//
// Started on  Wed Mar  9 12:51:28 2016 Antoine Lempereur
// Last update Sun Apr  3 17:02:33 2016 Antoine Lempereur
//

#ifndef MEDIAHANDLER_HPP_
#define MEDIAHANDLER_HPP_

#include <map>
#include <iostream>
#include <SFML/Graphics.hpp>
#include "Tuple.hpp"
#include "Protocol.hpp"
#include "Tile.hpp"

class MediaHandler
{
private:
  Tuple<double>           pos_map;
  Tuple<int>              dim_map;
  Tuple<int>              dim_window;
  double                  square;
  std::string             player;
  std::map<Tile::Type, sf::Texture> tileText;
  std::map<std::string, sf::Texture> bdText;
  std::map<std::string, sf::Sprite> bdSprites;
  std::map<Tile::Type, sf::Sprite> sprites;
public:
  MediaHandler(int, int);
  ~MediaHandler() {}
  void                setMapDim(int, int);
  void                addTileTexture(std::string const& path, Tile::Type);
  void                addBdTexture(std::string const& path, std::string const& key);
  sf::Sprite          getSprite(Tuple<Tile::Type, Tile::Direction>, int x, int y, double coeff);
  sf::Sprite          getSprite(std::string const&, int, int);
  sf::Sprite          getMapSprite(std::string const&);
  sf::RectangleShape  getMapRectangle();
  sf::Text            getHighScore(Tuple<std::string, int> hs, int i);
  sf::RectangleShape  getHighScoreRectangle();
  sf::Text            getTitle(std::string const&);
  sf::Text            getPlayer();
  sf::Text            getScore(std::string const&);
  std::string         getPlayerName() const { return (this->player); }
  sf::Text            getWinner(int);
  void                interpretTextInput(char);
  bool                hasSprite(Tile::Type);
  sf::Font*   font;
};

#endif
