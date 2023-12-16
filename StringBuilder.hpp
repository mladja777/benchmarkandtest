#include <algorithm>
#include <benchmark/benchmark.h>
#include <iostream>
#include <memory>
#include <stdexcept>
#include <string_view>

class StringBuilder {
public:
    StringBuilder() = default;
    ~StringBuilder() {
        if (mBuffer != nullptr) {
            delete[] mBuffer;
        }
    }

    StringBuilder& Append(std::string_view str) {
        char* tmp = new char[mLength + str.size()]();
        if (mBuffer != nullptr) {
            std::copy(mBuffer, mBuffer + mLength, tmp);
        }
        std::copy(str.begin(), str.end(), tmp + mLength);
        mLength += str.size();
        [](char** first, char** second) {
            char* tmp = *first;
            *first    = *second;
            *second   = tmp;
        }(&mBuffer, &tmp);
        if (tmp != nullptr) {
            delete[] tmp;
        }
        return *this;
    }
    std::string ToString() const { return std::string(mBuffer, mLength); }

private:
    char*       mBuffer = nullptr;
    std::size_t mLength = 0;
};

static void BM_StringBuilder(benchmark::State& state) {
    try {
        for (auto _ : state) {
            StringBuilder sb;
            sb.Append("Moj ").Append("pvi ").Append("string.");
            std::cout << sb.ToString() << std::endl;
            sb.Append(" Hello").Append(" World.");
            std::cout << sb.ToString() << std::endl;
        }
    } catch (const std::exception& e) {
        std::cout << "Exception occured: " << e.what() << std::endl;
    }
}

/// BENCHMARK(BM_StringBuilder);