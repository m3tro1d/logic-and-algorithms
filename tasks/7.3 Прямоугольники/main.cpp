/*
 * Текст задания:
 * 7.3. Прямоугольники 1 (8)
 * На координатной плоскости задано N прямоугольников со сторонами, параллельными координатным осям.
 * Найти площадь фигуры, получающейся в результате объединения прямоугольников.
 *
 * Ввод из файла INPUT.TXT. В первой строке содержится значение N (1 <= N <= 5000).
 * В каждой из следующих N  строк – четыре целых числа Ai, Bi, Ci, Di через пробел,
 определяющие координаты левого верхнего и правого нижнего углов  очередного  прямоугольника
 * (-10^6 <= Ai, Bi, Ci, Di <= 10^6; Ai <= Ci; Bi >= Di).
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
#include <fstream>
#include <iostream>
#include <tuple>
#include <vector>

using ll = long long;

struct Segment
{
	int xl, xr, y, type;
};

std::tuple<size_t, std::vector<int>, std::vector<Segment>> ReadCoordinates(std::istream& input)
{
	size_t N;
	input >> N;

	std::vector<int> x;
	std::vector<Segment> seg;
	for (size_t i = 0; i < N; ++i)
	{
		int x1, x2, y1, y2;
		input >> x1 >> y1 >> x2 >> y2;

		x.push_back(x1);
		x.push_back(x2);

		seg.push_back({ x1, x2, y1, 1 });
		seg.push_back({ x1, x2, y2, -1 });
	}

	return { N, x, seg };
}

void Sort(std::vector<int>& xCoordinates, std::vector<Segment>& segments)
{
	std::sort(xCoordinates.begin(), xCoordinates.end());
	std::sort(segments.begin(), segments.end(), [](Segment const& s1, Segment const& s2) {
		return s1.y < s2.y;
	});
}

ll CalculateResult(std::vector<int> const& xCoordinates, std::vector<Segment> const& segments, size_t N)
{
	ll result = 0;
	for (size_t i = 1; i < 2 * N; ++i)
	{
		int previousOrdinate = 0;
		int segmentCount = 0;

		for (size_t j = 0; j < 2 * N; ++j)
		{
			if (segments[j].xr <= xCoordinates[i - 1] || segments[j].xl >= xCoordinates[i])
			{
				continue;
			}

			if (segmentCount == 0)
			{
				previousOrdinate = segments[j].y;
			}

			segmentCount += segments[j].type;
			if (segmentCount == 0)
			{
				result += static_cast<ll>(segments[j].y - previousOrdinate) * static_cast<ll>(xCoordinates[i] - xCoordinates[i - 1]);
			}
		}
	}

	return result;
}

void Solve(std::istream& input, std::ostream& output)
{
	auto [N, xCoordinates, segments] = ReadCoordinates(input);

	Sort(xCoordinates, segments);
	auto result = CalculateResult(xCoordinates, segments, N);

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
