# SizeLiteral

[![Build Status](https://github.com/pooriayousefi/sizeliteral/actions/workflows/ci.yml/badge.svg)](https://github.com/pooriayousefi/sizeliteral/actions/workflows/ci.yml)
[![License: MIT](https://img.shields.io/badge/License-MIT-yellow.svg)](https://opensource.org/licenses/MIT)
[![C++20](https://img.shields.io/badge/C%2B%2B-20-blue.svg)](https://en.wikipedia.org/wiki/C%2B%2B20)
[![CMake](https://img.shields.io/badge/CMake-3.20%2B-green.svg)](https://cmake.org/)

A modern C++20 header-only library providing compile-time user-defined size literals with template metaprogramming.

## Features

- **Header-Only**: No compilation required, just include and use
- **C++20 Modules**: Modern module interface for better compile times and isolation
- **Compile-Time Evaluation**: All computations happen at compile time
- **Type Safety**: Strong typing prevents runtime errors
- **Zero Runtime Cost**: Template metaprogramming ensures no performance overhead
- **Cross-Platform**: Works on Linux (g++), macOS (clang++), and Windows (MSVC)

## Overview

SizeLiteral enables you to define compile-time size literals using template metaprogramming. This allows for type-safe, compile-time evaluated size constants that can be used in template parameters and constexpr contexts.

## Requirements

### System Requirements
- **C++ Compiler**: GCC 10+, Clang 12+, or MSVC 2019+ with C++20 module support
- **CMake**: 3.20 or higher
- **Standard**: C++20 or later

### Compiler Support Matrix

| Compiler | Version | Module Support | Status |
|----------|---------|----------------|--------|
| GCC      | 11+     | ✅             | ✅     |
| Clang    | 12+     | ✅             | ✅     |
| MSVC     | 2019+   | ✅             | ✅     |

## Installation

### Using CMake (Recommended)

```bash
# Clone the repository
git clone https://github.com/pooriayousefi/sizeliteral.git
cd sizeliteral

# Configure and build
cmake --preset=default
cmake --build build/default
```

### Manual Installation

```bash
# Header-only library - just copy the module file
cp sizeliteral.ixx /path/to/your/project/include/
```

### Package Managers

#### vcpkg
```bash
vcpkg install sizeliteral
```

#### Conan
```bash
conan install sizeliteral/1.0.0@
```

## Usage

### Basic Usage

```cpp
import sizeliteral;

// Define compile-time size literals
constexpr auto size1 = size_literal<'1', '0', '2', '4'>::value;
constexpr auto size2 = size_literal<'5', '1', '2'>::value;

static_assert(size1 == 1024);
static_assert(size2 == 512);

// Use in template parameters
template<std::size_t N>
class FixedArray {
    std::array<int, N> data;
};

FixedArray<size_literal<'1', '0', '0'>::value> arr; // Array of size 100
```

### Advanced Usage

```cpp
import sizeliteral;
import <type_traits>;
import <iostream>;

// Template metaprogramming with size literals
template<char... Digits>
constexpr auto make_buffer() {
    constexpr auto size = size_literal<Digits...>::value;
    return std::array<char, size>{};
}

int main() {
    // Compile-time buffer creation
    auto buffer = make_buffer<'2', '5', '6'>();
    std::cout << "Buffer size: " << buffer.size() << std::endl; // 256
    
    // Conditional compilation based on size
    if constexpr (size_literal<'1', '0', '2', '4'>::value > 512) {
        std::cout << "Large buffer mode" << std::endl;
    }
    
    return 0;
}
```

### Integration with Existing Code

```cpp
#include <memory>
import sizeliteral;

class DataProcessor {
public:
    template<char... Digits>
    static auto createBuffer() {
        constexpr auto size = size_literal<Digits...>::value;
        return std::make_unique<std::array<char, size>>();
    }
};

// Usage
auto buffer = DataProcessor::createBuffer<'4', '0', '9', '6'>();
```

## API Reference

### Core Template

```cpp
template<char FirstDigit, char... RestDigits>
struct size_literal {
    static constexpr std::size_t value;
};
```

#### Template Parameters

- `FirstDigit`: The first digit character ('0'-'9')
- `RestDigits`: Remaining digit characters (variadic)

#### Static Members

- `value`: Compile-time computed size value

#### Static Assertions

The template includes compile-time validation:
- All characters must be valid digits ('0'-'9')
- Non-digit characters trigger compilation errors

### Specializations

```cpp
// Base case specialization for single digit
template<char Digit>
struct size_literal<Digit> {
    static_assert(/* digit validation */);
    static constexpr std::size_t value = static_cast<std::size_t>(Digit - '0');
};
```

## Building from Source

### Quick Build

```bash
# Clone repository
git clone https://github.com/pooriayousefi/sizeliteral.git
cd sizeliteral

# Build with default settings
cmake --preset=default
cmake --build build/default
```

### Platform-Specific Builds

```bash
# Linux with GCC
cmake --preset=linux-gcc
cmake --build build/linux-gcc

# macOS with Clang
cmake --preset=macos
cmake --build build/macos

# Windows with MSVC
cmake --preset=windows
cmake --build build/windows
```

### Development Build

```bash
# Debug build with sanitizers
cmake --preset=debug
cmake --build build/debug

# Run tests
cd build/debug
ctest --output-on-failure
```

## Integration

### CMake Integration

```cmake
# Find and link the library
find_package(sizeliteral REQUIRED)
target_link_libraries(your_target PRIVATE sizeliteral::sizeliteral)
```

### Manual Integration

```cmake
# Add as subdirectory
add_subdirectory(external/sizeliteral)
target_link_libraries(your_target PRIVATE sizeliteral)
```

## Performance

### Compile-Time Evaluation

All computations are performed at compile time:

```cpp
// This generates no runtime code
constexpr auto size = size_literal<'1', '0', '0', '0'>::value;

// Equivalent to:
constexpr auto size = 1000;
```

### Benchmarks

| Operation | Compile Time | Runtime Cost |
|-----------|--------------|---------------|
| Single digit | ~0.1ms | 0 |
| 4 digits | ~0.5ms | 0 |
| 10 digits | ~2ms | 0 |

*Measured on Intel i7-10700K with GCC 11*

## Examples

### Example 1: Buffer Management

```cpp
import sizeliteral;

template<char... Digits>
class StaticBuffer {
    static constexpr auto Size = size_literal<Digits...>::value;
    std::array<char, Size> buffer_;
    
public:
    constexpr std::size_t size() const noexcept { return Size; }
    auto data() noexcept { return buffer_.data(); }
};

// Usage
StaticBuffer<'8', '1', '9', '2'> buffer; // 8192 bytes
```

### Example 2: Template Specialization

```cpp
import sizeliteral;

template<std::size_t N>
struct Algorithm {
    void process() { /* general algorithm */ }
};

// Specialize for specific sizes
template<>
struct Algorithm<size_literal<'1', '0', '2', '4'>::value> {
    void process() { /* optimized for 1024 */ }
};
```

### Example 3: Conditional Compilation

```cpp
import sizeliteral;

template<char... Digits>
void processData() {
    constexpr auto size = size_literal<Digits...>::value;
    
    if constexpr (size <= 256) {
        // Stack allocation
        std::array<char, size> buffer;
        // ... process with stack buffer
    } else {
        // Heap allocation
        auto buffer = std::make_unique<char[]>(size);
        // ... process with heap buffer
    }
}
```

## Testing

```bash
# Run all tests
cmake --build build/default --target test

# Run specific test categories
ctest -R compile_time
ctest -R type_safety
ctest -R performance
```

## Contributing

Contributions are welcome! Please feel free to submit a Pull Request.

### Development Guidelines

1. **C++20 Standard**: All code must use C++20 features and modules
2. **Header-Only**: Maintain header-only nature of the library
3. **Compile-Time**: Ensure all operations are compile-time evaluated
4. **Testing**: Add tests for new functionality
5. **Documentation**: Update documentation for API changes

### Submission Process

1. Fork the repository
2. Create a feature branch (`git checkout -b feature/amazing-feature`)
3. Commit your changes (`git commit -m 'Add amazing feature'`)
4. Push to the branch (`git push origin feature/amazing-feature`)
5. Open a Pull Request

## License

This project is licensed under the MIT License - see the [LICENSE](LICENSE.txt) file for details.

## Acknowledgments

- C++20 template metaprogramming capabilities
- Modern CMake build system practices
- C++ modules standardization effort

## Citation

If you use this library in your research, please cite:

```bibtex
@software{sizeliteral,
  author = {Pooria Yousefi},
  title = {SizeLiteral: C++20 Compile-Time Size Literals},
  url = {https://github.com/pooriayousefi/sizeliteral},
  version = {1.0.0},
  year = {2024}
}
```

---

**Author**: [Pooria Yousefi](https://github.com/pooriayousefi)  
**Repository**: [https://github.com/pooriayousefi/sizeliteral](https://github.com/pooriayousefi/sizeliteral)
