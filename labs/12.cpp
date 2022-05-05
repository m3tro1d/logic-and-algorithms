#include <bits/stdc++.h>

using FenwickTree = std::vector<int>;

void Add(FenwickTree& tree, int k, int d)
{
	for (; k < tree.size(); k = (k | (k + 1)))
	{
		tree[k] += d;
	}
}

FenwickTree BuildFenwickTree(std::vector<int> const& vector)
{
	FenwickTree result(vector.size(), 0);
	for (int i = 0; i < vector.size(); ++i)
	{
		Add(result, i, vector[i]);
	}

	return result;
}

int Rsq(FenwickTree const& tree, int r)
{
	int result = 0;
	for (; r >= 0; r = (r & (r + 1)) - 1)
	{
		result += tree[r];
	}

	return result;
}

int Rsq(FenwickTree const& tree, int l, int r)
{
	return Rsq(tree, r) - Rsq(tree, l - 1);
}

void Update(FenwickTree& tree, int k, int v)
{
	Add(tree, k, v - tree[k]);
}

void PrintTree(std::ostream& output, FenwickTree const& tree)
{
	std::copy(tree.begin(), tree.end(), std::ostream_iterator<int>(output, " "));
	output << '\n';
}

int main()
{
	std::vector<int> initialVector = { 7, 9, -4, 6, -5, 8 };
	auto tree = BuildFenwickTree(initialVector);

	std::string const RSQ_COMMAND = "rsq";
	std::string const ADD_COMMAND = "add";
	std::string const UPDATE_COMMAND = "update";
	std::string const EXIT_COMMAND = "exit";
	std::string const PROMPT = "> ";

	std::string command;
	int argument1;
	int argument2;

	std::cout << "Initial Tree: ";
	PrintTree(std::cout, tree);

	std::cout << "Commands:\n"
			  << RSQ_COMMAND << " l r: sum\n"
			  << ADD_COMMAND << " k D: add\n"
			  << UPDATE_COMMAND << " k V: update\n"
			  << EXIT_COMMAND << ": exit\n";

	while (std::cin)
	{
		std::cout << PROMPT;
		std::cin >> command;

		if (command == RSQ_COMMAND)
		{
			std::cin >> argument1 >> argument2;
			std::cout << "Result: " << Rsq(tree, argument1, argument2) << '\n';
		}
		else if (command == ADD_COMMAND)
		{
			std::cin >> argument1 >> argument2;
			Add(tree, argument1, argument2);

			std::cout << "Tree: ";
			PrintTree(std::cout, tree);
		}
		else if (command == UPDATE_COMMAND)
		{
			std::cin >> argument1 >> argument2;
			Update(tree, argument1, argument2);

			std::cout << "Tree: ";
			PrintTree(std::cout, tree);
		}
		else if (command == EXIT_COMMAND)
		{
			break;
		}
		else
		{
			std::cerr << "Unknown command\n";
		}
	}

	return EXIT_SUCCESS;
}
