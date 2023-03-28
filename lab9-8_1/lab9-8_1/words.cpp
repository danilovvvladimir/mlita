//	8.1.Слова(3)
//	Дано слово, состоящее из M(2 ≤ M ≤ 7) строчных букв латинского алфавита.Найти все
//	перестановки символов данного слова.
//
//	Ввод из файла INPUT.TXT.В первой строке файла находится исходное слово.
//
//	Вывод в файл OUTPUT.TXT.Вывести в алфавитном порядке без повторений все перестановки
//	символов данного слова по одной перестановке в каждой строке файла.
//
//	Примеры
//	Ввод 1	Ввод 2
//	ab		abb
//	Вывод 1 Вывод 2
//	ab		abb
//	ba		bab
//			bba
//
//	!!!не использовать next_permutation
//	
//	Данилов Владимир, ПС-21. Visual Studio 2017.

#include <fstream>
#include <iostream>
#include <string>
#include <set>

using Permutations = std::set<std::string>;

void HandleInput(std::istream& inputStream, std::string& word)
{
	inputStream >> word;
}

void HandleOutput(std::ostream& outputStream, Permutations const& permutations)
{
	for (auto &el : permutations)
	{
		outputStream << el << std::endl;
	}
}

void FindAllUniquePermutations(std::string word, int startIndex, int endIndex, Permutations& uniquePermutations) {
	if (startIndex == endIndex) {
		uniquePermutations.emplace(word);
	}
	else {
		for (int i = startIndex; i <= endIndex; i++) {
			std::swap(word[startIndex], word[i]);
			FindAllUniquePermutations(word, startIndex + 1, endIndex, uniquePermutations);
			std::swap(word[startIndex], word[i]);
		}
	}
}

std::set<std::string> GetPermutationsSet(std::string const& word)
{
	Permutations uniquePermutationsSet;
	FindAllUniquePermutations(word, 0, word.size() - 1, uniquePermutationsSet);
	return uniquePermutationsSet;
}

int main()
{
	std::ifstream inputFile("input.txt");
	if (!inputFile.is_open())
	{
		return 1;
	}

	std::string word;
	HandleInput(inputFile, word);

	std::set<std::string> permutations = GetPermutationsSet(word);

	std::ofstream outputFile("output.txt");
	if (!outputFile.is_open())
	{
		return 1;
	}

	HandleOutput(outputFile, permutations);
	return 0;
}