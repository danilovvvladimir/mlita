//2.12.Ферзи(7)
//Методом поиска в ширину расставить на шахматной доске размером N × N  клеток N  ферзей(1 ≤ N ≤ 12) так, 
//чтобы они не атаковали один другого.Иными словами, они должны стоять на разных горизонталях, вертикалях и диагоналях.
//Ввод из файла INPUT.TXT.В единственной строке задается значение N.
//
//Вывод в файл OUTPUT.TXT.Вывести все искомые позиции, используя шахматные обозначениях.
//Горизонтали доски нумеруются от 1 до N.Вертикали обозначаются строчными лаьтнскими буквами ‘a‘, ‘b‘, ‘c‘ и т.д.
//Поля в позиции должны следовать по возрастанию номера столбца(буквы по алфавиту).В последней строке сообщить о количестве найденных позиций.
//Примеры
//Ввод 1        Ввод 2        Ввод 3
//4             1             3
//Вывод 1       Вывод 2       Вывод 3
//a2 b4 c1 d3   a1            0 positions
//a3 b1 c4 d2   1 positions
//2 positions
//
// Данилов Владимир ПС-21, Visual Studio 2017

#include <iostream>
#include <fstream>
#include <queue>
#include <vector>
#include <string>
#include <math.h>

using namespace std;
const string positionLetters = "abcdefghijkl";

int main()
{
	ifstream inputFile;
	inputFile.open("input.txt");

	if (!inputFile.is_open())
	{
		return 1;
	}
	int N;
	inputFile >> N;

	ofstream outputFile;
	outputFile.open("output.txt");

	queue<vector<pair<int, int>>> q;
	int counter = 0;

	for (int i = 0; i < N; i++)
	{
		vector<pair<int, int>> positions;
		positions.push_back({ 0, i });
		if (N == 1)
		{
			outputFile << positionLetters[positions[i].first] << positions[i].second + 1 << ' ';
			outputFile << endl;
			counter++;
		}
		else
		{
			q.push(positions);
		}
	}

	while (!q.empty())
	{
		vector<pair<int, int>> positionsFather = q.front();

		if (positionsFather.size() == N)
		{
			break;
		}
		for (int i = 0; i < N; i++)
		{
			bool isXFound = false;
			vector<pair<int, int>> positionsSon = positionsFather;

			for (int j = 0; j < positionsFather.size(); j++)
			{
				if ((positionsSon[j].second == i)
					|| (positionsSon[j].first == positionsFather.size())
					|| (abs(positionsSon[j].second + positionsSon[j].first) == abs(i + int(positionsFather.size()) ))
					|| (abs(i - positionsSon[j].second) == abs(int(positionsFather.size() - positionsSon[j].first))))
				{
					isXFound = true;
					break;
				}
			}

			if (!isXFound)
			{
				positionsSon.push_back({ int(positionsFather.size()), i });
				if (positionsSon.size() == N)
				{
					for (int i = 0; i < positionsSon.size(); i++)
					{
						outputFile << positionLetters[positionsSon[i].first] << positionsSon[i].second + 1 << ' ';
					}
					outputFile << endl;
					counter++;
				}
				else
				{
					q.push(positionsSon);
				}
			}
			if (i == N - 1)
			{
				q.pop();
			}
		}
	}
	outputFile << counter << " positions" << endl;

	return 0;
}
