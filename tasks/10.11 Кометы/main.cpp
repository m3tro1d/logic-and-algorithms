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
 * Суть алгоритма: находим минимальную яркость из максимальных
 * по всем кометам и по всей оси t с заданным шагом.
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
