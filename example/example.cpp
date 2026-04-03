#include <iostream>

#include "../src/url_parser.h"

void PrintURL(const std::string& label, const std::string& input_url)
{
	std::cout << "=== " << label << " ===" << std::endl;
	std::cout << "input:[" << input_url << "]" << std::endl;

	URLParser::HTTP_URL http_url = URLParser::Parse(input_url);

	std::cout << "scheme:[" << http_url.scheme << "]" << std::endl;
	std::cout << "userinfo:[" << http_url.userinfo << "]" << std::endl;
	std::cout << "host:[" << http_url.host << "]" << std::endl;
	std::cout << "port:[" << http_url.port << "]" << std::endl;

	for (const auto& path : http_url.path)
		std::cout << "path:[" << path << "]" << std::endl;

	std::cout << "query_string:[" << http_url.query_string << "]" << std::endl;

	for (const auto& pair : http_url.query)
		std::cout << "Query:[" << pair.first << "]:[" << pair.second << "]" << std::endl;

	std::cout << "fragment:[" << http_url.fragment << "]" << std::endl;
	std::cout << std::endl;
}

int main(void)
{
	// Basic: host + port + path + query
	PrintURL("Basic", "http://127.0.0.1:40000/path_1/path_2/path_3/foo.git?test=1&test2=3");

	// No port
	PrintURL("No port", "http://127.0.0.1/path_1/path_2/path_3/foo.git?test=1&test2=3");

	// Path only, no query
	PrintURL("Path only", "http://127.0.0.1/path_1/path_2/path_3");

	// No scheme, with query
	PrintURL("No scheme", "/path_1/path_2/path_3/?test=1&test2=3");

	// Empty value in query
	PrintURL("Empty query value", "https://127.0.0.1:40000/path_1/path_2/path_3/foo.git?test=&test2=3");

	// Fragment
	PrintURL("Fragment", "http://example.com/docs/page?key=val#section-2");

	// Fragment only (no query)
	PrintURL("Fragment only", "http://example.com/a#top");

	// Userinfo
	PrintURL("Userinfo", "http://user:pass@example.com:8080/resource?id=1");

	// IPv6
	PrintURL("IPv6", "http://[2001:db8::1]:8080/v1/api?debug=true");

	// Host only (no path, no query, no fragment)
	PrintURL("Host only", "https://example.com");

	// Scheme-relative URL
	PrintURL("Scheme-relative", "//example.com/path_1/path_2?key=val#frag");

	// Scheme-relative with port
	PrintURL("Scheme-relative with port", "//example.com:9090/path");

	// Scheme-relative with userinfo
	PrintURL("Scheme-relative with userinfo", "//user:pass@example.com/path");

	return 0;
}