//
// Errors.cpp for  in /home/descam_d/workspace/C++/cpp_arcade
// 
// Made by Corentin Descamps
// Login   <descam_d@epitech.net>
// 
// Started on  Fri Mar 11 13:34:32 2016 Corentin Descamps
// Last update Fri Mar 11 15:00:18 2016 Corentin Descamps
//

#include	"Errors.hpp"

ArcadeError::ArcadeError(std::string const& message)
{
  this->m_message = message;
}

const char*	ArcadeError::what() const throw()
{
  return (this->m_message.c_str());
}

CoreError::CoreError(std::string const& message)
{
  this->m_message = message;
}
