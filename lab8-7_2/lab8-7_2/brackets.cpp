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
//	Ввод из файла INPUT.TXT.В первой строке задано значение N(1 ≤ N ≤ 3×10^5).Во второй
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
//	0		3		1
//
//	Данилов Владимир, ПС-21. Visual Studio 2017.

#include <fstream>
#include <iostream>
#include <vector>

void HandleInput(std::istream& inputStream, std::vector<int>& brackets)
{
	int N;
	inputStream >> N;
	brackets.assign(2 * N, 0);

	int countBrackets = 0;
	char tempBracket;

	for (int i = 0; i < 2 * N; i++)
	{
		inputStream >> tempBracket;
		if (tempBracket == '(')
		{
			countBrackets++;
		}
		else
		{
			countBrackets--;
		}

		brackets[i] = countBrackets;
	}
}

int FindExternalBracketsPairs(std::vector<int> const& brackets)
{
	int externalBracketsSize = brackets.size() / 2;
	std::vector<int> repeatedExternalBrackets(externalBracketsSize, 0);

	for (int i = 0; i < brackets.size(); i++)
	{
		int bracketIndex = brackets[i];

		if (bracketIndex >= externalBracketsSize)
		{
			return externalBracketsSize;
		}

		repeatedExternalBrackets[bracketIndex]++;

		if (repeatedExternalBrackets[bracketIndex] > 2)
		{
			return bracketIndex - 1;
		}

		if (bracketIndex == 0 && repeatedExternalBrackets[bracketIndex] > 1)
		{
			return bracketIndex;
		}
	}

	return externalBracketsSize;
}

void HandleOutput(std::ostream& outputStream, int externalBracketsPairs)
{
	outputStream << externalBracketsPairs;
}

int main()
{
	std::ifstream inputFile("input.txt");
	if (!inputFile.is_open())
	{
		return 1;
	}

	std::vector<int> brackets;
	HandleInput(inputFile, brackets);

	int externalBracketsPairs = FindExternalBracketsPairs(brackets);

	std::ofstream outputFile("output.txt");
	if (!outputFile.is_open())
	{
		return 1;
	}

	HandleOutput(outputFile, externalBracketsPairs);
	return 0;
}