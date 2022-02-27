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

const std::string CLOCKWISE = "clockwise";
const std::string UNCLOCKWISE = "unclockwise";
const std::string IMMOVABLE = "immovable";
const std::string BLOCK = "block";

void Solve(std::istream& input, std::ostream& output)
{
	int N, M;
	input >> N >> M;
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
