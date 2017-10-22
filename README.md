# URLParser
Very easy and simple URL parser for C++.

Very simple, header only URL parser for C++.

## Usage
Just include header file.

```C++
#include "../src/url_parser.h"

URLParser::HTTP_URL http_url = URLParser::Parse(input_url);

std::cout << "scheme:[" << http_url.scheme << "]" << std::endl;
std::cout << "host:[" << http_url.host << "]" << std::endl;
std::cout << "port:[" << http_url.port << "]" << std::endl;
```

## You can also
You can also parse another variated URL or URI.
```
std::string input_url = "http://127.0.0.1:40000/path_1/path_2/path_3/foo.git?test=1&test2=3";
std::string input_url = "http://127.0.0.1/path_1/path_2/path_3/foo.git?test=1&test2=3";
std::string input_url = "http://127.0.0.1/path_1/path_2/path_3";
std::string input_url = "/path_1/path_2/path_3/?test=1&test2=3";
```

Refer to example for detail information.
