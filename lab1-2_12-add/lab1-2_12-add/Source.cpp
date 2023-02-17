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

class Field
{
private:
public:
	int col;
	vector<pair<int, int>> positions;

	Field(int N)
	{
		col = 0;
	}
	Field(const Field& anotherField) : col(anotherField.col), positions(anotherField.positions)
	{
	}
};

int main()
{
	ifstream inputFile;
	inputFile.open("input.txt");

	int N;
	inputFile >> N;

	ofstream outputFile;
	outputFile.open("output.txt");

	queue<Field> q;
	int counter = 0;

	for (int i = 0; i < N; i++)
	{
		Field f(N);
		f.positions.push_back({ 0, i });
		f.col = f.col++;
		if (N == 1)
		{
			outputFile << positionLetters[f.positions[i].first] << f.positions[i].second + 1 << ' ';
			outputFile << endl;
			counter++;
		}
		else
		{
			q.push(f);
		}
	}

	while (!q.empty())
	{
		Field tempfatherF(q.front());

		if (tempfatherF.col == N)
		{
			break;
		}
		for (int i = 0; i < N; i++)
		{
			bool isXFound = false;
			Field tempsonF(tempfatherF);

			for (int j = 0; j < tempsonF.positions.size(); j++)
			{
				if ((tempsonF.positions[j].second == i)
					|| (tempsonF.positions[j].first == tempsonF.col)
					|| (abs(tempsonF.positions[j].second + tempsonF.positions[j].first) == abs(i + tempsonF.col))
					|| (abs(i - tempsonF.positions[j].second) == abs(tempsonF.col - tempsonF.positions[j].first)))
				{
					isXFound = true;
					break;
				}
			}

			if (!isXFound)
			{
				tempsonF.positions.push_back({ tempsonF.col, i });
				tempsonF.col = tempsonF.col + 1;
				if (tempsonF.col == N)
				{
					for (int i = 0; i < tempsonF.positions.size(); i++)
					{
						outputFile << positionLetters[tempsonF.positions[i].first] << tempsonF.positions[i].second + 1 << ' ';
					}
					outputFile << endl;
					counter++;
				}
				else
				{
					q.push(tempsonF);
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
