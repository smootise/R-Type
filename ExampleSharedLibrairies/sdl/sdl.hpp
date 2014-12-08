//
// Operand.hpp for Igraphic in /home/sarkad_l/Dropbox/Projets/nibbler_theo_lulu
// 
// Made by Lucas SARKADI
// Login   <sarkad_l@epitech.net>
// 
// Started on  Fri Apr  4 00:07:37 2014 Lucas SARKADI
// Last update Sun Apr  6 23:25:31 2014 theo richard
//

#ifndef GRAPHICSDL_H_
#define GRAPHICSDL_H_

#include <SDL/SDL.h>
#include "../Igraphic.hpp"
#include <vector>
#include <map>

# define BLOCK (48)

class	graphicSdl : public Igraphic
{
private:
  int				decal_x;
  int				decal_y;
  SDL_Surface			*screen;
  std::map<std::string, SDL_Surface *>	text;
  SDL_Surface	*toBlit(int, int);
public :
  graphicSdl(int, int);
  ~graphicSdl(void);
  eInput	gameLoop(const std::vector<std::vector<int> >&, int);
};

#endif /* !GRAPHICSDL_H_ */
