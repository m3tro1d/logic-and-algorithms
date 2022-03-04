/*
 * Текст задания:
 * 2.10. Шестеренки (7)
 * Имеется система сцепленных шестеренок, пронумерованных от 1 до N. Заданы пары номеров сцепленных шестеренок.
 * Первая должна двигаться по  часовой стрелке. Определить характер движения всех шестеренок.
 *
 *  Варианты движения:
 * •	clockwise - по часовой;
 * •	unclockwise - против;
 * •	immovable - шестеренка неподвижна;
 * •	block - заклинивание.
 *
 * Ввод из файла INPUT.TXT. В первой строке записаны через пробел число N - количество шестеренок (2 <= N <= 10000)
 * и M - количество пар (1 <= M <= 100000). Во следующих M строках указаны пары шестеренок в виде двух номеров через пробел.
 *
 * Вывод в файл OUTPUT.TXT. В i-й строке должна быть информация о движении i-й шестеренки: clockwise - по часовой,
 * against - против, immovable – шестеренка неподвижна. Если система заклинивается, то выдать block.
 *
 * Примеры
 *
 * Ввод 1       Ввод 2
 * 5 4          5 4
 * 1 2          1 2
 * 2 3          2 3
 * 3 4          1 3
 * 4 1          4 5
 *
 * Вывод 1      Вывод 2
 * clockwise    block
 * unclockwise
 * clockwise
 * unclockwise
 * immovable
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
#include <string>
#include <vector>

enum class Rotation
{
	CLOCKWISE,
	COUNTER_CLOCKWISE,
	IMMOVABLE,
};

using GearColumn = std::vector<bool>;
using GearSystem = std::vector<GearColumn>;

GearSystem ReadGearSystem(std::istream& input, int N, int M)
{
	GearSystem system(N, GearColumn(N, false));
	int firstGear, secondGear;
	for (int i = 0; i < M; ++i)
	{
		input >> firstGear >> secondGear;
		system[firstGear - 1][secondGear - 1] = true;
		system[secondGear - 1][firstGear - 1] = true;
	}

	return system;
}

bool MarkRotations(const GearSystem& system, std::vector<Rotation>& rotations, int currentGear)
{
	// TODO: current gear may be immovable by now
	//  we can't imply that current gear has been processed by now
	//  rotations can be marked recursively or with a queue, but not linear
	for (int i = 0; i < system.size(); ++i)
	{
		if (system[currentGear][i])
		{
			if (rotations[currentGear] == Rotation::CLOCKWISE)
			{
				if (rotations[i] == Rotation::CLOCKWISE)
				{
					return false;
				}

				rotations[i] = Rotation::COUNTER_CLOCKWISE;
			}
			else if (rotations[currentGear] == Rotation::COUNTER_CLOCKWISE)
			{
				if (rotations[i] == Rotation::COUNTER_CLOCKWISE)
				{
					return false;
				}

				rotations[i] = Rotation::CLOCKWISE;
			}
		}
	}

	return true;
}

std::vector<Rotation> GetGearRotations(const GearSystem& system)
{
	std::vector<Rotation> result(system.size(), Rotation::IMMOVABLE);
	result[0] = Rotation::CLOCKWISE;
	for (int i = 0; i < system.size(); ++i)
	{
		if (!MarkRotations(system, result, i))
		{
			return {};
		}
	}

	return result;
}

void PrintGearRotations(std::ostream& output, const std::vector<Rotation>& rotations)
{
	for (auto const& rotation : rotations)
	{
		switch (rotation)
		{
		case Rotation::CLOCKWISE:
			output << "clockwise\n";
			break;
		case Rotation::COUNTER_CLOCKWISE:
			output << "unclockwise\n";
			break;
		case Rotation::IMMOVABLE:
			output << "immovable\n";
			break;
		default:
			break;
		}
	}
}

void Solve(std::istream& input, std::ostream& output)
{
	int N, M;
	input >> N >> M;

	auto const system = ReadGearSystem(input, N, M);

	auto const rotations = GetGearRotations(system);
	if (!rotations.empty())
	{
		PrintGearRotations(output, rotations);
	}
	else
	{
		output << "block\n";
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
