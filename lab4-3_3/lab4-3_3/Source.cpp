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

constexpr size_t INITIAL_ROW = 0;
constexpr size_t INITIAL_COST = 0;
constexpr size_t MIN_CUTTING_POINT = 0;
constexpr size_t NO_COST = -1;

typedef std::vector<int> CuttingPoints;
typedef std::vector<int> CostRow;
typedef std::vector<CostRow> CostTable;

struct TablePosition
{
	size_t x;
	size_t y;
};



int GetMinCostTableCell(TablePosition& position, CostTable& costTable, CuttingPoints& cuttingPoints)
{
	int cost = NO_COST;
	int length = cuttingPoints[position.y] - cuttingPoints[position.x];
	for (size_t i = position.x + 1; i < position.y; ++i)
	{
		int currCost = costTable[position.x][i] + costTable[i][position.y] + length;
		if (currCost < cost || cost == NO_COST)
		{
			cost = currCost;
		}
	}

	return cost;
}

void PrintCostTable(CostTable& costTable)
{
	std::cout << "X " << "\t";
	for (int i = 0; i < costTable.size(); i++)
	{
		std::cout << i << "\t";
	}
	std::cout << std::endl;
	for (int i = 0; i < costTable.size(); i++)
	{
		std::cout << "---------";
	}
	std::cout << std::endl;
	for (int i = 0; i < costTable.size(); i++)
	{
		std::cout << i << "|\t";
		for (int j = 0; j < costTable.size(); j++)
		{
			std::cout << costTable[i][j] << "\t";
		}
		std::cout << std::endl;
	}
	std::cout << "------------------------------------" << std::endl;
	std::cout << std::endl;
}

void FillMinCostTable(CostTable& costTable, CuttingPoints& cuttingPoints)
{
	size_t column = INITIAL_ROW + 1;
	while (column < cuttingPoints.size())
	{
		TablePosition currPosition = { INITIAL_ROW, column };
		for (; currPosition.x < cuttingPoints.size() && currPosition.y < cuttingPoints.size();
			++currPosition.x, ++currPosition.y)
		{
			if (currPosition.y <= currPosition.x + 1)
			{
				continue;
			}

			int currCost = GetMinCostTableCell(currPosition, costTable, cuttingPoints);
			if (currCost != NO_COST)
			{
				costTable[currPosition.x][currPosition.y] = currCost;
			}

			PrintCostTable(costTable);
		}
		column++;
	}
}

CostTable GetMinCostTable(CuttingPoints& cuttingPoints)
{
	int tableSize = cuttingPoints.size();
	CostTable result(tableSize, CostRow(tableSize, INITIAL_COST));

	PrintCostTable(result);

	FillMinCostTable(result, cuttingPoints);

	return result;
}

void HandleInput(std::istream& inputStream, int& L, int& N, CuttingPoints& cuttingPoints)
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
	CuttingPoints cuttingPoints;
	HandleInput(inputFile, L, N, cuttingPoints);
	

	CostTable costTable = GetMinCostTable(cuttingPoints);
	int minCuttingPrice = costTable[0][costTable.size() - 1];

	std::ofstream outputFile("output.txt");
	if (!outputFile.is_open())
	{
		return 1;
	}
	HandleOutput(std::cout, minCuttingPrice);

	return 0;
}
