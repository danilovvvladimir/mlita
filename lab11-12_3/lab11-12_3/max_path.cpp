//	12.3.Максимальный путь 1 (6)
//	Имеется взвешенный ориентированный ациклический граф.Найти максимальный путь,
//	используя алгоритм Беллмана - Форда.
//
//	Ввод из файла INPUT.TXT.Первая строка входного файла INPUT.TXT содержит 3 числа: N -
//	количество вершин графа(3 ≤ N ≤ 1000), M – дуг(3 ≤ M ≤ 500000), A – номер начальной вершины.
//	В следующих M строках по 3 числа, задающих дуги : начало дуги, конец дуги, длина(вес).
//
//	Вывод в файл OUTPUT.TXT.В i - й строке выводится длина максимального пути из вершины S
//	до i - й вершины, затем количество вершин максимального пути, а далее номера вершин
//	максимального пути.Все числа разделены пробелами.
//  Если пути в некоторую вершину не существует, то в соответствующей строке выводится слово No.
//  Если в графе имеется достижимый из начальной вершины цикл положительной длины, 
//  то вывод состоит из двух строк.
//  В первой строке выводится слово No, а во второй – количество и номера вершин обнаруженного цикла
//	через пробел, начиная с его любой вершины и заканчивая ей же.При наличии нескольких циклов
//	вывести информацию о любом из них.
//
//	Пример
//	Ввод 1		Ввод 2
//	4 6 1		5 6 1 | N = 5 (кол-во вершин), M = 6 (кол-во дуг, т.е кол-во следующих записей), A = 1 (номер стартовой вершины)
//	1 2 1		1 2 1 | от какой вершины, к какой вершине, за сколько
//	1 4 2		1 4 2
//	2 3 3		2 3 3
//	2 4 3		2 4 3
//	3 4 1		3 4 1
//	4 3 1		5 2 5
//	Вывод 1		Вывод 2
//	No			0 1 1		| [максимальный путь до вершины i = 1] длина, сколько вершин в пути, вершины
//	3 4 3 4		1 2 1 1(2) 
//				4 3 1 2 3
//				5 4 1 2 3 4
//				No
//
// Данилов Владимир, ПС-21. Visual Studio 2017.

#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>

using matrix = std::vector<std::vector<int>>;

matrix HandleInput(std::istream& inputStream, int& vertexesAmount, int& edgesAmount, int& startVertexNumber )
{
	inputStream >> vertexesAmount >> edgesAmount >> startVertexNumber;

	matrix graphMatrix(vertexesAmount, std::vector<int>(vertexesAmount, 0));

	int startEdge = 0;
	int finishEdge = 0;
	int weigthEdge = 0;

	for (int i = 0; i < edgesAmount; i++)
	{
		inputStream >> startEdge >> finishEdge >> weigthEdge;
		graphMatrix[startEdge-1][finishEdge-1] = weigthEdge;
	}
	return graphMatrix;
}

void HandleOutput(std::ostream& outputStream, matrix const& graphMatrix)
{
	for (int i = 0; i < graphMatrix.size(); i++)
	{
		for (int j = 0; j < graphMatrix.size(); j++)
		{
			outputStream << graphMatrix[i][j] << " ";
		}
		outputStream << std::endl;
	}
}

int main()
{
	std::ifstream inputFile("input.txt");
	if (!inputFile.is_open())
	{
		return 1;
	}

	int vertexesAmount = 0;
	int edgesAmount = 0;
	int startVertexNumber = 0;

	matrix graphMatrix = HandleInput(inputFile, vertexesAmount, edgesAmount, startVertexNumber);



	std::ofstream outputFile("output.txt");
	if (!outputFile.is_open())
	{
		return 1;
	}

	HandleOutput(std::cout, graphMatrix);
	return 0;
}