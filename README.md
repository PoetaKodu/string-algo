# String algorithms

A C++ string algorithm library.

## 🔽 Installation

Use [**PACC**](https://github.com/PoetaKodu/pacc) package manager.

### Add to dependencies

Add `string-algo@0.1.0` to `dependencies` field of your `cpackage.json`:
```json
"dependencies": [
	"string-algo@0.1.0"
]
```

### Install packages

Run the following shell command:
```
pacc install
```

## 🎯 Usage

### 1. Initial configuration

Include the header file:

```cpp
#include <StringAlgo/Everything.hpp>
```

You may want to create a namespace alias, for example:

```cpp
namespace sa = string_algo;
```

### 2. Iterating over tokens in a string

```cpp
constexpr std::string_view toAnalyze = "The quick brown fox jumps over the lazy dog";

for(std::string_view v : sa::StringTokenIterator(toAnalyze, " "))
{
	std::cout << v << "\n";
}
```

Output:
```
The
quick
brown
fox
jumps
over
the
lazy
dog
```

### 3. Converting strings to numbers

```cpp
constexpr std::string_view str = "-41423";

std::optional<int> i = sa::to<int>(str);

if (i.has_value())
	std::cout << "i: " << *i << std::endl;

// Without optional
int j;
if (sa::to<int>(j, str))
{
	std::cout << "j: " << j << std::endl;
}
```


## 👱‍♂️ Author

Paweł Syska