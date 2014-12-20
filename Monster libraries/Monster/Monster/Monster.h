#pragma once
class Monster
{
private:
	int _health; 
	int _dmg;
	float _speed;
	float _size;
	float _x;
	float _y;
	bool _alive;

public:
	Monster();
	~Monster();
	void update();
	void draw();
	void move(float x, float y);
};

class M_light :
	public Monster
{
public:
	M_light();
	~M_light();
};

class M_heavy :
	public Monster
{
public:
	M_heavy();
	~M_heavy();
};

class M_medium :
	public Monster
{
public:
	M_medium();
	~M_medium();
};

class M_boss :
	public Monster
{
public:
	M_boss();
	~M_boss();
};

