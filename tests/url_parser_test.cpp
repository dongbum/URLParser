#include <cstdlib>
#include <iostream>
#include <string>
#include <unordered_map>
#include <vector>

#include "../src/url_parser.h"

namespace
{
	struct ExpectedURL
	{
		std::string scheme;
		std::string userinfo;
		std::string host;
		std::string port;
		std::vector<std::string> path;
		std::string query_string;
		std::unordered_map<std::string, std::string> query;
		std::string fragment;
	};

	bool CheckEqual(const std::string& label, const std::string& actual, const std::string& expected)
	{
		if (actual == expected)
			return true;

		std::cerr << label << " mismatch. expected:[" << expected << "] actual:[" << actual << "]" << std::endl;
		return false;
	}

	bool CheckPath(const std::vector<std::string>& actual, const std::vector<std::string>& expected)
	{
		if (actual == expected)
			return true;

		std::cerr << "path mismatch. expected size:[" << expected.size() << "] actual size:[" << actual.size() << "]" << std::endl;
		return false;
	}

	bool CheckQuery(const std::unordered_map<std::string, std::string>& actual, const std::unordered_map<std::string, std::string>& expected)
	{
		if (actual.size() != expected.size())
		{
			std::cerr << "query size mismatch. expected:[" << expected.size() << "] actual:[" << actual.size() << "]" << std::endl;
			return false;
		}

		for (const auto& pair : expected)
		{
			const auto it = actual.find(pair.first);
			if (it == actual.end())
			{
				std::cerr << "query key missing:[" << pair.first << "]" << std::endl;
				return false;
			}

			if (it->second != pair.second)
			{
				std::cerr << "query value mismatch for key:[" << pair.first << "] expected:[" << pair.second << "] actual:[" << it->second << "]" << std::endl;
				return false;
			}
		}

		return true;
	}

	bool RunCase(const std::string& label, const std::string& input, const ExpectedURL& expected)
	{
		const URLParser::HTTP_URL actual = URLParser::Parse(input);

		bool ok = true;
		ok = CheckEqual(label + " scheme", actual.scheme, expected.scheme) && ok;
		ok = CheckEqual(label + " userinfo", actual.userinfo, expected.userinfo) && ok;
		ok = CheckEqual(label + " host", actual.host, expected.host) && ok;
		ok = CheckEqual(label + " port", actual.port, expected.port) && ok;
		ok = CheckPath(actual.path, expected.path) && ok;
		ok = CheckEqual(label + " query_string", actual.query_string, expected.query_string) && ok;
		ok = CheckQuery(actual.query, expected.query) && ok;
		ok = CheckEqual(label + " fragment", actual.fragment, expected.fragment) && ok;
		return ok;
	}
}

int main()
{
	bool ok = true;

	ok = RunCase(
		"absolute",
		"http://user:pass@example.com:8080/a/b?key=val#section",
		ExpectedURL{
			"http",
			"user:pass",
			"example.com",
			"8080",
			{ "a", "b" },
			"key=val",
			{ { "key", "val" } },
			"section"
		}) && ok;

	ok = RunCase(
		"ipv6",
		"http://[2001:db8::1]:8080/v1/api?debug=true",
		ExpectedURL{
			"http",
			"",
			"2001:db8::1",
			"8080",
			{ "v1", "api" },
			"debug=true",
			{ { "debug", "true" } },
			""
		}) && ok;

	ok = RunCase(
		"scheme-relative",
		"//example.com/path_1/path_2?key=val#frag",
		ExpectedURL{
			"",
			"",
			"example.com",
			"",
			{ "path_1", "path_2" },
			"key=val",
			{ { "key", "val" } },
			"frag"
		}) && ok;

	ok = RunCase(
		"path-only",
		"/path/to/resource?flag&key=value",
		ExpectedURL{
			"",
			"",
			"",
			"",
			{ "path", "to", "resource" },
			"flag&key=value",
			{ { "flag", "" }, { "key", "value" } },
			""
		}) && ok;

	ok = RunCase(
		"invalid-port",
		"http://example.com:99999/path",
		ExpectedURL{
			"http",
			"",
			"example.com",
			"",
			{ "path" },
			"",
			{},
			""
		}) && ok;

	ok = RunCase(
		"relative-path",
		"docs/page.html#top",
		ExpectedURL{
			"",
			"",
			"",
			"",
			{ "docs", "page.html" },
			"",
			{},
			"top"
		}) && ok;

	if (!ok)
		return EXIT_FAILURE;

	std::cout << "All URLParser tests passed." << std::endl;
	return EXIT_SUCCESS;
}
