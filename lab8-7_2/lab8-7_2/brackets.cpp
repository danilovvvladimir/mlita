//	7.2.Скобки(4)
//	Последовательность круглых скобок называют правильной, если можно добавить в нее числа и
//	знаки арифметических операций так, что полученное алгебраическое выражение станет
//	корректным.Например, скобочная последовательность(())() является правильной, а(())) и())(()
//	такими не являются.Пустая последовательность также считается правильной.
//	Задана правильная скобочная последовательность.Назовем парой внешних скобок первую
//	открывающую и последнюю закрывающую скобки.
//
//	После удаления пары внешних скобок правильность последовательности может как
//	сохраниться, так и нарушиться.Найти наибольшее число пар внешних скобок, которые можно
//	удалять до первого нарушения правильности последовательности.
//
//	Ввод из файла INPUT.TXT.В первой строке задано значение N(1 ≤ N ≤ 3×10 5).Во второй
//	строке находится правильная скобочная последовательность длины 2N.
//
//	Вывод в файл OUTPUT.TXT.Вывести единственное значение : указанное число пар внешних
//	скобок.
//
//	Примеры
//	Ввод 1 Ввод 2 Ввод 3
//	3		3		5
//	()()() ((())) ((())(()))
//	Вывод 1 Вывод 2 Вывод 3
//	0 3 1
//
//	Данилов Владимир, ПС-21. Visual Studio 2017.

#include <fstream>
#include <iostream>
#include <vector>

void HandleInput(std::istream& inputStream, int& N, std::vector<char>& bracketsVector)
{
	inputStream >> N;
	bracketsVector.assign(2*N, ' ');
	char tempBracket;
	for (int i = 0; i < 2*N; i++)
	{
		inputStream >> tempBracket;
		bracketsVector[i] = tempBracket;
	}
}

void HandleOutput(std::ostream& outputStream, int externalBracketsPairs)
{
	outputStream << externalBracketsPairs;
}

int FindExternalBracketsPairs(std::vector<char>& bracketsVector)
{
	for (int i = 0; i < bracketsVector.size(); i++)
	{
		std::cout << bracketsVector[i] ;
	}
	std::cout << std::endl;
	return 1;
}

int main()
{
	int N;

	std::ifstream inputFile("input.txt");
	if (!inputFile.is_open())
	{
		return 1;
	}

	std::vector<char> bracketsVector;
	HandleInput(inputFile, N, bracketsVector);

	int externalBracketsPairs = FindExternalBracketsPairs(bracketsVector);

	std::ofstream outputFile("output.txt");
	if (!outputFile.is_open())
	{
		return 1;
	}

	HandleOutput(std::cout, externalBracketsPairs);
	return 0;
}