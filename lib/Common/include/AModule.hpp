//
// AModule.hpp for  in /home/yuruh/rendu/cpp/cpp_arcade/lib/Caca/include/
//
// Made by Antoine Lempereur
// Login   <lemper_a@epitech.eu>
//
// Started on  Mon Mar 14 13:45:42 2016 Antoine Lempereur
// Last update Fri Apr  1 17:03:41 2016 Antoine Lempereur
//

#ifndef AModule_HPP_
#define AModule_HPP_

#include "Core.hpp"
#include "Event.hpp"

class   AModule
{
protected:
  int   x;
  int   y;
  bool  selected;
  e_menu type;
  std::string path;
public:
  AModule(int, int, e_menu type, std::string const& path);
  virtual ~AModule();
  virtual void  display() = 0;
  virtual void  setSelected(bool);
  virtual bool  isSelected() const;
  virtual e_menu getType () const {return (this->type);}
  virtual std::string getPath () const {return (this->path);}
};

#endif
