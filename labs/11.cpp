#include <bits/stdc++.h>

using namespace std;
using ll = long long;
using ld = long double;

string FindLongestUniqueSubstring(string const& initialString)
{
	int i;
	int st = 0;
	int currentLength;
	int maxLength = 0;
	int start;

	unordered_map<char, int> occurred;
	occurred[initialString[0]] = 0;

	for (i = 1; i < initialString.length(); ++i)
	{
		if (occurred.find(initialString[i]) != occurred.end())
		{
			if (occurred[initialString[i]] >= st)
			{
				currentLength = i - st;
				if (maxLength < currentLength)
				{
					maxLength = currentLength;
					start = st;
				}

				st = occurred[initialString[i]] + 1;
			}
		}

		occurred[initialString[i]] = i;
	}

	if (maxLength < i - st)
	{
		maxLength = i - st;
		start = st;
	}

	return initialString.substr(start, maxLength);
}

void Solve()
{
	size_t N;
	cin >> N;

	string initialString;
	cin >> initialString;

	cout << FindLongestUniqueSubstring(initialString) << '\n';
}

int main()
{
	freopen("input.txt", "r", stdin);
	freopen("output.txt", "w", stdout);
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	Solve();
}
