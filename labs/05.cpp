#include <bits/stdc++.h>

using namespace std;
using ll = long long;
using ld = long double;

void Solve()
{
	int N;
	std::cin >> N;

	vector<int> inversion(N);
	copy(istream_iterator<int>(cin), istream_iterator<int>(), inversion.begin());

	vector<int> temp(N);
	for (int i = 1; i <= N; ++i)
	{
		temp[i - 1] = i;
	}

	vector<int> result;
	for (int i = N - 1; i >= 0; --i)
	{
		int index = inversion[i];
		result.push_back(temp[temp.size() - index - 1]);
		temp.erase(temp.end() - index - 1);
	}

	copy(result.rbegin(), result.rend(), ostream_iterator<int>(cout, " "));
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
