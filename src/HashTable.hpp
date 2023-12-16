#include <algorithm>
#include <benchmark/benchmark.h>
#include <cmath>
#include <iostream>
#include <list>
#include <memory>
#include <stdexcept>
#include <string>
#include <vector>

template<typename ValueType>
class HashMap {
public:
    using KVPair = std::pair<std::string, ValueType>;
    using Bucket = std::list<KVPair>;

    HashMap() { mArray.resize(3); }

    void Insert(const std::string& key, const ValueType& value) {
        if (ShouldResize()) {
            Resize();
        }
        InsertInternal(key, value, mArray);
    }
    void Remove(const std::string& key) {
        auto& bucket = mArray[HashKey(key)];
        bucket.erase(std::find_if(bucket.begin(), bucket.end(), [&](const KVPair& bucket) {
            if (bucket.first == key) {
                return true;
            }
            return false;
        }));
    }
    const ValueType& Lookup(const std::string& key) const {
        const auto& bucket = mArray[HashKey(key)];
        const auto& [_,
                     val]  = *std::find_if(bucket.begin(), bucket.end(), [&](const KVPair& bucket) {
            if (bucket.first == key) {
                return true;
            }
            return false;
        });
        return val;
    }

private:
    void InsertInternal(const std::string&   key,
                        const ValueType&     value,
                        std::vector<Bucket>& map) const {
        map[HashKey(key)].emplace_back(key, value);
    }
    unsigned int HashKey(const std::string& key) const {
        unsigned long long sum = 0;
        for (const auto& ch : key) {
            sum += ch;
        }
        return sum % mArray.size();
    }
    bool IsPrime(unsigned int number) const {
        for (int i = 2; i < std::sqrt(number); ++i) {
            if (number % i == 0) {
                return false;
            }
        }
        return true;
    }
    unsigned int NextPrime(unsigned int number) const {
        if (IsPrime(number)) {
            return number;
        }
        return NextPrime(number + 1);
    }
    void Resize() {
        std::vector<Bucket> temp(NextPrime(mArray.size() * 2));
        for (const auto& bucket : mArray) {
            for (const auto& [key, val] : bucket) {
                InsertInternal(key, val, temp);
            }
        }
        mArray = std::move(temp);
    }
    bool ShouldResize() const {
        if (static_cast<double>(mSize) / mArray.size() > 0.7) {
            return true;
        }
        return false;
    }

    std::vector<Bucket> mArray;
    std::size_t         mSize = 0;
};

static void BM_HashTable(benchmark::State& state) {
    try {
        for (auto _ : state) {
            HashMap<int> map;
            map.Insert("mojprvikljuc", 1);
            map.Insert("mojdrugikljuc", 2);
            map.Insert("mojtrecikljuc", 3);
            map.Insert("mojcetvrtikljuc", 4);
            map.Insert("mojpetikljuc", 5);
            map.Insert("mojsestikljuc", 6);
            map.Insert("mojsedmikljuc", 7);
            map.Insert("mojosmikljuc", 8);
            std::cout << map.Lookup("mojtrecikljuc") << std::endl;
            std::cout << map.Lookup("mojsedmikljuc") << std::endl;
            map.Remove("mojpetikljuc");
            std::cout << map.Lookup("mojsestikljuc") << std::endl;
        }
    } catch (const std::exception& e) {
        std::cout << "Exception occured: " << e.what() << std::endl;
    }
}

/// BENCHMARK(BM_HashTable);