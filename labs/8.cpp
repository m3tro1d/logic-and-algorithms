#include <bits/stdc++.h>

using namespace std;
using ll = long long;
using ld = long double;

using CellRow = vector<int>;
using CellField = vector<CellRow>;

int FindStepsCount(CellField& field, int infectedCellsCount)
{
	int stepsCount = 0;

	while (infectedCellsCount < field.size() * field.size())
	{
		++stepsCount;
		for (int x = 0; x < field.size(); ++x)
		{
			for (int y = 0; y < field.size(); ++y)
			{
				if (field[x][y] == stepsCount)
				{
					if (x > 0 && field[x - 1][y] == 0)
					{
						field[x - 1][y] = stepsCount + 1;
						++infectedCellsCount;
					}

					if (x < field.size() - 1 && field[x + 1][y] == 0)
					{
						field[x + 1][y] = stepsCount + 1;
						++infectedCellsCount;
					}

					if (y > 0 && field[x][y - 1] == 0)
					{
						field[x][y - 1] = stepsCount + 1;
						++infectedCellsCount;
					}

					if (y < field.size() - 1 && field[x][y + 1] == 0)
					{
						field[x][y + 1] = stepsCount + 1;
						++infectedCellsCount;
					}
				}
			}
		}
	}

	return stepsCount;
}

void Solve()
{
	int N;
	int M;
	cin >> N >> M;

	CellField field(N, CellRow(N, 0));
	for (int i = 0; i < M; ++i)
	{
		int x;
		int y;

		cin >> x >> y;
		field[x - 1][y - 1] = 1;
	}

	cout << FindStepsCount(field, M) << '\n';
}

int main()
{
	freopen("input.txt", "r", stdin);
	freopen("output.txt", "w", stdout);
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	Solve();
}
