//
// DispOpengl.cpp for  in /home/yuruh/rendu/cpp_arcade/lib/
//
// Made by Antoine Lempereur
// Login   <lemper_a@epitech.eu>
//
// Started on  Tue Mar  8 18:23:41 2016 Antoine Lempereur
// Last update Sun Apr  3 20:53:58 2016 Antoine Lempereur
//

#include "DispOpengl.hpp"
#include "Event.hpp"

DispOpengl::DispOpengl() : ADisplay(), media(1920, 1080), window(NULL)
{
  this->lastTick = 0;
  this->ressource_rotat = 0;
  this->setKeyMap();
}

void  DispOpengl::init(Map *map, Core *core, Score *score, std::map<Tile::Type, std::string> *text_path)
{
  this->map = map;
  this->core = core;
  this->score = score;
  if (this->map != NULL)
  {
    this->media.setMapDim(map->getWidth(), map->getHeight());
    this->eye = glm::vec3(-this->map->getWidth() / 2, -25.0f, -30.0);
    this->camera = glm::vec3(-this->map->getWidth() / 2, -this->map->getHeight() / 2, 0.0);
  }
  if (text_path != NULL)
  {
    std::map<Tile::Type, std::string>::iterator it = text_path->begin();

    while (it != text_path->end())
    {
      Ressources::setTexture(&this->textures[it->first], it->second);
      it++;
    }
  }
  this->media.addBdTexture("media/arcade_panorama_flou.png", "background");
}

DispOpengl::~DispOpengl()
{
  if (this->window)
  {
    this->window->close();
    delete this->window;
  }
}

extern "C"
{
  IDisplay  *create_instance()
  {
    return (new DispOpengl());
  }
}

void  DispOpengl::setKeyMap()
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

void  DispOpengl::interpretKey(int keycode)
{
  if (this->keyMap.find(keycode) != this->keyMap.end())
    this->core->notify(this->keyMap[keycode]);
}

void  DispOpengl::handleEvents()
{
  sf::Event event;
  while (this->window->pollEvent(event))
  {
    if (event.type == sf::Event::KeyPressed)
      this->interpretKey(event.key.code);
      if (event.type == sf::Event::JoystickButtonPressed)
        {
          if (sf::Joystick::isButtonPressed(0, 0))
            this->core->notify(EVENT_PRESS_DOWN);
          if (sf::Joystick::isButtonPressed(0, 1))
            this->core->notify(EVENT_PRESS_RIGHT);
          if (sf::Joystick::isButtonPressed(0, 2))
            this->core->notify(EVENT_PRESS_LEFT);
          if (sf::Joystick::isButtonPressed(0, 3))
            this->core->notify(EVENT_PRESS_UP);
          if (sf::Joystick::isButtonPressed(1, 0))
            this->core->notify(EVENT_P2_DOWN);
          if (sf::Joystick::isButtonPressed(1, 1))
            this->core->notify(EVENT_P2_RIGHT);
          if (sf::Joystick::isButtonPressed(1, 2))
            this->core->notify(EVENT_P2_LEFT);
          if (sf::Joystick::isButtonPressed(1, 3))
            this->core->notify(EVENT_P2_UP);
          if (sf::Joystick::isButtonPressed(0, 6))
            this->core->notify(EVENT_PAUSE);
          if (sf::Joystick::isButtonPressed(0, 7))
            this->core->notify(EVENT_RESTART);
          if (sf::Joystick::isButtonPressed(0, 4) || sf::Joystick::isButtonPressed(0, 5))
            this->core->notify(EVENT_SHOOT);
        }
  }
  if (sf::Joystick::getAxisPosition(0, sf::Joystick::Y) > 50 || sf::Joystick::getAxisPosition(0, sf::Joystick::Y) < -50)
    this->eye.y += sf::Joystick::getAxisPosition(0, sf::Joystick::Y) / 1000;
  if (sf::Joystick::getAxisPosition(0, sf::Joystick::X) > 50 || sf::Joystick::getAxisPosition(0, sf::Joystick::X) < -50)
    this->eye.x += sf::Joystick::getAxisPosition(0, sf::Joystick::X) / 1000;


}


void  DispOpengl::drawMenu(std::map<std::string, std::string> modules)
{
  sf::Event event;
  int       ylib = 250;
  int       ygames = 350;

  if (!this->window)
  {
    this->window = new sf::RenderWindow(sf::VideoMode(1920, 1080), "Arcade", sf::Style::Default, sf::ContextSettings(24));
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
      this->window->draw(this->media.getSprite("background", 0, 0));
      this->window->draw(this->media.getTitle("arcade         OPENGL"));
      this->window->draw(this->media.getPlayer());
      this->menu.display();
      this->window->display();
    }
}

bool  DispOpengl::initResources()
{
  GLenum glew_status = glewInit();
	if (glew_status != GLEW_OK)
  {
		std::cout << "Error: glewInit: " << glewGetErrorString(glew_status) << std::endl;
		return false;
	}
  Ressources::setCubeVertices(&this->vbo_cube_vertices);
  Ressources::setCubeElements(&this->ibo_cube_elements);
  Ressources::setCubeTexcoord(&this->vbo_cube_texcoords);
  Ressources::setTexture(&this->texture_bd, "media/wood_texture.png");
  Ressources::setTexture(&this->texture_wall, "media/darkwood_texture.jpg");

  	GLint link_ok = GL_FALSE;
  	GLuint vs;
    GLuint fs;

  	if ((vs = Ressources::create_shader("lib/Opengl/shaders/cube.v.glsl", GL_VERTEX_SHADER))   == 0) return false;
  	if ((fs = Ressources::create_shader("lib/Opengl/shaders/cube.f.glsl", GL_FRAGMENT_SHADER)) == 0) return false;

  	program = glCreateProgram();
  	glAttachShader(program, vs);
  	glAttachShader(program, fs);
  	glLinkProgram(program);
  	glGetProgramiv(program, GL_LINK_STATUS, &link_ok);
  	if (!link_ok)
  		return false;

  	if ((attribute_coord3d = glGetAttribLocation(program, "coord3d")) == -1)
  		return false;
  	if ((uniform_mvp = glGetUniformLocation(program, "mvp")) == -1)
  		return false;
    if ((uniform_mytexture = glGetUniformLocation(program, "mytexture")) == -1)
      return false;
    if ((attribute_texcoord = glGetAttribLocation(program, "texcoord")) == -1)
      return false;
  glEnable(GL_BLEND);
  glEnable(GL_DEPTH_TEST);
  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	return true;
}

void   DispOpengl::moveElements(glm::vec3 pos, glm::vec3 scale, float angle)
{
  glm::vec3 axis(0, 0, 1);
  pos.x *= -1;
  pos.y *= -1;
  pos.z *= -1;
  glm::mat4 anim = glm::rotate(glm::mat4(1.0f), glm::radians(1.0f * angle), axis);

  glm::mat4 model = glm::scale(glm::translate(glm::mat4(1.0f), pos), scale);
  glm::mat4 view = glm::lookAt(this->eye, this->camera, glm::vec3(0.0, 1.0, 0.0));
  glm::mat4 projection = glm::perspective(45.0f, 1.0f * 1920 / 1080, 0.1f, 100.0f);
  glm::mat4 mvp = projection * view * model * anim;

  glUseProgram(this->program);
  glUniformMatrix4fv(this->uniform_mvp, 1, GL_FALSE, glm::value_ptr(mvp));
}

void   DispOpengl::drawMapBorder()
{
  int size;

  glBindTexture(GL_TEXTURE_2D, texture_bd);
  glGetBufferParameteriv(GL_ELEMENT_ARRAY_BUFFER, GL_BUFFER_SIZE, &size);
  this->moveElements(glm::vec3((this->map->getWidth() - 1.0f) / 2, (this->map->getHeight() - 1.0f) / 2, -1 -15 / 2),
    glm::vec3(this->map->getWidth(), this->map->getHeight(), 15), 0.0f);
  glDrawElements(GL_TRIANGLES, size / sizeof(GLushort), GL_UNSIGNED_SHORT, 0);

  glBindTexture(GL_TEXTURE_2D, texture_wall);

  this->moveElements(glm::vec3(-1.0f, (this->map->getHeight() - 1.0f) / 2, 0.0f),
    glm::vec3(1.0f, this->map->getHeight(), 1.0f), 90);
  glDrawElements(GL_TRIANGLES, size / sizeof(GLushort), GL_UNSIGNED_SHORT, 0);
  this->moveElements(glm::vec3(this->map->getWidth(), (this->map->getHeight() - 1.0f) / 2, 0.0f),
    glm::vec3(1.0f, this->map->getHeight(), 1.0f), 90);
  glDrawElements(GL_TRIANGLES, size / sizeof(GLushort), GL_UNSIGNED_SHORT, 0);

  this->moveElements(glm::vec3((this->map->getWidth() - 1.0f) / 2, -1.0f, 0.0f),
    glm::vec3(this->map->getWidth() + 2, 1.0f, 1.0f), 0);
  glDrawElements(GL_TRIANGLES, size / sizeof(GLushort), GL_UNSIGNED_SHORT, 0);
  this->moveElements(glm::vec3((this->map->getWidth() - 1.0f) / 2, this->map->getHeight(), 0.0f),
    glm::vec3(this->map->getWidth() + 2, 1.0f, 1.0f), 0);
  glDrawElements(GL_TRIANGLES, size / sizeof(GLushort), GL_UNSIGNED_SHORT, 0);
}

void  DispOpengl::drawEndScreen()
{
  if (this->status->who_won == 0)
  {
    for (size_t i = 0; i < this->score->getScores().size() && i < 10; i++) {
     this->window->draw(this->media.getHighScore(this->score->getScores()[i], i));
   }
  }
  else
   this->window->draw(this->media.getWinner(this->status->who_won));
}

void  DispOpengl::setCamera()
{
  Tile::Direction d;
  glm::vec3   p1(this->camera);
  glm::vec3   p2(this->camera);
  bool        has2players = false;

  for (int y = 0; y < this->map->getHeight(); y++) {
    for (int x = 0; x < this->map->getWidth(); x++) {
      if (this->map->getTiles()[y][x].a == Tile::Type::HEAD)
      {
        p1.x = -x;
        p1.y = -y;
        d = this->map->getTiles()[y][x].b;
        this->camera.x = -x;
        this->camera.y = -y;
        if (d == Tile::Direction::RIGHT)
          this->camera.x += (1 - this->status->camera_coeff);
        if (d == Tile::Direction::LEFT)
          this->camera.x -= (1 - this->status->camera_coeff);
        if (d == Tile::Direction::DOWN)
          this->camera.y += (1 - this->status->camera_coeff);
        if (d == Tile::Direction::UP)
          this->camera.y -= (1 - this->status->camera_coeff);
      }
      if (this->map->getTiles()[y][x].a == Tile::Type::HEAD_P2)
        has2players = true;
    }
  }
  if (has2players)
  {
    this->camera.x = this->map->getWidth() / 2 * -1;
    this->camera.y = this->map->getHeight() / 2 * -1;
  }
}

glm::vec3   DispOpengl::getPos(double x, double y, Tile::Direction d)
{
  glm::vec3 ret(x, y, 0);

  if (this->status->coeff >= 0.99)
    return (ret);
  if (d == Tile::Direction::RIGHT)
    ret.x -= (1 - this->status->coeff);
  if (d == Tile::Direction::LEFT)
    ret.x += (1 - this->status->coeff);
  if (d == Tile::Direction::DOWN)
    ret.y -= (1 - this->status->coeff);
  if (d == Tile::Direction::UP)
    ret.y += (1 - this->status->coeff);
  return (ret);
}

void   DispOpengl::drawMap()
{
  if (!this->window)
  {
    this->window = new sf::RenderWindow(sf::VideoMode(1920, 1080), "Arcade", sf::Style::Default, sf::ContextSettings(24));
    if (!this->initResources())
      return;
  }

  this->window->clear();
  glClearColor(1.0, 1.0, 1.0, 1.0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  this->window->pushGLStates();
  this->window->draw(this->media.getSprite("background", 0, 0));
  this->window->draw(this->media.getTitle("arcade         OPENGL"));
  if (this->status->is_over)
    this->drawEndScreen();
  else
    this->window->draw(this->media.getScore(std::to_string(this->status->score)));
  this->window->popGLStates();
  this->setCamera();
	glUseProgram(this->program);

  glActiveTexture(GL_TEXTURE0);
  glUniform1i(this->uniform_mytexture, 0);


  glEnableVertexAttribArray(this->attribute_coord3d);
	glBindBuffer(GL_ARRAY_BUFFER, this->vbo_cube_vertices);
	glVertexAttribPointer(
		this->attribute_coord3d, // attribute
		3,                 // number of elements per vertex, here (x,y,z)
		GL_FLOAT,          // the type of each element
		GL_FALSE,          // take our values as-is
		0,                 // no extra data between each position
		0                  // offset of first element
	);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo_cube_elements);

  glEnableVertexAttribArray(this->attribute_texcoord);
	glBindBuffer(GL_ARRAY_BUFFER, this->vbo_cube_texcoords);
	glVertexAttribPointer(
		this->attribute_texcoord, // attribute
		2,                 // number of elements per vertex, here (R,G,B)
		GL_FLOAT,          // the type of each element
		GL_FALSE,          // take our values as-is
		0,                 // no extra data between each position
		0                  // offset of first element
	);
  this->ressource_rotat += 1;
  if (!this->status->is_over)
  {
    this->drawMapBorder();

    int size;
    glGetBufferParameteriv(GL_ELEMENT_ARRAY_BUFFER, GL_BUFFER_SIZE, &size);
  for (double x = 0; x < this->map->getWidth(); x++)
    for (double y = 0; y < this->map->getHeight(); y++)
    {
      if (this->map->getTiles()[(int)y][(int)x].a != Tile::Type::EMPTY)
      {
        glBindTexture(GL_TEXTURE_2D, this->textures[this->map->getTiles()[(int)y][(int)x].a]);
        if (this->map->getTiles()[(int)y][(int)x].a != Tile::Type::RESSOURCE &&
      this->map->getTiles()[(int)y][(int)x].a != Tile::Type::POWERUP && this->map->getTiles()[(int)y][(int)x].a)
          this->moveElements(this->getPos(x, y, this->map->getTiles()[(int)y][(int)x].b), glm::vec3(1.0f, 1.0f, 1.0f), (float)(this->map->getTiles()[(int)y][(int)x].b));
        else
          this->moveElements(glm::vec3(x, y, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f), this->ressource_rotat);
       if (this->map->getTiles()[(int)y][(int)x].a == Tile::Type::EVIL_DUDE)
          this->moveElements(glm::vec3(x, y, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f), (float)(this->map->getTiles()[(int)y][(int)x].b));
        glDrawElements(GL_TRIANGLES, size / sizeof(GLushort), GL_UNSIGNED_SHORT, 0);
      }
    }
  }

  glDisableVertexAttribArray(attribute_texcoord);
  glDisableVertexAttribArray(attribute_coord3d);
  glBindBuffer(GL_ARRAY_BUFFER, 0);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
  glUseProgram(0);

  this->window->display();


  this->handleEvents();
}
