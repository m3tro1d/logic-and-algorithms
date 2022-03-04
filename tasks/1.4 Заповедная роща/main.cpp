/*
 * Текст задания:
 * 1.4. Заповедная роща (6)
 * В заповеднике растет роща редких деревьев. Для их защиты требуется обнести рощу забором.
 * Но для обеспечения доступа к остальной территории заповедника площадь участка, окруженного
 * забором, должна быть минимальной. Деревья растут точно в узлах координатной сетки на расстоянии
 * одного метра друг от друга. Любое из деревьев имеет хотя бы одного соседа (с юга, севера,
 * востока или запада). Забор состоит из блоков длиной в один метр.
 * Чтобы огородить одно дерево необходимо 4 блока забора, а чтобы огородить такую группу
 * из 9 деревьев нужно 20 блоков.
 *
 * По заданной конфигурации рощи найти минимально необходимое число блоков для забора.
 *
 * Ввод. В первой строке записаны через пробел два числа N и K (1 <= N, K <= 300)– количество строк и столбцов данных.
 * В следующих N строках содержатся последовательности из K символов (единиц или нулей).
 * Единицей обозначается расположение дерева, а нулем – его отсутствие в узле координатной сетки.
 *
 * Вывод. В единственной строке выводится число блоков забора, необходимое для огораживания.
 *
 * Примеры
 *
 * Ввод 1      Ввод 2
 * 3 6         5 7
 * 001110      0101010
 * 011011      1111111
 * 011110      0101010
 *             1100011
 *             0111110
 *
 * Вывод 1     Вывод 2
 * 16          32
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
