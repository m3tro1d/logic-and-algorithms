/*
 * ����� �������:
 * 4.6. ������ ����� (6)
 * ��������� ��������� �������� ����� ����� ����������� ����������� �����.
 *
 * ����. ������ ������ ����� INPUT.TXT �������� ����� ����� L (1 <= L <= 20000) �
 * ���������� ����� ����� N (1 <= N <= 30). ������ ������ �������� N ��������
 * Ci ����� ������: ��������� ����� ����� (1 <= Ci <= L).
 *
 * �����. � ������ ������ ��������� ���������� ����� ����� K, ����������� ���
 * �������, � ����� ����������� ���������� ����� M. � ��������� K ������� ���������
 * ����� ������ �� 2 �����: ��������� ������ � ���������� ����������� ������ ������.
 * ��� K ����� ������ ��������� � ������� �������� ��������� �����. ���� �������
 * ��������� ��������� �������, ���������� ������� ����� �� ���. ���� ��������� �����
 * ��������� ����������, �� �������� ���� ������ ��������� No.
 *
 * �������
 *
 * ���� 1      ���� 2
 * 15 3        12 3
 * 5 11 1      1 10 3
 *
 * ����� 1     ����� 2
 * 1 3         2 3
 * 5 3         10 1
 *             1 2
 *
 *
 * ��������:
 * ������� �����, ��-21
 *
 * ����� ����������:
 * Visual Studio 2022
 */

#define _CRT_SECURE_NO_WARNINGS
#include <fstream>
#include <iostream>
#include <map>
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
			cache[sum] = coin;
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
	if (minChange > 0)
	{
		std::vector<int> coinAmounts(sum, 0);
		while (sum > 0)
		{
			int coin = last[sum];
			++coinAmounts[coin];
			sum -= coin;
		}

		int coinTypesAmount = 0;
		std::map<int, int> coinTypes;
		for (int i = 0; i < coinAmounts.size(); ++i)
		{
			if (coinAmounts[i] > 0)
			{
				++coinTypesAmount;
				coinTypes[i] = coinAmounts[i];
			}
		}

		output << coinTypesAmount << ' ' << minChange << '\n';
		for (auto it = coinTypes.rbegin(); it != coinTypes.rend(); ++it)
		{
			output << it->first << ' ' << it->second << '\n';
		}
	}
	else
	{
		output << "No\n";
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
	PrintResult(output, minChange, L, last);
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
