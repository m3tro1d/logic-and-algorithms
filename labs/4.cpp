#include <bits/stdc++.h>

using namespace std;
using ll = long long;
using ld = long double;

enum class Mark
{
	OPENING = 0,
	CLOSING = 1,
};

struct Part
{
	int coordinate;
	Mark mark;
};

int FindOverlappingParts(int minimalOverlap, vector<Part>& parts)
{
	sort(
		parts.begin(),
		parts.end(),
		[](const Part& part1, const Part& part2) {
			return tie(part1.coordinate, part1.mark) < tie(part2.coordinate, part2.mark);
		});

	int result = 0;
	int count = 0;
	bool needsIncrement;
	const Part* prevPart = nullptr;
	for (auto const& part : parts)
	{
		needsIncrement = count < minimalOverlap;

		if (part.mark == Mark::OPENING)
		{
			++count;
		}
		if (part.mark == Mark::CLOSING)
		{
			--count;
		}

		if (count >= minimalOverlap && needsIncrement)
		{
			++result;
		}

		if (prevPart)
		{
			if (prevPart->coordinate == part.coordinate)
			{
				if (prevPart->mark == Mark::CLOSING && part.mark == Mark::OPENING)
				{
					if (minimalOverlap > 1)
					{
						--result;
					}
				}
			}
		}

		prevPart = &part;
	}

	return result;
}

void Solve()
{
	int N, M;
	cin >> N >> M;
	vector<Part> parts(N * 2);
	for (int i = 0; i < N * 2; ++i)
	{
		cin >> parts[i].coordinate;
		parts[i].mark = (i % 2) ? Mark::CLOSING : Mark::OPENING;
	}

	cout << FindOverlappingParts(M, parts) << '\n';
}

int main()
{
	freopen("input.txt", "r", stdin);
	freopen("output.txt", "w", stdout);
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	Solve();
}
