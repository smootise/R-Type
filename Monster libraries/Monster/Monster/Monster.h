#pragma once
class Monster
{
protected:
	int _timing;
	int _health;
	int _dmg;
	float _speed;
	float _size;
	float _x;
	float _y;
	bool _alive;
	bool _dead;

public:
	Monster(int time);
	~Monster();
	void update();
	void draw();
	bool isAlive(int time);
	void Die();
	bool isDead();
	void move(float x, float y);
	void afftiming();
};
