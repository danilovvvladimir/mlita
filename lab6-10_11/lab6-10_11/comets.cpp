//	10.11.Кометы(6)
//
//	Астроном Коперни увлечен кометами.Он определил новую физическую единицу яркости Co и
//	вывел закон нахождения яркости комет в зависимости от времени в виде Y = At + B.В дальнейших
//	исследованиях ему удалось рассчитать коэффициенты A и B для всех известных комет.Коперни в
//	любой момент времени всегда наблюдает в свой телескоп комету с наибольшей яркостью.Как
//	только у другой кометы яркость оказывается большей, он переносит на нее свои наблюдения.Для
//	заказа нового телескопа ему необходимо знать минимальную яркость наблюдаемой им кометы на
//	определенный период времени.Помогите астроному Коперни.
//
//	Ввод из файла INPUT.TXT.В первой строке указаны N и T(1 ≤ N, T ≤ 2000) – число комет и
//	период наблюдения.В следующих N строках содержатся коэффициенты A i и B i(-100 ≤ A i, B i ≤ 100)
//	для всех N комет.Все числа N, T, A i, B i целые.Необходимо иметь в виду, что яркость кометы в
//	единицах Co может быть как положительной, так и отрицательной.
//
//	Вывод в файл OUTPUT.TXT.В единственной строке вывести минимальную яркость кометы,
//	которую будет наблюдать астрономом в период от 0 до T с точностью 10 знаков после запятой.
//
//	Пример
//	Ввод
//	2 4
//	1 1
//	- 1 5
//	Вывод
//	3.0000000000
//
//	Данилов Владимир, ПС-21. Visual Studio 2017.

#include <iostream>
#include <fstream>
#include <vector>
#include <iomanip>

double FindMaxBrightness(double t, std::vector<std::pair<int, int>>& const coefs)
{
	double maxBrightness = std::numeric_limits<double>::min();

	for (int i = 0; i < coefs.size(); ++i)
	{
		int A = coefs[i].first;
		int B = coefs[i].second;
		double const Co = A*t + B;

		if (Co > maxBrightness)
		{
			maxBrightness = Co;
		}
	}

	return maxBrightness;
}

double FindMinBrightness(double T, std::vector<std::pair<int, int>>& const coefs)
{
	double minBrightness = std::numeric_limits<double>::max();

	for (double t = 0; t <= T; t += 0.1)
	{
		double const currentBrightness = FindMaxBrightness(t, coefs);

		if (currentBrightness < minBrightness)
		{
			minBrightness = currentBrightness;
		}
	}

	return minBrightness;
}


void HandleInput(std::istream& inputStream, int& N, int& T, std::vector<std::pair<int, int>>& coefs)
{
	inputStream >> N >> T;

	int A;
	int B;
	for (int i = 0; i < N; i++)
	{
		inputStream >> A >> B;
		coefs.push_back({A,B});
	}
}

void HandleOutput(std::ostream& output, double minBrightness)
{
	output << std::fixed << std::setprecision(10) << minBrightness << std::endl;
}


int main()
{
	int N;
	int T;
	std::vector<std::pair<int, int>> coefs;
	std::ifstream inputFile("input.txt");
	if (!inputFile.is_open())
	{
		return 1;
	}

	HandleInput(inputFile, N, T, coefs);
	double minBrightness = FindMinBrightness(T, coefs);

	std::ofstream outputFile("output.txt");
	if (!inputFile.is_open())
	{
		return 1;
	}

	HandleOutput(outputFile, minBrightness);
}