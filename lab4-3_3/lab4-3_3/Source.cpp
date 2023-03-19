//3.3.Распил бруса(7)
//
//  На пилораму привезли брус длиной L метров.Известны места, в которых необходимо сделать
//  распилы.Стоимость одного распила равна длине распиливаемого бруса.Различный порядок
//  распилов приводит к различным итоговым ценам.Например, брус длиной 10 метров, который
//  нужно распилить на расстоянии 2, 4 и 7 метров можно пилить разными способами.Можно
//  распилить сначала на отметке 2, потом 4 и потом 7. Стоимость будет 10 + 8 + 6 = 24. А если сначала
//  распилить на отметке 4, потом 2 и затем 7, то стоимость составит 10 + 4 + 6 = 20. Требуется написать
//  программу, которая определяла бы минимальную стоимость распила.
//
//  Ввод из файла INPUT.TXT.В первой строке содержатся через пробел натуральные числа L
//  и N(1 ≤ L ≤ 500, N &lt; L) – длина бруса и число разрезов.Вторая строка содержит N натуральных
//  чисел C i(0 & lt; C i &lt; L) через пробел, задающих в строго возрастающем порядке места, в которых
//  нужно сделать распилы.
//
//  Вывод в файл OUTPUT.TXT.В единственной строке вывести минимальную стоимость
//  распилов.
//
//  Примеры
//  Ввод 1 Ввод 2
//  10 2	10 4
//  2 7		4 5 7 8
//  Вывод 1 Вывод 2
//  
//  17		22
//
//	Данилов Владимир, ПС-21. Visual Studio 2017.
//

#include <iostream>
#include <fstream>
#include <vector>

struct TablePosition
{
	int firstPoint;
	int secondPoint;
};

int GetMinTableCost(TablePosition& position, std::vector<std::vector<int>>& costTable, std::vector<int> & cuttingPoints)
{
	int cost = -1;
	int cutPoiX = cuttingPoints[position.firstPoint];
	int cutPoiY = cuttingPoints[position.secondPoint];
	//int length = cuttingPoints[position.y] - cuttingPoints[position.x];
	int length = cutPoiY - cutPoiX;

	for (size_t i = position.firstPoint + 1; i < position.secondPoint; ++i)
	{
		int tempX = costTable[position.firstPoint][i];
		int tempY = costTable[i][position.secondPoint];

		//int currCost = costTable[position.x][i] + costTable[i][position.y] + length;
		int currCost = tempX +tempY + length;

		if (currCost < cost || cost == -1)
		{
			cost = currCost;
		}
	}

	return cost;
}

void PrintTable(std::vector<std::vector<int>>& table)
{
	int tableSize = table.size();
	std::cout << "X " << "\t";
	for (int i = 0; i < tableSize; i++)
	{
		std::cout << i << "\t";
	}
	std::cout << std::endl;

	for (int i = 0; i < tableSize; i++)
	{
		std::cout << "---------";
	}
	std::cout << std::endl;

	for (int i = 0; i < tableSize; i++)
	{
		std::cout << i << "|\t";
		for (int j = 0; j < tableSize; j++)
		{
			std::cout << table[i][j] << "\t";
		}
		std::cout << std::endl;
	}

	std::cout << "------------------------------------" << std::endl;
	std::cout << std::endl;
}


int GetMinCostTable(std::vector<int> & cuttingPoints)
{
	int tableSize = cuttingPoints.size();
	std::vector<std::vector<int>> table(tableSize, std::vector<int>(tableSize, 0));

	PrintTable(table);

	for (int column = 1; column < tableSize; column++)
	{
		TablePosition currPosition = { 0, column };

		while ((currPosition.firstPoint < tableSize) && (currPosition.secondPoint < tableSize))
		{
			if (currPosition.secondPoint <= currPosition.firstPoint + 1)
			{
				currPosition.firstPoint++, currPosition.secondPoint++;
				continue;
			}

			int currentCost = GetMinTableCost(currPosition, table, cuttingPoints);

			if (currentCost != -1)
			{
				table[currPosition.firstPoint][currPosition.secondPoint] = currentCost;
			}

			PrintTable(table);

			currPosition.firstPoint++, currPosition.secondPoint++;
		}
	}

	return table[0][tableSize-1];
}

void HandleInput(std::istream& inputStream, int& L, int& N, std::vector<int>& cuttingPoints)
{
	inputStream >> L >> N;
	cuttingPoints.push_back(0);
	for (int i = 0; i < N; i++)
	{
		int cuttingPoint;
		inputStream >> cuttingPoint;
		cuttingPoints.push_back(cuttingPoint);
	}
	cuttingPoints.push_back(L);
}

void HandleOutput(std::ostream& outputStream, int minCuttingPrice)
{
	outputStream << minCuttingPrice << std::endl;
}

int main()
{
	std::ifstream inputFile("input.txt");
	if (!inputFile.is_open())
	{
		return 1;
	}

	int L;
	int N;
	std::vector<int> cuttingPoints;
	HandleInput(inputFile, L, N, cuttingPoints);
	

	int minCuttingPrice = GetMinCostTable(cuttingPoints);

	std::ofstream outputFile("output.txt");
	if (!outputFile.is_open())
	{
		return 1;
	}
	HandleOutput(std::cout, minCuttingPrice);

	return 0;
}
