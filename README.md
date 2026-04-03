# URLParser
[![License: MIT](https://img.shields.io/badge/License-MIT-yellow.svg)](https://github.com/dongbum/URLParser/blob/master/LICENSE)
[![Build status](https://ci.appveyor.com/api/projects/status/6lpcxnsf7uor15sw?svg=true)](https://ci.appveyor.com/project/dongbum/urlparser)

A small header-only URL parser for C++.

## Features
* Header-only: just include and use
* No external dependencies beyond the C++11 standard library
* Parses scheme, userinfo, host, port, path, query string, query map, and fragment
* Supports IPv6 bracketed hosts such as `[2001:db8::1]:8080`
* Supports scheme-relative URLs such as `//example.com/path`
* Supports relative and absolute paths such as `path/to/file` and `/path/to/file`
* Validates port strings as numeric values in the range `0-65535`

## Usage

Include the header and call `URLParser::Parse()`.

```cpp
#include "url_parser.h"

std::string input_url = "http://user:pass@example.com:8080/a/b?key=val#section";

URLParser::HTTP_URL http_url = URLParser::Parse(input_url);

std::cout << "scheme:" << http_url.scheme << std::endl;             // http
std::cout << "userinfo:" << http_url.userinfo << std::endl;         // user:pass
std::cout << "host:" << http_url.host << std::endl;                 // example.com
std::cout << "port:" << http_url.port << std::endl;                 // 8080
std::cout << "query_string:" << http_url.query_string << std::endl; // key=val
std::cout << "fragment:" << http_url.fragment << std::endl;         // section

for (const auto& seg : http_url.path)
    std::cout << "path:" << seg << std::endl;                       // a, b

for (const auto& pair : http_url.query)
    std::cout << "query " << pair.first << "=" << pair.second << std::endl;
```

## Return Value

`URLParser::Parse()` returns an `HTTP_URL` struct:

```cpp
struct HTTP_URL
{
    std::string scheme;       // Protocol such as "http", "https", or "ftp".
                              // Empty for scheme-relative or path-only input.

    std::string userinfo;     // Credentials before "@" such as "user:pass".
                              // Empty if not present.

    std::string host;         // Hostname or IP address such as "example.com",
                              // "127.0.0.1", or "2001:db8::1".
                              // IPv6 brackets are stripped automatically.
                              // Empty for path-only input.

    std::string port;         // Port number as a string such as "8080".
                              // Empty if not present or invalid.

    std::vector<std::string> path;
                              // Path segments split by "/".
                              // Leading, trailing, and empty segments are omitted.

    std::string query_string; // Raw query string without the leading "?".
                              // Empty if not present.

    std::unordered_map<std::string, std::string> query;
                              // Parsed query key/value pairs.
                              // Keys without "=" are stored with an empty value.

    std::string fragment;     // Fragment without the leading "#".
                              // Empty if not present.
};
```

`query` is an `unordered_map`, so iteration order is not guaranteed. Duplicate query keys follow `unordered_map::insert` behavior, which keeps the first inserted value for the same key.

## Supported Input Forms

| Form | Example |
|------|---------|
| Absolute URL | `http://example.com/path?key=val#frag` |
| URL with port | `http://example.com:8080/path` |
| URL with userinfo | `http://user:pass@example.com/path` |
| IPv6 host | `http://[2001:db8::1]:8080/path` |
| Scheme-relative URL | `//example.com/path?key=val` |
| Absolute path | `/path/to/resource?key=val` |
| Relative path | `path/to/resource?key=val` |

## Parsing Rules

* Authority (`userinfo`, `host`, `port`) is parsed only when the input contains `://` or starts with `//`.
* Path-only input such as `/docs/page` or `docs/page` leaves `scheme`, `userinfo`, `host`, and `port` empty.
* Port values must contain only digits and must be in the range `0-65535`. Invalid ports are cleared.
* The fragment is split before path and query parsing, so `#...` does not leak into path segments or query tokens.
* Query tokens without `=` such as `?flag` are stored with an empty string value.

## Example Program

See [`example/example.cpp`](example/example.cpp) for a runnable example that covers:

* basic host, port, path, and query parsing
* fragment parsing
* userinfo parsing
* IPv6 hosts
* scheme-relative URLs
* path-only inputs

## Tests

A small regression test executable is included at [`tests/url_parser_test.cpp`](tests/url_parser_test.cpp).

With CMake, you can build and run it with:

```bash
cmake -S . -B build
cmake --build build
ctest --test-dir build --output-on-failure
```
