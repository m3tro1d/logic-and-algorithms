/*
 * ����� �������:
 * 1.4. ���������� ���� (6)
 * � ����������� ������ ���� ������ ��������. ��� �� ������ ��������� ������� ���� �������.
 * �� ��� ����������� ������� � ��������� ���������� ����������� ������� �������, �����������
 * �������, ������ ���� �����������. ������� ������ ����� � ����� ������������ ����� �� ����������
 * ������ ����� ���� �� �����. ����� �� �������� ����� ���� �� ������ ������ (� ���, ������,
 * ������� ��� ������). ����� ������� �� ������ ������ � ���� ����.
 * ����� ��������� ���� ������ ���������� 4 ����� ������, � ����� ��������� ����� ������
 * �� 9 �������� ����� 20 ������.
 *
 * �� �������� ������������ ���� ����� ���������� ����������� ����� ������ ��� ������.
 *
 * ����. � ������ ������ �������� ����� ������ ��� ����� N � K (1 <= N, K <= 300)� ���������� ����� � �������� ������.
 * � ��������� N ������� ���������� ������������������ �� K �������� (������ ��� �����).
 * �������� ������������ ������������ ������, � ����� � ��� ���������� � ���� ������������ �����.
 *
 * �����. � ������������ ������ ��������� ����� ������ ������, ����������� ��� ������������.
 *
 * �������
 *
 * ���� 1      ���� 2
 * 3 6         5 7
 * 001110      0101010
 * 011011      1111111
 * 011110      0101010
 *             1100011
 *             0111110
 *
 * ����� 1     ����� 2
 * 16          32
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
#include <vector>

using Column = std::vector<char>;
using Field = std::vector<Column>;

constexpr char EMPTY = '0';
constexpr char TREE = '1';
constexpr char FENCED = '2';
constexpr char EMPTY_EXTERNAL = '3';

void FillExternal(Field& field, int const& N, int const& K, int row, int column)
{
	if (field[row][column] == EMPTY)
	{
		field[row][column] = EMPTY_EXTERNAL;

		if (row + 1 < N)
		{
			FillExternal(field, N, K, row + 1, column);
		}

		if (row - 1 >= 0)
		{
			FillExternal(field, N, K, row - 1, column);
		}

		if (column + 1 < K)
		{
			FillExternal(field, N, K, row, column + 1);
		}

		if (column - 1 >= 0)
		{
			FillExternal(field, N, K, row, column - 1);
		}
	}
}

void PutFences(Field& field, int& result, int row, int column)
{
	if (field[row][column] == TREE)
	{
		field[row][column] = FENCED;

		if (field[row + 1][column] == EMPTY_EXTERNAL)
		{
			++result;
		}
		if (field[row - 1][column] == EMPTY_EXTERNAL)
		{
			++result;
		}
		if (field[row][column + 1] == EMPTY_EXTERNAL)
		{
			++result;
		}
		if (field[row][column - 1] == EMPTY_EXTERNAL)
		{
			++result;
		}

		PutFences(field, result, row + 1, column);
		PutFences(field, result, row - 1, column);
		PutFences(field, result, row, column + 1);
		PutFences(field, result, row, column - 1);
	}
}

void Solve(std::istream& input, std::ostream& output)
{
	int N, K;
	input >> N >> K;

	Field field(N + 2, Column(K + 2, EMPTY));
	int startRow = 0;
	int startColumn = 0;
	for (int i = 1; i <= N; ++i)
	{
		for (int j = 1; j <= K; ++j)
		{
			input >> field[i][j];
			if (field[i][j] == TREE && startRow == 0 && startColumn == 0)
			{
				startRow = i;
				startColumn = j;
			}
		}
	}

	FillExternal(field, N + 2, K + 2, 0, 0);

	int result = 0;
	PutFences(field, result, startRow, startColumn);

	output << result << '\n';
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
