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
#include <vector>
#include <set>


void HandleInput(std::istream& inputStream, std::string& word)
{
	inputStream >> word;
}

void HandleOutput(std::ostream& outputStream, std::set<std::string> const& permutations)
{
	for (auto &el : permutations)
	{
		outputStream << el;
	}
}

std::set<std::string> FindAllPermutationsInString(std::string const& word)
{

	std::set<std::string> permutations;
	return permutations;
}

int main()
{
	std::string word;

	std::ifstream inputFile("input.txt");
	if (!inputFile.is_open())
	{
		return 1;
	}

	HandleInput(inputFile, word);

	std::set<std::string> permutations = FindAllPermutationsInString(word);

	std::ofstream outputFile("output.txt");
	if (!outputFile.is_open())
	{
		return 1;
	}

	HandleOutput(outputFile, permutations);
	return 0;
}