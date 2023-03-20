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
#include <map>

void HandleInput(std::istream& inputStream, int& sum, std::vector<int>& coinValues)
{
	int coinAmount = 0;
	inputStream >> sum >> coinAmount;
	int value = 0;
	for (int i = 0; i < coinAmount; i++)
	{
		inputStream >> value;
		coinValues.push_back(value);
	}
}

std::optional<std::vector<int>> FindCombination(int sum, const std::vector<int>& coinValues)
{
	std::vector<std::optional<std::vector<int>>> table(sum + 1, std::nullopt);
	std::vector<int> firstAssignedCell;
	table[0] = firstAssignedCell;

	for (int i = 0; i < sum + 1; i++)
	{
		if (table[i])
		{
			for (auto num : coinValues)
			{
				std::vector<int> combination = table[i].value();
				combination.push_back(num);

				if (i+num < sum+1)
				{
					if (!table[i + num] || table[i + num].value().size() > combination.size())
					{
						table[i + num] = combination;
					}
				}
			}
		}
	}

	return table[sum];
}

void HandleOutput(std::ostream& outputStream, const std::optional<std::vector<int>>& resultCombination)
{
	if (!resultCombination)
	{
		outputStream << "No" << std::endl;
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

	outputStream << uniqueCoins.size() << " " << resultCombination.value().size() << std::endl;

	for (auto pair : uniqueCoins)
	{
		outputStream << pair.first << " " << pair.second << std::endl;
	}

}

int main()
{
	int sum = 0;
	std::vector<int> coinValues;

	std::ifstream inputFile("input.txt");
	if (!inputFile.is_open())
	{
		return 1;
	}

	HandleInput(inputFile, sum, coinValues);

	std::optional<std::vector<int>> resultCombination = FindCombination(sum, coinValues);

	std::ofstream outputFile("output.txt");
	if (!outputFile.is_open())
	{
		return 1;
	}
	HandleOutput(outputFile, resultCombination);
	return 0;
}