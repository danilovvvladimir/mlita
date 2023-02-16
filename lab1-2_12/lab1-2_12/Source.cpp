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
	char **mainMap;
	int length;
	int col;
	vector<string> positions;
	Field(int N)
	{
		col = 0;
		length = N;
		char ** map = new char *[length];
		for (int i = 0; i < length; i++)
		{
			map[i] = new char[length];
		}
		for (int i = 0; i < length; i++)
		{
			for (int j = 0; j < length; j++)
			{
				map[i][j] = '.';
			}
		}
		mainMap = map;
	}
	Field(const Field& anotherField) :
		length(anotherField.length), col(anotherField.col)
	{
		char ** map = new char *[length];
		for (int i = 0; i < length; i++)
		{
			map[i] = new char[length];
		}

		for (int i = 0; i < length; i++)
		{
			for (int j = 0; j < length; j++)
			{
				map[i][j] = anotherField.mainMap[i][j];
			}
		}
		mainMap = map;
	}
	~Field()
	{
		for (int i = 0; i < length; i++)
		{
			delete[]mainMap[i];
		}
		delete[] mainMap;
	}

	void printField()
	{
		for (int i = 0; i < length; i++)
		{
			for (int j = 0; j < length; j++)
			{
				cout << mainMap[i][j];
			}
			cout << endl;
		}
		cout << endl;
	}
};

int main()
{
	ifstream inputFile;
	string inputFilePath;
	cout << "Input File: ";
	cin >> inputFilePath;
	inputFile.open(inputFilePath);

	int N;
	inputFile >> N;

	ofstream outputFile;
	string outputFilePath;
	cout << "Output File: ";
	cin >> outputFilePath;
	outputFile.open(outputFilePath);



	queue<Field> q;
	queue<Field> qWIN;

	for (int i = 0; i < N; i++)
	{
		Field f(N);
		for (int j = 0; j < N; j++)
		{
			for (int k = 0; k < N; k++)
			{
				if (j == i)
				{
					if (k == 0)
					{
						f.mainMap[i][k] = 'X';

					}
					else
					{
						f.mainMap[j][k] = '=';
					}
				}
				if (f.mainMap[j][k] != 'X')
				{

					if (k == f.col)
					{
						f.mainMap[j][k] = '=';
					}
					if (abs(i) == abs(j + k))
					{
						f.mainMap[j][k] = '=';
					}
					if (abs(j - i) == abs(k))
					{
						f.mainMap[j][k] = '=';
					}
				}
			}
		}
		f.col = f.col++;
		if (N == 1)
		{
			qWIN.push(f);
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

		for (int i = 0; i < tempfatherF.length; i++)
		{
			bool isPlaced = false;
			Field tempsonF(tempfatherF);
			if (tempsonF.mainMap[i][tempsonF.col] == '.')
			{
				tempsonF.mainMap[i][tempsonF.col] = 'X';
				isPlaced = true;

			}
			for (int j = 0; j < tempfatherF.length; j++)
			{
				bool isPossibleToSkip = false;
				for (int k = tempsonF.col; k < tempfatherF.length; k++)
				{
					if (tempsonF.mainMap[i][k] == '.')
					{
						tempsonF.mainMap[i][k] = '=';
					}
					if (tempsonF.mainMap[j][k] == '.')
					{
						if (k == tempsonF.col)
						{
							tempsonF.mainMap[j][k] = '=';
						}
						if (abs(i + tempsonF.col) == abs(j + k))
						{
							tempsonF.mainMap[j][k] = '=';
						}
						if (abs(j - i) == abs(k - tempsonF.col))
						{
							tempsonF.mainMap[j][k] = '=';
						}
					}
				}
			}
			if (isPlaced)
			{
				tempsonF.col = tempsonF.col++;
				q.push(tempsonF);
				if (tempsonF.col == N)
				{
					qWIN.push(tempsonF);
				}
			}

			if (i == tempfatherF.length - 1)
			{
				q.pop();
			}
		}
	}

	int counter = 0;

	while (!qWIN.empty())
	{
		Field winField(qWIN.front());
		//winField.printField();
		for (int i = 0; i < N; i++)
		{
			for (int j = 0; j < N; j++)
			{
				if (winField.mainMap[j][i] == 'X')
				{
					winField.positions.push_back(positionLetters[i] + to_string(j + 1));
				}
			}
		}
		for (int i = 0; i < N; i++)
		{
			outputFile << winField.positions[i] << ' ';
		}
		outputFile << endl;
		qWIN.pop();
		counter++;
	}
	outputFile << counter << " positions" << endl;


	return 0;
}