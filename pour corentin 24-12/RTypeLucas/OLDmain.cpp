#include "Gui.hpp"

int main()
{
	Gui	graphic;

	if (!graphic.init())
		return (-1);
	while (graphic.affGame() == Gui::Default);
    return 0;
}