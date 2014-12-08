//
// Operand.hpp for Igraphic in /home/sarkad_l/Dropbox/Projets/nibbler_theo_lulu
// 
// Made by Lucas SARKADI
// Login   <sarkad_l@epitech.net>
// 
// Started on  Fri Apr  4 00:07:37 2014 Lucas SARKADI
// Last update Sun Apr  6 23:26:24 2014 Lucas SARKADI
//

#ifndef IGRAPHIC_H_
# define IGRAPHIC_H_

#include <vector>

# define FRUIT (-3)

# define WALL (-1)

enum { RIGHT,
       DOWN,
       LEFT,
       UP};

enum eInput {NOTHING = 0, 
	     LEFTKEY = 1,
	     RIGHTKEY = 2,
	     ECHAPKEY = 3};

class	Igraphic
{
public :
  Igraphic() {};
  virtual ~Igraphic(void) {};
  virtual eInput	gameLoop(const std::vector<std::vector<int> > &, int) = 0;
};

#endif /* !IGRAPHIC_H_ */
