#include <SFML/Graphics.hpp>
#include<string.h>
using namespace sf;

class Bomb
{
public:
	Sprite bom;
	int x,y;
	float move_speed;
	Texture tex;
	Bomb()
	{
		tex.loadFromFile("img/enemy_laser.png");
		bom.setTexture(tex);
		move_speed = 4;
	}
	
	void move()
	{
		y += move_speed;
		bom.move(0,move_speed);	
	}
};
