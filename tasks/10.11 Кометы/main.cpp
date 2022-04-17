/*
 * ����� �������:
 * 10.11. ������ (6)
 * �������� ������� ������� ��������. �� ��������� ����� ���������� ������� ������� Co
 * � ����� ����� ���������� ������� ����� � ����������� �� ������� � ���� Y = At + B.
 * � ���������� ������������� ��� ������� ���������� ������������ A � B ��� ���� ���������
 * �����. ������� � ����� ������ ������� ������ ��������� � ���� �������� ������ � ����������
 * ��������. ��� ������ � ������ ������ ������� ����������� �������, �� ��������� �� ���
 * ���� ����������. ��� ������ ������ ��������� ��� ���������� ����� ����������� �������
 * ����������� �� ������ �� ������������ ������ �������. �������� ��������� �������.
 *
 * ���� �� ����� INPUT.TXT. � ������ ������ ������� N � T (1 <= N, T <= 2000) � �����
 * ����� � ������ ����������. � ��������� N ������� ���������� ������������ Ai � Bi
 * (-100 <= Ai, Bi <= 100) ��� ���� N �����. ��� ����� N, T, Ai, Bi �����. ����������
 * ����� � ����, ��� ������� ������ � �������� Co ����� ���� ��� �������������, ��� � �������������.
 *
 * ����� � ���� OUTPUT.TXT. � ������������ ������ ������� ����������� ������� ������, ������� �����
 * ��������� ���������� � ������ �� 0 �� T � ��������� 10 ������ ����� �������.
 *
 * ������
 *
 * ����
 * 2 4
 * 1 1
 * -1 5
 *
 * �����
 * 3.0000000000
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
#include <vector>

using Coefficients = std::vector<std::pair<int, int>>;

constexpr double PRECISION = 1e-12;
constexpr int PRINT_PRECISION = 10;

bool ApproximatelyEqual(double a, double b)
{
	return std::abs(a - b) < PRECISION;
}

bool GreaterWithinPrecision(double a, double b)
{
	if (ApproximatelyEqual(a, b))
	{

		return false;
	}
	return a > b;
}

double FindMaxBrightnessForTime(double t, Coefficients const& coefficients)
{
	double maxBrightness = std::numeric_limits<double>::lowest();
	for (auto const& [A, B] : coefficients)
	{
		double const Y = A * t + B;
		if (Y > maxBrightness)
		{
			maxBrightness = Y;
		}
	}

	return maxBrightness;
}

double FindMinBrightnessOverTime(double overallTime, Coefficients const& coefficients)
{
	double low = 0;
	double high = overallTime;

	double lowValue = FindMaxBrightnessForTime(low, coefficients);
	double highValue = FindMaxBrightnessForTime(high, coefficients);

	while (GreaterWithinPrecision(std::abs(highValue - lowValue), PRECISION))
	{
		double const low3 = (2 * low + high) / 3;
		double const high3 = (low + 2 * high) / 3;

		double const low3Value = FindMaxBrightnessForTime(low3, coefficients);
		double const high3Value = FindMaxBrightnessForTime(high3, coefficients);

		if (GreaterWithinPrecision(low3Value, high3Value))
		{
			low = low3;
			lowValue = low3Value;
		}
		else
		{
			high = high3;
			highValue = high3Value;
		}
	}

	return FindMaxBrightnessForTime((low + high) / 2, coefficients);
}

void Solve(std::istream& input, std::ostream& output)
{
	int N;
	int T;
	input >> N >> T;

	Coefficients coefficients(N);
	for (int i = 0; i < N; ++i)
	{
		auto& current = coefficients[i];
		input >> current.first >> current.second;
	}

	auto const minBrightness = FindMinBrightnessOverTime(T, coefficients);

	output << std::fixed << std::setprecision(PRINT_PRECISION)
		   << minBrightness << '\n';
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
