# URLParser
Very easy and simple URL parser for C++.

## Feature
* Very simple
* Header only
* Parse any type of url

## Usage
Just include header file.

```C++
#include "../src/url_parser.h"

URLParser::HTTP_URL http_url = URLParser::Parse(input_url);

std::cout << "scheme:[" << http_url.scheme << "]" << std::endl;
std::cout << "host:[" << http_url.host << "]" << std::endl;
std::cout << "port:[" << http_url.port << "]" << std::endl;
```

## Return
```C++
class URLParser
{
public:
	struct HTTP_URL
	{
		std::string scheme; // Defined porotocol on URL. (http, ssh, ftp... etc.)
		std::string host; // Host name or ip address.
		std::string port; // Port
		std::vector<std::string> path; // It contains path information that partitioned. (path_1, path_2...)
		std::string query_string; // Full of query string.
		std::unordered_map<std::string, std::string> query; // It conatains query information. That made up of key, value pair.
	};
}
```
* URLParser is return HTTP_URL structure under URLParser class.
* You can access and use member variable in this structure.

## You can also
You can also parse another variated URL or URI.
```C++
std::string input_url = "http://127.0.0.1:40000/path_1/path_2/path_3/foo.git?test=1&test2=3";
std::string input_url = "http://127.0.0.1/path_1/path_2/path_3/foo.git?test=1&test2=3";
std::string input_url = "http://127.0.0.1/path_1/path_2/path_3";
std::string input_url = "/path_1/path_2/path_3/?test=1&test2=3";
```

Refer to example for detail information.
