#include <bits/stdc++.h>

using ll = unsigned long long;

void Solve()
{
	ll N;
	std::cin >> N;

	if (N % 2 == 0)
	{
		std::cout << "No\n";
		return;
	}
	N >>= 1;

	std::vector<ll> result;
	while (N != 0)
	{
		result.push_back((N & 1) + 1);
		N >>= 1;
	}

	std::cout << result.size() << '\n';
	std::copy(result.rbegin(), result.rend(), std::ostream_iterator<int>(std::cout, " "));
	std::cout << '\n';
}

int main()
{
	freopen("input.txt", "r", stdin);
	freopen("output.txt", "w", stdout);
	std::ios::sync_with_stdio(false);
	std::cin.tie(nullptr);
	Solve();
}
