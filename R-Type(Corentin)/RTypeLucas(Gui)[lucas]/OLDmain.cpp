#include <SFML/Graphics.hpp>
#include "Gui.hpp"

int main()
{
	Gui	graphic;

	if (!graphic.init())
		return (-1);
	while (graphic.affScreen() == Gui::Default);
    return 0;
}