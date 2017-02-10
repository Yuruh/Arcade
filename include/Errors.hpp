//
// Errors.hpp for  in /home/descam_d/workspace/C++/cpp_arcade
// 
// Made by Corentin Descamps
// Login   <descam_d@epitech.net>
// 
// Started on  Fri Mar 11 13:34:37 2016 Corentin Descamps
// Last update Fri Mar 11 15:43:21 2016 Corentin Descamps
//

#ifndef		ERRORS_HPP_
# define	ERRORS_HPP_

# include	<stdexcept>
# include	<string>

class		ArcadeError : public std::exception
{
public:
  ArcadeError(std::string const& message = "");
  ~ArcadeError() throw() {}
  virtual const char* what() const throw();

protected:
  std::string	m_message;
};

class		CoreError : public ArcadeError
{
public:
  CoreError(std::string const& message);
};

#endif		/* !ERRORS_HPP_ */
