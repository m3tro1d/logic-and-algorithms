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
#include <queue>
#include <vector>

using Column = std::vector<char>;
using Field = std::vector<Column>;

struct Cell
{
	int row = 0;
	int column = 0;
};

constexpr char EMPTY = '0';
constexpr char TREE = '1';
constexpr char FENCED = '2';
constexpr char EMPTY_EXTERNAL = '3';

void FillExternal(Field& field, int const& N, int const& K, const Cell& cell)
{
	if (field[cell.row][cell.column] == EMPTY)
	{
		field[cell.row][cell.column] = EMPTY_EXTERNAL;

		if (cell.row + 1 < N)
		{
			FillExternal(field, N, K, { cell.row + 1, cell.column });
		}

		if (cell.row - 1 >= 0)
		{
			FillExternal(field, N, K, { cell.row - 1, cell.column });
		}

		if (cell.column + 1 < K)
		{
			FillExternal(field, N, K, { cell.row, cell.column + 1 });
		}

		if (cell.column - 1 >= 0)
		{
			FillExternal(field, N, K, { cell.row, cell.column - 1 });
		}
	}
}

void PutFences(Field& field, int& result, const Cell& cell)
{
	if (field[cell.row][cell.column] == TREE)
	{
		field[cell.row][cell.column] = FENCED;

		if (field[cell.row + 1][cell.column] == EMPTY_EXTERNAL)
		{
			++result;
		}
		if (field[cell.row - 1][cell.column] == EMPTY_EXTERNAL)
		{
			++result;
		}
		if (field[cell.row][cell.column + 1] == EMPTY_EXTERNAL)
		{
			++result;
		}
		if (field[cell.row][cell.column - 1] == EMPTY_EXTERNAL)
		{
			++result;
		}

		PutFences(field, result, { cell.row + 1, cell.column });
		PutFences(field, result, { cell.row - 1, cell.column });
		PutFences(field, result, { cell.row, cell.column + 1 });
		PutFences(field, result, { cell.row, cell.column - 1 });
	}
}

void Solve(std::istream& input, std::ostream& output)
{
	int N, K;
	input >> N >> K;

	Field field(N + 2, Column(K + 2, EMPTY));
	Cell start;
	for (int i = 1; i <= N; ++i)
	{
		for (int j = 1; j <= K; ++j)
		{
			input >> field[i][j];
			if (field[i][j] == TREE && start.row == 0 && start.column == 0)
			{
				start.row = i;
				start.column = j;
			}
		}
	}

	FillExternal(field, N + 2, K + 2, { 0, 0 });

	int result = 0;
	PutFences(field, result, start);

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
