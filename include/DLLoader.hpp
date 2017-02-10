//
// DLLoader.hpp for  in /home/descam_d/workspace/C++/cpp_arcade
//
// Made by Corentin Descamps
// Login   <descam_d@epitech.net>
//
// Started on  Thu Mar 10 19:04:26 2016 Corentin Descamps
// Last update Sun Apr  3 16:08:02 2016 Antoine Lempereur
//

#ifndef		DLLOADER_HPP_
# define	DLLOADER_HPP_

# include	<stdexcept>
# include	<dlfcn.h>
# include	"IDisplay.hpp"
# include	"Errors.hpp"

template<class T>
class		DLLoader
{
public:
  DLLoader();
  ~DLLoader();
  void		open(std::string const& path);
  void		close();
  T*		getInstance();

private:
  void		*handle;
  std::string m_path;
  T*      m_instance;
};

template<class T>
DLLoader<T>::DLLoader()
{
  this->handle = NULL;
  this->m_instance = NULL;
}

template<class T>
DLLoader<T>::~DLLoader()
{
  this->close();
}

#include <iostream>
template<class T>
void		DLLoader<T>::open(std::string const& path)
{
  if (!this->handle)
  {
    this->handle = dlopen(path.c_str(), RTLD_LAZY);
    this->m_path = path;
  }
  if (this->handle == NULL)
    throw CoreError("Could not load dll : " + path + " because " + dlerror());
}

template<class T>
void		DLLoader<T>::close()
{
  if (this->m_instance)
  {
    delete this->m_instance;
    this->m_instance = NULL;
  }
  if (this->handle)
  {
    dlclose(this->handle);
    this->handle = NULL;
  }
}

template<class T>
T*		DLLoader<T>::getInstance()
{
  T*		(*external_creator)();

  if (this->m_instance != NULL)
    return (this->m_instance);
  external_creator = reinterpret_cast<T* (*)()>(dlsym(this->handle, "create_instance"));
  if (external_creator == NULL)
    throw CoreError("Could not resolve symbols");
  this->m_instance = external_creator();
  return (this->m_instance);
}


#endif		/* !DLLOADER_HPP_ */
