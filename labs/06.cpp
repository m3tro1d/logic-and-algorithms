#include <bits/stdc++.h>

using namespace std;
using ll = long long;
using ld = long double;

struct Point
{
	int x;
	int y;
};

int CrossProduct(const Point& p1, const Point& p2, const Point& p3)
{
	return (p1.x - p3.x) * (p2.y - p3.y) - (p2.x - p3.x) * (p1.y - p3.y);
}

void Solve()
{
	int N;
	cin >> N;

	std::vector<Point> points(N);
	for (int i = 0; i < N; ++i)
	{
		cin >> points[i].x >> points[i].y;
	}

	int result = 0;
	for (int i = 0; i < N - 2; ++i)
	{
		auto const& p1 = points[i];
		auto const& p2 = points[i + 1];
		auto const& p3 = points[i + 2];
		if (CrossProduct(p1, p2, p3) > 0)
		{
			++result;
		}
	}

	cout << result << '\n';
}

int main()
{
	freopen("input.txt", "r", stdin);
	freopen("output.txt", "w", stdout);
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	Solve();
}
