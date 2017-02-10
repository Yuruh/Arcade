//
// Ressources.cpp for  in /home/yuruh/rendu/cpp/cpp_arcade/lib/Sfml/src/
//
// Made by Antoine Lempereur
// Login   <lemper_a@epitech.eu>
//
// Started on  Fri Apr  1 13:17:32 2016 Antoine Lempereur
// Last update Sat Apr  2 22:44:28 2016 Antoine Lempereur
//

#include "Ressources.hpp"

Ressources::Ressources()
{

}

Ressources::~Ressources()
{

}

void        Ressources::setCubeVertices(GLuint *vertices)
{
  GLfloat cube_vertices[] = {
    // front
    -0.5, -0.5,  0.5,
     0.5, -0.5,  0.5,
     0.5,  0.5,  0.5,
    -0.5,  0.5,  0.5,
    // top
    -0.5,  0.5,  0.5,
     0.5,  0.5,  0.5,
     0.5,  0.5, -0.5,
    -0.5,  0.5, -0.5,
    // back
     0.5, -0.5, -0.5,
    -0.5, -0.5, -0.5,
    -0.5,  0.5, -0.5,
     0.5,  0.5, -0.5,
    // bottom
    -0.5, -0.5, -0.5,
     0.5, -0.5, -0.5,
     0.5, -0.5,  0.5,
    -0.5, -0.5,  0.5,
    // left
    -0.5, -0.5, -0.5,
    -0.5, -0.5,  0.5,
    -0.5,  0.5,  0.5,
    -0.5,  0.5, -0.5,
    // right
     0.5, -0.5,  0.5,
     0.5, -0.5, -0.5,
     0.5,  0.5, -0.5,
     0.5,  0.5,  0.5,
  };
  glGenBuffers(1, vertices);
  glBindBuffer(GL_ARRAY_BUFFER, *vertices);
  glBufferData(GL_ARRAY_BUFFER, sizeof(cube_vertices), cube_vertices, GL_STATIC_DRAW);
}

GLuint Ressources::create_shader(std::string const& filename, GLenum type)
{
  std::ifstream stream;
  stream.open(filename);
  if (!stream.is_open())
    exit(1);
  std::string buffer;
  std::string line;

  while (std::getline(stream, line))
    buffer += line + '\n';
  stream.close();

	GLuint res = glCreateShader(type);
  const GLchar* sources = (GLchar*)(buffer.c_str());
	glShaderSource(res, 1, &sources, NULL);

	glCompileShader(res);
	GLint compile_ok = GL_FALSE;
	glGetShaderiv(res, GL_COMPILE_STATUS, &compile_ok);
	if (compile_ok == GL_FALSE) {
		std::cerr << filename << ":";
		glDeleteShader(res);
		return 0;
	}
	return res;
}

void  Ressources::setCubeColors(GLuint *colors)
{
  GLfloat cube_colors[] = {
    // front colors
    1.0, 1.0, 1.0,
    1.0, 1.0, 1.0,
    0.5, 0.5, 0.5,
    0.5, 0.5, 0.5,
    // back colors
    1.0, 1.0, 1.0,
    1.0, 1.0, 1.0,
    0.5, 0.5, 0.5,
    0.5, 0.5, 0.5,
  };

  glGenBuffers(1, colors);
  glBindBuffer(GL_ARRAY_BUFFER, *colors);
  glBufferData(GL_ARRAY_BUFFER, sizeof(cube_colors), cube_colors, GL_STATIC_DRAW);
}

void  Ressources::setCubeElements(GLuint *elements)
{
  GLushort cube_elements[] = {
    // front
    0,  1,  2,
    2,  3,  0,
    // top
    4,  5,  6,
    6,  7,  4,
    // back
    8,  9, 10,
    10, 11,  8,
    // bottom
    12, 13, 14,
    14, 15, 12,
    // left
    16, 17, 18,
    18, 19, 16,
    // right
    20, 21, 22,
    22, 23, 20,
  };

  glGenBuffers(1, elements);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, *elements);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(cube_elements), cube_elements, GL_STATIC_DRAW);
}

void  Ressources::setCubeTexcoord(GLuint *texcoord)
{
  GLfloat cube_texcoords[2*4*6] = {
      // front
      0.0, 0.0,
      1.0, 0.0,
      1.0, 1.0,
      0.0, 1.0,
    };
    for (int i = 1; i < 6; i++)
      memcpy(&cube_texcoords[i*4*2], &cube_texcoords[0], 2*4*sizeof(GLfloat));
  glGenBuffers(1, texcoord);
  glBindBuffer(GL_ARRAY_BUFFER, *texcoord);
  glBufferData(GL_ARRAY_BUFFER, sizeof(cube_texcoords), cube_texcoords, GL_STATIC_DRAW);
}
void  Ressources::setTexture(GLuint *texture_id, std::string const& path)
{
  sf::Image img_data;
  if (!img_data.loadFromFile(path))
    return;

  glGenTextures(1, texture_id);
  glBindTexture(GL_TEXTURE_2D, *texture_id);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
  glTexImage2D(GL_TEXTURE_2D, // target
    0,  // level, 0 = base, no minimap,
    GL_RGBA, // internalformat
    img_data.getSize().x,  // width
    img_data.getSize().y,  // height
    0,  // border, always 0 in OpenGL ES
    GL_RGBA,  // format
    GL_UNSIGNED_BYTE, // type
    img_data.getPixelsPtr());
}
