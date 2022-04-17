/*
 * Текст задания:
 * 10.11. Кометы (6)
 * Астроном Коперни увлечен кометами. Он определил новую физическую единицу яркости Co
 * и вывел закон нахождения яркости комет в зависимости от времени в виде Y = At + B.
 * В дальнейших исследованиях ему удалось рассчитать коэффициенты A и B для всех известных
 * комет. Коперни в любой момент времени всегда наблюдает в свой телескоп комету с наибольшей
 * яркостью. Как только у другой кометы яркость оказывается большей, он переносит на нее
 * свои наблюдения. Для заказа нового телескопа ему необходимо знать минимальную яркость
 * наблюдаемой им кометы на определенный период времени. Помогите астроному Коперни.
 *
 * Ввод из файла INPUT.TXT. В первой строке указаны N и T (1 <= N, T <= 2000) – число
 * комет и период наблюдения. В следующих N строках содержатся коэффициенты Ai и Bi
 * (-100 <= Ai, Bi <= 100) для всех N комет. Все числа N, T, Ai, Bi целые. Необходимо
 * иметь в виду, что яркость кометы в единицах Co может быть как положительной, так и отрицательной.
 *
 * Вывод в файл OUTPUT.TXT. В единственной строке вывести минимальную яркость кометы, которую будет
 * наблюдать астрономом в период от 0 до T с точностью 10 знаков после запятой.
 *
 * Пример
 *
 * Ввод
 * 2 4
 * 1 1
 * -1 5
 *
 * Вывод
 * 3.0000000000
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
