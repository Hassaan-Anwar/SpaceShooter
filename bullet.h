#include <SFML/Graphics.hpp>
#include<string.h>
using namespace sf;

class Bullet
{
public:
	Sprite bull;
	int x,y;
	float move_speed;
	Texture laser;
	Bullet()
	{
		laser.loadFromFile("img/laserBlue16.png");
		bull.setTexture(laser);
		move_speed = 8;
	}
	
		
		
	
	void move()
	{
		y -= move_speed;
		bull.move(0,-move_speed);	
	}
};
