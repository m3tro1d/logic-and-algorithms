/*
 * ����� �������:
 * 2.10. ���������� (7)
 * ������� ������� ���������� ����������, ��������������� �� 1 �� N. ������ ���� ������� ���������� ����������.
 * ������ ������ ��������� ��  ������� �������. ���������� �������� �������� ���� ����������.
 *
 *  �������� ��������:
 * �	clockwise - �� �������;
 * �	unclockwise - ������;
 * �	immovable - ���������� ����������;
 * �	block - ������������.
 *
 * ���� �� ����� INPUT.TXT. � ������ ������ �������� ����� ������ ����� N - ���������� ���������� (2 <= N <= 10000)
 * � M - ���������� ��� (1 <= M <= 100000). �� ��������� M ������� ������� ���� ���������� � ���� ���� ������� ����� ������.
 *
 * ����� � ���� OUTPUT.TXT. � i-� ������ ������ ���� ���������� � �������� i-� ����������: clockwise - �� �������,
 * against - ������, immovable � ���������� ����������. ���� ������� �������������, �� ������ block.
 *
 * �������
 *
 * ���� 1       ���� 2
 * 5 4          5 4
 * 1 2          1 2
 * 2 3          2 3
 * 3 4          1 3
 * 4 1          4 5
 *
 * ����� 1      ����� 2
 * clockwise    block
 * unclockwise
 * clockwise
 * unclockwise
 * immovable
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
