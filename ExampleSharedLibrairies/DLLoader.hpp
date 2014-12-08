//
// DLLoader.hpp for dllloader in /home/sarkad_l/Dropbox/Projets/nibbler_theo_lulu/cpy
// 
// Made by Lucas SARKADI
// Login   <sarkad_l@epitech.net>
// 
// Started on  Sun Apr  6 19:01:19 2014 Lucas SARKADI
// Last update Sun Apr  6 21:20:25 2014 Lucas SARKADI
//

#ifndef DLLoader_H_
# define DLLoader_H_

#include "Igraphic.hpp"
#include <iostream>
#include <string>

class		DLLoader
{
protected:
  void		*_handle;
  int		_lenght;
  int		_width;

public:
  DLLoader(const std::string &, int, int);
  ~DLLoader();
  Igraphic	*getInstance(void *);
};

#endif /* !DLLoader_H_ */
