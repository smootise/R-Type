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
