#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include<string.h>
#include<iostream>
#include"bomb.h"
using namespace sf;
using namespace std;

class Enemy
{
public: 
	SoundBuffer soundbuff;
	Sound shoot;
	Sprite sprit,sprit2,sprit3,beam;
	Texture tex,tex3;
	int x,y;
	float move_speed;
	int score;
	bool shooting=0;
	
	virtual void check_and_fire(float t=0) =0;
	virtual void movement()=0;
};


class Invader: public Enemy
{
public:	
	Bomb* bombs;
	int bomb_count =0,interval;
	float time = 0;
	
	void movement(){}
	
	void update_time(float t)		//updates the time for interval check
	{
		time += t;
	}
	
	void update_bombs()			//movement of bombs
	{
		for(int i=0;i<bomb_count;i++)
			bombs[i].move();
	}
	
	bool collision_detection(int xx,int yy)	//detecting collision
	{
		bool temp1=0,temp2=0;
		if(xx>x-13 && xx<x+99)
			temp1 = 1;
		if(yy>y-10 && yy<y+10)
			temp2 = 1;
		if(temp1 && temp2)
			return 1;
		return 0;
	}
	
	void fire_bomb()			//fires a bombs 
	{
		if(bomb_count ==0)
		{
			bombs = new Bomb;
			bombs->x = x+31;
			bombs->y = y+45;
			bombs->bom.setPosition(x+31,y+45);
			bomb_count++;
		}
		else
		{
			Bomb* temp;
			temp = bombs;
			bombs = new Bomb[++bomb_count];
			for(int i=0;i<bomb_count;i++)
			{
				bombs[i].x = temp[i].x;
				bombs[i].y = temp[i].y;
				bombs[i].bom.setPosition(temp[i].x,temp[i].y);
			}
			bombs[bomb_count-1].x = x+31;
			bombs[bomb_count-1].y = y+45;
			bombs[bomb_count-1].bom.setPosition(x+31,y+45);
			if(bomb_count == 2)
				delete temp;
			else
				delete[]temp;
		}
	}
};
