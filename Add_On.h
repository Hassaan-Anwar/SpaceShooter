#include <SFML/Graphics.hpp>
#include<string.h>
#include<ctime>
using namespace sf;


class Add_On
{
public:
	Sprite sprite;
	Texture tex;
	int x,y,type;
	float speed = 4;
	void move()
	{
		sprite.move(0,speed);
		y += speed;
	}
};


class A_Fire: public Add_On
{
public:
	A_Fire()
	{
		srand(time(0));
		tex.loadFromFile("img/things_silver.png");
		sprite.setTexture(tex);
		x = 10+rand()%700;
		y = 10;
		type =1;
		sprite.setPosition(x,y);
	}
};

class A_Life: public Add_On
{
public:
	A_Life()
	{
		srand(time(0));
		tex.loadFromFile("img/pill_green.png");
		sprite.setTexture(tex);
		x = 10+rand()%700;
		y = 10;
		type = 2;
		sprite.setPosition(x,y);
		sprite.setScale(1.5,1.5);
	}
};

class A_Power: public Add_On
{
public:
	A_Power()
	{
		srand(time(0));
		tex.loadFromFile("img/star_gold.png");
		sprite.setTexture(tex);
		x = 10+rand()%700;
		y = 10;
		type = 3;
		sprite.setPosition(x,y);
	}
};

class A_Danger: public Add_On
{
public:
	A_Danger()
	{
		srand(time(0));
		tex.loadFromFile("img/powerupRed.png");
		sprite.setTexture(tex);
		x = 10+rand()%700;
		y = 10;
		type = 4;
		speed = 3;
		sprite.setScale(1.5,1.5);
		sprite.setPosition(x,y);
	}
};
