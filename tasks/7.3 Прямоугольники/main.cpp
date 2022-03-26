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
