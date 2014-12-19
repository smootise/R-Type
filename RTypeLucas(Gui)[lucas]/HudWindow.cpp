#include <algorithm>
#include "HudWindow.hpp"

HudWindow::HudWindow(const std::string param, int paramX, int paramY, int paramWidth, int paramLength)
{
	winX = paramX;
	winY = paramY;
	winWidth = paramWidth;
	winLength = paramLength;
	setColor(sf::Color::Black, sf::Color::White);
	setText(param);
	isSelected = false;
	inited = false;
}

HudWindow::~HudWindow(void)
{

}

void	HudWindow::updateText(void)
{
	int	div = std::count(str_text.begin(), str_text.end(), '\n') + 1;
	text.setCharacterSize((winLength * 8 / 10) / div);
	if (text.getCharacterSize() < 6)
		text.setCharacterSize(6);
	while (text.getCharacterSize() > 106 && text.getLocalBounds().width >= winWidth * 9 / 10 + 100)
		text.setCharacterSize(text.getCharacterSize() - 100);
	while (text.getCharacterSize() > 16 && text.getLocalBounds().width >= winWidth * 9 / 10 + 10)
		text.setCharacterSize(text.getCharacterSize() - 10);
	while (text.getCharacterSize() > 6 && text.getLocalBounds().width > winWidth * 9 / 10)
		text.setCharacterSize(text.getCharacterSize() - 1);
	text.setPosition(winX + winWidth / 2 - text.getLocalBounds().width / 2,
	winY + winLength / 2 - text.getCharacterSize() * div / 2);
}

bool	HudWindow::init(void)
{
	inited = true;
	if (!font.loadFromFile("Font.ttf"))
		return (false);
	if (!textSelec.loadFromFile("HudWindowN.png"))
		return (false);
	if (!textNotSel.loadFromFile("HudWindow.png"))
		return (false);
	text.setFont(font);
	setPosition(winX, winY, winWidth, winLength);
	setSelected(isSelected);
	return (true);
}

void	HudWindow::draw(sf::RenderWindow &app) const
{
	app.draw(bg);
	app.draw(text);
}

void	HudWindow::setText(const std::string &paramText)
{
	str_text = paramText;
	text.setString(str_text);
	updateText();
}

void	HudWindow::setPosition(int paramX, int paramY, int paramWidth, int paramLength)
{
	if (paramX >= 0 && paramY >= 0)
	{
		winX = paramX;
		winY = paramY;
	}
	if (paramWidth > 0 && paramLength > 0)
	{
		winWidth = paramWidth;
		winLength = paramLength;
	}
	updateText();
	bg.setSize(sf::Vector2f(winWidth, winLength));
	bg.setPosition(sf::Vector2f(winX, winY));
}

void	HudWindow::setSelected(bool param)
{
	isSelected = param;
	if (!inited)
		return ;
	if (isSelected)
	{
		text.setColor(colorTextS);
		bg.setTexture(&textSelec);
	}
	else
	{
		text.setColor(colorTextN);
		bg.setTexture(&textNotSel);
	}
}

void	HudWindow::setColor(sf::Color paramTextS, sf::Color paramTextN)
{
	colorTextN = paramTextN;
	colorTextS = paramTextS;
	if (isSelected)
		text.setColor(colorTextS);
	else
		text.setColor(colorTextN);
}

const std::string & HudWindow::getText(void) const
{
	return (str_text);
}

bool	HudWindow::getSelected(void) const
{
	return (isSelected);
}

HudWindow::Type	HudWindow::getType(void)
{
	return (Default);
}