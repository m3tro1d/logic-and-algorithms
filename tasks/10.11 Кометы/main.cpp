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

using Coefficients = std::vector<int>;

constexpr double STEP = 0.01;
constexpr int PRINT_PRECISION = 10;

double FindMaxBrightnessForTime(double t, int N, Coefficients const& A, Coefficients const& B)
{
	double maxBrightness = std::numeric_limits<double>::min();
	for (int i = 0; i < N; ++i)
	{
		double const S = A[i] * t + B[i];
		if (S > maxBrightness)
		{
			maxBrightness = S;
		}
	}

	return maxBrightness;
}

/*
 * ���� ���������: ������� ����������� ������� �� ������������
 * �� ���� ������� � �� ���� ��� t � �������� �����.
 */
double FindMinBrightnessOverTime(double overallTime, Coefficients const& A, Coefficients const& B)
{
	double minBrightness = std::numeric_limits<double>::max();

	for (double currentTime = 0; currentTime <= overallTime; currentTime += STEP)
	{
		double const currentBrightness = FindMaxBrightnessForTime(currentTime, A.size(), A, B);

		if (currentBrightness < minBrightness)
		{
			minBrightness = currentBrightness;
		}
	}

	return minBrightness;
}

void Solve(std::istream& input, std::ostream& output)
{
	int N;
	int T;
	input >> N >> T;

	Coefficients A(N);
	Coefficients B(N);
	for (int i = 0; i < N; ++i)
	{
		input >> A[i] >> B[i];
	}

	auto const minBrightness = FindMinBrightnessOverTime(T, A, B);

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
