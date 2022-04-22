/*
 * Текст задания:
 * 7.3. Прямоугольники 1 (8)
 * На координатной плоскости задано N прямоугольников со сторонами, параллельными координатным осям.
 * Найти площадь фигуры, получающейся в результате объединения прямоугольников.
 *
 * Ввод из файла INPUT.TXT. В первой строке содержится значение N (1 <= N <= 5000).
 * В каждой из следующих N  строк – четыре целых числа Ai, Bi, Ci, Di через пробел,
 определяющие координаты левого верхнего и правого нижнего углов  очередного  прямоугольника
 * (-106 <= Ai, Bi, Ci, Di <= 106; Ai <= Ci; Bi >= Di).
 *
 * Вывод в файл OUTPUT.TXT единственного целого числа - площади фигуры.
 *
 * Пример
 *
 * Ввод
 * 2
 * 5 15 25 5
 * 0 10 20 0
 *
 * Вывод
 * 325
 *
 *
 * Выполнил:
 * Хафизов Булат, ПС-21
 *
 * Среда выполнения:
 * Visual Studio 2022
 */

#define _CRT_SECURE_NO_WARNINGS
#include <algorithm>
#include <array>
#include <fstream>
#include <iostream>
#include <vector>

struct Point
{
	int x;
	int y;
};

using Points = std::vector<Point>;
using RectanglesPoints = std::array<Points, 2>;

bool DoesRectangleIntersect(Point const& leftTop, Point const& rightBottom, int x)
{
	return leftTop.x <= x && rightBottom.x > x;
}

void DoubleSort(std::vector<int> coordinates, std::vector<int>& indicators, int left, int right)
{
	int pivot = coordinates[(left + right) / 2];
	int i = left;
	int j = right;
	do
	{
		while (pivot > coordinates[i])
		{
			++i;
		}
		while (pivot < coordinates[j])
		{
			--j;
		}

		if (i <= j)
		{
			std::swap(coordinates[i], coordinates[j]);
			std::swap(indicators[i], indicators[j]);
			++i;
			--j;
		}
	} while (i <= j);

	if (left < j)
	{
		DoubleSort(coordinates, indicators, left, j);
	}
	if (i < right)
	{
		DoubleSort(coordinates, indicators, i, right);
	}
}

void Solve(std::istream& input, std::ostream& output)
{
	size_t N;
	input >> N;

	RectanglesPoints points;
	std::vector<int> xCoordinates(2 * N);
	for (size_t i = 0; i < N; ++i)
	{
		Point leftTopCorner;
		input >> leftTopCorner.x >> leftTopCorner.y;
		Point rightBottomCorner;
		input >> rightBottomCorner.x >> rightBottomCorner.y;

		points[0].push_back(leftTopCorner);
		points[1].push_back(rightBottomCorner);

		xCoordinates[2 * i] = leftTopCorner.x;
		xCoordinates[2 * i + 1] = rightBottomCorner.x;
	}

	std::sort(xCoordinates.begin(), xCoordinates.end());

	int sectionHeight = 0;
	int result = 0;
	for (size_t i = 0; i < 2 * N; ++i)
	{
		if (i != 0)
		{
			result += std::abs((xCoordinates[i] - xCoordinates[i - 1]) * sectionHeight);
		}

		if (i == 0 || xCoordinates[i] != xCoordinates[i - 1])
		{
			size_t M = 0;
			std::vector<int> yCoordinates(2 * N);
			std::vector<int> sectionIndicators(2 * N);

			for (size_t j = 0; j < N; ++j)
			{
				if (DoesRectangleIntersect(points[0][j], points[1][j], xCoordinates[i]))
				{
					yCoordinates[M] = points[0][j].y;
					yCoordinates[M + 1] = points[1][j].y;

					sectionIndicators[M] = 1;
					sectionIndicators[M + 1] = -1;

					M += 2;
				}

				if (M == 0)
				{
					sectionHeight = 0;
				}
				else
				{
					DoubleSort(yCoordinates, sectionIndicators, 0, M - 1);

					int sc = 0;
					int bb = 0;
					if (sectionIndicators[0] > 0)
					{
						++bb;
					}
					for (size_t k = 1; k < N; ++k)
					{
						if (bb > 0)
						{
							sc += yCoordinates[k] - yCoordinates[k - 1];
							bb += sectionIndicators[k];
						}
					}

					sectionHeight = std::abs(sc);
				}
			}
		}
	}

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
