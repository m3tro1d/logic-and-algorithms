/*
 * ����� �������:
 * 13.1. �������� ������ (6)
 * ��������� ����� ��� ��������� ������� � ��������� ����� ������� ������. � ����� ��� �������� ����.
 * ������� ����� �������� ������� � ���������� � ����� ������ ����� �� ������. ����� ������ �����
 * ����� ������������������ ��� ������. ���������� ������ �� ������ �������� �� �������� ����, ��
 * ���� ������ ����� � ������� � ����� ����� ���� ��� ��������, ���  � ���������.
 *
 * ���� �� ����� INPUT.TXT. ������ ������ ����� �������� �������� � ����� ����� �� 1 �� 255.
 * ������ ������ ������ ��� ���������� �����.
 *
 * ����� � ���� OUTPUT.TXT. ������� � ������ ������ ����� ������ ������������������ �������
 * ����� � ������� � ������, ������� � ������� ������� ������ � �����. ��������� ����� �
 * ������� � ������ ���������� � 1. ���� ��������� ���, ������� No.
 *
 * ������
 *
 * ����
 * ���� ���� ����
 * Bukvar.txt
 *
 * �����
 * 1 1
 * 1 23
 *
 * ���������. ���� Bukvar.txt ������� �� ��������� ���� �����:
 * ���� ���� ���� �����, ����
 * ���� ���� �������.
 *
 *
 * ��������:
 * ������� �����, ��-21
 *
 * ����� ����������:
 * Visual Studio 2022
 */

#define _CRT_SECURE_NO_WARNINGS
#include <fstream>
#include <iostream>
#include <string>

using Hash = int;

void ReplaceAll(std::string& str, const std::string& from, const std::string& to)
{
	if (from.empty())
		return;
	size_t start_pos = 0;
	while ((start_pos = str.find(from, start_pos)) != std::string::npos)
	{
		str.replace(start_pos, from.length(), to);
		start_pos += to.length();
	}
}

Hash InitializeHash(std::size_t length)
{
	int const d = 52;
	int const p = 65713;

	Hash result = 1;
	for (std::size_t i = 0; i < length; ++i)
	{
		result = (result * d) % p;
	}

	return result;
}

Hash CalculateHash(std::string const& str, std::size_t length, Hash prevHash, Hash& hash)
{
	int d = 52;
	int p = 65713;

	if (hash == 0)
	{
		hash = InitializeHash(length);
	}

	if (prevHash == 0)
	{
		for (std::size_t i = 0; i < length; ++i)
		{
			prevHash += (d * prevHash + static_cast<Hash>(str[i])) % p;
		}

		if (prevHash < 0)
		{
			prevHash += p;
		}

		return prevHash;
	}
	else
	{
		Hash result = (d * (prevHash - static_cast<Hash>(str[0]) * hash) + static_cast<Hash>(str[length - 1])) % p;
		if (result < 0)
		{
			result += p;
		}

		return result;
	}
}

void Search(std::istream& haystack, std::string const& needle)
{
	std::string window;
	char* buffer = new char[needle.length() + 1];
	haystack.read(buffer, needle.length());
	buffer[needle.length()] = '\0';
	window = buffer;
	ReplaceAll(window, "\n", " ");

	Hash hash = 0;
	auto needleHash = CalculateHash(needle, needle.length(), 0, hash);
	auto windowHash = CalculateHash(window, needle.length(), 0, hash);

	std::size_t k = 0;
	bool found = false;
	while (haystack)
	{
		if (needleHash == windowHash)
		{
			for (std::size_t i = 0; i < needle.length() && needle[i] == window[k + i]; ++i)
			{
				if (i == needle.length() - 1)
				{
					std::cout << k << '\n';
					found = true;
				}
			}
		}

		++k;
		haystack.read(buffer, needle.length());
		buffer[needle.length()] = '\0';
		window = buffer;
		ReplaceAll(window, "\n", " ");
		windowHash = CalculateHash(window, needle.length(), windowHash, hash);
	}

	if (!found)
	{
		std::cout << "No\n";
	}
}

void Solve(std::istream& input, std::ostream& output)
{
	std::string needle;
	std::string haystackFilename;

	std::getline(input, needle);
	std::getline(input, haystackFilename);

	std::ifstream haystackFile(haystackFilename);

	Search(haystackFile, needle);
}

int main()
{
	std::ifstream input("input.txt");
	std::ofstream output("output.txt");

	input.tie(nullptr);
	std::cin.tie(nullptr);
	std::ios::sync_with_stdio(false);

	Solve(input, output);
}
