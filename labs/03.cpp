#include <bits/stdc++.h>

using namespace std;
using ll = long long;
using ld = long double;

int F(std::vector<int>& cache, std::vector<int>& last, int N)
{
	if (N == 0)
	{
		return 0;
	}

	if (N == 1)
	{
		return 1;
	}

	if (cache[N] != 0)
	{
		return cache[N];
	}

	int min = INT_MAX;
	for (int i = static_cast<int>(sqrt(N)); i > 0; --i)
	{
		int iSquared = i * i;
		int value = F(cache, last, N - iSquared) + 1;
		if (value < min)
		{
			min = value;
			last[N] = iSquared;
		}
	}

	cache[N] = min;
	return min;
}

void Solve()
{
	int N;
	cin >> N;

	std::vector<int> cache(N + 1, 0);
	std::vector<int> last(N + 1, 0);
	last[1] = 1;
	cout << F(cache, last, N) << '\n';

	while (N > 0)
	{
		cout << last[N] << ' ';
		N -= last[N];
	}
	cout << '\n';
}

int main()
{
	freopen("input.txt", "r", stdin);
	freopen("output.txt", "w", stdout);
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	Solve();
}
