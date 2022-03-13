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
