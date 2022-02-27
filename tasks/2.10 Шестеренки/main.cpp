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
