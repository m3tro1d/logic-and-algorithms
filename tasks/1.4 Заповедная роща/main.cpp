#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <vector>

using namespace std;
using ll = long long;
using ld = long double;

using Column = vector<char>;
using Field = vector<Column>;

constexpr char EMPTY = '0';
constexpr char TREE = '1';

void solve()
{
	int N, K;
	cin >> N >> K;

	Field field(N + 2, Column(K + 2, EMPTY));
	for (int i = 1; i <= N; ++i)
	{
		for (int j = 1; j <= K; ++j)
		{
			cin >> field[i][j];
		}
	}

	// TODO
}

int main()
{
	freopen("input.txt", "r", stdin);
	freopen("output.txt", "w", stdout);
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	solve();
}
