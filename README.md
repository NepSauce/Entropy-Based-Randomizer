# Entropy-Based-Randomizer

A minimal **C++17 random number generator** that pulls directly from **system entropy sources**.  
On Linux/macOS it reads from `/dev/urandom`, while on Windows it uses `BCryptGenRandom`.  
The library is header-only, lightweight, and requires no external dependencies.

---

## Features
-  High-quality randomness from system entropy.
-  Cross-platform support (Linux, macOS, Windows).
-  Header-only, just include `EntropyRandom.hpp`.
-  Simple API:
  - `rand32()` → random 32-bit unsigned integer
  - `randint(lo, hi)` → integer in a given range
  - `randdouble()` → floating-point in [0, 1)

---

## Example

```cpp
#include <iostream>
#include "EntropyRandom.hpp"

int main() {
    EntropyRandom rng;

    std::cout << "Random uint32: " << rng.rand32() << "\n";
    std::cout << "Random int [1,10]: " << rng.randint(1, 10) << "\n";
    std::cout << "Random double [0,1): " << rng.randdouble() << "\n";
}
