//	3.3.Распил бруса(7)
//
//  На пилораму привезли брус длиной L метров.Известны места, в которых необходимо сделать
//  распилы.Стоимость одного распила равна длине распиливаемого бруса.Различный порядок
//  распилов приводит к различным итоговым ценам.Например, брус длиной 10 метров, который
//  нужно распилить на расстоянии 2, 4 и 7 метров можно пилить разными способами.Можно
//  распилить сначала на отметке 2, потом 4 и потом 7. Стоимость будет 10 + 8 + 6 = 24. А если сначала
//  распилить на отметке 4, потом 2 и затем 7, то стоимость составит 10 + 4 + 6 = 20. Требуется написать
//  программу, которая определяла бы минимальную стоимость распила.
//
//  Ввод из файла INPUT.TXT. В первой строке   содержатся   через пробел натуральные числа L и N (1 ≤ L ≤ 500, N < L) – длина бруса и число разрезов. 
//  Вторая строка содержит N натуральных чисел Ci (0 <Ci <L ) через пробел, задающих в строго возрастающем порядке места, в которых нужно сделать распилы.
//
//  Вывод в файл OUTPUT.TXT.В единственной строке вывести минимальную стоимость
//  распилов.
//
//  Примеры
//  Ввод 1		Ввод 2
//  10 2		10 4
//  2 7			4 5 7 8
//  Вывод 1		Вывод 2
//  
//  17			22
//
//	Данилов Владимир, ПС-21. Visual Studio 2017.


#include <iostream>
#include <fstream>
#include <vector>

void PrintTable(std::vector<std::vector<int>> const& table)
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

int GetMinTableCost(int tableX, int tableY, std::vector<std::vector<int>> const& costTable, std::vector<int> const& cuttingPoints)
{
	int cost = -1;
	int cutX = cuttingPoints[tableX];
	int cutY = cuttingPoints[tableY];

	for (int i = tableX + 1; i < tableY; ++i)
	{
		int tempX = costTable[tableX][i];
		int tempY = costTable[i][tableY];

		int currCost = tempX + tempY + cutY - cutX;

		if (cost == -1 || currCost < cost)
		{
			cost = currCost;
		}
	}

	return cost;
}


int GetMinCuttingCost(std::vector<int> const& cuttingPoints)
{
	int tableSize = cuttingPoints.size();

	std::vector<std::vector<int>> table(tableSize, std::vector<int>(tableSize, 0));

	for (int y = 0; y < tableSize; y++)
	{
		int tableX = 0;
		int tableY = y;

		while ((tableY < tableSize))
		{
			if (tableY > tableX + 1)
			{
				int currentCost = GetMinTableCost(tableX, tableY, table, cuttingPoints);

				if (currentCost != -1)
				{
					table[tableX][tableY] = currentCost;
				}
				//PrintTable(table);
			}

			tableX++;
			tableY++;
		}
	}

	return table[0][tableSize - 1];
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

void HandleOutput(std::ostream& outputStream, int minCuttingCost)
{
	outputStream << minCuttingCost << std::endl;
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

	int minCuttingCost = GetMinCuttingCost(cuttingPoints);

	std::ofstream outputFile("output.txt");
	if (!outputFile.is_open())
	{
		return 1;
	}

	HandleOutput(outputFile, minCuttingCost);

	return 0;
}
