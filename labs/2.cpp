#include <bits/stdc++.h>

using namespace std;
using ll = long long;
using ld = long double;

using Field = vector<vector<char>>;

constexpr char FILLED = '#';
constexpr char EMPTY = '.';

void mark(Field& field, ll row, ll column)
{
	if (field[row][column] == FILLED)
	{
		field[row][column] = EMPTY;
		mark(field, row + 1, column);
		mark(field, row - 1, column);
		mark(field, row, column + 1);
		mark(field, row, column - 1);
	}
}

void solve()
{
	ll N, M;
	cin >> N >> M;

	Field field(N + 2, vector<char>(M + 2, EMPTY));
	for (ll i = 1; i <= N; ++i)
	{
		for (ll j = 1; j <= M; ++j)
		{
			cin >> field[i][j];
		}
	};

	ll result = 0;
	for (ll i = 1; i <= N; ++i)
	{
		for (ll j = 1; j <= M; ++j)
		{
			if (field[i][j] == FILLED)
			{
				++result;
				mark(field, i, j);
			}
		}
	};

	cout << result << '\n';
}

int main()
{
	freopen("input.txt", "r", stdin);
	freopen("output.txt", "w", stdout);
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	solve();
}
