// FinalAStar.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

#include <iostream>
#include <fstream>
#include <string>
#include <Windows.h>

int NowX = 0;
int NowY = 0;

int NewX = 0;
int NewY = 0;

int StartX = 0;
int StartY = 0;

int TargetX = 0;
int TargetY = 0;
int blockValue = 0;
int CheckValue = 9999;
int duplicateCount = 1;
int openingOrder[20][20] = { 0 };
char map[20][20];
int Distance[20][20];
bool PointsToCheck[20][20];
bool PointsChecked[20][20];
int SumUpCost[20][20] = { 0 };
int MovementCost[20][20] = { 0 };
int parentX[20][20] = { 0 };
int parentY[20][20] = { 0 };
using namespace std;

void Start()
{
	cout << "Podaj Wspolrzedne Startowe(1-20)\n";
	cout << "start X: ";
	cin >> NowX;
	cout << "start Y: ";
	cin >> NowY;
	cout << "Podaj Wspolrzedne Celu(1-20)\n";
	cout << "Cel X: ";
	cin >> TargetX;
	cout << "Cel Y: ";
	cin >> TargetY;
	TargetX = TargetX - 1;
	TargetY = TargetY - 1;
	NowX = NowX- 1;
	NowY = NowY- 1;
	StartX = NowX;
	StartY = NowY;
	getchar();
}

void LoadMap()
{
	ifstream myfile("C:\\Users\\grzes\\Desktop\\FinalAstar\\FinalAstar\\grid.txt");
	for (int i = 19;i >= 0;i--)
	{
		for (int j = 0;j < 20;j++)
		{
			myfile >> map[j][i];
		}
	}
	myfile.close();
}

void ToTargetDistance()
{
	for (int i = 0;i < 20;i++)
	{
		for (int j = 0;j < 20;j++)
		{
			Distance[i][j] = abs(TargetX - i + TargetY - j);
		}
	}
}

void SetUpLists()
{
	for (int i = 0;i < 20;i++)
	{
		for (int j = 0;j < 20;j++)
		{
			if (i == 0 && j == 0)
			{
			PointsChecked[i][j] = true;
			}

			PointsChecked[i][j] = false;
			PointsToCheck[i][j] = false;
		}
	}
}

void CalculateMovementCost(int x, int y)
{
	MovementCost[x][y] = MovementCost[parentX[x][y]][parentY[x][y]] + 1;
}

void WholeCost(int x, int y)
{
	SumUpCost[x][y] = MovementCost[x][y] + Distance[x][y];
}

void PointsCheckedValue(int x, int y)
{
	PointsChecked[x][y] = true;
	PointsToCheck[x][y] = false;

}
void PointsToCheckValue(int x, int y)
{
	PointsToCheck[x][y] = true;
}


int Move(int x, int y)
{
	if (x > 19 || x < 0 || y > 19 || y < 0 || PointsChecked[x][y] == true || map[x][y] == '5')
	{
		blockValue++;
		return 0;
	}
	else
	{
		PointsToCheckValue(x, y);
		parentX[x][y] = NowX;
		parentY[x][y] = NowY;
		CalculateMovementCost(x, y);
		WholeCost(x, y);

	}
}
void WhereToMove(int x, int y)
{
	if ((PointsToCheck[x][y] == true) && SumUpCost[x][y] < CheckValue)
	{
		CheckValue = SumUpCost[x][y];
		NewX = x;
		NewY = y;
	}
	
}
void TobeSure()
{
	for (int i = 0;i < 20;i++)
	{
		for (int j = 0;j < 20;j++)
		{
			if ((PointsToCheck[i][j] == true) && SumUpCost[i][j] < CheckValue)
			{
				CheckValue = SumUpCost[i][j];
				NewX = i;
				NewY = j;
			}
		}
	}

}

void Path()
{
		int X = TargetX;
		int Y = TargetY;
		map[StartX][StartY] = 'x';
		while (X != StartX || Y != StartY)
		{
			map[X][Y] = 'x';
			int temp = X;
			X = parentX[X][Y];
			Y = parentY[temp][Y];
		}
}



void Draw()
{
	for (int i = 19;i >= 0;i--)
	{
		for (int j = 0;j < 20;j++)
		{
			if (map[j][i] == 'x')
			{
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 2);
				cout << map[j][i] << " ";
			}
			else if (map[j][i] == '5')
			{
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 4);
				cout << map[j][i] << " ";
			}
			else
			{
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
				cout << map[j][i] << " ";

			}

		}
		cout << "\n";
	}
}
void drawParent()
{
	for (int i = 19;i >= 0;i--)
	{
		for (int j = 0;j < 20;j++)
		{
			cout << parentX[j][i] << parentY[j][i] << " ";
		}
		cout << "\n";
	}
}



int main()
{
		Start();
		LoadMap();
		SetUpLists();
		ToTargetDistance();
		while (map[StartX][StartY] =='5' || map[TargetX][TargetY] == '5')
		{
			char k;
			cout << "przeszkoda" << "\n";
			cout << "Chcesz Kontynuowac? [Y/N]";
			cin >> k;
			if (k == 'y' || k == 'Y')
			{
				Start();
			}
			else
			{
				return 0;
			}

		
		}
		while (NowX != TargetX || NowY != TargetY)
		{
			PointsCheckedValue(NowX, NowY);


			Move(NowX, NowY + 1);
			/*	WhereToMove(NowX, NowY + 1);*/

			Move(NowX, NowY - 1);
			/*WhereToMove(NowX, NowY - 1);*/

			Move(NowX + 1, NowY);
			/*	WhereToMove(NowX + 1, NowY);*/

			Move(NowX - 1, NowY);
			/*WhereToMove(NowX - 1, NowY);*/



			TobeSure();
			NowX = NewX;
			NowY = NewY;
			/*	if (blockValue == 4)
			{
			int temp = NowX;
			NowX = parentX[NowX][NowY];
			NowY = parentY[temp][NowY];
			}
			else {
			NowX = NewX;
			NowY = NewY;
			}
			blockValue = 0;*/
			CheckValue = 9999;

		}
		Path();
		drawParent();
		Draw();
		printf("Nacisnij dowolny klawisz aby zakończyć...");
		getchar();
		return 0;
}

