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
#include <vector>

void Solve(std::istream& input, std::ostream& output)
{
	int L, N;
	input >> L >> N;

	std::vector<int> C(N);
	for (int i = 0; i < N; ++i)
	{
		input >> C[i];
	}

	std::vector<int> values(L + 1, 0);
	std::vector<int> last(L + 1, 0);
	for (int i = 1; i <= L; ++i)
	{
		values[i] = std::numeric_limits<int>::max();
		for (auto const& coin : C)
		{
			if (i - coin >= 0 && values[i - coin] + 1 < values[i])
			{
				values[i] = values[i - coin] + 1;
				last[i] = coin;
			}
		}
	}

	output << values[L] << '\n';
	while (L > 0)
	{
		output << last[L] << ' ';
		L -= last[L];
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
