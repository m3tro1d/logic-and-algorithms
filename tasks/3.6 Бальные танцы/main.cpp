/*
 * Текст задания:
 * 3.6. Бальные танцы (6)
 * В школу бальных танцев профессора Падеграса записались N учеников — мальчиков и девочек.
 * Профессор построил их в один ряд, и хочет отобрать из них для первого занятия группу стоящих
 * подряд учеников, в которой количество мальчиков и девочек одинаково. Сколько вариантов
 * выбора есть у профессора? Решить задачу с помощью рекуррентных соотношений.
 *
 * Ввод. В первой строке входного файла задано число N (1 <= N <= 10^6). Во второй строке задается
 * описание построенного ряда из мальчиков и девочек — строка из N символов a и b
 * (символ a соответствует девочке, а символ b — мальчику).
 *
 * Вывод. В единственной строке выходного файла должно содержаться количество вариантов выбора требуемой группы.
 *
 * Примеры
 *
 * Ввод 1         Ввод 2
 * 3              8
 * bab            abbababa
 *
 * Вывод 1        Вывод 2
 * 2              13
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
#include <iostream>
#include <vector>

using ll = long long;

constexpr int MAX = 1000001;

constexpr char BOY = 'b';
constexpr char GIRL = 'a';

ll FindVariants(std::istream& input, int N)
{
	ll result = 0;
	std::vector<int> values(MAX * 2, 0);

	char ch;
	int depth = 0;
	for (int i = 0; i < N; ++i)
	{
		input.get(ch);
		if (ch == BOY)
		{
			++depth;
		}
		else if (ch == GIRL)
		{
			--depth;
		}

		if (depth == 0)
		{
			++result;
		}

		result += values[depth + MAX];
		++values[depth + MAX];
	}

	return result;
}

void Solve(std::istream& input, std::ostream& output)
{
	int N;
	input >> N;
	input.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

	output << FindVariants(input, N) << '\n';
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
