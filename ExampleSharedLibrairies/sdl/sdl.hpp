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
