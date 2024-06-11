#include<SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <time.h>
#include<string>
#include <iostream>


using namespace std;
#include"level.h"
#include"menu.h"
#include"highscores.cpp"
const char title[] = "OOP-Project, Spring-2023";
using namespace sf;

class Game
{
public:
Sprite background; //Game background sprite
Texture bg_texture;
Player* p; //player
string s_temp = "LIVES:\n\t";
string s_temp2 = "SCORE:\n\t"; 
// add other game attributes
Menu men;

Text life,score,invinci,scores;
Font font;

SoundBuffer soundBuff2,soundBuff3,soundBuff4,soundBuff5,soundBuff6,soundBuff7;
Sound backg,shoot,explode,pickup,roar,damage,big_beam;

Enemy* boss;
bool b_monster =0,power_up =0,reset=0,b_dragon=0;
int rando,random;
float monster_timer=0,dragon_timer=0;

Bullet *bulls;
Bomb* bombs;
int temp_count=0,total_score=0,cool_down=28;
float respawn_timer=0;
int highscores[10]{0};

Add_On* add_on;

Level* lvl;


Game()
{


p=new Player("img/player_ship.png");
bg_texture.loadFromFile("img/background.jpg");
background.setTexture(bg_texture);
background.setScale(2, 1.5);
lvl = new Level;

soundBuff3.loadFromFile("sounds/shooting.wav");
shoot.setBuffer(soundBuff3);

soundBuff4.loadFromFile("sounds/explosion.wav");
explode.setBuffer(soundBuff4);
explode.setVolume(50);

soundBuff5.loadFromFile("sounds/pick_up.wav");
pickup.setBuffer(soundBuff5);

soundBuff6.loadFromFile("sounds/roar.wav");
roar.setBuffer(soundBuff6);

soundBuff7.loadFromFile("sounds/player_hurt.wav");
damage.setBuffer(soundBuff7);

soundBuff2.loadFromFile("sounds/theme.ogg");	
backg.setBuffer(soundBuff2);
backg.setVolume(65);
backg.setLoop(true);
backg.play();


font.loadFromFile("font/SaucerBB.ttf");

invinci.setFont(font);
invinci.setPosition(300,1);
invinci.setCharacterSize(30);
invinci.setString("INVINCIBLE");
invinci.setFillColor(Color::Yellow);

life.setFont(font);
life.setPosition(660,1);
life.setCharacterSize(30);
life.setFillColor(Color::Green);

score.setFont(font);
score.setPosition(10,1);
score.setCharacterSize(30);
score.setFillColor(Color::Red);

get_highscore(highscores);
}
void start_game()
{
    srand(time(0));
    RenderWindow window(VideoMode(780, 780), title);
    Clock clock;
    float timer=0;
    bool game_over = 1;
    while (window.isOpen())
    {
 		game_over = 1;
 		
    	men.display_menu(window,game_over,reset,highscores);
    	if(reset)		//resets information
    	{
    		if(p !=0)
    		{
    			delete p;
    			p=new Player("img/player_ship.png");
    		}
    		if(lvl != 0)
    		{
    			delete lvl;
    			lvl = new Level;
    		}
    		b_monster =0;
    		monster_timer=0;
    		game_over =0;
    		temp_count=0;
    		total_score=0;
    		respawn_timer=0;
    		p->lives = 3;
    	}
    	
    	while(!game_over && window.isOpen())
    	{
		    float time = clock.getElapsedTime().asSeconds(); 
		    clock.restart();
		    timer += time;
		    //cout<<time<<endl; 
	 		Event e;
		    while (window.pollEvent(e))
		    {  
		        if (e.type == Event::Closed) // If cross/close is clicked/pressed
		            window.close(); //close the game                        	    
		    }
				  
			if (Keyboard::isKeyPressed(Keyboard::Left)) //If left key is pressed
				    p->move("l");    // Player will move to left
			if (Keyboard::isKeyPressed(Keyboard::Right)) // If right key is pressed
				    p->move("r");  //player will move to right
			if (Keyboard::isKeyPressed(Keyboard::Up)) //If up key is pressed
				    p->move("u");    //playet will move upwards
			if (Keyboard::isKeyPressed(Keyboard::Down)) // If down key is pressed
				    p->move("d");  //player will move downwards

			if(Keyboard::isKeyPressed(Keyboard::Space) && temp_count>=cool_down) //have cooldown to stop crazy shooting plus to increase speed of shooting as game progresses
			{			
				shoot.play();
				p->fire();
				bulls = p->bullets;
				temp_count =0;
			}
			temp_count++;
			
			if(Keyboard::isKeyPressed(Keyboard::P))		//Pause
			{
				backg.pause();
				men.display_pause(window,game_over,highscores);
				backg.play();
			}
			///////////////////////////////////////////////
			/////  Call your functions here           /////
			//////////////////////////////////////////////
			p->update_bullets();
			p->process_add_ons(time);
			if(power_up)	//if powerup exists in game process it
			{
				if(p->add_on_collision(add_on->x,add_on->y,add_on))
				{
					if(add_on->type == 4)
					{
						total_score -=5;
						p->collision_detection(p->x,p->y);
					}
					else
						pickup.play();
					power_up =0;
				}
			}
			if(b_monster)	//processing monster if it exists
			{
				monster_timer += time;
				boss->check_and_fire(time);
				boss->movement();
				if(monster_timer >=40)
				{
					total_score += boss->score;
					delete boss;
					b_monster =0;
				}
				if(boss->shooting && !p->respawn && !p->invincible)
				{
					if(p->x < (boss->x+200) && p->x > (boss->x-10)) 
					{
						damage.play();
						p->collision_detection(p->x,p->y);
					}
				}
			}
			else if(b_dragon)	//processing dragon if it exists (both can't co-exist)
			{
				boss->x = p->x;
				dragon_timer +=time;
				boss->check_and_fire(time);
				if(dragon_timer>=20)
				{
					total_score += boss->score;
					delete boss;
					b_dragon =0;
				}
			}
			else				//else calculate odds for which a dragon/monster spawns
			{
				rando =1+rand()%3000;
				if(rando == 3)
				{
					boss = new Monster;
					b_monster = 1;
					monster_timer =0;	
				}
				if(rando == 4)
				{
					boss = new Dragon;
					b_dragon =1;
					dragon_timer=0;
					roar.play();
				}
			}
			
			if(!p->respawn && !p->invincible) //collision checks for invaders wont happen if player is invincible/respawning
			{
				if(!b_monster && !b_dragon)
				{
					for(int i=0;i<lvl->invader_count;i++)		//checks collisions on player
					{
						for(int j=0;j<lvl->wave[i]->bomb_count;j++)
						{
							if(p->collision_detection(lvl->wave[i]->bombs[j].x,lvl->wave[i]->bombs[j].y))
								damage.play();
						}
					}
				}
			}
			else if(p->respawn)		//updates respawn timer 
			{
				respawn_timer += time;
				if(respawn_timer >=3)
				{
					respawn_timer =0;
					p->respawn =0;
				}
			}
			
			if(p->lives <=0)		//game_over
			{
				update_highscore(highscores,total_score);
				break;
			}
			int temp_count=0;
			if(!b_monster && !b_dragon) //if dragon/monster not spawned, will process the regular level of invaders etc
			{
				lvl->update(time);
				while(temp_count < p->bullet_count)
				{
					if(lvl->collisions(p->bullets[temp_count].x,p->bullets[temp_count].y,total_score)) //collisions of bullets with invaders
					{
						explode.play();
						if(p->A_fire)		//will not delete bullets if fire powerup is on
						{
							temp_count++;
							continue;
						}
						p->delete_bullet(temp_count); //otherwise deletes bullets
						temp_count =0;
					}
					else
						temp_count++;
				}
				if(lvl->invader_count ==0)		//if all invaders killed, spawn next formation/level etc (also drops powerup)
				{
					random = 1+rand()%4;
					if(random == 1)
						add_on = new A_Life;	
					else if(random ==2)
						add_on = new A_Fire;
					else if(random==3)
						add_on = new A_Power;
					else
					{
						total_score += 5;
						add_on = new A_Danger;
					}
					if(cool_down>20)
						cool_down -=2;				//decreasing shooting cooldown
					power_up = 1;				//powerup exists
					lvl->wave_count++;			
					if(lvl->wave_count >3)
					{
						p->speed = 9;			//changing player's speed and as a result bullet's speed at next level
						if(lvl->level_no == 1)
							lvl->level_no++;
						lvl->wave_count=1;
					}
					if(lvl->level_no == 1)
						lvl->next_wave();
					else
						lvl->next_level();
				}
			}

			
			
			window.clear(Color::Black); //clears the screen
			window.draw(background);  // setting background
			window.draw(p->sprite);   // setting player on screen
			for(int i=0;i<p->bullet_count;i++)
			{
				window.draw(p->bullets[i].bull); //drawing all bullets
			}
			if(!b_monster && !b_dragon)		//will not draw invaders if monster/dragon exists
			{
				for(int i=0;i<lvl->invader_count;i++)
				{
					window.draw(lvl->wave[i]->sprit);	//drawing invaders
					for(int j=0;j<lvl->wave[i]->bomb_count;j++)
						window.draw(lvl->wave[i]->bombs[j].bom);		//drawing their bombs
				}
			}
			else
			{
				if(boss->shooting)			
					window.draw(boss->beam);		//draw the beam only if monster/dragon is shooting	
				if(b_dragon)
				{
					window.draw(boss->sprit2);
					window.draw(boss->sprit3);
				}
				window.draw(boss->sprit);			//draw monster itself
			}

			if(p->respawn ||p->invincible)			//draw text on top showing invincible
				window.draw(invinci);
			else if(p->A_fire)
			{
				invinci.setString("FIRE POWER-UP");
				window.draw(invinci);
				invinci.setString("INVINCIBLE");
			}
			
			if(power_up)							//if powerup exists move it and draw it
			{	
				add_on->move();
				window.draw(add_on->sprite);	
			}
			s_temp += to_string(p->lives);
			life.setString(s_temp);
			s_temp = "LIVES:\n\t";
			s_temp2 += to_string(total_score);
			score.setString(s_temp2);
			s_temp2 = "SCORE:\n\t";
			
			window.draw(score);
			window.draw(life);
			window.display();  //Displying all the sprites
		
		}
		window.draw(men.sprite); //drawing menu
		window.display();
	}
	save_score(highscores);		//writes highscores into file before closing 


}


};

