#include <algorithm>
#include <benchmark/benchmark.h>
#include <iostream>
#include <memory>
#include <stdexcept>

template<typename Type>
class ArrayList {
public:
    ArrayList() = default;
    ArrayList(std::size_t size)
        : mArray(std::make_unique<Type[]>(size))
        , mSize(size) {}

    void Append(Type&& value) {
        if (mLastIndex == mSize) {
            if (mSize == 0) {
                mArray = std::make_unique<Type[]>(1);
                mSize  = 1;
            } else {
                auto temp = std::make_unique<Type[]>(mSize * 2);
                std::copy(mArray.get(), mArray.get() + mSize, temp.get());
                mArray = std::move(temp);
                mSize *= 2;
            }
        }
        mArray.get()[mLastIndex++] = std::forward<Type>(value);
    }
    const Type& Get(const std::size_t index) const {
        if (index >= mSize) {
            throw std::out_of_range("Trying to insert element at index " + std::to_string(index) +
                                    " while size is " + std::to_string(mSize));
        }
        return mArray.get()[index];
    }
    void Remove(const std::size_t index) {
        if (index >= mSize) {
            throw std::out_of_range("Trying to remove element at index " + std::to_string(index) +
                                    " while size is " + std::to_string(mSize));
        }
        std::copy(mArray.get() + index + 1, mArray.get() + mSize, mArray.get() + index);
        --mSize;
        --mLastIndex;
    }
    std::size_t Size() const { return mSize; }

private:
    std::unique_ptr<Type[]> mArray     = nullptr;
    std::size_t             mSize      = 0;
    std::size_t             mLastIndex = 0;
};

static void BM_ArrayList(benchmark::State& state) {
    try {
        for (auto _ : state) {
            ArrayList<int> array;
            for (int i = 0; i < state.range(0); ++i) {
                array.Append(i * i);
            }
            array.Remove(3);
        }
    } catch (const std::exception& e) {
        std::cout << "Exception occured: " << e.what() << std::endl;
    }
}

static void BM_StdVector(benchmark::State& state) {
    try {
        for (auto _ : state) {
            std::vector<int> array;
            for (int i = 0; i < state.range(0); ++i) {
                array.push_back(i * i);
            }
            array.erase(array.begin() + 3);
        }
    } catch (const std::exception& e) {
        std::cout << "Exception occured: " << e.what() << std::endl;
    }
}

/// BENCHMARK(BM_ArrayList)
///     ->Args({ 10 })
///     ->Args({ 100 })
///     ->Args({ 1000 })
///     ->Args({ 10000 })
///     ->Args({ 100000 });
///
/// BENCHMARK(BM_StdVector)
///     ->Args({ 10 })
///     ->Args({ 100 })
///     ->Args({ 1000 })
///     ->Args({ 10000 })
///     ->Args({ 100000 });