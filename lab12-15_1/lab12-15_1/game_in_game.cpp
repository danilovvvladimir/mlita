//	15.1.Игра в игре(5)
//
//	Вася и Петя любят игры со спичками. Несколько дней они играли в следующую игру. Два игрока поочередно забирают из кучки, содержащей N спичек, от 1 до M спичек.
//	Выигрывает игрок, после хода которого кучка спичек опустеет.Доведя до совершенства свое мастерство, они решили изменить правила.Первый игрок задает значение N.
//	Потом второй игрок указывает величину M.Далее игроки поочередно берут спички, начиная с первого игрока.
//	По жребию первым игроком оказался Вася.Для продления удовольствия Петя при любых дальнейших ответах Васи собирается выиграть так, чтобы партия состояла из наибольшего числа ходов.
//	Укажите правильный ответ Пети.
//
//	Ввод из файла INPUT.TXT.В единственной строке содержится значение N(2 ≤ N ≤ 10^12).
//
//	Вывод в файл OUTPUT.TXT.В единственной строке выводится значение M(2 ≤ M ≤ N). Если у Пети нет выигрывающего хода, вывести 0.
//
//	Примеры
//	Ввод 1          Ввод 2
//	3               2
//	Вывод 1         Вывод 2
//	2               0
//	
//	Данилов Владимир, ПС-21. Visual Studio 2017.

#include <fstream>
#include <iostream>

using LongNumber = unsigned long long;

void HandleInput(std::istream& inputStream, LongNumber& N)
{
	inputStream >> N;
}

void HandleOutput(std::ostream& outputStream, LongNumber& M)
{
	outputStream << M;
}

LongNumber FindStepsToWin(LongNumber& N)
{
	for (LongNumber i = 3; i <= static_cast<LongNumber>(N >= 10e8 ? (std::sqrt(N) + 1) : N / 2); i++)
	{
		if (N % i == 0)
		{
			return i - 1;
		}
	}

	if ((N - 1) > 1)
	{
		return N - 1;
	}

	return 0;
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

	LongNumber M = FindStepsToWin(N);

	std::ofstream outputFile("output.txt");
	if (!outputFile.is_open())
	{
		return 1;
	}

	HandleOutput(outputFile, M);
	return 0;
}