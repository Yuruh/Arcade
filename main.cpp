//
// main.cpp for azer in /home/yuruh/rendu/cpp_arcade
//
// Made by Antoine Lempereur
// Login   <yuruh@epitech.net>
//
// Started on  Tue Mar  8 13:02:38 2016 Antoine Lempereur
// Last update Sun Apr  3 21:02:45 2016 Corentin Descamps
//

#include <iostream>
#include <dlfcn.h>
#include "Core.hpp"
#include "DLLoader.hpp"
#include "Score.hpp"

int	main(int ac, char **av)
{
  Core core;

  if (ac != 2)
    return (1);
  try {
    srand(time(NULL));
    core.getPath();
    core.init(std::string(av[1]));
    core.run();
  }
  catch (CoreError& e) {
    std::cerr << e.what() << std::endl;
  }
  catch (std::exception& e) {
    std::cerr << e.what() << std::endl;
  }
  return (0);
}
