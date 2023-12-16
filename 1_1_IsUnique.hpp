#include <gtest/gtest.h>
#include <string>

bool isUnique(const std::string& input) {
    __int128_t mask = 0;
    for (const auto& c : input) {
        if (mask & (2 << c)) {
            return false;
        }
        mask |= (2 << c);
    }
    return true;
}

TEST(IsUniqueTest, UniqueString) {
    std::string input = "abcde";
    EXPECT_TRUE(isUnique(input));
}

TEST(IsUniqueTest, NonUniqueString) {
    std::string input = "hello";
    EXPECT_FALSE(isUnique(input));
}

TEST(IsUniqueTest, EmptyString) {
    std::string input = "";
    EXPECT_TRUE(isUnique(input)); // Assuming an empty string is considered unique
}

TEST(IsUniqueTest, SpecialCharacters) {
    std::string input = "!@#$%^&*()";
    EXPECT_TRUE(isUnique(input)); // Depends on your function's handling of special chars
}
