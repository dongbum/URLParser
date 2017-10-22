#include <iostream>

#include "../src/url_parser.h"

int main(void)
{
	std::string input_url = "http://127.0.0.1:40000/path_1/path_2/path_3/foo.git?test=1&test2=3";
	//std::string input_url = "http://127.0.0.1/path_1/path_2/path_3/foo.git?test=1&test2=3";
	//std::string input_url = "http://127.0.0.1/path_1/path_2/path_3";
	//std::string input_url = "/path_1/path_2/path_3/?test=1&test2=3";
	//std::string input_url = "https://127.0.0.1:40000/path_1/path_2/path_3/foo.git?test=&test2=3";

	URLParser::HTTP_URL http_url = URLParser::Parse(input_url);

	std::cout << "scheme:[" << http_url.scheme << "]" << std::endl;
	std::cout << "host:[" << http_url.host << "]" << std::endl;
	std::cout << "port:[" << http_url.port << "]" << std::endl;
	
	for (auto path : http_url.path)
		std::cout << "path:[" << path << "]" << std::endl;

	std::cout << "query_string:[" << http_url.query_string << "]" << std::endl;

	for (std::pair<std::string, std::string> pair : http_url.query)
		std::cout << "Query:[" << pair.first << "]:[" << pair.second << "]" << std::endl;

	return 0;
}