#include <SFML/Graphics.hpp>
#include<string.h>
#include"Add_On.h"
#include"bullet.h"
using namespace sf;

class Player{
public:

Texture tex;
Bullet* bullets;
int bullet_count,lives;
Sprite sprite;
float speed=7,add_on_timer =0;
int x,y;
bool respawn =0,add_on =0,A_fire=0,invincible =0;


Add_On* power=0;

Player(std::string png_path)
{
	bullet_count =0;
	lives = 3;
	tex.loadFromFile(png_path);
	sprite.setTexture(tex);
	x=340;y=700;
	sprite.setPosition(x,y);
	sprite.setScale(0.75,0.75);
}

void process_add_ons(float t)			//deals with any add ons (takes time as parameter for the time related power-ups)
{
	if(!add_on)
		return;
	if(power->type == 1)				//fire add on
	{
		add_on_timer += t;
		A_fire = 1;
		if(add_on_timer>=5)
		{
			A_fire =0;
			delete power;
			add_on =0;
			add_on_timer = 0;
		}
	}
	else if(power->type == 2)			//lives add on
	{
		lives++;
		delete power;
		add_on =0;
		add_on_timer=0;
	}
	else if(power->type == 3)			//invincible super power up
	{
		add_on_timer += t;
		invincible = 1;
		if(add_on_timer>=5)
		{
			invincible =0;
			delete power;
			add_on =0;
			add_on_timer = 0;
		}
	}
	else								//danger sign (no processing needed)
	{
		delete power;
		add_on=0;
		add_on_timer=0;
	}
}

void delete_bullet(int index)			//deletes bullet of said index
{
	if(bullet_count-1 > 0)
	{
		Bullet* temp = bullets;
		bullets = new Bullet[--bullet_count];
		for(int i=0,j=0;i<bullet_count+1,j<bullet_count;i++)
		{
			if(i == index)
				continue;
			bullets[j] = temp[i];
			j++;
		}
	}
	else
		--bullet_count;
}


void update_bullets()					//moves all bullets + deletes bullets that go out of range
{
	if(bullet_count != 0)
	{
		for(int i=0;i<bullet_count;i++)
		{	
			bullets[i].move_speed = speed*1.5;
			bullets[i].move();
		}
		int count =0;
		while(count < bullet_count)
		{
			if(bullets[count].y < -10)
			{
				this->delete_bullet(count);
				if(bullet_count == 0)
					break;
				count = 0;
			}
			else
				count++;
		}
	}
}



void fire()								//fires a bullet
{
	if(bullet_count ==0)
	{
		bullets = new Bullet;
		bullets->x = x+32;
		bullets->y = y-40;
		bullets->bull.setPosition(x+32,y-40);
		bullet_count++;
		bullets->move_speed = speed*1.5;
	}
	else
	{
		Bullet* temp;
		temp = bullets;
		bullets = new Bullet[++bullet_count];
		for(int i=0;i<bullet_count;i++)
		{
			bullets[i].x = temp[i].x;
			bullets[i].y = temp[i].y;
			bullets[i].bull.setPosition(temp[i].x,temp[i].y);
		}
		bullets[bullet_count-1].x = x+32;
		bullets[bullet_count-1].y = y-40;
		bullets[bullet_count-1].bull.setPosition(x+32,y-40);
		bullets[bullet_count-1].move_speed = speed*1.5;
		/*if(bullet_count == 2)
			delete temp;
		else
			delete[]temp;*/
	}
}

bool collision_detection(int xx,int yy)				//collision detection of player with bombs
{
	bool temp1=0,temp2=0;
	if(xx>x-13 && xx<x+99)
		temp1 = 1;
	if(yy>y-10 && yy<y+10)
		temp2 = 1;
	if(temp1 && temp2)
	{
		lives--;
		respawn = 1;
		sprite.setPosition(340,700);
		x = 340;
		y = 700;
		return 1;
	}
	return 0;
}

bool add_on_collision(int xx,int yy,Add_On* add)	//checks add on collisions
{
	bool temp1=0,temp2=0;
	if(xx>x-13 && xx<x+99)
		temp1 = 1;
	if(yy>y-10 && yy<y+10)
		temp2 = 1;
	if(temp1 && temp2)
	{
		power = add;
		add_on =1;
		return 1;
	}
	return 0;
}

void move(std::string s){
float delta_x=0,delta_y=0;
if(s=="l")
	delta_x -=1;//move the player left
else if(s=="r")
	delta_x +=1;//move the player right
if(s=="u")
	delta_y=-1;
else if(s=="d")
	delta_y=1;

delta_x*=speed;
delta_y*=speed;

x += delta_x;
y += delta_y;
bool out_of_bounds=0;
//for wrap-around display
if(x<0 && y<0)			
{
	x=779;
	y=779;
	out_of_bounds =1;
}
else if(x>780 && y>780)
{
	x=1;
	y=1;
	out_of_bounds =1;
}
else if(x>780 && y<0)
{
	x=1;
	y=779;
	out_of_bounds =1;
}
else if(y>780 && x<0)
{
	y=1;
	x=779;
	out_of_bounds =1;
}
else if(x >780)
{
	x=1;
	out_of_bounds = 1;
}
else if(x < 0)
{
	x=779;
	out_of_bounds = 1;
}
else if(y >780)
{
	y=1;
	out_of_bounds = 1;
}
else if(y < 0)
{
	y=779;
	out_of_bounds = 1;	
}
if(out_of_bounds)
	sprite.setPosition(x,y);
else
	sprite.move(delta_x, delta_y);

}

};
