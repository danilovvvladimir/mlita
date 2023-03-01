//1.1.Покраска лабиринта(5)
//
// Лабиринт представляет собой квадрат, состоящий из NxN сегментов.
// Каждый из сегментов может быть либо пустым, либо заполненным монолитной каменной стеной.Гарантируется, что левый верхний и правый нижний сегменты пусты.
// Лабиринт обнесён сверху, снизу, слева и справа стенами, оставляющими свободными только левый верхний и правый нижний углы.
// Директор лабиринта решил покрасить стены лабиринта, видимые изнутри(см.рисунок).Помогите ему рассчитать количество краски, необходимой для этого.
//
//Ввод из файла INPUT.TXT.В первой строке находится число N, затем идут N строк по N символов : точка обозначает пустой сегмент, решётка - сегмент со стеной.
//Вывод в файл OUTPUT.TXT.Вывести одно число - площадь видимой части внутренних стен лабиринта в квадратных метрах.
//Ограничения : 3 ≤ N ≤ 33, размер сегмента 3 x 3 м, высота стен 3 м, время 1 с.
//	Пример
//	Ввод
//	5
//	.....
//	...##
//	..#..
//	..###
//	.....
//	Вывод
//	198
//
//  Данилов Владимир, ПС-21, Visual Studio 2017.
//
#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

int dirX[4] = { 0, 1, 0 ,-1 };
int dirY[4] = { -1, 0, 1 ,0 };

struct Point
{
	int x, y;
};

void exploreNeighbours(Point p, vector<vector<char>>& mainVector, int n, int& counter)
{
	for (int i = 0; i < 4; i++)
	{
		Point nextPoint = p;
		nextPoint.x += dirX[i];
		nextPoint.y += dirY[i];

		if ((nextPoint.x == 0 && nextPoint.y == -1) || (nextPoint.x == -1 && nextPoint.y == 0)) continue;
		if ((nextPoint.x == n && nextPoint.y == n - 1) || (nextPoint.x == n - 1 && nextPoint.y == n)) continue;

		if ((nextPoint.x < 0 || nextPoint.x > n - 1) || (nextPoint.y < 0 || nextPoint.y > n - 1)  || (mainVector[nextPoint.y][nextPoint.x] == '#'))
		{
			counter++;
			continue;
		}

		if (mainVector[nextPoint.y][nextPoint.x] == 'O')
		{
			continue;
		}

		if (mainVector[nextPoint.y][nextPoint.x] == '.')
		{
			mainVector[nextPoint.y][nextPoint.x] = 'O';
			exploreNeighbours(nextPoint, mainVector, n, counter);
		}
	}
}

int main()
{
	ifstream inputFile("input.txt");
	ofstream outputFile("output.txt");

	if (!inputFile.is_open())
	{
		return 1;
	}

	int n;
	inputFile >> n;

	vector<vector<char>> mainVector(n, vector<char>(n, '.'));

	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
		{
			inputFile >> mainVector[i][j];
		}
	}

	int counter = 0;

	Point pointStart{ 0,0 };
	if (mainVector[pointStart.y][pointStart.x] == '.')
	{
		mainVector[pointStart.y][pointStart.x] = 'O';
		exploreNeighbours(pointStart, mainVector, n, counter);
	}

	Point pointEnd{ n-1,n-1 };
	if (mainVector[pointEnd.y][pointEnd.x] == '.')
	{
		mainVector[pointEnd.y][pointEnd.x] = 'O';
		exploreNeighbours(pointEnd, mainVector, n, counter);
	}
	outputFile << (counter * 9);
	return 0;
}