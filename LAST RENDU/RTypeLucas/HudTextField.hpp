#pragma once
#include "HudWindow.hpp"

class HudTextField :
	public HudWindow
{
protected:
	unsigned int	maxCount;
	bool			firstStrike;
public:
	HudTextField(unsigned int, const std::string = "", int paramX = 0, int paramY = 0,
		int paramWidth = 50, int paramLength = 50, bool paramB = true);
	~HudTextField(void);
	virtual void	updateField(sf::Event &);

	virtual void	setText(const std::string &);
	virtual Type	getType(void);
};

