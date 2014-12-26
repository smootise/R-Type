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
