#include<bits/stdc++.h>
#include<conio.h>
using namespace std;

bool gameOver;
//Dimensions of map
const int height=20;
const int width=20;
// variables for head position
int x,y;
//Variables for fruit position
int fruitX, fruitY;
int score;
//Enumerator for tracking the position of snake
enum eDirection { STOP=0, LEFT, RIGHT, UP, DOWN};
eDirection dir; // To hold the direction of the snake

int tailX[100], tailY[100];
int ntail;


void setup()
{
	gameOver=false;
	dir= STOP;
	
	//Center the snake head on the map
	x=width/2; 
	y=height/2;
	// To locate the fruits randonmly at any place b/w 0 to width-1 and 0 to height-1
	fruitX= rand()%width;
	fruitY= rand()%height;
	score=0;
}
void draw()
{
	system("cls"); // To clear screen
	// Displaying the top border of our map
	for(int i=0; i<width; i++)
	{
		cout<<"#";
	}
	cout<<endl;
	for(int i=0; i<height; i++)
	{
		for(int j=0; j<width; j++)
		{
			if(j==0 || j==width-1)
			{
				cout<<"#";
			}
			else
			{
				if(i==y && j==x)
				{
					cout<<"O";  // Head is denoted by "0"
				}
				else if(i==fruitY && j==fruitX)
				{
					cout<< "F";
				}
				else
				{
					bool print=false;
					for(int k=0; k<ntail; k++)
					{
						if(tailX[k]==j && tailY[k]==i)
						{
							cout<<"o";
							print=true;
						}
					}
					if(!print)
						cout<<" ";	
				}
			}
		}
		cout<<endl;
	}
	for(int i=0; i<width; i++)
	{
		cout<<"#";
	}
	cout<<endl;
	
	cout<< "SCORE:"<< score<<endl;
}
void input()
{
	if(_kbhit())
	{
		switch(_getch())
		{
			case 'a' :
				dir=LEFT;
				break;
			
			case 'd':
				dir=RIGHT;
				break;
			
			case 'w':
				dir=UP;
				break;
			
			case 's':
				dir=DOWN;
				break;
				
			case 'x':
				gameOver=true;
				break;
		}
	}
}
void logic()
{
	int prevX= tailX[0];
	int prevY= tailY[0];
	int prev2X, prev2Y;
	tailX[0]=x;
	tailY[0]=y;
	for(int i=1; i<ntail; i++)
	{
		prev2X= tailX[i];
		prev2Y= tailY[i];
		tailX[i]=prevX;
		tailY[i]=prevY;
		prevX=prev2X;
		prevY=prev2Y;
	}
	switch(dir)
	{
		case LEFT:
			x--;
			break;
			
		case RIGHT:
			x++;
			break;
			
		case UP:
			y--;
			break;
		
		case DOWN:
			y++;
			break;
			
		default:
			break;
		
	}
	if(x>width || x<0 || y>height || y<0)
	{
		gameOver=true;
	}
	
	//To terminate the game if the head touches the tail
	for(int i=0; i<ntail; i++)
	{
		if(x==tailX[i] && y==tailY[i])
		{
			gameOver=true;
		}
	}
	// Things to do if our snake eats a fruit
	if(x==fruitX && y==fruitY)
	{
		ntail++;
		score+=10;
		fruitX= rand()%width;
		fruitY= rand()%height;
	}
}

int main()
{
	setup();
	while(!gameOver)
	{
		draw();
		input();
		logic();
	}
}
