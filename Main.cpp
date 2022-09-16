/*
*	控制台小游戏《贪吃蛇》
*	作者：BBBAN_
*	QQ: 2260473283
*	最后修改日期：2022/4/19
*/
#include<windows.h>
#include<iostream>
#include<vector>
#include<conio.h>
#include<ctime>
using namespace std;

int food_x;	//食物X坐标
int food_y;	//食物Y坐标

			//设置光标坐标
void gotoxy(int x,int y)
{
	COORD pos;
	pos.X = x;
	pos.Y = y;
	HANDLE handle;
	handle = GetStdHandle(STD_OUTPUT_HANDLE);	
	SetConsoleCursorPosition(handle, pos);	
}
//30 X 25 大小的地图
void map()
{
	gotoxy(83, 10);
	cout << "欢迎使用《贪吃蛇》~" << endl;
	gotoxy(70, 13);
	cout << "============================================" << endl;
	gotoxy(70, 14);
	cout << "=\t\t   游戏规则如下：\t\t =" << endl;
	gotoxy(70, 15);
	cout << "=\t  您可以操作按键:↑↓←→来控制蛇移动\t =" << endl;
	gotoxy(70, 16);
	cout << "= 吃到食物后，会增加得分并且蛇的长度会增加 =" << endl;
	gotoxy(70, 17);
	cout << "=\t   触碰到墙壁或者咬到自身就会失败哦！\t =" << endl;
	gotoxy(70, 18);
	cout << "============================================" << endl;

	for (int i = 0; i < 60; i++)	//绘制X方向 1
	{
		gotoxy(i, 0);
		cout << "墙";
	}
	for (int j = 1; j < 25; j++)	//绘制Y方向
	{
		gotoxy(0, j);
		cout << "墙";
		gotoxy(60, j);
		cout << "墙";
	}
	for (int i = 0; i < 60; i++)	//绘制X方向 2
	{
		gotoxy(i, 25);
		cout << "墙";
	}

	gotoxy(100, 22);
	cout << "作者：BBBAN_" << endl;
}

enum direction { UP, DOWN, LEFT, RIGHT };

struct snake	//上下相隔1，左右相隔2
{
	int x;
	int y;
	int direction = RIGHT;
};

int score(const vector<snake>& s);

void judge(const vector<snake>& s)
{
	if (s[0].y == 25 || s[0].x == 60 || s[0].y == 0 || s[0].x == 0)
	{
		system("pause");
		system("cls");
		gotoxy(25, 5);
		cout << "你撞墙啦！" << endl;
		gotoxy(25, 6);
		cout << "最终得分："<< score(s) << endl;
		gotoxy(25, 7);
		cout << "游戏结束！" << endl;
			gotoxy(21, 8);
		cout << "按任意键退出游戏" << endl;
		system("pause");
		exit(0);
	}
	for (int i = 1; i < s.size(); i++)
	{
		if (s[0].x == s[i].x && s[0].y == s[i].y)
		{
			system("pause");
			system("cls");
			gotoxy(21, 5);
			cout << "你咬到自己的尾巴啦！" << endl;
			gotoxy(25, 6);
			cout << "最终得分：" << score(s) << endl;
			gotoxy(25, 7);
			cout << "游戏结束！" << endl;
			gotoxy(21, 8);
			cout << "按任意键退出游戏" << endl;
			system("pause");
			exit(0);
		}
	}
}

void initGame(vector<snake>& s)
{
	snake snk;
	s.push_back(snk);
	s[0].x = 10;
	s[0].y = 10;
}

void drawSnake(const vector<snake>& s)
{
	gotoxy(s[0].x, s[0].y);
	cout << "头";
	for (int i = 1; i < s.size(); i++)
	{
		gotoxy(s[i].x, s[i].y);
		cout << "身";
	}
}

void moveSnake(vector<snake>& s)
{
	if (s[0].direction == UP)
	{
		gotoxy(s[s.size() - 1].x, s[s.size() - 1].y);
		cout << "  ";
		for (int i = s.size() - 1; i > 0; i--)
		{
			s[i].x = s[i - 1].x;
			s[i].y = s[i - 1].y;
		}
		s[0].y -= 1;
	}
	else if (s[0].direction == DOWN)
	{
		gotoxy(s[s.size() - 1].x, s[s.size() - 1].y);
		cout << "  ";
		for (int i = s.size() - 1; i > 0; i--)
		{
			s[i].x = s[i - 1].x;
			s[i].y = s[i - 1].y;
		}
		s[0].y += 1;
	}
	else if (s[0].direction == LEFT)
	{
		gotoxy(s[s.size() - 1].x, s[s.size() - 1].y);
		cout << "  ";
		for (int i = s.size() - 1; i > 0; i--)
		{
			s[i].x = s[i - 1].x;
			s[i].y = s[i - 1].y;
		}
		s[0].x -= 2;
	}
	else
	{
		gotoxy(s[s.size() - 1].x, s[s.size() - 1].y);
		cout << "  ";
		for (int i = s.size() - 1; i > 0; i--)
		{
			s[i].x = s[i - 1].x;
			s[i].y = s[i - 1].y;
		}
		s[0].x += 2;
	}
	if(_kbhit())
	{
		if (GetAsyncKeyState(VK_UP))
		{
			if (s[0].direction != DOWN && s[0].direction != UP)
			{
				s[0].direction = UP;
				gotoxy(s[s.size() - 1].x, s[s.size() - 1].y);
				cout << "  ";
				for (int i = s.size() - 1; i > 0; i--)
				{
					s[i].x = s[i - 1].x;
					s[i].y = s[i - 1].y;
				}
				s[0].y -= 1;
			}
		}
		else if (GetAsyncKeyState(VK_DOWN))
		{
			if (s[0].direction != UP && s[0].direction != DOWN)
			{
				s[0].direction = DOWN;
				gotoxy(s[s.size() - 1].x, s[s.size() - 1].y);
				cout << "  ";
				for (int i = s.size() - 1; i > 0; i--)
				{
					s[i].x = s[i - 1].x;
					s[i].y = s[i - 1].y;
				}
				s[0].y += 1;
			}
		}
		else if (GetAsyncKeyState(VK_LEFT))
		{
			if (s[0].direction != RIGHT && s[0].direction != LEFT)
			{
				s[0].direction = LEFT;
				gotoxy(s[s.size() - 1].x, s[s.size() - 1].y);
				cout << "  ";
				for (int i = s.size() - 1; i > 0; i--)
				{
					s[i].x = s[i - 1].x;
					s[i].y = s[i - 1].y;
				}
				s[0].x -= 2;
			}
		}
		else if(GetAsyncKeyState(VK_RIGHT))	
		{
			if (s[0].direction != LEFT && s[0].direction != RIGHT)
			{
				s[0].direction = RIGHT;
				gotoxy(s[s.size() - 1].x, s[s.size() - 1].y);
				cout << "  ";
				for (int i = s.size() - 1; i > 0; i--)
				{
					s[i].x = s[i - 1].x;
					s[i].y = s[i - 1].y;
				}
				s[0].x += 2;
			}
		}
	}
}

void food()
{
	srand(time(0));
	food_x = ((rand() % 25)+3) * 2;
	food_y = (rand() % 20) + 3;
	gotoxy(food_x, food_y);
	cout << "饭";
}

void runGame(vector<snake>& s)
{
	food();
	while (true)
	{
		gotoxy(food_x, food_y);
		cout << "饭";

		gotoxy(83, 8);
		cout << "当前得分 ："<< score(s) << endl;

		if (s[0].x == food_x && s[0].y == food_y)
		{
			food();
			snake snk;
			s.push_back(snk);
		}
		moveSnake(s);
		drawSnake(s);
		judge(s);
		Sleep(100);
	}
}

void startGame()
{
	vector<snake> s;
	initGame(s);
	drawSnake(s);
	map();
	runGame(s);
}

void menu()
{
	gotoxy(20, 5);
	cout << "欢迎使用《贪吃蛇》~！" << endl;
	gotoxy(21, 7);
	cout << "按任意键开始游戏" << endl;
	_getch();
	system("cls");
}

int score(const vector<snake>& s)
{
	return 5 * (s.size() - 1);
}

int main()

{
	menu();
	startGame();
	return 0;
}


