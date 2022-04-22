/*
 * ����� �������:
 * 11.6. ����� ����� (6)
 * ������� ���� ������� R � ������� � ������ ���������. ������ ��� ����� (X1, Y1) � (X2, Y2).
 * ��������� ����� ����������� ����� �����, ����������� ��� �����, �� �� ������������ ������������ �����.
 *
 * ���� �� ����� INPUT.TXT. � ������ ������ ��������� ����� ����� N � ���������� ������ ������� ������.
 * ����� ������� N �����, ������ �� ������� �������� ���� ������������ ����� ����� ������ � X1, Y1, X2, Y2 � R.
 *
 * ����� � ���� OUTPUT.TXT. ��� ������� ����� ������� ������ ��������� ���� ������������ ����� � ����� �������
 * ����� ������� - ����������� ����� �����.
 *
 * ������
 *
 * ����
 * 2
 * 1 1 -1 -1 1
 * 1 1 -1 1 1
 *
 * �����
 * 3.571
 * 2.000
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
#include <iomanip>
#include <iostream>

constexpr std::streamsize PRINT_PRECISION = 3;

struct Point
{
	double x;
	double y;
};

Point ReadPoint(std::istream& input)
{
	double x, y;
	input >> x >> y;
	return { x, y };
}

double FindMinLineLength(Point const& p1, Point const& p2, double radius)
{
	// TODO
	return 0;
}

void Solve(std::istream& input, std::ostream& output)
{
	size_t N;
	input >> N;

	for (size_t i = 0; i < N; ++i)
	{
		auto const p1 = ReadPoint(input);
		auto const p2 = ReadPoint(input);

		double r;
		input >> r;

		output << std::fixed << std::setprecision(PRINT_PRECISION)
			   << FindMinLineLength(p1, p2, r) << '\n';
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
