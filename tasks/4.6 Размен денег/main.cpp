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
#include <limits>
#include <map>
#include <vector>

int FindMinChange(int overallSum, const std::vector<int>& coins, std::vector<int>& last)
{
	std::vector<int> values(overallSum + 1, -1);
	values[0] = 0;
	for (int currentSum = 1; currentSum <= overallSum; ++currentSum)
	{
		auto min = std::numeric_limits<int>::max();
		for (auto const& coin : coins)
		{
			if (currentSum >= coin)
			{
				auto const& valueForCoin = values[currentSum - coin];
				if (valueForCoin != -1 && valueForCoin + 1 < min)
				{
					min = valueForCoin + 1;
					last[currentSum] = coin;
				}
			}
		}

		if (min < std::numeric_limits<int>::max())
		{
			values[currentSum] = min;
		}
	}

	return values[overallSum];
}

void PrintSolution(std::ostream& output, int sum, int minChange, const std::vector<int>& last)
{
	std::map<int, int> coinOccurrences;
	while (sum > 0)
	{
		int coinValue = last[sum];
		sum -= coinValue;
		++coinOccurrences[coinValue];
	}

	output << coinOccurrences.size() << ' ' << minChange << '\n';
	for (auto it = coinOccurrences.rbegin(); it != coinOccurrences.rend(); ++it)
	{
		output << it->first << ' ' << it->second << '\n';
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

	std::vector<int> last(L + 1, 0);
	int minChange = FindMinChange(L, C, last);

	if (minChange > 0)
	{
		PrintSolution(output, L, minChange, last);
	}
	else
	{
		output << "No\n";
	}
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
