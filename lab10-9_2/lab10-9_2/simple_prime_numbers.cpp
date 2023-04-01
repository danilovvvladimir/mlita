//	9.2.Простоватые числа(3)
//
//	Студент Вася отыскивает простые числа в диапазоне от 1 до N(1 ≤  N ≤ 10^18).Если число M, не
//	превосходящее N, не делится на 2, 3 и 5, Вася называет его “простоватым”.По заданному
//	значению N найти количество простоватых чисел.
//
//	Ввод. В единственной строке файла INPUT.TXT находится число N.
//
//	Вывод. В единственную строку файла OUTPUT.TXT вывести количество простоватых чисел.
//
//	Пример
//	Ввод
//	10
//	Вывод
//	2
//
//	Данилов Владимир, ПС-21. Visual Studio 2017.

#include <iostream>
#include <fstream>

using LongNumber = unsigned long long;

void HandleInput(std::istream& inputStream, LongNumber& N)
{
	inputStream >> N;
}

void HandleOutput(std::ostream& outputStream, LongNumber const& N)
{
	outputStream << N << std::endl;
}

LongNumber GreatestCommonDivisor(LongNumber N, LongNumber devider) {
	while (devider) {
		N %= devider;
		std::swap(N, devider);
	}

	return N;
}

LongNumber LeastCommonMultiple(LongNumber N, LongNumber multiple) {
	return N / GreatestCommonDivisor(N, multiple) * multiple;
}

LongNumber GetSimplePrimeNumbers(LongNumber const& N)
{
	LongNumber counter = N;

	// вычитаю количество чисел, которое делится отдельно на 2, отдельно на 3, отдельно на 5
	counter -= N / 2 + N / 3 + N / 5;

	// прибавляю количество чисел, которые делятся на 2 и 3, 2 и 5, 3 и 5
	counter += N / LeastCommonMultiple(2, 3);
	counter += N / LeastCommonMultiple(2, 5);
	counter += N / LeastCommonMultiple(3, 5);

	// вычитаю количество чисел, которые делятся на все три числа
	counter -= N / LeastCommonMultiple(2, LeastCommonMultiple(3, 5));

	return counter;
}

int main()
{

	std::ifstream inputFile("input.txt");
	if (!inputFile.is_open())
	{
		return 1;
	}

	LongNumber N;
	HandleInput(inputFile, N);

	LongNumber simplePrimeNumbers = GetSimplePrimeNumbers(N);

	std::ofstream outputFile("output.txt");
	if (!outputFile.is_open())
	{
		return 1;
	}

	HandleOutput(outputFile, simplePrimeNumbers);
	return 0;
}