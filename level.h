#include<time.h>
#include"invaders.h"
#include<iostream>
using namespace std;
class Level
{
public:
	Invader**wave;
	int invader_count,wave_count,level_no;
	bool over;
	Level()
	{
		level_no =1;
		wave_count =1;
		srand(time(0));
		wave = new Invader*[12];
		int ran,x=40;
		invader_count = 12;
		
		for(int i=0;i<5;i++)	//top row of rectangle
		{
			ran = rand()%3;
			if(ran == 0)
				wave[i] = new Alpha(40+(i*160),75);
			else if(ran == 1)
				wave[i] = new Beta(40+(i*160),75);
			else
				wave[i] = new Gamma(40+(i*160),75);
		}
		
		ran = rand()%3;			//left col of rectangle
		if(ran == 0)
			wave[5] = new Alpha(40,75+160);
		else if(ran == 1)
			wave[5] = new Beta(40,75+160);
		else
			wave[5] = new Gamma(40,75+160);
			
			
		for(int i=6;i<11;i++)	//bottom row of rectangle
		{
			ran = rand()%3;
			if(ran == 0)
				wave[i] = new Alpha(40+((i-6)*160),75+(160*2));
			else if(ran == 1)
				wave[i] = new Beta(40+((i-6)*160),75+(160*2));
			else
				wave[i] = new Gamma(40+((i-6)*160),75+(160*2));
		}
		
		ran = rand()%3;			//right col of rectangle
		if(ran == 0)
			wave[11] = new Alpha(40+(160*4),75+160);
		else if(ran == 1)
			wave[11] = new Beta(40+(160*4),75+160);
		else
			wave[11] = new Gamma(40+(160*4),75+160);
		
	}
	
	void next_wave()
	{
		srand(time(0));
		int ran;
		if(wave_count ==2)						//cross sign
		{
			Invader** temp = new Invader*[9];
			invader_count = 9;
			for(int i=0;i<5;i++)				//1 diagonal of cross
			{
				ran = rand()%3;
				if(ran == 0)
					temp[i] = new Alpha(150+(i*100),50+(i*100));
				else if(ran == 1)
					temp[i] = new Beta(150+(i*100),50+(i*100));
				else
					temp[i] = new Gamma(150+(i*100),50+(i*100));
			}
			int tx = 350;
			int ty = 250;
			int x,y;
			int count = 5;
			int t_count =0;
			while(count<9)						//second diagonal cross
			{
				x = 550 - ((t_count)*100);
				y = 50+((t_count)*100);
				
				t_count++;
				if(x == tx && y == ty)			//to not overlap at center
					continue;
				ran = rand()%3;
				if(ran == 0)
					temp[count] = new Alpha(x,y);
				else if(ran == 1)
					temp[count] = new Beta(x,y);
				else
					temp[count] = new Gamma(x,y);
				count++;
			}
			wave = temp;
		}
		else
		{
			Invader** temp = new Invader*[12];		//triangle 
			invader_count = 12;
			ran = rand()%3;
			if(ran == 0)							//top part
				temp[0] = new Alpha(350,40);
			else if(ran == 1)
				temp[0] = new Beta(350,40);
			else
				temp[0] = new Gamma(350,40);
			for(int i=1;i<3;i++)					//1 diagonal
			{
				int x = 250 - ((i-1)*100);
				int y = 140 + ((i-1)*100);
				ran = rand()%3;
				if(ran == 0)
					temp[i] = new Alpha(x,y);
				else if(ran == 1)
					temp[i] = new Beta(x,y);
				else
					temp[i] = new Gamma(x,y);
			}
			for(int i=3;i<6;i++)					//second diagonal
			{
				int x = 450 + ((i-3)*100);
				int y = 140 + ((i-3)*100);
				ran = rand()%3;
				if(ran == 0)
					temp[i] = new Alpha(x,y);
				else if(ran == 1)
					temp[i] = new Beta(x,y);
				else
					temp[i] = new Gamma(x,y);
			}
			for(int i=6;i<12;i++)					//bottom line
			{
				int x = 50 + ((i-6)*100);
				int y = 340;
				ran = rand()%3;
				if(ran == 0)
					temp[i] = new Alpha(x,y);
				else if(ran == 1)
					temp[i] = new Beta(x,y);
				else
					temp[i] = new Gamma(x,y);
			
			}
			wave = temp;
		}
	}
	void next_level()
	{
		srand(time(0));
		int ran,x,y;
		if(wave_count ==1)
		{
			Invader** temp = new Invader*[8];
			invader_count = 8;
			for(int i=0;i<3;i++)					//first diagonal of diamond
			{
				x = 350-(i*100);
				y = 50+(i*100);
				ran = rand()%3;
				if(ran == 0)
					temp[i] = new Alpha(x,y);
				else if(ran == 1)
					temp[i] = new Beta(x,y);
				else
					temp[i] = new Gamma(x,y);
			}
			for(int i=3;i<5;i++)					//second diagonal
			{
				x=250+((i-3)*100);
				y=350+((i-3)*100);
				ran = rand()%3;
				if(ran == 0)
					temp[i] = new Alpha(x,y);
				else if(ran == 1)
					temp[i] = new Beta(x,y);
				else
					temp[i] = new Gamma(x,y);
			}
			for(int i=5;i<7;i++)					//third diagonal
			{
				x=350+((i-4)*100);
				y=450-((i-4)*100);
				ran = rand()%3;
				if(ran == 0)
					temp[i] = new Alpha(x,y);
				else if(ran == 1)
					temp[i] = new Beta(x,y);
				else
					temp[i] = new Gamma(x,y);
			}
			ran = rand()%3;
			if(ran == 0)
				temp[7] = new Alpha(450,150);
			else if(ran == 1)
				temp[7] = new Beta(450,150);
			else
				temp[7] = new Gamma(450,150);	
			
			wave = temp;
		}
		
	}
	
	void update(float time)							//updates all invaders in terms of shooting etc
	{
		for(int i=0;i<invader_count;i++)
		{
			wave[i]->update_time(time);
			wave[i]->check_and_fire();
			wave[i]->update_bombs();
		}
	}
	
	void delete_enemy(int index)					//removes enemy of index i
	{
		Invader** temp = wave;
		wave = new Invader*[--invader_count];
		
		for(int i=0,j=0;i<invader_count+1,j<invader_count;i++)
		{
			if(i==index)
				continue;
			wave[j] = temp[i];
			j++;
		}
		delete temp[index];
	}
	
	bool collisions(int xx,int yy,int& t_score)		//checking collision for all invaders
	{
		for(int i=0;i<invader_count;i++)
		{
			if(wave[i]->collision_detection(xx,yy))
			{
				t_score += level_no*wave[i]->score;
				this->delete_enemy(i);
				return 1;
			}
		}
		return 0;
	}
};
