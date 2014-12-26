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
