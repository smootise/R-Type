//
// sdl.cpp for sdl in /home/sarkad_l/Dropbox/Projets/nibbler_theo_lulu/sdl
// 
// Made by Lucas SARKADI
// Login   <sarkad_l@epitech.net>
// 
// Started on  Sun Apr  6 15:24:34 2014 Lucas SARKADI
// Last update Sun Apr  6 23:26:29 2014 theo richard
//

#include <string>
#include <iostream>
#include <cstdlib>
#include "sdl.hpp"

static void	my_error(const std::string & str)
{
  std::cout << str;
  exit(-1);
}

graphicSdl::graphicSdl(int width, int length)
{
  int		a_width;
  int		a_length;

  a_width = (width * BLOCK > 1440) ? 1440 : width * BLOCK;
  a_length = (length * BLOCK > 960) ? 960 : length * BLOCK;
  if (SDL_Init(SDL_INIT_VIDEO) == -1)
    my_error("Fail SDL INIT\n");
  if ((this->screen = SDL_SetVideoMode(a_width, a_length,
				       32, SDL_SWSURFACE | SDL_DOUBLEBUF)) == NULL)
    my_error("Fail SDL SetVideoMode\n");
  SDL_WM_SetCaption("Nibbler richar_x sarkad_l", NULL);
  if ((this->text["floor"] = SDL_LoadBMP("sdl/picture/grass.bmp")) == NULL)
    my_error("Fail SDL LoadBMP\n");
  if ((this->text["wall"] = SDL_LoadBMP("sdl/picture/stone.bmp")) == NULL)
    my_error("Fail SDL LoadBMP\n");
  SDL_SetColorKey(this->text["wall"], SDL_SRCCOLORKEY,
                  SDL_MapRGB(this->text["wall"]->format, 0, 255, 0));
  if ((this->text["fruit"] = SDL_LoadBMP("sdl/picture/fruit.bmp")) == NULL)
    my_error("Fail SDL LoadBMP\n");
  SDL_SetColorKey(this->text["fruit"], SDL_SRCCOLORKEY,
                  SDL_MapRGB(this->text["fruit"]->format, 0, 255, 0));
  if ((this->text["body"] = SDL_LoadBMP("sdl/picture/body.bmp")) == NULL)
    my_error("Fail SDL LoadBMP\n");
  SDL_SetColorKey(this->text["body"], SDL_SRCCOLORKEY,
                  SDL_MapRGB(this->text["body"]->format, 0, 255, 0));
  if ((this->text["head1"] = SDL_LoadBMP("sdl/picture/head1.bmp")) == NULL)
    my_error("Fail SDL LoadBMP\n");
  SDL_SetColorKey(this->text["head1"], SDL_SRCCOLORKEY,
                  SDL_MapRGB(this->text["head1"]->format, 0, 255, 0));
  if ((this->text["head2"] = SDL_LoadBMP("sdl/picture/head4.bmp")) == NULL)
    my_error("Fail SDL LoadBMP\n");
  SDL_SetColorKey(this->text["head2"], SDL_SRCCOLORKEY,
                  SDL_MapRGB(this->text["head2"]->format, 0, 255, 0));
  if ((this->text["head3"] = SDL_LoadBMP("sdl/picture/head3.bmp")) == NULL)
    my_error("Fail SDL LoadBMP\n");
  SDL_SetColorKey(this->text["head3"], SDL_SRCCOLORKEY,
                  SDL_MapRGB(this->text["head3"]->format, 0, 255, 0));
  if ((this->text["head4"] = SDL_LoadBMP("sdl/picture/head2.bmp")) == NULL)
    my_error("Fail SDL LoadBMP\n");
  SDL_SetColorKey(this->text["head4"], SDL_SRCCOLORKEY,
                  SDL_MapRGB(this->text["head4"]->format, 0, 255, 0));
}

graphicSdl::~graphicSdl(void)
{
  SDL_Quit();
}

SDL_Surface	*graphicSdl::toBlit(int block, int dir)
{
  std::string		str_head;

  if (block == WALL)
    return this->text["wall"];
  if (block == FRUIT)
    return this->text["fruit"];
  if (block == 1)
    {
      str_head = "headx";
      str_head[4] = dir + '1';
      return this->text[str_head];
    }
  if (block > 1)
    return this->text["body"];
  return (NULL);
}

static eInput	maj_to_ret(const SDL_Event *event, const eInput to_ret)
{
  if (event->key.keysym.sym == SDLK_ESCAPE || to_ret == ECHAPKEY)
    return (ECHAPKEY);
  if (to_ret != NOTHING)
    return (to_ret);
  if (event->key.keysym.sym == SDLK_LEFT)
    return (RIGHTKEY);
  if (event->key.keysym.sym == SDLK_RIGHT)
    return (LEFTKEY);
  return (to_ret);
}

static void	get_decal(const std::vector<std::vector<int> > & map, int *decal_x, int *decal_y)
{
  unsigned int	i;
  unsigned int	j;
  int		x;
  int		y;

  for (i = 0; i < map.size(); i++)
    for (j = 0; j < map[i].size(); j++)
      if (map[i][j] == 1)
	{
	  x = i;
	  y = j;
	}
  *decal_x = -1 * x + 15;
  *decal_y = -1 * y + 10;
  if (map.size() > 30 && *decal_x < 0)
    *decal_x = (*decal_x < -1 * (map.size() - 30)) ? -1 * (map.size() - 30) : *decal_x;
  else
    *decal_x = 0;
  if (map[0].size() > 20 && *decal_y < 0)
    *decal_y = (*decal_y < -1 * (map[0].size() - 20)) ? -1 * (map[0].size() - 20) : *decal_y;
  else
    *decal_y = 0;
  *decal_x = (*decal_x > 0) ? 0 : *decal_x;
  *decal_y = (*decal_y > 0) ? 0 : *decal_y;
}

eInput		graphicSdl::gameLoop(const std::vector<std::vector<int> > & map, int dir)
{
  unsigned int	i;
  unsigned int	j;
  SDL_Rect	pos;
  SDL_Surface	*toblit;
  SDL_Event     event;
  eInput	to_ret;

  get_decal(map, &(this->decal_x), &(this->decal_y));
  for (i = 0; i < map.size(); i++)
    for (j = 0; j < map[i].size(); j++)
      {
	pos.x = (i + this->decal_x) * BLOCK;
	pos.y = (j + this->decal_y) * BLOCK;
	if (pos.x >= 0 && pos.y >= 0)
	  {
	    if ((SDL_BlitSurface(this->text["floor"], NULL, this->screen, &pos)) == -1)
	      my_error("Couldn't Blit on the screen (SDL)\n");	
	    if ((toblit = toBlit(map[i][j], dir)))
	      if ((SDL_BlitSurface(toblit, NULL, this->screen, &pos)) == -1)
		my_error("Couldn't Blit on the screen (SDL)\n");	 
	  }
     }
  if ((SDL_Flip(this->screen)) == -1)
    my_error("Fail SDL Flip\n");
  i = 0;
  to_ret = NOTHING;
  while (i < 10)
    {
      SDL_Delay(20);
      SDL_PollEvent(&event);
      if (event.type == SDL_KEYDOWN)
	to_ret = maj_to_ret(&event, to_ret);
      i++;
    }
  return (to_ret);
}

extern "C"
{
  graphicSdl		*create(int width, int lenght, graphicSdl *todelete)
  {
    graphicSdl		*ret = NULL;

    if (todelete == NULL)
      ret = new graphicSdl(width, lenght);
    else
      delete todelete;
    return (ret);
  }
}
