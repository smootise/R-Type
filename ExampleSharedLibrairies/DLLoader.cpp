//
// DLLoader.cpp for dllloader in /home/sarkad_l/Dropbox/Projets/nibbler_theo_lulu/cpy
// 
// Made by Lucas SARKADI
// Login   <sarkad_l@epitech.net>
// 
// Started on  Sun Apr  6 19:01:09 2014 Lucas SARKADI
// Last update Sun Apr  6 21:23:45 2014 Lucas SARKADI
//

#include <dlfcn.h>
#include "DLLoader.hpp"
#include "raise.hpp"

DLLoader::DLLoader(const std::string &lib, int lenght, int width)
  : _lenght(lenght), _width(width)
{ 
  void			*dlhandle;

  dlhandle = dlopen(lib.c_str(), RTLD_LAZY);
  if (dlhandle == NULL)
    raise("Dlopen failed (Wrong library path)");
  this->_handle = dlhandle;
}

DLLoader::~DLLoader(void)
{ 
  dlclose(this->_handle);
}

Igraphic		*DLLoader::getInstance(void *todelete)
{
  Igraphic	*(*external_creator)(int, int, void *);

  external_creator = reinterpret_cast<Igraphic* (*)(int, int, void *)>(dlsym(this->_handle, "create"));
  if (external_creator == NULL)
    raise("Couldn't use the create function in the library");
  Igraphic	*ret;
  
  if (todelete == NULL)
    ret = external_creator(this->_width, this->_lenght, NULL);
  else
    ret = external_creator(0, 0, todelete);    
  return (ret);
}
