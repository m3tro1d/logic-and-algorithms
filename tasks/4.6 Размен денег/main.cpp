#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <vector>
#include <limits>

using namespace std;

constexpr int INF = std::numeric_limits<int>::max() - 1;

int findMinChange(int sum, const vector<int>& coins, vector<bool>& ready, vector<int>& value)
{
	if (sum < 0)
	{
		return INF;
	}
	if (sum == 0)
	{
		return 0;
	}

	if (ready[sum])
	{
		return value[sum];
	}

	int best = INF;
	for (auto const& coin : coins)
	{
		best = min(best, findMinChange(sum - coin, coins, ready, value) + 1);
	}

	value[sum] = best;
	ready[sum] = true;

	return best;
}

void solve()
{
	int L, N;
	cin >> L >> N;

	vector<int> coins(N);
	for (int i = 0; i < N; ++i)
	{
		cin >> coins[i];
	}

	vector<bool> ready(L + 1, false);
	vector<int> value(L + 1);

	int min = findMinChange(L, coins, ready, value);
	if (min == INF)
	{
		cout << "No\n";
		return;
	}

	cout << min << '\n';
}

int main()
{
	freopen("input.txt", "r", stdin);
	freopen("output.txt", "w", stdout);
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	solve();
}
