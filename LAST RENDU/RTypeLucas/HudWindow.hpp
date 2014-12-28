#pragma once

#include <SFML/Graphics.hpp>
#include <string>

class HudWindow
{
protected:
	std::string	str_text;
	sf::Font	font;
	sf::Text	text;
	sf::RectangleShape	bg;
	sf::Texture textNotSel;
	sf::Texture	textSelec;
	sf::Color	colorTextS;
	sf::Color	colorTextN;
	int			winX;
	int			winY;
	int			winWidth;
	int			winLength;
	bool		isSelected;
	bool		inited;

	void	updateText(void);
public:
	enum Type
	{
		Default,
		TextField
	};
	HudWindow(const std::string = "", int paramX = 0, int paramY = 0, int paramWidth = 50, int paramLength = 50);
	virtual ~HudWindow(void);
	virtual bool	init(void);
	virtual void	draw(sf::RenderWindow &) const;

	virtual void	setText(const std::string &);
	virtual void	setPosition(int paramX, int paramY, int paramWidth = -1, int paramLength = -1);
	virtual void	setColor(sf::Color, sf::Color);
	virtual void	setSelected(bool);

	virtual bool	getSelected(void) const;
	virtual const	std::string & getText(void) const;
	virtual Type	getType(void);
};

