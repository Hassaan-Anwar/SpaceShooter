#include <SFML/Graphics.hpp>
#include"enemy.h"
#include<string.h>


class Monster: public Enemy
{
public:
	float shooting_time=0,cooldown=0;
	Texture tex2;
	Monster()
	{
		tex2.loadFromFile("img/laserGreen08.png");
		beam.setTexture(tex2);
		beam.setScale(8,16);
		
		tex.loadFromFile("img/monster.png");
		sprit.setTexture(tex);
		sprit.setScale(0.2,0.2);
		sprit.setPosition(350,50);
		x=350;
		y=50;
		move_speed = 2;
		score = 40;
		
		soundbuff.loadFromFile("sounds/big_beam.wav");
		shoot.setBuffer(soundbuff);
	}
	
	void check_and_fire(float t=0)			//fires at alternate times 
	{
		if(!shooting)
		{
			cooldown += t;
			if(cooldown >=2)
			{
				shooting =1;
				shoot.play();
				cooldown=0;
			}
		}
		else
		{
			shooting_time += t;
			beam.setPosition(x+80,y+150);
			if(shooting_time>=6)
			{
				shooting = 0;
				shooting_time =0;
			}
		}	
	}
	
	void movement()							//moves left and right
	{
		sprit.move(move_speed,0);
		x+= move_speed;
		if(x >525|| x < 4)
		{
			move_speed *= -1;
		}
	}
	
};

class Dragon: public Enemy
{
public:
	Texture tex2;
	float timer=0;
	Dragon()
	{
		tex.loadFromFile("img/dragon2.png");
		sprit.setTexture(tex);
		sprit.setScale(0.6,0.6);
		sprit.setPosition(180,10);
		tex2.loadFromFile("img/laserRed04.png");
		beam.setTexture(tex2);
		
		tex3.loadFromFile("img/dragon1.png");
		sprit2.setTexture(tex3);
		sprit3.setTexture(tex3);
		
		
		sprit2.setPosition(5,200);
		sprit3.setPosition(550,200);
		
		x= -1000;
		y = -1000;
		score = 50;
		shooting =0;
		
		soundbuff.loadFromFile("sounds/big_beam.wav");
		shoot.setBuffer(soundbuff);
		shoot.setLoop(1);
	}
	
	void movement(){}			//dragons dont move (in this game atleast)
	
	void check_and_fire(float t=0)		//checks location of player and fires accordingly
	{
		timer += t;
		if(shooting)
			return;
		if(timer<5)
			return;
		else
		{
			shoot.play();
			shooting = 1;
		}
		if(x < 260)
		{
			beam.setPosition(110,400);
			beam.setScale(2,15);
			x= 110;
			y= 400;
		
		}
		else if(x >520)
		{
			beam.setPosition(660,400);
			beam.setScale(2,15);
			x = 660;
			y= 400;
		}
		else
		{
			beam.setPosition(350,260);
			beam.setScale(2,15);
			x = 350;
			y= 260;
		}
		
	}
};
