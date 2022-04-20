#include <bits/stdc++.h>

using namespace std;
using ll = long long;
using ld = long double;

using AdjacencyListItem = vector<int>;
using AdjacencyList = vector<AdjacencyListItem>;

AdjacencyList ReadGraph()
{
	int K;
	cin >> K;

	AdjacencyList result(K, AdjacencyListItem());

	int connectionsAmount;
	int connection;
	for (int i = 0; i < K; ++i)
	{
		cin >> connectionsAmount;
		for (int j = 0; j < connectionsAmount; ++j)
		{
			cin >> connection;
			result[i].push_back(connection - 1);
		}
	}

	return result;
}

void TopologicalSortImpl(int i, const AdjacencyList& graph, vector<bool>& visited, stack<int>& stack)
{
	visited[i] = true;

	for (auto const& connected : graph[i])
	{
		if (!visited[connected])
		{
			TopologicalSortImpl(connected, graph, visited, stack);
		}
	}

	stack.push(i + 1);
}

stack<int> TopologicalSort(const AdjacencyList& graph)
{
	stack<int> stack;
	vector<bool> visited(graph.size(), false);

	for (int i = 0; i < graph.size(); ++i)
	{
		if (!visited[i])
		{
			TopologicalSortImpl(i, graph, visited, stack);
		}
	}

	return stack;
}

bool HasCycle(const AdjacencyList& graph, stack<int> stack, vector<int>& result)
{
	unordered_map<int, int> pos;
	int index = 0;

	while (!stack.empty())
	{
		pos[stack.top() - 1] = index;
		result.push_back(stack.top());
		++index;
		stack.pop();
	}

	for (int i = 0; i < graph.size(); ++i)
	{
		for (auto const& connection : graph[i])
		{
			if (pos[i] > pos[connection])
			{
				return true;
			}
		}
	}

	return false;
}

void Solve()
{
	auto const graph = ReadGraph();
	auto sortStack = TopologicalSort(graph);

	vector<int> result;
	if (HasCycle(graph, sortStack, result))
	{
		cout << "NO\n";
	}
	else
	{
		cout << "YES\n";
		copy(result.rbegin(), result.rend(), ostream_iterator<int>(cout, "\n"));
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
