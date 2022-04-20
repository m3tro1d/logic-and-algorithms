#include <bits/stdc++.h>

using namespace std;
using ll = long long;
using ld = long double;

vector<string> ReadWords()
{
	vector<string> result;
	string word;
	while (cin >> word)
	{
		result.push_back(move(word));
	}

	return result;
}

unordered_map<char, int> BuildCharactersMap(string const& word)
{
	unordered_map<char, int> result;
	for (auto const& ch : word)
	{
		++result[ch];
	}

	return result;
}

bool IsCompatibleWord(unordered_map<char, int> sourceCharacters, string const& word)
{
	for (auto const& ch : word)
	{
		if (sourceCharacters[ch])
		{
			--sourceCharacters[ch];
		}
		else
		{
			return false;
		}
	}

	return true;
}

void SortWords(vector<string>& words)
{
	sort(words.begin(), words.end(), [](string const& s1, string const& s2) {
		if (s1.length() != s2.length())
		{
			return s1.length() > s2.length();
		}

		return s1 < s2;
	});
}

void PrintResult(int points, vector<string> const& result)
{
	cout << points << '\n';
	for (auto const& word : result)
	{
		cout << word << '\n';
	}
}

void Solve()
{
	string sourceWord;
	cin >> sourceWord;
	auto words = ReadWords();

	auto const sourceCharacters = BuildCharactersMap(sourceWord);

	vector<string> result;
	int points = 0;
	for (auto& word : words)
	{
		if (IsCompatibleWord(sourceCharacters, word))
		{
			points += static_cast<int>(word.length());
			result.push_back(move(word));
		}
	}

	SortWords(result);
	PrintResult(points, result);
}

int main()
{
	freopen("input.txt", "r", stdin);
	freopen("output.txt", "w", stdout);
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	Solve();
}
