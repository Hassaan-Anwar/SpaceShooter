#include<string>
#include <SFML/Graphics.hpp>
#include"player.h"
using namespace sf;

class Menu{
public:
Sprite sprite,help,paused,high;
Texture tex,tex2,tex3,tex4;
Text scores;
Font font;
SoundBuffer soundBuff;
Sound choice;
//add menu attributes here
Menu()
{
tex.loadFromFile("img/Main_Menu_Final.png");
tex2.loadFromFile("img/Instructions.png");
tex3.loadFromFile("img/Paused.png");
tex4.loadFromFile("img/highscores.png");

soundBuff.loadFromFile("sounds/choice.wav");
choice.setBuffer(soundBuff);

font.loadFromFile("font/SaucerBB.ttf");
scores.setFont(font);
scores.setPosition(350,100);
scores.setCharacterSize(60);
scores.setFillColor(Color::Red);

high.setTexture(tex4);
high.setScale(1,1.3);

paused.setTexture(tex3);
paused.setScale(1,1.3);

help.setTexture(tex2);
help.setScale(1,1.3);

sprite.setTexture(tex);
sprite.setScale(1,1.3);
//constructors body
}

void display_menu(RenderWindow& window,bool& game_over,bool& reset,int highscores[])
{
	while(window.isOpen())
	{
		Event f;
		while(window.pollEvent(f))
    		if(f.type == Event::Closed)
    			window.close();
    			
    	if(Keyboard::isKeyPressed(Keyboard::Num1))		//starts game/ resets information incase it is called mid-game through pause
    	{
    		choice.play();
			reset =1;
			game_over =0;
			break;
    	}
    	else if(Keyboard::isKeyPressed(Keyboard::Num2))	//highscores display
    	{
    		choice.play();
    		string temp;
    		for(int i=0;i<9;i++)
    		{
    			temp += to_string(highscores[i]);
    			temp+='\n';
    		}
			scores.setString(temp);
    		while(!Keyboard::isKeyPressed(Keyboard::Escape))
    		{

    			Event x;
    			while(window.pollEvent(x))
    				if(x.type == Event::Closed)
    					window.close();
    			window.draw(high);
    			window.draw(scores);		
    			window.display();
    		}
    		choice.play();
    		break;
    	}
    	else if(Keyboard::isKeyPressed(Keyboard::Num3))	//intructions screen
    	{
    		choice.play();
    		while(!Keyboard::isKeyPressed(Keyboard::Escape))
    		{
    			Event g;
    			while(window.pollEvent(g))
    				if(g.type == Event::Closed)
    					window.close();
    			window.draw(help);
    			window.display();
    		}
    		choice.play();
    		break;
    	}
    	else if(Keyboard::isKeyPressed(Keyboard::Num5))	//closes (choose 5 as options as in pause 4 is exit to main menu and if you press that it closes the game directly cuz inputs)
    		window.close();
    	window.draw(sprite);
    	window.display();
   }			
}

void display_pause(RenderWindow& window,bool& game_over,int highscores[])
{
	while(window.isOpen())
	{
		Event g;
		while(window.pollEvent(g))
    		if(g.type == Event::Closed)
    			window.close();
		if(Keyboard::isKeyPressed(Keyboard::Num1))	//resume option
		{
			choice.play();
    		break;
    	}
    	else if(Keyboard::isKeyPressed(Keyboard::Num2))	//highscore display
    	{
    		choice.play();
    		string temp;
    		for(int i=0;i<9;i++)
    		{
    			temp += to_string(highscores[i]);
    			temp+='\n';
    		}
			scores.setString(temp);
    		while(!Keyboard::isKeyPressed(Keyboard::Escape))
    		{

    			Event x;
    			while(window.pollEvent(x))
    				if(x.type == Event::Closed)
    					window.close();
    			window.draw(high);
    			window.draw(scores);		
    			window.display();
    		}
    		choice.play();
    	}
    	
    	else if(Keyboard::isKeyPressed(Keyboard::Num3))	//instructions
    	{
    		choice.play();
    		while(!Keyboard::isKeyPressed(Keyboard::Escape))
    		{
    			Event x;
    			while(window.pollEvent(x))
    				if(x.type == Event::Closed)
    					window.close();
    			window.draw(help);
    			window.display();
    		}
    		choice.play();
    	}
    	else if(Keyboard::isKeyPressed(Keyboard::Num4))	//returns to main menu
    	{
    		choice.play();
			game_over=1;
    		break;
    	}
    	window.draw(paused);
		window.display();
	}
}

};
