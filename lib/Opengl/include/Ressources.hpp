//
// Ressources.hpp for  in /home/yuruh/rendu/cpp/cpp_arcade/lib/Opengl/include/
//
// Made by Antoine Lempereur
// Login   <lemper_a@epitech.eu>
//
// Started on  Fri Apr  1 13:21:08 2016 Antoine Lempereur
// Last update Sat Apr  2 13:11:19 2016 Antoine Lempereur
//

#ifndef RESSOURCES_HPP
#define RESSOURCES_HPP

#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <GL/glew.h>
#include <string>
#include <iostream>
#include <fstream>
#include "Graphics.hpp"


class   Ressources
{
public:
  Ressources();
  ~Ressources();
  static void setCubeVertices(GLuint *);
  static void setCubeColors(GLuint *);
  static void setCubeElements(GLuint *);
  static void setCubeTexcoord(GLuint *);
  static void setTexture(GLuint *, std::string const&);
  static GLuint        create_shader(std::string const&, GLenum);
};

#endif
