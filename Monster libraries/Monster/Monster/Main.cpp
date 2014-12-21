/*fdef SFML_STATIC
#pragma comment(lib, "glew.lib")
#pragma comment(lib, "freetype.lib")
#pragma comment(lib, "jpeg.lib")
#pragma comment(lib, "opengl32.lib")
#pragma comment(lib, "winmm.lib")
#pragma comment(lib, "gdi32.lib")  
#endif // SFML_STATIC*/


#include <SFML/Graphics.hpp>

#include "Spawner.h"

int main()
{
	Spawner Test("test.txt");
	Test.afftiming();
	Test.isAlive(100);
	Test.update();
	Test.afftiming();
	getchar();
	return 0;
}