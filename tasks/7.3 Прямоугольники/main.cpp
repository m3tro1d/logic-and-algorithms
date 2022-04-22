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
#include <fstream>
#include <iostream>
#include <vector>

using ll = long long;

struct Segment
{
	int xl, xr, y, type;
};

void Solve(std::istream& input, std::ostream& output)
{
	int N;
	input >> N;

	std::vector<int> x;
	std::vector<Segment> seg;
	for (int i = 0; i < N; ++i)
	{
		int x1, x2, y1, y2;
		input >> x1 >> y1 >> x2 >> y2;

		x.push_back(x1);
		x.push_back(x2);

		seg.push_back({ x1, x2, y1, 1 });
		seg.push_back({ x1, x2, y2, -1 });
	}

	std::sort(x.begin(), x.end());
	std::sort(seg.begin(), seg.end(), [](Segment const& s1, Segment const& s2) {
		return s1.y < s2.y;
	});

	ll result = 0;
	for (int i = 1; i < 2 * N; ++i)
	{
		int prevY = 0, cnt = 0;
		for (int j = 0; j < 2 * N; ++j)
		{
			if (seg[j].xr <= x[i - 1] || seg[j].xl >= x[i])
			{
				continue;
			}
			if (cnt == 0)
			{
				prevY = seg[j].y;
			}
			cnt += seg[j].type;
			if (cnt == 0)
			{
				result += static_cast<ll>(seg[j].y - prevY) * static_cast<ll>(x[i] - x[i - 1]);
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
