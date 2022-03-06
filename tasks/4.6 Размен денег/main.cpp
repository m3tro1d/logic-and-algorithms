/*
 * Текст задания:
 * 4.6. Размен денег (6)
 * Требуется разменять заданную сумму денег минимальным количеством монет.
 *
 * Ввод. Первая строка файла INPUT.TXT содержит сумму денег L (1 <= L <= 20000) и
 * количество типов монет N (1 <= N <= 30). Вторая строка содержит N значений
 * Ci через пробел: стоимости типов монет (1 <= Ci <= L).
 *
 * Вывод. В первой строке выводится количество типов монет K, необходимое для
 * размена, и общее минимальное количество монет M. В следующих K строках выводятся
 * через пробел по 2 числа: стоимость монеты и количество экземпляров данной монеты.
 * Эти K строк должны выводится в порядке убывания стоимости монет. Если имеется
 * несколько вариантов решения, достаточно вывести любой из них. Если указанную сумму
 * разменять невозможно, то выходной файл должен содержать No.
 *
 * Примеры
 *
 * Ввод 1      Ввод 2
 * 15 3        12 3
 * 5 11 1      1 10 3
 *
 * Вывод 1     Вывод 2
 * 1 3         2 3
 * 5 3         10 1
 *             1 2
 *
 *
 * Выполнил:
 * Хафизов Булат, ПС-21
 *
 * Среда выполнения:
 * Visual Studio 2022
 */

#define _CRT_SECURE_NO_WARNINGS
#include <fstream>
#include <iostream>
#include <vector>

int CalculateMinChange(int sum, const std::vector<int>& coins, std::vector<int>& cache, std::vector<int>& last)
{
	if (sum <= 0)
	{
		return 0;
	}

	if (cache[sum] != 0)
	{
		return cache[sum];
	}

	int min = INT_MAX;
	for (auto const& coin : coins)
	{
		if (sum == coin)
		{
			last[sum] = coin;
			return 1;
		}

		if (sum >= coin)
		{
			int value = CalculateMinChange(sum - coin, coins, cache, last) + 1;
			if (value < min)
			{
				min = value;
				last[sum] = coin;
			}
		}
	}

	cache[sum] = min;
	return min;
}

void PrintResult(std::ostream& output, int minChange, int sum, const std::vector<int>& last)
{
	output << minChange << '\n';
	while (sum > 0)
	{
		output << last[sum] << ' ';
		sum -= last[sum];
	}
}

void Solve(std::istream& input, std::ostream& output)
{
	int L, N;
	input >> L >> N;

	std::vector<int> C(N);
	for (int i = 0; i < N; ++i)
	{
		input >> C[i];
	}

	std::vector<int> cache(L + 1, 0);
	std::vector<int> last(L + 1, 0);

	int minChange = CalculateMinChange(L, C, cache, last);
	if (minChange > 0)
	{
		PrintResult(output, minChange, L, last);
	}
	else
	{
		output << "No";
	}

	output << '\n';
}

int main()
{
	std::ifstream input("input.txt");
	std::ofstream output("output.txt");

	input.tie(nullptr);
	std::cin.tie(nullptr);
	std::ios::sync_with_stdio(false);

	Solve(input, output);
}
