#include <bits/stdc++.h>

using namespace std;
using ll = long long;
using ld = long double;

int FindWinner(int x, int y)
{
	if (x % 2 && y % 2)
	{
		return 2;
	}

	return 1;
}

void Solve()
{
	int N;
	cin >> N;
	for (int i = 0; i < N; ++i)
	{
		int x;
		int y;
		cin >> x >> y;
		cout << FindWinner(x, y) << '\n';
	}
}

int main()
{
	freopen("input.txt", "r", stdin);
	freopen("output.txt", "w", stdout);
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	Solve();
}
