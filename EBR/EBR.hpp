#pramga once
#include <cstdint>
#include <vector>
#include <fstream>
#include <stdexcept>

#if defined(_WIN32) || defined(_WIN64)
#include <windows.h>
#include <bcrypt.h>
#pragma comment(lib, "bcrypt.lib")
#endif

class EntropyRandom {
public:
    uint32_t rand32() {
        uint32_t val;
        fill_bytes(&val, sizeof(val));
        return val;
    }

    int randint(int lo, int hi) {
        uint32_t r = rand32();
        return lo + (r % (hi - lo + 1));
    }

    double randdouble() {
        return (double)rand32() / (double)UINT32_MAX;
    }

private:
    void fill_bytes(void* out, size_t n) {
        #if defined(_WIN32) || defined(_WIN64) 
        if (BCryptGenRandom(nullptr, static_cast<PUCHAR>(out), (ULONG)n,
                            BCRYPT_USE_SYSTEM_PREFERRED_RNG) != 0) {
            throw std::runtime_error("Windows RNG failed");
        }
        #else
        std::ifstream urandom("/dev/urandom", std::ios::in | std::ios::binary);
        if (!urandom) throw std::runtime_error("Cannot open /dev/urandom");
        urandom.read(static_cast<char*>(out), n);
        if (!urandom) throw std::runtime_error("Failed to read /dev/urandom");
        #endif
    }
};
