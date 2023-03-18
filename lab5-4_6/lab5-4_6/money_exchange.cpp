//	4.6.Размен денег(6)
//	Требуется разменять заданную сумму денег минимальным количеством монет.
//
//	Ввод.Первая строка файла INPUT.TXT содержит сумму денег L(1 ≤ L ≤ 20000) и количество
//	типов монет N(1 ≤ N ≤ 30).Вторая строка содержит N значений C i через пробел : стоимости типов монет(1 ≤ C i ≤ L).
//
//	Вывод.В первой строке выводится количество типов монет K, необходимое для размена, и
//	общее минимальное количество монет M. В следующих K строках выводятся через пробел по 2
//	числа : стоимость монеты и количество экземпляров данной монеты. Эти K строк должны
//	выводится в порядке убывания стоимости монет.Если имеется несколько вариантов решения,
//	достаточно вывести любой из них.Если указанную сумму разменять невозможно, то выходной
//	файл должен содержать No.
//
//	Примеры
//	Ввод 1	Ввод 2
//	15 3	12 3
//	5 11 1	1 10 3
//	Вывод 1 Вывод 2
//	1 3		2 3
//	5 3		10 1
//			1 2
//
// Данилов Владимир, ПС-21. Visual Studio 2017.
// Стандарт языка C++17

#include <iostream>
#include <vector>
#include <fstream>
#include <optional>
#include <set>
#include <map>

using MemoMap = std::map<int, std::optional<std::vector<int>>>;

void HandleInput(std::istream& inputStream, int& sum, int& coinAmount, std::vector<int>& coinValues)
{
	inputStream >> sum >> coinAmount;
	int value = 0;
	for (int i = 0; i < coinAmount; i++)
	{
		inputStream >> value;
		coinValues.push_back(value);
	}
}

std::optional<std::vector<int>> FindCombination(int sum, const std::vector<int>& coinValues, MemoMap& memo)
{
	if (memo.find(sum) != memo.end()) return memo[sum];
	if (sum == 0)
	{
		std::vector<int> v;
		return v;
	}
	if (sum < 0) return std::nullopt;

	std::optional<std::vector<int>> shortestCombination = std::nullopt;

	for (auto num : coinValues)
	{
		const int remainder = sum - num;
		auto remainderResult = FindCombination(remainder, coinValues, memo);

		if (remainderResult)
		{
			std::vector<int> combination = remainderResult.value();
			combination.push_back(num);

			if (!shortestCombination || shortestCombination.value().size() > combination.size())
			{
				shortestCombination = combination;
			}
		}
	}

	memo.emplace(sum, shortestCombination);
	return shortestCombination;
}

void HandleOutput(std::ostream& output, const std::optional<std::vector<int>>& resultCombination)
{
	if (!resultCombination)
	{
		output << "No" << std::endl;
		return;
	}

	std::map<int, int, std::greater<>> uniqueCoins;


	for (auto el : resultCombination.value())
	{
		if (uniqueCoins.find(el) != uniqueCoins.end())
		{

			uniqueCoins[el] = uniqueCoins[el] + 1;
		}
		else
		{
			uniqueCoins.emplace(el, 1);
		}

	}

	output << uniqueCoins.size() << " " << resultCombination.value().size() << std::endl;

	for (auto pair : uniqueCoins)
	{
		output << pair.first << " " << pair.second << std::endl;
	}

}

std::optional<std::vector<int>> FindCombinationMemoization(int targetSum, const std::vector<int>& numbers)
{
	MemoMap memo;
	return FindCombination(targetSum, numbers, memo);
}

int main()
{
	int sum = 0;
	int coinAmount = 0;
	std::vector<int> coinValues;

	std::ifstream inputFile("input4.txt");
	if (!inputFile.is_open())
	{
		return 1;
	}

	HandleInput(inputFile, sum, coinAmount, coinValues);
	std::optional<std::vector<int>> resultCombination = FindCombinationMemoization(sum, coinValues);

	HandleOutput(std::cout, resultCombination);
	//std::vector<std::vector<int>> table(sum + 1, std::vector<int>(sum+1, 0));
	return 0;
}