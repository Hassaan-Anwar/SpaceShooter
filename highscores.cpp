#include<fstream>

void update_highscore(int highscore[],int score)			//sorting the highscore array
{	
	int i,j,temp;
	if (score > highscore[9])
	{
		highscore[9] = score;		
		for (i=0; i<10; i++)
		{
			for (int j=0; j<9-i; j++)
				if (highscore[j] < highscore[j+1])
				{
					temp = highscore[j];
					highscore[j] = highscore[j+1];
					highscore[j+1] = temp;
				}	
		}
	}
}

void get_highscore(int highscore[])				//getting highscores from file
{
	int index = 0;
	std::ifstream scores;
	scores.open("scores.txt");
	while(!scores.eof())
	{
		scores>>highscore[index];
		index++;
	}
	scores.close();
}


void save_score(int highscore[])				//writing the highscores back into file
{
	std::ofstream scores;
	scores.open("scores.txt");
 	for(int i=0;i<10;i++)
 		scores<<highscore[i]<<'\n';
	scores.close();
}
