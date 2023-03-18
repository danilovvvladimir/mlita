//14.2.Произведение(6)
//Среди всех наборов различных целых чисел, сумма которых равна заданному числу N(1 ≤ N ≤
//	10000), найдите тот, который имеет максимальное произведение входящих в него чисел.
//	Ввод из файла INPUT.TXT.В единственной строке вводится N.
//	Вывод в файл OUTPUT.TXT.В единственной строке выдаются слагаемые через пробел.
//	Примеры
//	Ввод 1 Ввод 2
//	8 100
//	Вывод 1 Вывод 2
//	3 5 2 3 5 6 7 8 9 10 11 12 13 14
//
// Данилов Владимир, ПС-21. Visual Studio 2017.
//

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;
// Все проверять

// Function to find maximum product
int maxProduct(int N)
{
	// Vector to store all combinations 
	vector<int> arr;

	// Find all combinations of different 
	// elements whose sum is equal to N 
	for (int i = 1; i <= N; i++) {
		for (int j = i + 1; j <= N; j++) {
			if (i + j == N)
				arr.push_back(i * j);
		}
	}

	// Sort the vector 
	sort(arr.begin(), arr.end());

	// Return the last element 
	return arr[arr.size() - 1];
}

// Driver code 
int main()
{
	int N = 6;
	cout << maxProduct(N);
	return 0;
}