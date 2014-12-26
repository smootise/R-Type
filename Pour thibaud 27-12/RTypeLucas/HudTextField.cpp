#include "HudTextField.hpp"
#include <iostream>

HudTextField::HudTextField(unsigned int paramCount, const std::string param, int paramX, int paramY,
	int paramWidth, int paramLength, bool paramB) :
	HudWindow(param, paramX, paramY, paramWidth, paramLength)
{
	maxCount = paramCount;
	firstStrike = paramB;
}

HudTextField::~HudTextField(void)
{
}

void	HudTextField::setText(const std::string &paramText)
{
	str_text = paramText;
	text.setString(str_text + "_");
	updateText();
}

void	HudTextField::updateField(sf::Event & event)
{
	if (event.type == sf::Event::KeyPressed)
	{	
		int	keyCode = event.key.code;
		if (firstStrike && (keyCode == sf::Keyboard::Space || (keyCode <= sf::Keyboard::Z &&
				keyCode >= sf::Keyboard::A)))
		{
			firstStrike = false;
			setText("");
		}
		if (str_text.size() < maxCount)
		{
			if (keyCode <= sf::Keyboard::Z && keyCode >= sf::Keyboard::A)
				setText(str_text + (char)(keyCode - sf::Keyboard::A + 'a' -
				(event.key.shift * ('a' - 'A'))));
			if (keyCode == sf::Keyboard::Space)
				setText(str_text + ' ');
		}
		if (keyCode == sf::Keyboard::BackSpace && str_text.size() > 0)
			setText(str_text.erase(str_text.size() - 1));
	}
}

HudWindow::Type	HudTextField::getType(void)
{
	return (TextField);
}