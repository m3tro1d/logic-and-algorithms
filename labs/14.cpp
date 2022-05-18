#include <bits/stdc++.h>

std::vector<int> ReadNumbers(std::istream& input)
{
	size_t N;
	input >> N;

	std::vector<int> result(N);
	for (size_t j = 0; j < N; ++j)
	{
		input >> result[j];
	}

	return result;
}

bool isArithmeticProgression(std::vector<int>& numbers)
{
	std::sort(numbers.begin(), numbers.end());

	int diff = numbers[1] - numbers[0];
	for (size_t i = 1; i < numbers.size() - 1; ++i)
	{
		if (numbers[i + 1] - numbers[i] != diff)
		{
			return false;
		}
	}

	return true;
}

void Solve()
{
	size_t casesAmount;
	std::cin >> casesAmount;

	for (size_t i = 0; i < casesAmount; ++i)
	{
		auto numbers = ReadNumbers(std::cin);

		if (isArithmeticProgression(numbers))
		{
			std::cout << "Yes\n";
		}
		else
		{
			std::cout << "No\n";
		}
	}
}

int main()
{
	freopen("input.txt", "r", stdin);
	freopen("output.txt", "w", stdout);
	std::ios::sync_with_stdio(false);
	std::cin.tie(nullptr);
	Solve();
}
