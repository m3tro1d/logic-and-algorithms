/*
 * ����� �������:
 * 7.3. �������������� 1 (8)
 * �� ������������ ��������� ������ N ��������������� �� ���������, ������������� ������������ ����.
 * ����� ������� ������, ������������ � ���������� ����������� ���������������.
 * 
 * ���� �� ����� INPUT.TXT. � ������ ������ ���������� �������� N (1 <= N <= 5000).
 * � ������ �� ��������� N  ����� � ������ ����� ����� Ai, Bi, Ci, Di ����� ������,
 ������������ ���������� ������ �������� � ������� ������� �����  ����������  �������������� 
 * (-106 <= Ai, Bi, Ci, Di <= 106; Ai <= Ci; Bi >= Di).
 * 
 * ����� � ���� OUTPUT.TXT ������������� ������ ����� - ������� ������.
 * 
 * ������
 * 
 * ����
 * 2     
 * 5 15 25 5
 * 0 10 20 0
 * 
 * ����� 
 * 325
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

void Solve(std::istream& input, std::ostream& output)
{
	int N;
	input >> N;

	// TODO
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
