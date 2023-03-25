//  5.3.Число цифр(5)
//  Найти суммарное число цифр во всех целых числах от M до N включительно.
//
//  Ввод из файла INPUT.TXT.В  единственной  строке  находятся  целые  числа  M  и N(1 ≤ M ≤ N ≤ 10^15).
//
//  Вывод в файл OUTPUT.TXT.В единственную строку вывести суммарное число цифр.
//
//  Примеры
//  Ввод 1    Ввод 2
//  1 2       2 11
//  Вывод 1   Вывод 2
//  2         12
//
// Данилов Владимир, ПС-21. Visual Studio 2017. Стандарт: C++17.

#include <iostream>
#include <string>
#include <fstream>

using LongNumber = unsigned long long;

void HandleInput(std::istream& inputStream, LongNumber & M, LongNumber & N)
{
	inputStream >> M >> N;
}

void HandleOutput(std::ostream& outputStream, LongNumber sum)
{
	outputStream << sum;
}

LongNumber FindDigitsInSum(LongNumber M, LongNumber N)
{
	int sizeM = (std::to_string(M)).size();
	int sizeN = (std::to_string(N)).size();

	if (sizeM == sizeN)
	{
		return (N - M + 1) * sizeM;
	}

	LongNumber digitSum = static_cast<LongNumber>(pow(10, sizeM) - M) * sizeM;

	for (int digit = sizeM + 1; digit < sizeN; digit++)
	{
		digitSum += (static_cast<LongNumber>(pow(10, digit)) - static_cast<LongNumber>(pow(10, digit - 1))) * digit;
	}


	digitSum += (N + 1 - static_cast<LongNumber>(pow(10, sizeN - 1))) *sizeN;

	return digitSum;
}


int main()
{
	LongNumber M;
	LongNumber N;

	std::ifstream inputFile("input.txt");
	if (!inputFile.is_open())
	{
		return 1;
	}

	HandleInput(inputFile, M, N);

	LongNumber sum = FindDigitsInSum(M, N);

	std::ofstream outputFile("output.txt");
	if (!inputFile.is_open())
	{
		return 1;
	}

	HandleOutput(outputFile, sum);
	return 0;
}