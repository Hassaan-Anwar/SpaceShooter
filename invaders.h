#include <SFML/Graphics.hpp>
#include<string.h>
#include"monster.h"


class Alpha: public Invader
{
public:
	Alpha(int xx,int yy)
	{
		tex.loadFromFile("img/enemy_1.png");
		sprit.setTexture(tex);
		sprit.setPosition(xx,yy);
		x = xx;
		y = yy;
		interval = 5;
		sprit.setScale(0.75,0.75);
		score = 10;
	}
	void check_and_fire(float t=0)
	{
		if(time >= interval)
		{
			this->fire_bomb();
			time = 0;
		}
	}
	
};

class Beta: public Invader
{
public:
	Beta(int xx,int yy)
	{
		tex.loadFromFile("img/enemy_2.png");
		sprit.setTexture(tex);
		sprit.setPosition(xx,yy);
		x = xx;
		y = yy;
		interval = 3;
		sprit.setScale(0.65,0.65);
		score = 20;
	}
	void check_and_fire(float t=0)
	{
		if(time >= interval)
		{
			this->fire_bomb();
			time = 0;
		}
	}
};

class Gamma: public Invader
{
public:
	Gamma(int xx,int yy)
	{
		tex.loadFromFile("img/enemy_3.png");
		sprit.setTexture(tex);
		sprit.setPosition(xx,yy);
		x = xx;
		y = yy;
		interval = 2;
		sprit.setScale(0.55,0.55);
		score = 30;
	}
	void check_and_fire(float t=0)
	{
		if(time >= interval)
		{
			this->fire_bomb();
			time = 0;
		}
	}
};
