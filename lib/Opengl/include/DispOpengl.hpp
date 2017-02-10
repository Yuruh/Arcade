//
// Opengl.hpp for  in /home/yuruh/rendu/cpp_arcade/include/
//
// Made by Antoine Lempereur
// Login   <lemper_a@epitech.eu>
//
// Started on  Tue Mar  8 17:33:47 2016 Antoine Lempereur
// Last update Sun Apr  3 20:29:25 2016 Antoine Lempereur
//

#ifndef DISPOPENGL_HPP_
#define DISPOPENGL_HPP_

#include <unistd.h>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <GL/glew.h>

#include "Graphics.hpp"
#include "Window.hpp"

#include "ADisplay.hpp"
#include "Core.hpp"
#include "Ressources.hpp"
#include "ModuleSfml.hpp"
#include "MediaHandler.hpp"

class   DispOpengl : public ADisplay
{
private:
  MediaHandler        media;
  sf::RenderWindow    *window;
  std::map<int, e_action> keyMap;
  int                 lastTick;
  sf::Clock           clock;
  GLuint vbo_cube_vertices;
  GLuint vbo_cube_texcoords;
  GLuint ibo_cube_elements;
  GLuint program;
  GLint attribute_coord3d;
  GLint attribute_texcoord;
  GLint uniform_mvp;
  std::map<Tile::Type, GLuint> textures;
  GLuint texture_bd;
  GLuint texture_wall;
  GLuint program_id;
  GLint uniform_mytexture;
  float   ressource_rotat;
  glm::vec3     eye;
  glm::vec3     camera;
  sf::Texture   bd_text;
  sf::Sprite    bd_sprite;
public:
  DispOpengl();
  virtual ~DispOpengl();
  void    setKeyMap();
  virtual void  drawMenu(std::map<std::string, std::string>);
  glm::vec3      getPos(double, double, Tile::Direction);
  void          interpretKey(int);
  bool          initResources();
  void          setCamera();
  void          drawEndScreen();
  void          moveElements(glm::vec3, glm::vec3, float);
  void          handleEvents();
  void          drawMap();
  void          init(Map*, Core*, Score*, std::map<Tile::Type, std::string>*);
  void          drawMapBorder();
};

#endif
